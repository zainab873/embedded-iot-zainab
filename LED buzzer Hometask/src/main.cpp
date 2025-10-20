<<<<<<< HEAD
// PWM Example – 2 LED Brightness Fade and buzzer Tones


//Zainab Sultan 
// 23-NTU-CS-1097
// LED ESP32 WORKING CODE
#include <Arduino.h>

// ---------------- BUZZER SETUP ----------------
#define BUZZER_PIN   27    // GPIO connected to buzzer
#define PWM_CH_BUZZ  0     // PWM channel for buzzer
#define FREQ_BUZZ    2000  // Default frequency (Hz)
#define RES_BUZZ     10    // 10-bit resolution (0–1023)

// ---------------- LED SETUP ----------------
#define LED_PIN1     18    // First LED
#define LED_PIN2     5     // Second LED
#define PWM_CH_LED1  1     // Channel for LED 1
#define PWM_CH_LED2  2     // Channel for LED 2
#define FREQ_LED     5000  // Frequency for LEDs
#define RES_LED      8     // 8-bit resolution (0–255)

void setup() {
  // --- Setup for Buzzer ---
  ledcSetup(PWM_CH_BUZZ, FREQ_BUZZ, RES_BUZZ);
  ledcAttachPin(BUZZER_PIN, PWM_CH_BUZZ);

  // --- Setup for LEDs ---
  ledcSetup(PWM_CH_LED1, FREQ_LED, RES_LED);
  ledcSetup(PWM_CH_LED2, FREQ_LED, RES_LED);
  ledcAttachPin(LED_PIN1, PWM_CH_LED1);
  ledcAttachPin(LED_PIN2, PWM_CH_LED2);
}

void loop() {
  // ---------------- BUZZER SECTION ----------------

  // 1. Simple beep pattern
  for (int i = 0; i < 3; i++) {
    ledcWriteTone(PWM_CH_BUZZ, 2000 + i * 400); // change tone
    delay(50);
    ledcWrite(PWM_CH_BUZZ, 0);                  // stop tone
    delay(50);
  }

  // 2. Frequency sweep (400Hz → 3kHz)
  for (int f = 400; f <= 3000; f += 100) {
    ledcWriteTone(PWM_CH_BUZZ, f);
    delay(20);
  }
  ledcWrite(PWM_CH_BUZZ, 0);
  delay(50);

  // 3. Short melody
  int melody[] = {262, 294, 330, 349, 392, 440, 494, 523};
  for (int i = 0; i < 8; i++) {
    ledcWriteTone(PWM_CH_BUZZ, melody[i]);
    delay(50);
  }
  ledcWrite(PWM_CH_BUZZ, 0); // stop buzzer

  // ---------------- LED SECTION ----------------

  // Fade both LEDs up and down together
  for (int d = 0; d <= 255; d++) { 
    ledcWrite(PWM_CH_LED1, d);
    ledcWrite(PWM_CH_LED2, d);
    delay(10);
  }
  for (int d = 255; d >= 0; d--) { 
    ledcWrite(PWM_CH_LED1, d);
    ledcWrite(PWM_CH_LED2, d);
    delay(10);
  }

  // When loop() ends, it restarts — both buzzer and LED effects repeat
}
=======
//Zainab Sultan 
//23-NTU-CS-1097
// two led and one buzzer attach to esp 32 via breadboard



#include <Arduino.h>

// ---------------- BUZZER SETUP ----------------
#define BUZZER_PIN   27    // GPIO connected to buzzer
#define PWM_CH_BUZZ  0     // PWM channel for buzzer
#define FREQ_BUZZ    2000  // Default frequency (Hz)
#define RES_BUZZ     10    // 10-bit resolution (0–1023)

// ---------------- LED SETUP ----------------
#define LED_PIN1     18    // First LED
#define LED_PIN2     5     // Second LED
#define PWM_CH_LED1  1     // Channel for LED 1
#define PWM_CH_LED2  2     // Channel for LED 2
#define FREQ_LED     5000  // Frequency for LEDs
#define RES_LED      8     // 8-bit resolution (0–255)

void setup() {
  // --- Setup for Buzzer ---
  ledcSetup(PWM_CH_BUZZ, FREQ_BUZZ, RES_BUZZ);
  ledcAttachPin(BUZZER_PIN, PWM_CH_BUZZ);

  // --- Setup for LEDs ---
  ledcSetup(PWM_CH_LED1, FREQ_LED, RES_LED);
  ledcSetup(PWM_CH_LED2, FREQ_LED, RES_LED);
  ledcAttachPin(LED_PIN1, PWM_CH_LED1);
  ledcAttachPin(LED_PIN2, PWM_CH_LED2);
}

void loop() {
  // ---------------- BUZZER SECTION ----------------

  // 1. Simple beep pattern
  for (int i = 0; i < 3; i++) {
    ledcWriteTone(PWM_CH_BUZZ, 2000 + i * 400); // change tone
    delay(50);
    ledcWrite(PWM_CH_BUZZ, 0);                  // stop tone
    delay(50);
  }

  // 2. Frequency sweep (400Hz → 3kHz)
  for (int f = 400; f <= 3000; f += 100) {
    ledcWriteTone(PWM_CH_BUZZ, f);
    delay(20);
  }
  ledcWrite(PWM_CH_BUZZ, 0);
  delay(50);

  // 3. Short melody
  int melody[] = {262, 294, 330, 349, 392, 440, 494, 523};
  for (int i = 0; i < 8; i++) {
    ledcWriteTone(PWM_CH_BUZZ, melody[i]);
    delay(50);
  }
  ledcWrite(PWM_CH_BUZZ, 0); // stop buzzer

  // ---------------- LED SECTION ----------------

  // Fade both LEDs up and down together
  for (int d = 0; d <= 255; d++) { 
    ledcWrite(PWM_CH_LED1, d);
    ledcWrite(PWM_CH_LED2, d);
    delay(10);
  }
  for (int d = 255; d >= 0; d--) { 
    ledcWrite(PWM_CH_LED1, d);
    ledcWrite(PWM_CH_LED2, d);
    delay(10);
  }

  // When loop() ends, it restarts — both buzzer and LED effects repeat
}

>>>>>>> b29d852673804ac3d057f39bde64ecd5eb49feb2
