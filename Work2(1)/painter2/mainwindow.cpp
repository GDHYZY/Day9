#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"newdialog.h"
#include"painter.h"
#include<QFileDialog>
#include<QDir>
#include<QMessageBox>
#include<QColorDialog>
#include<QMimeData>
#include<QInputDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mypainter = new myPainter;
    scrollarea = new QScrollArea;
    setCentralWidget(scrollarea);
    scrollarea->setWidget(mypainter);
    scrollarea->widget()->resize(1366,768);
    scrollarea->widget()->setAcceptDrops(false);
    centralWidget()->setMouseTracking(true);
    scrollarea->widget()->setMouseTracking(true);
    setAcceptDrops(true);
    setMouseTracking(true);
    setWindowTitle(tr("o(╯□╰)o"));
    newmenu();
    resize(800,600);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::newmenu()
{
    QMenu *File = menuBar()->addMenu(tr("文件"));
    newimageact = new QAction(QIcon(":/image/new"),tr("新建"),this);
    newimageact->setShortcuts(QKeySequence::New);
    connect(newimageact,&QAction::triggered,this,&MainWindow::newimage);

    openimageact = new QAction(QIcon(":/image/open"),tr("打开"),this);
    openimageact->setShortcuts(QKeySequence::Open);
    connect(openimageact,&QAction::triggered,this,&MainWindow::openimage);

    saveimageact = new QAction(QIcon(":/image/save"),tr("保存"),this);
    saveimageact->setShortcuts(QKeySequence::Save);
    connect(saveimageact,&QAction::triggered,this,&MainWindow::saveimage);

    saveasimageact = new QAction(QIcon(":/image/save"),tr("另存为"),this);
    saveasimageact->setShortcuts(QKeySequence::Save);
    connect(saveasimageact,&QAction::triggered,this,&MainWindow::saveasimage);

    exitact = new QAction(QIcon(":/image/exit"),tr("退出"),this);
    exitact->setShortcuts(QKeySequence::Quit);
    connect(exitact,&QAction::triggered,this,&MainWindow::close);

    File->addAction(newimageact);
    File->addAction(openimageact);
    File->addSeparator();
    File->addAction(saveimageact);
    File->addAction(saveasimageact);
    File->addSeparator();
    File->addAction(exitact);

    //编辑
    QMenu *Compile = menuBar()->addMenu(tr("编辑"));
    undoAction =new QAction(QIcon(":/image/undo"),tr("撤销"),this);
    undoAction->setShortcuts(QKeySequence::Undo);
    connect(undoAction,&QAction::triggered,mypainter,&myPainter::myundo);

    redoAction = new QAction(QIcon(":/image/redo"),tr("重做"),this);
    redoAction->setShortcuts(QKeySequence::Redo);
    connect(redoAction,&QAction::triggered,mypainter,&myPainter::myredo);

    clearimageact = new QAction(QIcon(":/image/new"),tr("清空"),this);
    clearimageact->setShortcuts(QKeySequence::Back);
    connect(clearimageact,&QAction::triggered,mypainter,&myPainter::clearimage);
    Compile->addAction(undoAction);
    Compile->addAction(redoAction);
    Compile->addAction(clearimageact);
    //工具

    QMenu *polygonMenu = new QMenu(tr("图形"),this);
    Lineact = new QAction(QIcon(":/image/line"),tr("直线"),this);
    connect(Lineact,&QAction::triggered,this,&MainWindow::useLine);

    Ellipseact = new QAction(QIcon(":/image/ellipse"),tr("椭圆"),this);
    connect(Ellipseact,&QAction::triggered,this,&MainWindow::useEllipse);

    Circleact = new QAction(QIcon(":/image/circle"),tr("圆形"),this);
    connect( Circleact,&QAction::triggered,this,&MainWindow::useCircle);

    Rectangleact = new QAction(QIcon(":/image/rectangle"),tr("矩形"),this);
    connect(Rectangleact,&QAction::triggered,this,&MainWindow::useRectangle);

    Polygonact = new QAction(QIcon(":/image/polygon"),tr("多边形"),this);
    connect(Polygonact,&QAction::triggered,this,&MainWindow::usePolygon);

    Pathact = new QAction(QIcon(":/image/path"),tr("路径"),this);
    connect(Pathact,&QAction::triggered,this,&MainWindow::usePath);

    Arcact = new QAction(QIcon(":/image/arc"),tr("圆弧"),this);
    connect(Arcact,&QAction::triggered,this,&MainWindow::useArc);

    polygonMenu->addAction(Lineact);
    polygonMenu->addAction(Ellipseact);
    polygonMenu->addAction(Circleact);
    polygonMenu->addAction(Arcact);
    polygonMenu->addAction(Rectangleact);
    polygonMenu->addAction(Polygonact);
    polygonMenu->addAction(Pathact);

    QMenu *Tool = menuBar()->addMenu(tr("工具"));
    penact = new QAction(QIcon(":/images/tool-pen"),tr("设置画笔大小"),this);
    connect(penact,&QAction::triggered,this,&MainWindow::setpen);

    QMenu *pentype = new QMenu(tr("设置画笔类型"),this);
    penSolidLine = new QAction(QIcon(":/images/tool-pen"),tr("实线"),this);
    connect(penSolidLine,&QAction::triggered,mypainter,&myPainter::mySolidLine);

    penDashLine = new QAction(QIcon(":/images/tool-pen"),tr("虚线"),this);
    connect(penDashLine,&QAction::triggered,mypainter,&myPainter::myDashLine);

    penDotLine = new QAction(QIcon(":/images/tool-pen"),tr("点线"),this);
    connect(penDotLine,&QAction::triggered,mypainter,&myPainter::myDotLine);

    penDashDotLine = new QAction(QIcon(":/images/tool-pet"),tr("虚点线"),this);
    connect(penDashDotLine,&QAction::triggered,mypainter,&myPainter::myDashDotLine);

    penDashDotDotLine = new QAction(QIcon(":/images/tool-pen"),tr("虚点点线"),this);
    connect(penDashDotDotLine,&QAction::triggered,mypainter,&myPainter::myDashDotDotLine);

    pentype->addAction(penSolidLine);
    pentype->addAction(penDashLine);
    pentype->addAction(penDotLine);
    pentype->addAction(penDashDotLine);
    pentype->addAction(penDashDotDotLine);

    QMenu *brushtype = new QMenu(tr("设置笔刷类型"),this);
    brushsp = new QAction(QIcon(":/images/tool-pen"),tr("填充颜色"),this);
    connect(brushsp,&QAction::triggered,mypainter,&myPainter::mySolidPattern);

    brushhp = new QAction(QIcon(":/images/tool-pen"),tr("横线"),this);
    connect(brushhp,&QAction::triggered,mypainter,&myPainter::myHorPattern);

    brushcp = new QAction(QIcon(":/images/tool-pen"),tr("交线"),this);
    connect(brushcp,&QAction::triggered,mypainter,&myPainter::myCrossPattern);

    brushbdp = new QAction(QIcon(":/images/tool-pen"),tr("斜线"),this);
    connect(brushbdp,&QAction::triggered,mypainter,&myPainter::myBDiagPattern);

    brushd7p = new QAction(QIcon(":/images/tool-pen"),tr("点"),this);
    connect(brushd7p,&QAction::triggered,mypainter,&myPainter::myDense7Pattern);

    brushdcp = new QAction(QIcon(":/images/tool-pen"),tr("对角交线"),this);
    connect(brushdcp,&QAction::triggered,mypainter,&myPainter::myDiagCrossPattern);

    brushtype->addAction(brushsp);
    brushtype->addAction(brushhp);
    brushtype->addAction(brushcp);
    brushtype->addAction(brushbdp);
    brushtype->addAction(brushd7p);
    brushtype->addAction(brushdcp);

    eraseract = new QAction(QIcon(":/images/tool-Eraser"),tr("设置橡皮擦大小"),this);
    connect(eraseract,&QAction::triggered,this,&MainWindow::seteraser);

    Tool->addAction(penact);
    Tool ->addAction(eraseract);
    Tool->addMenu(pentype);
    Tool->addMenu(brushtype);
    Tool->addMenu(polygonMenu);
//旋转
    QMenu *trans = menuBar()->addMenu(tr("旋转翻转"));
    right = new QAction(QIcon(":/image/right"),tr("顺时针旋转90度"),this);
    connect(right,&QAction::triggered,this,&MainWindow::turnright);

    left = new QAction(QIcon(":/image/left"),tr("逆时针旋转90度"),this);
    connect(left,&QAction::triggered,this,&MainWindow::turnleft);

    lr = new QAction(QIcon(":/image/lr"),tr("左右翻转"),this);
    connect(lr,&QAction::triggered,this,&MainWindow::mlr);

    ud = new QAction(QIcon(":/image/lr"),tr("上下翻转"),this);
    connect(ud,&QAction::triggered,this,&MainWindow::mud);

    trans->addAction(right);
    trans->addAction(left);
    trans->addAction(lr);
    trans->addAction(ud);
//滤镜
    QMenu *filter =menuBar()->addMenu(tr("滤镜"));
    gray = new QAction(QIcon(":/image/gray"),tr("灰图"),this);
    connect(gray,&QAction::triggered,mypainter,&myPainter::grayimage);

    filter->addAction(gray);

    ui->mainToolBar->addAction(openimageact);
    ui->mainToolBar->addAction(saveimageact);
    ui->mainToolBar->addAction(clearimageact);
    usepenact = new QAction(QIcon(":/image/pen2"),tr("画笔"),this);
    connect(usepenact,&QAction::triggered,this,&MainWindow::usepen);
    ui->mainToolBar->addAction(usepenact);

    usebrushact = new QAction(QIcon(":/image/brush2"),tr("笔刷"),this);
    connect(usebrushact,&QAction::triggered,this,&MainWindow::usebrush);
    ui->mainToolBar->addAction(usebrushact);

    useeraseract = new QAction(QIcon(":/image/eraser2"),tr("橡皮擦"),this);
    connect(useeraseract,&QAction::triggered,this,&MainWindow::useeraser);
    ui->mainToolBar->addAction(useeraseract);

    Textact = new QAction(QIcon(":/image/word2"),tr("文字"),this);
    connect(Textact,&QAction::triggered,this,&MainWindow::useText);
    ui->mainToolBar->addAction(Textact);

    coloract = new QAction(QIcon(":/image/color"),tr("颜色"),this);
    connect(coloract,&QAction::triggered,this,&MainWindow::setcolor);
    ui->mainToolBar->addAction(coloract);

    ui->mainToolBar->addAction(Lineact);
    ui->mainToolBar->addAction(Rectangleact);
    ui->mainToolBar->addAction(Ellipseact);
    ui->mainToolBar->addAction(Polygonact);

    select = new QAction(QIcon(":/image/select2"),tr("选区"),this);
    connect(select,&QAction::triggered,mypainter,&myPainter::selecttime);
    ui->mainToolBar->addAction(select);

    QAction *tc = new QAction(QIcon(":/image/tianchong"),tr("填充颜色"),this);
    connect(tc,&QAction::triggered,this,&MainWindow::allcolor);
    ui->mainToolBar->addAction(tc);


    big = new QAction(QIcon(":/image/big"),tr("放大"),this);
    connect(big,&QAction::triggered,this,&MainWindow::tobig);
    ui->mainToolBar->addAction(big);

    small = new QAction(QIcon(":/image/small"),tr("缩小"),this);
    connect(small,&QAction::triggered,this,&MainWindow::tosmall);
    ui->mainToolBar->addAction(small);


//状态栏
    statusBar()->addWidget(mypainter->label);
    statusBar()->setStyleSheet(QString("QStatusBar::item{border: 0px}"));

}

