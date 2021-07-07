QT       += core \
            gui \
            qml \
            quick \
            quickwidgets \
            network \
            charts \

TARGET = DataProcesser

TEMPLATE = app

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 \
          thread \
          qt \

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    datafile.cpp \
    main.cpp \
    mainwindow.cpp \
    qmlwidget.cpp \
    screenshot.cpp \
    sectiondraw.cpp \

HEADERS += \
    datafile.h \
    mainwindow.h \
    qmlwidget.h \
    screenshot.h \
    sectiondraw.h \

FORMS += \
    mainwindow.ui \
    qmlwidget.ui \
    screenshot.ui \

OTHER_FILES += \
    UI/MainPage.qml \
    UI/QMLMainArea.qml \
    UI/WaveViewer.qml \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    DPResources.qrc
