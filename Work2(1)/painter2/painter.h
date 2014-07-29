#ifndef PAINTER_H
#define PAINTER_H
#include"test.h"
#include<QLabel>
#include <QWidget>
#include<QPoint>
#include<QImage>
#include<QMouseEvent>
#include<QSize>
#include<QString>
#include<QPaintEvent>
#include<QResizeEvent>
#include<QScrollArea>
#include<QSlider>
#include<QScrollArea>
#include<QInputDialog>
#include<QPainter>
#include<QUrl>
using namespace std;



class myPainter : public QWidget
{
    Q_OBJECT
public:
    explicit myPainter(QWidget *parent = 0);
    void init();                                                         //初始化状态
    void inlist(bool t=false);                                           //状态入列
    void newimage(int w,int h, QColor newonecolor);                      //新建图像
    void openimage(const QString &filename);                             //打开图像
    void saveasimage(const QString &filename);                           //图像另存为
    void saveimage();                                                    //图像保存
    bool isexit() const {return nowfile.length();}                       //返回有无文件状态
    bool isdrawing() const {return drawing;}                             //输出是否正在画图
    bool ischangeing() const {return changeing;}                         //输出图像是否改变
    bool judge();                                                        //判断多边形是否完成
    void setpencolor(QColor newcolor){color = newcolor;}                 //设置画笔颜色
    bool setimagesize(double t);                                         //设置放缩大小
    bool turn(int rad);                                                  //旋转
    void mirror(bool a,bool b);                                          //翻转
    void selecttime();                                                   //选区
    void bfs();                                                          //用于填充颜色

    void seterasersize(int newsize){erasersize = newsize;}               //设置橡皮擦大小
    void setpensize(int newpensize){pensize = newpensize;}               //设置画笔大小
    void openbrushmode(){brushmode = true;}                              //开启笔刷模式
    void closebrushmode(){brushmode = false;}                            //关闭笔刷模式
    void setnewimage(QImage *image,QSize newsize);                       //设置新画布用于打开图像
    void setdrawstyle(QString newstyle);                                 //用于接受基本图形模式
    QSize imageSize() const  {return image.size();}                      //反馈图像大小
    QLabel *label;                                                       //显示状态

signals:

protected:
    void mousePressEvent(QMouseEvent *event);       //重写鼠标按下事件
    void mouseMoveEvent(QMouseEvent *event);        //重写鼠标移动事件
    void mouseReleaseEvent(QMouseEvent *event);     //重写鼠标释放事件
    void paintEvent(QPaintEvent *event);            //重写绘图事件
    void resizeEvent(QResizeEvent * event);         //重写大小改变事件

public slots:
    void myredo();              //撤销
    void myundo();              //重做
    void clearimage();          //清空
    void grayimage();           //灰图

    //设置画笔类型
    void mySolidLine() {penstyLe = Qt::SolidLine;}
    void myDashLine()  {penstyLe = Qt::DashLine;}
    void myDotLine()   {penstyLe = Qt::DotLine;}
    void myDashDotLine() {penstyLe = Qt::DashDotLine;}
    void myDashDotDotLine() {penstyLe = Qt::DashDotDotLine;}
    //设置笔刷类型
    void mySolidPattern() {brushstyLe = Qt::SolidPattern;}
    void myDiagCrossPattern(){brushstyLe = Qt::DiagCrossPattern;}
    void myCrossPattern(){brushstyLe = Qt::CrossPattern;}
    void myDense7Pattern() {brushstyLe = Qt::Dense7Pattern;}
    void myBDiagPattern(){brushstyLe = Qt::BDiagPattern;}
    void myHorPattern(){brushstyLe = Qt::HorPattern;}

private:
    typedef pair<int,int> p;     //重命名,表示位置
    int i;                       //控制重绘高度
    int ttype;                   //变化状态(初始态0,顺时针1,逆时针2,上下翻转3,左右翻转4,变大5,变小6)
    bool op;                     //新建状态
    bool sl;                     //选区状态
    bool dg;                     //是否可以拖动
    QList<test>undo;             //撤销队列
    QList<test>redo;             //重做队列
    QImage *linshi;              //临时,用于记录选区
    QImage *rem;                 //用于记录选取后的图像
    QImage *followimage;         //跟踪画布，用于跟踪多边形绘画过程
    QImage remimage;             //跟踪画布,用于消除痕迹
    QImage image;                //画布
    QImage rimage;               //更换初态
    Qt::PenStyle penstyLe;       //画笔类型，用于接受画笔类型的更改
    Qt::BrushStyle brushstyLe;   //笔刷类型，用于接受笔刷类型的更改
    QColor backgroundcolor;      //设置背景色
    QColor color;                //颜色，用于颜色
    int pensize;                 //画笔大小
    int erasersize;              //橡皮大小
    QPoint lastpoint;            //
    QPoint endpoint;             //
    QPoint remfirst;             //坐标点，用于绘图
    QPoint *start;               //用于记录选区的起点
    QString drawtype;            //图形绘制状态
    QString nowfile;             //记录当前图片名称
    QString Text;                //文字
    bool clearmode;              //清空状态
    bool drawing;                //绘画状态
    bool changeing;              //图像改变状态
    bool brushmode;              //笔刷模式
    bool undomode;               //撤销模式
    bool drawpolygon;            //绘制多边形状态
};

#endif // PAINTER_H
