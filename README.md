# Mobile-Controlled-Home
The project I worked on is a Mobile Controlled Home. Using an ATMEGA32 microcontroller, it enables you to control various aspects of your home through a mobile phone application via Bluetooth.

The project has the following features:
1. Login system using a keypad to enter user ID and password.
2. Lights control [ON - OFF - Control].
3. Door control [Opened - Closed].
4. Fan control [ON - OFF - Control].
5. Alarm time.
6. Emergency button.

The following components were used in this project:
- MCU: Atmega32
- Hardware: CLCD, Keypad, LED, BUZZER, LDR, DC Motor, Servo Motor, Ultrasonic, Bluetooth Module
- MCU Peripherals: Timer, ICU, ADC, Interrupt, USART

Here are some notes to keep in mind while using the application:
1.  You can start the system at any time using the keypad.
2.  The system supports 10 users with different IDs and passwords.
3.  You must enter the correct ID.
4.  In case of entering the password incorrectly 3 times, the system will give an alarm.
5.  Most of the system can work in parallel.
6.  The selected feature will be displayed on the LCD.
7.  Lights are represented as an LED array.
8.  The LED array is controlled by mapping the LDR sensor output voltage level to the number of ON LEDs.
9.  The door is represented as a servo motor with two opposite positions (ability to manage servo motor with two angles).
10. The fan is represented as a DC motor.
11. The fan is controlled by mapping the output distance from the ultrasonic to PWM signal.
12. You can hear the alarm sound.
13. You can stop the system at any time using the keypad.

The project specifications are as follows:
1. Using ADC peripheral to measure the output voltage from the LDR sensor and turning LED array based on the value.
2. Using Timer1 to generate Fast PWM to communicate with the Servo Motor, moving it by modifying compare match value (On Time).
3. Using ultrasonic, change fan speed depends on measured distance using ultrasonic.
4. Using USART peripheral to communicate with the Bluetooth module.
5. Using External Interrupt peripheral to set Emergency button.

The following tools were used in this project:
1. Eclipse
2. Proteus
3. A mobile phone application that i created using App Inventor to control your smart home
