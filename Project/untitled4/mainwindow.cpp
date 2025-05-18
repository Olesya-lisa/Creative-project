#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "form.h"
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //инициализируем второе окно
    sWindow= new Form();
    //подключаем к слоту запуска главного окна по кнопке во втором окне
    connect (sWindow, &Form::firstWindow, this, &MainWindow::show);
     //инициализируем второе окно
    //tWindow= new Form();
    //подключаем к слоту запуска главного окна по кнопке в третьем окне
    //connect (tWindow, &Form::firstWindow, this, &MainWindow::show);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    sWindow->show();//открывает окно с моделью
    this-> close();//закрывает первое окно
}

//функция для выхода из приложения
void MainWindow::on_pushButton_3_clicked()
{
    QMessageBox::StandardButton reply =QMessageBox::question(this,"Текст","Выйти из приложения?",
                                                              QMessageBox::Yes| QMessageBox::No);
    if (reply==QMessageBox::Yes)
    {
        QApplication::quit();//выход из приложения
    }
    else
    {
        qDebug()<<"Кнопка нет была нажата";
    }

}

