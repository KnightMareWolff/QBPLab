#-------------------------------------------------
#
# Project created by QtCreator 2018-04-11T17:20:15
#
#-------------------------------------------------

QT       += core gui concurrent charts datavisualization 3dcore 3drender 3dinput 3dlogic 3dextras 3danimation

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QBPLab
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#Define copia do executavel no diretorio /bin
DESTDIR = $$PWD/../QBPLab/bin

SOURCES += \
    LibLUA/lapi.c \
    LibLUA/lauxlib.c \
    LibLUA/lbaselib.c \
    LibLUA/lbitlib.c \
    LibLUA/lcode.c \
    LibLUA/lcorolib.c \
    LibLUA/lctype.c \
    LibLUA/ldblib.c \
    LibLUA/ldebug.c \
    LibLUA/ldo.c \
    LibLUA/ldump.c \
    LibLUA/lfunc.c \
    LibLUA/lgc.c \
    LibLUA/linit.c \
    LibLUA/liolib.c \
    LibLUA/llex.c \
    LibLUA/lmathlib.c \
    LibLUA/lmem.c \
    LibLUA/loadlib.c \
    LibLUA/lobject.c \
    LibLUA/lopcodes.c \
    LibLUA/loslib.c \
    LibLUA/lparser.c \
    LibLUA/lstate.c \
    LibLUA/lstring.c \
    LibLUA/lstrlib.c \
    LibLUA/ltable.c \
    LibLUA/ltablib.c \
    LibLUA/ltm.c \
    LibLUA/lundump.c \
    LibLUA/lvm.c \
    LibLUA/lzio.c \
    LibToLUA/tolua_event.c \
    LibToLUA/tolua_is.c \
    LibToLUA/tolua_map.c \
    LibToLUA/tolua_push.c \
    LibToLUA/tolua_to.c \
    QBP_AttitudeMask.cpp \
    QBP_Categorizer.cpp \
    QBP_Chord.cpp \
    QBP_ClassifierPool.cpp \
    QBP_ClassifierSVM.cpp \
    QBP_Clusterizer.cpp \
    QBP_MainWindow.cpp \
    QBP_PriorityQueue.cpp \
    QBP_SWDebugInfo.cpp \
    QBP_ScriptObjects.cpp \
    QBP_TabPageCode.cpp \
    QBP_TabPageDataset.cpp \
    QBP_Main.cpp \
    MIDI/QBP_Binasc.cpp \
    MIDI/QBP_MidiEvent.cpp \
    MIDI/QBP_MidiEventList.cpp \
    MIDI/QBP_MidiFile.cpp \
    MIDI/QBP_MidiMessage.cpp \
    QBP_Classifier.cpp \
    QBP_Comparator.cpp \
    QBP_Mask.cpp \
    QBP_MussumMask.cpp \
    QBP_Matrix.cpp \
    QBP_MatrixValue.cpp \
    QBP_Note.cpp \
    QBP_Song.cpp \
    QBP_Feature.cpp \
    QBP_FeatureType.cpp \
    QBP_Keyboard.cpp \
    QBP_MidiDevice.cpp \
    QBP_TabPagePlayer.cpp \
    QBP_TabPageSVM.cpp \
    QBP_TabPageMusicSearch.cpp \
    QBP_Dataset.cpp \
    QBP_Genre.cpp \
    QBP_JSymbolicFile.cpp \
    QBP_Engine.cpp \
    QBP_LogQueue.cpp \
    QBP_ToolsTab.cpp \
    QBP_VisualizationTab.cpp \
    QBP_TabPageCharts.cpp \
    QBP_TabPage3DCharts.cpp \
    QBP_MussixMask.cpp \
    QBP_TabPageSWDebug.cpp \
    QBP_SWDebugGraph.cpp \
    QBP_SWDebugNode.cpp \
    QBP_SWDebugEdge.cpp \
    QBP_SWDebugGrid.cpp \
    QBP_SWDebugNotes.cpp \
    QBP_SWDebugDialog.cpp \
    QBP_SWDebugMask.cpp \
    QBP_SearchResults.cpp \
    QBP_Search.cpp \
    QBP_SWDebugPartiture.cpp \
    QBP_SWDebugSong.cpp \
    QBP_Alignment.cpp