void MainWindow::openimage()        //打开图片
{
    QString lay = QFileDialog::getOpenFileName(this,tr("打开图片"), QDir::currentPath());
    if(!lay.isEmpty())
    {
        QImage temp;
        if(!temp.load(lay)) return ;
        scrollarea->widget()->resize(temp.size());
        mypainter->openimage(lay);
    }
}

void MainWindow::saveimage()        //保存
{
    if(mypainter->isexit())
    {
        mypainter->saveimage();
    }
    else
        saveasimage();
}

void MainWindow::saveasimage()          //保存
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("另存为"),"./未命名.bmp",tr("Images(*.bmp);;Images(*.png);;Images(*.xpm);;Images(*.jpg)"));
       if (!fileName.isEmpty())
       {
           mypainter->saveasimage(fileName);
       }
}

bool MainWindow::maybesave()            //判断是否保存
{
    if(mypainter->ischangeing())
    {
        QMessageBox::StandardButton ask;
        ask = QMessageBox::warning(this,tr("画图"),tr("图片已发生改变,你想要保存吗?"),QMessageBox::Save |  QMessageBox::Cancel);
        if(ask == QMessageBox::Save)
        {
            saveimage();
            return true;
        }
    }
    return false;
}

void MainWindow::newimage()   //新建画布
{
    maybesave();
    Nd = new Newdialog ;
    Nd->exec();
    int weight = Nd->wh;
    int height = Nd->hh;
    bool ok = Nd->ans;
    QColor newcl = Nd->newwene;
    if(ok)
    {
        scrollarea->widget()->resize(weight,height);
        mypainter->newimage(weight,height,newcl);
    }

    delete Nd;
}


