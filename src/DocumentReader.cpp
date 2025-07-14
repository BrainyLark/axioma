#include "DocumentReader.h"

#include <QFile>
#include <QByteArray>
#include <QJsonDocument>
#include <QThread>
DocumentReader::DocumentReader(const QString& filepath)
{
    qInfo() << "DocumentReader object is spawned!" << filepath;
    this->filepath = filepath;
}


void DocumentReader::fetchFile()
{
    QFile file{this->filepath};

    if(!file.open(QIODevice::ReadOnly)) {
        emit fetchError("There is a problem opening the file");
        return;
    }

    QByteArray bytes = file.readAll();
    QJsonDocument document = QJsonDocument::fromJson(bytes);

    emit dataFetched(document.array());
}

