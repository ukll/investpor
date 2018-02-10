#include "investpor/gui/mainwindow.h"
#include <QApplication>

using investpor::gui::MainWindow;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("ukll");
    a.setOrganizationDomain("ukll.github.io");
    a.setApplicationName("Investpor");
    a.setApplicationVersion("0.1.0");

    MainWindow w;
    w.show();

    return a.exec();
}
