#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFont>
#include <QLabel>
#include <QMessageBox>
#include <QPlainTextEdit>

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
}

void MainWindow::initialSetup()
{
    qInfo() << "Initiating initial setup";
    qInfo() << "I am starting document setup";

    documentSetup();
    commandSetup();
}

void MainWindow::documentSetup()
{
    // Create necessary objects and threads

    documentWidget = new DocumentWidget();

    documentWidget->setColumnCount(3);
    documentWidget->setHeaderLabels(QList<QString>{"Structure", "Path", "Type"});

    ui->hbox->addWidget(documentWidget, 1);

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

    // Delete the objects conveniently
    QObject::connect(workerThread,
                     &QThread::finished, documentReader,
                     &QObject::deleteLater);

    QObject::connect(workerThread,
                     &QThread::finished, workerThread,
                     &QObject::deleteLater);

    workerThread->start();
}

void MainWindow::commandSetup()
{
    userCmdBox = new QVBoxLayout();

    QPlainTextEdit* responseArea = new QPlainTextEdit();
    QPlainTextEdit* messageArea = new QPlainTextEdit();

    responseArea->setPlaceholderText("Submit a request and you will receive your response here...");
    responseArea->setReadOnly(true);

    messageArea->setPlaceholderText("Ask your questions here...");

    QLabel* lblResponse{new QLabel()};
    QLabel* lblSubmit{new QLabel()};

    lblResponse->setText("Language model Response:");
    lblSubmit->setText("Your query:");

    userCmdBox->addWidget(lblResponse);
    userCmdBox->addWidget(responseArea, 4);

    userCmdBox->addWidget(lblSubmit);
    userCmdBox->addWidget(messageArea, 1);

    userCmdBox->setSpacing(7);

    ui->hbox->addLayout(userCmdBox, 1);
}

void MainWindow::onDataFetched(const QJsonArray &results)
{

    documentWidget->recursiveBuild(nullptr, results);
    documentWidget->expandAll();
}

void MainWindow::onFetchError(const QString &error)
{
    QMessageBox::critical(this, "Error message...", error);
    exit(1);
}
