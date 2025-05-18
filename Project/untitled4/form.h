#ifndef FORM_H
#define FORM_H
#include <QWidget>
#include <Qt3DCore/QEntity>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DRender/QCamera>
#include <QWidget>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

signals:
    void firstWindow();

private slots:
    void on_pushButton_clicked();//сигнал от кнопки

private:
    Ui::Form *ui;
    Qt3DExtras::Qt3DWindow *view;
    QWidget *container;
    Qt3DCore::QEntity *rootEntity;
    void setup3DScene();
};

#endif // FORM_H
