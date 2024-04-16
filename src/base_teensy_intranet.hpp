//
// Created by owhenthesaints on 13/04/24.
//

#include <zephyr/drivers/spi.h>
#include <common/channel/base_intranet_channel.hpp>

#ifndef APP_BASETEENSYINTRANET_H
#define APP_BASETEENSYINTRANET_H

class BaseTeensyIntranet : public virtual BaseIntranetChannel {
public:
    BaseTeensyIntranet();

    virtual void init() = 0;

    bool readByte(uint8_t &byte) override;

protected:
    // this is the buffer
    struct spi_buf *read_buffer;
    // this points to an array of spi_buffs
    const struct spi_buf *read_buffers;
    const struct spi_buf_set rx_bufs;
    struct k_poll_signal sig;
private:
    const struct spi_config spi_cfg;
    const struct device *spi;


};


#endif //APP_BASETEENSYINTRANET_H
