/*Author: Alexej Beňuš xbenus01*/
#include <Adafruit_SSD1306.h>
#include <AiEsp32RotaryEncoder.h>
#include <Arduino.h>
#include <Adafruit_VL53L0X.h>
#include <SPI.h>

/*
-- Menu --
1. Measure
2. Change units

-- Change units --
1. cm
2. in
*/

/*Proměnné pro práci s rotorem*/
#define ROTARY_ENCODER_A_PIN 35
#define ROTARY_ENCODER_B_PIN 34
#define ROTARY_ENCODER_BUTTON_PIN 13
#define ROTARY_ENCODER_VCC_PIN -1 
#define ROTARY_ENCODER_STEPS 4
AiEsp32RotaryEncoder rotaryEncoder = AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, ROTARY_ENCODER_BUTTON_PIN, ROTARY_ENCODER_VCC_PIN, ROTARY_ENCODER_STEPS);

/*Proměnné pro práci s displejem a měřičem*/
#define LED_W 128 
#define LED_H 64
uint16_t displayUnit = 0; // 0 - cm, 1 - inch
int position; // 0 - menu, 1 - measurement, 2 - changing values
Adafruit_SSD1306 display(LED_W, LED_H, &Wire, -1);
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

/**
 * @brief Funkce pro vypsání menu na displej
 */
void menu()
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 00);
  display.println("1 Mereni vzdalenosti");
  display.setCursor(0, 10);
  display.println("2 Zmena jednotky");
  display.setCursor(0, 30);
  display.println("Volba:");
  display.println(rotaryEncoder.readEncoder()+1);
  display.display();
}

/**
 * @brief Funkce pro vypsání menu pro změnu jednotek měření
 */
void changeUnits()
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("1 Milimetry");
  display.setCursor(0, 10);
  display.println("2 Palce");
  display.setCursor(0, 30);
  display.println("Volba:");
  display.print(rotaryEncoder.readEncoder()+1);
  display.display();
}

/**
 * @brief Funkce pro měření milimetrů, podle globální proměnenné displayUnit bude vypisovat cm nebo palce
 */
void measure()
{
  display.setTextSize(3);
  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false);

  if (measure.RangeStatus != 4) {
      display.clearDisplay();
      display.setCursor(0,0);
      float measured = measure.RangeMilliMeter;
      if(displayUnit == 0) // přepis změřených mm do cm a palců
      {
        float cm = measured/10;
        display.print(cm, 1);
        display.print("cm");
      }
      else
      {
        float inch = measured/25.4;
        display.print(inch, 1);
        display.print("in");
      }
      display.display();
      Serial.println();
      delay(50);
  } else {
    display.display();
    display.clearDisplay();
    return;
  }
}

/**
 * @brief Funkce pro implementaci stistknutí rotačního enkóderu
 */
void rotary_onButtonClick()
{
  static unsigned long lastTimePressed = 0;
  if (millis() - lastTimePressed < 500) //  pro ošetření více zmáčknutí za sebou
  {
    return;
  }
  
  if(position == 0) // přepnutí aplikace do jiné nabídky
  {
    if(rotaryEncoder.readEncoder() == 0)
    {
      Serial.println("pozice 1");
      position = 1;
    }
    if(rotaryEncoder.readEncoder() == 1)
    {
      Serial.println("pozice 2");
      position = 2;
    }
  }
  else if(position == 1)
  {
    position = 0; 
  }
  else if(position == 2)
  {
    displayUnit = rotaryEncoder.readEncoder();
    position = 0;
  }
  
  lastTimePressed = millis();
  Serial.print("button pressed ");
  Serial.print(millis());
  Serial.println(" milliseconds after restart");
}

/**
 * @brief Funkce pro kontrolu změn na enkóderu
 */
void rotary_loop()
{
  if (rotaryEncoder.encoderChanged()) // pokud se změní pozice enkóderu, vypiš na serial
  {
    Serial.print("Value: ");
    Serial.println(rotaryEncoder.readEncoder());
  }
  if (rotaryEncoder.isEncoderButtonClicked()) // pokud se stiskne enkóder, zavolej funkci
  {
    rotary_onButtonClick();
  }
}

/**
 * @brief Funkce pro čtení z enkóderu
 */
void IRAM_ATTR readEncoderISR()
{
  rotaryEncoder.readEncoder_ISR();
}

/**
 * @brief Funkce pro začátek práce s deskou, inicializace enkóderu a displeje
 */
void setup() {
  Serial.begin(115200);

  // Inicializace enkóderu
  rotaryEncoder.begin();
  rotaryEncoder.setup(readEncoderISR);
  rotaryEncoder.setBoundaries(0, 1, true);
  rotaryEncoder.setAcceleration(1);

  // Inicializace displeje
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(1000);
  Wire.begin();

  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
}

/**
 * @brief Halvní nekonečná smyčka programu, volá funkce podle nastavení enkóderu
 */
void loop() {
  rotary_loop();
  //Serial.println(position);
  if(position == 0)
  {
    menu();
  }
  if(position == 1)
  {
    measure();  
  }
  if(position == 2)
  {
    changeUnits();
  }
}
