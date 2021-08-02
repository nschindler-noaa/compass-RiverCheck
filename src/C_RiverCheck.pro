#-------------------------------------------------
#
# Project created by QtCreator 2012-12-12T14:25:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets charts printsupport

TARGET = C_RiverCheck
TEMPLATE = app


SOURCES += main.cpp\
    errordialog.cpp \
    logdialog.cpp \
        mainwindow.cpp \
    RiverSystem.cpp \
    RiverSegment.cpp \
    RiverPoint.cpp \
    Reach.cpp \
    Headwater.cpp \
    Dam.cpp \
    Stock.cpp \
    Species.cpp \
    PowerHouse.cpp \
    RSW.cpp \
    RiverFile.cpp \
    RiverSite.cpp \
    Log.cpp \
    River.cpp \
    detaildialog.cpp \
    matrix.cpp \
    mapTransform.cpp \
    mapScene.cpp \
    mapReach.cpp \
    mapPoint.cpp \
    mapLocalTransform.cpp \
    mapItem.cpp \
    mapHeadwater.cpp \
    mapDam.cpp \
    mapSite.cpp \
    infowidget.cpp \
    mapinfowidget.cpp \
    qstringlisteditdialog.cpp \
    qstringlisteditwidget.cpp \
    damdetaildialog.cpp \
    mapobject.cpp \
    segmenterrors.cpp \
    segmentinfo.cpp \
    reachdetaildialog.cpp \
    seeview.cpp \
    segmentViews.cpp \
    metadata.cpp \
    Period.cpp \
    Basin.cpp \
    Transport.cpp \
    widgetlog.cpp

HEADERS  += mainwindow.h \
    Stock.h \
    Species.h \
    RiverSystem.h \
    RiverSegment.h \
    RiverPoint.h \
    Reach.h \
    Headwater.h \
    Dam.h \
    PowerHouse.h \
    definitions.h \
    RSW.h \
    RiverFile.h \
    RiverSite.h \
    Log.h \
    River.h \
    detaildialog.h \
    errordialog.h \
    logdialog.h \
    mercatorTransform.h \
    matrix.h \
    mapTransform.h \
    mapScene.h \
    mapReach.h \
    mapPoint.h \
    mapLocalTransform.h \
    mapHeadwater.h \
    mapDam.h \
    mapConstants.h \
    mapSite.h \
    infowidget.h \
    mapinfowidget.h \
    qstringlisteditdialog.h \
    qstringlisteditwidget.h \
    damdetaildialog.h \
    mapobject.h \
    segmenterrors.h \
    segmentinfo.h \
    reachdetaildialog.h \
    mapItem.h \
    seeview.h \
    segmentViews.h \
    metadata.h \
    Period.h \
    Basin.h \
    Transport.h \
    widgetlog.h

FORMS    += mainwindow.ui \
    detaildialog.ui \
    errordialog.ui \
    logdialog.ui \
    reachDetailDialog.ui \
    damDetailDialog.ui \
    qstringlisteditdialog.ui \
    qstringlisteditwidget.ui \
    segmentinfo.ui \
    widgetlog.ui

OTHER_FILES += \
    readme.txt

DISTFILES += \
    ../readme.txt

RESOURCES += \
    rivCheck.qrc
