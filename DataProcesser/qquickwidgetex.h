#ifndef QQUICKWIDGETEX_H
#define QQUICKWIDGETEX_H

#include <QQuickWidget>

class QQuickWidgetEx : public QQuickWidget
{
    Q_OBJECT
public:
    QQuickWidgetEx(QWidget* parent = NULL);
    bool setSource(const QUrl& qmlUrl);
};

#endif // QQUICKWIDGETEX_H
