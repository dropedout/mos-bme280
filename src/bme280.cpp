/*
 * Copyright (c) 2014-2016 Cesanta Software Limited
 * All rights reserved
 */

/*
*
*
*
*/
#include "bme280.h"

BME280::BME280():
    _initDone(false){

    if (0x60 == mgos_i2c_read_reg_w(gI2C,BME280_ADDRESS,BME280_REGISTER_CHIPID))
    {
        // load calibration data...
        _comp.dig_T1  = mgos_i2c_read_reg_w(gI2C,BME280_ADDRESS,BME280_REGISTER_DIG_T1);
        _comp.dig_T2  = mgos_i2c_read_reg_w(gI2C,BME280_ADDRESS,BME280_REGISTER_DIG_T2);
        _comp.dig_T3  = mgos_i2c_read_reg_w(gI2C,BME280_ADDRESS,BME280_REGISTER_DIG_T3);

        _comp.dig_P1  = mgos_i2c_read_reg_w(gI2C,BME280_ADDRESS,BME280_REGISTER_DIG_P1);
        _comp.dig_P2  = mgos_i2c_read_reg_w(gI2C,BME280_ADDRESS,BME280_REGISTER_DIG_P2);
        _comp.dig_P3  = mgos_i2c_read_reg_w(gI2C,BME280_ADDRESS,BME280_REGISTER_DIG_P3);
        _comp.dig_P4  = mgos_i2c_read_reg_w(gI2C,BME280_ADDRESS,BME280_REGISTER_DIG_P4);
        _comp.dig_P5  = mgos_i2c_read_reg_w(gI2C,BME280_ADDRESS,BME280_REGISTER_DIG_P5);
        _comp.dig_P6  = mgos_i2c_read_reg_w(gI2C,BME280_ADDRESS,BME280_REGISTER_DIG_P6);
        _comp.dig_P7  = mgos_i2c_read_reg_w(gI2C,BME280_ADDRESS,BME280_REGISTER_DIG_P7);
        _comp.dig_P8  = mgos_i2c_read_reg_w(gI2C,BME280_ADDRESS,BME280_REGISTER_DIG_P8);
        _comp.dig_P9  = mgos_i2c_read_reg_w(gI2C,BME280_ADDRESS,BME280_REGISTER_DIG_P9);

        _comp.dig_H1  = mgos_i2c_read_reg_b(gI2C,BME280_ADDRESS,BME280_REGISTER_DIG_H1);
        _comp.dig_H2  = mgos_i2c_read_reg_w(gI2C,BME280_ADDRESS,BME280_REGISTER_DIG_H2);
        _comp.dig_H3  = mgos_i2c_read_reg_b(gI2C,BME280_ADDRESS,BME280_REGISTER_DIG_H3);

        _comp.dig_H4  = mgos_i2c_read_reg_b(gI2C,BME280_ADDRESS,BME280_REGISTER_DIG_H4) << 4;		// 11:4
        _comp.dig_H4 |= mgos_i2c_read_reg_w(gI2C,BME280_ADDRESS,BME280_REGISTER_DIG_H5) & 0x0f;	// 3:0

        _comp.dig_H5  = mgos_i2c_read_reg_w(gI2C,BME280_ADDRESS,BME280_REGISTER_DIG_H5) >> 4;		// 3:0
        _comp.dig_H5 |= mgos_i2c_read_reg_w(gI2C,BME280_ADDRESS,BME280_REGISTER_DIG_H5+1) << 4;		// 11:4

        _comp.dig_H6  = mgos_i2c_read_reg_b(gI2C,BME280_ADDRESS,BME280_REGISTER_DIG_H6);

        LOG(LOG_INFO,("t1: %d, t2: %d, t3: %d \n",\
                      _comp.dig_T1,_comp.dig_T2,_comp.dig_T3));
        LOG(LOG_INFO,("p1: %d,p2: %d,p3: %d,p4: %d,p5: %d\n",\
                      _comp.dig_P1,_comp.dig_P9,_comp.dig_P2,_comp.dig_P3,_comp.dig_P4,_comp.dig_P5));
        LOG(LOG_INFO,("p6: %d,p7: %d,p8: %d,p9: %d,\n",_comp.dig_P6,_comp.dig_P7,_comp.dig_P8,_comp.dig_P9));
        LOG(LOG_INFO,("h1: %d,h2: %d,h3: %d,h4: %d,h5: %d,h6: %d\n",\
                      _comp.dig_H1,_comp.dig_H2,_comp.dig_H3,_comp.dig_H4,_comp.dig_H5,_comp.dig_H6));
        _initDone = true;
    }
    else
    {
        LOG(LL_ERROR, ("Wrong Chip Id : %x",mgos_i2c_read_reg_w(gI2C,BME280_ADDRESS,BME280_REGISTER_CHIPID)));
    }
    LOG(LL_INFO, ("Frequenz i2c: %d",  mgos_i2c_get_freq(gI2C)));

}

