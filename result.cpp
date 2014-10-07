#include "result.h"
#include "ui_result.h"
#include "graph.h"

QString school_name;

void Result::choose_school(){
           //QPushButton *button[10];
           QPushButton *button[100];
           //QGridLayout *controlsLayout = new QGridLayout;

           /*for(int i=0; i < 7; i++)
           {
               button[i] = new QCommandLinkButton;
               button[i]->setText("a");
               button[i]->setDescription("a");
               button[i]->resize(40,40);
               ui->scrollAreaWidgetContents->layout()->addWidget(button[i]);
               //ui->scrollAreaSlots->show();
               //button[i]->show();
           }*/

           QString path = QDir::currentPath();
                   path.append("/schools");
           QDirIterator dirIt(path,QDirIterator::Subdirectories);

           QVBoxLayout *flowLayout = new QVBoxLayout;

                          // Populate FlowLayout with QLabels
                       signalMapper = new QSignalMapper(this);

           int i = 0;
           while (dirIt.hasNext()) {
               dirIt.next();
               if (QFileInfo(dirIt.filePath()).isFile())
                   if (QFileInfo(dirIt.filePath()).suffix() == "txt"){
                       button[i] = new QPushButton();
                       button[i]->setText(dirIt.fileName().section(".",0,0));
                       //button[i]->setDescription("a");
                       button[i]->setMinimumWidth(150);
                       button[i]->setMinimumHeight(30);

                       button[i]->setMaximumWidth(150);
                       button[i]->setMaximumHeight(30);

                       connect(button[i], SIGNAL(clicked()), signalMapper, SLOT(map()));


                       signalMapper->setMapping(button[i], dirIt.fileName().section(".",0,0));


                       flowLayout->addWidget(button[i]);
                       i++;
                   }
           }


            /*QVBoxLayout *flowLayout = new QVBoxLayout;

               // Populate FlowLayout with QLabels
            signalMapper = new QSignalMapper(this);




               for (int i=0; i<20; i++) {
                   button[i] = new QPushButton();
                   button[i]->setText(QString(i));
                   //button[i]->setDescription("a");
                   button[i]->setMinimumWidth(150);
                   button[i]->setMinimumHeight(30);

                   button[i]->setMaximumWidth(150);
                   button[i]->setMaximumHeight(30);

                   connect(button[i], SIGNAL(clicked()), signalMapper, SLOT(map()));


                   signalMapper->setMapping(button[i], "aafafafaf");


                   flowLayout->addWidget(button[i]);
               }*/

               connect(signalMapper, SIGNAL(mapped(const QString &)),
                            SLOT(buttonPressed(const QString &)));

               /*connect(this, SIGNAL(clicked(const QString &)),
                                    this, SLOT(buttonPressed(const QString &)))*/



               // Create QScrollArea
               ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
               ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
               ui->scrollArea->widget()->setLayout(flowLayout);

               ui->scrollArea->setMinimumWidth(180);
               ui->scrollArea->setMaximumWidth(180);

               ui->scrollArea->setMinimumHeight(100);
               ui->scrollArea->setMaximumHeight(16777215);



           /*for(i=0;i<7;i++)
           {
               for(j=0;j<7;j++)
               {
                   if(count<=42)
                   {
                       button[i][j] = new QPushButton("p");
                       button[i][j]->resize(40,40);
                       button[i][j]->move(40*j, 40*i);
                       button[i][j]->show();
                       ui->verticalLayout->addWidget(button[i][j],0,0);

                       count++;
                   }
               }
           }*/
           //setLayout(controlsLayout);
           //setCentralWidget(ui->scrollAreaWidgetContents);
}

Result::Result(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Result)
{
    ui->setupUi(this);

    
    choose_school();
    setMinimumWidth(180);
    setMaximumWidth(180);
    setGeometry (50,100, 180, 600);

    this->adjustSize();
    
    show();
}

Result::~Result()
{
    delete ui;
}

//vector <graph> w3;


void Result::buttonPressed(const QString &school_name){
    qDebug() << school_name;

    graph *w3 = new graph(school_name);
    //w3.push_back(graph(school_name));
    w3->setWindowTitle(school_name);
    //w3->getChart(school_name);
    //w3->setModal(true);
    w3->show();
}
