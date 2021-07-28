#include "metadata.h"

static QString ver;
static QString longorg;

metadata::metadata()
{
}

QString metadata::bigOrg()
{
    return QString("National Oceanic and Atmospheric Administration");
}

QString metadata::bigAcronym()
{
    return QString("NOAA");
}

QString metadata::medOrg()
{
    return QString("National Marine Fisheries Service");
}

QString metadata::medAcronym()
{
    return QString("NMFS");
}

QString metadata::smallOrg()
{
    return QString("Northwest Fisheries Science Center");
}

QString metadata::smallAcronym()
{
    return QString("NWFSC");
}

QString metadata::version()
{
    QString major = (QString::number(VER_MAJOR_RELEASE));
    QString minor = (QString::number(VER_MINOR_RELEASE));
    QString bugfix = (QString::number(VER_BUGFIX));
    QString release (VER_RELEASE_LEVEL);
    QString rels ("");
    if (!release.isEmpty())
    {
    if      (release.contains('a'))
        rels.append ("-alpha");
    else if (release.contains('b'))
        rels.append ("-beta");
    else if (release.contains('1'))
        rels.append("-RC1");
    else if (release.contains('2'))
        rels.append("-RC2");
    else if (release.contains('3'))
        rels.append("-RC3");
    }

    ver = QString("%1.%2.%3%4").arg (major, minor, bugfix, rels);
    return ver;
}
