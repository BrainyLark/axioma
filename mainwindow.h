#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QJsonArray>
#include <QVBoxLayout>

#include "DocumentReader.h"
#include "documentwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    // Initial setup methods
    void initialSetup();
    void documentSetup();
    void commandSetup();

    // visible elements
    Ui::MainWindow *ui;
    DocumentWidget* documentWidget;
    QVBoxLayout* userCmdBox;

    // background elements
    QThread* workerThread;
    DocumentReader* documentReader;

public slots:
    void onDataFetched(const QJsonArray& results);
    void onFetchError(const QString& error);

signals:
    void requestFetchData(const QString& filepath);

};
#endif // MAINWINDOW_H
