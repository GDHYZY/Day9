#include "painter.h"
#include<QPainter>
#include<QRect>
#include<QSize>
#include<QMouseEvent>
#include <QWidget>
#include<QPoint>
#include<QImage>
#include<QString>
#include<QPaintEvent>
#include<QResizeEvent>
#include<QMimeData>
#include<QInputDialog>
#include<QRgb>
#include<queue>



myPainter::myPainter(QWidget *parent) :
    QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    setAcceptDrops(true);
    setAutoFillBackground(true);
    label = new QLabel;
    label->setMinimumSize(label->sizeHint());
    label->setAlignment(Qt::AlignHCenter);
    undo.clear();
    redo.clear();
    init();
    inlist();
    redo.append(undo.back());
}

void myPainter::init()
{
    image.fill(backgroundcolor);
    penstyLe = Qt::SolidLine;
    brushstyLe = Qt::SolidPattern;
    i=1;
    pensize = 1;
    erasersize = 15;
    ttype = 0;
    color = Qt::black;
    backgroundcolor = Qt::white;
    penstyLe = Qt::SolidLine;
    brushstyLe = Qt::SolidPattern;;
    lastpoint  = endpoint = QPoint(0,0);
    sl = false;
    drawing = false;
    brushmode = false;
    changeing = false;
    drawpolygon = false;
    dg = false;
    undomode = false;           //撤销模式
    clearmode  = false;         //清空模式
    op = false;                 //打开模式
    drawtype = "Nothing";
}

void myPainter::newimage(int w, int h ,QColor newonecolor)          //新建画布
{
    QImage newone (QSize(w,h),QImage::Format_RGB32);
    backgroundcolor = newonecolor;
    newone.fill(backgroundcolor);
    image = newone;
    undo.clear();
    redo.clear();
    init();
    inlist();
    redo.append(undo.back());
    update();
}

void myPainter::openimage(const QString &filename)  //打开图像
{
    QImage newimage;
    nowfile = filename;
    if(!newimage.load(filename)) return ;
    QSize newsize = newimage.size().expandedTo(size());
    setnewimage(&newimage,newsize);
    init();
    image = rimage = newimage;
    op = true;
    undo.clear();
    redo.clear();
    inlist();
    redo.append(undo[undo.size()-1]);
    update();
}

void myPainter::saveasimage(const QString &filename)      //图像另存为
{
    QImage simage = image;
    nowfile = filename;
    setnewimage(&simage,size());
    if(simage.save(filename))
        changeing = false;
}

void myPainter::saveimage()         //图像保存
{
    QImage saveig = image;
    setnewimage(&saveig,size());
    if(saveig.save(nowfile))
        changeing = false;
}

bool myPainter::judge()     //判断多边形是否完成
{
    if((endpoint.rx() > remfirst.rx()-10 && endpoint.rx()< remfirst.rx()+10)&&(endpoint.ry() > remfirst.ry()-10 && endpoint.ry()< remfirst.ry()+10))
        return true;
    else
        return false;
}

bool myPainter::setimagesize(double t)      //设置放缩大小
{
    if(sl)
    {
        if(t==2.0)
            ttype = 5;
        else ttype = 6;
        QSize s = linshi->size();
        *linshi = linshi->scaled((int)(s.width() * t),(int)(s.height() * t));
        update();
        return 0;
    }
    else
    {
        QSize s = image.size();
        image = image.scaled((int)(s.width() * t),(int)(s.height() * t));
        changeing = true;
        i = undo.size();
        update();
        return 1;
    }
}

bool myPainter::turn(int rad)       //旋转
{
    QMatrix matrix;
    matrix.rotate(rad);
    if(sl)
    {
        if(rad==90) ttype = 1;
        else ttype=2;
        start->rx() += (linshi->width()-linshi->height())/2;
        start->ry() += (linshi->width()-linshi->height())/2;
        *linshi = linshi->transformed(matrix);
        update();
        return 0;
    }
    image = rimage = image.transformed(matrix);
    i=undo.size();
    update();
    return 1;
}

