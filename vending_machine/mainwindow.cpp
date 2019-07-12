#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
int MainWindow::getMoney(){
    return money;
}
void MainWindow::printMsg(){
    QMessageBox msg;
    msg.information(nullptr, "Error", "Not Enough Money");
}
bool MainWindow::checkMoney(){
    bool flag = true;
    if(money < 0){
        flag = false;
        money = 0;
    }else {
        flag = true;
    }
    return flag;
}
void MainWindow::disableBtn(){
    if(money < 200)
        ui->pbCoke->setEnabled(false);
    if(money < 150)
        ui->pbTea->setEnabled(false);
    if(money < 100)
        ui->pbCoffee->setEnabled(false);
}
void MainWindow::changeMoney(int n){
    money += n;
    ui->lcdNumber->display(money);
}

void MainWindow::on_pb10_clicked()
{
    changeMoney(10);
}


void MainWindow::on_pb50_clicked()
{
    changeMoney(50);
}

void MainWindow::on_pb100_clicked()
{
    changeMoney(100);
}

void MainWindow::on_pb500_clicked()
{
    changeMoney(500);
}

void MainWindow::on_pbCoffee_clicked()
{
    if(checkMoney() == false){
        printMsg();
        disableBtn();
        return;
    }else if(money >= 100){
        changeMoney(-100);
        QMessageBox msg;
        msg.information(nullptr, "Get Drink", "Get Coffee");
    }
}

void MainWindow::on_pbTea_clicked()
{
    if(checkMoney() == false){
        printMsg();
        disableBtn();
        return;
    }else if(money >= 150){
        changeMoney(-150);
        QMessageBox msg;
        msg.information(nullptr, "Get Drink", "Get Tea");
    }
}

void MainWindow::on_pbCoke_clicked()
{
    if(checkMoney() == false){
        printMsg();
        disableBtn();
        return;
    }else if(money >= 200){
        changeMoney(-200);
        QMessageBox msg;
        msg.information(nullptr, "Get Drink", "Get Coke");
    }
}

void MainWindow::on_pbReset_clicked()
{
    int fiveHun=0, hun=0, fifty=0, ten=0;
    QString refund;
    QMessageBox msg;
    while(money != 0){
        if((money/500) > 0){
            fiveHun += money/500;
            money -= 500*fiveHun;
            continue;
        }else if((money/100) > 0){
            hun += money/100;
            money -= 100*hun;
            continue;
        }else if((money/50) > 0){
            fifty += money/50;
            money -= 50*fifty;
            continue;
        }else{
            ten += money/10;
            money -= 10*ten;
            continue;
        }
    }
    refund = QString("500 = %1\n100 = %2\n50 = %3\n10 = %4\n")
                        .arg(fiveHun)
                        .arg(hun)
                        .arg(fifty)
                        .arg(ten);
    msg.information(nullptr, "Refund", refund);
    money = 0;
    ui->lcdNumber->display(money);
}
