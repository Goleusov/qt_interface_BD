#include "widget.h"
#include "ui_widget.h"
#include <QMediaPlayer>
#include <QCryptographicHash>
#include "QtSql/QSqlDatabase"
#include "QSqlQuery"
#include <QSqlError>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{

}

void Widget::on_pushButton_2_clicked()
{
    QSqlDatabase db;
   // db = QSqlDatabase::database();
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("test_base");
    db.open();



    //Осуществляем запрос
    //query.exec("SELECT id, name, surname, position, patronymic FROM people");

    /* Запрос SQL формируется из QVariantList,
     * в который передаются данные для вставки в таблицу.
     * */
    QSqlQuery query;
    /* В начале SQL запрос формируется с ключами,
     * которые потом связываются методом bindValue
     * для подстановки данных из QVariantList
     * */
    QVariantList data;
        data.append(ui->lineEdit->text());
        data.append(ui->lineEdit_2->text());
        data.append(ui->lineEdit_3->text());
        QString s = "My string";
        QByteArray ba = ui->lineEdit_2->text().toUtf8();
        QString result = QString(QCryptographicHash::hash((ba),QCryptographicHash::Md5).toHex());
        ui->textEdit->insertPlainText( result);
    query.prepare("INSERT INTO user ( login, password, admin ) "
                  "VALUES (:Login, :Password, :Admin)");
    query.bindValue(":Login",       ui->lineEdit->text());
    query.bindValue(":Password",       result);
    query.bindValue(":Admin",         ui->lineEdit_3->text().toInt());

    // После чего выполняется запросом методом exec()
    if(!query.exec()){
        //Debug() << "error insert into " << TABLE;
        //qDebug() << query.lastError().text();
       // ui->textEdit->insertPlainText( query.lastError().text());
    } else {

         ui->textEdit->insertPlainText( "норма"); ;
    }
    db.close();
/*
    //Выводим значения из запроса
    while (query.next())
    {
    QString id = query.value(0).toString();
    QString name = query.value(1).toString();
    QString surname = query.value(2).toString();
    QString position = query.value(3).toString();
    QString patronymic = query.value(4).toString();
    ui->textEdit->insertPlainText(id+" "+name+" "+surname+" "+position+" "+patronymic+"\n");
    ui->label->setText(name);
    ui->label_2->setText(surname);
    ui->label_3->setText(position);
    ui->label_4->setText(patronymic);

    }
     db.close();*/
}


