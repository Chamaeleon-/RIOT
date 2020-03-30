#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "phydat.h"
#include "board.h"
#include "saul.h"
#include "saul_periph.h"
#include "native_temp_saul.h"
#include "xtimer.h"
#define MAXCHAR 1000

FILE *sensorfile = NULL;
int8_t last_value = 0;
uint32_t valid_until = 0;
xtimer_ticks32_t consumed_time = {.ticks32 = 0}; // TODO use ms instead of ticks

static int read(const void *dev, phydat_t *res) 
{
    (void) dev;
    // const saul_native_params_t *params = *((const saul_native_params_t **)dev);
    char str[MAXCHAR];
    res->scale = 0;
    res->unit = UNIT_TEMP_C;
    res->val[0] = 00;
    
    // TODO : rollover proof solution
    if (xtimer_now().ticks32 <= consumed_time.ticks32){
        res->val[0] = last_value;
        return 1;
    }
    else
    {
        if (sensorfile == NULL)
        {
            printf("Could not read file\n");
            return 0;
        }
        while(consumed_time.ticks32 < xtimer_now().ticks32){
            printf("%lli\n",xtimer_now_usec64());
            if (fgets(str, MAXCHAR, sensorfile) != NULL)
            {
                char* value;
                char* time_or_keyword;
                time_or_keyword = strtok(str, ","); // maybe use strtok_r
                if (strcmp(time_or_keyword,"LOOP") == 0)
                {
                    rewind(sensorfile);
                    continue;
                }
                value = strtok(NULL, ",");
                last_value = atoi(value);
                valid_until = (uint32_t) atoi(time_or_keyword);
                consumed_time.ticks32 = consumed_time.ticks32 + valid_until;
                printf("Value valid until: %i\n", consumed_time.ticks32);

            }
            else
            {
                return 0;
            }
            
        }
        res->val[0] = last_value;
        return 1; /* number of values written into to result data structure [1-3] */

    }
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