void MainWindow::setpen()     //设置画笔大小
{
    bool ok;
   int newsize = QInputDialog::getInt(this, tr("设置笔宽"),tr("请选择笔宽:"),1,1,50,1,&ok);
        if (ok)
            mypainter->setpensize(newsize);
}


void MainWindow::seteraser()   //设置橡皮擦大小
{
    bool ok;
    int size = QInputDialog::getInt(this,tr("设置橡皮擦大小"),tr("请选择大小:"),1,10,30,1,&ok);
    if(ok) mypainter->seterasersize(size);
}

void MainWindow::turnright()        //顺时针旋转90
{
    if(mypainter->turn(90))
    {
        QSize s = mypainter->imageSize();
        scrollarea->widget()->resize(s);
    }
}

void MainWindow::turnleft()         //逆时针旋转90
{
    if(mypainter->turn(270))
    {
        QSize s = mypainter->imageSize();
        scrollarea->widget()->resize(s);
    }
}

void MainWindow::mlr()          //左右翻转
{
    mypainter->mirror(1,0);
}

void MainWindow::mud()          //上下翻转
{
    mypainter->mirror(0,1);
}



void MainWindow::usePolygon()
{
    mypainter->setdrawstyle("Polygon");
}

void MainWindow::useLine()
{
    mypainter->setdrawstyle("Line");
}