void myPainter::mirror(bool a, bool b)      //翻转
{
    if(sl)
    {
        if(a==0&&b==1) ttype = 3;
        else ttype = 4;
        *linshi = linshi->mirrored(a,b);
        update();
    }
    else
    {
        image = rimage = image.mirrored(a,b);
        i=undo.size();
        update();
    }
}

void myPainter::selecttime()
{
    drawtype = "Rectangle";
    myDashLine();
    setpensize(1);
    sl = true;
    dg = false;
}

void myPainter::bfs()
{
    int sx=undo[i].lastpoint.rx();
    int sy=undo[i].lastpoint.ry();
    queue<p>q;
    q.push(p(sx,sy));
    QRgb a = image.pixel(undo[i].lastpoint);
    QRgb b = undo[i].color.rgb();
    int dx[4] = {1,0,-1,0},dy[4]={0,1,0,-1};
    while(q.size())
    {
        p now = q.front();
        q.pop();
        QRgb x = image.pixel(QPoint(now.first,now.second));
        if(a == b) break;
        if(x!=a)
            continue;
        image.setPixel(now.first,now.second,b);
        for(int k = 0;k<4;k++)
        {
            int nx = now.first + dx[k],ny = now.second + dy[k];
            if(image.rect().contains(nx,ny))
            {
                QRgb n = image.pixel(nx,ny);
                if(n==a && n!=b)
                    q.push(p(nx,ny));
            }
        }
    }
}

void myPainter::clearimage()   //清空
{
    drawing = false;
    clearmode = true;
    changeing = true;
    inlist();
    update();
    drawpolygon = false;
    clearmode = false;
}

void myPainter::grayimage()     //灰度图
{
    unsigned char *data=image.bits();
    int W = image.width();
    int H = image.height();
    unsigned char r,g,b;
    for(int k =0;k<H;k++)
    {
        for(int l=0;l<W;l++)
        {
            r = *(data+2);
            g = *(data+1);
            b = *data;
            *data = (r*30 + g*59 + b*11)/100;
            *(data+1) = (r*30 + g*59 + b*11)/100;
            *(data+2) = (r*30 +g*59 + b*11)/100;
            data += 4;
        }
    }
    rimage = image;
    changeing = true;
    i = undo.size();
    update();
}


void myPainter::resizeEvent(QResizeEvent *event)    //重写大小改变事件
{
    int newWidth = qMax(width() , image.width());
    int newHeight = qMax(height() , image.height());
    setnewimage(&image, QSize(newWidth, newHeight));
    update();
    QWidget::resizeEvent(event);
}

void myPainter::myredo()             //重做
{
    if(redo.size()>1)
    {
        int k = redo.size()-1;
        if(redo[k].mark==0&&redo[k-1].mark==1)
            for(int l = k;;l--)
            {
                if(redo[l].mark==0&&l!=k)
                {
                    undo.append(redo[l]);
                    redo.removeAt(l);
                    break;
                }
                undo.append(redo[l]);
                redo.removeAt(l);
            }
        else if(redo[k].drawtype=="Polygon")        //处理多边形
        {
            for(int l = k;;l--)
            {
                if(redo[l].drawtype!="Polygon")
                    break;
                undo.append(redo[l]);
                redo.removeAt(l);
            }
        }
        else if(redo[k].mark==0 && redo[k-1].mark==0 && redo[k].drawtype == redo[k-1].drawtype && (!redo[k].clearmode))
        {
            undo.append(redo[k]);
            redo.removeAt(k);
            undo.append(redo[k-1]);
            redo.removeAt(k-1);
        }
        else
        {
            undo.append(redo[k]);
            redo.removeAt(k);
        }
        update();
    }
}


