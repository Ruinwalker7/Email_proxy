#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "qtoolbar.h"
#include "send_email.h"
#include "qtoolbar.h"
#include "QToolButton"
#include "QMenu"
#include "QVBoxLayout"
#include "QGridLayout"
#include "controlfiles.h"
#include "QStringList"
#include "emailreceive.h"

mainWidget::mainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainWidget)
{
    ui->setupUi(this);
    ui->tabWidget->setTabsClosable(true);
    this->updateAccounts();

    //连接
    connect(ui->tabWidget, &QTabWidget::tabCloseRequested,this,&mainWidget::on_tabWidget_tabCloseRequested);
    connect(ui->add,&QPushButton::clicked,this,&mainWidget::add);
}


//tab的关闭按钮被点击的槽
void mainWidget::on_tabWidget_tabCloseRequested(int index)
{
    ui->tabWidget->removeTab(index);
}

void mainWidget::updateAccounts(){
    controlFiles ctr;
    QStringList list;
    ctr.updateAccount(&list);

    //添加用户
    for(int i=0;i<list.size();i++){
        QString user,password;
        user=list[i];
        i++;
        password=list[i];

        //map存储账户密码
        accounts.insert(user,password);

        send_email *send = new send_email();
        QToolButton *toolBub = new QToolButton();
        QMenu *menuSelection = new QMenu();

        QAction *write  = new QAction();
        write->setText("写邮件");
        QAction *receive = new QAction();
        receive->setText("收件箱");

        socket *sc = new socket(user.toUtf8(),password.toUtf8());
        send_email *email = new send_email();
        EmailReceive *receiver = new EmailReceive();

        receiver->setUserName(user);
        email->setUser(user,password);

        connect(write, &QAction::triggered,[=](bool check){
          ui->tabWidget->addTab(email, QString("写邮件"));
         });
        connect(receive, &QAction::triggered,[=](bool check){
            sc->Pop3_receiver(receiver);
         });

        menuSelection->addAction(write);
        menuSelection->addAction(receive);

        toolBub->setText(user);
        toolBub->setPopupMode(QToolButton::InstantPopup);
        toolBub->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
        toolBub->setMenu(menuSelection);
        ui->accountLayout->insertWidget(0,toolBub);
        this->update();
    }

}

void mainWidget::add()
{
    addAccount *adda = new addAccount();
    adda->setWindowModality(Qt::ApplicationModal);
    adda->show();
}

mainWidget::~mainWidget()
{
    delete ui;
}
