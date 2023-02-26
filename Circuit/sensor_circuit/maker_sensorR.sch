EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 3
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
L power:GND #PWR?
U 1 1 63C292C6
P 7500 4200
AR Path="/63C292C6" Ref="#PWR?"  Part="1" 
AR Path="/63C0BC5B/63C292C6" Ref="#PWR075"  Part="1" 
F 0 "#PWR075" H 7500 3950 50  0001 C CNN
F 1 "GND" H 7505 4027 50  0000 C CNN
F 2 "" H 7500 4200 50  0001 C CNN
F 3 "" H 7500 4200 50  0001 C CNN
	1    7500 4200
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7500 4100 7500 4200
Wire Wire Line
	7550 3900 7500 3900
Wire Wire Line
	7550 4100 7500 4100
$Comp
L Device:R_Small R?
U 1 1 63C292D5
P 5650 3200
AR Path="/63C292D5" Ref="R?"  Part="1" 
AR Path="/63C0BC5B/63C292D5" Ref="R23"  Part="1" 
F 0 "R23" H 5709 3246 50  0000 L CNN
F 1 "10k" H 5709 3155 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 5650 3200 50  0001 C CNN
F 3 "~" H 5650 3200 50  0001 C CNN
	1    5650 3200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 63C292DB
P 6850 4200
AR Path="/63C292DB" Ref="#PWR?"  Part="1" 
AR Path="/63C0BC5B/63C292DB" Ref="#PWR074"  Part="1" 
F 0 "#PWR074" H 6850 3950 50  0001 C CNN
F 1 "GND" H 6855 4027 50  0000 C CNN
F 2 "" H 6850 4200 50  0001 C CNN
F 3 "" H 6850 4200 50  0001 C CNN
	1    6850 4200
	-1   0    0    -1  
$EndComp
Wire Wire Line
	6950 3650 6850 3650
Connection ~ 6850 3650
Wire Wire Line
	6850 3650 6850 3900
$Comp
L Device:C_Small C?
U 1 1 63C292E4
P 7050 3650
AR Path="/63C292E4" Ref="C?"  Part="1" 
AR Path="/63C0BC5B/63C292E4" Ref="C13"  Part="1" 
F 0 "C13" V 6821 3650 50  0000 C CNN
F 1 "0.1μ" V 6912 3650 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 7050 3650 50  0001 C CNN
F 3 "~" H 7050 3650 50  0001 C CNN
	1    7050 3650
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 63C292EA
P 7200 3700
AR Path="/63C292EA" Ref="#PWR?"  Part="1" 
AR Path="/63C0BC5B/63C292EA" Ref="#PWR071"  Part="1" 
F 0 "#PWR071" H 7200 3450 50  0001 C CNN
F 1 "GND" H 7205 3527 50  0000 C CNN
F 2 "" H 7200 3700 50  0001 C CNN
F 3 "" H 7200 3700 50  0001 C CNN
	1    7200 3700
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7200 3700 7200 3650
Wire Wire Line
	7150 3650 7200 3650
$Comp
L Device:C_Small C?
U 1 1 63C292F2
P 4400 3250
AR Path="/63C292F2" Ref="C?"  Part="1" 
AR Path="/63C0BC5B/63C292F2" Ref="C12"  Part="1" 
F 0 "C12" H 4492 3296 50  0000 L CNN
F 1 "0.1μ" H 4492 3205 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4400 3250 50  0001 C CNN
F 3 "~" H 4400 3250 50  0001 C CNN
	1    4400 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 3350 4000 3300
$Comp
L power:GND #PWR?
U 1 1 63C292F9
P 4400 3350
AR Path="/63C292F9" Ref="#PWR?"  Part="1" 
AR Path="/63C0BC5B/63C292F9" Ref="#PWR068"  Part="1" 
F 0 "#PWR068" H 4400 3100 50  0001 C CNN
F 1 "GND" H 4405 3177 50  0000 C CNN
F 2 "" H 4400 3350 50  0001 C CNN
F 3 "" H 4400 3350 50  0001 C CNN
	1    4400 3350
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4400 3100 4700 3100
Wire Wire Line
	4700 3100 4700 3400
Wire Wire Line
	4750 3400 4700 3400
Wire Wire Line
	4400 3150 4400 3100
