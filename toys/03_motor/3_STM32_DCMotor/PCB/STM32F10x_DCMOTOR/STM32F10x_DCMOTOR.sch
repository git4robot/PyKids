EESchema Schematic File Version 4
EELAYER 30 0
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
L DRV8833PW:DRV8833PW IC1
U 1 1 5D6F57F6
P 2200 2050
F 0 "IC1" H 2800 2200 50  0000 C CNN
F 1 "DRV8833PW" H 2800 1200 50  0000 C CNN
F 2 "SOP65P640X120-16N" H 3250 2150 50  0001 L CNN
F 3 "http://www.ti.com/lit/ds/symlink/drv8833.pdf" H 3250 2050 50  0001 L CNN
F 4 "Motor / Motion / Ignition Controllers & Drivers DRV8833 EVAL MOD" H 3250 1950 50  0001 L CNN "Description"
F 5 "1.2" H 3250 1850 50  0001 L CNN "Height"
F 6 "Texas Instruments" H 3250 1750 50  0001 L CNN "Manufacturer_Name"
F 7 "DRV8833PW" H 3250 1650 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "595-DRV8833PW" H 3250 1550 50  0001 L CNN "Mouser Part Number"
F 9 "https://www.mouser.com/Search/Refine.aspx?Keyword=595-DRV8833PW" H 3250 1450 50  0001 L CNN "Mouser Price/Stock"
F 10 "" H 3250 1350 50  0001 L CNN "RS Part Number"
F 11 "" H 3250 1250 50  0001 L CNN "RS Price/Stock"
	1    2200 2050
	1    0    0    -1  
$EndComp
$Comp
L STM32F103RCT6:STM32F103RCT6 IC?
U 1 1 5D6F6F36
P 6300 3550
F 0 "IC?" H 8444 2846 50  0000 L CNN
F 1 "STM32F103RCT6" H 8444 2755 50  0000 L CNN
F 2 "STM32F103RCT6:QFP50P1200X1200X160-64N" H 8250 4050 50  0001 L CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/CD00191185.pdf" H 8250 3950 50  0001 L CNN
F 4 "STM32F103RCT6, 32 bit ARM Cortex M3 Microcontroller 72MHz 256 kB Flash, 48 kB RAM, USB CAN I2C 64-Pin LQFP" H 8250 3850 50  0001 L CNN "Description"
F 5 "1.6" H 8250 3750 50  0001 L CNN "Height"
F 6 "STMicroelectronics" H 8250 3650 50  0001 L CNN "Manufacturer_Name"
F 7 "STM32F103RCT6" H 8250 3550 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "511-STM32F103RCT6" H 8250 3450 50  0001 L CNN "Mouser Part Number"
F 9 "https://www.mouser.com/Search/Refine.aspx?Keyword=511-STM32F103RCT6" H 8250 3350 50  0001 L CNN "Mouser Price/Stock"
F 10 "7141079P" H 8250 3250 50  0001 L CNN "RS Part Number"
F 11 "http://uk.rs-online.com/web/p/products/7141079P" H 8250 3150 50  0001 L CNN "RS Price/Stock"
F 12 "70391008" H 8250 3050 50  0001 L CNN "Allied_Number"
F 13 "http://www.alliedelec.com/stmicroelectronics-stm32f103rct6/70391008/" H 8250 2950 50  0001 L CNN "Allied Price/Stock"
	1    6300 3550
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 5D6FCF9F
P 3750 2250
F 0 "C2" V 3600 2250 50  0000 C CNN
F 1 "2.2uF" V 3900 2250 50  0000 C CNN
F 2 "" H 3788 2100 50  0001 C CNN
F 3 "~" H 3750 2250 50  0001 C CNN
	1    3750 2250
	0    1    1    0   
$EndComp
Wire Wire Line
	3400 2250 3600 2250