void myPainter::myundo()              //撤销
{
    if(undo.size()>1)
    {
        undomode = true;
        sl = false;
        dg = false;
        i=1;
        if(op)
            image = rimage;
        else
            image.fill(backgroundcolor);
        int k= undo.size()-1;
        if(undo[k].mark==0&&undo[k-1].mark==1)      //处理涂鸦
            for(int l = k;;l--)
            {
                if(undo[l].mark==0&&l!=k)
                {
                    redo.append(undo[l]);
                    undo.removeAt(l);
                    break;
                }
                redo.append(undo[l]);
                undo.removeAt(l);
            }
        else if(undo[k].drawtype=="Polygon")        //处理多边形
        {
            for(int l = k;;l--)
            {
                if(undo[l].drawtype!="Polygon")
                    break;
                redo.append(undo[l]);
                undo.removeAt(l);
            }
        }
        else if(undo[k].mark==0 && undo[k-1].mark==0 && undo[k].drawtype == undo[k-1].drawtype && (!undo[k].clearmode))
        {//处理其他
            redo.append(undo[k]);
            undo.removeAt(k);
            redo.append(undo[k-1]);
            undo.removeAt(k-1);
        }
        else //处理单一操作
        {
            redo.append(undo[k]);
            undo.removeAt(k);
        }
        update();
    }
}


void myPainter::inlist(bool t)         //状态入列
{
    test rd;
    rd.brushstyLe = brushstyLe;
    rd.penstyLe = penstyLe;
    rd.pensize = pensize;
    rd.erasersize = erasersize;
    rd.backgroundcolor = backgroundcolor;
    rd.color = color;
    rd.brushmode = brushmode;
    rd.lastpoint = lastpoint;
    rd.endpoint = endpoint;
    rd.drawtype = drawtype;
    rd.nowfile =nowfile;
    rd.sl = sl;
    rd.dg = dg;
    rd.mark = t;
    rd.clearmode = clearmode;
    undo.append(rd);
}



void myPainter::setnewimage(QImage *image, QSize newsize)   //设置新画布用于打开图像
{
    if(image->size()== newsize)
        return ;
    QImage NEWIMAGE(newsize,QImage::Format_RGB32);
    NEWIMAGE.fill(qRgb(255,255,255));
    QPainter painter(&NEWIMAGE);
    painter.drawImage(QPoint(0,0),*image);
    *image = NEWIMAGE;
}

void myPainter::setdrawstyle(QString newstyle)  //改变画笔类型
{
    drawtype = newstyle;
    sl=false;
    mySolidLine();
}



