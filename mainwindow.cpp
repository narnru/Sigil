#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    process = new Processing();
    thread = new QThread(this);

    connect(process, SIGNAL(responce(QString)), this, SLOT(updateResponce(QString)));
    connect(this, SIGNAL(openDataFile(QString)), process, SLOT(fileRead(QString)));
    connect(this, SIGNAL(openResultFile(QString)), process, SLOT(fileWrite(QString)));
    connect(process, SIGNAL(readEnded()), this, SLOT(onFileOpened()));
    connect(process, SIGNAL(progress(int)), this, SLOT(updateProgress(int)));

    process->moveToThread(thread);
    thread->start();

    ui->lineEditResponce->setDisabled(true);
    ui->progressBar->setValue(0);
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonDataPath_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "", QDir::currentPath());
    ui->lineEditDataPath->setText(path);
}

void MainWindow::updateResponce(QString responce)
{
    ui->lineEditResponce->setText(responce);
}

void MainWindow::onFileOpened()
{
    emit openResultFile(ui->lineEditResultPath->text());
    ui->pushButtonStart->setDisabled(false);
}


void MainWindow::on_pushButtonStart_clicked()
{
    emit openDataFile(ui->lineEditDataPath->text());
    ui->pushButtonStart->setDisabled(true);
}

void MainWindow::updateProgress(int value)
{
    ui->progressBar->setValue(value);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    thread->exit();
    QMainWindow::closeEvent(event);
}

