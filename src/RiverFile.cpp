#include "RiverFile.h"
#include "Log.h"
#include <QRegExp>
#include <QtCore/QString>
#include <QtGui/QMessageBox>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QLineEdit>
#include <QtGui/QBoxLayout>
#include <QtGui/QSpacerItem>
#include <qstring.h>

//#include "nsqstringlisteditdialog.h"
#include "qstringlisteditdialog.h"

RiverFile::RiverFile(QObject *parent) :
    QFile(parent)
{
    setup ();
}

RiverFile::RiverFile (const QString &name, QObject *parent) :
    QFile (name)
{
    setup ();
}

void RiverFile::setup ()
{
    header = new QStringList ();
    line = 0;
    tokens = new QStringList ();
}

RiverFile::~RiverFile ()
{
    delete header;
    delete tokens;
//    ~QFile();
}

bool RiverFile::parse ()
{
    bool okay = this->open (QIODevice::ReadOnly);

    if (okay) okay = readHeader ();
    if (okay) okay = readData ();

    close ();
    return okay;
}

bool RiverFile::readHeader ()
{
    bool okay = true, end = false;
    QString token ("");
    int lineno = 1;

    while (okay && !end)
    {
        token = popToken ();
        while (lineno < line)
        {
            header->append(QString(" "));
            lineno++;
        }
        if (token.contains ("EOF", Qt::CaseInsensitive))
        {
            printEOF ("Header information");
            okay = false;
        }
        else if (token.contains ("#====="))
        {
            skipLine ();
        }
        else if (token.startsWith ("#"))
        {
            pushToken (token);
            okay = readString (token);
            header->append (token);
        }
        else
        {
            pushToken (token);
            end = true;
        }
        lineno++;
    }

    return okay;
}

bool RiverFile::copyHeader(RiverFile *rfile)
{
    bool okay = true;
    for (int i = 0; i < rfile->header->count(); i++)
    {
        header->append(rfile->header->at(i));
    }
    return okay;
}

bool RiverFile::readData ()
{
    bool okay = true;
    return okay;
}

void RiverFile::editHeader ()
{
    QString name(fileName());
    QStringListEditDialog *dial = new QStringListEditDialog(QString("File Header: %1").arg(name), header);
//    nsQStringListEditDialog dial (QString("File Header"), *header);
    connect (dial, SIGNAL(dataChanged()), SIGNAL(dataChanged()));
    dial->exec();
    delete dial;
/*
    QDialog *headerDialog = new QDialog ();
    QBoxLayout *hdLayout = new QBoxLayout (QBoxLayout::TopToBottom);

    headerDialog->setWindowTitle(QString ("File %1 Header").arg (
                                     fileName()));

    for (int i = 0; i < header->count(); i++)
    {
        hdLayout->addWidget(new QLineEdit (header->at(i), headerDialog));
//        QLineEdit *d = ;
    }
    hdLayout->addSpacerItem(new QSpacerItem (0, 0, QSizePolicy::Preferred, QSizePolicy::Expanding));

    QDialogButtonBox *buttons = new QDialogButtonBox (
                QDialogButtonBox::Save |
                QDialogButtonBox::Cancel,
                Qt::Horizontal,
                headerDialog);
    connect (buttons, SIGNAL(accepted()), SLOT(saveHeader()));
    connect (buttons, SIGNAL(rejected()), headerDialog, SLOT(close()));

    hdLayout->addWidget(buttons);

    headerDialog->setLayout(hdLayout);
    headerDialog->exec();

    delete headerDialog;*/
}

void RiverFile::saveHeader ()
{

}

void RiverFile::editData ()
{

}

void RiverFile::saveData()
{

}

void RiverFile::writeData ()
{
    if (open (QIODevice::WriteOnly))
    {
        writeHeader ();
        if (fileName ().endsWith ("rls", Qt::CaseInsensitive))
        {
//            writeReleaseData (this);
        }

    }
    else
    {
        Log::instance ()->add (Log::Error, QString("Could not write to file: %1!")
                               .arg (fileName ()));
    }
}

void RiverFile::writeHeader ()
{
//    QString sep ("#==========================================================");
    this->open(QIODevice::WriteOnly);
//    this->writeString (0, sep);
    for (int i = 0; i < header->count(); i++)
    {
        if (header->at (i).isEmpty() || header->at (i) == " ")
            writeNewline();
        else
            writeString (0, header->at (i));
    }
//    writeString (0, sep);
}

