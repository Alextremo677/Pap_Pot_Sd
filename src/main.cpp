#include <Arduino.h>
#include <user_interfaces/potenciometer.h>
#include <actuator/stepper.h>
#include <user_interfaces/button.h>
#include <llp.h>

#define BUTTON_INPUT 0x09
long timer = millis();

#define servo1_ID 0xA6
#define servo2_ID 0x9C

PotentiometerInput pot = PotentiometerInput(A0);
PotentiometerInput pot2 = PotentiometerInput(A1);
StepperActuador stepper = StepperActuador(1,2, true);
ServoActuator servo1 = ServoActuator(9);
ServoActuator servo2 = ServoActuator(10);
//Button button = Button(BUTTON_INPUT, false, 100);

void setup(){
  servo1.attach(9);
  servo2.attach(10);
  pinMode(BUTTON_INPUT, OUTPUT);
  Serial.begin(115200);
}
void loop(){
    Position pos = pot.GetPosition();
    Position pos2 = pot2.GetPosition();
    stepper.execute(pos);
    //Serial.println(pos.getValue());
    //servo1.write(pos.getValue()); 
    //servo2.write(pos2.getValue()); 


    DataPack payload;
    payload.addData(
        servo1_ID, 
        uint16_t(pos.getValue())
    );
    payload.addData(
        servo2_ID, 
        uint16_t(pos2.getValue())
    );
    payload.write(Serial);
    while (Serial.available()) {
        Serial.read();
    }
 

}
