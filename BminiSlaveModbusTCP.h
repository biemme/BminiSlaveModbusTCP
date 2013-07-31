#ifndef BMINI_SLAVE_MODBUS_TCP_H
#define BMINI_SLAVE_MODBUS_TCP_H


/* Biemme Italia, 2013
 http://www.biemmeitalia.net/
*/

//the following variable enable the modbus library through RS485
//https://code.google.com/p/simple-modbus/
#define MODBUS_RS485_ENABLE 1

#include "Arduino.h"

// function definitions
#ifdef MODBUS_RS485_ENABLE
 void bmini_init(unsigned int slaveid, unsigned int baudrate, int TOTAL_REGS_SIZE);
 unsigned int modbus_update_regs(unsigned int *holdingRegs);
#else
 void bmini_init();
#endif

void relay(int relay_number, int value);
int get_inputs(int di_number);
float readTemperatureC(int an_number);
float readTemperatureF(int an_number);
int analogReadPin(int pin_number);

#endif
