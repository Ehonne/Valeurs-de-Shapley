QT       += core gui
QT += printsupport


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Sources/joueur.cpp \
    Sources/loadwindow.cpp \
    Sources/main.cpp \
    Sources/mainwindow.cpp \
    Sources/qplayerwindow.cpp \
    Sources/resultat.cpp \
    Sources/shapley.cpp \
    Sources/shapleyapprox.cpp \
    Sources/simple.cpp \
    Sources/tplayerwindow.cpp

HEADERS += \
    Headers/joueur.h \
    Headers/loadwindow.h \
    Headers/mainwindow.h \
    Headers/qplayerwindow.h \
    Headers/tplayerwindow.h \
    Headers/loadwindow.h \
    Headers/resultat.h

FORMS += \
    Forms/loadwindow.ui \
    Forms/mainwindow.ui \
    Forms/qplayerwindow.ui \
    Forms/tplayerwindow.ui \
    Forms/loadwindow.ui \
    Forms/resultat.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
   Ressources/Alice.qrc \
    Ressources/BossEnderDragon.qrc
