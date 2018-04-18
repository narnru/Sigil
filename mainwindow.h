#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "processing.h"
#include <QFileDialog>
#include <QString>
#include <QDir>
#include <QThread>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Processing *process;
    QThread* thread;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButtonDataPath_clicked();
    void updateResponce(QString responce);
    void onFileOpened();
    void on_pushButtonStart_clicked();
    void updateProgress(int value);
    void closeEvent(QCloseEvent *event);


signals:
    void openDataFile(QString path);
    void openResultFile(QString path);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
