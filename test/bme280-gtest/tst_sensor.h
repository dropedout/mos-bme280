#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "bme280.h"

#include "tst_bme280_testfixture.h"

struct mgos_i2c;
using ::testing::_;
using ::testing::Ge;
using ::testing::NotNull;



class UnitTestBME280 : public BME280TestFixture {
public:
    static struct mgos_i2c* _i2c;
    BME280* _bme {NULL};
    UnitTestBME280(){

    }
    virtual void TearDown(){
        if (_bme!=NULL) {
            delete _bme;
            _bme = NULL;
        }
    }
    virtual void SetUp(){}
    ~UnitTestBME280(){}

};

TEST_F(UnitTestBME280, init){
    EXPECT_CALL(*_mgosI2c,mgos_i2c_get_freq(_i2c)).Times(1);
    EXPECT_CALL(*_mgosI2c,mgos_i2c_read_reg_w(_i2c,BME280_ADDRESS,BME280_REGISTER_CHIPID))\
            .Times(2)\
            .WillOnce(Return(0x61))\
            .WillOnce(Return(0x61));

    _bme = new BME280();

    EXPECT_FALSE(_bme->isInitialized());

}

TEST_F(UnitTestBME280, initReadReadAllFFDigitis)
{
    EXPECT_CALL(*_mgosI2c,mgos_i2c_read_reg_w(_i2c,BME280_ADDRESS,BME280_REGISTER_CHIPID))\
            .Times(1)\
            .WillOnce(Return(0x60));

    EXPECT_CALL(*_mgosI2c,mgos_i2c_read_reg_w(_i2c,BME280_ADDRESS,BME280_REGISTER_DIG_T1))\
            .Times(1)\
            .WillOnce(Return(0xffff));

    EXPECT_CALL(*_mgosI2c,mgos_i2c_read_reg_w(_i2c,BME280_ADDRESS,BME280_REGISTER_DIG_T2))\
            .Times(1)\
            .WillOnce(Return(0xffff));
    EXPECT_CALL(*_mgosI2c,mgos_i2c_read_reg_w(_i2c,BME280_ADDRESS,BME280_REGISTER_DIG_T3))\
            .Times(1)\
            .WillOnce(Return(0xffff));
    EXPECT_CALL(*_mgosI2c,mgos_i2c_read_reg_w(_i2c,BME280_ADDRESS,BME280_REGISTER_DIG_P1))\
            .Times(1)\
            .WillOnce(Return(0xffff));
    EXPECT_CALL(*_mgosI2c,mgos_i2c_read_reg_w(_i2c,BME280_ADDRESS,BME280_REGISTER_DIG_P2))\
            .Times(1)\
            .WillOnce(Return(0xffff));
    EXPECT_CALL(*_mgosI2c,mgos_i2c_read_reg_w(_i2c,BME280_ADDRESS,BME280_REGISTER_DIG_P3))\
            .Times(1)\
            .WillOnce(Return(0xffff));
    EXPECT_CALL(*_mgosI2c,mgos_i2c_read_reg_w(_i2c,BME280_ADDRESS,BME280_REGISTER_DIG_P4))\
            .Times(1)\
            .WillOnce(Return(0xffff));
    EXPECT_CALL(*_mgosI2c,mgos_i2c_read_reg_w(_i2c,BME280_ADDRESS,BME280_REGISTER_DIG_P5))\
            .Times(1)\
            .WillOnce(Return(0xffff));
    EXPECT_CALL(*_mgosI2c,mgos_i2c_read_reg_w(_i2c,BME280_ADDRESS,BME280_REGISTER_DIG_P6))\
            .Times(1)\
            .WillOnce(Return(0xffff));
    EXPECT_CALL(*_mgosI2c,mgos_i2c_read_reg_w(_i2c,BME280_ADDRESS,BME280_REGISTER_DIG_P7))\
            .Times(1)\
            .WillOnce(Return(0xffff));
    EXPECT_CALL(*_mgosI2c,mgos_i2c_read_reg_w(_i2c,BME280_ADDRESS,BME280_REGISTER_DIG_P8))\
            .Times(1)\
            .WillOnce(Return(0xffff));
    EXPECT_CALL(*_mgosI2c,mgos_i2c_read_reg_w(_i2c,BME280_ADDRESS,BME280_REGISTER_DIG_P9))\
            .Times(1)\
            .WillOnce(Return(0xffff));

    EXPECT_CALL(*_mgosI2c,mgos_i2c_read_reg_b(_i2c,BME280_ADDRESS,BME280_REGISTER_DIG_H1))\
            .Times(1)\
            .WillOnce(Return(0xff));
    EXPECT_CALL(*_mgosI2c,mgos_i2c_read_reg_w(_i2c,BME280_ADDRESS,BME280_REGISTER_DIG_H2))\
            .Times(1)\
            .WillOnce(Return(0xffff));
    EXPECT_CALL(*_mgosI2c,mgos_i2c_read_reg_b(_i2c,BME280_ADDRESS,BME280_REGISTER_DIG_H3))\
            .Times(1)\
            .WillOnce(Return(0xff));
    EXPECT_CALL(*_mgosI2c,mgos_i2c_read_reg_b(_i2c,BME280_ADDRESS,BME280_REGISTER_DIG_H4))\
            .Times(1)\
            .WillOnce(Return(0xff));
    EXPECT_CALL(*_mgosI2c,mgos_i2c_read_reg_w(_i2c,BME280_ADDRESS,BME280_REGISTER_DIG_H5))\
            .Times(2)\
            .WillRepeatedly(Return(0xffff));
    EXPECT_CALL(*_mgosI2c,mgos_i2c_read_reg_w(_i2c,BME280_ADDRESS,BME280_REGISTER_DIG_H5+1))\
            .Times(1)\
            .WillRepeatedly(Return(0xffff));
    EXPECT_CALL(*_mgosI2c,mgos_i2c_read_reg_b(_i2c,BME280_ADDRESS,BME280_REGISTER_DIG_H6))\
            .Times(1)\
            .WillOnce(Return(0xff));
    _bme = new BME280();

    EXPECT_TRUE(_bme->isInitialized());

    EXPECT_EQ(_bme->getCompensate().dig_H1,255);
    EXPECT_EQ(_bme->getCompensate().dig_H2,-1);
    EXPECT_EQ(_bme->getCompensate().dig_H3,255);
    EXPECT_EQ(_bme->getCompensate().dig_H4,4095);
    EXPECT_EQ(_bme->getCompensate().dig_H5,-1);
    EXPECT_EQ(_bme->getCompensate().dig_H6,-1);

    EXPECT_EQ(_bme->getCompensate().dig_T1,65535);
    EXPECT_EQ(_bme->getCompensate().dig_T2,-1);
    EXPECT_EQ(_bme->getCompensate().dig_T3,-1);

    EXPECT_EQ(_bme->getCompensate().dig_P1,65535);
    EXPECT_EQ(_bme->getCompensate().dig_P2,-1);
    EXPECT_EQ(_bme->getCompensate().dig_P3,-1);
    EXPECT_EQ(_bme->getCompensate().dig_P4,-1);
    EXPECT_EQ(_bme->getCompensate().dig_P5,-1);
    EXPECT_EQ(_bme->getCompensate().dig_P6,-1);
    EXPECT_EQ(_bme->getCompensate().dig_P7,-1);
    EXPECT_EQ(_bme->getCompensate().dig_P8,-1);
    EXPECT_EQ(_bme->getCompensate().dig_P9,-1);

}

