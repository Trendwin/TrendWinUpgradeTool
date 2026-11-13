#include <QtTest>
#include <QComboBox>
#include <QDialog>
#include <QDir>
#include <QFile>
#include <QPushButton>
#include <QTimer>
#include "AnalyzerWinFrame.h"
#include "filepathmgr.h"
#include "languageManager.h"
#include "systemroot.h"
#include "upgradeObj_config.h"
#include "upgradepage.h"

class UpgradeRegression : public QObject
{
    Q_OBJECT
private:
    QString dataPath;
    QString powerPath;
    bool ownsData = false;

    bool writeFile(const QString &path, const QByteArray &content)
    {
        if (!QDir().mkpath(QFileInfo(path).absolutePath()))
            return false;
        QFile file(path);
        return file.open(QIODevice::WriteOnly) && file.write(content) == content.size();
    }

private slots:
    void initTestCase()
    {
        // This target must run from its own empty shadow-build directory.
        dataPath = QDir::cleanPath(QCoreApplication::applicationDirPath() + "/../Data");
        QVERIFY2(!QFileInfo::exists(dataPath), "Use a clean, dedicated shadow-build directory");
        ownsData = true;
        powerPath = dataPath + QStringLiteral("/UpgradeBin/功率驱动板");
        const QByteArray config = QStringLiteral(
            "[{\"Product\":\"功率驱动板\",\"ID\":2,\"Prefix\":\"TrendOne_APP\"},"
            "{\"Product\":\"通讯拓展板\",\"ID\":3,\"Prefix\":\"TrendOne_Comm\"}]").toUtf8();
        QVERIFY(writeFile(dataPath + "/Config/upgradeObj.json", config));
        QString error;
        QVERIFY2(UpGradeObj_Config::Instance()->Load(dataPath + "/Config", error), qPrintable(error));
        QVERIFY(writeFile(powerPath + "/TrendOne_APP_test.bin", "firmware"));
        QVERIFY(writeFile(powerPath + "/TrendOne_Comm_wrong.bin", "wrong board"));
        QVERIFY(writeFile(powerPath + "/TrendOne_APP_notes.txt", "not firmware"));
        QVERIFY(writeFile(powerPath + "/nested/TrendOne_APP_nested.bin", "nested"));
        QVERIFY(writeFile(dataPath + QStringLiteral("/UpgradeBin/通讯拓展板/TrendOne_Comm_test.bin"), "other board"));
    }

    void boardSelectorIsRemoved()
    {
        FilePathMgr paths;
        LanguageManager language;
        UpGradeCtrlMgr controller;
        UpgradePage page(&paths, &language, &controller);
        QVERIFY(!page.findChild<QWidget *>("upobj_combox"));
        QVERIFY(!page.findChild<QWidget *>("label_productType"));
    }

    void firmwareListAndRefreshUseOnlyPowerBoard()
    {
        FilePathMgr paths;
        LanguageManager language;
        UpGradeCtrlMgr controller;
        UpgradePage page(&paths, &language, &controller);
        auto files = page.findChild<QComboBox *>("upBinFile_combox");
        QVERIFY(files);
        QCOMPARE(files->count(), 1);
        QCOMPARE(files->currentText(), QString("TrendOne_APP_test.bin"));
        QVERIFY(writeFile(powerPath + "/TrendOne_APP_new.bin", "new firmware"));
        QVERIFY(QMetaObject::invokeMethod(&page, "on_btnRefreshUpgradeFile_clicked"));
        QCOMPARE(files->count(), 2);
        QVERIFY(QFile::remove(powerPath + "/TrendOne_APP_new.bin"));
    }

    void upgradeAndVersionQueryTargetPowerBoard()
    {
        FilePathMgr paths;
        LanguageManager language;
        UpGradeCtrlMgr controller;
        UpgradePage page(&paths, &language, &controller);
        // Observe the requested operation without opening a port or flashing hardware.
        QObject::disconnect(&page, &UpgradePage::sigStartUpgrade,
                            &controller, &UpGradeCtrlMgr::onStartInstrUpgrade);
        QObject::disconnect(&page, &UpgradePage::sigQueryVersion,
                            &controller, &UpGradeCtrlMgr::onQueryDevVersionInfo);
        QSignalSpy upgrade(&page, &UpgradePage::sigStartUpgrade);
        QSignalSpy query(&page, &UpgradePage::sigQueryVersion);
        QVERIFY(QMetaObject::invokeMethod(&page, "on_btn_StartUpgrade_clicked"));
        QCOMPARE(upgrade.count(), 1);
        QCOMPARE(QDir::cleanPath(upgrade.at(0).at(0).toString()), powerPath + "/TrendOne_APP_test.bin");
        QCOMPARE(upgrade.at(0).at(1).toUInt(), 2u);
        QVERIFY(QMetaObject::invokeMethod(&page, "on_btnQueryVersion_clicked"));
        QCOMPARE(query.count(), 1);
        QCOMPARE(query.at(0).at(0).toUInt(), 2u);
    }

    void emptyFirmwareListDoesNotStartUpgrade()
    {
        QVERIFY(QFile::remove(powerPath + "/TrendOne_APP_test.bin"));
        FilePathMgr paths;
        LanguageManager language;
        UpGradeCtrlMgr controller;
        UpgradePage page(&paths, &language, &controller);
        QSignalSpy upgrade(&page, &UpgradePage::sigStartUpgrade);
        auto files = page.findChild<QComboBox *>("upBinFile_combox");
        QVERIFY(files);
        QCOMPARE(files->count(), 0);
        QVERIFY(QMetaObject::invokeMethod(&page, "on_btn_StartUpgrade_clicked"));
        QCOMPARE(upgrade.count(), 0);
    }

    void startupShowsMainWindowWithoutLogin()
    {
        SystemRoot root;
        bool loginShown = false;
        QTimer escapeLogin;
        escapeLogin.setSingleShot(true);
        connect(&escapeLogin, &QTimer::timeout, [&] {
            for (QWidget *widget : QApplication::topLevelWidgets()) {
                if (auto dialog = qobject_cast<QDialog *>(widget)) {
                    if (dialog->isVisible()) {
                        loginShown = true;
                        dialog->reject();
                    }
                }
            }
        });
        escapeLogin.start(200);
        const bool started = root.Start();
        escapeLogin.stop();
        bool mainShown = false;
        for (QWidget *widget : QApplication::topLevelWidgets()) {
            if (auto main = qobject_cast<AnalyzerWinFrame *>(widget)) {
                mainShown = main->isVisible();
                main->close();
                delete main;
            }
        }
        QVERIFY(!loginShown);
        QVERIFY(started);
        QVERIFY(mainShown);
    }

    void cleanupTestCase()
    {
        if (ownsData)
            QVERIFY(QDir(dataPath).removeRecursively());
    }
};

QTEST_MAIN(UpgradeRegression)
#include "tst_upgrade_regression.moc"