void myPainter::paintEvent(QPaintEvent *event)  //重写绘图事件
{
    QPainter ipainter(this);
    if(sl&&(ttype==1 || ttype==2)) //旋转
    {
        *undo.back().rem = *linshi;
        *undo.back().start = *start;
        image = *rem;
        QPainter p(&image);
        p.drawImage(*start,*linshi);
        ttype = 0;
    }
    else if(sl&&(ttype==3 || ttype==4)) //翻转
    {
        *undo.back().rem = *linshi;
        image = *rem;
        QPainter p(&image);
        p.drawImage(*start,*linshi);
        ttype = 0;
    }
    else if(sl&&(ttype==5 || ttype==6)) //放缩
    {
        *undo.back().rem = *linshi;
        image = *rem;
        QPainter p(&image);
        p.drawImage(*start,*linshi);
        ttype = 0;
    }
    else
    {
    if(sl && dg && undo.back().mark==true && undo.back().drawtype=="Rectangle")      //选区移动
    {
        image = *rem;
        int k;
        for(k = undo.size()-1; ;k--)
            if(undo[k].mark==false)
                break;
        QPoint a = undo[k].lastpoint;
        QPoint b = undo.back().endpoint;
        QPoint s;
        int x = b.rx()-a.rx();
        int y = b.ry()-a.ry();
        s.rx()= x + start->rx();
        s.ry()= y + start->ry();
        QPainter p(&image);
        p.drawImage(s,*linshi);
    }
    else
    {
        if(sl && undo.back().mark==false && dg==false && undo.back().drawtype=="Rectangle")       //确定选区并获取选区内容
        {
            int t = undo.size()-2;
            QPainter p(&image);
            QPoint a = undo[t].lastpoint;
            QPoint b = undo.back().endpoint;
            start = new QPoint(qMin(a.rx(),b.rx()),qMin(a.ry(),b.ry()));
            int w = abs(b.rx()-a.rx());
            int h = abs(b.ry()-a.ry());
            if(w!=0&&h!=0)
            {
                linshi = new QImage;
                *linshi = image.copy(start->rx(),start->ry(),w+1,h+1);
                for(int k = start->rx(); k<=start->rx()+w; k++)
                    for(int l = start->ry();l<= start->ry()+h;l++)
                    {
                        QRgb q = backgroundcolor.rgb();
                        image.setPixel(k,l,q);
                    }
                //处理边框
                for(int k = start->rx(),l = start->ry(); l<=start->ry()+h;l++)
                {
                    QRgb q = remimage.pixel(k,l);
                    linshi->setPixel(0,l-(start->ry()),q);
                }
                for(int k = start->rx()+w,l=start->ry(); l<=start->ry()+h;l++)
                {
                    QRgb q = remimage.pixel(k,l);
                    linshi->setPixel(w,l-(start->ry()),q);
                }
                for(int k = start->rx(),l = start->ry(); k<=start->rx()+w;k++)
                {
                    QRgb q = remimage.pixel(k,l);
                    linshi->setPixel(k-(start->rx()),0,q);
                }
                for(int k = start->rx(),l = start->ry()+h; k<=start->rx()+w;k++)
                {
                    QRgb q = remimage.pixel(k,l);
                    linshi->setPixel(k-(start->rx()),h,q);
                }
                rem =new QImage;
                *rem = image;
                p.drawImage(start->rx(),start->ry(),*linshi);
                dg = true;
                undo.back().rem = new QImage(*linshi);
                undo.back().start = new QPoint;
                *undo.back().start = *start;
            }
        }
        else if(dg && sl && undo.back().mark==false && undo.back().drawtype=="Rectangle")  //移动完毕
        {
            QPoint a = undo.back().lastpoint;
            QPoint b = undo.back().endpoint;
            int c = b.rx()-a.rx();
            int d = b.ry()-a.ry();
            start->rx() += c;
            start->ry() +=d;
            undo.back().rem = new QImage(*linshi);
            undo.back().start = new QPoint;
            *undo.back().start = *start;
        }
        else
        {
            if(undomode)        //撤销模式
            {
                QRect dirtyRect = event->rect();
                ipainter.drawImage(dirtyRect,image, dirtyRect);
                undomode =false ;
            }
            QPainter painter(&image);
            for(;i < undo.size();i++)
            {
                painter.setPen(QPen(undo[i].color,undo[i].pensize,undo[i].penstyLe,Qt::RoundCap,Qt::RoundJoin));
                if(undo[i].clearmode)
                {
                    image.fill(undo[i].backgroundcolor);
                    continue;
                }
                if(undo[i].brushmode)           //判断是否为笔刷模式
                {
                    painter.setBrush(QBrush(undo[i].color,undo[i].brushstyLe));    //默认为填充
                }
                if(undo[i].drawtype=="Line" || undo[i].drawtype=="Nothing"|| undo[i].drawtype =="Polygon" )  //直线、多边形
                {
                    if(undo[i].lastpoint==undo[i].endpoint)
                        painter.drawPoint(undo[i].lastpoint);
                    else
                        painter.drawLine(undo[i].lastpoint,undo[i].endpoint);
                }
                else if( undo[i].drawtype=="Eraser") // 橡皮擦
                {
                    painter.setPen(QPen(undo[i].backgroundcolor,undo[i].erasersize,Qt::SolidLine, Qt::RoundCap,Qt::RoundJoin));
                    painter.drawLine(undo[i].lastpoint,undo[i].endpoint);
                }
                else if(undo[i].drawtype == "Ellipse")   //椭圆
                {
                    painter.drawEllipse(QRectF(undo[i].lastpoint.rx(),undo[i].lastpoint.ry(),undo[i].endpoint.rx()-undo[i].lastpoint.rx(),undo[i].endpoint.ry()-undo[i].lastpoint.ry()));
                }
                else if(undo[i].drawtype == "Circle")   //圆
                {
                    painter.drawEllipse(QPointF((undo[i].endpoint.rx()+undo[i].lastpoint.rx())/2.0,(undo[i].endpoint.ry()+undo[i].lastpoint.ry())/2.0),qMin(undo[i].endpoint.rx()-undo[i].lastpoint.rx(),undo[i].endpoint.ry()-undo[i].lastpoint.ry()),qMin(undo[i].endpoint.rx()-undo[i].lastpoint.rx(),undo[i].endpoint.ry()-undo[i].lastpoint.ry()));
                }
                else if(undo[i].drawtype=="Arc")  //圆弧
                {
                    painter.drawArc(QRectF(undo[i].lastpoint.rx(),undo[i].lastpoint.ry(),undo[i].endpoint.rx()-undo[i].lastpoint.rx(),undo[i].endpoint.ry()-undo[i].lastpoint.ry()),30*16,120*16);
                }
                else if(undo[i].drawtype == "Rectangle")   //矩形
                {
                    if(undo[i].sl && undo[i].mark==false && undo[i].dg==false && undo[i].lastpoint!=undo[i].endpoint )
                    {         //更改选区内容并移动
                        QPoint a = undo[i].lastpoint;
                        QPoint b = undo[i].endpoint;
                        int w = abs(b.rx()-a.rx());
                        int h = abs(b.ry()-a.ry());
                        for(int k = undo[i].start->rx(); k <= undo[i].start->rx()+w; k++)
                            for(int l = undo[i].start->ry();l<= undo[i].start->ry()+h;l++)
                            {
                                QRgb q = undo[i].backgroundcolor.rgb();
                                image.setPixel(k,l,q);
                            }
                        painter.drawImage(*undo[i].start,*undo[i].rem);
                    }
                    else if(undo[i].sl && undo[i].mark==false && undo[i].dg && undo[i].lastpoint!=undo[i].endpoint )
                    {         //更改选区内容并移动
                        QPoint a = undo[i-2].lastpoint;
                        QPoint b = undo[i-2].endpoint;
                        int w = abs(b.rx()-a.rx());
                        int h = abs(b.ry()-a.ry());
                        for(int k = undo[i-2].start->rx(); k <= undo[i-2].start->rx()+w; k++)
                            for(int l = undo[i-2].start->ry();l<= undo[i-2].start->ry()+h;l++)
                            {
                                QRgb q = undo[i-2].backgroundcolor.rgb();
                                image.setPixel(k,l,q);
                            }
                        painter.drawImage(*undo[i].start,*undo[i].rem);
                    }
                    else
                        painter.drawRect(undo[i].lastpoint.rx(),undo[i].lastpoint.ry(),undo[i].endpoint.rx()-undo[i].lastpoint.rx(),undo[i].endpoint.ry()-undo[i].lastpoint.ry());
                }
                else if(undo[i].drawtype == "Text")  //文本
                {
                    painter.drawText(QRectF(undo[i].lastpoint.rx(),undo[i].lastpoint.ry(),undo[i].endpoint.rx()-undo[i].lastpoint.rx(),undo[i].endpoint.ry()-undo[i].lastpoint.ry()),Text);
                }
                else if(undo[i].drawtype=="Path")   //路径
                {
                    QPainterPath *path = new QPainterPath(QPointF(undo[i].lastpoint));
                    path->cubicTo(QPointF(undo[i].endpoint.rx(),undo[i].lastpoint.ry()),(undo[i].lastpoint+undo[i].endpoint)/2,undo[i].endpoint);
                    painter.drawPath(*path);
                }
                else if(undo[i].drawtype == "Fill")     //填充
                {
                    bfs();
                }
            }
        }
    }
    }
    i = undo.size()-1;
    drawing = true;
    QRect dirtyRect = event->rect();
    ipainter.drawImage(dirtyRect,image, dirtyRect);
    if(drawtype!="Nothing" && drawtype!="Eraser")
    {
        for(;undo[i].mark;i--)
            undo.removeLast();
    }

}


