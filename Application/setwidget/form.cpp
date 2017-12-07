#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    ui->pushButton->setStyleSheet("background-color:rgb(184,232,153);color:rgb(75,126,25);hover{color:rgb(255,255,0); pressed{color:green}}");
}

Form::~Form()
{
    delete ui;
}
