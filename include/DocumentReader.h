#ifndef DOCUMENTREADER_H
#define DOCUMENTREADER_H

#include <QObject>
#include <QJsonArray>

#include <QDebug>
class DocumentReader : public QObject {

    Q_OBJECT

public:
    DocumentReader(const QString& filepath);

signals:
    void dataFetched(const QJsonArray& result);
    void fetchError(const QString& error);

private:
    QString filepath;

public slots:
    void fetchFile();

};

#endif // DOCUMENTREADER_H