void myPainter::mousePressEvent(QMouseEvent *event)  //鼠标按下事件
{
    if (event->button() == Qt::LeftButton)
    {
        if(sl && dg)        //判断选区是否可以拖动
        {
            lastpoint = endpoint = event->pos();
            if((lastpoint.rx() > start->rx()) && (lastpoint.rx() < (start->rx()+ linshi->width())) && (lastpoint.ry() > start->ry()) && (lastpoint.ry()<(start->ry()+linshi->height())))
            {
                if(undo.back().sl&&undo.back().dg&&undo.back().mark==false) //裁剪路径
                {
                    undo.pop_back();
                    undo.pop_back();
                }
                inlist();
                return ;
            }
            else
            {
                dg = false;
                delete rem;
                delete start;
                delete linshi;
            }
        }
        if(drawtype == "Polygon" && drawpolygon==false)
        {
            followimage = new QImage;
            lastpoint = endpoint = event->pos();
            remfirst = lastpoint;
            inlist();
            drawpolygon = true;
        }
        if(drawtype == "Polygon" && drawpolygon)
        {
            lastpoint = endpoint;
            endpoint  = event->pos();
            remimage = image;
        }
        else
        {
            if(drawpolygon)     //判断多边形是否中途中断
            {
                lastpoint = endpoint;
                endpoint = remfirst;
                QString s = drawtype;
                drawtype = "Polygon";
                inlist();
                drawtype = s;
                drawpolygon = false;
                update();
                delete followimage;
            }
            lastpoint = endpoint = event->pos();  //  核心部分（以上为控制多边形的控制条件和画法）
            drawing = true;                       //
            inlist();                             //
            remimage = image;                     //
        }
    }
}


