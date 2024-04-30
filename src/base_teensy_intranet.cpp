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

// possibilité de définir le channel sur lequel on veut le spi BaseTeensyIntranet(device_get_binding(DEVICE_DT_NAME(DT_NODELABEL(lpspi4))))
// spi 4; 10 11 12 13 CS MOSI MISO SCK
// spi 3; 39 26 27 38 MISO MOSI SCK CS
BaseTeensyIntranet::BaseTeensyIntranet(const device * device) : rxBufferSync{byteBufferRx, BUFFER_LENGTH},
                                           txBufferSync{byteBufferTx, BUFFER_LENGTH},
                                           dev(device),
                                           spiCfg{FREQUENCY, SPI_OP_MODE_MASTER | SPI_TRANSFER_MSB | SPI_WORD_SET(8) |
                                                             SPI_MODE_CPHA, SLAVE_NUMBER,
                                                  CHIP_SELECT_OPT},// the one represents the size of
                                           txBuffersSync{&txBufferSync, 1}, // j'ai vu ça dans un autre code ça devrait marcher
                                           rxBuffersSync{&rxBufferSync, 1} {

}

uint8_t BaseTeensyIntranet::readByte(uint8_t &byte) {
    readError =  spi_read(dev, &spiCfg, &rxBuffersSync);
    return byteBufferRx[0];
}

uint8_t BaseTeensyIntranet::writeByte(const uint8_t &byte) {
    byteBufferTx[0] = byte;
    writeError = spi_transceive(dev, &spiCfg, &txBuffersSync, &rxBuffersSync);
    return byteBufferRx[0];
}

bool BaseTeensyIntranet::getWriteSuccessful() const{
    return !writeError;
}

bool BaseTeensyIntranet::getReadSuccessful() const{
    return !readError;
}

