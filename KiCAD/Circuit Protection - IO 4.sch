EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr B 17000 11000
encoding utf-8
Sheet 7 10
Title "CIRCUIT PROTECTION SUBSYSTEM - I/O PIN 4"
Date "2020-02-05"
Rev "A"
Comp "THE UNIVERSITY OF AKRON"
Comment1 "DT18 - I/O MASTER"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Notes 700  800  0    98   ~ 0
OVERVOLTAGE PROTECTION
Text Notes 6250 800  0    98   ~ 0
OVERCURRENT PROTECTION
Wire Wire Line
	8900 5350 8950 5350
Wire Wire Line
	8950 5350 8950 5050
Connection ~ 8950 5350
$Comp
L Device:D D25
U 1 1 5E62CA48
P 9950 5250
F 0 "D25" V 9996 5171 50  0000 R CNN
F 1 "1N4148" V 9905 5171 50  0000 R CNN
F 2 "" H 9950 5250 50  0001 C CNN
F 3 "~" H 9950 5250 50  0001 C CNN
	1    9950 5250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9950 5400 9950 5450
Connection ~ 9950 5450
Wire Wire Line
	9950 5450 9950 5500
Wire Wire Line
	9300 5900 8950 5900
Wire Wire Line
	9600 5900 9950 5900
Wire Wire Line
	8950 5350 8950 5900
Wire Wire Line
	9950 5800 9950 5900
Connection ~ 9950 5900
Wire Wire Line
	9950 5900 10400 5900
Wire Wire Line
	9950 5100 9950 5050
Wire Wire Line
	11350 6450 11350 6500
Connection ~ 11350 6500
Wire Wire Line
	11350 6550 11350 6500
$Comp
L power:GND #PWR095
U 1 1 5E63136C
P 11350 6900
F 0 "#PWR095" H 11350 6650 50  0001 C CNN
F 1 "GND" H 11355 6727 50  0000 C CNN
F 2 "" H 11350 6900 50  0001 C CNN
F 3 "" H 11350 6900 50  0001 C CNN
	1    11350 6900
	1    0    0    -1  
$EndComp
Wire Wire Line
	11350 6850 11350 6900
Wire Wire Line
	11350 6150 11350 6100
Text HLabel 2000 4350 0    50   BiDi ~ 0
IO_4
Text HLabel 15000 4350 2    50   BiDi ~ 0
TARGET_IO_4
$Comp
L io-master:NCV20074 U21
U 1 1 5E62EECD
P 8050 5350
F 0 "U21" H 8050 5200 50  0000 L CNN
F 1 "NCV20074" H 8050 5500 50  0000 L CNN
F 2 "Package_SO:TSSOP-14_4.4x5mm_P0.65mm" H 8000 5450 50  0001 C CNN
F 3 "https://www.onsemi.com/pub/Collateral/NCS20071-D.PDF" H 8100 5550 50  0001 C CNN
	1    8050 5350
	1    0    0    1   
$EndComp
$Comp
L io-master:NCV20074 U21
U 5 1 5E62EEBA
P 8050 5350
F 0 "U21" H 8008 5396 50  0001 L CNN
F 1 "NCV20074" H 8008 5350 50  0001 L CNN
F 2 "Package_SO:TSSOP-14_4.4x5mm_P0.65mm" H 8000 5450 50  0001 C CNN
F 3 "https://www.onsemi.com/pub/Collateral/NCS20071-D.PDF" H 8100 5550 50  0001 C CNN
	5    8050 5350
	1    0    0    -1  
$EndComp
Wire Notes Line
	6000 500  6000 10500
Wire Wire Line
	2000 4350 4000 4350
Wire Wire Line
	4000 4350 4000 4450
Connection ~ 4000 4350
$Comp
L io-master:Q_DUAL_NMOS_DMN63D8LDW Q?
U 1 1 5E62EEB7
P 12150 4450
AR Path="/5DA7F595/5E62EEB7" Ref="Q?"  Part="1" 
AR Path="/5D9F8176/5E62EEB7" Ref="Q?"  Part="1" 
AR Path="/5DAD2F4A/5E62EEB7" Ref="Q15"  Part="1" 
F 0 "Q15" V 12500 4450 50  0000 C CNN
F 1 "DMN63D8LDW" V 12400 4450 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-363_SC-70-6" H 12350 4450 50  0001 C CNN
F 3 "https://www.diodes.com/assets/Datasheets/DMN63D8LDW.pdf" H 12350 4450 50  0001 C CNN
	1    12150 4450
	0    -1   -1   0   
