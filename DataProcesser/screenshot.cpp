#include "screenshot.h"
#include "ui_screenshot.h"
#include <QMessageBox>
#include <QThread>

#include <QDebug>

ScreenShot::ScreenShot() {
    ui->setupUi(this);
}

ScreenShot::~ScreenShot() {
    delete ui;
}

void ScreenShot::pSize() { //get screenshot point
    m_pw = abs(m_endPt.x()-m_startPt.x());
    m_ph = abs(m_endPt.y()-m_startPt.y());
    m_px = m_startPt.x()<m_endPt.x()?m_startPt.x():m_endPt.x();
    m_py = m_startPt.y()<m_endPt.y()?m_startPt.y():m_endPt.y();
}

void ScreenShot::setRubber() { //set screenshot rect
    m_rubber = new  QRubberBand(QRubberBand::Rectangle,this);
    m_rubber->show();

    m_rubber->setGeometry(m_startPt.x(),m_startPt.y(),0,0);
}

void ScreenShot::keyPressEvent(QKeyEvent *e) {
    if(e->key()==Qt::Key_Escape) {
        this->hide();
    }
}

void ScreenShot::mousePressEvent(QMouseEvent *e) {
    m_startPt = e->pos();
    if(e->button() == Qt::LeftButton) {
        if(m_shot==true) {
            setRubber();
            m_shot = false;
        }
        else {
            m_rubber->close();
            m_sizeLabel->close();
            m_shotButton->close();
            setRubber();
        }
        m_quit = false;
    }

}

void ScreenShot::mouseMoveEvent(QMouseEvent *e) {
    if(e->buttons() & Qt::LeftButton) {
        m_endPt = e->pos();
        pSize();
        m_rubber->setGeometry(m_px,m_py,m_pw,m_ph);
        setLabel(m_pw,m_ph,m_px,m_py);
        setButton(m_pw,m_ph,m_px,m_py);
    }
}

void ScreenShot::mouseReleaseEvent(QMouseEvent *e) {
    if(e->button()==Qt::LeftButton) {
    }
    else if(e->button()==Qt::RightButton) {
        if(m_quit == false) {
            m_shot = true;
            m_rubber->close();
            m_sizeLabel->close();
            m_shotButton->close();
            m_quit = true;
        }
        else {
           this->hide();
        }
    }
}

void ScreenShot::grabScreen() {
    QImage pic = m_imageBg.copy(m_px,m_py,m_pw,m_ph);
    QDir dir("C:/bak");
    if(!dir.exists()) {
       bool ok = dir.mkdir("C:/bak");
       if (!ok) {
           return;
       }
    }
    QString path = "C:/bak/"+QDateTime::currentDateTime().toString("yymmddhhmmss")+".jpg";
    qDebug() << path;
    pic.save(path);
    QDesktopServices::openUrl(QUrl(path));
    QClipboard *b = QApplication::clipboard();
    b->setImage(pic);
    m_shotButton->close();
    m_sizeLabel->close();
    m_rubber->close();
    this->hide();
}

void ScreenShot::setBackground(int w, int h, double n) { //set current screen
    QScreen *screen = QGuiApplication::primaryScreen();

    int r,g,b;
    m_imageBg = screen->grabWindow(0).toImage();
    QImage bg_grey(w,h,QImage::Format_RGB32);
    for(int i=0;i<w;i++) {
        for(int j=0;j<h;j++) {
            r = qRed(m_imageBg.pixel(i,j))*n;
            g = qGreen(m_imageBg.pixel(i,j))*n;
            b = qBlue(m_imageBg.pixel(i,j))*n;
            bg_grey.setPixel(i,j,qRgb(r,g,b));
        }
    }
    QPalette palette;
    palette.setBrush(this->backgroundRole(), QBrush(bg_grey));
    this->setPalette(palette);
    this->showFullScreen();
}

void ScreenShot::setLabel(int w,int h,int x,int y) { //set label info for size
    QString size = QString("%1  x %2                                  ").arg(w).arg(h);
    m_sizeLabel->setText(size);
    QRect rect(m_sizeLabel->contentsRect());
    if(y>rect.height())
        m_sizeLabel->move(QPoint(x,y-rect.height()));
    else
        m_sizeLabel->move(QPoint(x,y));
    m_sizeLabel->show();
}

void ScreenShot::setButton(int w,int h,int x,int y) {
    QRect rect(m_shotButton->contentsRect());
    if(m_screenHeight-y-h>rect.height())
        m_shotButton->move(QPoint(x+w-rect.width(),y+h));
    else
        m_shotButton->move(QPoint(x+w-rect.width(),y+h-rect.height()));
    m_shotButton->show();
}

void ScreenShot::shot(double n) {
    QDesktopWidget *desktop = QApplication::desktop();
    QRect deskRect = desktop->screenGeometry();
    m_screenWidth = deskRect.width();
    m_screenHeight = deskRect.height();
    this->setMouseTracking(true);
    this->resize(m_screenWidth, m_screenHeight);
    this ->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    m_shot = true;
    m_quit = true;
    setBackground(m_screenWidth, m_screenHeight, n);
    m_rubber =  FP_ZERO;
    m_startPt = m_endPt = QPoint(0,0);
    m_sizeLabel = new QLabel("");

    m_shotButton = new QPushButton("Done");
    m_sizeLabel->setAttribute(Qt::WA_TranslucentBackground);
    m_shotButton->setAttribute(Qt::WA_TranslucentBackground);

    QPalette pal;
    pal.setColor(QPalette::WindowText,Qt::white);
    m_sizeLabel->setPalette(pal);
    m_shotButton->setPalette(pal);
    m_sizeLabel->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    m_shotButton->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);

    connect(m_shotButton, SIGNAL(clicked()), this, SLOT(grabScreen()));
    this->show();
}

void ScreenShot::shotSlot() {
    QThread::msleep(100);
    shot(0.7);
}

