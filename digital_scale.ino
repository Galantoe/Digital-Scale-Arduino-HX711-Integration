#include <HX711_ADC.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <HX711_ADC.h> 
#include <EEPROM.h>

// 1. Pin Definitions
const int LOADCELL_DOUT_PIN = 4; 
const int LOADCELL_SCK_PIN = 5;  
const int TARE_BUTTON_PIN = 3;   

// 2. Initialize Objects
HX711_ADC scale(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2);

float calibration_factor = 13098.62; 

// --- SETUP RUNS ONCE ---
void setup() {
  Serial.begin(9600);
  pinMode(TARE_BUTTON_PIN, INPUT_PULLUP);
  
  lcd.init();
  lcd.backlight();
  
  scale.begin();
  
  // Handle EEPROM Storage
  float storedFactor;
  EEPROM.get(0, storedFactor);
  if (isnan(storedFactor) || storedFactor == 0) {
    EEPROM.put(0, calibration_factor);
  } else {
    calibration_factor = storedFactor;
  }

  // Startup the scale
  unsigned long stabilizingtime = 2000; 
  scale.start(stabilizingtime, true); 
  scale.setCalFactor(calibration_factor); 

  // Setup Screen
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("A.E.A");
}

// --- LOOP RUNS FOREVER ---
void loop() {
  static unsigned long lastUpdate;
  
  // This must run constantly to process data
  scale.update();

  // Check Tare Button
  if (digitalRead(TARE_BUTTON_PIN) == LOW) {
    scale.tareNoDelay();
    delay(200); // Simple debounce
  }

  // Update Display every 250 milliseconds
  if (millis() > lastUpdate + 250) {
    float weight = scale.getData();
    
    // Zero-out noise
    if (weight < 0.05 && weight > -0.05) weight = 0.00;

    // Format string: 6 wide, 2 decimal places
    char weightString[9]; 
    dtostrf(weight, 6, 2, weightString);

    // Write to LCD (Right aligned)
    lcd.setCursor(8, 1); 
    lcd.print(weightString);
    lcd.print("kg");

    // Mirror to Serial
    Serial.print("Weight: ");
    Serial.println(weightString);
    
    lastUpdate = millis();
  }
}