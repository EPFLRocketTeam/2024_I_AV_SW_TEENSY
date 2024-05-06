//
// Created by owhenthesaints on 14/04/24.
//
#include "base_teensy_intranet.hpp"
#include <zephyr/drivers/spi.h>
#include <zephyr/drivers/i2c.h>
#include <stdexcept>

#define FREQUENCY 1000000
#define CHIP_SELECT_OPT 0
#define TEST_BUFFER_LENGTH 1000
// define the number
#define SLAVE_NUMBER 0
#define NUM_READ_BUFFERS


// possibilité de définir le channel sur lequel on veut le spi BaseTeensyIntranet(device_get_binding(DEVICE_DT_NAME(DT_NODELABEL(lpspi4))))
// spi 4; 10 11 12 13 CS MOSI MISO SCK
// spi 3; 39 26 27 38 MISO MOSI SCK CS
BaseTeensyIntranetSPI::BaseTeensyIntranetSPI(const device *device) : BaseTeensyIntranet(device),
                                                                     rxBufferSync{byteBufferRx, BUFFER_LENGTH},
                                                                     txBufferSync{byteBufferTx, BUFFER_LENGTH},
                                                                     readError(0),
                                                                     writeError(0),
                                                                     spiCfg{FREQUENCY,
                                                                              SPI_OP_MODE_MASTER | SPI_TRANSFER_MSB |
                                                                              SPI_WORD_SET(8) |
                                                                              SPI_MODE_CPHA, SLAVE_NUMBER,
                                                                              CHIP_SELECT_OPT},
                                                                     txBuffersSync{&txBufferSync, 1},
                                                                     rxBuffersSync{&rxBufferSync, 1} {}

uint8_t BaseTeensyIntranetSPI::readByte(uint8_t &byte) {
    readError = spi_read(dev, &spiCfg, &rxBuffersSync);
    return byteBufferRx[0];
}

uint8_t BaseTeensyIntranetSPI::writeByte(const uint8_t &byte) {
    byteBufferTx[0] = byte;
    writeError = spi_transceive(dev, &spiCfg, &txBuffersSync, &rxBuffersSync);
    return byteBufferRx[0];
}

bool BaseTeensyIntranetSPI::getWriteSuccessful() const {
    return !writeError;
}

bool BaseTeensyIntranetSPI::getReadSuccessful() const {
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
bool BaseTeensyIntranet::flush() {
    while (!classBuffer.empty()) {
        writeByte(classBuffer.front());
        if (writeError)
            return false;
        classBuffer.erase(classBuffer.begin());
    }
    return true;
}

BaseTeensyIntranet::BaseTeensyIntranet(const device *const device) : dev(device), writeError(0) {}

BaseTeensyIntranetI2C::BaseTeensyIntranetI2C(const device *const i2c_dev, const uint8_t & slave_addr) : BaseTeensyIntranet(i2c_dev),
                                                                            i2cCfg(I2C_SPEED_SET(I2C_SPEED_STANDARD) |
                                                                                   I2C_MODE_CONTROLLER),
                                                                            i2c_slave_address(slave_addr) {
    if (!device_is_ready(dev))
        throw std::runtime_error("bad i2c init");
    if (i2c_configure(dev, i2cCfg))
        throw std::runtime_error("bad config i2c");


}

/**
 * @brief a function that writes a byte in I2C
 * @param byte the byte to write
 * @return writeError
 */
uint8_t BaseTeensyIntranetI2C::writeByte(const uint8_t &byte) {
    i2c_data[0] = byte;
    writeError = i2c_write(dev, i2c_data, BUFFER_LENGTH, i2c_slave_address);
    return writeError;
}

bool BaseTeensyIntranet::getWriteSuccessful() const {
    return !writeError;
}