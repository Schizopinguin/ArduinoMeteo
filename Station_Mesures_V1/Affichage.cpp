#include "Affichage.h"

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
//Adafruit_GFX(319, 479);

void Affichage::TFT_setup(void)
{
  tft.reset();
  uint16_t identifier = tft.readID();
  tft.begin(identifier);
  tft.fillScreen(WHITE);
  tft.setCursor(0, 0);
  tft.setTextColor(BLACK);
  tft.setTextSize(2);
  tft.println("Station Meteo Arduino");
  tft.println(" ");
}

void Affichage::TFT_fillScreen(uint16_t color)
{
  tft.fillScreen(color);
}

void Affichage::TFT_setCursor(int a, int b)
{
  tft.setCursor(a, b);
}

void Affichage::TFT_println(String text)
{
  tft.println(text);
}

void Affichage::TFT_affichage(	Calendrier::date_RTC curDate, Calendrier::date_RTC prevDate,
                                Calendrier::heure_RTC curHour, Calendrier::heure_RTC prevHour,
                                int curIndic, int prevIndic,
                                char* curCity, char* prevCity,
                                bool syncState,
                                String curTemp, String prevTemp,
                                String curPres, String prevPres,
                                String curHum, String prevHum,
                                String curQual, String prevQual,
                                String curAcc, String prevAcc		)
{
  TFT_Affiche_Date(curDate, prevDate);
  TFT_Affiche_Heure(curHour, prevHour);
  TFT_Affiche_Indicateur_Ete_Hiver(curIndic, prevIndic);
  TFT_Affiche_ville_ref_fuseau_horaire(curCity, prevCity);
  TFT_Affiche_Etat_Synchro_GPS(syncState);
  TFT_Affiche_Temperature(curTemp, prevTemp);
  TFT_Affiche_Pression(curPres, prevPres);
  TFT_Affiche_Humidite(curHum, prevHum);
  TFT_Affiche_Qualite_Air(curQual, prevQual);
  TFT_Affiche_Precision_Qualite_Air(curAcc, prevAcc);
}