TEST_F(UnitTestBME280, initReadAllZeroDigits)
{
    EXPECT_CALL(*_mgosI2c,mgos_i2c_read_reg_w(_i2c,BME280_ADDRESS,BME280_REGISTER_CHIPID))\
            .Times(1)\
            .WillOnce(Return(0x60));

    EXPECT_CALL(*_mgosI2c,mgos_i2c_read_reg_w(_i2c,BME280_ADDRESS,BME280_REGISTER_DIG_T1))\
            .Times(1)\
            .WillOnce(Return(0x00));

    EXPECT_CALL(*_mgosI2c,mgos_i2c_read_reg_w(_i2c,BME280_ADDRESS,BME280_REGISTER_DIG_T2))\
            .Times(1)\
            .WillOnce(Return(0x00));
    EXPECT_CALL(*_mgosI2c,mgos_i2c_read_reg_w(_i2c,BME280_ADDRESS,BME280_REGISTER_DIG_T3))\
            .Times(1)\
            .WillOnce(Return(0x00));
    EXPECT_CALL(*_mgosI2c,mgos_i2c_read_reg_w(_i2c,BME280_ADDRESS,BME280_REGISTER_DIG_P1))\
            .Times(1)\
            .WillOnce(Return(0x00));
    EXPECT_CALL(*_mgosI2c,mgos_i2c_read_reg_w(_i2c,BME280_ADDRESS,BME280_REGISTER_DIG_P2))\
            .Times(1)\
            .WillOnce(Return(0x00));
    EXPECT_CALL(*_mgosI2c,mgos_i2c_read_reg_w(_i2c,BME280_ADDRESS,BME280_REGISTER_DIG_P3))\
            .Times(1)\
            .WillOnce(Return(0x00));
    EXPECT_CALL(*_mgosI2c,mgos_i2c_read_reg_w(_i2c,BME280_ADDRESS,BME280_REGISTER_DIG_P4))\
            .Times(1)\
            .WillOnce(Return(0x00));
    EXPECT_CALL(*_mgosI2c,mgos_i2c_read_reg_w(_i2c,BME280_ADDRESS,BME280_REGISTER_DIG_P5))\
            .Times(1)\
            .WillOnce(Return(0x00));
    EXPECT_CALL(*_mgosI2c,mgos_i2c_read_reg_w(_i2c,BME280_ADDRESS,BME280_REGISTER_DIG_P6))\
            .Times(1)\
            .WillOnce(Return(0x00));
    EXPECT_CALL(*_mgosI2c,mgos_i2c_read_reg_w(_i2c,BME280_ADDRESS,BME280_REGISTER_DIG_P7))\
            .Times(1)\
            .WillOnce(Return(0x00));
    EXPECT_CALL(*_mgosI2c,mgos_i2c_read_reg_w(_i2c,BME280_ADDRESS,BME280_REGISTER_DIG_P8))\
            .Times(1)\
            .WillOnce(Return(0x00));
    EXPECT_CALL(*_mgosI2c,mgos_i2c_read_reg_w(_i2c,BME280_ADDRESS,BME280_REGISTER_DIG_P9))\
            .Times(1)\
            .WillOnce(Return(0x00));

    EXPECT_CALL(*_mgosI2c,mgos_i2c_read_reg_b(_i2c,BME280_ADDRESS,BME280_REGISTER_DIG_H1))\
            .Times(1)\
            .WillOnce(Return(0x00));
    EXPECT_CALL(*_mgosI2c,mgos_i2c_read_reg_w(_i2c,BME280_ADDRESS,BME280_REGISTER_DIG_H2))\
            .Times(1)\
            .WillOnce(Return(0x00));
    EXPECT_CALL(*_mgosI2c,mgos_i2c_read_reg_b(_i2c,BME280_ADDRESS,BME280_REGISTER_DIG_H3))\
            .Times(1)\
            .WillOnce(Return(0x00));
    EXPECT_CALL(*_mgosI2c,mgos_i2c_read_reg_b(_i2c,BME280_ADDRESS,BME280_REGISTER_DIG_H4))\
            .Times(1)\
            .WillOnce(Return(0x00));
    EXPECT_CALL(*_mgosI2c,mgos_i2c_read_reg_w(_i2c,BME280_ADDRESS,BME280_REGISTER_DIG_H5))\
            .Times(2)\
            .WillRepeatedly(Return(0x00));
    EXPECT_CALL(*_mgosI2c,mgos_i2c_read_reg_w(_i2c,BME280_ADDRESS,BME280_REGISTER_DIG_H5+1))\
            .Times(1)\
            .WillRepeatedly(Return(0x00));
    EXPECT_CALL(*_mgosI2c,mgos_i2c_read_reg_b(_i2c,BME280_ADDRESS,BME280_REGISTER_DIG_H6))\
            .Times(1)\
            .WillOnce(Return(0x00));
    _bme = new BME280();

    EXPECT_TRUE(_bme->isInitialized());

    EXPECT_EQ(_bme->getCompensate().dig_H1,0);
    EXPECT_EQ(_bme->getCompensate().dig_H2,0);
    EXPECT_EQ(_bme->getCompensate().dig_H3,0);
    EXPECT_EQ(_bme->getCompensate().dig_H4,0);
    EXPECT_EQ(_bme->getCompensate().dig_H5,0);
    EXPECT_EQ(_bme->getCompensate().dig_H6,0);

    EXPECT_EQ(_bme->getCompensate().dig_T1,0);
    EXPECT_EQ(_bme->getCompensate().dig_T2,0);
    EXPECT_EQ(_bme->getCompensate().dig_T3,0);

    EXPECT_EQ(_bme->getCompensate().dig_P1,0);
    EXPECT_EQ(_bme->getCompensate().dig_P2,0);
    EXPECT_EQ(_bme->getCompensate().dig_P3,0);
    EXPECT_EQ(_bme->getCompensate().dig_P4,0);
    EXPECT_EQ(_bme->getCompensate().dig_P5,0);
    EXPECT_EQ(_bme->getCompensate().dig_P6,0);
    EXPECT_EQ(_bme->getCompensate().dig_P7,0);
    EXPECT_EQ(_bme->getCompensate().dig_P8,0);
    EXPECT_EQ(_bme->getCompensate().dig_P9,0);
}

