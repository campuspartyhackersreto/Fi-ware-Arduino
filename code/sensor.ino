// -- ********************************************************************* 
// -- Archivo : sensor.ino
// -- Proyecto : Campus-party FI-WARE
// -- Fecha : junio 2014 
// -- Copyright 2014 Eduardo R., Josue S., Armando V., Victor G., Ricardo B.
// -- --------------------------------------------------------------------- 
// -- This program is free software: you can redistribute it and/or modify 
// -- it under the terms of the GNU General Public License as published by 
// -- the Free Software Foundation, either version 3 of the License, or 
// -- (at your option) any later version. 

// -- This program is distributed in the hope that it will be useful, 
// -- but WITHOUT ANY WARRANTY; without even the implied warranty of 
// -- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
// -- GNU General Public License for more details. 

// -- You should have received a copy of the GNU General Public License 
// -- along with this program.  If not, see <http://www.gnu.org/licenses/>. 
// -- *********************************************************************

// Libraries 
// Library  Process.h, enables to run Linux processes on the Atheros AR9331
// processor.
#include <Process.h>

// Variables declaration.
// Variable Trigger enables and marks the beginning of the 8 cycle sonic burst.
// Variable Echo, gets the returned ultrasonic signal.
const int Trigger= A0;
const int Echo= A2;

// Settings
// In setup(), start serial communication for debugging purposes, and turn the
// built-in LED on pin 13 high while Bridge begins. Bridge.begin() is blocking,
// and should take about 2 seconds to complete. Once Bridge starts up, turn the
// LED off. Serial.begin() start serial communication for monitoring the data
// sent. pinMode set Trigger as an output signal and Echo as an input signal.
void setup() {
	Bridge.begin();
	Serial.begin(9600);
	while (!Serial);
	pinMode(Trigger,OUTPUT); // Trigger como salida
	pinMode(Echo,INPUT); // Echo como entrada
}

// Main loop process.
void loop() {
	// The bottom block create a single pulse with a 2 microseconds
	// of duty cycle
	digitalWrite(Trigger, LOW);
	delayMicroseconds(2);
	digitalWrite(Trigger, HIGH);
	delayMicroseconds(5);
	digitalWrite(Trigger, LOW);

	// Functions that calculate the distance 
	long time= pulseIn(Echo,HIGH);
	long distmm= funcionDistancia(time); 

	// Serial communication.
	Serial.print("dist ");
	Serial.print(distmm);
	Serial.println(" cm");

	// The following lines describe the process that make possible the
	// communication with the Atheros AR9331 Linux processor.
	Process p;
	p.begin("/root/project/updatedatavalue.sh");
	p.addParameter(String(distmm));
	p.run();
	while( p.running());
	while( p.available()) {
		int value=p.parseInt();
		if ( value == 200 ) {
			Serial.print("service ");
			Serial.println(value);
			}
		else
			Serial.println("service error!");
		break;
	}
	Serial.flush();
	delay(1000);
}

// Mathematical operation that calculates the distance.
long funcionDistancia(long t)
{
	long distance= (t/29)/2;
	return distance;
}