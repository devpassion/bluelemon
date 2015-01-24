#include <iostream>
#include <gpio.h>
#include <chrono>
#include <thread>

using namespace io;

int main(int argc, char **argv) {
    
    std::cout << "Begin..." << std::endl;
    
    
    try {
        GPIO<Output> gpio(4);
        
        std::cout << "Blink on GPIO 4 ..." << std::endl;
        
        
        for(int i = 0; i < 10; i++)
        {
            // test calling desctructor in multiple object qith same pin
            if(4 == i)
            {
                GPIO<Output> gpio2(4);
                gpio2.set(PinState::HIGH);
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                gpio2.set(PinState::LOW);
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
            }
            gpio.set(PinState::HIGH);
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            gpio.set(PinState::LOW);
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    }
    catch( std::exception& ex )
    {
        std::cerr << "ERROR: " << ex.what() << std::endl;
    }
    std::cout << "Bye ..." << std::endl;
    
    return 0;
}
