#ifndef RIVERFILE_H
#define RIVERFILE_H

#include <QFile>
#include <QtCore/QString>
#include <QStringList>
#include <QPrinter>

#define MAX_LINE_LENGTH    1024

/** String to print for numeric token */
#define NUMERIC_TOKEN "unknown command {%1}, which is a number.\n\tSkipping all numbers until a non-numeric token is reached.\n"
/** String to print for unknown token */
#define UNKNOWN_TOKEN "unknown command {%1}: line discarded\n"

class RiverFile : public QFile
{
    Q_OBJECT
public:
    explicit RiverFile(QObject *parent = 0);
    RiverFile (const QString &name, QObject *parent = 0);
    ~RiverFile ();
    void setup ();

    bool parse ();
    bool readHeader ();
    bool copyHeader (RiverFile *rfile);
    bool readData ();

    void editHeader ();
    void editData ();
    void saveHeader ();
    void saveData ();

    void writeHeader ();
    void writeData ();

    void print(QPrinter printer);

    QStringList *header;  /**< Header information (lines at top starting with '#') */
    int      line;        /**< Current line number of input */
    QStringList *tokens;  /**< Current line elements (tokens) */

    void skipLine ();     /**< skip rest of current line */
    void skipAllNumbers ();  /**< skip to next non-numeric token */
    void skipToEnd ();    /**< skip to next 'end' statement */

    /** checks for type and optional name in line after 'end' statement */
    bool checkEnd (QString type, QString name = QString(""));
    bool isEOL () {return tokens->isEmpty();} /**< is current token string empty? */
    bool isEOF (QString token);   /**< is it the end of file marker ('EOF')? */
    bool isNa (QString token);    /**< is it string 'na'? */
    bool isInt (QString token);   /**< can convert string to int value? */
    bool isFloat (QString token); /**< can convert string to float value? */
    bool readInt (int &val);      /**< read an integer value */
    bool readUnsigned (unsigned &val);    /**< read an unsigned integer value */
    bool readFloatOrNa (QString &na, float &val); /**< read float or 'na' */
    bool readFloatArray (float *farray); /**< read values to end or next token */
    bool readIntArray (int *iarray);  /**< read values to end or next token */
    bool readString (QString &string); /**< read to end of current line */

    void writeNewline ();
    void writeSpace ();
    void writeIndent (int indent);
    void writeString (int indent, QString keyword, QString option1 = QString (""), QString option2 = QString (""));
    void writeStringNR (int indent, QString keyword, QString option1 = QString (""));
    void writeFloatOrNa (float val);
    void writeFloat (double val);
    void writeInt (int val);
    void writeEnd (int indent, QString keyword, QString name);

    void handle_obsolete_token (QString obs_token, QString new_token = QString(""));
    void handle_unknown_token (QString token);

signals:
    void eof (bool);     /**< signals end of file reached */
    void dataChanged ();  /**< if data is changed in dialogs */

public slots:
    QString getToken (); /**< next space delimited string from file */
    QString popToken (); /**< check token for data and return it or "EOF" if no data found */
    void pushToken (QString token); /**< puts token back (to reprocesses) */

    void printEOF (QString data = QString (""));
    void printError (QString errmsg);
    void printMessage (QString msg);
    void printFileLine ();
};

#endif // RIVERFILE_H
