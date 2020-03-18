#include "log.h"
#include "saul_reg.h"
#include "saul_periph.h"
#include "native_temp_saul.h"

/**
 * @brief   Memory for the registry entries
 */
static saul_reg_t saul_reg_entry;

/**
 * @brief   Reference the driver struct
 */
extern saul_driver_t native_temp_saul_driver;

static const saul_native_params_t *saul_native_sensor;


void auto_init_native_temp_saul(void) 
{

    LOG_DEBUG("[auto_init_native_temp_saul] initializing virtual saul sensor\n");
    saul_reg_entry.dev = &saul_native_sensor;
    
    // saul_reg_entry.name = saul_native_sensor->name;
    saul_reg_entry.name = "Virtual Saul sensor";
    saul_reg_entry.driver = &native_temp_saul_driver;
    /* add to registry */
    saul_reg_add(&(saul_reg_entry));
    saul_native_init();
}