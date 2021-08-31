#include <io.hpp>

PCF8574 pcf8574(0x20);

void pcfinit(){
	Wire.setClock(400000); 
    pcf8574.pinMode(P0, INPUT);
	pcf8574.pinMode(P1, INPUT);
	pcf8574.pinMode(P2, INPUT);
	pcf8574.pinMode(P3, INPUT);
	pcf8574.pinMode(P4, INPUT);
	pcf8574.pinMode(P5, INPUT);
	pcf8574.pinMode(P6, INPUT);
	pcf8574.pinMode(P7, INPUT);
    if (pcf8574.begin()){
		Serial.println("OK");
	}else{
		Serial.println("KO");
	}
    pcf8574.pinMode(P0, INPUT);
	pcf8574.pinMode(P1, INPUT);
	pcf8574.pinMode(P2, INPUT);
	pcf8574.pinMode(P3, INPUT);
	pcf8574.pinMode(P4, INPUT);
	pcf8574.pinMode(P5, INPUT);
	pcf8574.pinMode(P6, INPUT);
	pcf8574.pinMode(P7, INPUT);
}

unsigned int readallbuttons(){
    unsigned int state = 0b0;
    for(int i = 0; i < 8; i++){
        state |= (!pcf8574.digitalRead(i) & 1) << i;
    }
    return state;
}