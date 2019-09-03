#include "form1.h"

Form1::Form1(QWidget *parent):QWidget(parent)
{
    ui->setupUi(this);
}

Form1::~Form1()
{
    delete ui;
}