double BME280::getTemperature()
{
    if (readBurstBME280())
        return compensate_T_double();
    return 0.0;
}

bool BME280::triggerMeasurement()
{
    if (_initDone) {
        _controlMeasurement = mgos_i2c_read_reg_b(gI2C,BME280_ADDRESS,BME280_REGISTER_CONTROL);
        LOG(LL_INFO,("control register before: %x",_controlMeasurement.get()));
        _controlMeasurement.print();
        _controlMeasurement.osrs_p = BME280_OVERSAMPLING_16;
        _controlMeasurement.osrs_t = BME280_OVERSAMPLING_16;
        _controlMeasurement.mode = BME280_MODE_NORMAL;
        _controlMeasurement.print();
        return mgos_i2c_write_reg_b(gI2C,BME280_ADDRESS,BME280_REGISTER_CONTROL,_controlMeasurement.get());
    }
    else
        return false;
}


bool BME280::readBurstBME280()
{
    uint8_t buffer[8] {0};
    uint8_t ret = false;

    ret = mgos_i2c_read_reg_b(gI2C,BME280_ADDRESS,BME280_REGISTER_STATUS);
    LOG(LL_INFO,("status: %d",ret));
    if (BME280_STATUS_MEASURING != (BME280_STATUS_MEASURING & ret))
    {
        mgos_i2c_read_reg_n(gI2C,BME280_ADDRESS,\
                               BME280_REGISTER_PRESSUREDATA,8,buffer);
        LOG(LOG_DEBUG,("%x %x %x",buffer[0],buffer[2],buffer[7]));
        _rawPres = &buffer[0];
        _rawTemp = &buffer[3];
        _rawHum = ((uint16_t)(buffer[6]<<8)|buffer[7]);
    }
    else
        LOG(LL_ERROR,("bme is busy"));

    return (ret==0?true:false);
}

// Returns temperature in DegC, double precision. Output value of “51.23” equals 51.23 DegC.
// t_fine carries fine temperature as global value
double BME280::compensate_T_double()
{
    double var1, var2, T;
    LOG(LOG_DEBUG,(__PRETTY_FUNCTION__));_rawTemp.print();

    int32_t adc_T = _rawTemp.get();
    var1 = (((((double)adc_T)/16384.0) - ((double)_comp.dig_T1/1024.0)) * ((double)_comp.dig_T2));

    var2 = ((((double)adc_T)/131072.0 - ((double)_comp.dig_T1)/8192.0)\
            - (((double)adc_T)/131072.0 - ((double)_comp.dig_T1)/8192.0))\
            * ((double)_comp.dig_T3);
    _fine = (int32_t)(var1 + var2);
    T = (var1 + var2) / 5120.0;
    return T;
}
// Returns pressure in Pa as double. Output value of “96386.2” equals 96386.2 Pa = 963.862 hPa
double BME280::compensate_P_double()
{
    double var1, var2, p;
    int32_t adc_P = _rawPres.get();
    var1 = ((double)_fine/2.0) - 64000.0;
    var2 = var1 * var1 * ((double)_comp.dig_P6) / 32768.0;
    var2 = var2 + var1 * ((double)_comp.dig_P5) * 2.0;
    var2 = (var2/4.0)+(((double)_comp.dig_P4) * 65536.0);
    var1 = (((double)_comp.dig_P3) * var1 * var1 / 524288.0 + ((double)_comp.dig_P2) * var1) / 524288.0;
    var1 = (1.0 + var1 / 32768.0)*((double)_comp.dig_P1);
    if (var1 == 0.0)
    {
        return 0; // avoid exception caused by division by zero
    }
    p = 1048576.0 - (double)adc_P;
    p = (p - (var2 / 4096.0)) * 6250.0 / var1;
    var1 = ((double)_comp.dig_P9) * p * p / 2147483648.0;
    var2 = p * ((double)_comp.dig_P8) / 32768.0;
    p = p + (var1 + var2 + ((double)_comp.dig_P7)) / 16.0;
    return p;
}
// Returns humidity in %rH as as double. Output value of “46.332” represents 46.332 %rH
double BME280::compensate_H_double()
{
    double var_H;
    int32_t adc_H = _rawHum;
    var_H = (((double)_fine) - 76800.0);
    var_H = (adc_H - (((double)_comp.dig_H4) * 64.0 + ((double)_comp.dig_H5) / 16384.0 * var_H)) *
            (((double)_comp.dig_H2) / 65536.0 * (1.0 + ((double)_comp.dig_H6) / 67108864.0 * var_H *
                                           (1.0 + ((double)_comp.dig_H3) / 67108864.0 * var_H)));
    var_H = var_H * (1.0 - ((double)_comp.dig_H1) * var_H / 524288.0);
    if (var_H > 100.0)
        var_H = 100.0;
    else if (var_H < 0.0)
        var_H = 0.0;
    return var_H;
}