//bool RiverFile::read
bool RiverFile::readString (QString &string)
{
    bool okay = true;
    string.clear ();
    if (tokens->count () > 0)
    {
        string.append (tokens->takeFirst ());
        while (tokens->count() > 0)
        {
            QString token (tokens->takeFirst());
            token.remove('\t');
            token.remove(' ');
            string.append (' ');
            string.append (token);
        }
    }
    else
    {
        okay = false;
    }
    return okay;
}

QString RiverFile::getToken ()
{
    while (tokens->isEmpty ())
    {
        QString rline ("");
        while (rline.length () < 2)
        {
            rline.clear ();
            if (this->atEnd ())
            {
                rline.append ("EOF");
            }
            else
            {
                rline.append (this->readLine (MAX_LINE_LENGTH));
                rline.remove('\n');
                rline.remove('\r');
            }
            line++;
        }
        delete tokens;
        tokens = new QStringList (rline.split ('\t', QString::SkipEmptyParts));
        readString (rline);
        delete tokens;
        tokens = new QStringList (rline.split(' ', QString::SkipEmptyParts));
    }

    return tokens->takeFirst ();
}

QString RiverFile::popToken ()
{
    QString token ("");
    token.append (getToken ());
    if (token.length() == 0)
        token.append (getToken ());
    if (token.compare(" ") == 0)
    {
        token.clear();
        token.append(getToken());
    }
    else if (token.compare("\t") == 0)
    {
        token.clear();
        token.append(getToken());
    }
/*    if (token.length () < 2)
    {
        QRegExp rx ("[a-z] | [A-Z] | [d] | [#]");
        token.contains (rx);
        if (rx.isEmpty())
            token = getToken ();
    }*/
#ifdef DEBUG
    Log::instance ()->add (Log::Debug, QString ("size of token %1 is %2").arg
                           (token, QString::number (token.size ())));
#endif
    return token;
}

void RiverFile::pushToken (QString token)
{
//    tokens->prepend (" ");
    tokens->prepend (token);
}

void RiverFile::skipLine ()
{
    tokens->clear ();
}

void RiverFile::skipAllNumbers()
{
    bool end = false;
    QString token;
    skipLine ();
    while (!end)
    {
        token = popToken ();
        if (token.compare ("eof", Qt::CaseInsensitive) == 0)
        {
            printEOF("skipping numbers");
        }
        else if (isFloat (token))
        {
            skipLine ();
        }
        else
        {
            pushToken (token);
            end = true;
        }
    }
}

void RiverFile::skipToEnd ()
{
    QString token;
    tokens->clear ();
    token = popToken ();
    while (!token.contains ("eof", Qt::CaseInsensitive))
    {
        if (token.contains ("end", Qt::CaseInsensitive))
        {
            pushToken (token);
            break;
        }
        skipLine ();
    }
}

bool RiverFile::checkEnd (QString type, QString name)
{
    bool okay = true;
    QString token = popToken ();
    QString compare;
    if (token.contains('('))
    {
        compare = token.remove('(');
        while (!compare.contains(')'))
        {
            compare.append(' ');
            compare.append (popToken());
        }
        compare.remove(')');
        if (!name.contains(compare, Qt::CaseInsensitive))
        {
            QString msg (QString("{end} statement name '%1' does not match expected '%2'")
                         .arg (compare, name));
            printMessage (msg);
        }
    }
    else if (!token.contains (type, Qt::CaseInsensitive))
    {
        QString msg (QString("{end} statement type '%1' does not match expected '%2'")
                     .arg (token, type));
        printMessage(msg);
        okay = false;
    }
    else
    {
        if (!name.isEmpty ())
        {
            if (!isEOL ())
            {
                token = popToken ();
                if (!token.contains (name.section(' ', 0, -2), Qt::CaseInsensitive))
                {
                    QString msg (QString("{end} statement name '%1' does not match expected '%2'")
                                 .arg (token, name));
                    printMessage (msg);
                }
            }
        }
    }
    if (!isEOL())
        skipLine();

    return okay;
}

bool RiverFile::isNa (QString token)
{
    return (token.compare ("na", Qt::CaseInsensitive) == 0);
}

bool RiverFile::isEOF (QString token)
{
    return (token.compare ("eof", Qt::CaseInsensitive) == 0);
}

bool RiverFile::isInt (QString token)
{
    bool okay = true;
    token.toInt (&okay);
    return okay;
}

bool RiverFile::isFloat (QString token)
{
    bool okay = true;
    token.toFloat (&okay);
    return okay;
}

