RC_FILE = abe.rc
RESOURCES = icons.qrc
contains(QT_CONFIG, opengl): QT += opengl
QT += 
QT += network
INCLUDEPATH += /c/PFM_ABEv7.0.0_Win64/include
LIBS += -L /c/PFM_ABEv7.0.0_Win64/lib -lpfm -lnvutility -lgdal -lxml2 -lpoppler -liconv -lwsock32
DEFINES += XML_LIBRARY WIN32 NVWIN3X
CONFIG += console

#
# The following line is included so that the contents of acknowledgments.hpp will be available for translation
#

HEADERS += /c/PFM_ABEv7.0.0_Win64/include/acknowledgments.hpp

QMAKE_LFLAGS += 
######################################################################
# Automatically generated by qmake (2.01a) Wed Jan 22 13:49:51 2020
######################################################################

TEMPLATE = app
TARGET = abe
DEPENDPATH += .
INCLUDEPATH += .

# Input
HEADERS += abe.hpp abeDef.hpp abeHelp.hpp dndButton.hpp release.hpp version.hpp
SOURCES += abe.cpp dndButton.cpp env_in_out.cpp main.cpp set_defaults.cpp
RESOURCES += icons.qrc
TRANSLATIONS += abe_xx.ts
