#ifndef STEPPER
#define STEPPER

#include <stdint.h>

#include <entities.h>
#include <AccelStepper.h>

#include <Servo.h>

class StepperActuador: public AccelStepper, public Actuator {
private:
public:
    StepperActuador(
        uint8_t pin1, 
        uint8_t pin2, 
        /*
        uint8_t pin3, 
        uint8_t pin4, 
        */
        bool enable = true
    ):AccelStepper(
        /*
        AccelStepper::FULL4WIRE,
        pin1, 
        pin2, 
        pin3, 
        pin4, 
        enable
        */
    //Se cambia la configuracion para usar controlador
       AccelStepper::DRIVER,
        pin1, 
        pin2, 
        enable
    ), Actuator(){};
    void execute(Position);
};

class ServoActuator: public Servo{
private:
    uint8_t pin;
public:
    ServoActuator(uint8_t pin){
        this->pin=pin;
    };
    void execute(Position);
};




void StepperActuador::execute(Position pos){}

void ServoActuator::execute(Position pos){}

#endif