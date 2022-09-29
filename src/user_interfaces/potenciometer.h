#ifndef POTENTIOMETER
#define POTENTIOMETER

#include <entities.h>
#include <Arduino.h>

class PotentiometerInput: public UserInterface {
    private:
        uint8_t pin;
    public:
        PotentiometerInput(uint8_t pin){
            this->pin = pin;
        };
        Position GetPosition();
};

Position PotentiometerInput::GetPosition(){
    uint8_t value = map(analogRead(this->pin), 0, 1023, 0, 180);
    void sample();
    return Position(value);
}

#endif