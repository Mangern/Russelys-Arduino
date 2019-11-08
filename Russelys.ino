// Knappen er koblet til DIGITAL pin 2
const int BTN_PIN = 2;

// Definerer "makroer"
// Alle steder i koden der det står 'LED_1' blir byttet ut med LED[0] etc. før kompilering
// Dette for å tilpasse det nye array-systemet til gammel kode
#define LED_1 LED[0]
#define LED_2 LED[1]
#define LED_3 LED[2]
#define LED_4 LED[3]
#define LED_5 LED[4]
#define LED_6 LED[5]

// Antall led-pærer vi har
const int NUM_LEDS = 6;
// En array med pin-nummeret til hver LED
// Array er bedre egnet til mange LEDs, siden man kan loope gjennom (se resetAll()), legge til fler etc.
const int LED[] = {
  11,
  10,
  9,
  7,
  6,
  5,
};

// Antal moduser vi har. MÅ ØKES MED 1 HVER GANG MAN LEGGER TIL NY MODUS!!
const int NUM_MODES = 8;

// Lagrer hvilken lysmodus vi er i
int mode = 0;

// Er true dersom noen trykket på knappen 
// forrige gang loop() kjørte
bool trykketForrige = false;

// Skal lagre millis() verdi 
unsigned long time;

void setup()
{
  // Knappen gir input til programmet
  pinMode(BTN_PIN, INPUT);
  
  // LED-lampene styres av programmet. Er derfor OUTPUT
  for(int i = 0; i < NUM_LEDS; i++) {
    pinMode(LED[i], OUTPUT);
  }

  // analogRead(0) gir bare støy dersom det ikke er koblet til noe
  // Egnes derfor godt til å seede randomgeneratoren, altså gjøre slik at det blir forskjellige tall hver gang programmet kjøres.
  randomSeed(analogRead(0));

  // For debugging, gjør at vi kan sende data fra arduinoen til pc-en
  Serial.begin(9600);
}

// Funksjon som skrur av alle LED-pærene
void resetAll() {
  // Går gjennom alle tall fra 0 til NUM_LEDS-1, altså 
  // 0, 1, 2, 3, 4, 5
  for(int i = 0; i < NUM_LEDS; i++) {
    // Slår opp hvilken pin som hører til LED[i] og setter den på LOW
    digitalWrite(LED[i], LOW);
  }
}

// Skrevet av: alle
void mode0() {
  // En modus der alle LEDs er av
  resetAll();
}

// Skrevet av: alle
void mode1() {
  // En modus der alle LEDs er på
  for(int i = 0; i < NUM_LEDS; i++) {
    digitalWrite(LED[i], HIGH);
  }
}

// Skrevet av: Magnus
void mode2() {
   // Bølgen etterfulgt av blinking
  
    if(time % 1000 < 500) {
        if(time % 500 < 166) {
            digitalWrite(LED_1, HIGH);
            digitalWrite(LED_2, LOW);
            digitalWrite(LED_3, LOW);

            digitalWrite(LED_4, HIGH);
            digitalWrite(LED_5, LOW);
            digitalWrite(LED_6, LOW);
        }
        else if(time % 500 < 333) {
            digitalWrite(LED_1, LOW);
            digitalWrite(LED_2, HIGH);
            digitalWrite(LED_3, LOW);

            digitalWrite(LED_4, LOW);
            digitalWrite(LED_5, HIGH);
            digitalWrite(LED_6, LOW);
        }
        else {
            digitalWrite(LED_1, LOW);
            digitalWrite(LED_2, LOW);
            digitalWrite(LED_3, HIGH);

            digitalWrite(LED_4, LOW);
            digitalWrite(LED_5, LOW);
            digitalWrite(LED_6, HIGH);
        }
    }
    else {
        if(time % 500 < 100) {
            for(int i = 0; i < NUM_LEDS; i++) {
              digitalWrite(LED[i], HIGH);
            }
        }
        else if(time % 500 < 200) {
            resetAll();
        }
        else if(time % 500 < 300) {
            for(int i = 0; i < NUM_LEDS; i++) {
              digitalWrite(LED[i], HIGH);
            }
        }
        else if(time % 500 < 400) {
            resetAll();
        }
        else {
          for(int i = 0; i < NUM_LEDS; i++) {
              digitalWrite(LED[i], HIGH);
            }
        }
     
    }
}

