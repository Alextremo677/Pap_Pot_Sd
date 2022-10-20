#ifndef STEPPER
#define STEPPER

#include <stdint.h>

#include <entities.h>

#include <Servo.h>

class ServoActuator: public Servo{
private:
    uint8_t pin;
public:
    ServoActuator(uint8_t pin){
        this->pin=pin;
    };
    void execute(Position);
};

void ServoActuator::execute(Position pos){}

#endif