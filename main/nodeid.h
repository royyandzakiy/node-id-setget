#ifndef NODEID_H
#define NODEID_H

#include "global.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "nvs.h"

#define NODEID 1

void init_nvs();
uint8_t get_nodeid();
void set_nodeid(uint8_t);
void restart_module();

#endif