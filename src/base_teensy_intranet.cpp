//
// Created by owhenthesaints on 14/04/24.
//
#include "base_teensy_intranet.hpp"
#include <zephyr/drivers/spi.h>

#define FREQUENCY 1000000
#define CHIP_SELECT_OPT 0
#define TEST_BUFFER_LENGTH 1000
// define the number
#define SLAVE_NUMBER 0
#define NUM_READ_BUFFERS

BaseTeensyIntranet::BaseTeensyIntranet() : rxBufferSync{byteBufferRx, BUFFER_LENGTH},
                                           txBufferSync{byteBufferTx, BUFFER_LENGTH},
                                           dev(device_get_binding(DEVICE_DT_NAME(DT_NODELABEL(lpspi3)))),
                                           spiCfg{FREQUENCY, SPI_OP_MODE_MASTER | SPI_TRANSFER_MSB | SPI_WORD_SET(8) |
                                                             SPI_MODE_CPHA, SLAVE_NUMBER,
                                                  CHIP_SELECT_OPT},// the one represents the size of
                                           txBuffersSync{&txBufferSync, 1}, // j'ai vu ça dans un autre code ça devrait marcher
                                           rxBuffersSync{&rxBufferSync, 1} {
    // if this does not work try
    // Inside class initialise txIntermediaryBufferSync un array the txBufferSync de length 1(dépendant du nombre de buffer que l'on veut)
    // const struct spi_buf txIntermediaryBufferSync[1] = {byteBufferTx}
    // et puis feed ça à txBuffersSync
}

bool BaseTeensyIntranet::readByte(uint8_t &byte) {
    // j'imagine que c'est l'implémentation souhaité
    byteBufferTx[0] = byte;
    return spi_transceive(dev, &spiCfg, &txBuffersSync, &rxBuffersSync);
}

bool BaseTeensyIntranet::writeByte(const uint8_t &byte) {
    byteBufferTx[0] = byte;
    return spi_write(dev, &spiCfg, &txBuffersSync);
}
