#include "calculator.h"
#include "./ui_calculator.h"
#include <QRegularExpression>

double calc_val = 0.0;
double mem_val = 0.0;
bool divTrigger = false;
bool mulTrigger = false;
bool subTrigger = false;
bool addTrigger = false;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);
    ui->Display->setText(QString::number(calc_val));
    QPushButton* numButtons[10];
    for(int i = 0; i<10; i++){
        QString butName = "Button"+QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *>(butName);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }
    connect(ui->Add, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Subtract, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Multiply, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Divide, SIGNAL(released()), this, SLOT(MathButtonPressed()));

    connect(ui->Equals, SIGNAL(released()), this, SLOT(EqualButton()));
    connect(ui->ChangeSign, SIGNAL(released()), this, SLOT(ChangeNumberSign()));

    connect(ui->MemAdd, SIGNAL(released()), this, SLOT(SetMemory()));
    connect(ui->MemGet, SIGNAL(released()), this, SLOT(GetMemory()));
    connect(ui->MemClear, SIGNAL(released()), this, SLOT(ClearMemory()));

    connect(ui->Clear, SIGNAL(released()), this, SLOT(ClearAll()));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumPressed(){
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    QString displayVal = ui->Display->text();
    if(displayVal.toDouble() == 0 || displayVal.toDouble()==0.0){
        ui->Display->setText(butVal);
    } else {
        QString newVal = displayVal+butVal;
        double dblNewVal = newVal.toDouble();
        ui->Display->setText(QString::number(dblNewVal, 'g', 16));
    }
}

void Calculator::MathButtonPressed(){
    if((addTrigger||mulTrigger||divTrigger||subTrigger) && CheckIfNumber(ui->Display->text())){
        double solution = 0.0;
        double dblDisplayVal = ui->Display->text().toDouble();
        if(addTrigger){
            solution = calc_val+dblDisplayVal;
        } else if(subTrigger){
            solution = calc_val-dblDisplayVal;
        } else if(mulTrigger){
            solution = calc_val*dblDisplayVal;
        } else {
            solution = calc_val/dblDisplayVal;
        }

        ui->Display->setText(QString::number(solution));
    }

    divTrigger=false;
    mulTrigger=false;
    subTrigger=false;
    addTrigger=false;
    QString displayVal = ui->Display->text();
    calc_val = displayVal.toDouble();

    QPushButton* button = (QPushButton*) sender();
    QString butVal = button->text();
    if(QString::compare(butVal, "/", Qt::CaseInsensitive)==0){
        divTrigger=true;
    } else if(QString::compare(butVal, "*", Qt::CaseInsensitive)==0){
        mulTrigger=true;
    } else if(QString::compare(butVal, "+", Qt::CaseInsensitive)==0){
        addTrigger=true;
    } else {
        subTrigger=true;
    }

    ui->Display->setText(butVal);
}

void Calculator::EqualButton(){
    QString displayVal = ui->Display->text();
    double doubleDisplayVal = displayVal.toDouble();
    double solution = doubleDisplayVal;
    if(addTrigger || subTrigger || divTrigger || mulTrigger){
        if(addTrigger){
            solution = calc_val+doubleDisplayVal;
        } else if(subTrigger){
            solution = calc_val-doubleDisplayVal;
        } else if(mulTrigger){
            solution = calc_val*doubleDisplayVal;
        } else {
            solution = calc_val/doubleDisplayVal;
        }
        addTrigger=subTrigger=divTrigger=mulTrigger=false;
    }

    ui->Display->setText(QString::number(solution));
}

bool Calculator::CheckIfNumber(QString val){
    static QRegularExpression reg("[-]?[0-9.]*");
    QRegularExpressionMatch match = reg.match(val);
    return match.hasMatch();
}

void Calculator::ChangeNumberSign(){
    QString displayVal = ui->Display->text();
    if(CheckIfNumber(displayVal)){
        double dblDisplayVal = displayVal.toDouble();
        dblDisplayVal *= -1;
        ui->Display->setText(QString::number(dblDisplayVal));
    }
}

void Calculator::SetMemory(){
    QString displayVal = ui->Display->text();
    if(CheckIfNumber(displayVal)){
        double dblDisplayVal = displayVal.toDouble();
        mem_val = dblDisplayVal;
    }
}

void Calculator::GetMemory(){
    ui->Display->setText(QString::number(mem_val));
}

void Calculator::ClearMemory(){
    mem_val=0.0;
}

void Calculator::ClearAll(){
    addTrigger=subTrigger=mulTrigger=divTrigger=0.0;
    mem_val=0.0;
    calc_val=0.0;
    ui->Display->setText(QString::number(calc_val));
}
