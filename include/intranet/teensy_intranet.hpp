//
// Created by owhenthesaints on 13/04/24.
//

#ifndef APP_BASETEENSYINTRANET_H
#define APP_BASETEENSYINTRANET_H

#include <zephyr/drivers/spi.h>
#include "intranet/intranet_packets.hpp"

// just to avoid magic constants
#define BUFFER_LENGTH 1

class TeensyIntranet {
public:
    explicit TeensyIntranet();

    void init();

    void encode(const IntranetPacket& packet);
    
    bool readByte(uint8_t &byte);
    bool writeByte(const uint8_t &byte);

private:
    uint8_t byteBufferRx[BUFFER_LENGTH] = {0};
    uint8_t byteBufferTx[BUFFER_LENGTH] = {0};
    //Synchronous read buffer
    const struct spi_buf  rxBufferSync;
    //Synchronous write buffer
    const struct spi_buf txBufferSync;
    const struct device *dev;
    const struct spi_config spiCfg;
    // synchronous transmition set points to an array of buffers
    const struct spi_buf_set txBuffersSync;
    // synchronous recieve set
    const struct spi_buf_set rxBuffersSync;
};


#endif //APP_BASETEENSYINTRANET_H
