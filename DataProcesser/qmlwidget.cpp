#include "qmlwidget.h"
#include "ui_qmlwidget.h"

QmlWidget::QmlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QmlWidget)
{
    ui->setupUi(this);

    layout()->setContentsMargins(0, 0, 0, 0);
    ui->quickWidget->rootContext()->engine()->addImportPath("qrc:/qml/UI");

    setResizeMode(QQuickWidget::SizeRootObjectToView);
}

QmlWidget::~QmlWidget()
{
    delete ui;
}

void QmlWidget::setSource(const QUrl& qmlUrl)
{
    return ui->quickWidget->setSource(qmlUrl);
}

void QmlWidget::setContextPropertyObject(const QString& name, QObject* object)
{
    ui->quickWidget->rootContext()->setContextProperty(name, object);
}

QQmlContext* QmlWidget::getRootContext(void)
{
    return ui->quickWidget->rootContext();
}

QQuickItem* QmlWidget::getRootObject(void)
{
    return ui->quickWidget->rootObject();
}

QQmlEngine*	QmlWidget::getEngine()
{
    return ui->quickWidget->engine();
}

void QmlWidget::setResizeMode(QQuickWidget::ResizeMode resizeMode)
{
    ui->quickWidget->setResizeMode(resizeMode);
}
