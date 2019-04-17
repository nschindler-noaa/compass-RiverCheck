#include <iostream>

#include "Log.h"
#define DEFAULT_LOGNAME  "COMPASSXXXX.log"

static Log *outputlog = nullptr;

Log *Log::instance (QObject *parent)
{
    if (outputlog == nullptr)
        outputlog = new Log (parent);

    return outputlog;
}

Log *Log::instance (QString filename, QObject *parent)
{
    if (outputlog == nullptr)
        outputlog = new Log (filename);

    return outputlog;
}


Log::Log (QString filename, QObject *parent)
{
    setLogFile (filename);
    setup ();
    outputlog = this;
}

Log::Log (QObject *parent)
{
    setLogFile ();
    setup ();
    outputlog = this;
}

void Log::setup ()
{
    prefix.append ("*ERROR*: ");
    prefix.append ("Warning: ");
    prefix.append ("  ");
    prefix.append ("RawData: ");
    prefix.append ("--debug: ");
    prefix.append ("  FATAL! ");
    prefix.append (" ");

    lastLine = QString ("");
    repCount = 0;

    logFileName = logFile->fileName ();
    logFile->open ();
}

void Log::setLogFile (QString filename)
{
    if (filename.isEmpty())
    {
        filename.append (DEFAULT_LOGNAME);
    }
    deleteLogFile ();
    logFile = new QTemporaryFile (filename);
    logFileName = logFile->fileName ();
    logFile->open ();
}

Log::~Log()
{
    deleteLogFile ();
    outputlog = nullptr;
}


void Log::deleteLogFile ()
{
    if (outputlog != nullptr)
    {
        if (logFile != nullptr)
        {
            logFile->close ();
            delete logFile;
        }
    }
}

void Log::add (MessageType id, QString msg)
{
    bool addtolog = true;
    QByteArray bytes;
    bytes.append(prefix[id]);
    bytes.append(msg);
    bytes.append('\n');

    switch (id)
    {
    case Warning:
        addtolog = warning;
        break;
    case Message:
        addtolog = message;
        break;
    case RawDump:
        addtolog = rawdump;
        break;
    case Debug:
        addtolog = debug;
        break;
    default:
        addtolog = true;
    }

    if (addtolog)
    {
        // add to the display
        addToDisplay (bytes);
    }
    // always add to the temp file
    logFile->write(bytes);
//    logFile->write (msg.data(), msg.size());
}

void Log::addToDisplay (QString text)
{
    if (lastLine.compare (text) == 0)
    {
        repCount++;
    }
    else
    {
        if (repCount > 0)
        {
            if (repCount > 1)
            {
                display (QString("       last line repeated %1 times.")
                         .arg (QString::number (repCount)));
            }
            else
            {
                display ("       last line repeated 1 time.");
            }
            repCount = 0;
        }
        display (text);
        lastLine = text;
    }
}

void Log::display (QString text)
{
    std::cout << text.data () << std::endl;
}

void Log::setMessage (bool flag)
{
    message = flag;
}

void Log::setWarning (bool flag)
{
    warning = flag;
}

void Log::setRawDump (bool flag)
{
    rawdump = flag;
}

void Log::setDebug (bool flag)
{
    debug = flag;
}

void Log::clear ()
{
    logFile->close ();
    logFile->open ();
}
