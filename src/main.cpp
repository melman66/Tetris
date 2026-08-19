#include <QApplication>
#include "ui/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/res/src/tet.ico"));
    MainWindow window;
    window.show();
    return app.exec();
}
