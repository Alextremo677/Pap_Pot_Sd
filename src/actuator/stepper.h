#ifndef STEPPER
#define STEPPER

#include <stdint.h>

#include <entities.h>
#include <AccelStepper.h>
#include <MultiStepper.h>

class StepperActuador: public AccelStepper, public Actuator {
private:
public:
    StepperActuador(
        uint8_t pin1, 
        uint8_t pin2, 
        uint8_t pin3, 
        uint8_t pin4, 
        bool enable = true
    ):AccelStepper(
        AccelStepper::FULL4WIRE,
        pin1, 
        pin2, 
        pin3, 
        pin4, 
        enable
    ), Actuator(){};
    void execute(Position);
};

void StepperActuador::execute(Position pos){}

#endif