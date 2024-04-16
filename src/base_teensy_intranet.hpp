//
// Created by owhenthesaints on 13/04/24.
//

#ifndef APP_BASETEENSYINTRANET_H
#define APP_BASETEENSYINTRANET_H

#include <zephyr/drivers/spi.h>
#include <common/channel/base_intranet_channel.hpp>
// just to avoid magic constants
#define BUFFER_LENGTH 1

class BaseTeensyIntranet : public virtual BaseIntranetChannel {
public:
    BaseTeensyIntranet();

    virtual void init() = 0;

    bool readByte(uint8_t &byte) override;
    bool writeByte(const uint8_t &byte) override;

protected:
    uint8_t byteBufferRx[BUFFER_LENGTH] = {0};
    uint8_t byteBufferTx[BUFFER_LENGTH] = {0};
    //Synchronous read buffer
    const struct spi_buf  rxBufferSync;
    //Synchronous write buffer
    const struct spi_buf txBufferSync;
private:
    const struct device * dev;
    const struct spi_config spiCfg;
    // synchronous transmition set points to an array of buffers
    const struct spi_buf_set txBuffersSync;
    // synchronous recieve set
    const struct spi_buf_set rxBuffersSync;
};


#endif //APP_BASETEENSYINTRANET_H
