#ifndef TST_BME280_TESTFIXTURE_H
#define TST_BME280_TESTFIXTURE_H

#include "mgos_hal_mock.h"
#include "mgos_i2c_mock.h"

class BME280TestFixture: public Test{
public:
    BME280TestFixture(){
        _mgosI2c.reset(new ::testing::NiceMock<MgosI2cMock>());
        _mgosHal.reset(new ::testing::NiceMock<MgosHalMock>());
    }
    ~BME280TestFixture(){
        _mgosI2c.reset();
        _mgosHal.reset();
    }
    virtual void SetUp(){}
    virtual void TearDown(){}

    // pointer for accessing mocked library
    static std::unique_ptr<MgosI2cMock> _mgosI2c;
    static std::unique_ptr<MgosHalMock> _mgosHal;
};

#endif // TST_BME280_TESTFIXTURE_H
