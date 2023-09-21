#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<QRegularExpression>

double calcval = 0.0;
double solution =0.0;
bool divTrigger=false;
bool mulTrigger=false;
bool subTrigger=false;
bool addTrigger=false;



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
     ui->stackedWidget->setCurrentIndex(0);
    ui->display->setText(QString::number(calcval));
    QPushButton *numButtons[10];
    for(int i=0;i<10;++i){
        QString butname = "button" + QString::number(i);
        numButtons[i] = MainWindow::findChild<QPushButton *>(butname);
        connect(numButtons[i],SIGNAL(released()),this,
                SLOT(Numpressed()));
    }

    connect(ui->add,SIGNAL(released()),this,
            SLOT(mathbuttonpressed()));
    connect(ui->subtract,SIGNAL(released()),this,
            SLOT(mathbuttonpressed()));
    connect(ui->multiply,SIGNAL(released()),this,
            SLOT(mathbuttonpressed()));
    connect(ui->divide,SIGNAL(released()),this,
            SLOT(mathbuttonpressed()));

    //connect(ui->result,SIGNAL(released()),this,
            //SLOT(resultbutton()));

    connect(ui->result,SIGNAL(released()),this,
            SLOT(resultbutton()));
    connect(ui->changesign,SIGNAL(released()),this,
            SLOT(changesign()));

    connect(ui->clear,SIGNAL(released()),this,
            SLOT(clearpressed()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::Numpressed(){
    QPushButton *button = (QPushButton *)sender();
    QString butval =button->text();
    QString displayval = ui->display->text();
    if(displayval.toDouble()==0 || displayval.toDouble()==0.0){
        ui->display->setText(butval);
    }
    else {
        QString newval =displayval+butval;
        double dblnew =newval.toDouble();
        ui->display->setText(QString::number(dblnew,'g',16));
    }
}

void MainWindow::mathbuttonpressed(){

    divTrigger=false;
    mulTrigger=false;
    subTrigger=false;
    addTrigger=false;
    QString displayval =ui->display->text();
    calcval=displayval.toDouble();
    QPushButton *button=(QPushButton *)sender();
    QString butval=button->text();
    if(QString::compare(butval,"/",Qt::CaseInsensitive)==0){
        divTrigger=true;
    }
    else if(QString::compare(butval,"*",Qt::CaseInsensitive)==0){
        mulTrigger=true;
    }
    else if(QString::compare(butval,"-",Qt::CaseInsensitive)==0){
        subTrigger=true;
    }
    else {
        addTrigger=true;
    }
    ui->display->setText("");
}

void MainWindow::on_result_clicked()
{


    QString displayval=ui->display->text();
    double dbldisplayval = displayval.toDouble();
    solution=0.0;
    if(addTrigger||subTrigger||mulTrigger||divTrigger){
        if(addTrigger){
            solution=calcval + dbldisplayval;
        }
        else if(subTrigger){
            solution=calcval - dbldisplayval;
        }
        else if(mulTrigger){
            solution=calcval * dbldisplayval;
        }
        else {
            solution=calcval / dbldisplayval;
        }
    }
    else {
        solution=dbldisplayval;
    }
    divTrigger=false;
    mulTrigger=false;
    subTrigger=false;
    addTrigger=false;
    ui->display->setText(QString::number(solution));
    ui->stackedWidget->setCurrentIndex(1);
    ui->resultdisplay->setText(QString::number(solution));

}

void MainWindow::changesign(){
    QString displayval=ui->display->text();
    QRegularExpression reg("[-]?[0-9.]*");
    QRegularExpressionMatch match =reg.match(displayval);
    bool has=match.hasMatch();
    if(has){
        double dbldisplayval = displayval.toDouble();
        double dbldisplaysign= -1 * dbldisplayval;
        ui->display->setText(QString::number(dbldisplaysign));
    }
}

void MainWindow::clearpressed(){
    ui->display->setText("0.0");
    ui->resultdisplay->setText("0.0");
    ui->eodisplay->setText("");
}

/*void MainWindow::on_result_clicked()
{

    solution = 0.0;
    QString displayval=ui->display->text();
    double dbldisplayval = displayval.toDouble();
    if(addTrigger||subTrigger||mulTrigger||divTrigger){
        if(addTrigger){
            solution=calcval + dbldisplayval;
        }
        else if(subTrigger){
            solution=calcval - dbldisplayval;
        }
        else if(mulTrigger){
            solution=calcval * dbldisplayval;
        }
        else {
            solution=calcval / dbldisplayval;
        }
    }
    else {
        solution=dbldisplayval;
    }
    ui->stackedWidget->setCurrentIndex(1);
    ui->resultdisplay->setText(QString::number(solution));

}*/

void MainWindow::on_backtocalc_clicked()
{
    //ui->resultdisplay->setText(QString::number(solution));
    ui->stackedWidget->setCurrentIndex(0);
    ui->display->setText(QString::number(solution));
}


void MainWindow::on_checkres_clicked()
{
    ui->resultdisplay->setText("0.0");
     ui->stackedWidget->setCurrentIndex(2);
    if(solution==int(solution) && int(solution)%2==1 ){
        ui->eodisplay->setText("ODD");
     }
    else if(solution==int(solution) && int(solution)%2==0){
        ui->eodisplay->setText("EVEN");
    }
     else{
        ui->eodisplay->setText("CAN'T BE DETERMINED");
     }
}

void MainWindow::on_bac2calc_clicked()
{
     ui->eodisplay->setText("");
     ui->stackedWidget->setCurrentIndex(0);
     ui->display->setText(QString::number(solution));
}

