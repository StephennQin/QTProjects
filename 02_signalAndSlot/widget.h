#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include"teacher.h"
#include"student.h"


//需求:老师   下课后饿了 ->  学生   请老师吃饭
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
    void classIsOver();
    void classIsOverNoFoodName();

private:
    Teacher *te;
    Student *st;
};

#endif // WIDGET_H
