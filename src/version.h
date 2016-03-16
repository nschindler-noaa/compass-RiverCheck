#ifndef VERSION_H
#define VERSION_H

class version
{
public:
    version();

    QString versionDate();
    void setVersionDate (QString dt);
    void setVersion (QString ver);

private:
    QString build_date;
    QString history;
    QString creator_name;
    QString modifier_name;
};

#endif // VERSION_H
