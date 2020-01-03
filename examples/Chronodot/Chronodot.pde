// Date, time and temperature functions using 
// a Chronodot RTC connected via I2C and Wire lib

#include <Wire.h>
#include "Chronodot.h"

Chronodot RTC;
ChronodotAlarm1 RADIO;
ChronodotAlarm2 REVEIL;

void setup () {
    Serial.begin(9600);
    Serial.println("Initializing Chronodot.");

    Wire.begin();
    RTC.begin();

  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }

// to set the time
  RTC.adjust(DateTime(2014,12,25,10,30,12));  // années, mois, jour, heures, minutes, secondes

// to set the alarm1
  RADIO.adjust(AlarmTime1(6,30,0));	// heures, minutes, secondes

// to set the alarm2
  REVEIL.adjust(AlarmTime2(7,30)); 	// heures, minutes
}

void loop () {
    DateTime now = RTC.now();
    
    Serial.print(now.year(), DEC);
    Serial.print('/');
    if(now.month() < 10) Serial.print("0");
    Serial.print(now.month(), DEC);
    Serial.print('/');
    if(now.day() < 10) Serial.print("0");
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    if(now.hour() < 10) Serial.print("0");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    if(now.minute() < 10) Serial.print("0");
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    if(now.second() < 10) Serial.print("0");
    Serial.print(now.second(), DEC);
    Serial.println();

    Serial.print(now.tempC(), 1);
    Serial.println(" degrees Celcius");
    Serial.print(now.tempF(), DEC);
    Serial.println(" degrees Farenheit");
    
    Serial.println();
    delay(3000);

Alarm1SetON();	// Activate the alarm1
Alarm1SetOFF();	// deactivate the alarm1
Alarm1Flag();	// return 1 for alarm1 active … return 0 for alarm1 inactive
Alarm1Status();	// return 1 for alarm1 ON … return 0 for alarm1 OFF
Alarm1Stop();	// set alarm1 to OFF

Alarm2SetON();	// Activate the alarm2
Alarm2SetOFF();	// deactivate the alarm2
Alarm2Flag();	// return 1 for alarm2 active … return 0 for alarm2 inactive
Alarm2Status();	// return 1 for alarm2 ON … return 0 for alarm2 OFF
Alarm2Stop();	// set alarm2 to OFF
}


// To read the alarm1  
void alarme1 ()
{
  AlarmTime1 now = RADIO.now();  	// lecture de l'alarme1
  heuresAlarme = now.hourA1(), DEC;     // stocke l'heure en décimale dans la variable "heures" grace à la fct "hour" de la lib chronodot
  minutesAlarme = now.minuteA1(), DEC;  // stocke les minutes en décimale dans la variable "minutes" grace à la fct "minute" de la lib chronodot
  Serial.print(heuresAlarme);   	//décommenter pour débug
  Serial.print(':');   
  Serial.print(minutesAlarme); 
  Serial.println();  
}

// To read the alarm2
void alarme2 ()
{
  AlarmTime2 now = REVEIL.now(); 	 // lecture de l'alarme2
  heuresAlarme = now.hourA2(), DEC;      // stocke l'heure en décimale dans la variable "heures" grace à la fct "hour" de la lib chronodot
  minutesAlarme = now.minuteA2(), DEC;   // stocke les minutes en décimale dans la variable "minutes" grace à la fct "minute" de la lib chronodot
  Serial.print(heuresAlarme);  		 //décommenter pour débug
  Serial.print(':');   
  Serial.print(minutesAlarme); 
  Serial.println();  
}
