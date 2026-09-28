#include <zephyr/kernel.h>
#include <stdio.h>
#include <stdint.h>
#include "main.h"
#include <errno.h>
#include "api_sd.h"


int main(void)
{
    int ret = 0;

    sd1_mount();
    sd_get_cid(CONFIG_SDMMC1_DEVICE_NAME);

    return ret;
}