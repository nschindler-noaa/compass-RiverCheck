#ifndef METADATA_H
#define METADATA_H

#include <QString>

#define APPLICATION_NAME   "River Description File Checker"
#define VER_MAJOR_RELEASE   1
#define VER_MINOR_RELEASE   2
#define VER_BUGFIX          2
#define VER_RELEASE_LEVEL  "rc1"
#define BUILD_DATE         "25 Feb 2016"
#define MODIFIER           "Neal E. Schindler"
#define CREATOR            "Neal E. Schindler"
#define CREATED_DATE       "02 Jan 2013"

class metadata
{
public:
    metadata();

    static QString name ()        {return QString(APPLICATION_NAME);}

    static QString creator ()     {return QString(CREATOR);}
    static QString createdDate () {return QString(CREATED_DATE);}

    static QString modifier ()    {return QString (MODIFIER);}
    static QString version ();
    static QString versionDate () {return QString (BUILD_DATE);}
};

#endif // METADATA_H