void Affichage::TFT_Affiche_Date(Calendrier::date_RTC curDate, Calendrier::date_RTC prevDate)
{
  const char* jour_semaine[7] = {"Dimanche", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi"};
  const char* nom_mois[12] = {"Janvier", "Février", "Mars", "Avril", "Mai", "Juin", "Juillet", "Aout", "Septembre", "Octobre", "Novembre", "Décembre"};
  if (curDate.jour != prevDate.jour)
  {
    tft.setTextColor(BLACK);
    int x = tft.getCursorX();
    int y = tft.getCursorY();
    tft.setTextColor(WHITE);
    tft.print("Mardi 0 Janvier 2000");
    tft.setCursor(x, y);
    int prevannee = 2000 + prevDate.annee;
    tft.print(jour_semaine[jourSemaine(prevDate)]); tft.print(" "); tft.print(prevDate.jour); tft.print(" "); tft.print(nom_mois[prevDate.nbr_mois]); tft.print(" "); tft.print(prevannee); tft.println(" ");
    tft.setCursor(x, y);
    tft.setTextColor(BLACK);
    int curannee = 2000 + curDate.annee;
    tft.print(jour_semaine[jourSemaine(curDate)]); tft.print(" "); tft.print(curDate.jour); tft.print(" "); tft.print(nom_mois[curDate.nbr_mois]); tft.print(" "); tft.print(curannee); tft.println(" ");
  }
  else {
    tft.println(" ");
  }
}

void Affichage::TFT_Affiche_Heure(Calendrier::heure_RTC curHour, Calendrier::heure_RTC prevHour)
{
  if (curHour.seconde != prevHour.seconde)
  {
    int x = tft.getCursorX();
    int y = tft.getCursorY();
    tft.setTextColor(WHITE);
    tft.print("00:00 00");
    tft.setCursor(x, y);
    if (prevHour.heure < 10) {
      tft.print("0");
    } tft.print(prevHour.heure); tft.print(":"); if (prevHour.minute < 10) {
      tft.print("0");
    } tft.print(prevHour.minute); tft.print(" "); if (prevHour.seconde < 10) {
      tft.print("0");
    } tft.println(prevHour.seconde);
    tft.setCursor(x, y);
    tft.setTextColor(BLACK);
    if (curHour.heure < 10) {
      tft.print("0");
    } tft.print(curHour.heure); tft.print(":"); if (curHour.minute < 10) {
      tft.print("0");
    } tft.print(curHour.minute); tft.print(" "); if (curHour.seconde < 10) {
      tft.print("0");
    } tft.println(curHour.seconde);
  }
  else {
    tft.println(" ");
  }
}

void Affichage::TFT_Affiche_Indicateur_Ete_Hiver(int curIndic, int prevIndic)
{
  if (curIndic != prevIndic)
  {
    String saison;
    if (curIndic == 1) {
      saison = "Été";
    }
    else saison = "Hiver";

    tft.setTextColor(BLACK);
    tft.print("Heure d'");
    int x = tft.getCursorX();
    int y = tft.getCursorY();
    tft.setTextColor(WHITE);
    tft.print(saison);
    tft.setCursor(x, y);
    tft.setTextColor(BLACK);
    tft.println(saison);

  }
  else {
    tft.println(" ");
  }
}

void Affichage::TFT_Affiche_ville_ref_fuseau_horaire(char* curCity, char* prevCity)
{
  if (curCity != prevCity)
  {
    tft.setTextColor(BLACK);
    tft.print("Heure de ");
    int x = tft.getCursorX();
    int y = tft.getCursorY();
    tft.setTextColor(WHITE);
    tft.print(prevCity);
    tft.setCursor(x, y);
    tft.setTextColor(BLACK);
    tft.println(curCity);
  }
  else {
    tft.println(" ");
  }
}

void Affichage::TFT_Affiche_Etat_Synchro_GPS(bool syncState)
{
  if (syncState)
  {
    tft.fillCircle(309, 10, 5, GREEN);
  }
  else {
    tft.fillCircle(309, 10, 5, RED);
  }
}

void Affichage::TFT_Affiche_Temperature(String curTemp, String prevTemp)
{
  if (curTemp != prevTemp)
  {
    tft.setTextColor(BLACK);
    tft.print("Temperature : ");
    int x = tft.getCursorX();
    int y = tft.getCursorY();
    tft.setTextColor(WHITE);
    tft.print(prevTemp);
    tft.setCursor(x, y);
    tft.setTextColor(BLACK);
    tft.println(curTemp);
  }
  else {
    tft.println(" ");
  }
}

void Affichage::TFT_Affiche_Pression(String curPres, String prevPres)
{
  if (curPres != prevPres)
  {
    tft.setTextColor(BLACK);
    tft.print("Pression : ");
    int x = tft.getCursorX();
    int y = tft.getCursorY();
    tft.setTextColor(WHITE);
    tft.print(prevPres);
    tft.setCursor(x, y);
    tft.setTextColor(BLACK);
    tft.println(curPres);
  }
  else {
    tft.println(" ");
  }
}

void Affichage::TFT_Affiche_Humidite(String curHum, String prevHum)
{
  if (curHum != prevHum)
  {
    tft.setTextColor(BLACK);
    tft.print("Humidite : ");
    int x = tft.getCursorX();
    int y = tft.getCursorY();
    tft.setTextColor(WHITE);
    tft.print(prevHum);
    tft.setCursor(x, y);
    tft.setTextColor(BLACK);
    tft.println(curHum);
  }
  else {
    tft.println(" ");
  }
}

void Affichage::TFT_Affiche_Qualite_Air(String curQual, String prevQual)
{
  if (curQual != prevQual)
  {
    tft.setTextColor(BLACK);
    tft.print("Qualite air : ");
    int x = tft.getCursorX();
    int y = tft.getCursorY();
    tft.setTextColor(WHITE);
    tft.print(prevQual);
    tft.setCursor(x, y);
    tft.setTextColor(BLACK);
    tft.println(curQual);
  }
  else {
    tft.println(" ");
  }
}

void Affichage::TFT_Affiche_Precision_Qualite_Air(String curAcc, String prevAcc)
{
  if (curAcc != prevAcc)
  {
    tft.setTextColor(BLACK);
    tft.print("Precision qualite air : ");
    int x = tft.getCursorX();
    int y = tft.getCursorY();
    tft.setTextColor(WHITE);
    tft.print(prevAcc);
    tft.setCursor(x, y);
    tft.setTextColor(BLACK);
    tft.println(curAcc);
  }
  else {
    tft.println(" ");
  }
}

int Affichage::jourSemaine(Calendrier::date_RTC date) {
  int c = (14 - date.nbr_mois) / 12;
  int a = (date.annee + 2000) - c;
  int m = date.nbr_mois + (12 * c) - 2;
  return (date.jour + a + (a / 4) - (a / 100) + (a / 400) + (31 * m) / 12) % 7;
}
