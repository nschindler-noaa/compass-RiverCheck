#include "metadata.h"

static QString ver;

metadata::metadata()
{
}


QString metadata::version()
{
    QString major = (QString::number(VER_MAJOR_RELEASE));
    QString minor = (QString::number(VER_MINOR_RELEASE));
    QString bugfix = (QString::number(VER_BUGFIX));
    QString rels ("-");
    if      (QString(VER_RELEASE_LEVEL).contains('a'))
        rels.append ("alpha");
    else if (QString(VER_RELEASE_LEVEL).contains('b'))
        rels.append ("beta");
    else if (QString(VER_RELEASE_LEVEL).contains('1'))
        rels.append("RC1");
    else if (QString(VER_RELEASE_LEVEL).contains('2'))
        rels.append("RC2");
    else if (QString(VER_RELEASE_LEVEL).contains('3'))
        rels.append("RC3");

    ver = QString("%1.%2.%3%4").arg (major, minor, bugfix, rels);
    return ver;
}
