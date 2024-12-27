# Smart-Room
Design of a smart room using a light dependent resistor (photoresistor), a passive infrared sensor, and a temperature sensor

![Screenshot (28)](https://github.com/user-attachments/assets/2acb3928-47e4-4eae-a33c-5c2cb32922d9)
Simulation using Proteus

### Components Used

Arduino Board  
PIR Sensor  
LDR Sensor  
Temperature Sensor (DHT11)  
2 LEDs  
1 Motor  
Motor Driver (L293D)  
Resistors

The arduino is used as the microcontroller. The PIR sensor detects motion in the room. If it is ON i.e if it detects motion, the room light switches ON, represented by the red LED in my simulation. The fan represented by a motor switches ON when the temperature sensor reads that the room temperature is above 35 degrees Celsius. Otherwise, it is OFF. The LDR checks how bright it is outside so that when it gets dark enough, it turns ON the red LED which represents a light outside the house like the security light.
