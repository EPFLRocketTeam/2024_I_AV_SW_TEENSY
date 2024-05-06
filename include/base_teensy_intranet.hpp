//
// Created by owhenthesaints on 13/04/24.
//

#ifndef APP_BASETEENSYINTRANET_H
#define APP_BASETEENSYINTRANET_H

#include <zephyr/drivers/spi.h>
#include <vector>

// just to avoid magic constants
#define BUFFER_LENGTH 1

class BaseTeensyIntranet {
public:
    explicit BaseTeensyIntranet(const device *device);

    BaseTeensyIntranet(BaseTeensyIntranet &) = delete;

    BaseTeensyIntranet& operator=(const BaseTeensyIntranet &) = delete;

    virtual bool getWriteSuccessful() const;

    virtual void appendToSend(uint8_t *bufffer, size_t size);

    virtual void appendToSend(uint8_t &buffer);

    virtual bool flush();

protected:

    const struct device *dev;

    virtual uint8_t writeByte(const uint8_t &byte) = 0;


    uint8_t writeError;
private:
    std::vector<uint8_t> classBuffer;


};

class BaseTeensyIntranetSPI : public BaseTeensyIntranet {
public:
    explicit BaseTeensyIntranetSPI(const device *device = device_get_binding(DEVICE_DT_NAME(DT_NODELABEL(lpspi4))));

    // know if you managed to write
    bool getWriteSuccessful() const override;

    bool getReadSuccessful() const;

private:
    uint8_t byteBufferRx[BUFFER_LENGTH] = {0};
    uint8_t byteBufferTx[BUFFER_LENGTH] = {0};
    //Synchronous read buffer
    const struct spi_buf rxBufferSync;
    //Synchronous write buffer
    const struct spi_buf txBufferSync;
    uint8_t readError;
    uint8_t writeError;
    const struct spi_config spiCfg;
    // synchronous transmition set points to an array of buffers
    const struct spi_buf_set txBuffersSync;
    // synchronous recieve set
    const struct spi_buf_set rxBuffersSync;

    //functions to read write internally
    uint8_t readByte(uint8_t &byte);

    uint8_t writeByte(const uint8_t &byte) override;

};

/**
 * @brief a class to implement I2C communication
 */
class BaseTeensyIntranetI2C : public BaseTeensyIntranet {
public:
    explicit BaseTeensyIntranetI2C(const device *i2c_dev = device_get_binding(DEVICE_DT_NAME(DT_NODELABEL(lpi2c1))),
                                   const uint8_t &slave_adress = 0x06);

private:
    uint32_t i2cCfg;
    uint8_t i2c_data[BUFFER_LENGTH]{};
    uint8_t i2c_slave_address;
    uint8_t writeByte(const uint8_t &byte) override;

};

#endif //APP_BASETEENSYINTRANET_H
