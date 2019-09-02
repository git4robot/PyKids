EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "PositionSensor_AS5600"
Date "2019-08-30"
Rev "Ver1.0"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L AS5600-ASOT:AS5600-ASOT U1
U 1 1 5D693324
P 5600 3800
F 0 "U1" H 5600 4470 50  0000 C CNN
F 1 "AS5600-ASOT" H 5600 4379 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 5600 3800 50  0001 L BNN
F 3 "AS5600-ASOT" H 5600 3800 50  0001 L BNN
F 4 "Rotary Position Sensor 5.5V/3.6V Digital Output 8-Pin SOIC T/R" H 5600 3800 50  0001 L BNN "字段4"
F 5 "Good" H 5600 3800 50  0001 L BNN "字段5"
F 6 "2.55 USD" H 5600 3800 50  0001 L BNN "字段6"
F 7 "SOIC-8 ams" H 5600 3800 50  0001 L BNN "字段7"
F 8 "ams" H 5600 3800 50  0001 L BNN "字段8"
	1    5600 3800
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 5D694B17
P 7000 3650
F 0 "C1" H 7115 3696 50  0000 L CNN
F 1 "100nF" H 7115 3605 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 7038 3500 50  0001 C CNN
F 3 "~" H 7000 3650 50  0001 C CNN
	1    7000 3650
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 5D6964EA
P 7600 3550
F 0 "C2" H 7715 3596 50  0000 L CNN
F 1 "1uF" H 7715 3505 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 7638 3400 50  0001 C CNN
F 3 "~" H 7600 3550 50  0001 C CNN
	1    7600 3550
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5D697F6E
P 4050 3550
F 0 "R1" H 4120 3596 50  0000 L CNN
F 1 "4k7" H 4120 3505 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 3980 3550 50  0001 C CNN
F 3 "~" H 4050 3550 50  0001 C CNN
	1    4050 3550
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5D6991BB
P 4350 3550
F 0 "R2" H 4420 3596 50  0000 L CNN
F 1 "4k7" H 4420 3505 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 4280 3550 50  0001 C CNN
F 3 "~" H 4350 3550 50  0001 C CNN
	1    4350 3550
	1    0    0    -1  
$EndComp
Text GLabel 3200 3300 0    50   Input ~ 0
5V
Text GLabel 3200 3900 0    50   Input ~ 0
SCL
Text GLabel 3200 4000 0    50   Input ~ 0
SDA
Wire Wire Line
	4700 3900 4050 3900
Wire Wire Line
	4050 3700 4050 3900
Connection ~ 4050 3900
Wire Wire Line
	4050 3900 3200 3900
Wire Wire Line
	4350 3700 4350 4000
Wire Wire Line
	3200 4000 4350 4000
Connection ~ 4350 4000
Wire Wire Line
	4350 4000 4700 4000
Wire Wire Line
	3200 3300 4050 3300
Wire Wire Line
	4350 3300 4350 3400
Wire Wire Line
	4050 3400 4050 3300
Connection ~ 4050 3300
Wire Wire Line
	4050 3300 4350 3300
NoConn ~ 4700 3700
NoConn ~ 4700 3800
NoConn ~ 6500 3700
NoConn ~ 8700 2100
Wire Wire Line
	6500 3400 7600 3400
Wire Wire Line
	6500 3500 7000 3500
Wire Wire Line
	7600 4200 7600 3700
Wire Wire Line
	7000 3800 7000 4200
Wire Wire Line
	6500 4200 7000 4200
Connection ~ 7000 4200
Wire Wire Line
	7000 4200 7600 4200
Text GLabel 8450 4450 2    50   Input ~ 0
GND
$Comp
L power:GND #PWR0101
U 1 1 5D69D6EE
P 7600 4650
F 0 "#PWR0101" H 7600 4400 50  0001 C CNN
F 1 "GND" H 7605 4477 50  0000 C CNN
F 2 "" H 7600 4650 50  0001 C CNN
F 3 "" H 7600 4650 50  0001 C CNN
	1    7600 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	7600 4200 7600 4450
Connection ~ 7600 4200
Wire Wire Line
	8450 4450 8050 4450
