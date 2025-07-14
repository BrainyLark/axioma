#ifndef CMDEXECUTION_H
#define CMDEXECUTION_H

#include <QObject>
#include <QStringList>

class CmdExecution : public QObject
{
    Q_OBJECT

public:

    // establish connection here probably
    explicit CmdExecution(QObject *parent = nullptr);

    // takes user query, document dirs and tool descriptions
    // to generate the response asynchronously.
    void execute(QString userCmd, QStringList documentDirs);

public slots:
    // response is generated, processed and parsed here.
    // it should probably emit a signal that the UI keeps
    // concatenating the response onto the screen.
    void handle_response();

signals:
};

#endif // CMDEXECUTION_H
