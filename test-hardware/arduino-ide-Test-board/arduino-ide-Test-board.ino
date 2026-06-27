/*
   PENS Expansion Board V2.0
   Full Hardware Test
   Arduino Mega 2560
*/

// =======================
// LED ARRAY
// =======================
const byte leds[] = {
  22, 23, 24, 25,
  26, 27, 28, 29
};

// =======================
// LED INDIKATOR
// =======================
#define LED_RED   12
#define LED_GREEN 13

// =======================
// BUZZER PASIF
// =======================
#define BUZZER 11

// =======================
// BUTTON
// =======================
#define BTN1 10
#define BTN2 9
#define BTN3 8
#define BTN4 7

// =======================
// ANALOG
// =======================
#define POT1 A0
#define POT2 A1
#define LDR  A2

// =================================================
// BUZZER TEST
// =================================================
void testBuzzer()
{
  Serial.println("=== BUZZER TEST ===");

  int melody[] = {
    262, 294, 330, 349,
    392, 440, 494, 523
  };

  for (int i = 0; i < 8; i++) {
    tone(BUZZER, melody[i]);
    delay(200);
  }

  noTone(BUZZER);
  delay(300);
}

// =================================================
// LED TEST
// =================================================
void testLED()
{
  Serial.println("=== LED TEST ===");

  for (int i = 0; i < 8; i++) {
    digitalWrite(leds[i], HIGH);
    delay(100);
    digitalWrite(leds[i], LOW);
  }

  digitalWrite(LED_RED, HIGH);
  delay(300);
  digitalWrite(LED_RED, LOW);

  digitalWrite(LED_GREEN, HIGH);
  delay(300);
  digitalWrite(LED_GREEN, LOW);
}

// =================================================
// PORTA COUNTER
// =================================================
void testCounter()
{
  Serial.println("=== PORTA COUNTER ===");

  for (int n = 0; n < 256; n++) {

    for (int b = 0; b < 8; b++) {
      digitalWrite(leds[b], bitRead(n, b));
    }

    delay(25);
  }

  for (int i = 0; i < 8; i++) {
    digitalWrite(leds[i], LOW);
  }
}

// =================================================
// BUTTON TEST
// =================================================
void testButton()
{
  Serial.println("=== BUTTON TEST ===");
  Serial.println("Tekan tombol selama 10 detik");

  unsigned long t0 = millis();

  while (millis() - t0 < 10000) {

    if (!digitalRead(BTN1)) {
      Serial.println("BTN1");
      tone(BUZZER, 500);
      digitalWrite(LED_RED, HIGH);
    }

    else if (!digitalRead(BTN2)) {
      Serial.println("BTN2");
      tone(BUZZER, 1000);
      digitalWrite(LED_GREEN, HIGH);
    }

    else if (!digitalRead(BTN3)) {
      Serial.println("BTN3");
      tone(BUZZER, 1500);

      for (int i = 0; i < 8; i++)
        digitalWrite(leds[i], HIGH);
    }

    else if (!digitalRead(BTN4)) {
      Serial.println("BTN4");
      tone(BUZZER, 2000);

      for (int i = 0; i < 8; i++)
        digitalWrite(leds[i], i & 1);
    }

    else {
      noTone(BUZZER);

      digitalWrite(LED_RED, LOW);
      digitalWrite(LED_GREEN, LOW);

      for (int i = 0; i < 8; i++)
        digitalWrite(leds[i], LOW);
    }

    delay(50);
  }

  noTone(BUZZER);
}

// =================================================
// ANALOG TEST
// =================================================
void testAnalog()
{
  Serial.println("=== ANALOG TEST ===");

  for (int i = 0; i < 30; i++) {

    int p1 = analogRead(POT1);
    int p2 = analogRead(POT2);
    int l  = analogRead(LDR);

    Serial.print("POT1=");
    Serial.print(p1);

    Serial.print("  POT2=");
    Serial.print(p2);

    Serial.print("  LDR=");
    Serial.println(l);

    delay(200);
  }
}

void setup()
{
  Serial.begin(115200);

  for (int i = 0; i < 8; i++) {
    pinMode(leds[i], OUTPUT);
  }

  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);

  pinMode(BUZZER, OUTPUT);

  pinMode(BTN1, INPUT_PULLUP);
  pinMode(BTN2, INPUT_PULLUP);
  pinMode(BTN3, INPUT_PULLUP);
  pinMode(BTN4, INPUT_PULLUP);

  delay(1000);

  Serial.println();
  Serial.println("PENS Expansion Board V2.0");
  Serial.println("Hardware Self Test");
}

void loop()
{
  testLED();

  testBuzzer();

  testButton();

  testAnalog();

  testCounter();

  Serial.println("===== TEST COMPLETE =====");
  delay(2000);
}