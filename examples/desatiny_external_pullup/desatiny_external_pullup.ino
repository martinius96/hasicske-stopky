/*|------------------------------------------------------------------------------------------|*/
/*|VYHOTOVIL: MARTIN CHLEBOVEC                                                               |*/
/*|HASICSKE STOPKY - VERZIA ZDARMA - NA DESATINY SEKUNDY S CASOM PRE DVA UTOKY - LAVY/PRAVY  |*/
/*|FUNGUJE NA PRINCIPE FUNKCIE MILLIS() A VYKONAVANI KRATKYCH PROGRAMOVYCH CYKLOV            |*/
/*|INPUT PULLUP ZAPOJENIE S 20kohm INTERNAMY REZISTOROM (PODLA SCHEMY)                       |*/
/*|Doska: Arduino Uno, Nano, Mega, AtMega328P (Hardware I2C)                                 |*/
/*|WEB: https://arduino.php5.sk/hasicske-stopky.php                                          |*/
/*|PODPORA PROJEKTU PRE UVOLNENIE PLNEJ VERZIE ZDARMA: https://www.paypal.me/chlebovec       |*/
/*|------------------------------------------------------------------------------------------|*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//I2C adresa, stlpce, riadky, pouziva sa i 0x3F pre displej 20x4, 0x27 pre 16x2, skontruj cez I2C scanner https://playground.arduino.cc/Main/I2cScanner/
LiquidCrystal_I2C lcd(0x3F, 20, 4);

//DEKLARACIA DIGITALNYCH PINOV NA KTORE SU NAPOJENE TLACIDLA
const int start_tlacidlo = 12;
const int lavy_terc_kontakt = 11;
const int pravy_terc_kontakt = 10;
const int vynulovat_cas_tlacidlo = 9;

boolean run = false;         //bezi cas pre LAVY UTOK?
boolean run2 = false;         //bezi cas pre PRAVY UTOK?

//STAVY NACITANYCH LOGICKYCH HODNOT TLACIDIEL
int start_tlacidlo_stav = HIGH;
int lavy_terc_kontakt_stav = HIGH;
int pravy_terc_kontakt_stav = HIGH;
int vynulovat_cas_tlacidlo_stav = HIGH;

unsigned long timer = 0; //timer

//PREMENNE PRE PRVY CAS - LAVY UTOK
int second = 0;
int minute = 0;
int tenth = 0;

//PREMENNE PRE DRUHY CAS - PRAVY UTOK
int second2 = 0;
int minute2 = 0;
int tenth2 = 0;

void setup() {
  lcd.begin(); //incializacia displeja na I2C zbernici
  lcd.backlight(); //zapnutie podsvietenia
  pinMode(start_tlacidlo, INPUT); //nastav ako klasicky vystup - NUTNY EXTERNY PULLUP REZISTOR!!!!
  pinMode(lavy_terc_kontakt, INPUT);
  pinMode(pravy_terc_kontakt, INPUT);
  pinMode(vynulovat_cas_tlacidlo, INPUT);
  lcd.setCursor(0, 0); //nastav kurzor pre zapis na 1. riadok, 1. stlpec
  lcd.print("STOPKY - DHZ");
  lcd.setCursor(0, 1); //nastav kurzor pre zapis na 2. riadok, 1. stlpec
  lcd.print("MARTIN CHLEBOVEC");
  delay(2500);
  lcd.clear();
  lcd.setCursor(0, 0); //nastav kurzor pre zapis na 1. riadok, 1. stlpec
  lcd.print("00:00:0 L. PRUD");
  lcd.setCursor(0, 1); //nastav kurzor pre zapis na 2. riadok, 1. stlpec
  lcd.print("00:00:0 P. PRUD");
}

void tickClock() {
  Serial.println(millis() / 10);
  if (millis() - timer >= 100 || timer == 0) {
    tick();
    timer = millis();
  }
}

void loop() {
  tickClock();
  start_tlacidlo_stav = digitalRead(start_tlacidlo);
  lavy_terc_kontakt_stav = digitalRead(lavy_terc_kontakt);
  pravy_terc_kontakt_stav = digitalRead(pravy_terc_kontakt);
  vynulovat_cas_tlacidlo_stav = digitalRead(vynulovat_cas_tlacidlo);
  checkStart();
}

void checkStart() {
  if (start_tlacidlo_stav == LOW ) {
    run = true; //aktivuj cas pre lavy prud
    run2 = true; //aktivuj cas pre pravy prud
  }
  if (lavy_terc_kontakt_stav == LOW ) {
    run = false;
  }
  if (pravy_terc_kontakt_stav == LOW ) {
    run2 = false;
  }
  if (vynulovat_cas_tlacidlo_stav == LOW ) {
    run = false;
    run2 = false;
    second = 0;
    minute = 0;
    tenth = 0;
    second2 = 0;
    minute2 = 0;
    tenth2 = 0;
    updateLCD();
    updateLCD2();
  }
}


void tick() { //tick sa vykonava kazdych 100 miliseund, teda kazdu desatinu sekundy
  //LOGIKA BEZIACEHO CASU PRVEHO UTOKU (UTOK LAVY)
  if (run) {
    updateLCD();
    if (tenth == 9) {
      tenth = 0;
      if (second == 59) {
        second = 0;
        minute++;
      } else {
        second++;
      }
    } else {
      tenth++;
    }
  }

  //LOGIKA BEZIACEHO CASU DRUHEHO UTOKU (UTOK PRAVY)
  if (run2) {
    updateLCD2();
    if (tenth2 == 9) {
      tenth2 = 0;
      if (second2 == 59) {
        second2 = 0;
        minute2++;
      } else {
        second2++;
      }
    } else {
      tenth2++;
    }
  }
}

//VYPIS PRVEHO UTOKU NA DISPLEJ (UTOK LAVY)
void updateLCD() {
  lcd.setCursor(0, 0);
  if (minute < 10) {
    lcd.print("0");
  }
  lcd.print(minute, DEC);
  lcd.print(":");
  if (second < 10) {
    lcd.print("0");
  }
  lcd.print(second, DEC);
  lcd.print(":");
  lcd.print(tenth, DEC);
}

//VYPIS DRUHEHO UTOKU NA DISPLEJ (UTOK PRAVY)
void updateLCD2() {
  lcd.setCursor(0, 1);
  if (minute2 < 10) {
    lcd.print("0");
  }
  lcd.print(minute2, DEC);
  lcd.print(":");
  if (second2 < 10) {
    lcd.print("0");
  }
  lcd.print(second2, DEC);
  lcd.print(":");
  lcd.print(tenth2, DEC);
}