void MainWindow::useCircle()
{
    mypainter->setdrawstyle("Circle");
}

void MainWindow::useRectangle()
{
    mypainter->setdrawstyle("Rectangle");
}

void MainWindow::useEllipse()
{
    mypainter->setdrawstyle("Ellipse");
}

void MainWindow::useArc()
{
    mypainter->setdrawstyle("Arc");
}

void MainWindow::useText()
{
    mypainter->setdrawstyle("Text");
}

void MainWindow::usePath()
{
    mypainter->setdrawstyle("Path");
}

void MainWindow::usepen()
{
    mypainter->setdrawstyle("Nothing");
    mypainter->closebrushmode();
}

void MainWindow::usebrush()
{
    mypainter->openbrushmode();
}

void MainWindow::useeraser()
{
    mypainter->setdrawstyle("Eraser");
    mypainter->closebrushmode();

}

void MainWindow::setcolor()       //设置颜色
{
    QColor newcolor = QColorDialog::getColor();
    mypainter->setpencolor(newcolor);
}

void MainWindow::allcolor()     //填充颜色
{
    mypainter->setdrawstyle("Fill");
}


void MainWindow::tobig()                //放大
{
    if(mypainter->setimagesize(2.0))
    scrollarea->widget()->resize(mypainter->imageSize());
}

void MainWindow::tosmall()              //缩小
{
    if(mypainter->setimagesize(0.5))
    scrollarea->widget()->resize(mypainter->imageSize());
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    if(maybesave())
    {
        event->accept();
    }
    else
        event->accept();
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
}

void MainWindow::dropEvent(QDropEvent *event)
{
    maybesave();
    QList<QUrl> urls = event->mimeData()->urls();
    if(urls.isEmpty())
        return;
    QString fileName = urls.first().toLocalFile();
    if(fileName.isEmpty())
        return;
    QImage linshi;
    if(!linshi.load(fileName))
        return;
    scrollarea->widget()->resize(linshi.size());
    mypainter->openimage(fileName);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    mypainter->label->setText(tr("o(╯□╰)o"));
    QWidget::mouseMoveEvent(event);
}

