#ifndef MGOS_I2C_MOCK_H
#define MGOS_I2C_MOCK_H

// MOCKING C-Functions with GMOCK :)
#include <memory>
#include <cinttypes>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

struct mgos_i2c;

using namespace ::testing;
using ::testing::Return;

class MgosI2cMock {
public:
    virtual ~MgosI2cMock(){}

    MOCK_METHOD1(mgos_i2c_get_freq,int(mgos_i2c*));
    // mock methods
    MOCK_METHOD3(mgos_i2c_read_reg_b,int(mgos_i2c*,uint16_t,uint8_t));
    MOCK_METHOD3(mgos_i2c_read_reg_w,int(mgos_i2c*,uint16_t,uint8_t));
    MOCK_METHOD5(mgos_i2c_read_reg_n,bool(mgos_i2c*,uint16_t,uint8_t,size_t,uint8_t*));

    MOCK_METHOD4(mgos_i2c_write_reg_b,bool(mgos_i2c*,uint16_t,uint8_t,uint8_t));
    MOCK_METHOD4(mgos_i2c_write_reg_w,bool(mgos_i2c*,uint16_t,uint8_t,uint16_t));
    MOCK_METHOD5(mgos_i2c_write_reg_n,bool(mgos_i2c*,uint16_t,uint8_t,size_t,uint8_t*));
};

#endif // MGOS_I2C_MOCK_H
