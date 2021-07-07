#ifndef SECTIONDRAW_H
#define SECTIONDRAW_H

#include <QObject>
#include <QQuickPaintedItem>
#include <QFontMetrics>
#include <QPainter>
#include <QImage>
#include <QtGlobal>
#include <QTimerEvent>
#include <QToolTip>
#include <QCursor>
#include <QVector>
#include <QPoint>
#include <QTime>
#include <QtGlobal>

#include <QtCharts>

#include "datafile.h"
#include "screenshot.h"

#define PIER_NUM 6
#define MARGIN_WIDTH 30
#define DELTA_VALUE 3

class SectionDraw : public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(float  borderWidth READ borderWidth WRITE setBorderWidth)
    Q_PROPERTY(float  borderHeight READ borderHeight WRITE setBorderHeight)
    Q_PROPERTY(float  lineWidth READ lineWidth WRITE setLineWidth)
    Q_PROPERTY(float  gridLineWidth READ gridLineWidth WRITE setGridLineWidth)
    Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor)
    Q_PROPERTY(QColor gridColor READ gridColor WRITE setGridColor)
    Q_PROPERTY(int    gridColumnNum READ gridColumnNum WRITE setGridColumnNum)
    Q_PROPERTY(int    gridRowNum READ gridRowNum WRITE setGridRowNum )
    Q_PROPERTY(bool   drawGrid READ drawGrid WRITE setDrawGrid)
    Q_PROPERTY(bool   drawBGround READ drawBGround WRITE setDrawBGround)
    Q_PROPERTY(bool   drawTest READ drawTest WRITE setDrawTest)
    Q_PROPERTY(bool   drawPierLine READ drawPierLine WRITE setDrawPierLine)
    Q_PROPERTY(bool   drawTravelLine READ drawTravelLine WRITE setDrawTravelLine)
    Q_PROPERTY(bool   drawDegree READ drawDegree WRITE setDrawDegree)
    Q_PROPERTY(bool   drawAreaBoder READ drawAreaBoder WRITE setDrawAreaBoder)
    Q_PROPERTY(int    updateTimer READ updateTimer WRITE setUpdateTimer)
    ///used to get/set the interval bettwen x-axis point.
    Q_PROPERTY(int    xLineInterval READ xLineInterval WRITE setXLineInterval)
    Q_PROPERTY(int    newData READ newData WRITE setNewData)
public:
    explicit SectionDraw(QQuickPaintedItem *parent = FP_ZERO);
    ~SectionDraw();

    float   borderWidth() const;
    void    setBorderWidth(float w);

    float   borderHeight() const;
    void    setBorderHeight(float h);

    float   lineWidth() const { return m_lineWidth; }
    void    setLineWidth(float w) { m_lineWidth = w; }

    float   gridLineWidth() const { return m_gridLineWidth; }
    void    setGridLineWidth(const float w) { m_gridLineWidth = w; }

    QColor  gridColor() const { return m_gridColor; }
    void    setGridColor(const QColor &grid_color) { m_gridColor = grid_color; }

    QColor  lineColor() const { return m_lineColor; }
    void    setLineColor(const QColor &color) { m_lineColor = color; }

    int     gridRowNum() const { return m_gridRowNum; }
    void    setGridRowNum(int num) { m_gridRowNum = num; }

    int     gridColumnNum() const { return m_gridColumnNum; }
    void    setGridColumnNum(int num) { m_gridColumnNum = num; }

    bool    drawGrid() const { return m_drawGrid; }
    void    setDrawGrid(bool draw) { m_drawGrid = draw; }

    bool    drawBGround() const { return m_drawBGround; }
    void    setDrawBGround(bool draw) { m_drawBGround = draw; }

    bool    drawTest() const { return m_drawTest; }
    void    setDrawTest(bool draw) { m_drawTest = draw; }

    bool    drawPierLine() const { return m_drawPierLine; }
    void    setDrawPierLine(bool draw) { m_drawPierLine = draw; }

    bool    drawTravelLine() const { return m_drawTravelLine; }
    void    setDrawTravelLine(bool draw) { m_drawTravelLine = draw; }

    bool    drawDegree() const { return m_drawDegree; }
    void    setDrawDegree(bool draw) { m_drawDegree = draw; }

    bool    drawAreaBoder() const { return m_drawAreaBoder; }
    void    setDrawAreaBoder(bool draw) { m_drawAreaBoder = draw; }

    int     updateTimer() const;
    void    setUpdateTimer(int interval);

    int     xLineInterval() const;
    void    setXLineInterval(int interval);

    int     newData() const;
    void    setNewData( uint data);

protected:
    void    mousePressEvent(QMouseEvent *event);
    void    hoverMoveEvent(QHoverEvent* event);
    void    timerEvent(QTimerEvent *event);
    void    paint(QPainter *painter);
    void    drawTest(QPainter *painter);
    void    drawBorder(QPainter *painter);
    void    drawBackgroundPNG(QPainter *painter);
    void    drawBackgroundGrid(QPainter *painter, int row_num, int column_num);
    void    drawPierCentralLine(QPainter *painter);
    void    drawDegree(QPainter *painter);
    void    drawTravelLine(QPainter *painter);

private:
    bool    isInWaveDatas(QPoint oPoint);
signals:
    void    clickPoint(QString point);
    void    tooltip(QString point);
    void    screenShot();
//public slots:

private:
    QImage    m_backGroundImage;
    DataFile* m_pDataFile;

    float     m_borderWidth;
    float     m_borderHeight;

    float     m_lineWidth;
    float     m_gridLineWidth;

    QColor    m_lineColor;
    QColor    m_gridColor;

    int       m_gridColumnNum;
    int       m_gridRowNum;

    bool      m_drawGrid;
    bool      m_drawBGround;
    bool      m_drawTest;
    bool      m_drawPierLine;
    bool      m_drawTravelLine;
    bool      m_drawDegree;
    bool      m_drawAreaBoder;

    int       m_bufferSize;

    /// wave's updating frequence.
    int       m_updateInterval;
    /// save the current timer id ,in timer event used to judge if the specified timer event come.
    int       m_holdOffTimer;

    /// interval bettwen x-axis point.
    int       m_xInterval;
    int       m_yInterVal;

    ///used to receive the newest wave data.
    uint      m_newData;

    QVector<QPoint> m_waveData;

    ScreenShot* m_pScreenShot;
};

#endif // SECTIONDRAW_H
