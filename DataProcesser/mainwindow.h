#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>

#include <qmlwidget.h>
#include <QDesktopWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    static MainWindow* createObj();
    static MainWindow* instance(void);
    ~MainWindow();

private:
    MainWindow(QWidget *parent = nullptr);
    void initUI();
private:
    Ui::MainWindow          *ui;
    QVBoxLayout             *m_parentlayout;
    QmlWidget               *m_mainQmlWidget;
};
#endif // MAINWINDOW_H
