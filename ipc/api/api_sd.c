#include "api_sd.h"
#include "api_uart.h"

#ifdef CONFIG_SDMMC1_USE
static FATFS fat_fs_sdmmc1 = {
    0,
};

static struct fs_mount_t sd1_handle = {
    .type = FS_FATFS,
    .fs_data = &fat_fs_sdmmc1,
    .storage_dev = CONFIG_SDMMC1_DEVICE_NAME,
    .mnt_point = CONFIG_SDMMC1_MOUNT_DIR_NAME,
};

void sd1_mount()
{
    int ret = 0;
    ret = fs_mount(&sd1_handle);
    if (ret < 0) {
        DBG(DBG_ERR, "sdmmc1 fs mount fail - %s", strerror(ret));
    }
}
#endif

extern struct disk_info *disk_access_get_di(const char *name);

int sd_get_cid(char *dev_name)
{
    struct disk_info *disk = NULL;
	const struct device *dev = NULL;
	struct stm32_sdmmc_priv *priv = NULL;
    uint8_t *buf = NULL;

    disk = disk_access_get_di(dev_name);
    if (disk == NULL) {
        return ENOENT;
    }

    dev = disk->dev;
    priv = dev->data;

    buf = (void *)&priv->hsd.CID;
    //todo 이제 sd 문서보고 추출하기
    return 0;
}