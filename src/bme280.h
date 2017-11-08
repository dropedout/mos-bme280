#ifndef BME280_H
#define BME280_H

#include "mgos.h"
#include "mgos_debug.h"
#include "mgos_i2c.h"
#include "bm280_types.h"

#define BME280_ADDRESS  0x76

extern struct mgos_i2c* gI2C;

class BME280 {
    bool _initDone;
    int32_t _fine;
    _sRegRawValue _rawTemp,_rawPres;
    int16_t _rawHum;
    _sCompensate _comp;
    sRegConfig _config;
    sRegControlMeasurement _controlMeasurement;
    sControlHumidity _controlHumiditiy;
    sRegStatus _status;

    bool readBurstBME280();

    double compensate_T_double();
    double compensate_H_double();
    double compensate_P_double();

public:
    BME280();
    virtual ~BME280(){LOG(LL_INFO,(__PRETTY_FUNCTION__));}

    bool isInitialized() const {
        return _initDone;
    }
    double getTemperature();
    double getHumidity() const;
    double getPressure() const;
    const sCompensate& getCompensate() const {return _comp;}
    bool triggerMeasurement();

};


#endif /* end of include guard: BME280_H */