// Skrevet av: Magnus
void mode3() {
  // En kompleks modus med 4 forskjellige sekvenser i løpet av 8 sekunder
  // Lagrer 'mod' for mer oversiktlig kode
  int mod = time % 8000;
  if(mod < 3000) {
    // De første 3 sekundene skrur alle lampene på én etter en    
    resetAll();
    // En fordel med array-systemet er kode som dette:
    for(int i = 0; i < 6; i++) {
      if(mod % 3000 > 500*i) {
        digitalWrite(LED[i], HIGH);
      }
    }
  }
  else if(mod < 5000) {
    // De neste 2 sekundene veksler annenhver LED mellom på og av
    if(mod % 2000 < 400) {
      digitalWrite(LED_1, HIGH);
      digitalWrite(LED_2, LOW);
      digitalWrite(LED_3, HIGH);
      digitalWrite(LED_4, LOW);
      digitalWrite(LED_5, HIGH);
      digitalWrite(LED_6, LOW);
    }
    else if(mod % 2000 < 800) {
      digitalWrite(LED_1, LOW);
      digitalWrite(LED_2, HIGH);
      digitalWrite(LED_3, LOW);
      digitalWrite(LED_4, HIGH);
      digitalWrite(LED_5, LOW);
      digitalWrite(LED_6, HIGH);
    }
    else if(mod % 2000 < 1200) {
      digitalWrite(LED_1, HIGH);
      digitalWrite(LED_2, LOW);
      digitalWrite(LED_3, HIGH);
      digitalWrite(LED_4, LOW);
      digitalWrite(LED_5, HIGH);
      digitalWrite(LED_6, LOW);
    }
    else if(mod % 2000 < 1600) {
      digitalWrite(LED_1, LOW);
      digitalWrite(LED_2, HIGH);
      digitalWrite(LED_3, LOW);
      digitalWrite(LED_4, HIGH);
      digitalWrite(LED_5, LOW);
      digitalWrite(LED_6, HIGH);
    }
    else {
      digitalWrite(LED_1, HIGH);
      digitalWrite(LED_2, LOW);
      digitalWrite(LED_3, HIGH);
      digitalWrite(LED_4, LOW);
      digitalWrite(LED_5, HIGH);
      digitalWrite(LED_6, LOW);
    }
  }
  else if(mod < 7000) {
    // De neste 2 sekundene gjør bølgen med alle LED-ene 4 ganger
    int nMod = mod % 2000;
    
    if(nMod < 500) {
      resetAll();
      int egg = nMod % 500;
      if(egg < 83) {
        digitalWrite(LED_1, HIGH);
      }
      else if(egg < 167) {
        digitalWrite(LED_2, HIGH);
      }
      else if(egg < 250) {
        digitalWrite(LED_3, HIGH);
      }
      else if(egg < 333) {
        digitalWrite(LED_4, HIGH);
      }
      else if(egg < 417) {
        digitalWrite(LED_5, HIGH);
      }
      else {
        digitalWrite(LED_6, HIGH);
      }
    }
    else if(nMod < 1000) {
      resetAll();
      int egg = nMod % 500;
      if(egg < 83) {
        digitalWrite(LED_6, HIGH);
      }
      else if(egg < 167) {
        digitalWrite(LED_5, HIGH);
      }
      else if(egg < 250) {
        digitalWrite(LED_4, HIGH);
      }
      else if(egg < 333) {
        digitalWrite(LED_3, HIGH);
      }
      else if(egg < 417) {
        digitalWrite(LED_2, HIGH);
      }
      else {
        digitalWrite(LED_1, HIGH);
      }
    }
    else if(nMod < 1500) {
      resetAll();
      int egg = nMod % 500;
      if(egg < 83) {
        digitalWrite(LED_1, HIGH);
      }
      else if(egg < 167) {
        digitalWrite(LED_2, HIGH);
      }
      else if(egg < 250) {
        digitalWrite(LED_3, HIGH);
      }
      else if(egg < 333) {
        digitalWrite(LED_4, HIGH);
      }
      else if(egg < 417) {
        digitalWrite(LED_5, HIGH);
      }
      else {
        digitalWrite(LED_6, HIGH);
      }
    }
    else {
      resetAll();
      int egg = nMod % 500;
      if(egg < 83) {
        digitalWrite(LED_6, HIGH);
      }
      else if(egg < 167) {
        digitalWrite(LED_5, HIGH);
      }
      else if(egg < 250) {
        digitalWrite(LED_4, HIGH);
      }
      else if(egg < 333) {
        digitalWrite(LED_3, HIGH);
      }
      else if(egg < 417) {
        digitalWrite(LED_2, HIGH);
      }
      else {
        digitalWrite(LED_1, HIGH);
      }
    }
  }
  else {
    // Det siste sekundet er alle LEDs av
    resetAll();
  }
}

