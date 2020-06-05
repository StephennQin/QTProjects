#include "student.h"
#include<QDebug>

Student::Student(QObject *parent) : QObject(parent)
{

}

void Student::treat()
{
    qDebug() << "treat teacher!";
}

void Student::treat(QString foodName)
{
    //QString转为char *: 先转成QByteArray,再转成char *.
    qDebug() << "treat teacher" << foodName.toUtf8().data();
}

