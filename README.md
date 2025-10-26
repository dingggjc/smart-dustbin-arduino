# Smart Dustbin - Automatic Waste Segregation System

An intelligent dustbin that automatically detects and segregates wet and dry waste using Arduino.

## 🚀 Features
- Automatic object detection with ultrasonic sensor
- Wet/dry classification using moisture sensor
- Servo-controlled compartment opening
- Real-time Serial monitoring

## 📋 Components
- Arduino Uno
- HC-SR04 Ultrasonic Sensor  
- Soil Moisture Sensor
- SG90 Servo Motor

## 🚀 Quick Start

1. **Hardware Setup**
   - Connect HC-SR04: Trig=12, Echo=11, VCC=5V, GND=GND
   - Connect Moisture Sensor: SIG=A0, VCC=5V, GND=GND  
   - Connect Servo: Signal=8, VCC=5V, GND=GND

2. **Software Setup**
   - Install [Arduino IDE](https://www.arduino.cc/en/software)
   - Open `src/smart_dustbin.ino`
   - Select: **Tools → Board → Arduino Uno**
   - Select correct COM port
   - Click **Upload**

3. **Calibration** (Important!)
   - Test moisture sensor with dry and wet items
   - Adjust `wetWasteThreshold` in code if needed
   - Default: <600 = Wet, ≥600 = Dry

## 🐛 Troubleshooting

- **Servo not moving?** Check power supply
- **False triggers?** Adjust `ultrasonicDistanceCM` 
- **Wrong waste detection?** Calibrate moisture threshold

## 📁 Files
- `src/smart_dustbin.ino` - Main Arduino code
