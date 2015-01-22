#include <iostream>
#include <gpio.h>
#include <chrono>
#include <thread>

using namespace io;

int main(int argc, char **argv) {
    
    std::cout << "Begin..." << std::endl;
    
    GPIO<Output> gpio(4);
    
    std::cout << "Blink on GPIO 4 ..." << std::endl;
    
    
    for(int i = 0; i < 10; i++)
    {
        gpio.set(PinState::HIGH);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        gpio.set(PinState::LOW);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    
    std::cout << "Bye ..." << std::endl;
    
    return 0;
}