void myPainter::mouseMoveEvent(QMouseEvent *event)      //鼠标移动事件
{
    QPoint nowpos = event->pos();
    label->setText(QString(tr("当前鼠标位置(%1,%2) | 画布大小(%3,%4)")).arg(nowpos.x()).arg(nowpos.y()).arg(image.size().width()).arg(image.size().height()));
    if(event->buttons()& Qt::LeftButton)
    {
        if(drawtype != "Text" /*&& drawtype!="Fill"*/)
        {
            if(drawtype == "Nothing" || drawtype=="Eraser" || drawtype=="Brush")
            {
                lastpoint = endpoint;
                inlist(1);
            }
            endpoint = event->pos();
            inlist(1);
            if(drawtype != "Nothing" && (drawtype!="Eraser"|| drawtype=="Brush"))
                image = remimage;
            update();
        }
    }
}


void myPainter::mouseReleaseEvent(QMouseEvent *event)       //鼠标释放事件
{
    if(event->button() ==Qt::LeftButton)
    {
        endpoint = event->pos();
        if(drawtype == "Text")
        {
            bool ok;
            Text = QInputDialog::getMultiLineText(this,tr("请输入文字"),tr("内容:"),tr("您的内容"),&ok);
            if(ok)
            {
                inlist();
                update();
            }
        }
        if(judge() && drawtype == "Polygon")
        {
            image = *followimage;
            endpoint = remfirst;
            inlist();
            update();
            drawpolygon = false;
            delete followimage;
        }
        else
        {
            if(drawtype!="Text")
            {
                inlist();
                update();
            }
        }
        if(drawpolygon)
        *followimage = image;

        drawing = false;
        changeing = true;
        undo.back().drawing = false;
        undo.back().changeing = true;
    }
}

