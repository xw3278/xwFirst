#include "sectiondraw.h"

SectionDraw::SectionDraw(QQuickPaintedItem *parent) :
QQuickPaintedItem(parent)
, m_pDataFile(FP_ZERO)
, m_gridColor(Qt::darkBlue)
, m_lineColor(Qt::red)
, m_borderWidth(100)
, m_borderHeight(100)
, m_gridLineWidth(1)
, m_holdOffTimer(-1)
, m_lineWidth(1)
, m_drawGrid(false)
, m_drawBGround(false)
, m_drawTest(false)
, m_drawPierLine(false)
, m_drawTravelLine(false)
, m_drawDegree(false)
, m_drawAreaBoder(false)
, m_yInterVal(0)
, m_xInterval(0) {
    m_pDataFile = DataFile::instance();
    m_pScreenShot = new ScreenShot();
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::AllButtons);
    setFlag(ItemAcceptsInputMethod, true);

    connect(this, &SectionDraw::screenShot, m_pScreenShot, &ScreenShot::shotSlot);
    connect(this, &SectionDraw::clickPoint, this, &SectionDraw::tooltip);
}

SectionDraw::~SectionDraw() {
    if (m_pDataFile != FP_ZERO) {
        delete m_pDataFile;
        m_pDataFile = FP_ZERO;
    }
}

float SectionDraw::borderWidth() const {
    return m_borderWidth;
}
void SectionDraw::setBorderWidth(float w) {
    m_borderWidth = w;

    m_xInterval = (m_borderWidth - MARGIN_WIDTH*2)/177;
    if (m_lineWidth <= 0)
    {
       m_lineWidth=1;
    }
    m_bufferSize = m_xInterval>0?(m_borderWidth - MARGIN_WIDTH*2)/(m_lineWidth+m_xInterval)+1:(m_borderWidth - MARGIN_WIDTH*2)/(m_lineWidth+m_xInterval);

//    if (m_waveData.size() < m_bufferSize)
//    {
//       m_waveData.insert(0, m_bufferSize - m_waveData.size(), 0);
//    }
//    else if (m_waveData.size() > m_bufferSize)
//    {
//       m_waveData.remove(0, m_waveData.size()- m_bufferSize);
//    }
}

float SectionDraw::borderHeight() const {
    return m_borderHeight;
}

void SectionDraw::setBorderHeight(float h) {
    m_borderHeight = h;
    m_yInterVal = (m_borderHeight - MARGIN_WIDTH*2)/36;


}

void SectionDraw::drawTest(QPainter *painter) {
    if (painter == FP_ZERO) {
        return;
    }

    QFont font;
    font.setPixelSize(24);
    QString text="1234567";
    QFontMetrics metrics(font);
    int w=metrics.width(text);
    int h=metrics.height();
    painter->setFont(font);
    painter->setPen(Qt::blue);
    painter->drawText(QRect(width()/2 - w, height()/2 - h, w, h), text);
    painter->drawRect(QRect(width()/2 - w, height()/2 - h, w, h));
}

void SectionDraw::drawBorder(QPainter *painter) {
    if (painter == FP_ZERO) {
        return;
    }
    painter->drawLine(MARGIN_WIDTH, MARGIN_WIDTH, m_borderWidth - MARGIN_WIDTH, MARGIN_WIDTH);
    painter->drawLine(m_borderWidth - MARGIN_WIDTH, MARGIN_WIDTH, m_borderWidth - MARGIN_WIDTH, m_borderHeight - MARGIN_WIDTH);
    painter->drawLine(m_borderWidth - MARGIN_WIDTH, m_borderHeight - MARGIN_WIDTH, MARGIN_WIDTH, m_borderHeight - MARGIN_WIDTH);
    painter->drawLine(MARGIN_WIDTH, m_borderHeight - MARGIN_WIDTH, MARGIN_WIDTH, MARGIN_WIDTH);
}

