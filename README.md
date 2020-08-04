# Stopky pre požiarny šport cez Arduino
* Stopky vhodné sú vhodné pre Dobrovoľný hasičský zbor (DHZ) pre tréningové meranie útoku tímu.
* Logika systému sa vykonáva každých 10ms (rozlíšenie na stotiny), alebo 100ms (rozlíšenie na desatiny sekundy)
* Čas je vypisovaný na LCD znakový displej rozmeru 20x4, alebo 16x2 s ktorými ráta aj programová implementácia
* Vstupy sú pripojené v režime INPUT_PULLUP buď k internému 20-kohm rezistoru Arduina, alebo prostredníctvom externého pullup rezistora
* Stopky na desatiny sekundy sú dostupné so zdrojovým kódom, **stopky na stotiny sú dostupné iba v strojovom kóde - shareware - 30 sekúnd inicializácia**
* Pri záujme o plný zdrojový kód pre stopky na stotiny - martinius96@gmail.com

**Nahratie strojového kódu do Arduina - vzorovo pre COM21 - nástroj avrdude - program sketch.ino.hex**
* avrdude -CC: avrdude.conf -v -patmega328p -carduino -PCOM21 -b115200 -D -Uflash:w:sketch.ino.hex:i

![Hasičské stopky - Arduino - desatiny](https://i.imgur.com/Ciz66ft.jpg)
# Funkčnosť systému:
* Stopky sa odštartujú kontaktom (môže byť nahradené signálnou pištoľou)
* 2 spínacie kontakty umiestnené na terčoch sa aktivujú pri spadnutí terča, zastaví sa ľavý/pravý prúd na stopkách.
* Posledný kontakt slúži na vynulovanie času - reset času, nové družstvo, nový štart tímu, neplatný štart.

# Hardvér pre projekt:
* Arduino Uno/Nano - AtMega328P
* LCD znakový displej 16x2 alebo 20x4
* I2C prevodník
* 4x spínacie kontakty

**Režim I2C zbernice vzhľadom na verzie stopiek**
**Verzia stopiek** | **Režim I2C**
:---       |      ---:
Na desatiny | Standard Mode 100 kHz
Na stotiny | Fast Mode 400 kHz

**Najpoužívanejšie adresy I2C prevodníka displejov**
* **0x3F**
* **0x27**
* Over adresu nahratím I2C scannera: https://playground.arduino.cc/Main/I2cScanner/

# Tabuľkové zapojenie vývodov
**Arduino** | **Kontakty**
:---       |      ---:
D12 | Kontakt ŠTART
D11 | Kontakt STOP - ľavý terč
D10 | Kontakt STOP - pravý terč
D10 | Kontakt RESET
GND | GND
**Arduino** | **I2C DISPLEJ**
GND | GND
5V | VCC
A4 | SDA
A5 | SCK
# Schéma zapojenia
![Schéma zapojenia - Hasičské stopky - Arduino](https://i.imgur.com/GbU5zPK.png)
# Video stopiek na stotiny v akcii s meraním spotreby
[![IMAGE ALT TEXT](http://img.youtube.com/vi/E_z6doJvXng/0.jpg)](https://www.youtube.com/watch?v=E_z6doJvXng "Hasičské stopky - Arduino - spotreba - funkčnosť")