$EndComp
$Comp
L io-master:Q_DUAL_NMOS_DMN63D8LDW Q?
U 2 1 5E62EEBB
P 12850 4450
AR Path="/5DA7F595/5E62EEBB" Ref="Q?"  Part="2" 
AR Path="/5D9F8176/5E62EEBB" Ref="Q?"  Part="2" 
AR Path="/5DAD2F4A/5E62EEBB" Ref="Q15"  Part="2" 
F 0 "Q15" V 13200 4450 50  0000 C CNN
F 1 "DMN63D8LDW" V 13100 4450 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-363_SC-70-6" H 13050 4450 50  0001 C CNN
F 3 "https://www.diodes.com/assets/Datasheets/DMN63D8LDW.pdf" H 13050 4450 50  0001 C CNN
	2    12850 4450
	0    1    -1   0   
$EndComp
Wire Wire Line
	12350 4350 12500 4350
Connection ~ 12500 4350
Wire Wire Line
	12500 4350 12650 4350
Wire Wire Line
	12500 4400 12500 4350
Wire Wire Line
	12150 4650 12150 4750
Wire Wire Line
	12150 4750 12500 4750
Wire Wire Line
	12850 4750 12850 4650
Wire Wire Line
	12500 4750 12500 4700
Connection ~ 12500 4750
Wire Wire Line
	12500 4750 12850 4750
$Comp
L Device:R R165
U 1 1 5E631365
P 12500 4550
F 0 "R165" H 12570 4596 50  0000 L CNN
F 1 "100K" H 12570 4505 50  0000 L CNN
F 2 "" V 12430 4550 50  0001 C CNN
F 3 "~" H 12500 4550 50  0001 C CNN
	1    12500 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	13050 4350 15000 4350
Text HLabel 8000 5000 2    50   Input ~ 0
+15V
Text HLabel 8000 5700 2    50   Input ~ 0
-15V
Wire Wire Line
	7950 5700 7950 5650
Wire Wire Line
	7950 5700 8000 5700
Wire Wire Line
	7950 5050 7950 5000
Wire Wire Line
	7950 5000 8000 5000
$Comp
L Device:R R156
U 1 1 5E60C82D
P 7700 5700
F 0 "R156" H 7750 5750 50  0000 L CNN
F 1 "100K" H 7750 5650 50  0000 L CNN
F 2 "" V 7630 5700 50  0001 C CNN
F 3 "~" H 7700 5700 50  0001 C CNN
	1    7700 5700
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7750 5450 7700 5450
Wire Wire Line
	7700 5450 7700 5550
$Comp
L power:GND #PWR093
U 1 1 5E62EED2
P 7700 5900
F 0 "#PWR093" H 7700 5650 50  0001 C CNN
F 1 "GND" H 7705 5727 50  0000 C CNN
F 2 "" H 7700 5900 50  0001 C CNN
F 3 "" H 7700 5900 50  0001 C CNN
	1    7700 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	7700 5900 7700 5850
$Comp
L Device:R R155
U 1 1 5E62CA3A
P 7500 5450
F 0 "R155" V 7400 5450 50  0000 C CNN
F 1 "10K" V 7500 5450 50  0000 C CNN
F 2 "" V 7430 5450 50  0001 C CNN
F 3 "~" H 7500 5450 50  0001 C CNN
	1    7500 5450
	0    1    -1   0   
$EndComp
Wire Wire Line
	7650 5450 7700 5450
Connection ~ 7700 5450
$Comp
L Device:R R157
U 1 1 5E631372
P 8050 4850
F 0 "R157" V 7950 4850 50  0000 C CNN
F 1 "100K" V 8050 4850 50  0000 C CNN
F 2 "" V 7980 4850 50  0001 C CNN
F 3 "~" H 8050 4850 50  0001 C CNN
	1    8050 4850
	0    1    1    0   
$EndComp
Wire Wire Line
	7900 4850 7700 4850
Wire Wire Line
	7700 4850 7700 5250
Wire Wire Line
	7700 5250 7750 5250
Wire Wire Line
	8200 4850 8400 4850
Wire Wire Line
	8400 4850 8400 5350
Wire Wire Line
	8400 5350 8350 5350
