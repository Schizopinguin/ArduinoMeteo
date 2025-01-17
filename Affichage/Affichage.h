#include "bsec.h"
#include "GPS.h"
#include "RTC_DS1307.h"
//#include "TFT_Affichage.h"
#include <Adafruit_GFX.h>
#include <Adafruit_TFTLCD.h>

// D�finir l'objet tft pour l'�cran TFT
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0

#define LCD_RESET A4

// Assign human-readable names to some common 16-bit color values:
#define  BLACK  0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

class Affichage {
  private :

    void TFT_Affiche_Date(Calendrier::date_RTC curDate, Calendrier::date_RTC prevDate);
    void TFT_Affiche_Heure(Calendrier::heure_RTC curHour, Calendrier::heure_RTC prevHour);
    void TFT_Affiche_Indicateur_Ete_Hiver(int curIndic, int prevIndic);
    void TFT_Affiche_ville_ref_fuseau_horaire(char* curCity, char* prevCity);
    void TFT_Affiche_Etat_Synchro_GPS(bool syncState);

    void TFT_Affiche_Temperature(String curTemp, String prevTemp);
    void TFT_Affiche_Pression(String curPres, String prevPres);
    void TFT_Affiche_Humidite(String curHum, String prevHum);
    void TFT_Affiche_Qualite_Air(String curQual, String prevQual);
    void TFT_Affiche_Precision_Qualite_Air(String curAcc, String prevAcc);


  public :

    Calendrier::date_RTC prevDate; Calendrier::date_RTC curDate;
    Calendrier::heure_RTC prevHour;   Calendrier::heure_RTC curHour;
    int prevIndic; int curIndic;
    char* prevCity; char* curCity;
    bool syncState;
    String prevTemp; String curTemp;
    String prevPres; String curPres;
    String prevHum; String curHum;
    String prevQual; String curQual;
    String prevAcc; String curAcc;

    void TFT_setup(void);
    void TFT_setCursor(int a, int b);
    void TFT_println(String text);
    void TFT_fillScreen(uint16_t color);
    void TFT_affichage(	Calendrier::date_RTC curDate, Calendrier::date_RTC prevDate,
                        Calendrier::heure_RTC curHour, Calendrier::heure_RTC prevHour,
                        int curIndic, int prevIndic,
                        char* curCity, char* prevCity,
                        bool syncState,
                        String curTemp, String prevTemp,
                        String curPres, String prevPres,
                        String curHum, String prevHum,
                        String curQual, String prevQual,
                        String curAcc, String prevAcc		);
};
