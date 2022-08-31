#ifndef ENTITIES
#define ENTITIES

#include <stdint.h>

class Position {
private:
    uint8_t value;
public:
    Position(uint8_t value){
        this->value = (value <= 180) ? value : 180;   

        Serial.print("value2=  ");
        Serial.println(value);
    };
};

class UserInterface { 
public:
    virtual Position GetPosition(); 
};

class Actuator {
public:
    virtual void execute(Position);
};

class Storage
{
public:
    virtual void Save(Position, uint16_t);
    virtual Position read(uint16_t);
};

#endif