#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QQmlEngine>
#include <QSize>
#include "sectiondraw.h"

static MainWindow* _instance = FP_ZERO;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_mainQmlWidget(nullptr)
{
    _instance = this;
    ui->setupUi(this);
    ui->statusbar->hide();

    initUI();
}

MainWindow* MainWindow::createObj()
{
    new MainWindow();
    return _instance;
}

MainWindow* MainWindow::instance(void)
{
    return _instance;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_mainQmlWidget;
    _instance = nullptr;
}

void MainWindow::initUI()
{
    QDesktopWidget* desktopWidget = QApplication::desktop();

    QRect deskRect = desktopWidget->availableGeometry();

    int g_nActScreenX = deskRect.width();
    int g_nActScreeny = deskRect.height();
    this->setGeometry(desktopWidget->screenGeometry(0));
    this->setGeometry(g_nActScreenX/2-550,g_nActScreeny/2-400,1100,600);
    QSize stSize(1100, 601);
    this->setMinimumSize(stSize);

    m_parentlayout = new QVBoxLayout();
    m_parentlayout->setContentsMargins(0, 0, 0, 0);
    centralWidget()->setLayout(m_parentlayout);

    m_mainQmlWidget = new QmlWidget(this);
    m_parentlayout->addWidget(m_mainQmlWidget);
    m_mainQmlWidget->setVisible(true);

    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
    m_mainQmlWidget->setSource(QUrl::fromUserInput("qrc:qml/UI/QMLMainArea.qml"));

    setWindowTitle(qApp->applicationName() + " " + qApp->applicationVersion());
    show();

}
