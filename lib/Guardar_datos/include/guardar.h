
#ifndef guardar
#define guardar

#include <guardar.h>



if (digitalRead(sw1) == HIGH && digitalRead(sw2) == LOW)
  {
    Serial.println("Guardar datos");
    if (digitalRead(sw1) == HIGH && digitalRead(sw2) == LOW)
    {
      myFile = SD.open("datalog.txt", FILE_WRITE);//abrimos  el archivo

      if (myFile) {
        //Serial.print("Escribiendo SD: ");
        int sensor1 = analogRead(1);
        int sensor2 = analogRead(0);
        myFile.print(sensor1);
        myFile.print(",");
        myFile.println(sensor2);

        myFile.close(); //cerramos el archivo
      } else {
        Serial.println("Error al leer el archivo");
      }
    }
    i++;
  }