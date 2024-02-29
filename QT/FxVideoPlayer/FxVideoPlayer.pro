QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mediasession/FxDemuxThread.cpp \
    mediasession/FxFrameQueue.cpp \
    mediasession/FxPacketQueue.cpp \
    mediasession/FxPlayerSessionMgr.cpp \
    player/FxPlayerWidget.cpp \
    player/FxProgressBar.cpp

HEADERS += \
    IFxPlayerSessionMgr.h \
    mediasession/FxDemuxThread.h \
    mediasession/FxFrameQueue.h \
    mediasession/FxPacketQueue.h \
    mediasession/FxPlayerSessionMgr.h \
    mediasession/FxQueue.h \
    mediasession/IFxPlayerSessionMgr.h \
    player/FxPlayerWidget.h \
    player/FxProgressBar.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

contains(QT_ARCH, i386){        # 使用32位编译器
DESTDIR = $$PWD/../bin          # 程序输出路径
}else{
DESTDIR = $$PWD/../bin64        # 使用64位编译器
}
# msvc >= 2017  编译器使用utf-8编码
msvc {
    greaterThan(QMAKE_MSC_VER, 1900){       # msvc编译器版本大于2015
        QMAKE_CFLAGS += /utf-8
        QMAKE_CXXFLAGS += /utf-8
    }else{
        message(msvc2015及以下版本在代码中使用【pragma execution_character_set("utf-8")】指定编码)
    }
}

macx {
    FFMPEG_HOME = /opt/homebrew/Cellar/ffmpeg/6.1.1_3
    INCLUDEPATH += $$FFMPEG_HOME/include
    LIBS += -L$$FFMPEG_HOME/lib \
            -lavcodec \
            -lavdevice \
            -lavfilter \
            -lavformat \
            -lavutil \
            -lpostproc \
            -lswscale \
}

DISTFILES +=
