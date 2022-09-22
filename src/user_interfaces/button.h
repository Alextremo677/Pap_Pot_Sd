#ifndef button
#define button

#include <Arduino.h>

class Button
{
    private:
        uint8_t pin;
        bool state;
        bool change;
        bool normal;
        long timer;
        long bounce_time;
    public:
        Button(uint8_t pin, bool normal, long bounce_time);
        bool getState();
};

Button::Button(uint8_t pin, bool normal, long bounce_time){
    this->pin = pin;
    this->normal = normal;
    this->change = false;
    this->bounce_time = bounce_time;
    this->state = digitalRead(this->pin);
    this->timer = millis();
}

bool Button::getState(){
    long actual_time = millis();
    if (actual_time - this->timer < this->bounce_time) {
        return this->normal;
    }
    this->timer = actual_time;
    bool act_status = digitalRead(this->pin);
    this->change = act_status != this->state;
    if (this->change) {
        this->state = act_status;
    }
    return (!this->change) ? this->normal : this->state;
}


#endif