#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //settings root's pathgit
    QString sPath="/";
    //filters for txt sources
    QStringList nameFilter;
    nameFilter<<"*.txt";

    //settings file System of directories
    dirModel=new QFileSystemModel(this);
    dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dirModel->setRootPath(sPath);

    //settings all files in the columns
    fileModel=new QFileSystemModel(this);
    fileModel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    fileModel->setRootPath(sPath);
    fileModel->setNameFilters(nameFilter);
    fileModel->setNameFilterDisables(false);

    //settings data files in system
    dataFileModel=new QFileSystemModel(this);
    dataFileModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files);
    dataFileModel->setRootPath(sPath);
    dataFileModel->setNameFilters(nameFilter);
    dataFileModel->setNameFilterDisables(false);

    ui->TV_dataFiles->setModel(dataFileModel);
    ui->TV_fileSystem->setModel(dirModel);
    ui->LV_showFiles->setModel(fileModel);

    MainWindow::makePlot();
    //MainWindow::drawGraph(QWidget * graph);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_TV_fileSystem_clicked(const QModelIndex &index)
{
   QString sPath=dirModel->fileInfo(index).absoluteFilePath();
   ui->LV_showFiles->setRootIndex(fileModel->setRootPath(sPath));
   ui->TV_dataFiles->setRootIndex(dataFileModel->setRootPath(sPath));
}

void MainWindow::on_LV_showFiles_clicked(const QModelIndex &index)
{
   QString sPath=dirModel->fileInfo(index).absoluteFilePath();
   QFile file(sPath);
   if(!file.open(QIODevice::ReadOnly))
        QMessageBox::information(0, "info", file.errorString());
   QTextStream in(&file);
   ui->TB_readAsText->setText(in.readAll());
}

void MainWindow::makePlot()
{
    // generate some data:
    QVector<double> x(1001), y(1001), z(1001); // initialize with entries 0..100
    for (int i=0; i<1000; ++i)
    {
      x[i] = i/50.0 - 1; // x goes from -1 to 1
      y[i] = x[i]*x[i]; // let's plot a quadratic function
      z[i]=sin(x[i]);
    }


    // create graph and assign data to it:
    ui->plotGraphOrigin->addGraph();
    ui->plotGraphOrigin->graph(0)->setData(x, y);
    // give the axes some labels:
    ui->plotGraphOrigin->xAxis->setLabel("x");
    ui->plotGraphOrigin->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->plotGraphOrigin->xAxis->setRange(-1, 1);
    ui->plotGraphOrigin->yAxis->setRange(0, 1);
    ui->plotGraphOrigin->replot();

    ui->plotGraphNew->addGraph();
    ui->plotGraphNew->graph(0)->setData(x, z);
    // give the axes some labels:
    ui->plotGraphNew->xAxis->setLabel("x");
    ui->plotGraphNew->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->plotGraphNew->xAxis->setRange(0, 10);
    ui->plotGraphNew->yAxis->setRange(-1, 1);
    ui->plotGraphNew->replot();
}
