EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:MCP9808-E_MS
LIBS:TemperatureSensor-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCP9808-E/MS U1
U 1 1 583B81F7
P 5350 3300
F 0 "U1" H 4760 3720 50  0000 L CNN
F 1 "MCP9808-E/MS" H 4750 2830 50  0000 L CNN
F 2 "MCP9808-E_MS:SOP65P490X110-8N" H 5350 3300 50  0001 L CNN
F 3 "Microchip" H 5350 3300 50  0001 L CNN
F 4 "1.02 USD" H 5350 3300 50  0001 L CNN "Price"
F 5 "Good" H 5350 3300 50  0001 L CNN "Availability"
F 6 "MSOP-8 Microchip" H 5350 3300 50  0001 L CNN "Package"
F 7 "MCP9808-E/MS" H 5350 3300 50  0001 L CNN "MP"
F 8 "MCP9808 Series SMD 3.6 V Memory Module Digital Temperature Sensor - MSOP-8" H 5350 3300 50  0001 L CNN "Description"
	1    5350 3300
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 583B8314
P 2700 3350
F 0 "R1" V 2780 3350 50  0000 C CNN
F 1 "10K" V 2700 3350 50  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 2630 3350 50  0000 C CNN
F 3 "" H 2700 3350 50  0000 C CNN
	1    2700 3350
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 583B8385
P 2950 3350
F 0 "R2" V 3030 3350 50  0000 C CNN
F 1 "10K" V 2950 3350 50  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 2880 3350 50  0000 C CNN
F 3 "" H 2950 3350 50  0000 C CNN
	1    2950 3350
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 583B83D8
P 3800 2650
F 0 "R3" V 3880 2650 50  0000 C CNN
F 1 "10K" V 3800 2650 50  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 3730 2650 50  0000 C CNN
F 3 "" H 3800 2650 50  0000 C CNN
	1    3800 2650
	0    -1   -1   0   
$EndComp
$Comp
L R R4
U 1 1 583B842C
P 3800 2450
F 0 "R4" V 3880 2450 50  0000 C CNN
F 1 "10K" V 3800 2450 50  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 3730 2450 50  0000 C CNN
F 3 "" H 3800 2450 50  0000 C CNN
	1    3800 2450
	0    -1   -1   0   
$EndComp
$Comp
L R R5
U 1 1 583B8485
P 3800 2250
F 0 "R5" V 3880 2250 50  0000 C CNN
F 1 "10K" V 3800 2250 50  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 3730 2250 50  0000 C CNN
F 3 "" H 3800 2250 50  0000 C CNN
	1    3800 2250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2950 3500 4550 3500
Wire Wire Line
	2700 3500 2700 3600
Wire Wire Line
	2700 3600 4550 3600
Wire Wire Line
	6150 3600 6300 3600
Wire Wire Line
	6300 3600 6300 3700
Wire Wire Line
	6300 3000 6150 3000
$Comp
L C C1
U 1 1 583B92D4
P 7250 3200
F 0 "C1" H 7275 3300 50  0000 L CNN
F 1 "1uF" H 7275 3100 50  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 7288 3050 50  0000 C CNN
F 3 "" H 7250 3200 50  0000 C CNN
	1    7250 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	7250 3350 7250 3650
Wire Wire Line
	6150 3300 6600 3300
Text Label 4100 3600 0    60   ~ 0
SDA
Text Label 4100 3500 0    60   ~ 0
SCL
Wire Wire Line
	3650 2650 3650 2800
Wire Wire Line
	3650 2450 3450 2450
Wire Wire Line
	3450 2450 3450 2800
Wire Wire Line
	3650 2250 3250 2250
Wire Wire Line
	3250 2250 3250 2800
$Comp
L CONN_01X08 P1
U 1 1 583BA9E7
P 5500 4650
F 0 "P1" H 5500 5100 50  0000 C CNN
F 1 "CONN_01X08" V 5600 4650 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Angled_1x08" H 5500 4650 50  0000 C CNN
F 3 "" H 5500 4650 50  0000 C CNN
	1    5500 4650
	1    0    0    -1  
$EndComp
Text Label 4250 5350 0    60   ~ 0
VDD
Text GLabel 5000 4300 0    60   Input ~ 0
VDD
Text GLabel 5000 4400 0    60   Input ~ 0
GND
Text GLabel 5000 4500 0    60   Input ~ 0
SCL
Text GLabel 5000 4600 0    60   Input ~ 0
SDA
Text GLabel 5000 4700 0    60   Input ~ 0
ALERT
Text GLabel 5000 4800 0    60   Input ~ 0
A0
Text GLabel 5000 4900 0    60   Input ~ 0
A1
Text GLabel 5000 5000 0    60   Input ~ 0
A2
Wire Wire Line
	5000 4300 5300 4300
Wire Wire Line
	5000 4400 5300 4400
Wire Wire Line
	5000 4500 5300 4500
Wire Wire Line
	5000 4600 5300 4600
Wire Wire Line
	5000 4700 5300 4700
Wire Wire Line
	5000 4800 5300 4800
Wire Wire Line
	5300 4900 5000 4900
Wire Wire Line
	5000 5000 5300 5000
Text GLabel 2950 2750 1    60   Input ~ 0
VDD
Text GLabel 2600 2750 1    60   Input ~ 0
VDD
Text GLabel 6300 2300 1    60   Input ~ 0
VDD
Text GLabel 7250 2300 1    60   Input ~ 0
VDD
Wire Wire Line
	6300 2300 6300 3000
Wire Wire Line
	7250 2300 7250 3050
Wire Wire Line
	2950 2750 2950 3200
Wire Wire Line
	2600 2750 2600 3200
Wire Wire Line
	2600 3200 2700 3200
Text GLabel 6300 3700 3    60   Input ~ 0
GND
Text GLabel 3650 2800 3    60   Input ~ 0
GND
Text GLabel 3450 2800 3    60   Input ~ 0
GND
Text GLabel 3250 2800 3    60   Input ~ 0
GND
Text GLabel 6600 3300 2    60   Input ~ 0
ALERT
Text GLabel 7250 3650 3    60   Input ~ 0
GND
Wire Wire Line
	4550 3100 4550 2250
Wire Wire Line
	4550 2250 3950 2250
Wire Wire Line
	4550 3200 4400 3200
Wire Wire Line
	4400 3200 4400 2450
Wire Wire Line
	4400 2450 3950 2450
Wire Wire Line
	3950 2650 4100 2650
Wire Wire Line
	4100 2650 4100 3300
Wire Wire Line
	4100 3300 4550 3300
Text GLabel 4100 3300 0    60   Input ~ 0
A2
Text GLabel 4400 2450 1    60   Input ~ 0
A1
Text GLabel 4550 2250 1    60   Input ~ 0
A0
$EndSCHEMATC