HEADERS += \
    LibLUA/lapi.h \
    LibLUA/lauxlib.h \
    LibLUA/lcode.h \
    LibLUA/lctype.h \
    LibLUA/ldebug.h \
    LibLUA/ldo.h \
    LibLUA/lfunc.h \
    LibLUA/lgc.h \
    LibLUA/llex.h \
    LibLUA/llimits.h \
    LibLUA/lmem.h \
    LibLUA/lobject.h \
    LibLUA/lopcodes.h \
    LibLUA/lparser.h \
    LibLUA/lstate.h \
    LibLUA/lstring.h \
    LibLUA/ltable.h \
    LibLUA/ltm.h \
    LibLUA/lua.h \
    LibLUA/lua.hpp \
    LibLUA/luaconf.h \
    LibLUA/lualib.h \
    LibLUA/lundump.h \
    LibLUA/lvm.h \
    LibLUA/lzio.h \
    LibToLUA/tolua.h \
    LibToLUA/tolua_event.h \
    QBP_AttitudeMask.h \
    QBP_Categorizer.h \
    QBP_Chord.h \
    QBP_ClassifierPool.h \
    QBP_ClassifierSVM.h \
    QBP_Clusterizer.h \
    QBP_MainWindow.h \
    QBP_PriorityQueue.h \
    QBP_SWDebugInfo.h \
    QBP_ScriptObjects.h \
    QBP_ScriptObjectsBind.h \
    QBP_TabPageCode.h \
    QBP_TabPageDataset.h \
    MIDI/QBP_Binasc.h \
    MIDI/QBP_MidiEvent.h \
    MIDI/QBP_MidiEventList.h \
    MIDI/QBP_MidiFile.h \
    MIDI/QBP_MidiMessage.h \
    QBP_Classifier.h \
    QBP_Comparator.h \
    QBP_Mask.h \
    QBP_MussumMask.h \
    QBP_Matrix.h \
    QBP_MatrixValue.h \
    QBP_Note.h \
    QBP_Song.h \
    QBP_Feature.h \
    QBP_FeatureType.h \
    QBP_Keyboard.h \
    QBP_MidiDevice.h \
    QBP_TabPagePlayer.h \
    QBP_TabPageSVM.h \
    QBP_TabPageMusicSearch.h \
    QBP_Dataset.h \
    QBP_Genre.h \
    QBP_JSymbolicFile.h \
    QBP_GlobalDef.h \
    QBP_Engine.h \
    QBP_LogQueue.h \
    QBP_ToolsTab.h \
    QBP_VisualizationTab.h \
    QBP_TabPageCharts.h \
    QBP_TabPage3DCharts.h \
    QBP_MussixMask.h \
    QBP_TabPageSWDebug.h \
    QBP_SWDebugGraph.h \
    QBP_SWDebugNode.h \
    QBP_SWDebugEdge.h \
    QBP_SWDebugGrid.h \
    QBP_SWDebugNotes.h \
    QBP_SWDebugDialog.h \
    QBP_SWDebugMask.h \
    QBP_SearchResults.h \
    QBP_Search.h \
    QBP_SWDebugPartiture.h \
    QBP_SWDebugSong.h \
    QBP_Alignment.h

LIBS += -lwinmm

#QMAKE_CXXFLAGS += -Wl,--stack,1000000000000
#QMAKE_CXXFLAGS += -Wl,--heap,1000000000000

#OpenCV 4.1.0
#win32: LIBS += -L$$PWD/LibOCV/410/x64/mingw/lib/ -llibopencv_core410.dll
#win32: LIBS += -L$$PWD/LibOCV/410/x64/mingw/lib/ -llibopencv_highgui410.dll
#win32: LIBS += -L$$PWD/LibOCV/410/x64/mingw/lib/ -llibopencv_imgcodecs410.dll
#win32: LIBS += -L$$PWD/LibOCV/410/x64/mingw/lib/ -llibopencv_videoio410.dll
#win32: LIBS += -L$$PWD/LibOCV/410/x64/mingw/lib/ -llibopencv_video410.dll
#win32: LIBS += -L$$PWD/LibOCV/410/x64/mingw/lib/ -llibopencv_imgproc410.dll
#win32: LIBS += -L$$PWD/LibOCV/410/x64/mingw/lib/ -llibopencv_ml410.dll

#INCLUDEPATH += $$PWD/LibOCV/410/include
#DEPENDPATH += $$PWD/LibOCV/410/include

#OpenCV 4.5.1
win32: LIBS += -L$$PWD/LibOCV/451/x64/mingw/lib/ -llibopencv_world451.dll

INCLUDEPATH += $$PWD/LibOCV/451/include
DEPENDPATH += $$PWD/LibOCV/451/include


RC_ICONS = qbpicon.ico

DISTFILES += \
    bin/automation/ExampleScript.txt





