# AE-Course-Project
# Arduino-Based Digital Multimeter

An open-source Arduino project for measuring **resistance**, **voltage**, **current**, and **capacitance** using simple components and an LCD display. This project is ideal for students, electronics hobbyists, and makers looking to build a low-cost, functional multimeter using Arduino.

## 🚀 Features

- Measure:
  - Resistance (Ohmmeter)
  - Voltage (Voltmeter)
  - Current (Ammeter)
  - Capacitance (Capacitance Meter)
- LCD Interface for easy display and navigation
- Button-controlled menu to switch between modes
- Supports both microfarad and nanofarad ranges for capacitors
- Compact and simple hardware design

## 🧰 Components Used

- Arduino Uno or compatible board  
- 16x2 I2C LCD display  
- Resistors (reference resistors for measurement)  
- Capacitors (for testing)  
- ACS712 current sensor  
- Tactile push buttons  
- Breadboard and jumper wires  
- Power supply or USB

## 🛠️ How It Works

Each measurement mode uses standard electrical principles:
- **Resistance**: Voltage divider method with known resistors
- **Voltage**: Voltage divider circuit for safe analog input
- **Current**: ACS712 Hall-effect current sensor
- **Capacitance**: RC charging time with analog read

## 📁 Code Structure

- `main.ino`: The complete Arduino sketch for measurement and LCD handling
- Functions:
  - `calculate_resistor()`
  - `calculate_voltage()`
  - `calculate_current()`
  - `calculate_capacitance()`

## 🔧 Setup

1. Clone this repository or download the `.ino` file.
2. Open the file in the Arduino IDE.
3. Connect components as described in the circuit diagram (to be uploaded).
4. Upload to your Arduino board.
5. Use the push buttons to navigate the menu and select measurement modes.

## 📷 Preview

![Multimeter UI on LCD](link-to-your-image-if-any)

## 📊 Example Output

| Parameter     | Sample Reading | Actual Value |
|---------------|----------------|---------------|
| Resistance    | 998 Ω           | 1 kΩ           |
| Voltage       | 4.94 V          | 5.00 V         |
| Current       | 148.7 mA        | 150 mA         |
| Capacitance   | 98.2 µF         | 100 µF         |

## 🔮 Future Improvements

- Auto-ranging support
- AC measurement capability
- Data logging to SD card
- Bluetooth/Mobile app integration
- Graphical user interface

## 📜 License

This project is open-source and available under the [MIT License](LICENSE).

## 🙌 Acknowledgements

Thanks to the contributors, educators, and open-source community for providing libraries and guidance to make this project possible.

---

Feel free to fork, modify, and share this project!

