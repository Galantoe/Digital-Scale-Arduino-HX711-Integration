# Digital-Scale-Arduino-HX711-Integration-Instructional

A high-resolution weighing system using an Arduino Nano and 24-bit HX711 ADC to interface with a load cell. It features a streamlined I2C LCD interface, hardware-debounced Tare function, and EEPROM-based calibration for measurement persistence. Developed with a custom Proteus schematic for advanced hardware simulation.

---
<img width="1920" height="1032" alt="image" src="https://github.com/user-attachments/assets/2e8b13d4-d1ac-4537-b5aa-a8b38fdcff7b" />

## 🛠️ Components List
* **Microcontroller**: Arduino Nano V3.
* **ADC**: Raw HX711 IC (integrated into the schematic for simulation compatibility).
* **Sensor**: Load Cell (Wheatstone Bridge).
* **Display Interface**: PCF8574 I2C Expander.
* **Display**: 16x2 Parallel LCD (LM016L).
* **External Components**: 
    * **2N4403 PNP Transistor**: Used for HX711 voltage regulation.
    * **4.7kΩ I2C Pull-up Resistors**: Essential for SDA/SCL communication.
    * **Tactile Push Button**: For the Tare function.
    * **Capacitors**: Various 0.1uF and 10uF for signal filtering.

---

## 🔬 Simulation vs. Real-World Configuration

### Proteus Simulation (Raw IC)
In this simulation, we use the **raw HX711 IC** because the common "green breakout board" module is not natively available in the standard Proteus library. This requires a more complex analog configuration to manage the excitation voltage for the load cell.

### Real-World Hardware (Module)
Using a pre-built HX711 module in real life is much simpler. The module simplifies the connection to four main terminals:
1. **Load Cell to Module**: Connect the four wires to **E+**, **E-**, **A+**, and **A-**.
2. **Power**: VCC to 5V and GND to Arduino Ground.
3. **Data Interface**: Connect **DT (Data)** to Nano pin **D4** and **SCK (Clock)** to Nano pin **D5**.

> [!IMPORTANT]  
> **Common Ground**: Ensure a shared ground reference between the Arduino, the HX711, and the LCD I2C backpack. Without a common ground, the digital signals will be unstable and the display may show "ghost" characters.

---

## ⚖️ Calibration Guide

### What is the Calibration Factor?
The `calibration_factor` is a mathematical constant used to translate raw electrical fluctuations from the HX711 into a weight value in kilograms. Because every load cell has slight manufacturing differences, you must find your specific factor before the scale is accurate.

### How to Calibrate:
1. **Flash Calibration Sketch**: Upload a basic calibration sketch (e.g., `calibfactor.ino`) to your Arduino and run the sketch.
2. **Zero the Scale**: Ensure nothing is on the load cell.
3. **Use a Known Weight**: Place an object of a strictly known weight (e.g., a 1kg dumbbell or a specific 5kg weight) on the scale.
4. **Input the Value**: Write in the value of the known weight on your serial monitor and the calibration Factor will be provided on the monitor.
5. **Update Main Code**: Copy this final value into the `calibration_factor` variable in the `digital_scale.ino` file.

---

## 📝 Usage Instructions
* **Startup**: The display shows **"A.E.A"** while the scale stabilizes for 2 seconds.
* **Persistence**: The code automatically retrieves the last saved calibration factor from **EEPROM**.
* **Tare Function**: Press the physical button on **Pin D3** to reset the scale to **0.00kg**.

---
