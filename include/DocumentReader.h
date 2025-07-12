#ifndef DOCUMENTREADER_H
#define DOCUMENTREADER_H

#include <QObject>
#include <QJsonArray>

#include <QDebug>
class DocumentReader : public QObject {

    Q_OBJECT

public:
    DocumentReader(const QString& filepath);
    const QJsonArray& data();

signals:
    void dataFetched(const QJsonArray& result);
    void fetchError(const QString& error);

private:
    QJsonArray items;
    QString filepath;

public slots:
    void fetchFile();

};

#endif // DOCUMENTREADER_H
