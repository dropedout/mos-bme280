#include "mgos.h"
#include "mgos_debug.h"
#include "mgos_i2c.h"
#include "mgos_rpc.h"

struct mgos_i2c* gI2C = NULL;

static void timer_cb(void *i2c) {

  LOG(LL_INFO,("timer_cb"));

  LOG(LL_INFO, ("i2c read from : %x, data: %d", BME280_ADDRESS, mgos_i2c_read_reg_w(gI2C,BME280_ADDRESS,BME280_REGISTER_TEMPDATA)));
}

static void rpc_cb_chip(struct mg_rpc_request_info *ri, const char *args,
                              const char *src, void *user_data) {
  mg_rpc_send_responsef(ri, "{value: %d}", mgos_i2c_read_reg_w((struct mgos_i2c*)user_data,BME280_ADDRESS,BME280_REGISTER_TEMPDATA));
  LOG(LL_INFO,("info:%s / source: %s",ri->method.p,src));
  LOG(LL_INFO,("userdata:%p ",user_data));
  LOG(LL_INFO,("args:%s ",args));
}

enum mgos_app_init_result mgos_app_init(void) {

  if (mgos_i2c_init())
    gI2C = mgos_i2c_get_global();
  else
    return MGOS_APP_INIT_ERROR;

  mgos_set_timer(10000, true, timer_cb, gI2C);
  mgos_rpc_add_handler( "Hum.Read", rpc_cb_chip,gI2C);

  mgos_i2c_read_reg_w(gI2C,BME280_ADDRESS,BME280_REGISTER_HUMIDDATA);

  return MGOS_APP_INIT_SUCCESS;
}
