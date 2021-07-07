#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include <QWidget>
#include <QRubberBand>
#include <QImage>
#include <QLabel>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QDesktopServices>
#include <QScreen>
#include <QKeyEvent>
#include <QDir>
#include <QDateTime>
#include <QPushButton>
#include <QClipboard>
#include <QPalette>
#include <QPoint>

namespace Ui {
class ScreenShot;
}

class ScreenShot : public QWidget
{
    Q_OBJECT
public:
    ~ScreenShot();
    explicit ScreenShot();
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void keyPressEvent(QKeyEvent *e);

    void setBackground(int w,int h, double n);
    void setLabel(int w,int h,int x,int y);
    void setButton(int w,int h,int x,int y);
    void setRubber();
    void pSize();

private:
    Ui::ScreenShot *ui;
    QRubberBand *m_rubber;
    QPoint m_startPt;///mouse start position
    QPoint m_endPt;  ///mouse end position
    QImage m_imageBg;///store current desktop shot screen
    QLabel* m_sizeLabel;///show screen size
    QPushButton* m_shotButton;
    int m_screenWidth;///screen width
    int m_screenHeight;///screen height
    int m_pw,m_ph,m_px,m_py;
    bool m_shot; ///judge rebuild rubber
    bool m_quit; ///select right button event

public slots:
    void shot(double n);
    void grabScreen();
    void shotSlot();
};

#endif // SCREENSHOT_H
