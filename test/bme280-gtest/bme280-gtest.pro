include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

HEADERS +=     tst_sensor.h \
    mgos.h \
    mgos_debug.h \
    mgos_i2c.h \
    mgos_mock.h \
    mgos_mock.h \
    mgos_i2c_mock.h \
    mgos_hal.h \
    mgos_hal_mock.h \
    tst_bme280_testfixture.h \
    tst_rawvalues.h

SOURCES +=     main.cpp \
    mgos_mock.cpp \
    mgos_i2c_mock.cpp \
    mgos_hal_mock.cpp


# source under test
SOURCES += $$PWD/../../src/bme280.cpp
HEADERS += $$PWD/../../src/bme280.h

INCLUDEPATH += $$PWD \
    $$PWD/../../src

# mocks

