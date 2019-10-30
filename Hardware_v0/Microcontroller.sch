EESchema Schematic File Version 4
LIBS:io-master-cache
EELAYER 30 0
EELAYER END
$Descr B 17000 11000
encoding utf-8
Sheet 2 11
Title "MICROCONTROLLER SUBSYSTEM"
Date "2019-10-30"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_ST_STM32H7:STM32H743VITx U?
U 1 1 5DA7E3F9
P 7000 5500
F 0 "U?" H 7000 2611 50  0000 C CNN
F 1 "STM32H743VITx" H 7000 2520 50  0000 C CNN
F 2 "Package_QFP:LQFP-100_14x14mm_P0.5mm" H 6300 2900 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/DM00387108.pdf" H 7000 5500 50  0001 C CNN
	1    7000 5500
	1    0    0    -1  
$EndComp
Text Notes 4500 1000 0    98   ~ 0
STM32 MICROCONTROLLER
Text Notes 10750 1000 0    98   ~ 0
VOLTAGE-CONTROLLED OSCILLATOR (VCO)
Wire Notes Line
	10250 500  10250 10500
Text Notes 1000 1000 0    98   ~ 0
USB 2.0 TRANSCEIVER
Wire Notes Line
	4000 500  4000 10500
$EndSCHEMATC
