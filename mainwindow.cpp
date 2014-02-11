#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "http.h"


const char DOMAIN[]={"www.erepublik.com"};

const std::string MAIN_PAGE="en";
const std::string LOGIN_PAGE="en/login";

const std::string FOOD_RAW_MARKET_PAGE="en/economy/market/41/7/1/citizen/0/price_asc/1";
const std::string WEAPON_RAW_MARKET_PAGE="en/economy/market/41/12/1/citizen/0/price_asc/1";
const std::string WEAPON_MARKET_PAGE="en/economy/market/41/2/$q$/citizen/0/price_asc/1";
const std::string FOOD_MARKET_PAGE="ssen/economy/market/41/1/$q$/citizen/0/price_asc/1";

std::string get="GET";
std::string post="POST";

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


    //ui->listWidget->addItem(QString::number(1));
    string s="\r\n"
                     "User-Agent: Mozilla/5.0\r\n"
                     "Accept: text/html\r\n"
                     "Accept-Language: ru-RU,ru;q=0.8,en-US;q=0.6,en;q=0.4\r\n"
                     "Accept-Charset: windows-1251,utf-8;q=0.7,*;q=0.3\r\n"
                     "Connection: keep-alive\r\n";
    http *parser = new http();

    //Get auth token
    string html = parser->get_page(get ,DOMAIN, MAIN_PAGE, s+"\r\n", 23, 25);
    if (html.length()==0)\
    {
        cout<<"Any http error, void answer for request given"<<std::endl;
        ui->lineEdit->setEnabled(true);
        ui->lineEdit_2->setEnabled(true);
        ui->pushButton->setEnabled(true);
        ui->progressBar->setEnabled(false);
        QMessageBox Msgbox;
        Msgbox.setText("Any http error, void answer for request given");
        Msgbox.exec();
        return;
    }

    cout<<html<<endl;
    string token = html.substr(html.find("name=\"_token\"")+21,32);
    cout<<"Site token: "<<token<<endl;
    ui->listWidget->addItem("Site token: "+QString::fromStdString(token));
    ui->progressBar->setValue(6);
    ui->listWidget->updateGeometry();

    //Login

    string login=ui->lineEdit->text().replace("@","%40").toUtf8().constData();
    string password=ui->lineEdit_2->text().toUtf8().constData();

    html=parser->get_page(post, DOMAIN, LOGIN_PAGE, s+"Content-Length:101\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\n_token="+token+"&citizen_email="+login+"&citizen_password="+password, 0, 1);
    string cookies="erpk_auth=1;"+html.substr(html.find("erpk_mid="), 42);
    cookies+=html.substr(html.find("erpk="), 33);
    cout<<endl<<"Auth cookie: "<<cookies<<endl;
    ui->listWidget->addItem("Auth cookie: "+QString::fromStdString(cookies));
    ui->progressBar->setValue(12);

    //Get markets pages
    html=parser->get_page(get, DOMAIN, FOOD_RAW_MARKET_PAGE, s+"Cookie: "+cookies+" \r\n\r\n", 158, 179);
    cout<<endl<<html<<endl;
    string count = html.substr(html.find_first_of("m_stock"), 30);
    for (int i=0; i<count.length(); i++)
        if (count[i]==)


}
