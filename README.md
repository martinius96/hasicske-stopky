# Stopky pre požiarny šport cez Arduino
* Stopky vhodné sú vhodné pre Dobrovoľný hasičský zbor (DHZ) pre tréningové meranie útoku tímu.
* Logika systému sa vykonáva každých 10ms (rozlíšenie na stotiny), alebo 100ms (rozlíšenie na desatiny sekundy)
* Čas je vypisovaný na LCD znakový displej rozmeru 20x4, alebo 16x2 s ktorými ráta aj programová implementácia
* Vstupy sú pripojené v režime INPUT_PULLUP buď k internému 20-kohm rezistoru Arduina, alebo prostredníctvom externého pullup rezistora
![Hasičské stopky - Arduino - desatiny](https://i.imgur.com/Ciz66ft.jpg)
# Funkčnosť systému:
* Stopky sa odštartujú kontaktom (môže byť nahradené signálnou pištoľou)
* 2 spínacie kontakty umiestnené na terčoch sa aktivujú pri spadnutí terča, zastaví sa ľavý/pravý prúd na stopkách.
* Posledný kontakt slúži na vynulovanie času - reset času, nové družstvo, nový štart tímu, neplatný štart.

**Hardvér pre projekt:**
* Arduino Uno/Nano - AtMega328P
* LCD znakový displej 16x2 alebo 20x4
* I2C prevodník
* 4x spínacie kontakty
# Zapojenie
Arduino | Periféria
------------ | -------------
D12 | Kontakt ŠTART
D11 | Kontakt STOP - ľavý terč
D10 | Kontakt STOP - pravý terč
D10 | Kontakt RESET
A4 | SDA
A5 | SCK
# Schéma zapojenia
![Schéma zapojenia - Hasičské stopky - Arduino](https://i.imgur.com/GbU5zPK.png)