$Comp
L Device:R R154
U 1 1 5E631351
P 7500 5250
F 0 "R154" V 7400 5250 50  0000 C CNN
F 1 "10K" V 7500 5250 50  0000 C CNN
F 2 "" V 7430 5250 50  0001 C CNN
F 3 "~" H 7500 5250 50  0001 C CNN
	1    7500 5250
	0    1    1    0   
$EndComp
Wire Wire Line
	7650 5250 7700 5250
Connection ~ 7700 5250
Wire Wire Line
	8600 5350 8400 5350
Connection ~ 8400 5350
Wire Wire Line
	7300 5250 7350 5250
Wire Wire Line
	6900 5450 7350 5450
$Comp
L io-master:NCV20074 U21
U 2 1 5E631356
P 9450 5450
F 0 "U21" H 9450 5300 50  0000 L CNN
F 1 "NCV20074" H 9450 5600 50  0000 L CNN
F 2 "Package_SO:TSSOP-14_4.4x5mm_P0.65mm" H 9400 5550 50  0001 C CNN
F 3 "https://www.onsemi.com/pub/Collateral/NCS20071-D.PDF" H 9500 5650 50  0001 C CNN
	2    9450 5450
	1    0    0    1   
$EndComp
Wire Wire Line
	9150 5350 8950 5350
$Comp
L Device:R R158
U 1 1 5E631357
P 8750 5350
F 0 "R158" V 8650 5350 50  0000 C CNN
F 1 "100K" V 8750 5350 50  0000 C CNN
F 2 "" V 8680 5350 50  0001 C CNN
F 3 "~" H 8750 5350 50  0001 C CNN
	1    8750 5350
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR094
U 1 1 5E63136D
P 9100 5600
F 0 "#PWR094" H 9100 5350 50  0001 C CNN
F 1 "GND" H 9105 5427 50  0000 C CNN
F 2 "" H 9100 5600 50  0001 C CNN
F 3 "" H 9100 5600 50  0001 C CNN
	1    9100 5600
	1    0    0    -1  
$EndComp
Wire Wire Line
	9150 5550 9100 5550
Wire Wire Line
	9100 5550 9100 5600
Wire Wire Line
	9750 5450 9950 5450
$Comp
L Device:R R159
U 1 1 5E63136E
P 9450 5050
F 0 "R159" V 9350 5050 50  0000 C CNN
F 1 "100K" V 9450 5050 50  0000 C CNN
F 2 "" V 9380 5050 50  0001 C CNN
F 3 "~" H 9450 5050 50  0001 C CNN
	1    9450 5050
	0    1    1    0   
$EndComp
Wire Wire Line
	9600 5050 9950 5050
Connection ~ 9950 5050
Wire Wire Line
	9300 5050 8950 5050
$Comp
L Device:R R160
U 1 1 5E631368
P 9450 5900
F 0 "R160" V 9350 5900 50  0000 C CNN
F 1 "100K" V 9450 5900 50  0000 C CNN
F 2 "" V 9380 5900 50  0001 C CNN
F 3 "~" H 9450 5900 50  0001 C CNN
	1    9450 5900
	0    1    -1   0   
$EndComp
$Comp
L Device:R R161
U 1 1 5E62EECE
P 10200 5050
F 0 "R161" V 10100 5050 50  0000 C CNN
F 1 "100K" V 10200 5050 50  0000 C CNN
F 2 "" V 10130 5050 50  0001 C CNN
F 3 "~" H 10200 5050 50  0001 C CNN
	1    10200 5050
	0    1    1    0   
$EndComp
Wire Wire Line
	10050 5050 9950 5050
Wire Wire Line
	10350 5050 10400 5050
Connection ~ 10400 5050
Wire Wire Line
	10400 5050 10400 5350
$Comp
L io-master:NCV20074 U21
U 3 1 5E631359
P 10750 5450
F 0 "U21" H 10750 5300 50  0000 L CNN
F 1 "NCV20074" H 10750 5600 50  0000 L CNN
F 2 "Package_SO:TSSOP-14_4.4x5mm_P0.65mm" H 10700 5550 50  0001 C CNN
F 3 "https://www.onsemi.com/pub/Collateral/NCS20071-D.PDF" H 10800 5650 50  0001 C CNN
	3    10750 5450
	1    0    0    1   
$EndComp
Wire Wire Line
	10450 5350 10400 5350
Wire Wire Line
	10450 5550 10400 5550
