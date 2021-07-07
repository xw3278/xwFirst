#include "mainwindow.h"
#include <QApplication>
#include "sectiondraw.h"

void registerType()
{
   qmlRegisterType<SectionDraw>("SectionDraw", 1, 0, "SectionDraw");
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    registerType();

    MainWindow* mainWindow = MainWindow::createObj();
    Q_CHECK_PTR(mainWindow);

    a.processEvents();
    return a.exec();
}
