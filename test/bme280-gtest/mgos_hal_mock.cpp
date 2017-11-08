#include "mgos_hal.h"
#include "mgos_hal_mock.h"

#include "tst_bme280_testfixture.h"

// instantiate mocked lib
std::unique_ptr<MgosHalMock> BME280TestFixture::_mgosHal;

/* Delay routines */
void mgos_msleep(uint32_t secs){
 return BME280TestFixture::_mgosHal->mgos_msleep(secs);
}
void mgos_usleep(uint32_t usecs){
    return BME280TestFixture::_mgosHal->mgos_usleep(usecs);
}