Connection ~ 4400 3100
Wire Wire Line
	4000 3600 4000 3550
Wire Wire Line
	4000 3600 4750 3600
Wire Wire Line
	5650 3600 5650 3700
$Comp
L power:GND #PWR?
U 1 1 63C2930D
P 5650 3700
AR Path="/63C2930D" Ref="#PWR?"  Part="1" 
AR Path="/63C0BC5B/63C2930D" Ref="#PWR070"  Part="1" 
F 0 "#PWR070" H 5650 3450 50  0001 C CNN
F 1 "GND" H 5655 3527 50  0000 C CNN
F 2 "" H 5650 3700 50  0001 C CNN
F 3 "" H 5650 3700 50  0001 C CNN
	1    5650 3700
	-1   0    0    -1  
$EndComp
$Comp
L robotrace_sensorV4-rescue:S7136-mylib U?
U 1 1 63C29313
P 5150 3500
AR Path="/63C29313" Ref="U?"  Part="1" 
AR Path="/63C0BC5B/63C29313" Ref="U10"  Part="1" 
F 0 "U10" H 5138 3138 60  0000 C CNN
F 1 "S7136" H 5138 3244 60  0000 C CNN
F 2 "mcr0:S7136" H 5150 3500 60  0001 C CNN
F 3 "" H 5150 3500 60  0000 C CNN
	1    5150 3500
	1    0    0    1   
$EndComp
Wire Wire Line
	5550 3600 5650 3600
Wire Wire Line
	5650 3300 5650 3400
Wire Wire Line
	5650 3400 5550 3400
Wire Wire Line
	6850 4100 6850 4200
Connection ~ 5650 4600
Wire Wire Line
	5650 4600 5550 4600
Wire Wire Line
	5650 4500 5650 4600
Wire Wire Line
	5550 4800 5650 4800
$Comp
L robotrace_sensorV4-rescue:S7136-mylib U?
U 1 1 63C29324
P 5150 4700
AR Path="/63C29324" Ref="U?"  Part="1" 
AR Path="/63C0BC5B/63C29324" Ref="U12"  Part="1" 
F 0 "U12" H 5138 4338 60  0000 C CNN
F 1 "S7136" H 5138 4444 60  0000 C CNN
F 2 "mcr0:S7136" H 5150 4700 60  0001 C CNN
F 3 "" H 5150 4700 60  0000 C CNN
	1    5150 4700
	1    0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 63C2932A
P 5650 4900
AR Path="/63C2932A" Ref="#PWR?"  Part="1" 
AR Path="/63C0BC5B/63C2932A" Ref="#PWR080"  Part="1" 
F 0 "#PWR080" H 5650 4650 50  0001 C CNN
F 1 "GND" H 5655 4727 50  0000 C CNN
F 2 "" H 5650 4900 50  0001 C CNN
F 3 "" H 5650 4900 50  0001 C CNN
	1    5650 4900
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5650 4800 5650 4900
Wire Wire Line
	4000 4800 4750 4800
Wire Wire Line
	4000 4800 4000 4750
Connection ~ 4400 4300
Wire Wire Line
	4400 4350 4400 4300
Wire Wire Line
	4750 4600 4700 4600
Wire Wire Line
	4700 4300 4700 4600
Wire Wire Line
	4400 4300 4700 4300
$Comp
L power:GND #PWR?
U 1 1 63C2933E
P 4400 4550
AR Path="/63C2933E" Ref="#PWR?"  Part="1" 
AR Path="/63C0BC5B/63C2933E" Ref="#PWR079"  Part="1" 
F 0 "#PWR079" H 4400 4300 50  0001 C CNN
F 1 "GND" H 4405 4377 50  0000 C CNN
F 2 "" H 4400 4550 50  0001 C CNN
F 3 "" H 4400 4550 50  0001 C CNN
	1    4400 4550
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4000 4550 4000 4500
$Comp
L Device:C_Small C?
U 1 1 63C29345
P 4400 4450
AR Path="/63C29345" Ref="C?"  Part="1" 
AR Path="/63C0BC5B/63C29345" Ref="C14"  Part="1" 
F 0 "C14" H 4492 4496 50  0000 L CNN
F 1 "0.1μ" H 4492 4405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4400 4450 50  0001 C CNN
F 3 "~" H 4400 4450 50  0001 C CNN
	1    4400 4450
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R?
U 1 1 63C2934B
P 5650 4400
AR Path="/63C2934B" Ref="R?"  Part="1" 
AR Path="/63C0BC5B/63C2934B" Ref="R26"  Part="1" 
F 0 "R26" H 5709 4446 50  0000 L CNN
F 1 "10k" H 5709 4355 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 5650 4400 50  0001 C CNN
F 3 "~" H 5650 4400 50  0001 C CNN
	1    5650 4400
	1    0    0    -1  
