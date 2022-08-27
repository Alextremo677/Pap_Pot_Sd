
#ifndef guardar
#define guardar

#include <guardar.h>
#include <stdint.h>

class guardar
{
  public:
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
};

#endif