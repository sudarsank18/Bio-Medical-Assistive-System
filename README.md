# BIO-MEDICAL ASISTIVE SYSTEM
This system uses Node-Mcu and integrating flex sensors into gloves and a strap to monitor hand movements and spinal posture respectively. 
A pulse sensor will also be incorporated to track pulse rate.
The system will enable users to communicate basic needs and emergencies through simple hand movements, trigger predefined messages, and activate an emergency alert mechanism when necessary.

### TOOLS USED
• **HARDWARE**: Breadboard, Jumper wires, Single strand wires, 1K ohm Resistor, ADC Converter, 5v Battery
• **SOFTWARE**: Arduino IDE v.2.2.1, Blynk
• **BOARD**: Node MCU Esp - 8266
• **SENSOR**: Flex sensor, Pulse sensor (HW-827), Accelerometer (ADXL-345)

### Connectivity:
#### 1. Flex sensor:
• Pin2 to 3.3V pin on the Node-MCU board.
• Pin1 to GND pin on the Node-MCU board using 1k ohm resistor in serial
connection.
• Pin1 to analog pin on ADC converter
#### 2. Pulse sensor:
• + to 3.3V pin on the Node-MCU Board
• - to GND pin on the Node-MCU Board
• S to Analog pin on the Node-MCU Board
#### 3. Accelerometer sensor:
• VCC to 3.3V pin on the Node-MCU Board
• GND to GND pin on the Node-MCU Board`
• SDA to D2 on the Node-MCU Board
• SCL to D1 on the Node-MCU Board
#### 4. ADC (ADS 1115):
• VCC to 3.3V pin on the Node-MCU Board
• GND to GND pin on the Node-MCU Board
• SDA to D2 on the Node-MCU Board
• SCL to D1 on the Node-MCU Board
