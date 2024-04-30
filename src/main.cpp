
#include "base_teensy_intranet.hpp"


int main(){
    auto spi_device = BaseTeensyIntranet();
    uint8_t array[3] = {1, 2, 3};
    uint8_t byte = 7;

    while(1){
        spi_device.appendToSend(array, 3);
        spi_device.flush();
    }
}