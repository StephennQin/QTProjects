#include "widget.h"
#include <QPushButton>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->te = new Teacher(this);
    this->st = new Student(this);

    //connect参数的含义: 发送对象, fun1的地址, 接收方, fun2的地址.

    ///无参信号和槽
    //当不存在函数重载时,可以直接使用&Teacher::hungry的方式
    //connect(te, &Teacher::hungry, st, &Student::treat);
    //classIsOverNoFoodName(); //也可以如此触发:te->hungry();

    //当存在函数重载时,需要使用函数指针.
    void(Teacher:: * teacherSignalVoid)(void) = &Teacher::hungry;
    void(Student:: * studentSlotVoid)(void) = &Student::treat;
    connect(te, teacherSignalVoid, st, studentSlotVoid);
    classIsOverNoFoodName(); //也可以如此触发:te->hungry();


    ///带参数的信号和槽
    //函数指针 -> 函数地址
    void(Teacher:: * teacherSignal)(QString) = &Teacher::hungry;    //这里的函数指针要指明它是作用域,它是Teacher类下的,不是别的下面的.
    void(Student:: * studentSlot)(QString) = &Student::treat;
    connect(te, teacherSignal, st, studentSlot);
//    classIsOver();

    ///点击按钮来触发下课
    QPushButton * btn = new QPushButton("classIsOver", this);
    btn->move(100,100);
    this->setFixedSize(600, 300);
    this->setWindowTitle("signalAndSlotDemo");
    //这里把一般的函数也可以作为槽函数来使用.
    //connect(btn, &QPushButton::clicked, this, &Widget::classIsOver);


    ///信号连接信号
    //!注意,这里的clicked原型是clicked(bool checked = false),它有一个bool参数,作为它的槽函数要么是一个bool参数,要么是没有参数(即为void);
    connect(btn, &QPushButton::clicked, te, teacherSignalVoid); //此处因为hungry有重载的问题,所以不能够直接使用Teacher::hungry.

    ///断开信号
    //disconnect(te, teacherSignalVoid, st, studentSlotVoid);
    //disconnect(btn, &QPushButton::clicked, te, teacherSignalVoid);

    //!!!!!!拓展!!!!!!!!!!
    //1.信号是可以连接信号
    //2.一个信号可以连接多个槽函数
    //3.多个信号 可以连接 同一个槽函数.
    //!4.信号和槽函数的参数 必须类型一一对应,就像信号里传递的是QString类型的"宫保鸡丁",那么槽函数里也要用QString类型的foodName来接收.
    //!5.信号的参数个数可以多于槽函数参数个数.比如上面的clicked原型是clicked(bool checked = false),它有一个bool参数,作为它的槽函数要么是一个bool参数,要么是没有参数(即为void);


    //!!Qt4版本以前连接方式:
    //无参版本:
    //connect(te, SIGNAL(hungry(), st, SLOT(treat());
    //优点:参数直观.  缺点:类型不做检测.

    ///Lambda表达式:匿名函数,简便书写.
    [=](){                      //=:值传递
        btn->setText("lambda");
    }();                        //加上后面的()才能算是执行函数

    ///利用Lambda表达式实现点击按钮关闭窗口
    connect(btn, &QPushButton::clicked, this, [=](){
        this->close();
    });
}

Widget::~Widget()
{

}

void Widget::classIsOver()
{
    emit te->hungry("kongpochicken");
}

void Widget::classIsOverNoFoodName()
{
    emit te->hungry();
}
