#include "widget.h"
#include "ui_widget.h"
#include "toast.h"
#include <QPixmap>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>
#include <QCoreApplication>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 连接登录按钮的点击信号和槽
    connect(ui->login, &QPushButton::clicked, this, &Widget::login);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::login()
{
    QString username = ui->account->text();
    QString password = ui->password->text();
    setUserName(username);

    QPixmap image("");

    if (username.isEmpty() && password.isEmpty()) {
        Toast::instance().show(Toast::INFO, "请输入账号和密码！");
        this->hide();
        emit showdashboard();
    }
    else if (username.isEmpty()) {
        Toast::instance().show(Toast::INFO, "请输入账号！");
    }
    else if (password.isEmpty()) {
        Toast::instance().show(Toast::INFO, "请输入密码！");
        this->hide();
        emit showdashboard();
    } else {
        // 连接数据库
        QString dbName = "database.db";
        QString dbPath = QCoreApplication::applicationDirPath() + "./" + dbName;  // Use a relative path
        QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName(dbPath);

        if (!database.open()) {
            QMessageBox::critical(nullptr, "错误", "无法打开数据库：" + database.lastError().text());
            return;
        }

        // 执行查询
        QSqlQuery query;
        query.prepare("SELECT * FROM user WHERE username = :username AND password = :password");
        query.bindValue(":username", username);
        query.bindValue(":password", password);
        if (!query.exec()) {
            QMessageBox::critical(nullptr, "错误", "查询执行失败：" + query.lastError().text());
            return;
        }
        if (query.next()) {
            // 找到匹配的数据记录
            QString cusNumberResult = query.value("cusNumber").toString();
            setCusNumber(cusNumberResult);
            Toast::instance().show(Toast::INFO, "登录成功！");
            this->hide();
            emit showdashboard();
        } else {
            // 没有找到匹配的数据记录
            Toast::instance().show(Toast::INFO, "用户名或密码错误！");
        }

        // 关闭数据库连接
        database.close();
    }

}

void Widget::setUserName(const QString& data) {
    globalUserName = data;
};

void Widget::setCusNumber(const QString& data) {
    globalCusNumber = data;
};

