# Upgrade regression checks

This Qt Test target exercises the real upgrade page and startup flow without
opening a serial port or flashing a board. It covers removal of the board
selector, power-board firmware filtering and refresh, target ID `0x02` for
upgrade and version queries, an empty firmware list, and startup without login.

Build the release libraries first using the same Qt kit as the application:
`Configs`, `Utility`, `Preset`, `Logger`, `Language`, `cc`, then `Core`.
Run `qmake <source>/tests/upgrade_regression.pro` followed by your kit's make
tool from a dedicated, otherwise empty shadow-build directory.

Add `<source>/bin/Release` and the Qt kit's `bin` directory to `PATH` before
running `run/upgrade_regression.exe`. For a headless run, set
`QT_QPA_PLATFORM=offscreen` and `QT_QUICK_BACKEND=software`.

The tests create and remove their own `Data` directory beside `run`, and refuse
to overwrite an existing one. Startup also initializes the application's
existing preset/log paths in `D:/LumigenxTool`, just as a normal launch does.
