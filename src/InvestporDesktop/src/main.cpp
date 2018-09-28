#include "desktop/mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QMap>
#include <QList>

using desktop::MainWindow;

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(InvestporLib);

    QApplication a(argc, argv);
    a.setOrganizationName("ukll");
    a.setOrganizationDomain("ukll.github.io");
    a.setApplicationName("Investpor");
    a.setApplicationVersion("0.1.0");

    QMap<QString, QList<QTranslator*> > langTranslatorMap;

    QList<QTranslator*> enTranslatorList;
    QTranslator *enDesktopTranslator = new QTranslator(qApp);
    QTranslator *enLibTranslator = new QTranslator(qApp);
    enDesktopTranslator->load(":/translations/InvestporDesktop_en_US.qm");
    enLibTranslator->load(":/translations/InvestporLib_en_US.qm");
    enTranslatorList << enDesktopTranslator << enLibTranslator;
    langTranslatorMap.insert(QStringLiteral("en_US"), enTranslatorList);

    QList<QTranslator*> trTranslatorList;
    QTranslator *trDesktopTranslator = new QTranslator(qApp);
    QTranslator *trLibTranslator = new QTranslator(qApp);
    trDesktopTranslator->load(":/translations/InvestporDesktop_tr_TR.qm");
    trLibTranslator->load(":/translations/InvestporLib_tr_TRqm");
    trTranslatorList << trDesktopTranslator << trLibTranslator;
    langTranslatorMap.insert(QStringLiteral("tr_TR"), trTranslatorList);

    MainWindow w(&langTranslatorMap);
    w.show();

    return a.exec();
}
