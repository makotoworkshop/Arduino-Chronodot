// Code by JeeLabs http://news.jeelabs.org/code/
// Released to the public domain! Enjoy!
//
// Modified for Chronodot / DS3132 with 
//   temperature data by Stephanie Maks
//   http://planetstephanie.net/
//
// Alarm 1 & 2 added by Makoto
// http://makotoworkshop.org/

#ifndef CHRONODOT_H
#define CHRONODOT_H

// Simple general-purpose date/time class (no TZ / DST / leap second handling!)
class DateTime {
public:
    DateTime (uint32_t t =0);
    DateTime (uint16_t year, uint8_t month, uint8_t day,
                uint8_t hour =0, uint8_t min =0, uint8_t sec =0, int tempF =0, float tempC = 0.0);
    DateTime (const char* date, const char* time);
    uint16_t year() const       { return 2000 + yOff; }
    uint8_t month() const       { return m; }
    uint8_t day() const         { return d; }
    uint8_t hour() const        { return hh; }
    uint8_t minute() const      { return mm; }
    uint8_t second() const      { return ss; }
    int tempF() const			{ return ttf; }
    float tempC() const			{ return ttc; }
    uint8_t dayOfWeek() const;

    // 32-bit times as seconds since 1/1/2000
    long secondstime() const;   
    // 32-bit times as seconds since 1/1/1970
    uint32_t unixtime(void) const;

protected:
    uint8_t yOff, m, d, hh, mm, ss;
    int ttf;
    float ttc;
};

// Chronodot based on the DS3231 chip connected via I2C and the Wire library
class Chronodot {
public:
  static uint8_t begin(void);
    static void adjust(const DateTime& dt);
    uint8_t isrunning(void);
    static DateTime now();
};

// RTC using the internal millis() clock, has to be initialized before use
// NOTE: this clock won't be correct once the millis() timer rolls over (>49d?)
class RTC_Millis {
public:
    static void begin(const DateTime& dt) { adjust(dt); }
    static void adjust(const DateTime& dt);
    static DateTime now();

protected:
    static long offset;
};

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// Ajouté par Makoto

// Alarm1 class
class AlarmTime1 {
public:
    AlarmTime1 (uint8_t hourA1 =0, uint8_t minA1 =0, uint8_t secA1 =0);
    uint8_t hourA1() const        { return hhA1; }
    uint8_t minuteA1() const      { return mmA1; }
    uint8_t secondA1() const      { return ssA1; }

protected:
    uint8_t hhA1, mmA1, ssA1;
};

// ChronodotAlarm based on the DS3231 chip connected via I2C and the Wire library
class ChronodotAlarm1 {
public:
    static void adjust(const AlarmTime1& dt);
    static AlarmTime1 now();
    static void Alarm1SetON();
    static void Alarm1SetOFF();
    static int Alarm1Flag();
    static int Alarm1Status();
    static void Alarm1Stop();
};


// Alarm2 class
class AlarmTime2 {
public:
    AlarmTime2 (uint8_t hourA2 =0, uint8_t minA2 =0);
    uint8_t hourA2() const        { return hhA2; }
    uint8_t minuteA2() const      { return mmA2; }

protected:
    uint8_t hhA2, mmA2;
};

// ChronodotAlarm based on the DS3231 chip connected via I2C and the Wire library
class ChronodotAlarm2 {
public:
    static void adjust(const AlarmTime2& dt);
    static AlarmTime2 now();
    static void Alarm2SetON();
    static void Alarm2SetOFF();
    static int Alarm2Flag();
    static int Alarm2Status();
    static void Alarm2Stop();
};


#endif CHRONODOT_H

// EXEMPLE
// ALARM.adjust(AlarmTime1(6,30,10));		// met à l'heure : heures, minutes, secondes  
//  AlarmTime1 now = ALARM.now();		// lecture de l'heure en cours dans la puce DS3231, référence à la librairie Chronodot
//  heuresAlarme = now.hourA1(), DEC;		// stocke l'heure en décimale dans la variable "heures" grace à la fct "hour" de la lib chronodot
//  minutesAlarme = now.minuteA1(), DEC;	// stocke les minutes en décimale dans la variable "minutes" grace à la fct "minute" de la lib chronodot
