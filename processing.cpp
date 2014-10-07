#include "processing.h"
#include "ui_processing.h"
#include "result.h"
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
#include <QDesktopServices>
#include <QUrl>
using namespace std;

extern QString filename[3];

QString outPath;

template<typename T, typename M, template<typename> class C = std::less>
struct member_comparer : std::binary_function<T, T, bool>
{
    explicit member_comparer(M T::*p) : p_(p) { }

    bool operator ()(T const& lhs, T const& rhs) const
    {
        return C<M>()(lhs.*p_, rhs.*p_);
    }

private:
    M T::*p_;
};

template<typename T, typename M>
member_comparer<T, M> make_member_comparer(M T::*p)
{
    return member_comparer<T, M>(p);
}

template<template<typename> class C, typename T, typename M>
member_comparer<T, M, C> make_member_comparer2(M T::*p)
{
    return member_comparer<T, M, C>(p);
}

class student{
  public:
    int id_num;     // 10000
    string school_name;
    int ranking;
    string name;
    int score;
    QVector<int> submit;

    void get_score(QVector<int> &);
};

void student::get_score(QVector<int> &answers){
    qDebug() << answers.size();
    for (int i = 0; i < answers.size(); i++){
        if (submit[i] == answers[i]){
            score++;
        }
    }
}

class school{
    public:
    string name;
    double mean;
    int ranking;
    vector<int> pupil_ids;

    float get_mean(const QVector<student> &);
};

float school::get_mean(const QVector<student> &students){
    int total_score = 0;

    for (unsigned int i = 0; i < pupil_ids.size(); i++){
        total_score+= students[pupil_ids[i]-1].score;
    }

    int a = pupil_ids.size();

    mean = total_score/float(a);

    return mean;
}

void im_brief(string path, QVector <school> &schools){
    ifstream file(path.c_str());
    if (file.is_open()){
        school skl;
        string rubbish;
        getline(file, rubbish);
        //getline(file,rubbish);
        string school_name;

        if (rubbish == "school_names"){
            while (getline(file, skl.name)){
                    schools.push_back(skl);

            }
        }



    }else qDebug() << "Fail";
    file.close();
}

void im_answer(string path, QVector<int> &answers, int &no_answer){
    ifstream file;

    file.open(path.c_str());
    if (file.is_open()){
        int answer;
        //string rubbish;
        //getline(file, rubbish);
        while (file >> answer){
            answers.push_back(answer);
            no_answer++;
        }
    }
    file.close();
}

void im_answersheets(string path, QVector<student> &students, QVector<school> &schools, int no_answer){
  ifstream file;
  file.open(path.c_str());
  if (file.is_open()){
        string school_name;
        string check;
        string rubbish;
        //getline(file, rubbish);

        do{
            student Candidate;
            students.push_back(student());
            getline(file, students.back().name);
            qDebug()<< "name? " << QString::fromStdString(students.back().name);
            string intBuff;
            getline(file, intBuff);
            stringstream(intBuff) >> students.back().id_num;
            getline(file, students.back().school_name);

            int given_ans;


            for (int i = 0; i < no_answer; i++){

                getline(file, intBuff);
                stringstream(intBuff) >> given_ans;
                students.back().submit.push_back(given_ans);
            }

            for (int i = 0; i < schools.size(); i++){
                if (strcmp(students.back().school_name.c_str() ,schools[i].name.c_str())== 0){
                    schools[i].pupil_ids.push_back(students.back().id_num);
                }
            }

            getline(file, check);
            //qDebug() << QString::fromStdString(check);
        }while(check == "-----");
  }
  file.close();
}

void gen_score(QVector<int> &answers, QVector<student> &students){
    for (int i = 0; i < students.size()-1; i++){
        students[i].get_score(answers);
    }
}

void gen_rank(QVector<student> &students){
    int ranks[students.size()];
    for(int i=0;i<students.size();i++){
        int rnk=0;
        for(int z=0;z<students.size();z++){
            if(students[z].score < students[i].score)
                rnk++;
        }
    ranks[i]=rnk;
    }
    for(int i=0;i<students.size();i++){
        students[i].ranking =ranks[i];
    }
}

void gen_skl_mean(const QVector<student> &students, QVector<school> &schools){
    for(int i = 0; i < schools.size(); i++){
        schools[i].get_mean(students);
    }
}

