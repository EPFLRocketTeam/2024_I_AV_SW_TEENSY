//
// Created by owhenthesaints on 14/04/24.
//
#include "teensy_intranet.hpp"
#include <zephyr/drivers/spi.h>

#define FREQUENCY 1000000
#define CHIP_SELECT_OPT 0
#define TEST_BUFFER_LENGTH 1000
// define the number
#define SLAVE_NUMBER 0
#define NUM_READ_BUFFERS

TeensyIntranet::TeensyIntranet() :
    rxBufferSync{byteBufferRx, BUFFER_LENGTH},
    txBufferSync{byteBufferTx, BUFFER_LENGTH},
    txBuffersSync{&txBufferSync, 1},
    rxBuffersSync{&rxBufferSync, 1},
    dev(device_get_binding(DEVICE_DT_NAME(DT_NODELABEL(lpspi3)))),
    spiCfg{FREQUENCY, SPI_OP_MODE_MASTER | SPI_TRANSFER_MSB | SPI_WORD_SET(8) | SPI_MODE_CPHA, SLAVE_NUMBER, CHIP_SELECT_OPT} {

}

bool TeensyIntranet::readByte(uint8_t &byte) {
    // j'imagine que c'est l'implémentation souhaité
    byteBufferRx[0] = byte;
    return spi_transceive(dev, &spiCfg, &txBuffersSync, &rxBuffersSync);
}

bool TeensyIntranet::writeByte(const uint8_t &byte) {
    byteBufferTx[0] = byte;
    return spi_write(dev, &spiCfg, &txBuffersSync);
}