// Skrevet av: Isak
void mode4() {
  resetAll();
  
  if(time % 1000 < 400) {
        digitalWrite(LED_1, LOW);
        digitalWrite(LED_2, HIGH);
        digitalWrite(LED_3, LOW);
        digitalWrite(LED_4, HIGH);
        digitalWrite(LED_5, LOW);
        digitalWrite(LED_6, HIGH);
    }
    else if(time % 1000 < 750) {
        digitalWrite(LED_1, HIGH);
        digitalWrite(LED_2, LOW);
        digitalWrite(LED_3, HIGH);
        digitalWrite(LED_4, LOW);
        digitalWrite(LED_5, HIGH);
        digitalWrite(LED_6, LOW);
    }
    else if(time % 1000 < 800) {
        digitalWrite(LED_1, LOW);
        digitalWrite(LED_2, LOW);
        digitalWrite(LED_3, LOW);
        digitalWrite(LED_4, LOW);
        digitalWrite(LED_5, HIGH);
        digitalWrite(LED_6, HIGH);
    }
    else if(time % 1000 < 850) {
        digitalWrite(LED_1, HIGH);
        digitalWrite(LED_2, HIGH);
        digitalWrite(LED_3, LOW);
        digitalWrite(LED_4, LOW);
        digitalWrite(LED_5, LOW);
        digitalWrite(LED_6, LOW);
    }
    else if(time % 1000 < 900) {
        digitalWrite(LED_1, LOW);
        digitalWrite(LED_2, LOW);
        digitalWrite(LED_3, HIGH);
        digitalWrite(LED_4, HIGH);
        digitalWrite(LED_5, LOW);
        digitalWrite(LED_6, LOW);
    }
}