void gen_skl_rank(QVector<school> &schools){
    sort(schools.begin(), schools.end(), make_member_comparer2<greater>(&school::mean));

     for (int i = 0; i < schools.size(); i++){
        schools[i].ranking = i+1;
     }
}

void ex_analysis(const QVector<student> &students, const QVector<school> &schools){



    //QDir().mkdir(QDir::currentPath()+"schools");
    QString path = QDir::currentPath();
            path.append("/schools");
    outPath = path;
    QDir().mkdir(path);



    ofstream file;

    for (int i = 0; i < schools.size();i++){
        string Spath = path.toStdString() + "/" + schools[i].name + ".txt";
        file.open(Spath.c_str());

        // the analysis of schools
        file << "School analysis" << endl << "=================" << endl;
        file << "school name: " << schools[i].name << '\n';
        file << "school mean: " << setprecision(2) << schools[i].mean << '\n';
        file << "school rank: " << schools[i].ranking << '\n';
        file << '\n';
        // the analysis of students
        file << "Individual analysis" << endl << "=================" << endl;
        for (unsigned int j = 0; j < schools[i].pupil_ids.size(); j++){
            file << "student id: " << setfill('0') << setw(4)<< students[schools[i].pupil_ids[j]-1].id_num << '\n';
            file<< "student name: " << students[schools[i].pupil_ids[j]-1].name << '\n';
            file << "student rank: " << students[schools[i].pupil_ids[j]-1].ranking << '\n';
            file << "student score: " << students[schools[i].pupil_ids[j]-1].score << '\n';
            file << '\n';
        }

        file.close();
    }
}

void process_data(Ui::Processing *);


Processing::Processing(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Processing)
{
    //this->setWindowFlags(Qt::FramelessWindowHint); //Set a frameless window

    ui->setupUi(this);
    //setGeometry(400, 250, 542, 390);
    ui->progressBar->setValue(0);
    QApplication::setOverrideCursor( Qt::BusyCursor );
    show();

    //QThread::sleep(3);

    qApp->processEvents();
    update();

    process_data();

}

void Processing::process_data(){
    QVector<student> students;
    students.reserve(1000);
    QVector<school> schools;
    schools.reserve(100);

    QVector<int> answers;
    answers.reserve(20);

    int no_answer = 0;

    ui->progress->append("Importing files....");
    for(int i = 0; i <= 30; i++){
        QThread::msleep(35);
        ui->progressBar->setValue(i);
    }
    im_brief(filename[0].toStdString(), schools);
    im_answer(filename[1].toStdString(), answers, no_answer);
    im_answersheets(filename[2].toStdString(), students, schools, no_answer);
    //QThread::sleep(2);


    ui->progress->append("Generating results....");
    for(int i = 30; i <= 60; i++){
        QThread::msleep(40);
        ui->progressBar->setValue(i);
    }
    gen_score(answers, students);
    gen_rank(students);
    gen_skl_mean(students, schools);
    gen_skl_rank(schools);
    //QThread::sleep(1);

    ui->progress->append("Exporting results....");
    for(int i = 60; i <= 90; i++){
        QThread::msleep(30);
        ui->progressBar->setValue(i);
    }

    ex_analysis(students, schools);
    //QThread::sleep(1);

    for(int i = 90; i <= 100; i++){
        QThread::msleep(30);
        ui->progressBar->setValue(i);
    }
    ui->progress->append("Done!");

    ui->next->setEnabled(true);
    QApplication::restoreOverrideCursor();

    QMessageBox::information(this, tr("Finished"), "Analysis path: /n /'"+ QDir::currentPath() + "/schools/'" );
    QString path = "file:///"+QDir::currentPath() + "/schools";
     //QDesktopServices::openUrl(QUrl("file:///C:/Documents and Settings/All Users/Desktop", QUrl::TolerantMode));
    //QDesktopServices::openUrl(QUrl("file:///C:/Documents and Settings/All Users/Desktop", QUrl::TolerantMode));
    QDesktopServices::openUrl(QUrl(path, QUrl::TolerantMode));
}

Processing::~Processing()
{
    delete ui;
}

void Processing::on_next_clicked()
{
    this->hide();
    Result *w2 = new Result;
    w2->setModal(true);
    w2->exec();
    close();
}
