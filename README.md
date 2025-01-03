# Lost-and-Found Management System

## Overview
This project is a **Lost-and-Found Management System** designed to help individuals and organizations efficiently track and recover lost items. 
It utilizes **RFID technology** for item identification and a **GSM module** for real-time SMS notifications.
The system is user-friendly, cost-effective, and scalable for various applications.

---

## Features
- **RFID Integration**: Detects and identifies items using unique RFID tags.
- **GSM Module**: Sends SMS notifications to item owners when their items are found.
- **LCD Display**: Displays the process and information for user convenience.
- **Buzzer Alerts**: Audible alerts for unregistered items.
- **Expandable**: Can be scaled to include IoT functionalities.

---

## Hardware Components
- Arduino Uno R3
- MFRC522 RFID Module
- SIM900A GSM Module (with external power supply)
- I2C LCD Display
- Buzzer
- Push Button (Switch)
- Power Supply (External for GSM module)

---

## Pin Configuration
| Component         | Pin Name         | Arduino Pin         |
|--------------------|------------------|---------------------|
| **RFID Module**    | RST             | 9                   |
|                    | SS              | 10                  |
|                    | MOSI            | 11 (SPI)            |
|                    | MISO            | 12 (SPI)            |
|                    | SCK             | 13 (SPI)            |
| **GSM Module**     | RX (to GSM TX)  | 2                   |
|                    | TX (to GSM RX)  | 3                   |
| **Buzzer**         | Positive (+)    | 7                   |
| **Switch**         | One Terminal    | 8                   |
| **I2C LCD**        | SDA             | A4 (on Uno)         |
|                    | SCL             | A5 (on Uno)         |

---

## Software Requirements
- **Arduino IDE**
- Required Libraries:
  - `MFRC522`
  - `LiquidCrystal_I2C`
  - `SPI` (Pre-installed with Arduino IDE)
  - `Wire` (Pre-installed with Arduino IDE)
  - `SoftwareSerial` (Pre-installed with Arduino IDE)

---

## Setup and Usage
1. **Hardware Assembly**:
   - Connect all components as per the pin configuration table.
   - Ensure the GSM module is powered externally.

2. **Library Installation**:
   - Open Arduino IDE.
   - Install required libraries via **Tools > Manage Libraries**.

3. **Upload Code**:
   - Open the provided code file in Arduino IDE.
   - Select the correct board and port.
   - Upload the code to the Arduino Uno.

4. **Test the System**:
   - Power up the system.
   - Scan RFID tags and observe system responses on the LCD and via SMS.

---

## Achievements
- Developed a fully functional prototype showcased at the **Techno Fair**.
- Integrated multiple technologies (RFID, GSM, LCD) seamlessly.
- Designed a user-friendly interface for practical applications.

---

## Future Scope
- Integration with mobile apps for enhanced user experience.
- GPS tracking for precise location of items.
- Broader applications in airports, schools, and offices.

---

## Credits
- Thondamalla SARWAN - System Design and Hardware Integration
- Software Development and Coding
- Testing and Debugging
- Documentation and Presentation

### **Acknowledgments**
- **Mentor/Guide Name**: For guidance and support throughout the project.
- **Institution Name**: For providing the platform and resources.

### **Libraries Used**
- **MFRC522 Library**: [GitHub Repository](https://github.com/miguelbalboa/rfid)
- **LiquidCrystal_I2C Library**: [GitHub Repository](https://github.com/johnrickman/LiquidCrystal_I2C)
- **SPI Library**: Pre-installed with Arduino IDE.
- **Wire Library**: Pre-installed with Arduino IDE.
- **SoftwareSerial Library**: Pre-installed with Arduino IDE.

---

## Contact
If you have any questions or feedback, feel free to reach out to us through GitHub !
