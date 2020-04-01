#ifndef SAUL_PERIPH_H
#define SAUL_PERIPH_H
#include <stdint.h>

// TODO use this struc for configuration vars
typedef struct {
    const char *name;
    char* filename;
    uint8_t type;           /**< device class the device belongs to */
    uint8_t unit;
} saul_native_params_t;

#endif