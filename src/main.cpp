#include <QApplication>
#include <QIcon>

#include "mainwindow.h"
#include "metadata.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    QIcon i(a.applicationDirPath() + QString("river.png"));
    a.setApplicationName(metadata::name());
    a.setApplicationVersion(metadata::version());
//    a.setWindowIcon(QIcon(QString("river.png")));
//    a.setWindowIcon();
    MainWindow w;
    w.show();

    return a.exec();
}