Connection ~ 7600 4450
Wire Wire Line
	7600 4450 7600 4650
Text GLabel 7250 3150 2    50   Input ~ 0
5V
Wire Wire Line
	7000 3500 7000 3150
Wire Wire Line
	7000 3150 7250 3150
Connection ~ 7000 3500
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5D69F5F4
P 6750 3050
F 0 "#FLG0101" H 6750 3125 50  0001 C CNN
F 1 "PWR_FLAG" H 6750 3223 50  0000 C CNN
F 2 "" H 6750 3050 50  0001 C CNN
F 3 "~" H 6750 3050 50  0001 C CNN
	1    6750 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 3150 6750 3150
Wire Wire Line
	6750 3150 6750 3050
Connection ~ 7000 3150
$Comp
L power:+3.3V #PWR0102
U 1 1 5D6A1034
P 7600 3000
F 0 "#PWR0102" H 7600 2850 50  0001 C CNN
F 1 "+3.3V" H 7615 3173 50  0000 C CNN
F 2 "" H 7600 3000 50  0001 C CNN
F 3 "" H 7600 3000 50  0001 C CNN
	1    7600 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	7600 3000 7600 3150
Connection ~ 7600 3400
$Comp
L power:+5V #PWR0103
U 1 1 5D6A21AF
P 7000 3050
F 0 "#PWR0103" H 7000 2900 50  0001 C CNN
F 1 "+5V" H 7015 3223 50  0000 C CNN
F 2 "" H 7000 3050 50  0001 C CNN
F 3 "" H 7000 3050 50  0001 C CNN
	1    7000 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 3050 7000 3150
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 5D6A37E0
P 8000 3000
F 0 "#FLG0102" H 8000 3075 50  0001 C CNN
F 1 "PWR_FLAG" H 8000 3173 50  0000 C CNN
F 2 "" H 8000 3000 50  0001 C CNN
F 3 "~" H 8000 3000 50  0001 C CNN
	1    8000 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	8000 3000 8000 3150
Wire Wire Line
	8000 3150 7600 3150
Connection ~ 7600 3150
Wire Wire Line
	7600 3150 7600 3400
$Comp
L power:PWR_FLAG #FLG0103
U 1 1 5D6A4FA4
P 8050 4450
F 0 "#FLG0103" H 8050 4525 50  0001 C CNN
F 1 "PWR_FLAG" H 8050 4623 50  0000 C CNN
F 2 "" H 8050 4450 50  0001 C CNN
F 3 "~" H 8050 4450 50  0001 C CNN
	1    8050 4450
	1    0    0    -1  
$EndComp
Connection ~ 8050 4450
Wire Wire Line
	8050 4450 7600 4450
Text GLabel 3050 2800 0    50   Input ~ 0
GND
Text GLabel 3050 2500 0    50   Input ~ 0
5V
Text GLabel 3050 2700 0    50   Input ~ 0
SDA
Text GLabel 3050 2700 0    50   Input ~ 0
SDA
Text GLabel 3050 2700 0    50   Input ~ 0
SDA
Text GLabel 3050 2700 0    50   Input ~ 0
SDA
Text GLabel 3050 2700 0    50   Input ~ 0
SDA
Text GLabel 3050 2700 0    50   Input ~ 0
SDA
Text GLabel 3050 2700 0    50   Input ~ 0
SDA
Text GLabel 3050 2700 0    50   Input ~ 0
SDA
Text GLabel 3050 2600 0    50   Input ~ 0
SCL
Wire Wire Line
	3600 2500 3050 2500
$Comp
L Connector_Generic:Conn_01x04 J1
U 1 1 5D6A9532
P 3800 2600
F 0 "J1" H 3750 2800 50  0000 L CNN
F 1 "Conn_01x04" H 3700 2300 50  0000 L CNN
F 2 "Connector_JST:JST_SH_BM04B-SRSS-TB_1x04-1MP_P1.00mm_Vertical" H 3800 2600 50  0001 C CNN
F 3 "~" H 3800 2600 50  0001 C CNN
	1    3800 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	3050 2600 3600 2600
Wire Wire Line
	3050 2700 3600 2700
Wire Wire Line
	3050 2800 3600 2800
$EndSCHEMATC
