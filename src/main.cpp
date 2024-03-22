/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/drivers/spi.h>

#define SPI_MESSAGE 0xA5

#define LOG_LEVEL CONFIG_LOG_DEFAULT_LEVEL
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(app);

const struct spi_config spi_cfg = {
        .frequency = 1000000,
        .operation = SPI_OP_MODE_MASTER | SPI_TRANSFER_MSB | SPI_WORD_SET(8) | SPI_MODE_CPHA,
        .cs = 0,
};

uint8_t buf[1000] = {0};

int main(void)
{
    memset(buf, SPI_MESSAGE, 1000);
    struct spi_buf tx_buf = {.buf = buf, .len = 1000};
    struct spi_buf_set tx_bufs = {.buffers = &tx_buf, .count = 1};
    const struct device *spi;

    // this part is modified from the original code
    spi = device_get_binding(DEVICE_DT_NAME(DT_N_NODELABEL_flexspi));
    if (!device_is_ready(spi)) {
        return 0;
    }

    while (1) {
        spi_write(spi, &spi_cfg, &tx_bufs);
        k_sleep(K_MSEC(100));
    }

    return 0;
}
