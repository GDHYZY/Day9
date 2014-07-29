#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QAction>
#include"painter.h"
#include"newdialog.h"
#include<QCloseEvent>
#include<QList>
#include<QSlider>
#include<QSize>
#include<QLabel>
#include<QScrollArea>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void newmenu();         //新建界面菜单
    void openimage();       //打开
    void saveimage();       //保存
    void saveasimage();     //另存为
    bool maybesave();       //用于退出时判断是否有修改，是否需要保存
    void newimage();        //新建图像

    void setpen();          //设置画笔大小
    void seteraser();       //设置橡皮擦大小

    void turnright();       //顺时针旋转90度
    void turnleft();        //逆时针旋转90度
    void mlr();             //左右翻转
    void mud();             //上线翻转

    void usePolygon();      //画多边形模式
    void useLine();         //画直线模式
    void useCircle();       //画圆形模式
    void useRectangle();    //画矩形模式
    void useEllipse();      //画椭圆模式
    void useArc();          //画圆弧模式
    void useText();         //画文字模式
    void usePath();         //画路径

    void usepen();          //使用画笔
    void usebrush();        //使用笔刷
    void useeraser();       //使用橡皮擦
    void setcolor();        //设置颜色
    void allcolor();      //填充颜色

    void tobig();           //放大
    void tosmall();         //缩小


protected:
    void closeEvent(QCloseEvent *event);  //关闭事件
    void dragEnterEvent(QDragEnterEvent *event);    //重写鼠标起拖事件
    void dropEvent(QDropEvent *event);              //重写鼠标放下事件
    void mouseMoveEvent(QMouseEvent *event);   //跟踪鼠标
private slots:

private:
    Ui::MainWindow *ui;
    QScrollArea *scrollarea;
    QLabel *label;
    Newdialog *Nd;
//文件菜单下的动作
    myPainter *mypainter;
    QAction *openimageact;
    QAction *saveimageact;
    QAction *saveasimageact;
    QAction *exitact;
    QAction *newimageact;
//编辑菜单下的动作
    QAction *undoAction;
    QAction *redoAction;
    QAction *clearimageact;
//工具栏下的动作
    QAction *usepenact;
    QAction *useeraseract;
    QAction *usebrushact;
    QAction *eraseract;
    QAction *coloract;
    QAction *big;
    QAction *small;
    QAction *gray;
    QAction *select;
//工具菜单下的动作
    QAction *penact;
    //设置画笔类型动作
    QAction *penSolidLine;
    QAction *penDashLine;
    QAction *penDotLine;
    QAction *penDashDotLine;
    QAction *penDashDotDotLine;
    //设置笔刷类型动作
    QAction *brushsp;
    QAction *brushdcp;
    QAction *brushcp;
    QAction *brushd7p;
    QAction *brushhp;
    QAction *brushbdp;
    //图形动作
    QAction *wordact;
    QAction *Lineact;
    QAction *Ellipseact;
    QAction *Arcact;
    QAction *Circleact;
    QAction *Rectangleact;
    QAction *Polygonact;
    QAction *Textact;
    QAction *Pathact;

    QAction *right;
    QAction *left;
    QAction *lr;
    QAction *ud;
};

#endif // MAINWINDOW_H