$EndComp
$Comp
L 74xGxx:74AHC1G32 U?
U 1 1 63C29357
P 6850 4000
AR Path="/63C29357" Ref="U?"  Part="1" 
AR Path="/63C0BC5B/63C29357" Ref="U11"  Part="1" 
F 0 "U11" H 6600 4300 50  0000 C CNN
F 1 "TC7S32F" H 6600 4200 50  0000 C CNN
F 2 "Package_SO:TSOP-5_1.65x3.05mm_P0.95mm" H 6850 4000 50  0001 C CNN
F 3 "http://www.ti.com/lit/sg/scyt129e/scyt129e.pdf" H 6850 4000 50  0001 C CNN
	1    6850 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 4050 6350 4600
Wire Wire Line
	6350 3400 6350 3950
Wire Wire Line
	6350 3950 6550 3950
Wire Wire Line
	6550 4050 6350 4050
Wire Wire Line
	7550 4000 7100 4000
Text Notes 7150 3250 0    100  ~ 0
Maker_SenserR
Wire Wire Line
	5650 4250 5650 4300
Wire Wire Line
	4400 4250 4400 4300
Wire Wire Line
	4000 4300 4000 4250
Wire Wire Line
	4400 3050 4400 3100
Wire Wire Line
	5650 3050 5650 3100
Wire Wire Line
	4000 3100 4000 3050
Wire Wire Line
	6850 3550 6850 3650
Wire Wire Line
	7500 3900 7500 3800
$Comp
L power:+5V #PWR?
U 1 1 63C2937D
P 6850 3550
AR Path="/63C2937D" Ref="#PWR?"  Part="1" 
AR Path="/63C0BC5B/63C2937D" Ref="#PWR069"  Part="1" 
F 0 "#PWR069" H 6850 3400 50  0001 C CNN
F 1 "+5V" H 6865 3723 50  0000 C CNN
F 2 "" H 6850 3550 50  0001 C CNN
F 3 "" H 6850 3550 50  0001 C CNN
	1    6850 3550
	-1   0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 63C29383
P 7500 3800
AR Path="/63C29383" Ref="#PWR?"  Part="1" 
AR Path="/63C0BC5B/63C29383" Ref="#PWR072"  Part="1" 
F 0 "#PWR072" H 7500 3650 50  0001 C CNN
F 1 "+5V" H 7515 3973 50  0000 C CNN
F 2 "" H 7500 3800 50  0001 C CNN
F 3 "" H 7500 3800 50  0001 C CNN
	1    7500 3800
	-1   0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 63C29395
P 4000 4250
AR Path="/63C29395" Ref="#PWR?"  Part="1" 
AR Path="/63C0BC5B/63C29395" Ref="#PWR076"  Part="1" 
F 0 "#PWR076" H 4000 4100 50  0001 C CNN
F 1 "+5V" H 4015 4423 50  0000 C CNN
F 2 "" H 4000 4250 50  0001 C CNN
F 3 "" H 4000 4250 50  0001 C CNN
	1    4000 4250
	-1   0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 63C2938F
P 4400 4250
AR Path="/63C2938F" Ref="#PWR?"  Part="1" 
AR Path="/63C0BC5B/63C2938F" Ref="#PWR077"  Part="1" 
F 0 "#PWR077" H 4400 4100 50  0001 C CNN
F 1 "+5V" H 4415 4423 50  0000 C CNN
F 2 "" H 4400 4250 50  0001 C CNN
F 3 "" H 4400 4250 50  0001 C CNN
	1    4400 4250
	-1   0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 63C29389
