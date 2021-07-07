#ifndef QMLWIDGET_H
#define QMLWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QQmlContext>
#include <QQuickWidget>
#include <QQuickItem>
#include <QQmlEngine>


namespace Ui {
class QmlWidget;
}

class QmlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QmlWidget(QWidget *parent = nullptr);
    ~QmlWidget();

    QQmlContext* getRootContext(void);
    QQuickItem*  getRootObject(void);
    QQmlEngine*	 getEngine();
    void setSource(const QUrl& qmlUrl);
    void setContextPropertyObject(const QString& name, QObject* object);
    void setResizeMode(QQuickWidget::ResizeMode resizeMode);
private:
    Ui::QmlWidget *ui;
};

#endif // QMLWIDGET_H