// Skrevet av: Audun
void mode5() {
  // Bølgen
  
    //1
  if (time % 1200 < 0) {
    digitalWrite (LED_6, HIGH);
    digitalWrite (LED_5, LOW);
    digitalWrite (LED_4, LOW);
    digitalWrite (LED_3, LOW);
    digitalWrite (LED_2, LOW);
    digitalWrite (LED_1, LOW);
    }
    //2
  else if (time % 1200 < 100) {
    digitalWrite (LED_6, LOW);
    digitalWrite (LED_5, HIGH);
    digitalWrite (LED_4, LOW);
    digitalWrite (LED_3, LOW);
    digitalWrite (LED_2, LOW);
    digitalWrite (LED_1, LOW);
    } 
    //3
   else if (time % 1200 < 200) {
    digitalWrite (LED_6, LOW);
    digitalWrite (LED_5, LOW);
    digitalWrite (LED_4, HIGH);
    digitalWrite (LED_3, LOW);
    digitalWrite (LED_2, LOW);
    digitalWrite (LED_1, LOW);
    }
    //4
   else if (time % 1200 < 300) {
    digitalWrite (LED_6, LOW);
    digitalWrite (LED_5, LOW);
    digitalWrite (LED_4, LOW);
    digitalWrite (LED_3, HIGH);
    digitalWrite (LED_2, LOW);
    digitalWrite (LED_1, LOW);
    }
    //5
   else if (time % 1200 < 400) {
    digitalWrite (LED_6, LOW);
    digitalWrite (LED_5, LOW);
    digitalWrite (LED_4, LOW);
    digitalWrite (LED_3, LOW);
    digitalWrite (LED_2, HIGH);
    digitalWrite (LED_1, LOW);
    }
    //6
   else if (time % 1200 < 500) {
    digitalWrite (LED_6, LOW);
    digitalWrite (LED_5, LOW);
    digitalWrite (LED_4, LOW);
    digitalWrite (LED_3, LOW);
    digitalWrite (LED_2, HIGH);
    digitalWrite (LED_1, LOW);
    }
    //7
   else if (time % 1200 < 600) {
    digitalWrite (LED_6, LOW);
    digitalWrite (LED_5, LOW);
    digitalWrite (LED_4, LOW);
    digitalWrite (LED_3, LOW);
    digitalWrite (LED_2, LOW);
    digitalWrite (LED_1, HIGH);
    }
    //8
   else if (time % 1200 < 700) {
    digitalWrite (LED_6, LOW);
    digitalWrite (LED_5, LOW);
    digitalWrite (LED_4, LOW);
    digitalWrite (LED_3, LOW);
    digitalWrite (LED_2, HIGH);
    digitalWrite (LED_1, LOW);
    }
    //9
   else if (time % 1200 < 800) {
    digitalWrite (LED_6, LOW);
    digitalWrite (LED_5, LOW);
    digitalWrite (LED_4, LOW);
    digitalWrite (LED_3, HIGH);
    digitalWrite (LED_2, LOW);
    digitalWrite (LED_1, LOW);
    }
    //10
   else if (time % 1200 < 900) {
    digitalWrite (LED_6, LOW);
    digitalWrite (LED_5, LOW);
    digitalWrite (LED_4, HIGH);
    digitalWrite (LED_3, LOW);
    digitalWrite (LED_2, LOW);
    digitalWrite (LED_1, LOW);
    }
    //11
   else if (time % 1200 < 1000) {
    digitalWrite (LED_6, LOW);
    digitalWrite (LED_5, HIGH);
    digitalWrite (LED_4, LOW);
    digitalWrite (LED_3, LOW);
    digitalWrite (LED_2, LOW);
    digitalWrite (LED_1, LOW);
    }
    //12
   else if (time % 1200 < 1100) {
    digitalWrite (LED_6, HIGH);
    digitalWrite (LED_5, LOW);
    digitalWrite (LED_4, LOW);
    digitalWrite (LED_3, LOW);
    digitalWrite (LED_2, LOW);
    digitalWrite (LED_1, LOW);
    }
}


// Variabler til bruk i modes som krever randomness
long randomnumber = 1;
bool randSwitch = true;

// Skrevet av: Christopher
void mode6() {
  // Skrur på en tilfeldig lampe hvert 400. millisekund
  
  if(time % 400 < 200) {
    if(randSwitch == true) {
      randomnumber = random(0, 6);
      randSwitch = false;
    }
  }
  else {
    randSwitch = true;
  }
  
  // Skru av alle
  resetAll();
  
  digitalWrite(LED[randomnumber], HIGH);

}