bool RiverFile::readFloatOrNa (QString &na, float &val)
{
    bool okay = true;
    na.clear ();
    val = -1.0;
    na.append (popToken ());
    if (isEOF (na))
        okay = false;
    else if (isNa (na))
        okay = false;
    else
        val = na.toFloat (&okay);

    return okay;
}

bool RiverFile::readInt (int &val)
{
    bool okay = true;
    QString token = popToken ();
    val = -1;

    if (isEOF (token))
    {
        okay = false;
        printEOF ("integer value");
    }
    else
    {
        val = token.toInt (&okay);
    }

    return okay;
}
bool RiverFile::readUnsigned (unsigned &val)
{
    bool okay = true;
    QString token = popToken ();
    val = -1;

    if (isEOF (token))
    {
        okay = false;
        printEOF ("integer value");
    }
    else
    {
        val = token.toUInt(&okay);
    }

    return okay;
}

bool RiverFile::readFloatArray (float *farray)
{
    bool okay = true;


    return okay;
}

bool RiverFile::readIntArray (int *iarray)
{
    bool okay = true;

    return okay;
}

void RiverFile::writeNewline ()
{
    write ("\n", 1);
}

void RiverFile::writeSpace ()
{
    write (" ", 1);
}

void RiverFile::writeIndent (int indent)
{
    for (int i = 0; i < indent; i++)
        write ("\t", 1);
}

void RiverFile::writeString (int indent, QString keyword, QString option1, QString option2)
{
    QByteArray bytes;
    writeIndent(indent);
    bytes.append(keyword);

    if (!option1.isEmpty())
    {
        bytes.append(QString(" %1").arg(option1));
//        writeSpace();
  //      write (option1.data(), option1.size());
    }
    if (!option2.isEmpty())
    {
        bytes.append(QString(" %1").arg(option2));
//        writeSpace();
  //      write (option2.data(), option2.size());
    }
    write (bytes);
    writeNewline();
}

void RiverFile::writeStringNR (int indent, QString keyword, QString option1)
{
    QByteArray bytes;
    writeIndent(indent);
    bytes.append(keyword);
//    this << keyword;
//    write (keyword.toAscii());
    if (!option1.isEmpty())
    {
        bytes.append(QString(" %1").arg(option1));
//        writeSpace();
  //      this << option1;
//        write (option1.data(), option1.size());
    }
    write (bytes);
}

void RiverFile::writeFloatOrNa (float val)
{
    if (val == -1)
        write ("na");
    else
        writeFloat (val);
}

void RiverFile::writeFloat (double val)
{
    QByteArray bytes;
    bytes.append(QString::number(val, 'g', 6));
    write (bytes);
//    write (QString::number(val, 'g', 6).data());
}

void RiverFile::writeInt (int val)
{
    QByteArray bytes;
    bytes.append(QString::number(val));
    write (bytes);
}

void RiverFile::writeEnd(int indent, QString type, QString name)
{
    QString namestring (QString ("(%1)").arg(name));
    if (name.isEmpty())
        writeString (indent, "end", type);
    else
        writeString (indent, "end", type, namestring);
}

void RiverFile::printEOF (QString data)
{
    if (data.isEmpty ())
        printMessage ("Found EOF.");
    else
        printError (QString ("Found EOF instead of %1.").arg (data));
}

void RiverFile::printMessage (QString msg)
{
    Log::instance ()->add (Log::Message, msg);
    printFileLine ();
}

void RiverFile::printError (QString errmsg)
{
    Log::instance ()->add (Log::Error, errmsg);
    printFileLine ();
}

void RiverFile::printFileLine ()
{
    QString fileline (QString("File: %1, Line: %2").arg
                      (fileName (), QString::number (line)));
    Log::instance ()->add (Log::Force, fileline);
}

void RiverFile::handle_unknown_token (QString token)
{
    bool isFloat;
    token.toFloat (&isFloat);
    QString msg("");

    if (isFloat)
    {
        msg.append (QString (NUMERIC_TOKEN).arg (token));
        skipAllNumbers();
    }
    else
    {
        msg.append (QString (UNKNOWN_TOKEN).arg (token));
        skipLine();
    }
    printFileLine();
}

void RiverFile::handle_obsolete_token (QString obs_token, QString new_token)
{
        QString message (QString("obsolete token {%1}. ").arg(obs_token));

        if (new_token.isEmpty())
        {
                message.append ("Data discarded.\n");
                skipLine();
        }
        else
        {
                message.append (QString ("Replaced with {%1).\n").arg(new_token));
                pushToken(new_token);
        }
        printError(message);
}

void RiverFile::print(QPrinter printer)
{

}
