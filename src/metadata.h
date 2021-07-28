#ifndef METADATA_H
#define METADATA_H

#include <QString>

#define APPLICATION_NAME   "Compass River Description File Checker"
#define VER_MAJOR_RELEASE   1
#define VER_MINOR_RELEASE   3
#define VER_BUGFIX          0
#define VER_RELEASE_LEVEL  "b"
#define BUILD_DATE         "2021-07-28"
#define ORGANIZATION       "NOAA-NWFSC"

#define MODIFIER           "Neal Schindler"
#define LAST_MODIFIED      "2021 Jul 28"

#define CREATOR            "Neal Schindler"
#define CREATED_DATE       "2013 Jan 02"

class metadata
{
public:
    metadata();

    static QString name ()        {return QString(APPLICATION_NAME);}
    static QString org ()         {return QString(ORGANIZATION);}
    static QString bigOrg ();
    static QString bigAcronym ();
    static QString medOrg ();
    static QString medAcronym ();
    static QString smallOrg ();
    static QString smallAcronym ();

    static QString creator ()     {return QString(CREATOR);}
    static QString createdDate () {return QString(CREATED_DATE);}

    static QString modifier ()    {return QString (MODIFIER);}
    static QString modifiedDate() {return QString (LAST_MODIFIED);}

    static QString version ();
    static QString versionDate () {return QString (BUILD_DATE);}
};

#endif // METADATA_H
