#ifndef STUDENT_H
#define STUDENT_H

#include <QObject>

class Student : public QObject
{
    Q_OBJECT
public:
    explicit Student(QObject *parent = 0);

signals:

public slots:
    //早期qt版本,必须要写到public slots,高级版本可以下到public或者全局下.
    //返回值是 void, 需要声明,也需要实现
    //可以有参数,可以重载
    void treat();
    void treat(QString foodName);
};

#endif // STUDENT_H
