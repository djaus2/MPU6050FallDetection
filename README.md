# MPU6050 Fall Detection

## About
Arduino sketch to detect a fall based pitch and roll tilt calculations using the MPU6050 accelerometer.

## Algorithm

Start
- Set fallcount = 0;

Loop
- Calculate Pitch and Roll
- If Pitch or Roll are greater than triggers
  - Increment fallcount
  - If fallcount > largetrigger
    - Report fallen on ground
  - Else if fallcount > medium trigger
    - Report has fallen
  - Else report falen
- Else if fallcount >0
  - Report Stumble
  - Set fallcount = 0
