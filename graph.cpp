#include "graph.h"
#include "ui_graph.h"
#include "qcustomplot.h"
#include <QApplication>
#include <QMainWindow>
#include <qthread.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <sstream>

#include <algorithm>
#include <functional>

#include<string.h>
#include <iomanip>
#include <QVector>

#include<QDebug>
#include<QDir>
//#include <boost/algorithm/string.hpp>

using namespace std;

graph::graph(const QString &school_name, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::graph)
{
    ui->setupUi(this);

    setGeometry(250, 100, 542, 390);

    QString path = QDir::currentPath();
            path.append("/schools/" + school_name + ".txt");

    setupBarChart(ui->customPlot,path, school_name);
}

graph::~graph()
{
    delete ui;
}

void graph::getSchoolData(const QString & path){
    ifstream file(path.toStdString().c_str());
    if (file.is_open()){
        string rubbish;
        for (int i = 0; i < 11;i++)
            getline(file, rubbish);
        string Sscore;
        while(getline(file,Sscore)){
            string Subscore;
            //Sscore.copy (Subscore.c_str(), 14, Sscore.size()-1);
            Subscore = Subscore.append(Sscore, 14, Sscore.size()-1);
            int score = atoi(Subscore.c_str());
            //string score = strtok (Sscore.c_str(),':');
            //split(Sscore, Sscore, ':');
            qDebug() << "score: " << score;
            schoolData << score;
            for (int i = 0; i < 4;i++)
                getline(file, rubbish);
            /*if ((score >= 0) && (score <= 20)){
                schoolData[score-1]++;
            }*/
        }
    }
}

void graph::setupBarChart(QCustomPlot *customPlot,QString path,QString school_name)
{
  // create empty bar chart objects:
  QCPBars *score = new QCPBars(customPlot->xAxis, customPlot->yAxis);
  customPlot->addPlottable(score);
  // set names and colors:
  QPen pen;
  pen.setWidthF(1.2);
  score->setName("Students");
  pen.setColor(QColor(255, 131, 0));
  score->setPen(pen);
  score->setBrush(QColor(255, 131, 0, 50));

  // prepare x axis with country labels:
  QVector<double> ticks;
  QVector<QString> labels;
  for (int i = 1; i <= 20; i++) ticks << i;
  for (int i = 1; i <= 20; i++) labels << QString::number(i);
  customPlot->yAxis->setLabel("Score");
  customPlot->xAxis->setAutoTicks(false);
  customPlot->xAxis->setAutoTickLabels(false);
  customPlot->xAxis->setTickVector(ticks);
  customPlot->xAxis->setTickVectorLabels(labels);
  customPlot->xAxis->setTickLabelRotation(60);
  customPlot->xAxis->setSubTickCount(0);
  customPlot->xAxis->setTickLength(0, 4);
  customPlot->xAxis->grid()->setVisible(true);
  customPlot->xAxis->setRange(0, 21);

  // prepare y axis:
  customPlot->yAxis->setRange(0, 21);
  customPlot->yAxis->setPadding(5); // a bit more space to the left border
  customPlot->yAxis->setLabel("Number of student");
  customPlot->yAxis->grid()->setSubGridVisible(true);
  QPen gridPen;
  gridPen.setStyle(Qt::SolidLine);
  gridPen.setColor(QColor(0, 0, 0, 25));
  customPlot->yAxis->grid()->setPen(gridPen);
  gridPen.setStyle(Qt::DotLine);
  customPlot->yAxis->grid()->setSubGridPen(gridPen);

  // Add data:
  getSchoolData(path);

  score->setData(ticks, schoolData);
  // setup legend:
  customPlot->legend->setVisible(true);
  customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
  customPlot->legend->setBrush(QColor(255, 255, 255, 200));
  QPen legendPen;
  legendPen.setColor(QColor(130, 130, 130, 200));
  customPlot->legend->setBorderPen(legendPen);
  QFont legendFont = font();
  legendFont.setPointSize(10);
  customPlot->legend->setFont(legendFont);
  customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}
