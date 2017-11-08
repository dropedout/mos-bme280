#include "mgos.h"
#include "mgos_debug.h"
#include "mgos_i2c.h"

enum mgos_app_init_result mgos_app_init(void) {

  (mgos_i2c_init()) ? mgos_debug_init():return MGOS_APP_INIT_ERROR;
  mgos_i2c_get_freq(mgos_i2c_get_global());
  return MGOS_APP_INIT_SUCCESS;
}
