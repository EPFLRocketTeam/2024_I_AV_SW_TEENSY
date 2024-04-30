//
// Created by owhenthesaints on 13/04/24.
//

#ifndef APP_BASETEENSYINTRANET_H
#define APP_BASETEENSYINTRANET_H

#include <zephyr/drivers/spi.h>
// just to avoid magic constants
#define BUFFER_LENGTH 1

class BaseTeensyIntranet{
public:
    explicit BaseTeensyIntranet(const device * device = device_get_binding(DEVICE_DT_NAME(DT_NODELABEL(lpspi4))));

    uint8_t readByte(uint8_t &byte);
    uint8_t writeByte(const uint8_t &byte);

    // know if you managed to write
    bool getWriteSuccessful() const;
    bool getReadSuccessful() const;
private:
    uint8_t byteBufferRx[BUFFER_LENGTH] = {0};
    uint8_t byteBufferTx[BUFFER_LENGTH] = {0};
    //Synchronous read buffer
    const struct spi_buf  rxBufferSync;
    //Synchronous write buffer
    const struct spi_buf txBufferSync;
    uint8_t readError{};
    uint8_t writeError{};
    const struct device * dev;
    const struct spi_config spiCfg;
    // synchronous transmition set points to an array of buffers
    const struct spi_buf_set txBuffersSync;
    // synchronous recieve set
    const struct spi_buf_set rxBuffersSync;
};


#endif //APP_BASETEENSYINTRANET_H
