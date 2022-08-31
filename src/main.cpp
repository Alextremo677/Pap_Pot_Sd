#include <Arduino.h>
#include <user_interfaces/potenciometer.h>
#include <actuator/stepper.h>

PotentiometerInput pot = PotentiometerInput(A0);
StepperActuador stepperr = StepperActuador(1,2,3,4, true);



/*Las siguientes lineas son ejemplo de como se definen los pines 
AccelStepper stepper(1, 30, 31); // Pin 30 para controlar los pulsos y el pin 31 para la dirección Eje codo
AccelStepper stepper2(1, 7, 8);  // Pin 7 para controlar los pulsos y el pin 8 para la dirección Eje hombro
MultiStepper steppers;
*/

void setup(){
  Serial.begin(9600);
}
void loop(){
  Position pos = pot.GetPosition();
  stepperr.execute(pos);
  pot.GetPosition();

  Serial.print("value=  ");
  Serial.println(stepperr.currentPosition());
  //Serial.println(PotentiometerInput);
}



