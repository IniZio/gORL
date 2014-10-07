#ifndef GRAPH_H
#define GRAPH_H

//#include <QChartView>
#include <QDialog>
#include "qcustomplot.h"
#include <iostream>
#include <fstream>

using namespace std;

namespace Ui {
class graph;
}

class graph : public QDialog
{
    Q_OBJECT

public:
    explicit graph(const QString &, QWidget *parent = 0);
    ~graph();

    void getChart(const QString &);

private:
    Ui::graph *ui;

    void setupBarChart(QCustomPlot *,QString,QString);

    void getSchoolData(const QString &);

    QVector<double> schoolData;
};

#endif // GRAPH_H
