
#include "base_teensy_intranet.hpp"


int main(){
    auto spi_device = BaseTeensyIntranet();
    uint8_t test_int= 8;

    while(1){
        spi_device.writeByte(test_int);
    }
}