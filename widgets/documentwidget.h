#ifndef DOCUMENTWIDGET_H
#define DOCUMENTWIDGET_H

#include <QTreeWidget>
#include <QJsonArray>
#include <QTreeWidgetItem>

class DocumentWidget : public QTreeWidget
{

public:

    explicit DocumentWidget(QWidget *parent = nullptr);
    void recursiveBuild(QTreeWidgetItem* parent, const QJsonArray& array);

signals:
};

#endif // DOCUMENTWIDGET_H
