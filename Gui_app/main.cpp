#include "AnalyzerWinFrame.h"
#include <QTextCodec>
#include <QApplication>
#include "systemroot.h"
int main(int argc, char *argv[])
{
    //![设置编码格式]
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QApplication a(argc, argv);
    SystemRoot root;
    if(root.Start())
    {
        return a.exec();
    }
}