P 5650 4250
AR Path="/63C29389" Ref="#PWR?"  Part="1" 
AR Path="/63C0BC5B/63C29389" Ref="#PWR078"  Part="1" 
F 0 "#PWR078" H 5650 4100 50  0001 C CNN
F 1 "+5V" H 5665 4423 50  0000 C CNN
F 2 "" H 5650 4250 50  0001 C CNN
F 3 "" H 5650 4250 50  0001 C CNN
	1    5650 4250
	-1   0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 63C29377
P 4000 3050
AR Path="/63C29377" Ref="#PWR?"  Part="1" 
AR Path="/63C0BC5B/63C29377" Ref="#PWR065"  Part="1" 
F 0 "#PWR065" H 4000 2900 50  0001 C CNN
F 1 "+5V" H 4015 3223 50  0000 C CNN
F 2 "" H 4000 3050 50  0001 C CNN
F 3 "" H 4000 3050 50  0001 C CNN
	1    4000 3050
	-1   0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 63C29371
P 4400 3050
AR Path="/63C29371" Ref="#PWR?"  Part="1" 
AR Path="/63C0BC5B/63C29371" Ref="#PWR066"  Part="1" 
F 0 "#PWR066" H 4400 2900 50  0001 C CNN
F 1 "+5V" H 4415 3223 50  0000 C CNN
F 2 "" H 4400 3050 50  0001 C CNN
F 3 "" H 4400 3050 50  0001 C CNN
	1    4400 3050
	-1   0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 63C2936B
P 5650 3050
AR Path="/63C2936B" Ref="#PWR?"  Part="1" 
AR Path="/63C0BC5B/63C2936B" Ref="#PWR067"  Part="1" 
F 0 "#PWR067" H 5650 2900 50  0001 C CNN
F 1 "+5V" H 5665 3223 50  0000 C CNN
F 2 "" H 5650 3050 50  0001 C CNN
F 3 "" H 5650 3050 50  0001 C CNN
	1    5650 3050
	-1   0    0    -1  
$EndComp
$Comp
L Device:R_Small R?
U 1 1 64108A35
P 6000 4250
AR Path="/64108A35" Ref="R?"  Part="1" 
AR Path="/63C0BC5B/64108A35" Ref="R24"  Part="1" 
F 0 "R24" H 6059 4296 50  0000 L CNN
F 1 "1k" H 6059 4205 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 6000 4250 50  0001 C CNN
F 3 "~" H 6000 4250 50  0001 C CNN
	1    6000 4250
	1    0    0    -1  
$EndComp
$Comp
L robotrace_sensorV4-rescue:LED_Small_ALT-Device D?
U 1 1 64108A3C
P 6000 4450
AR Path="/64108A3C" Ref="D?"  Part="1" 
AR Path="/63C0BC5B/64108A3C" Ref="D21"  Part="1" 
F 0 "D21" V 6046 4382 50  0000 R CNN
F 1 "LED" V 5955 4382 50  0000 R CNN
F 2 "LED_SMD:LED_0603_1608Metric_Castellated" V 6000 4450 50  0001 C CNN
F 3 "~" V 6000 4450 50  0001 C CNN
	1    6000 4450
	0    -1   -1   0   
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 64112CE1
P 6000 4150
AR Path="/64112CE1" Ref="#PWR?"  Part="1" 
AR Path="/63C0BC5B/64112CE1" Ref="#PWR073"  Part="1" 
F 0 "#PWR073" H 6000 4000 50  0001 C CNN
F 1 "+5V" H 6015 4323 50  0000 C CNN
F 2 "" H 6000 4150 50  0001 C CNN
F 3 "" H 6000 4150 50  0001 C CNN
	1    6000 4150
	-1   0    0    -1  
$EndComp
Wire Wire Line
	6000 4550 6000 4600
Wire Wire Line
	5650 4600 6000 4600
Connection ~ 6000 4600
Wire Wire Line
	6000 4600 6350 4600
Connection ~ 5650 3400
$Comp
L power:+5V #PWR?
U 1 1 6411D7C3
P 6000 2950
AR Path="/6411D7C3" Ref="#PWR?"  Part="1" 
AR Path="/63C0BC5B/6411D7C3" Ref="#PWR064"  Part="1" 
F 0 "#PWR064" H 6000 2800 50  0001 C CNN
F 1 "+5V" H 6015 3123 50  0000 C CNN
F 2 "" H 6000 2950 50  0001 C CNN
F 3 "" H 6000 2950 50  0001 C CNN
	1    6000 2950
	-1   0    0    -1  