TEST_F(UnitTestBME280, readTemperatureAdc)
{
    ON_CALL(*_mgosI2c,mgos_i2c_read_reg_w(_i2c,BME280_ADDRESS,Ge(BME280_REGISTER_CHIPID)))\
            .WillByDefault(Return(0x60));
    ON_CALL(*_mgosI2c,mgos_i2c_read_reg_w(_i2c,BME280_ADDRESS,Ge(BME280_REGISTER_STATUS)))\
            .WillByDefault(Return(0x00));
    _bme = new BME280();


    EXPECT_CALL(*_mgosI2c,mgos_i2c_write_reg_b(_i2c,BME280_ADDRESS,BME280_REGISTER_CONTROL,(5<<5)|(5<<2)|3))\
                .Times(1)\
                .WillOnce(Return(true));

    _bme->triggerMeasurement();

    EXPECT_CALL(*_mgosI2c,mgos_i2c_read_reg_n(_i2c,BME280_ADDRESS,BME280_REGISTER_PRESSUREDATA,8,NotNull()))\
                .Times(1)\
                .WillOnce(Return(0x0000));


    EXPECT_EQ(_bme->getTemperature(),0);
}

TEST_F(UnitTestBME280, readTemperatureAdcNonZero)
{
    ON_CALL(*_mgosI2c,mgos_i2c_read_reg_w(_i2c,BME280_ADDRESS,Ge(BME280_REGISTER_CHIPID)))\
            .WillByDefault(Return(0x60));
    ON_CALL(*_mgosI2c,mgos_i2c_read_reg_w(_i2c,BME280_ADDRESS,Ge(BME280_REGISTER_STATUS)))\
            .WillByDefault(Return(0x00));
    uint8_t buffer[8] {0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55};
    _bme = new BME280();

    EXPECT_CALL(*_mgosI2c,mgos_i2c_write_reg_b(_i2c,BME280_ADDRESS,BME280_REGISTER_CONTROL,_))\
                .Times(1)\
                .WillOnce(Return(true));

    EXPECT_CALL(*_mgosI2c,mgos_i2c_read_reg_n(_i2c,BME280_ADDRESS,\
                           BME280_REGISTER_PRESSUREDATA,8,_))\
            .Times(1)\
            .WillOnce(DoAll(SetArrayArgument<4>(buffer,buffer+7+1),Return(true)));

    _bme->triggerMeasurement();

//    EXPECT_CALL(*_mgosI2c,mgos_i2c_read_reg_n(_i2c,BME280_ADDRESS,BME280_REGISTER_PRESSUREDATA,8,NotNull()))\
//                .Times(1)\
//                .WillOnce(Return(true));


    EXPECT_EQ(_bme->getTemperature(),0);
}

struct mgos_i2c{
    uint32_t dummy;
};

struct mgos_i2c gI2c;
struct mgos_i2c* gI2C;

struct mgos_i2c* UnitTestBME280::_i2c = gI2C;