void SectionDraw::drawBackgroundPNG(QPainter *painter) {
    if (painter == FP_ZERO) {
        return;
    }
    QPixmap pix;
    painter->translate(0, 0);
    pix.load(":/image/UI/image/background.PNG");
    painter->drawPixmap(MARGIN_WIDTH, MARGIN_WIDTH, static_cast<int>(width() - MARGIN_WIDTH*2), static_cast<int>(height() - MARGIN_WIDTH*2), pix);
}

void SectionDraw::drawBackgroundGrid(QPainter *painter, int row_num, int column_num) {
    if (painter == FP_ZERO) {
        return;
    }
    row_num = (row_num <= 0)? 1 : row_num;
    column_num = (column_num <= 0)? 1 : column_num;

    QPen p(m_gridColor, static_cast<qreal>(m_gridLineWidth));
    painter->setPen(p);
    double dx((m_borderWidth-MARGIN_WIDTH*2)/column_num);
    for (double x = MARGIN_WIDTH; x < m_borderWidth-MARGIN_WIDTH; x += dx ) {
      painter->drawLine(QPointF(x,MARGIN_WIDTH), QPointF(x, m_borderHeight-MARGIN_WIDTH));
    }
    painter->drawLine(QPointF( m_borderWidth-MARGIN_WIDTH, MARGIN_WIDTH ), QPointF(m_borderWidth-MARGIN_WIDTH, m_borderHeight-MARGIN_WIDTH));

    double dy((m_borderHeight-MARGIN_WIDTH*2)/row_num);
    for (double y = MARGIN_WIDTH; y < m_borderHeight-MARGIN_WIDTH; y += dy) {
      painter->drawLine(QPointF( MARGIN_WIDTH, y ), QPointF(m_borderWidth-MARGIN_WIDTH, y));
    }
    painter->drawLine(QPointF(MARGIN_WIDTH, m_borderHeight-MARGIN_WIDTH), QPointF(m_borderWidth-MARGIN_WIDTH, m_borderHeight-MARGIN_WIDTH));
}

