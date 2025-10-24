Zainab Sultan
23-NTU-CS-FL-2097

TASK A - WOKWI link

https://wokwi.com/projects/445485546359644161

TASK A -PINMAP

| Component | Pin |    Direction    | Description                                 |
| --------- | :-: | :-------------: | ------------------------------------------- |
| LED1      |  23 |      Output     | Part of LED mode display (Blink / ON / OFF) |
| LED2      |  19 |      Output     | Part of LED mode display (Alternate blink)  |
| LED3      |  17 |    PWM Output   | Used for PWM fade mode                      |
| Button1   |  14 | Input (Pull-up) | Mode change button                          |
| Button2   |  13 | Input (Pull-up) | Reset to OFF mode                           |
| OLED SDA  |  21 |     I2C Data    | Communication with OLED                     |
| OLED SCL  |  22 |    I2C Clock    | Communication with OLED                     |
| GND       |  —  |      Ground     | Common ground for components                |
| 3.3V      |  —  |      Power      | Power for OLED                              |

**SHORT DESCRIPTION FOR TASK A**

This project uses two buttons and three LEDs with an OLED display to show the current mode.
Pressing Button1 cycles through four display modes:
1️ Both OFF
2️ Alternate Blinking
3️ Both ON
4️ PWM Fade effect
Pressing Button2 resets back to Mode 0 (All OFF).

TASK A -- SCREENSHOT
![WhatsApp Image 2025-10-24 at 21 17 38_52c1430c](https://github.com/user-attachments/assets/cc587e04-9d1a-4a27-8093-05f4af549225)

![WhatsApp Image 2025-10-24 at 21 05 57_ee1a9d2f](https://github.com/user-attachments/assets/463a33f6-0649-4555-9842-4094fd138783)


************************************************************************************************
******************************************   TASK B   ******************************************
************************************************************************************************
TASK B - WOKWI link

https://wokwi.com/projects/445711469091759105

TASK B -PIN MAP

| Component | Pin |    Direction    | Description                         |
| --------- | :-: | :-------------: | ----------------------------------- |
| LED1      |  23 |      Output     | Indicates short-press toggle ON/OFF |
| Button1   |  14 | Input (Pull-up) | Detects short vs long press         |
| Buzzer    |  27 |    PWM Output   | Plays tone on long button press     |
| OLED SDA  |  21 |     I2C Data    | OLED communication                  |
| OLED SCL  |  22 |    I2C Clock    | OLED communication                  |
| GND       |  —  |      Ground     | Shared ground for components        |
| 3.3V      |  —  |      Power      | Supplies OLED                       |



**SHORT DESCRIPTION FOR TASK B**

Task B, a single button is used to detect two types of press actions:
 Short press (< 1.5 seconds)
→ Toggles the LED ON/OFF
→ OLED displays "LED ON" or "LED OFF"

 Long press (> 1.5 seconds)
→ Plays a musical buzzer tone
→ OLED displays "BUZZER!" and returns to "READY"

The project uses:
Debounced button press timing
OLED to show feedback
PWM/tone() for buzzer audio

TASK B -- SCREENSHOT

![WhatsApp Image 2025-10-24 at 21 37 40_14370c0b](https://github.com/user-attachments/assets/64db5c2f-4eb6-407d-bf54-3f920b952318)





