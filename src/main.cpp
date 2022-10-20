#include <Arduino.h>
#include <user_interfaces/potenciometer.h>
#include <actuator/stepper.h>
#include <llp.h>

long timer = millis();

#define servo1_ID 0xA6
#define servo2_ID 0x9C

PotentiometerInput pot = PotentiometerInput(A0);
PotentiometerInput pot2 = PotentiometerInput(A1);
ServoActuator servo1 = ServoActuator(9);
ServoActuator servo2 = ServoActuator(10);

void setup(){
  servo1.attach(9);
  servo2.attach(10);
  Serial.begin(115200);
}
void loop(){
    Position pos = pot.GetPosition();
    Position pos2 = pot2.GetPosition();

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