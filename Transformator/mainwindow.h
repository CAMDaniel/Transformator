#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "transformator.h"
#include <QMainWindow>
#include <QtPrintSupport/QPrinter>
#include <QFileSystemModel>
#include <QtGui>
#include <QDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void makePlot();
    void on_TV_fileSystem_clicked(const QModelIndex &index);
    void on_LV_showFiles_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    QFileSystemModel *dirModel;
    QFileSystemModel *fileModel;
    QFileSystemModel *dataFileModel;
};

#endif // MAINWINDOW_H
