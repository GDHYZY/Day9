#include "newdialog.h"
#include<QLineEdit>
#include<QLabel>
#include<QGridLayout>
#include<QPushButton>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QIntValidator>
#include<QColorDialog>
#include<QToolButton>

Newdialog::Newdialog(QWidget *parent) :
    QDialog(parent)
{
    ans = false;
    newwene = Qt::white;
    QLabel* wLabel = new QLabel(tr("宽度:"));
    QLabel* hLabel = new QLabel(tr("高度:"));
    w = new QLineEdit;
    w->setValidator(new QIntValidator(0,3000,this));
    h = new QLineEdit;
    h->setValidator(new QIntValidator(0,3000,this));

    QPushButton *setcolor = new QPushButton(tr("背景色"));

    QGridLayout* gridLayout = new QGridLayout;
    gridLayout->addWidget(wLabel, 0, 0, 1, 1);
    gridLayout->addWidget(w, 0, 1, 1, 2);
    gridLayout->addWidget(hLabel, 1, 0, 1, 1);
    gridLayout->addWidget(h, 1, 1, 1, 2);
    gridLayout->addWidget(setcolor, 5, 0, 1, 1);//创建一个网格布局管理器

    QPushButton* ok = new QPushButton(tr("确定"));
    QPushButton* cancel = new QPushButton(tr("取消"));
    QHBoxLayout* HLayout = new QHBoxLayout;
    HLayout->setSpacing(60);
    HLayout->addWidget(ok);
    HLayout->addWidget(cancel);
    QVBoxLayout* VLayout = new QVBoxLayout;
    VLayout->setMargin(40);
    VLayout->addLayout(gridLayout);
    VLayout->addStretch(40);
    VLayout->addLayout(HLayout);
    setLayout(VLayout);

    connect(setcolor,SIGNAL(clicked()),this,SLOT(getcolor()));
    connect(ok, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));

    setWindowTitle(tr("新建"));
    resize(350, 200);
}

Newdialog::~Newdialog()
{
    delete w;
    delete h;
}

void Newdialog::getcolor()
{
    newwene = QColorDialog::getColor();
}

void Newdialog::accept()
{
    ans = true;
    bool ok,ko;
    QString getw = w->text().trimmed();
    QString geth = h->text().trimmed();
    if(getw==NULL || geth==NULL )
        return ;
    wh=getw.toInt(&ok);
    hh=geth.toInt(&ko);
    QDialog::accept();
}
