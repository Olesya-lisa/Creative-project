#include "form.h"
#include "ui_form.h"
#include <QGuiApplication>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DRender/QSceneLoader>
#include <QPushButton>
#include <QVBoxLayout>
#include <Qt3DRender/QCameraLens>
#include <Qt3DRender/QCamera>
#include <Qt3DExtras/QTorusMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DCore/QTransform>
#include <Qt3DCore/QEntity>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <Qt3DRender/QClearBuffers>
#include <Qt3DRender/QDirectionalLight>
#include <Qt3DRender/QTexture>
#include <Qt3DExtras/QDiffuseSpecularMaterial>
#include <Qt3DRender/QRenderSettings>

Form::Form(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Form)
{
    ui->setupUi(this);
    // Создаем контейнер для 3D окна
    view = new Qt3DExtras::Qt3DWindow();
    container = QWidget::createWindowContainer(view);
    container->setMinimumSize(600, 400);//размер

    // Настройка 3D сцены
    rootEntity = new Qt3DCore::QEntity();
    setup3DScene();
    // Компоновка
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(container);
}
void Form::setup3DScene()
{
    //основное окно
    //Qt3DExtras::Qt3DWindow view;

    //главная функция-родитель
    Qt3DCore::QEntity*rootEntity= new Qt3DCore::QEntity();

    // Источник света (направленный)
    Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(rootEntity);
    Qt3DRender::QDirectionalLight *light = new Qt3DRender::QDirectionalLight(lightEntity);
    light->setColor(Qt::white);
    light->setIntensity(1.5);
    lightEntity->addComponent(light);

    // Трансформация света
    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
    lightTransform->setRotation(QQuaternion::fromEulerAngles(-30, 20, 0));
    lightEntity->addComponent(lightTransform);


    //Добавление 3D модели
    Qt3DCore::QEntity*objectEntity=new Qt3DCore::QEntity(rootEntity);//родитель
    Qt3DRender::QSceneLoader*sceneLoader=new Qt3DRender::QSceneLoader(objectEntity);
    sceneLoader->setSource(QUrl("qrc:/obj/Brooo.obj"));
    //sceneLoader->setSource(QUrl("qrc:/obj/brain122.obj"));
    //sceneLoader->setSource(QUrl("qrc:/obj/Brain45.obj"));
    //sceneLoader->setSource(QUrl::fromLocalFile("path/to/your/Brain43.fbx"));
    //sceneLoader->setSource(QUrl::fromLocalFile("Brain44.gltf"));
    objectEntity->addComponent(sceneLoader);

    Qt3DCore::QTransform*objectTransform=new Qt3DCore::QTransform(objectEntity);
    objectTransform->setScale(12.0f);//масштаб
    objectEntity->addComponent(objectTransform);

    //Камера-влияет на проекцию объекта
    Qt3DRender::QCamera *camera=view->camera();//возвращает указатель на камеру
    camera->lens()->setPerspectiveProjection(60.0f,(float)view->width()/view->height(),0.1f,1000.0f);//угол обзора, ширина на высоту, дальняя и ближняя плоскости
    camera->setPosition(QVector3D(0.0f,0.0f,40.0f));//позиция по векторам
    camera->setViewCenter(QVector3D(0.0f,0.0f,0.0f));//вращение камеры

    //Камера-контроллер позволяет крутить объект
    Qt3DExtras::QOrbitCameraController *cameraController=new Qt3DExtras::QOrbitCameraController(rootEntity);
    cameraController->setCamera(camera);
    cameraController->setLookSpeed(180.0f);
    cameraController->setLinearSpeed(50.0f);

    // Анимация масштабирования (пульсация)
    QPropertyAnimation *scaleAnim = new QPropertyAnimation(objectTransform);
    scaleAnim->setTargetObject(objectTransform);
    scaleAnim->setPropertyName("scale");
    scaleAnim->setStartValue(13.0f);
    scaleAnim->setEndValue(10.5f);//увеличение в 10.5 раз
    scaleAnim->setDuration(2000);//2 секунды
    scaleAnim->setLoopCount(-1);//бесконечная анимация
    scaleAnim->setEasingCurve(QEasingCurve::InOutSine);
    scaleAnim->start();

    //Устанавливаем кореную сущность в окно
    view->setRootEntity(rootEntity);
    //view.show();
    //return app.exec();
}
Form::~Form()
{
    //delete ui;
    delete view;
}

void Form::on_pushButton_clicked()
{
    this->close();//закрываем окно
    emit firstWindow();
}

