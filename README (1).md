# ⚡ EV Wireless Charging System with RFID Authentication

An Arduino-based Electric Vehicle (EV) wireless charging control system that uses RFID card authentication to authorize and manage charging sessions — with real-time status display on an LCD screen.

---

## 📌 Overview

This project implements a smart, access-controlled EV charging station prototype. When an authorized RFID card is tapped, the system activates the wireless charging module and displays the session status on a 16×2 I2C LCD. Unauthorized cards are denied access immediately.

This is ideal for college projects, IoT prototypes, or smart EV infrastructure demonstrations.

---

## 🎯 Features

- 🔐 **RFID-based Authentication** — Only authorized cards/tags can start a charging session
- 📟 **16×2 LCD Display** — Real-time feedback: Authorized, Charging Started, Charging Ended, Access Denied
- ⚡ **Relay-controlled Charging** — Controls the wireless charging module via a digital output pin
- 🔁 **Automatic Reset** — Returns to idle state after each session
- 🖥️ **Serial Monitor Logging** — UID and access status logged for debugging

---

## 🛠️ Hardware Requirements

| Component | Quantity |
|---|---|
| Arduino Uno / Nano | 1 |
| MFRC522 RFID Reader Module | 1 |
| RFID Card / Key Fob | 1+ |
| 16×2 I2C LCD (address 0x27) | 1 |
| Relay Module (5V) | 1 |
| Wireless Charging Module (Tx + Rx coils) | 1 set |
| Jumper Wires | As needed |
| Breadboard / PCB | 1 |
| Power Supply (5V) | 1 |

---

## 🔌 Circuit Connections

### MFRC522 RFID → Arduino

| MFRC522 Pin | Arduino Pin |
|---|---|
| SDA (SS) | 10 |
| SCK | 13 |
| MOSI | 11 |
| MISO | 12 |
| RST | 9 |
| GND | GND |
| 3.3V | 3.3V |

### I2C LCD → Arduino

| LCD Pin | Arduino Pin |
|---|---|
| SDA | A4 |
| SCL | A5 |
| VCC | 5V |
| GND | GND |

### Relay Module → Arduino

| Relay Pin | Arduino Pin |
|---|---|
| IN | Pin 8 |
| VCC | 5V |
| GND | GND |

> The relay output controls the wireless charging transmitter coil circuit.

---

## 💻 Software Requirements

- [Arduino IDE](https://www.arduino.cc/en/software) (v1.8+ or v2.x)
- Libraries (install via Arduino Library Manager):
  - `MFRC522` by GithubCommunity
  - `LiquidCrystal_I2C` by Frank de Brabander
  - `SPI` (built-in)
  - `Wire` (built-in)

---

## 🚀 Getting Started

### 1. Clone the Repository

```bash
git clone https://github.com/indubumesh04-beep/EV_wireless_charging.git
cd EV_wireless_charging
```

### 2. Install Required Libraries

In Arduino IDE: **Sketch → Include Library → Manage Libraries**

Search and install:
- `MFRC522`
- `LiquidCrystal_I2C`

### 3. Find Your RFID Card UID

Upload the code, open Serial Monitor (9600 baud), and tap your RFID card. Note the UID printed (e.g., `B3 8B 7B C9`).

### 4. Update the Authorized UID

In `ev_wireless_charging.ino`, locate this line and replace with your card's UID:

```cpp
if (content.substring(1) == "B3 8B 7B C9")
```

### 5. Upload and Run

- Connect Arduino via USB
- Select the correct **Board** and **Port** in Arduino IDE
- Click **Upload**
- Open Serial Monitor to view logs

---

## 📋 How It Works

```
Power ON
   │
   ▼
Display "EV Charging System" on LCD
   │
   ▼
Wait for RFID Card...
   │
   ├── Authorized Card? ──YES──► Display "Authorized"
   │                                   │
   │                             Display "Charging Started"
   │                                   │
   │                             Relay ON (Pin 8 LOW) → Charging begins
   │                                   │
   │                             Wait (configurable delay)
   │                                   │
   │                             Relay OFF (Pin 8 HIGH) → Charging ends
   │                                   │
   │                             Display "Charging Ended"
   │                                   │
   └── Unauthorized? ──NO───► Display "Access Denied"
                                       │
                               Return to idle screen
```

---

## ⚙️ Configuration

You can customize the following in the code:

```cpp
// Charging duration (in milliseconds)
delay(10000);  // Default: 10 seconds → change as needed

// Relay output pin
#define RELAY_PIN 8

// LCD I2C address (default 0x27, try 0x3F if LCD doesn't work)
LiquidCrystal_I2C lcd(0x27, 16, 2);
```

---

## 📁 Project Structure

```
EV_wireless_charging/
│
└── ev_wireless_charging.ino    # Main Arduino sketch
```

---

## 🔮 Future Enhancements

- [ ] Add multiple authorized RFID cards support
- [ ] Integrate IoT (ESP8266/ESP32) for remote monitoring
- [ ] Add a power/energy meter to track kWh consumed per session
- [ ] Mobile app integration for session history
- [ ] OTA (Over-the-Air) UID management

---

## 🧑‍💻 Author

**Indubumesh**
- GitHub: [@indubumesh04-beep](https://github.com/indubumesh04-beep)

---

## 📄 License

This project is open source and available under the [MIT License](LICENSE).

---

## 🙏 Acknowledgements

- [MFRC522 Library](https://github.com/miguelbalboa/rfid) by Miguel Balboa
- [LiquidCrystal_I2C Library](https://github.com/johnrickman/LiquidCrystal_I2C) by Frank de Brabander
- Arduino Community for documentation and support
