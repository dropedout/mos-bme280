#ifndef BM280_TYPES_H
#define BM280_TYPES_H

#include "mgos.h"

#define BME280_REGISTER_CONTROLHUMID 0xF2
#define BME280_REGISTER_STATUS 0XF3
#define BME280_REGISTER_CONTROL 0xF4
#define BME280_REGISTER_CONFIG 0xF5

#define BME280_REGISTER_PRESSUREDATA 0xF7
#define BME280_REGISTER_TEMPDATA 0xFA
#define BME280_REGISTER_HUMIDDATA 0xFD

#define BME280_REGISTER_CHIPID 0xD0
#define BME280_REGISTER_VERSION  0xD1
#define BME280_REGISTER_SOFTRESET  0xE0

#define BME280_REGISTER_DIG_T1 0x88
#define BME280_REGISTER_DIG_T2 0x8A
#define BME280_REGISTER_DIG_T3 0x8C

#define BME280_REGISTER_DIG_P1 0x8E
#define BME280_REGISTER_DIG_P2 0x90
#define BME280_REGISTER_DIG_P3 0x92
#define BME280_REGISTER_DIG_P4 0x94
#define BME280_REGISTER_DIG_P5 0x96
#define BME280_REGISTER_DIG_P6 0x98
#define BME280_REGISTER_DIG_P7 0x9A
#define BME280_REGISTER_DIG_P8 0x9C
#define BME280_REGISTER_DIG_P9 0x9E

#define BME280_REGISTER_DIG_H1 0xA1
#define BME280_REGISTER_DIG_H2 0xE1
#define BME280_REGISTER_DIG_H3 0xE3
#define BME280_REGISTER_DIG_H4 0xE4
#define BME280_REGISTER_DIG_H5 0xE5
#define BME280_REGISTER_DIG_H6 0xE7

#define BME280_MODE_SLEEP   0x00
#define BME280_MODE_FORCED  0x01
#define BME280_MODE_NORMAL  0x03

#define BME280_STATUS_MEASURING     0x08u
#define BME280_STATUS_IM_UPDATING   0x01u

#define BME280_OVERSAMPLING_SKIP	0x00u
#define BME280_OVERSAMPLING_1		0x01u
#define BME280_OVERSAMPLING_2		0x02u
#define BME280_OVERSAMPLING_4		0x03u
#define BME280_OVERSAMPLING_8		0x04u
#define BME280_OVERSAMPLING_16		0x05u

#define DEBUG_PRINT_STRUCT void print() {  LOG(LOG_DEBUG,("%d",get()));}

typedef struct _sCompensate{
    uint16_t dig_T1;
    int16_t  dig_T2;
    int16_t  dig_T3;
    uint16_t dig_P1;
    int16_t  dig_P2;
    int16_t  dig_P3;
    int16_t  dig_P4;
    int16_t  dig_P5;
    int16_t  dig_P6;
    int16_t  dig_P7;
    int16_t  dig_P8;
    int16_t  dig_P9;
    uint8_t  dig_H1;
    int16_t  dig_H2;
    uint8_t  dig_H3;
    int16_t  dig_H4;
    int16_t  dig_H5;
    int8_t   dig_H6;
} sCompensate;

typedef struct _sRegConfig {
    uint8_t t_sb: 3; //standby time
    uint8_t filter: 3; // iir filter
    uint8_t spare: 1;
    uint8_t spiw_en : 1;
    uint8_t get() {
        return (t_sb << 5) | (filter << 3) | spiw_en;
    }
    DEBUG_PRINT_STRUCT
} sRegConfig;
typedef struct _sRegControlMeasurement {
    uint8_t osrs_t : 3; // temperature oversampling
    uint8_t osrs_p : 3; // pressure oversampling
    uint8_t mode : 2; // device mode
    uint8_t get() {
        return (osrs_t << 5) | (osrs_p << 2) | mode;
    }
    DEBUG_PRINT_STRUCT
    _sRegControlMeasurement& operator= (const int& c){
        osrs_t = (c>>5)&0x07;
        osrs_p = (c>>3)&0x07;
        mode = c&0x03;
        return *this;
    }
} sRegControlMeasurement;

typedef struct _sRegControlHumidity {
    uint8_t spare : 5;
    uint8_t osrs_h : 3;       // pressure oversampling
    uint8_t get() {
        return (osrs_h);
    }
    void print() {  LOG(LOG_DEBUG,("%s : %c",__PRETTY_FUNCTION__,get()));}
} sControlHumidity;

typedef struct _sRegStatus {
    uint8_t spare :4;
    uint8_t measuring:1;
    uint8_t spare2:2;
    uint8_t inupdate:1;
    uint8_t get() {
        return (measuring<<3)|inupdate;
    }
    DEBUG_PRINT_STRUCT
    _sRegStatus& operator= (const u_int8_t& c){
        inupdate = c&0x01;
        measuring = (c>>3)&0x01;
        return *this;
    }
} sRegStatus;

typedef struct _sRegRawValue {
    uint32_t spare1: 8;
    uint32_t temp_msb:8;
    uint32_t temp_lsb :8;
    uint32_t temp_xlsb:4;
    uint32_t temp_spare2: 4;
    int32_t get() {
        return (int32_t) (temp_xlsb)|(temp_lsb<<4)|(temp_msb<<12);
    }
    DEBUG_PRINT_STRUCT
    _sRegRawValue& operator= (const uint8_t* c){
        temp_msb = c[0];
        temp_lsb = c[1];
        temp_xlsb = (c[2]>>4)&0x0f;
        return *this;
    }
} sRegRawValue;

#endif // BM280_TYPES_H