$Comp
L power:GND #PWR?
U 1 1 5D6FE6FC
P 4050 2250
F 0 "#PWR?" H 4050 2000 50  0001 C CNN
F 1 "GND" V 4055 2122 50  0000 R CNN
F 2 "" H 4050 2250 50  0001 C CNN
F 3 "" H 4050 2250 50  0001 C CNN
	1    4050 2250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4050 2250 3900 2250
Wire Wire Line
	2000 2250 2200 2250
$Comp
L Device:R R2
U 1 1 5D6FF262
P 1850 2250
F 0 "R2" V 1750 2250 50  0000 C CNN
F 1 "200" V 1950 2250 50  0000 C CNN
F 2 "" V 1780 2250 50  0001 C CNN
F 3 "~" H 1850 2250 50  0001 C CNN
	1    1850 2250
	0    1    1    0   
$EndComp
$Comp
L Device:R R1
U 1 1 5D700EEB
P 1850 2550
F 0 "R1" V 1750 2550 50  0000 C CNN
F 1 "200" V 1950 2550 50  0000 C CNN
F 2 "" V 1780 2550 50  0001 C CNN
F 3 "~" H 1850 2550 50  0001 C CNN
	1    1850 2550
	0    1    1    0   
$EndComp
Wire Wire Line
	2200 2550 2000 2550
$Comp
L power:GND #PWR?
U 1 1 5D703E04
P 1250 2250
F 0 "#PWR?" H 1250 2000 50  0001 C CNN
F 1 "GND" V 1255 2122 50  0000 R CNN
F 2 "" H 1250 2250 50  0001 C CNN
F 3 "" H 1250 2250 50  0001 C CNN
	1    1250 2250
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5D704333
P 1250 2550
F 0 "#PWR?" H 1250 2300 50  0001 C CNN
F 1 "GND" V 1255 2422 50  0000 R CNN
F 2 "" H 1250 2550 50  0001 C CNN
F 3 "" H 1250 2550 50  0001 C CNN
	1    1250 2550
	0    1    1    0   
$EndComp
Wire Wire Line
	1250 2250 1700 2250
Wire Wire Line
	1700 2550 1250 2550
$Comp
L Device:C C3
U 1 1 5D705D1A
P 4000 2450
F 0 "C3" V 3850 2450 50  0000 C CNN
F 1 "10uF" V 4150 2450 50  0000 C CNN
F 2 "" H 4038 2300 50  0001 C CNN
F 3 "~" H 4000 2450 50  0001 C CNN
	1    4000 2450
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5D705D24
P 4300 2450
F 0 "#PWR?" H 4300 2200 50  0001 C CNN
F 1 "GND" V 4305 2322 50  0000 R CNN
F 2 "" H 4300 2450 50  0001 C CNN
F 3 "" H 4300 2450 50  0001 C CNN
	1    4300 2450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4300 2450 4150 2450
Wire Wire Line
	3850 2450 3400 2450
$Comp
L Regulator_Linear:L7805 U?
U 1 1 5D708BAE
P 5850 2800
F 0 "U?" H 5850 3042 50  0000 C CNN
F 1 "L7805" H 5850 2951 50  0000 C CNN
F 2 "" H 5875 2650 50  0001 L CIN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/41/4f/b3/b0/12/d4/47/88/CD00000444.pdf/files/CD00000444.pdf/jcr:content/translations/en.CD00000444.pdf" H 5850 2750 50  0001 C CNN
	1    5850 2800
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Current:ZXCT1109 U?
U 1 1 5D70A135
P 2600 3450
F 0 "U?" H 2880 3496 50  0000 L CNN
F 1 "ZXCT1109" H 2880 3405 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 2600 3450 50  0001 C CNN
F 3 "https://www.diodes.com/assets/Datasheets/ZXCT1107_10.pdf" H 2550 3450 50  0001 C CNN
	1    2600 3450
	1    0    0    -1  
$EndComp
$EndSCHEMATC
