#include "dialog.h"
#include "ui_dialog.h"
#include "QtSql/QSqlDatabase"
#include "QSqlQuery"
#include "widget.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    ui->label->setText("");
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("test_base");
    db.open();

    //Осуществляем запрос
    QSqlQuery query;
    query.exec("SELECT login, password FROM user");

    //Выводим значения из запроса
    while (query.next())
    {
    QString login = query.value(0).toString();
    ui->label_2->setText(login);
    QString password = query.value(1).toString();
    ui->label_3->setText(password);
    if(ui->lineEdit->text()==login && ui->lineEdit_2->text()==password)
    {
        db.close();
        Widget *w =new Widget();
        w->show();
    }

    }
    ui->label->setText("Неверный логин или пароль");

}
