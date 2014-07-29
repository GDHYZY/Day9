#ifndef NEWDIALOG_H
#define NEWDIALOG_H

#include <QDialog>
#include<QLineEdit>


class Newdialog : public QDialog
{
    Q_OBJECT
public:
    explicit Newdialog(QWidget *parent = 0);
    ~Newdialog();
    QLineEdit *h;
    QLineEdit *w;
    int wh;
    int hh;
    bool ans;
    QColor newwene;
signals:

public slots:
    void accept();
    void getcolor();
};

#endif // NEWDIALOG_H
