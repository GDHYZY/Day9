#ifndef TEST_H
#define TEST_H
#include<QWidget>
class test
{
public:
    test();
    Qt::PenStyle penstyLe;       //画笔类型，用于接受画笔类型的更改
    Qt::BrushStyle brushstyLe;   //笔刷类型，用于接受笔刷类型的更改
    QColor backgroundcolor;      //设置背景色
    QColor color;                //颜色，用于颜色
    int pensize;                 //画笔大小
    int erasersize;              //橡皮大小
    QPoint lastpoint;            //
    QPoint endpoint;             //
    QPoint *start;               //移动初始位置
    QImage *rem;                 //记录选区
    QString drawtype;            //图形绘制状态
    QString nowfile;             //记录当前图片名称
    bool drawing;                //绘画状态
    bool changeing;              //图像改变状态
    bool brushmode;              //笔刷模式
    bool clearmode;              //清空模式
    bool sl;                     //记录选框模式是否打开
    bool dg;                     //记录是否可以拖动
    bool mark;                   //权
};

#endif // TEST_H