Wire Wire Line
	10400 5550 10400 5900
Wire Wire Line
	10600 5050 10400 5050
Wire Wire Line
	11050 5450 11200 5450
Connection ~ 11200 5450
Wire Wire Line
	11200 5450 11200 5050
Wire Wire Line
	10900 5050 11200 5050
$Comp
L Device:R R162
U 1 1 5E62EEBF
P 10750 5050
F 0 "R162" V 10650 5050 50  0000 C CNN
F 1 "100K" V 10750 5050 50  0000 C CNN
F 2 "" V 10680 5050 50  0001 C CNN
F 3 "~" H 10750 5050 50  0001 C CNN
	1    10750 5050
	0    1    1    0   
$EndComp
$Comp
L io-master:NCV20074 U21
U 4 1 5E63135B
P 11900 5550
F 0 "U21" H 11900 5400 50  0000 L CNN
F 1 "NCV20074" H 11900 5700 50  0000 L CNN
F 2 "Package_SO:TSSOP-14_4.4x5mm_P0.65mm" H 11850 5650 50  0001 C CNN
F 3 "https://www.onsemi.com/pub/Collateral/NCS20071-D.PDF" H 11950 5750 50  0001 C CNN
	4    11900 5550
	1    0    0    1   
$EndComp
Wire Wire Line
	12200 5550 12500 5550
Wire Wire Line
	12500 5550 12500 4750
Wire Wire Line
	11200 5450 11600 5450
Wire Wire Line
	11600 5650 11550 5650
Wire Wire Line
	11550 5650 11550 6500
Wire Wire Line
	11350 6500 11550 6500
$Comp
L Device:R R163
U 1 1 5E631353
P 11350 6300
F 0 "R163" H 11400 6350 50  0000 L CNN
F 1 "100K" H 11400 6250 50  0000 L CNN
F 2 "" V 11280 6300 50  0001 C CNN
F 3 "~" H 11350 6300 50  0001 C CNN
	1    11350 6300
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R164
U 1 1 5E631362
P 11350 6700
F 0 "R164" H 11400 6750 50  0000 L CNN
F 1 "6.8K" H 11400 6650 50  0000 L CNN
F 2 "" V 11280 6700 50  0001 C CNN
F 3 "~" H 11350 6700 50  0001 C CNN
	1    11350 6700
	-1   0    0    -1  
$EndComp
Text HLabel 11300 6100 0    50   Input ~ 0
+15V
Wire Wire Line
	11300 6100 11350 6100
Text Notes 10450 4850 0    50   ~ 0
Vshunt = abs(10 * Ishunt * Rshunt)
Text Notes 11650 6000 0    50   ~ 0
Vlimit = 10 * Ilimit * Rshunt
Text Notes 11300 6550 2    50   ~ 0
Vlimit
$Comp
L Device:D D26
U 1 1 5E63135D
P 9950 5650
F 0 "D26" V 9996 5571 50  0000 R CNN
F 1 "1N4148" V 9905 5571 50  0000 R CNN
F 2 "" H 9950 5650 50  0001 C CNN
F 3 "~" H 9950 5650 50  0001 C CNN
	1    9950 5650
	0    -1   -1   0   
$EndComp
Text Notes 11550 3900 0    50   ~ 0
TRANSISTOR POWER DISSIPATION:\n  (WORST CASE: OUPUTTING +15V, PIN SHORTED TO -15V)\n  Pq = (15V - -15V) * 50mA = 1.5W\n\n  MAX AVG Pq IS 275mW,\n  ALLOWABLE DUTY CYCLE IS 0.275 / 1.5 = 0.18\n  (10 SEC SHORT CIRCUIT OVER 1 MIN)
$Comp
L Device:LED D27
U 1 1 5E631369
P 13600 5950
F 0 "D27" V 13639 5832 50  0000 R CNN
F 1 "RED" V 13548 5832 50  0000 R CNN
F 2 "" H 13600 5950 50  0001 C CNN
F 3 "~" H 13600 5950 50  0001 C CNN
	1    13600 5950
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R167
U 1 1 5E62EEC0
P 13600 6300
F 0 "R167" H 13670 6346 50  0000 L CNN
F 1 "10K" H 13670 6255 50  0000 L CNN
F 2 "" V 13530 6300 50  0001 C CNN
F 3 "~" H 13600 6300 50  0001 C CNN
	1    13600 6300
	1    0    0    -1  
