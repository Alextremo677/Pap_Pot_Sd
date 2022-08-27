#include <Arduino.h>


//Este codigo se usa para reproducir los movimientos de dos potensiometros en el robot Scara y utiliza una memoria microSD para guardar los datos de posiciones y
//luego poderlos reporducir

#include <AccelStepper.h>
#include <MultiStepper.h>

AccelStepper stepper(1, 30, 31); // Pin 30 para controlar los pulsos y el pin 31 para la dirección Eje codo
AccelStepper stepper2(1, 7, 8);  // Pin 7 para controlar los pulsos y el pin 8 para la dirección Eje hombro
int val = 512;
int val2 = 512;
int previous = 0;
int previous2 = 0;
int long newval = 0;
int long newval2 = 0;
int sw1 = 36;
int sw2 = 37;
long positions[2];//Vector para almacenar posicion del motor

int vect[2];//Vector para almacenar los datos de la SD
int i = 0; //Variable de incremento para el vector
int j = 0; //Variable de incremento para el vector

int var = 0; //Variable relaciona al if para dar posicion inicial al motor
MultiStepper steppers;


#include <SD.h>

File myFile;

int UltimaPocicion = 0;
String cadena = "";


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(sw1, INPUT);
  pinMode(sw2, INPUT);

  digitalWrite(sw1, LOW);
  digitalWrite(sw2, LOW);
  //Codo
  stepper.setMaxSpeed(1000);
  stepper.setAcceleration(800);
  //Hombro
  stepper2.setMaxSpeed(4000);
  stepper2.setAcceleration(4800);

  steppers.addStepper(stepper);
  steppers.addStepper(stepper2);

  Serial.print("Iniciando SD ...");
  if (!SD.begin(53)) {
    Serial.println("No se pudo inicializar");
    return;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
    //If para guardar los datos
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


  if ((digitalRead(sw1) == LOW) && (digitalRead(sw2) == HIGH) && var == 0) // && (j <= i))
  {
    //    int sensor1 = analogRead(0);
    //    int sensor2 = analogRead(1);

    //    positions[0] = map(analogRead(0), 0, 1023, 0, 35000);
    //    positions[1] = map(analogRead(1), 0, 1023, 0, 35000);

    stepper.targetPosition();
    stepper2.targetPosition();
    //    Serial.print("    stepper.targetPosition()");
    //    Serial.print(    stepper.targetPosition());
    //    positions[0] = stepper.currentPosition();
    //    positions[1] = stepper2.currentPosition();
    //    stepper.setCurrentPosition(positions[0]);
    //    stepper2.setCurrentPosition(positions[1]);
    //stepper.currentPosition(10000);
    steppers.moveTo(positions);
    steppers.runSpeedToPosition();

    Serial.print("Posicion inicial=");
    Serial.print(stepper.currentPosition());
    Serial.print(",");
    Serial.print(stepper2.currentPosition());
    Serial.print("++++++++++++++++++++++++++++++++++++++++++++++++");
    var = 1;
  }


  //If para leer los datos
  if ((digitalRead(sw1) == LOW) && (digitalRead(sw2) == HIGH))// && (j <= i))
  {

    Serial.print("Posicion inicial=");
    Serial.print(stepper.currentPosition());
    Serial.print(",");
    Serial.print(stepper2.currentPosition());
    //Serial.println("Leer datos");

    //Leer la SD
    myFile = SD.open("datalog.txt");//abrimos  el archivo
    if (myFile) {
      int totalBytes = myFile.size();
      cadena = "";
      if (UltimaPocicion >= totalBytes)   UltimaPocicion = 0;
      myFile.seek(UltimaPocicion);

      while (myFile.available()) {

        char caracter = myFile.read();
        cadena = cadena + caracter;
        UltimaPocicion = myFile.position();
        if (caracter == 10) //ASCII de nueva de línea
        {
          break;
        }
      }
      myFile.close(); //cerramos el archivo
      //Serial.print(cadena);
      int index = 0;
      char c = cadena[index++];
      //pausa = 0;
      while (c >= '0' && c <= '9')
      {
        //pausa = 10 * pausa + (c - '0');
        c = cadena[index++];
      }
      //int val[2];
      for (int k = 0; k < 2 ; k++)//For para separar el vector, ubica cada dato en una ubicacion diferente del vector
      {
        int index = cadena.indexOf(',');
        vect[k] = cadena.substring(0, index).toInt();
        cadena = cadena.substring(index + 1);
      }
      //      Serial.print("    ");
      //      Serial.print(vect[0]);
      //      Serial.print(",");
      //      Serial.print(vect[1]);
      //      Serial.print("       ");
    } else {
      Serial.println("Error al leer el archivo");
    }

    val = vect[0];
    val2 = vect[1];

    Serial.print("    ");
    Serial.print(val);
    Serial.print(",");
    Serial.print(val2);
    Serial.print("       ");
    if (((val > previous + 2) || (val < previous - 2))  ) //Eje codo
    {
      //int long newval = map(val, 0, 1023, 0, 35000);
      int long newval = map(val, 0, 1023, -17500, 17500);
      positions[0] = newval;
      previous = val;
    }
    if (((val2 > previous2 + 2) || (val2 < previous2 - 2))) //Eje hombro
    {
      //int long newval2 = map(val2, 0, 1023, 200000, 0);
      int long newval2 = map(val2, 0, 1023, 100000, -100000);
      positions[1] = newval2;
      previous2 = val2;
    }

    Serial.print(positions[0]);
    Serial.print(",");
    Serial.println(positions[1]);
    //    Serial.println("Mover a posicion");
    steppers.moveTo(positions);
    steppers.runSpeedToPosition();
    j++;
  }
  //If para borrar los datos
  if (digitalRead(sw1) == HIGH && digitalRead(sw2) == HIGH)
  {
    //Borrar datos SD
    Serial.println("Borrar datos");
    SD.remove("datalog.txt");
  }
}