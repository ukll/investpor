#include "investpor/gui/HeaderFiles/mainwindow.h"
#include <QApplication>

using investpor::gui::MainWindow;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
