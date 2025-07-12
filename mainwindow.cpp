#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initialSetup();
}

MainWindow::~MainWindow()
{
    delete ui;

    delete documentReader;
    delete documentWidget;
}

void MainWindow::initialSetup()
{
    qInfo() << "Initiating initial setup";
    qInfo() << "I am starting document setup";

    documentSetup();
}

void MainWindow::documentSetup()
{
    // Create necessary objects and threads

    documentWidget = new DocumentWidget();
    setCentralWidget(documentWidget);

    QString documentFilePath = "C:\\Users\\erden\\QtProjects\\Axioma\\data\\tree.json";
    documentReader = new DocumentReader(documentFilePath);

    workerThread = new QThread();


    documentReader->moveToThread(workerThread);

    // Establish connections between signals and slots
    QObject::connect(workerThread,
                     &QThread::started, documentReader,
                     &DocumentReader::fetchFile);

    QObject::connect(documentReader, &DocumentReader::dataFetched,
                     this, &MainWindow::onDataFetched);

    QObject::connect(documentReader, &DocumentReader::fetchError,
                     this, &MainWindow::onFetchError);

    workerThread->start();
}

void MainWindow::onDataFetched(const QJsonArray &results)
{
    qInfo() << "onDataFetched is called";
    qInfo() << results;

    documentWidget->recursiveBuild(nullptr, results);
}

void MainWindow::onFetchError(const QString &error)
{
    QMessageBox::critical(this, "Error message...", error);
    exit(1);
}
