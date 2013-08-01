#include "BminiSlaveModbusTCP.h"
#ifdef MODBUS_RS485_ENABLE
 #include "SimpleModbusSlave.h"
#endif

/*bmini shield pins mapping
with Arduino Ethernet Board
Biemme Italia 2013
*/

#define DIGIN1 A0
#define DIGIN2 A1
#define DIGIN3 5
#define DIGIN4 6

#define RELAY1 3
#define RELAY2 2
#define RELAY3 8
#define RELAY4 7

#define MODBUSPIN 9

//analog pins

#define ANALOG1 5
#define ANALOG2 3
#define ANALOG3 4
#define ANALOG4 2

// pins initialization
void pin_init(){

	//digital inputs init
	pinMode(DIGIN1, INPUT_PULLUP);
	pinMode(DIGIN2, INPUT_PULLUP);
	pinMode(DIGIN3, INPUT_PULLUP);
	pinMode(DIGIN4, INPUT_PULLUP);

	//digital outputs init
	pinMode(RELAY1, OUTPUT);
	pinMode(RELAY2, OUTPUT);
	pinMode(RELAY3, OUTPUT);
	pinMode(RELAY4, OUTPUT);
}

#ifdef MODBUS_RS485_ENABLE
//modbus registers update
unsigned int modbus_update_regs(unsigned int *holdingRegs){
 	unsigned int ret = modbus_update(holdingRegs);
 	return ret;
}

// Bmini pins initialization
void bmini_init(unsigned int slaveid, unsigned int baudrate, int TOTAL_REGS_SIZE)
{	
	pin_init();
	//modbus_configure(baudrate, slaveid, MODBUSPIN, TOTAL_REGS_SIZE);
	modbus_configure(baudrate, slaveid, MODBUSPIN, TOTAL_REGS_SIZE);

}
#else
void bmini_init(){
	pin_init();
}
#endif

/* Read analog pins
* Biemme Italia
*/
int analogReadPin(int pin_number){
	int pin_toread;
	switch(pin_number){
                case 1:
                        pin_toread = ANALOG1;
                        break;
                case 2:
                        pin_toread = ANALOG2;
                        break;
                case 3:
                        pin_toread = ANALOG3;
                        break;
                case 4:
                        pin_toread = ANALOG4;
                        break;
                default:
                        // no more than 4 analog input are allowed
                        return -999;
        }
	//analog read will be between 0 and 1023 (8 bit resolution)
	int value = analogRead(pin_toread);
        
	return value;

}

//set relays status
void relay(int relay_number, int value){
	int pin_relay;
	switch(relay_number){
		case 1:
			pin_relay = RELAY1;
			break;
		case 2:
			pin_relay = RELAY2;
			break;
		case 3:
			pin_relay = RELAY3;
			break;
		case 4:
			pin_relay = RELAY4;
			break;
		default:
			// no more than 4 relays are allowed
			return;
	}
	digitalWrite(pin_relay,value);
}

/* Returns digital inputs status
* Biemme Italia
*/
int get_inputs(int di_number){
	int dig_pin, ret;

	switch(di_number){
		case 1:
			dig_pin = DIGIN1;
			break;
		case 2:
			dig_pin = DIGIN2;
			break;
		case 3:
			dig_pin = DIGIN3;
			break;
		case 4:
			dig_pin = DIGIN4;
			break;
		default:
			return -1;
	}
	ret = 1-digitalRead(dig_pin);
	return ret;
}

/* Reads temperature from TMP36 like sensors (Celsius)
* Biemme Italia
*/
float readTemperatureC(int an_number){

	int reading = analogReadPin(an_number);

	if (reading > -999){

		float voltage = reading * 5.0;
		voltage /= 1024.0; 
	 
		 //converting from 10 mv per degree wit 500 mV offset
		//to degrees ((volatge - 500mV) times 100)
	 	float temperatureC = (voltage - 0.5) * 100 ; 
	 
		return temperatureC;

	}else{
		return -999;		
	}
 
}

/* Reads temperature from TMP36 like sensors (Fahrenheit)
* Biemme Italia
*/
float readTemperatureF(int an_number){

	int reading = analogReadPin(an_number);

	if (reading > -999){

		float voltage = reading * 5.0;
		voltage /= 1024.0; 
	 
		 //converting from 10 mv per degree wit 500 mV offset
		//to degrees ((volatge - 500mV) times 100)
	 	float temperatureC = (voltage - 0.5) * 100 ; 



	 	// now convert to Fahrenheight
		float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
		return temperatureF;
	}else{
		return -999;
	}
}

