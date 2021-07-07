#include "qquickwidgetex.h"

#include <QQmlContext>
#include <QQmlEngine>

QQuickWidgetEx::QQuickWidgetEx(QWidget* parent) :
    QQuickWidget(parent)
{
    rootContext()->engine()->addImportPath("qrc:/qml");
}

bool QQuickWidgetEx::setSource(const QUrl& qmlUrl)
{
    QQuickWidget::setSource(qmlUrl);
    if (status() != Ready) {
        QString errorList;

        foreach (QQmlError error, errors()) {
            errorList += error.toString();
            errorList += "\n";
        }
        return false;
    }

    return true;
}
