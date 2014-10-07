#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "processing.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <QDebug>

QString filename[3];
QString foldername;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setAcceptDrops(true);

    setWindowTitle ("ORL system");

    setWindowFlags(windowFlags() ^ Qt::WindowMaximizeButtonHint);
    ui->setupUi(this);

    //ui->path_1->setText("C:/Users/Mann/Documents/GitHub/ORL/real_data/brief_info.txt");
    //ui->path_2->setText("C:/Users/Mann/Documents/GitHub/ORL/real_data/answer.txt");
    //ui->path_3->setText("C:/Users/Mann/Documents/GitHub/ORL/real_data/answer_sheets.txt");

    //filename[0]="C:/Users/Mann/Documents/GitHub/ORL/real_data/brief_info.txt";
    //filename[1]="C:/Users/Mann/Documents/GitHub/ORL/real_data/answer.txt";
    //filename[2]="C:/Users/Mann/Documents/GitHub/ORL/real_data/answer_sheets.txt";

    //foldername = "C:/Users/Mann/Documents/GitHub/ORL/schools";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked() // get brief info
{
    filename[0] = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C://",
                "Text file (*.txt);;Data file(*.dat);;All files (*.*)"
                );
    if (filename[0] != QString("")){
        ui->path_1->setText(filename[0]);
    }
}

void MainWindow::on_pushButton_3_clicked() // get real answer
{
    filename[1] = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C://",
                "Text file (*.txt);;Data file(*.dat);;All files (*.*)"
                );
    if (filename[1] != QString("")){
        ui->path_2->setText(filename[1]);
    }
}

void MainWindow::on_pushButton_4_clicked() // get answer sheets
{
    filename[2] = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C://",
                "Text file (*.txt);;Data file(*.dat);;All files (*.*)"
                );
    if (filename[2] != QString("")){
        ui->path_3->setText(filename[2]);
    }
}

void MainWindow::on_pushButton_clicked() // start button pressed
{
    if((filename[0] != "")&&(filename[1] != "")&&(filename[2] != "")){
        this->hide();
        Processing *w1 = new Processing;

        w1->setModal(true);
        //close();
    }else {
        QMessageBox::information(this, tr("Not enough information"), "Please import all three files!");
    }
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(this, tr("About"), "An ORL system using QT GUI and C++ instead of stupid Pascal");
}

void MainWindow::on_path_1_textChanged()
{

    QString path = ui->path_1->toPlainText();
    path.replace(0, 8, "");
    QFile file(path);
    if (file.exists()){
        filename[0] = path;
    }
    file.close();
}

void MainWindow::on_path_2_textChanged()
{
    QString path = ui->path_2->toPlainText();
    path.replace(0, 8, "");

    QFile file(path);
    if (file.exists()){
        filename[1] = path;
    }
    file.close();
}

void MainWindow::on_path_3_textChanged()
{
    QString path = ui->path_3->toPlainText();
    path.replace(0, 8, "");
    QFile file(path);
    if (file.exists()){
        filename[2] = path;
    }
    file.close();
}
