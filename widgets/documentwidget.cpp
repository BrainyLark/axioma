#include "documentwidget.h"

#include <QJsonValue>
#include <QJsonObject>

DocumentWidget::DocumentWidget(QWidget *parent)
    : QTreeWidget{parent}
{}

void DocumentWidget::recursiveBuild(QTreeWidgetItem *parent, const QJsonArray &array)
{
    for (const QJsonValue& value : array) {
        QJsonObject object = value.toObject();

        QString name = object["name"].toString();
        QString type = object["type"].toString();
        QString path = object["path"].toString();


        QTreeWidgetItem* item;

        if (parent == nullptr) {
            item = new QTreeWidgetItem(this);
        } else {
            item = new QTreeWidgetItem(parent);
        }

        item->setText(0, name);
        item->setText(1, path);
        item->setText(2, type);

        if (object.contains("children")) {
            recursiveBuild(item, object["children"].toArray());
        }
    }
}
