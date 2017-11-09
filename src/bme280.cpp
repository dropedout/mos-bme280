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

    if (0x60 == mgos_i2c_read_reg_b(gI2C,BME280_ADDRESS,BME280_REGISTER_CHIPID))
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


        LOG(LL_INFO,("t1: %d, t2: %d, t3: %d \n",\
                      _comp.dig_T1,_comp.dig_T2,_comp.dig_T3));
        LOG(LL_INFO,("p1: %d,p2: %d,p3: %d,p4: %d\n",\
                      _comp.dig_P1,_comp.dig_P2,_comp.dig_P3,_comp.dig_P4));
       	LOG(LL_INFO,("p5: %d,",_comp.dig_P5));
        LOG(LL_INFO,("p6: %d,p7: %d,p8: %d,p9: %d\n",_comp.dig_P6,_comp.dig_P7,_comp.dig_P8,_comp.dig_P9));
        
        LOG(LL_INFO,("h1: %d,h2: %d,h3: %d,h4: %d\n",\
                      _comp.dig_H1,_comp.dig_H2,_comp.dig_H3,_comp.dig_H4));

				LOG(LL_INFO,("h5: %d,h6: %d",_comp.dig_H5,_comp.dig_H6));
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

double BME280::getHumidity()
{
    if (readBurstBME280())
        return compensate_H_double();
    return 0.0;
}
bool BME280::triggerMeasurement()
{
    if (_initDone) {
        _controlMeasurement = mgos_i2c_read_reg_b(gI2C,BME280_ADDRESS,BME280_REGISTER_CONTROL);
        //_controlHumiditiy = mgos_i2c_read_reg_b(gI2C,BME280_ADDRESS,BME280_REGISTER_CONTROLHUMID);
        
        LOG(LL_INFO,("control register before: %d",_controlMeasurement.get()));
        LOG(LL_INFO,("control humidty register before: %d",_controlHumiditiy.get()));
        _controlMeasurement.osrs_p = BME280_OVERSAMPLING_16;
        _controlMeasurement.osrs_t = BME280_OVERSAMPLING_16;
        _controlMeasurement.mode = BME280_MODE_FORCED;
        
        _controlHumiditiy.osrs_h = BME280_OVERSAMPLING_16;
        mgos_i2c_write_reg_b(gI2C,BME280_ADDRESS,BME280_REGISTER_CONTROL,_controlMeasurement.get());
        mgos_i2c_write_reg_b(gI2C,BME280_ADDRESS,BME280_REGISTER_CONTROLHUMID,_controlHumiditiy.get());
    }
    else
        return false;
    return true;
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
        LOG(LL_DEBUG,("%x %x %x %x %x %x %x %x",buffer[0],buffer[1],buffer[2],buffer[3],buffer[4],buffer[5],buffer[6],buffer[7]));
        _rawPres = &buffer[0];
        _rawTemp = &buffer[3];
        _rawHum = ((uint16_t)(buffer[6]<<8)|buffer[7]);
        
        LOG(LL_DEBUG,("rawPres: %x",_rawPres.get()));
        LOG(LL_DEBUG,("rawTemp: %x",_rawTemp.get()));
        LOG(LL_DEBUG,("rawPres: %x",_rawHum));
    }
    else {
        LOG(LL_ERROR,("bme is busy"));
        return false;
        }

    return true;
}

// Returns temperature in DegC, double precision. Output value of “51.23” equals 51.23 DegC.
// t_fine carries fine temperature as global value
double BME280::compensate_T_double()
{
    double var1, var2, T;
    int32_t adc_T = _rawTemp.get();
    
    LOG(LL_DEBUG,("%s: rawTemp: %d",__PRETTY_FUNCTION__,adc_T));
    var1 = (((((double)adc_T)/16384.0) - ((double)_comp.dig_T1/1024.0)) * ((double)_comp.dig_T2));

    var2 = ((((double)adc_T)/131072.0 - ((double)_comp.dig_T1)/8192.0)\
            - (((double)adc_T)/131072.0 - ((double)_comp.dig_T1)/8192.0))\
            * ((double)_comp.dig_T3);
    _fine = (int32_t)(var1 + var2);
    T = (var1 + var2) / 5120.0;
    LOG(LL_DEBUG,("%s: compTemp: %f",__PRETTY_FUNCTION__,T));
    LOG(LL_DEBUG,("%s: fine: %d, var1: %f, var2: %f",__PRETTY_FUNCTION__,_fine,var1,var2));
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
    LOG(LL_DEBUG,("%s: rawHum: %d, _fine: %f",__PRETTY_FUNCTION__,adc_H,(double)_fine));
    var_H = (((double)_fine) - 76800.0);
    var_H = (adc_H - (((double)_comp.dig_H4) * 64.0 + ((double)_comp.dig_H5) / 16384.0 * var_H)) *
            (((double)_comp.dig_H2) / 65536.0 * (1.0 + ((double)_comp.dig_H6) / 67108864.0 * var_H *
                                           (1.0 + ((double)_comp.dig_H3) / 67108864.0 * var_H)));
    var_H = var_H * (1.0 - ((double)_comp.dig_H1) * var_H / 524288.0);
    
    LOG(LL_DEBUG,("%s: compHum: %f",__PRETTY_FUNCTION__,var_H));
    
    if (var_H > 100.0)
        var_H = 100.0;
    else if (var_H < 0.0)
        var_H = 0.0;
        
    
    
    return var_H;
}
