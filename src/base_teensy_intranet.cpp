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
BaseTeensyIntranet::BaseTeensyIntranet(const device *device) : rxBufferSync{byteBufferRx, BUFFER_LENGTH},
                                                               txBufferSync{byteBufferTx, BUFFER_LENGTH},
                                                               readError(0),
                                                               writeError(0),// the one represents the size of
                                                               dev(device), // j'ai vu ça dans un autre code ça devrait marcher
                                                               spiCfg{FREQUENCY, SPI_OP_MODE_MASTER | SPI_TRANSFER_MSB |
                                                                                 SPI_WORD_SET(8) |
                                                                                 SPI_MODE_CPHA, SLAVE_NUMBER,
                                                                      CHIP_SELECT_OPT}, txBuffersSync{&txBufferSync, 1},
                                                               rxBuffersSync{&rxBufferSync, 1} {}

uint8_t BaseTeensyIntranet::readByte(uint8_t &byte) {
    readError = spi_read(dev, &spiCfg, &rxBuffersSync);
    return byteBufferRx[0];
}

uint8_t BaseTeensyIntranet::writeByte(const uint8_t &byte) {
    byteBufferTx[0] = byte;
    writeError = spi_transceive(dev, &spiCfg, &txBuffersSync, &rxBuffersSync);
    return byteBufferRx[0];
}

bool BaseTeensyIntranet::getWriteSuccessful() const {
    return !writeError;
}

bool BaseTeensyIntranet::getReadSuccessful() const {
    return !readError;
}

void BaseTeensyIntranet::appendToSend(uint8_t &val) {
    classBuffer.push_back(val);
}

void BaseTeensyIntranet::appendToSend(uint8_t *vals, size_t size) {
    classBuffer.reserve(size);
    copy(vals, vals + size, std::back_inserter(classBuffer));
}

// l'implémentation n'est pas très efficace mieux de faire un circular buffer
bool BaseTeensyIntranet::flush(){
    while(!classBuffer.empty()){
        writeByte(classBuffer.front());
        if(writeError)
            return false;
        classBuffer.erase(classBuffer.begin());
    }
    return true;
}