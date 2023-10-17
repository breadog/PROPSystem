#ifndef WIDGET_H
#define WIDGET_H

#include "globalData.h"

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;

private slots:
    void login(); // 槽函数，用于登录

signals:
    void showdashboard();//显示想要显示的页面

public:
    void setUserName(const QString& data);
    void setCusNumber(const QString& data);
};
#endif // WIDGET_H
