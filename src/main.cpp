#include <Arduino.h>
#include <user_interfaces/potenciometer.h>
#include <actuator/stepper.h>

PotentiometerInput pot = PotentiometerInput(A0);
StepperActuador stepper = StepperActuador(1,2, true);

void setup(){}
void loop(){
  Position pos = pot.GetPosition();
  stepper.execute(pos);
  Serial.println(pos.getValue());
}
