QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
<<<<<<< Updated upstream
    dinode.cpp \
    disk.cpp \
    diskblock.cpp \
=======
    instruction.cpp \
>>>>>>> Stashed changes
    main.cpp \
    mainwindow.cpp \
    minode.cpp \
    sfd.cpp \
    superblock.cpp \
    user.cpp

HEADERS += \
    configure.h \
<<<<<<< Updated upstream
    dinode.h \
    disk.h \
    diskblock.h \
    mainwindow.h \
    minode.h \
    sfd.h \
    superblock.h \
    user.h
=======
    file-struct.h \
    instruction.h \
    mainwindow.h
>>>>>>> Stashed changes

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
