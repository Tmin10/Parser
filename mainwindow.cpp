#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "http.h"
#include "parser.h"
#include <stdexcept>

using namespace std;

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

void MainWindow::on_pushButton_clicked()
{
    ui->lineEdit->setEnabled(false);
    ui->lineEdit_2->setEnabled(false);
    ui->pushButton->setEnabled(false);
    ui->progressBar->setEnabled(true);

    string login=ui->lineEdit->text().replace("@","%40").toUtf8().constData();
    string password=ui->lineEdit_2->text().toUtf8().constData();

    try {
        parser *pars = new parser (login, password);
        if (!pars->auth())
        {
            ui->lineEdit->setEnabled(true);
            ui->lineEdit_2->setEnabled(true);
            ui->pushButton->setEnabled(true);
            ui->progressBar->setEnabled(false);
            QMessageBox Msgbox;
            Msgbox.setText("Any http error, void answer for request given");
            Msgbox.exec();
        }
        else
        {
            ui->listWidget->addItem("Site token: "+QString::fromStdString(pars->get_token()));
            ui->listWidget->addItem("Cookies: "+QString::fromStdString(pars->get_cookies()));

            ui->progressBar->setValue(28);

            raw food_raw = pars->get_food_raw();
            ui->listWidget->addItem(QString::fromStdString(food_raw.print()));
            ui->progressBar->setValue(42);

            raw weapon_raw = pars->get_weapon_raw();
            ui->listWidget->addItem(QString::fromStdString(weapon_raw.print()));
            ui->progressBar->setValue(56);

            production food = pars->get_food();
            ui->listWidget->addItem(QString::fromStdString(food.print()));
            ui->progressBar->setValue(70);

            production weapon = pars->get_weapon();
            ui->listWidget->addItem(QString::fromStdString(weapon.print()));
            ui->progressBar->setValue(84);

            if (pars->send_data(food_raw, weapon_raw, food, weapon))
                ui->listWidget->addItem("Data loaded to remote server");
            else
                ui->listWidget->addItem("Sending data error");
            ui->progressBar->setValue(100);
        }

    }
    catch  (out_of_range& e)
    {
        ui->lineEdit->setEnabled(true);
        ui->lineEdit_2->setEnabled(true);
        ui->pushButton->setEnabled(true);
        ui->progressBar->setEnabled(false);
        QMessageBox Msgbox;
        Msgbox.setText("Wrong login or password, try again.");
        Msgbox.exec();
    }

    ui->lineEdit->setEnabled(true);
    ui->lineEdit_2->setEnabled(true);
    ui->pushButton->setEnabled(true);
    ui->progressBar->setEnabled(false);

}

