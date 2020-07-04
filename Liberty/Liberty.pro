QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

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
    model/autoelettrica.cpp \
    model/autoibrida.cpp \
    model/autotermica.cpp \
    model/model.cpp \
    model/rifornimento.cpp \
    model/veicolo.cpp \
    model/veicoloelettrico.cpp \
    model/veicolotermico.cpp \
    controller/controller.cpp \
    view/dettagliveicoliwidget.cpp \
    view/liberty.cpp \
    main.cpp \
    view/proprietalabel.cpp \
    view/rifornimentiveicolowidget.cpp \
    view/setrifornimentowidget.cpp \
    view/setveicolowidget.cpp \
    view/veicololistwidgetitem.cpp

HEADERS += \
    model/autoelettrica.h \
    model/autoibrida.h \
    model/autotermica.h \
    container.h \
    model/model.h \
    model/rifornimento.h \
    model/veicolo.h \
    model/veicoloelettrico.h \
    model/veicolotermico.h \
    controller/controller.h \
    view/dettagliveicoliwidget.h \
    view/liberty.h \
    view/proprietalabel.h \
    view/rifornimentiveicolowidget.h \
    view/setrifornimentowidget.h \
    view/setveicolowidget.h \
    view/veicololistwidgetitem.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
