#include <QApplication>
#include <QIcon>

#include "mainwindow.h"
#include "metadata.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName(metadata::name());
    a.setApplicationVersion(metadata::version());
    MainWindow w;
    w.show();

    return a.exec();
}