$EndComp
Text Notes 14000 6000 0    79   ~ 0
CURRENT LIMIT LED
Wire Wire Line
	13600 6150 13600 6100
Wire Wire Line
	13600 6500 13600 6450
Connection ~ 12500 5550
$Comp
L Device:R R166
U 1 1 5E63135A
P 13100 5550
F 0 "R166" V 13000 5550 50  0000 C CNN
F 1 "10K" V 13100 5550 50  0000 C CNN
F 2 "" V 13030 5550 50  0001 C CNN
F 3 "~" H 13100 5550 50  0001 C CNN
	1    13100 5550
	0    1    1    0   
$EndComp
Wire Wire Line
	13300 5550 13250 5550
$Comp
L Transistor_BJT:MMBT3906 Q?
U 1 1 5E631355
P 13500 5550
AR Path="/5DA7F595/5E631355" Ref="Q?"  Part="1" 
AR Path="/5D9F8176/5E631355" Ref="Q?"  Part="1" 
AR Path="/5DAD2F4A/5E631355" Ref="Q16"  Part="1" 
F 0 "Q16" H 13500 5400 50  0000 R CNN
F 1 "MMBT3906" H 13500 5700 50  0000 R CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 13700 5475 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N3906.pdf" H 13500 5550 50  0001 L CNN
	1    13500 5550
	1    0    0    1   
$EndComp
Text HLabel 13650 5300 2    50   Input ~ 0
+15V
Wire Wire Line
	13650 5300 13600 5300
Wire Wire Line
	13600 5300 13600 5350
Wire Wire Line
	13600 5800 13600 5750
$Comp
L power:GND #PWR096
U 1 1 5E62CA30
P 13600 6500
F 0 "#PWR096" H 13600 6250 50  0001 C CNN
F 1 "GND" H 13605 6327 50  0000 C CNN
F 2 "" H 13600 6500 50  0001 C CNN
F 3 "" H 13600 6500 50  0001 C CNN
	1    13600 6500
	1    0    0    -1  
$EndComp
Wire Wire Line
	12500 5550 12950 5550
$Comp
L Device:R R153
U 1 1 5E60C844
P 7100 4350
F 0 "R153" V 7000 4350 50  0000 C CNN
F 1 "2" V 7100 4350 50  0000 C CNN
F 2 "" V 7030 4350 50  0001 C CNN
F 3 "~" H 7100 4350 50  0001 C CNN
	1    7100 4350
	0    1    1    0   
$EndComp
Wire Wire Line
	4000 4350 6900 4350
Wire Wire Line
	7250 4350 7300 4350
Wire Wire Line
	7300 4350 7300 5250
Connection ~ 7300 4350
Wire Wire Line
	7300 4350 11950 4350
Wire Wire Line
	6900 4350 6900 5450
Connection ~ 6900 4350
Wire Wire Line
	6900 4350 6950 4350
Text Notes 3800 4900 2    50   ~ 0
OVERVOLTAGES LIMITED TO +/-15.56V\n  Vf = 0.9V\n  Vz = 14.66V
$Comp
L Connector:TestPoint TP138
U 1 1 5E631360
P 8450 4850
F 0 "TP138" V 8450 5038 50  0000 L CNN
F 1 "TestPoint" V 8495 5038 50  0001 L CNN
F 2 "" H 8650 4850 50  0001 C CNN
F 3 "~" H 8650 4850 50  0001 C CNN
	1    8450 4850
	0    1    1    0   
$EndComp
Wire Wire Line
	8450 4850 8400 4850
Connection ~ 8400 4850
$Comp
L Connector:TestPoint TP139
U 1 1 5E62EED9
P 11250 5050
F 0 "TP139" V 11250 5238 50  0000 L CNN
F 1 "TestPoint" V 11295 5238 50  0001 L CNN
F 2 "" H 11450 5050 50  0001 C CNN
F 3 "~" H 11450 5050 50  0001 C CNN
	1    11250 5050
	0    1    1    0   
$EndComp
Wire Wire Line
	11250 5050 11200 5050
Connection ~ 11200 5050
$Comp
L Connector:TestPoint TP140
U 1 1 5E62EEDA
P 12500 5600
F 0 "TP140" H 12500 5850 50  0000 C TNN
F 1 "TestPoint" V 12545 5788 50  0001 L CNN
F 2 "" H 12700 5600 50  0001 C CNN
F 3 "~" H 12700 5600 50  0001 C CNN
	1    12500 5600
	-1   0    0    1   