void SectionDraw::drawPierCentralLine(QPainter *painter) {
    if (painter == FP_ZERO) {
        return;
    }
    QFont font;
    font.setPixelSize(12);
    painter->setFont(font);

    float fUnitWidth  = (m_borderWidth-MARGIN_WIDTH*2)/177; //bridge width is 177(m)
    //float fUnitHeight = (m_borderHeight-MARGIN_WIDTH*2)/36;
    float fHalfHeight = (m_borderHeight-MARGIN_WIDTH*2)/2;

    QPen penPierCenLine;
    penPierCenLine.setColor(Qt::blue);
    penPierCenLine.setWidth(2);
    penPierCenLine.setStyle(Qt::DotLine);
    painter->setPen(penPierCenLine);

    float fWidthAdd = 2; //(m)
    float fAddPara  = 32.8f; //(m)
    int iBegLinex = (fUnitWidth*fWidthAdd) + MARGIN_WIDTH; //update
    int iBegLiney = fHalfHeight;
    int iEndLinex = iBegLinex; //update
    int iEndLiney = 45 + MARGIN_WIDTH;

    int iEllipseX = iBegLinex - 12; //update
    int iEllipseY = 20 + MARGIN_WIDTH;
    int iEllipseW = 25;
    int iEllipseH = 25;

    int iTextX = iBegLinex - 3; //update
    int iTextY = 37 + MARGIN_WIDTH;
    QString qText = "0"; //update

    for (int iIndex = 0; iIndex < PIER_NUM; ++ iIndex) {
        if (0 == iIndex) {
            painter->drawLine(iBegLinex, iBegLiney, iEndLinex, iEndLiney);
            painter->drawEllipse(iEllipseX, iEllipseY, iEllipseW, iEllipseH);
            painter->drawText(iTextX, iTextY, qText);
        } else {
            fWidthAdd += fAddPara;
            iBegLinex = fUnitWidth*fWidthAdd + MARGIN_WIDTH;
            iEndLinex = iBegLinex;
            iEllipseX = iBegLinex - 12;
            iTextX = iBegLinex - 3;
            qText = QString("%1").arg(iIndex);

            painter->drawLine(iBegLinex, iBegLiney, iEndLinex, iEndLiney);
            painter->drawEllipse(iEllipseX, iEllipseY, iEllipseW, iEllipseH);
            painter->drawText(iTextX, iTextY, qText);
        }

    }

    /*int iWidthAdd = 640 + 10/2;
    int iAddPara  = 10 + 3260;
    int iBegLinex = (fUnitWidth*iWidthAdd)/100 + MARGIN_WIDTH; //update
    int iBegLiney = fHalfHeight;
    int iEndLinex = iBegLinex; //update
    int iEndLiney = 45 + MARGIN_WIDTH;

    int iEllipseX = iBegLinex - 15; //update
    int iEllipseY = 15 + MARGIN_WIDTH;
    int iEllipseW = 30;
    int iEllipseH = 30;

    int iTextX = iBegLinex - 5; //update
    int iTextY = 37 + MARGIN_WIDTH;
    QString qText = "0"; //update


    for (int iIndex = 0; iIndex < PIER_NUM; ++ iIndex) {
        if (0 == iIndex) {
            painter->drawLine(iBegLinex, iBegLiney, iEndLinex, iEndLiney);
            painter->drawEllipse(iEllipseX, iEllipseY, iEllipseW, iEllipseH);
            painter->drawText(iTextX, iTextY, qText);
        } else {
            iWidthAdd += iAddPara;
            iBegLinex = fUnitWidth*iWidthAdd/100 + MARGIN_WIDTH + 2; //ajustment(2)
            iEndLinex = iBegLinex;
            iEllipseX = iBegLinex - 15;
            iTextX = iBegLinex - 5;
            qText = QString("%1").arg(iIndex);

            painter->drawLine(iBegLinex, iBegLiney, iEndLinex, iEndLiney);
            painter->drawEllipse(iEllipseX, iEllipseY, iEllipseW, iEllipseH);
            painter->drawText(iTextX, iTextY, qText);
        }

    }*/
}

void SectionDraw::drawDegree(QPainter *painter) {
    if (painter == FP_ZERO) {
        return;
    }

    QFont font;
    font.setPixelSize(7);
    painter->setFont(font);

    QPen penDegreeLine;
    penDegreeLine.setColor(Qt::red);
    penDegreeLine.setWidth(2);
    penDegreeLine.setStyle(Qt::DotLine);
    painter->setPen(penDegreeLine);

    //width degree
    float fUnitWidth  = (m_borderWidth-MARGIN_WIDTH*2)/177; //bridge width is 177(m)

    int iWidthDegree = 0;
    for(int i = MARGIN_WIDTH; i < m_borderWidth-MARGIN_WIDTH; i += fUnitWidth) {
         painter->drawLine(i, m_borderHeight-MARGIN_WIDTH, i, m_borderHeight-MARGIN_WIDTH+6);
         if (iWidthDegree%2 == 0) {
            painter->drawText(i-2, m_borderHeight-MARGIN_WIDTH + 10, QString::number(iWidthDegree));
         }

         ++iWidthDegree;
    }

    //height degree
    float fUnitHeight  = (m_borderHeight-MARGIN_WIDTH*2)/36; //height is 36.186(m)

    int iNegFlag = -6; //Neg -6(m)
    int iHeightDegree = 0;
    for(int i = m_borderHeight-MARGIN_WIDTH; i > MARGIN_WIDTH; i -= fUnitHeight) {
         painter->drawLine(m_borderWidth-MARGIN_WIDTH, i, m_borderWidth-MARGIN_WIDTH+6, i);

         if (iNegFlag < 0) {
            painter->drawText(m_borderWidth-MARGIN_WIDTH + 10, i+2, QString::number(iNegFlag));
            iNegFlag = iNegFlag + 1;
         }else {
             painter->drawText(m_borderWidth-MARGIN_WIDTH + 10, i+2, QString::number(iHeightDegree));
             ++iHeightDegree;
         }
    }


}

