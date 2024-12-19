# SMART-STREET-LIGHT-MONITORING-AND-CONTROLLING-SYSTEM

## Project Overview

This project presents an **IoT-powered Smart Street Lighting System** designed to reduce energy consumption by automatically turning on streetlights only when necessary. By incorporating motion and light detection sensors, this system ensures optimal lighting conditions, providing both energy efficiency and enhanced safety.

---

## Team Members

- **Aniket Maurya** (UI21EC10)
- **Ankit Kumar** (UI21EC12)
- **Ashwani Kumar** (UI21EC18)

---

## Components Used

1. **ESP8266 NodeMCU**  
   A low-cost Wi-Fi microcontroller used for connecting the system to the internet for real-time monitoring.

2. **IR Sensors**  
   Infrared sensors detect motion and obstacles in the surrounding area, ensuring the streetlight turns on only when someone is passing by.

3. **LDR Sensor (Light Dependent Resistor)**  
   Detects ambient light conditions. The streetlight turns on only when the light levels are low (nighttime).

4. **LEDs**  
   Represent streetlights and are controlled based on motion detection and light intensity.

5. **Micro USB Cable**  
   Used to power the NodeMCU.

6. **Jumper Wires**  
   For connecting the components to the NodeMCU and other parts of the circuit.

---

## Working

1. **Light Detection:**  
   The **LDR sensor** detects the ambient light level. If the light level is below a certain threshold (indicating it's nighttime), the system moves to the next step of checking for motion.

2. **Motion Detection:**  
   The **IR sensors** are placed along the street to detect movement. When a person or vehicle crosses the sensor's path, the corresponding **LED (streetlight)** is turned on.

3. **Data Monitoring:**  
   The system uploads the data from the **LDR sensor** and **IR sensors** to **ThingSpeak**, an IoT cloud platform, allowing real-time monitoring of the system.

4. **Control via Web Interface:**  
   The system also includes a web interface that allows users to control the streetlights remotely over the internet.

5. **Energy Efficiency:**  
   The lights remain off during the day or when no motion is detected, significantly saving energy compared to traditional streetlights.

---

## Features

- **Energy Efficient:** The system ensures streetlights only turn on when necessary, reducing unnecessary energy consumption.
- **Real-time Monitoring:** The data is uploaded to ThingSpeak, enabling remote monitoring of the streetlight conditions.
- **Web Interface:** Allows users to control and check the status of the streetlights from anywhere with an internet connection.

---

## Conclusion

This project successfully demonstrates an IoT-based solution for smart street lighting. By utilizing motion and light sensors, the system provides energy-efficient and automated street lighting that can be monitored and controlled remotely. The project can be further enhanced by integrating renewable energy sources and expanding the control system for multiple units.

---

## Future Enhancements

1. **Integration with Solar Panels:** To make the system more sustainable by using solar energy for powering the streetlights.
2. **Advanced Motion Sensors:** Incorporating more accurate sensors to detect motion in a broader area and reduce false triggers.
3. **Centralized Control:** Developing a system to manage multiple streetlight units across larger areas or cities.

---

## How to Use

1. Clone this project to your local machine:
   ```bash
   git clone https://github.com/ANKIT-12GU/SMART-STREET-LIGHT-MONITORING-AND-CONTROLLING-SYSTEM.git
