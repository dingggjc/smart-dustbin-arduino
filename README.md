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

## 🔧 Setup
1. Upload `src/smart_dustbin.ino` to Arduino
2. Connect sensors:
   - Ultrasonic: Trig=12, Echo=11
   - Moisture: A0
   - Servo: Pin 8

## 📁 Files
- `src/smart_dustbin.ino` - Main Arduino code
