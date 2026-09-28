#ifndef __API_SD_H__
#define __API_SD_H__

#include "main.h"
#include <zephyr/fs/fs.h>
#include <zephyr/storage/disk_access.h>
#include <ff.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/disk.h>
#include <zephyr/drivers/disk/sdmmc_stm32.h>
#include <zephyr/drivers/clock_control.h>
#include <zephyr/drivers/clock_control/stm32_clock_control.h>
#include <zephyr/drivers/pinctrl.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/reset.h>
#include <zephyr/pm/policy.h>
#include <zephyr/logging/log.h>
#include <zephyr/irq.h>
#include <zephyr/cache.h>
#include <soc.h>
#include <stm32_ll_rcc.h>
#include <api_config.h>

struct stm32_sdmmc_priv {
	void (*irq_config)();
	struct k_sem thread_lock;
	struct k_sem sync;
	SD_HandleTypeDef hsd;
	int status;
	struct k_work work;
	struct gpio_callback cd_cb;
	struct gpio_dt_spec cd;
	struct gpio_dt_spec pe;
	struct stm32_pclken *pclken;
	const struct pinctrl_dev_config *pcfg;
	const struct reset_dt_spec reset;

#if STM32_SDMMC_USE_DMA
#if STM32_SDMMC_USE_DMA_SHARED
	struct sdmmc_dma_stream dma_txrx;
	DMA_HandleTypeDef dma_txrx_handle;
#else
	struct sdmmc_dma_stream dma_rx;
	struct sdmmc_dma_stream dma_tx;
	DMA_HandleTypeDef dma_tx_handle;
	DMA_HandleTypeDef dma_rx_handle;
#endif
#endif /* STM32_SDMMC_USE_DMA */
};

#ifdef CONFIG_SDMMC1_USE
void sd1_mount();
#endif

int sd_get_cid(char *dev_name);

#endif