void SectionDraw::drawTravelLine(QPainter *painter) {
    if (painter == FP_ZERO) {
        return;
    }

    if (m_waveData.size() > 2) {

        for (int i = 1; i < m_waveData.size(); ++i) {
            QPoint stFront = m_waveData.at(i-1);
            QPoint stBack = m_waveData.at(i);

            int iFrontX = stFront.x()*m_xInterval + MARGIN_WIDTH;
            int iFrontY = stFront.y()*m_yInterVal + MARGIN_WIDTH;

            int iBackX = stBack.x()*m_xInterval + MARGIN_WIDTH;
            int iBackY = stBack.y()*m_yInterVal + MARGIN_WIDTH;

            if (iFrontX < m_borderWidth-MARGIN_WIDTH && iFrontX > MARGIN_WIDTH) {
                if (iFrontY < m_borderHeight-MARGIN_WIDTH && iFrontY > MARGIN_WIDTH) {

                    if (iBackX < m_borderWidth-MARGIN_WIDTH && iBackX > MARGIN_WIDTH) {
                        if (iBackY < m_borderHeight-MARGIN_WIDTH && iBackY > MARGIN_WIDTH) {

                            QPen penFront;
                            penFront.setColor(Qt::blue);
                            penFront.setWidth(4);
                            painter->setPen(penFront);
                            painter->drawPoint(iFrontX, iFrontY);

                            QPen penLine;
                            penLine.setColor(Qt::red);
                            penLine.setWidth(1);
                            painter->setPen(penLine);
                            painter->drawLine(QPointF( iFrontX, iFrontY ), QPointF(iBackX, iBackY));

                            QPen penBack;
                            penBack.setColor(Qt::blue);
                            penBack.setWidth(4);
                            painter->setPen(penBack);
                            painter->drawPoint(iBackX, iBackY);
                        }
                    }
                }
            }


        }

    }

}

void SectionDraw::paint(QPainter *painter) {
    if (painter == FP_ZERO) {
        return;
    }

    painter->setRenderHint(QPainter::Antialiasing, true);

    if (m_drawBGround) {
        drawBackgroundPNG(painter);
    }

    if (m_drawAreaBoder) {
        drawBorder(painter);
    }

    if (m_drawGrid) {
        drawBackgroundGrid(painter, m_gridRowNum, m_gridColumnNum);
    }

    if (m_drawTest) {
        drawTest(painter);
    }

    if (m_drawPierLine) {
        drawPierCentralLine(painter);
    }

    if (m_drawDegree) {
        drawDegree(painter);
    }

    if (m_drawTravelLine) {
        drawTravelLine(painter);
    }

}

void SectionDraw::hoverMoveEvent(QHoverEvent* event) {

    //qDebug() << "hoverMoveEvent: " << event->pos();
    QQuickItem::hoverMoveEvent(event);
    QPoint oPaint = event->pos();
    if (oPaint.x() > MARGIN_WIDTH && oPaint.y() > MARGIN_WIDTH && oPaint.x() < (m_borderWidth - MARGIN_WIDTH) && oPaint.y() < (m_borderHeight - MARGIN_WIDTH) && isInWaveDatas(oPaint)) {
        QString qText = QString("longitude: %1; latitude: %2; depth: %3").arg(oPaint.x()).arg(oPaint.y()).arg(5);
        QToolTip::showText(QCursor::pos(), qText);
    }

    //if (isInWaveDatas(oPaint)) {
        //QString qText = QString("longitude: %1; latitude: %2; depth: %3").arg(oPaint.x()).arg(oPaint.y()).arg(5);
        //QToolTip::showText(QCursor::pos(), qText);
    //}

}

