//
// Created by owhenthesaints on 13/04/24.
//

// this include to be changed to abs path
#include "../ARCH/include/common/channel/base_intranet_channel.hpp"
#include <zephyr/drivers/spi.h>

#ifndef APP_BASETEENSYINTRANET_H
#define APP_BASETEENSYINTRANET_H

class BaseTeensyIntranet : public virtual BaseIntranetChannel {
public:
    BaseTeensyIntranet();
    virtual void init() = 0;
    bool readByte(uint8_t& byte) override;
protected:
    const struct spi_config spi_cfg;


};



#endif //APP_BASETEENSYINTRANET_H
