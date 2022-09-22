#ifndef BUTTON
#define BUTTON

#include <stdint.h>

#include <entities.h>
#include <Arduino.h>

class Button:{
private:
public:
    Button(uint8_t PinD){
        this->PinD = PinD;
        init();
    }
    void init(){
        pinMode(pinD,INPUT);
    }
};

void StepperActuador::execute(Position pos){}

#endif