#ifndef RESULT_H
#define RESULT_H

#include "graph.h"
#include <QDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QCommandLinkButton>
#include <QDebug>
#include <QSignalMapper>


namespace Ui {
class Result;
}

class Result : public QDialog
{
    Q_OBJECT

public:
    explicit Result(QWidget *parent = 0);
    ~Result();

    void choose_school();

    public slots:
    void buttonPressed(const QString &);

signals:
     void clicked(const QString &);

private:
    Ui::Result *ui;

    QSignalMapper *signalMapper;


};

#endif // RESULT_H
