#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "phydat.h"
#include "board.h"
#include "saul.h"
#include "saul_periph.h"
#include "native_temp_saul.h"
#define MAXCHAR 1000

FILE *sensorfile = NULL;
int8_t last_value = 0;
__time_t valid_until = 0;

static int read(const void *dev, phydat_t *res) 
{
    (void) dev;
    // const saul_native_params_t *params = *((const saul_native_params_t **)dev);
    char str[MAXCHAR];
    res->scale = 0;
    res->unit = UNIT_TEMP_C;
    res->val[0] = 00;

    // if (now <= valid_until){
    //     res->val[0] = last_value;
    //     return 1;
    // }
    // else
    // {
        if (sensorfile == NULL)
        {
            printf("Could not read file\n");
            return 0;
        }
        // while(valid_until < now){
            if (fgets(str, MAXCHAR, sensorfile) != NULL)
            {
                char* value;
                char* time;
                time = strtok(str, ","); // maybe use strtok_r
                value = strtok(NULL, ",");
                last_value = atoi(value);
                printf("Value valid until: %s\n", time);
                // valid_until = &time;
            }
            else
            {
                return 0;
            }
            
        // }
        res->val[0] = last_value;
        return 1; /* number of values written into to result data structure [1-3] */

    // }
    return 0;

}

const saul_driver_t native_temp_saul_driver = {
    .read = read,
    .write = saul_notsup,
    .type = SAUL_SENSE_TEMP,
};

int saul_native_init(void)
{
    char* filename = "temp";
    sensorfile = fopen(filename, "r");
    if (sensorfile == NULL){
        printf("Could not open file %s\n",filename);
        return 1;
    }
    return 0;
}