$EndComp
$Comp
L robotrace_sensorV4-rescue:LED_Small_ALT-Device D?
U 1 1 6411D7BD
P 6000 3250
AR Path="/6411D7BD" Ref="D?"  Part="1" 
AR Path="/63C0BC5B/6411D7BD" Ref="D19"  Part="1" 
F 0 "D19" V 6046 3182 50  0000 R CNN
F 1 "LED" V 5955 3182 50  0000 R CNN
F 2 "LED_SMD:LED_0603_1608Metric_Castellated" V 6000 3250 50  0001 C CNN
F 3 "~" V 6000 3250 50  0001 C CNN
	1    6000 3250
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_Small R?
U 1 1 6411D7B7
P 6000 3050
AR Path="/6411D7B7" Ref="R?"  Part="1" 
AR Path="/63C0BC5B/6411D7B7" Ref="R21"  Part="1" 
F 0 "R21" H 6059 3096 50  0000 L CNN
F 1 "1k" H 6059 3005 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 6000 3050 50  0001 C CNN
F 3 "~" H 6000 3050 50  0001 C CNN
	1    6000 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	6000 3400 6350 3400
Wire Wire Line
	5650 3400 6000 3400
Connection ~ 6000 3400
Wire Wire Line
	6000 3350 6000 3400
$Comp
L Connector_Generic:Conn_01x03 J?
U 1 1 63C292C0
P 7750 4000
AR Path="/63C292C0" Ref="J?"  Part="1" 
AR Path="/63C0BC5B/63C292C0" Ref="J3"  Part="1" 
F 0 "J3" H 7750 4200 50  0000 C CNN
F 1 "maker_outR" H 8050 4000 50  0000 C CNN
F 2 "Connectors_JST:JST_SH_BM03B-SRSS-TB_03x1.00mm_Straight" H 7750 4000 50  0001 C CNN
F 3 "~" H 7750 4000 50  0001 C CNN
	1    7750 4000
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R?
U 1 1 63C29351
P 4000 4400
AR Path="/63C29351" Ref="R?"  Part="1" 
AR Path="/63C0BC5B/63C29351" Ref="R25"  Part="1" 
F 0 "R25" H 4059 4446 50  0000 L CNN
F 1 "330" H 4059 4355 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 4000 4400 50  0001 C CNN
F 3 "~" H 4000 4400 50  0001 C CNN
	1    4000 4400
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R?
U 1 1 63C292CF
P 4000 3200
AR Path="/63C292CF" Ref="R?"  Part="1" 
AR Path="/63C0BC5B/63C292CF" Ref="R22"  Part="1" 
F 0 "R22" H 4059 3246 50  0000 L CNN
F 1 "330" H 4059 3155 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 4000 3200 50  0001 C CNN
F 3 "~" H 4000 3200 50  0001 C CNN
	1    4000 3200
	1    0    0    -1  
$EndComp
$Comp
L robotrace_sensorV4-rescue:LED_Small_ALT-Device D?
U 1 1 63C29333
P 4000 4650
AR Path="/63C29333" Ref="D?"  Part="1" 
AR Path="/63C0BC5B/63C29333" Ref="D22"  Part="1" 
F 0 "D22" V 4046 4582 50  0000 R CNN
F 1 "LED" V 3955 4582 50  0000 R CNN
F 2 "LED_SMD:LED_0603_1608Metric_Castellated" V 4000 4650 50  0001 C CNN
F 3 "~" V 4000 4650 50  0001 C CNN
	1    4000 4650
	0    -1   -1   0   
$EndComp
$Comp
L robotrace_sensorV4-rescue:LED_Small_ALT-Device D?
U 1 1 63C29304
P 4000 3450
AR Path="/63C29304" Ref="D?"  Part="1" 
AR Path="/63C0BC5B/63C29304" Ref="D20"  Part="1" 
F 0 "D20" V 4046 3382 50  0000 R CNN
F 1 "LED" V 3955 3382 50  0000 R CNN
F 2 "LED_SMD:LED_0603_1608Metric_Castellated" V 4000 3450 50  0001 C CNN
F 3 "~" V 4000 3450 50  0001 C CNN
	1    4000 3450
	0    -1   -1   0   
$EndComp
$EndSCHEMATC
