
#include <Arduino.h>
#include <Wire.h>
#ifndef __DS1307_H__
#define __DS1307_H__


#define DS1307_I2C_ADDRESS 0x68

class DS1307 {
  private:
    uint8_t decToBcd(uint8_t val);
    uint8_t bcdToDec(uint8_t val);

  public:
    void setDate(void);
    void getDate(void);
	  int jourSemaine(void);
	  void printTime(void);
    void remplissage_heure(uint8_t seconde, uint8_t minute, uint8_t heure);
    void remplissage_date(uint8_t jour_semaine, uint8_t jour, uint8_t mois, uint8_t annee);
    void initialiser_horloge(void);
    uint8_t seconde;
    uint8_t minute;
    uint8_t hour;
    uint8_t dayOfWeek;// day of week, 1 = Monday
    uint8_t dayOfMonth;
    uint8_t month;
    uint16_t year;
    
    struct Date_RTC{
	    uint8_t jour_semaine;
    	uint8_t jour;
    	uint8_t nbr_mois;
	    uint8_t annee;
    }date;

    struct Heure_RTC{
	    uint8_t seconde;
	    uint8_t minute;
	    uint8_t heure;
    }heure_RTC;

    struct Horloge_RTC{
	    Heure_RTC heure;
	    Date_RTC date;
    }horloge;
};


#endif
