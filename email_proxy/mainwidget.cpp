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


mainWidget::mainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainWidget)
{
    ui->setupUi(this);
    ui->tabWidget->setTabsClosable(true);
    this->updateAccounts();
    connect(ui->tabWidget, &QTabWidget::tabCloseRequested,this,&on_tabWidget_tabCloseRequested);
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
    for(int i=0;i<list.size();i++){
        QString user,password;
        user=list[i];
        i++;
        password=list[i];
        accounts.insert(user,password);

        send_email *send = new send_email();
        QToolButton *toolB = new QToolButton();
        QMenu *menuSelection = new QMenu();

        QAction *write  = new QAction();
        write->setText("写邮件");
        send_email *email = new send_email();
        connect(write, &QAction::triggered,[=](bool check){
          ui->tabWidget->addTab(email, QString("发送邮件"));
         });
        menuSelection->addAction(write);
        menuSelection->addAction("收件箱");
        toolB->setText(user);
        toolB->setPopupMode(QToolButton::InstantPopup);
        toolB->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
        toolB->setMenu(menuSelection);
        ui->accountLayout->insertWidget(0,toolB);
        this->update();
    }

}


void mainWidget::add()
{
    addAccount *adda = new addAccount();
    adda->show();
}

mainWidget::~mainWidget()
{
    delete ui;
}
