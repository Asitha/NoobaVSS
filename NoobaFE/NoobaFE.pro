######################################################################
# Automatically generated by qmake (2.01a) Tue Apr 2 00:20:58 2013
######################################################################

TEMPLATE = app

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG(debug, debug|release): message(FE Debug build!)
CONFIG(release, debug|release): message(FE Release build!)

CONFIG(debug, debug|release): TARGET = NoobaVSS_Debug
CONFIG(release, debug|release): TARGET = NoobaVSS

CONFIG(debug, debug|release): DESTDIR = ../../NoobaVSS_build/NoobaFE/Debug/
CONFIG(release, debug|release): DESTDIR = ../../NoobaVSS_build/NoobaFE/Release/

# creates visual studio files
#win32:TEMPLATE = vcapp

RESOURCES += Resources/mainwind.qrc
# sets the application icon for windows
RC_FILE = Resources/nooba_logo.rc

# Input
HEADERS += \
           MainWindow.h \
           NoobaEye.h \
           PluginLoader.h \
           PluginsConfigUI.h \
    NoobaPlugin.h \
    OutputWind.h \
    ParamConfigWind.h \
    ParamDelegate.h \
    pluginconndelegate.h \
    FrameViewer.h \
    Structures.h \
    SharedImageBuffer.h \
    Config.h \
    CaptureThread.h \
    Buffer.h \
    CameraView.h \
    ProcessingThread.h \
    MatToQImage.h \
    StatPanel.h \
    PathLineEdit.h \
    FrameLabel.h

FORMS += Forms/MainWindow.ui Forms/PluginsConfigUI.ui \
    Forms/OutputWind.ui \
    Forms/ParamConfigWind.ui \
    Forms/FrameViewer.ui \
    Forms/CameraView.ui \
    Forms/StatPanel.ui \
    Forms/PathLineEdit.ui

SOURCES += \
           main.cpp \
           MainWindow.cpp \
           PluginLoader.cpp \
           PluginsConfigUI.cpp \
    NoobaPlugin.cpp \
    OutputWind.cpp \
    ParamConfigWind.cpp \
    ParamDelegate.cpp \
    pluginconndelegate.cpp \
    FrameViewer.cpp \
    SharedImageBuffer.cpp \
    CaptureThread.cpp \
    CameraView.cpp \
    ProcessingThread.cpp \
    MatToQImage.cpp \
    StatPanel.cpp \
    PathLineEdit.cpp \
    FrameLabel.cpp

unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += opencv
}

win32:CONFIG(release, debug|release){
    # need to put win32 opencv lib paths
    INCLUDEPATH += $$OUT_PWD/../../OpenCV244/release/include
    LIBS += -L$$OUT_PWD/../../OpenCV244/release/lib \
    -lopencv_core244.dll \
    -lopencv_highgui244.dll \
    -lopencv_imgproc244.dll \
    -lopencv_features2d244.dll \
    -lopencv_calib3d244.dll
}

win32:CONFIG(debug, debug|release){
    # need to put win32 opencv lib paths
    INCLUDEPATH += $$OUT_PWD/../../OpenCV244/debug/include
    LIBS += -L$$OUT_PWD/../../OpenCV244/debug/lib \
    -lopencv_core244.dll \
    -lopencv_highgui244.dll \
    -lopencv_imgproc244.dll

}

CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../NoobaVSS_build/NoobaPluginAPI/Debug/ -lNoobaPluginAPId
CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../NoobaVSS_build/NoobaPluginAPI/Release/ -lNoobaPluginAPI

INCLUDEPATH += $$PWD/../NoobaPluginAPI
DEPENDPATH += $$PWD/../NoobaPluginAPI
