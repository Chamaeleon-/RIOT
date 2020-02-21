#include <stdio.h>
#include "phydat.h"
#include "board.h"
#include "saul.h"
#include "saul_periph.h"

#define MAXCHAR 1000

static int read(const void *dev, phydat_t *res) 
{
    (void) dev;
    // const saul_native_params_t *params = *((const saul_native_params_t **)dev);
    // FILE *fp;
    // char str[MAXCHAR];
    // char* filename = "temp";
    res->scale = 0;
    res->unit = UNIT_TEMP_C;
    res->val[0] = 25;
    // fp = fopen(filename, "r");
    // if (fp == NULL){
    //     printf("Could not open file %s",filename);
    //     return 1;
    // }
    // while (fgets(str, MAXCHAR, fp) != NULL)
    //     res->val[0] = stoi(str);
    // fclose(fp);
    return 1;
}

const saul_driver_t native_temp_saul_driver = {
    .read = read,
    .write = saul_notsup,
    .type = SAUL_SENSE_TEMP,
};