$EndComp
Wire Wire Line
	12500 5600 12500 5550
$Comp
L power:GND #PWR?
U 1 1 5E51B97E
P 4000 5150
AR Path="/5D9F8176/5E51B97E" Ref="#PWR?"  Part="1" 
AR Path="/5DAD2F4A/5E51B97E" Ref="#PWR087"  Part="1" 
F 0 "#PWR087" H 4000 4900 50  0001 C CNN
F 1 "GND" H 4005 4977 50  0000 C CNN
F 2 "" H 4000 5150 50  0001 C CNN
F 3 "" H 4000 5150 50  0001 C CNN
	1    4000 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 5150 4000 5100
Wire Wire Line
	4000 4800 4000 4750
$Comp
L Device:D_Zener D?
U 1 1 5E51B986
P 4000 4950
AR Path="/5D9F8176/5E51B986" Ref="D?"  Part="1" 
AR Path="/5DAD2F4A/5E51B986" Ref="D37"  Part="1" 
F 0 "D37" V 3950 4850 50  0000 R CNN
F 1 "MM3Z15VST1G" V 4050 4850 50  0000 R CNN
F 2 "" H 4000 4950 50  0001 C CNN
F 3 "~" H 4000 4950 50  0001 C CNN
	1    4000 4950
	0    -1   1    0   
$EndComp
$Comp
L Device:D_Zener D?
U 1 1 5E51B98C
P 4000 4600
AR Path="/5D9F8176/5E51B98C" Ref="D?"  Part="1" 
AR Path="/5DAD2F4A/5E51B98C" Ref="D36"  Part="1" 
F 0 "D36" V 4050 4500 50  0000 R CNN
F 1 "MM3Z15VST1G" V 3950 4500 50  0000 R CNN
F 2 "" H 4000 4600 50  0001 C CNN
F 3 "~" H 4000 4600 50  0001 C CNN
	1    4000 4600
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C?
U 1 1 5E55EC4E
P 8250 2850
AR Path="/5DA7F595/5E55EC4E" Ref="C?"  Part="1" 
AR Path="/5DAD2F4A/5E55EC4E" Ref="C115"  Part="1" 
F 0 "C115" H 8365 2896 50  0000 L CNN
F 1 "0.1u" H 8365 2805 50  0000 L CNN
F 2 "" H 8288 2700 50  0001 C CNN
F 3 "~" H 8250 2850 50  0001 C CNN
	1    8250 2850
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E55EC54
P 8500 3100
AR Path="/5DA7F595/5E55EC54" Ref="#PWR?"  Part="1" 
AR Path="/5DAD2F4A/5E55EC54" Ref="#PWR0151"  Part="1" 
F 0 "#PWR0151" H 8500 2850 50  0001 C CNN
F 1 "GND" H 8505 2927 50  0000 C CNN
F 2 "" H 8500 3100 50  0001 C CNN
F 3 "" H 8500 3100 50  0001 C CNN
	1    8500 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	8250 2650 8250 2700
Text Notes 7750 2500 0    50   ~ 0
NOTE: DECOUPLING CAPS,\nPLACE CLOSE TO V+/V-
Wire Wire Line
	8200 2650 8250 2650
$Comp
L Device:C C?
U 1 1 5E55EC5D
P 8250 3250
AR Path="/5DA7F595/5E55EC5D" Ref="C?"  Part="1" 
AR Path="/5DAD2F4A/5E55EC5D" Ref="C116"  Part="1" 
F 0 "C116" H 8365 3296 50  0000 L CNN
F 1 "0.1u" H 8365 3205 50  0000 L CNN
F 2 "" H 8288 3100 50  0001 C CNN
F 3 "~" H 8250 3250 50  0001 C CNN
	1    8250 3250
	-1   0    0    -1  
$EndComp
Wire Wire Line
	8250 3000 8250 3050
Wire Wire Line
	8200 3450 8250 3450
Wire Wire Line
	8250 3450 8250 3400
Connection ~ 8250 3050
Wire Wire Line
	8250 3050 8250 3100
Wire Wire Line
	8500 3050 8500 3100
Wire Wire Line
	8250 3050 8500 3050
Text HLabel 8200 2650 0    50   Input ~ 0
+15V
Text HLabel 8200 3450 0    50   Input ~ 0
-15V
$EndSCHEMATC