// Skrevet av: Isak
void mode7() {
      //1
  if (time % 600 < 0) {
    digitalWrite (LED_6, HIGH);
    digitalWrite (LED_5, LOW);
    digitalWrite (LED_4, LOW);
    digitalWrite (LED_3, LOW);
    digitalWrite (LED_2, LOW);
    digitalWrite (LED_1, LOW);
    }
    //2
  else if (time % 600 < 50) {
    digitalWrite (LED_6, LOW);
    digitalWrite (LED_5, LOW);
    digitalWrite (LED_4, LOW);
    digitalWrite (LED_3, LOW);
    digitalWrite (LED_2, LOW);
    digitalWrite (LED_1, HIGH);
    } 
    //3
   else if (time % 600 < 100) {
    digitalWrite (LED_6, LOW);
    digitalWrite (LED_5, HIGH);
    digitalWrite (LED_4, LOW);
    digitalWrite (LED_3, LOW);
    digitalWrite (LED_2, LOW);
    digitalWrite (LED_1, LOW);
    }
    //4
   else if (time % 600 < 150) {
    digitalWrite (LED_6, LOW);
    digitalWrite (LED_5, LOW);
    digitalWrite (LED_4, LOW);
    digitalWrite (LED_3, LOW);
    digitalWrite (LED_2, HIGH);
    digitalWrite (LED_1, LOW);
    }
    //5
   else if (time % 600 < 200) {
    digitalWrite (LED_6, LOW);
    digitalWrite (LED_5, LOW);
    digitalWrite (LED_4, HIGH);
    digitalWrite (LED_3, LOW);
    digitalWrite (LED_2, LOW);
    digitalWrite (LED_1, LOW);
    }
    //6
   else if (time % 600 < 250) {
    digitalWrite (LED_6, LOW);
    digitalWrite (LED_5, LOW);
    digitalWrite (LED_4, LOW);
    digitalWrite (LED_3, HIGH);
    digitalWrite (LED_2, LOW);
    digitalWrite (LED_1, LOW);
    }
    //7
   else if (time % 600 < 300) {
    digitalWrite (LED_6, LOW);
    digitalWrite (LED_5, LOW);
    digitalWrite (LED_4, HIGH);
    digitalWrite (LED_3, LOW);
    digitalWrite (LED_2, LOW);
    digitalWrite (LED_1, LOW);
    }
    //8
   else if (time % 600 < 350) {
    digitalWrite (LED_6, LOW);
    digitalWrite (LED_5, LOW);
    digitalWrite (LED_4, LOW);
    digitalWrite (LED_3, LOW);
    digitalWrite (LED_2, HIGH);
    digitalWrite (LED_1, LOW);
    }
    //9
   else if (time % 600 < 400) {
    digitalWrite (LED_6, LOW);
    digitalWrite (LED_5, HIGH);
    digitalWrite (LED_4, LOW);
    digitalWrite (LED_3, LOW);
    digitalWrite (LED_2, LOW);
    digitalWrite (LED_1, LOW);
    }
    //10
   else if (time % 600 < 450) {
    digitalWrite (LED_6, LOW);
    digitalWrite (LED_5, LOW);
    digitalWrite (LED_4, LOW);
    digitalWrite (LED_3, LOW);
    digitalWrite (LED_2, LOW);
    digitalWrite (LED_1, HIGH);
    }
    //11
   else if (time % 600 < 500) {
    digitalWrite (LED_6, HIGH);
    digitalWrite (LED_5, LOW);
    digitalWrite (LED_4, LOW);
    digitalWrite (LED_3, LOW);
    digitalWrite (LED_2, LOW);
    digitalWrite (LED_1, LOW);
    }
    //12
   else if (time % 600 < 550) {
    resetAll();
   }
}


void loop()
{
  // Lagrer millis() i 'time' for convenience
  time = millis();

  // Leser verdien i ledningen fra knappen
  // Hvis det er strøm i knappen ble den trykket ned
  int btnVal = digitalRead(BTN_PIN);
  // Endrer bare mode dersom vi ikke allerede har gjort det på dette 'trykket'
  if(btnVal == HIGH && !trykketForrige) {
    mode++; // Øker 'mode' med 1
    // Lagrer at vi har trykket for å unngår å endre mode flere ganger
    trykketForrige = true;
    if(mode >= NUM_MODES)mode = 0;
  }
  else if(btnVal == LOW) {
    // Klar for å registrere nye klikk
    trykketForrige = false;
  }
  
  
  // Bestemmer hva vi gjør utifra hvilken verdi 'mode' har
  if(mode == 0) {
    mode0();
  }
  else if(mode == 1) {
    mode1();
  }
  else if(mode == 2) {
    mode2();
  }
  else if(mode == 3) {
    mode3();
  }
  else if(mode == 4) {
    mode4();
  }
  else if(mode == 5) {
    mode5();
  }
  else if(mode == 6) {
    mode6();
  }
  else if(mode == 7) {
    mode7();
  }
}