void SectionDraw::mousePressEvent(QMouseEvent *event) {
    QQuickItem::mousePressEvent(event);

    int iFrontX = event->pos().x();
    int iFrontY = event->pos().y();

    bool bInArea = false;

    for (int i = 0; i < m_waveData.size(); ++i)
    {
        int x = m_waveData.at(i).x()*m_xInterval + MARGIN_WIDTH;
        int y = m_waveData.at(i).y()*m_yInterVal + MARGIN_WIDTH;

        if (x-DELTA_VALUE < iFrontX  && iFrontX < x+DELTA_VALUE) {
            if (y-DELTA_VALUE < iFrontY && iFrontY < y+DELTA_VALUE) {

                bInArea = true;
                emit clickPoint("point informations : *****************************");
                break;
            }


        }
    }

    if (!bInArea) {
        emit clickPoint("");
    }

}

/// @brief then update the wave
void SectionDraw::timerEvent(QTimerEvent *event)
{
   // qDebug()<<"void SectionDraw::timerEvent(QTimerEvent *event)";
   if (event->timerId() != m_holdOffTimer)
   {
      return;
   }

   QVector<QString> vecMsg;
   if (m_pDataFile != FP_ZERO) {
       vecMsg = m_pDataFile->getUdpDataFromROV();
   }

   static int iAddx = 7;
   static int iAddy = 10;

   //temp test code
   if (m_waveData.size() < m_bufferSize) {
//       qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
//       int a = qrand()%9;
       QPoint addPoint(iAddx, iAddy);
       //stNodeInfo oNodeInfo;
       //oNodeInfo.ix
       m_waveData.push_back(addPoint);

       iAddx += 3;
       if (iAddy > 160) iAddy -= 1;
       if (iAddy < 30) iAddy += 1;
   }

   update();
}

int SectionDraw::updateTimer() const
{
   return m_updateInterval;
}

void SectionDraw::setUpdateTimer(int interval)
{
   m_updateInterval= interval;
   if (m_holdOffTimer != -1)
   {
      killTimer(m_holdOffTimer);
   }
   if(m_updateInterval == -1) return;
   m_holdOffTimer = startTimer(m_updateInterval);
}

/**
 * @brief used to get the interval bettwen x-axis point.
 */
int SectionDraw::xLineInterval() const
{
   return m_xInterval;
}

/**
 * @brief used to set the interval bettwen x-axis point.
 */
void SectionDraw::setXLineInterval(int interval)
{
   m_xInterval = interval < 0 ? 0 : interval; // m_xInterval will always be no less than zero
   m_bufferSize = m_xInterval > 0 ? (m_borderWidth - MARGIN_WIDTH*2) /(m_lineWidth + m_xInterval)+1 : (m_borderWidth - MARGIN_WIDTH*2)/(m_lineWidth + m_xInterval);
   /*if (m_waveData.size() < m_bufferSize)
   {
      m_waveData.insert(0, m_bufferSize - m_waveData.size(), 0);
   }
   else if (m_waveData.size() > m_bufferSize)
   {
      m_waveData.remove(0, m_waveData.size()- m_bufferSize);
   }*/
}

int SectionDraw::newData() const
{
   return m_newData;
}

void SectionDraw::setNewData(uint newdata)
{
   Q_UNUSED(newdata)
   //m_newData = (newdata>m_lineHeight)? m_lineHeight:newdata;
   if (m_bufferSize >= 1)
   {
      /*m_waveData.push_back(m_newData);
      m_waveData.pop_front();*/
   }
}

bool SectionDraw::isInWaveDatas(QPoint oPoint) {
    bool bIsExit = false;
    for (int i = 0; i < m_waveData.size(); ++i) {
        if (oPoint.x() == m_waveData.at(i).x() && oPoint.y() == m_waveData.at(i).y() ) {
            bIsExit = true;
            break;
        }
    }

    return bIsExit;
}
