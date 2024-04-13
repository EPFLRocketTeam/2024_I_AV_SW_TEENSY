//
// Created by owhenthesaints on 14/04/24.
//
#include "base_teensy_intranet.hpp"
#include <zephyr/drivers/spi.h>

#define FREQUENCY 1000000
#define CHIP_SELECT_OPT 0
#define TEST_BUFFER_LENGTH 1000
// define the max num of slaves to see
#define SLAVE_LIMIT 1

BaseTeensyIntranet::BaseTeensyIntranet() : spi_cfg{FREQUENCY, SPI_OP_MODE_MASTER | SPI_TRANSFER_MSB
                                                              | SPI_WORD_SET(8) | SPI_MODE_CPHA, SLAVE_LIMIT,
                                                   CHIP_SELECT_OPT},
                                           spi(device_get_binding(DEVICE_DT_NAME(DT_NODELABEL(lpspi4)))) {}


bool BaseTeensyIntranet::readByte(uint8_t &byte) {
    // doc
    spi_read_signal(spi, spi_cfg,)
    return true;
}