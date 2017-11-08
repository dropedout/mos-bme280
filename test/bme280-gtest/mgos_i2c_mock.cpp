
#include "mgos_i2c_mock.h"
#include "mgos_i2c.h"

#include "tst_bme280_testfixture.h"

// instantiate mocked lib
std::unique_ptr<MgosI2cMock> BME280TestFixture::_mgosI2c;

int mgos_i2c_read_reg_b(struct mgos_i2c *conn, uint16_t addr, uint8_t reg)
{
    return BME280TestFixture::_mgosI2c->mgos_i2c_read_reg_b(conn,addr,reg);
}
int mgos_i2c_read_reg_w(struct mgos_i2c *conn, uint16_t addr, uint8_t reg)
{
    return BME280TestFixture::_mgosI2c->mgos_i2c_read_reg_w(conn,addr,reg);
}
bool mgos_i2c_read_reg_n(struct mgos_i2c *conn, uint16_t addr, uint8_t reg,
                         size_t n, uint8_t *buf)
{
   return  BME280TestFixture::_mgosI2c->mgos_i2c_read_reg_n(conn,addr,reg,n,buf);
}

int mgos_i2c_get_freq(struct mgos_i2c *i2c){
    return BME280TestFixture::_mgosI2c->mgos_i2c_get_freq(i2c);
}

bool mgos_i2c_write_reg_b(mgos_i2c *conn, uint16_t addr, uint8_t reg, uint8_t value)
{
    return BME280TestFixture::_mgosI2c->mgos_i2c_write_reg_b(conn,addr,reg,value);
}
bool mgos_i2c_write_reg_w(mgos_i2c *conn, uint16_t addr, uint8_t reg, uint16_t value)
{
    return BME280TestFixture::_mgosI2c->mgos_i2c_write_reg_w(conn,addr,reg,value);
}
bool mgos_i2c_write_reg_n(mgos_i2c *conn, uint16_t addr, uint8_t reg, size_t n, uint8_t* buf)
{
    return BME280TestFixture::_mgosI2c->mgos_i2c_write_reg_n(conn,addr,reg,n,buf);
}
