#ifndef PORT_CFG_H
#define PORT_CFG_H

/*============================================================================*\
 * PREPROCESSOR DIRECTIVES
\*============================================================================*/

/* INCLUDE DIRECTIVES FOR STANDARD HEADERS -----------------------------------*/

#include "Std_Types.h"

/**
 * \defgroup
 * \name Microprocessor familly switches:
 * \details
 * Set STD_ON/STD_OFF for familly of microprocessor. Only one switch can be set as ON.
 * @{
 */
#define uP78F1841_to_uP78F1845 (STD_OFF)
#define uP78F1836_to_uP78F1840 (STD_ON)
#define uP78F1831_to_uP78F1835 (STD_OFF)
#define uP78F1826_to_uP78F1830 (STD_OFF)
#define uP78F1823_to_uP78F1825 (STD_OFF)
#define uP78F1821_to_uP78F1822 (STD_OFF)
#define uP78F1818_to_uP78F1820 (STD_OFF)
#define uP78F1812_to_uP78F1817 (STD_OFF)
#define uP78F1804_to_uP78F1807_30pins (STD_OFF)
#define uP78F1804_to_uP78F1807_32pins (STD_OFF)

/*----------------------------------------------------------------------------*\
 * CONFIGURATION VARIANT
\*----------------------------------------------------------------------------*/

/* This offsets are used during access to single bit. */
#define PORT_BIT_OFFSET_0 ((uint8)0)
#define PORT_BIT_OFFSET_1 ((uint8)1)
#define PORT_BIT_OFFSET_2 ((uint8)2)
#define PORT_BIT_OFFSET_3 ((uint8)3)
#define PORT_BIT_OFFSET_4 ((uint8)4)
#define PORT_BIT_OFFSET_5 ((uint8)5)
#define PORT_BIT_OFFSET_6 ((uint8)6)
#define PORT_BIT_OFFSET_7 ((uint8)7)

/* Pull resistors types */
#define PORT_PULL_UP    ((uint8)0)
#define PORT_PULL_DOWN  ((uint8)1)

/* Directions types - IN/OUT*/
#define PORT_PIN_DIR_OUT     (STD_LOW)
#define PORT_PIN_DIR_IN      (STD_HIGH)

/*
 * Port_Pin list - number of pins are depend from uP
 */
#define PORT_PIN_P00 ((Port_PinType)0)
#define PORT_PIN_P01 ((Port_PinType)1)
#define PORT_PIN_P02 ((Port_PinType)2)
#define PORT_PIN_P10 ((Port_PinType)3)
#define PORT_PIN_P11 ((Port_PinType)4)
#define PORT_PIN_P12 ((Port_PinType)5)
#define PORT_PIN_P13 ((Port_PinType)6)
#define PORT_PIN_P14 ((Port_PinType)7)
#define PORT_PIN_P15 ((Port_PinType)8)
#define PORT_PIN_P16 ((Port_PinType)9)
#define PORT_PIN_P17 ((Port_PinType)10)
#define PORT_PIN_P30 ((Port_PinType)11)
#define PORT_PIN_P31 ((Port_PinType)12)
#define PORT_PIN_P32 ((Port_PinType)13)
#define PORT_PIN_P40 ((Port_PinType)14)
#define PORT_PIN_P41 ((Port_PinType)15)
#define PORT_PIN_P42 ((Port_PinType)16)
#define PORT_PIN_P43 ((Port_PinType)17)
#define PORT_PIN_P44 ((Port_PinType)18)
#define PORT_PIN_P45 ((Port_PinType)19)
#define PORT_PIN_P46 ((Port_PinType)20)
#define PORT_PIN_P47 ((Port_PinType)21)
#define PORT_PIN_P50 ((Port_PinType)22)
#define PORT_PIN_P51 ((Port_PinType)23)
#define PORT_PIN_P52 ((Port_PinType)24)
#define PORT_PIN_P53 ((Port_PinType)25)
#define PORT_PIN_P54 ((Port_PinType)26)
#define PORT_PIN_P55 ((Port_PinType)27)
#define PORT_PIN_P56 ((Port_PinType)28)
#define PORT_PIN_P57 ((Port_PinType)29)
#define PORT_PIN_P60 ((Port_PinType)30)
#define PORT_PIN_P61 ((Port_PinType)31)
#define PORT_PIN_P62 ((Port_PinType)32)
#define PORT_PIN_P63 ((Port_PinType)33)
#define PORT_PIN_P64 ((Port_PinType)34)
#define PORT_PIN_P65 ((Port_PinType)35)
#define PORT_PIN_P66 ((Port_PinType)36)
#define PORT_PIN_P67 ((Port_PinType)37)
#define PORT_PIN_P70 ((Port_PinType)38)
#define PORT_PIN_P71 ((Port_PinType)39)
#define PORT_PIN_P72 ((Port_PinType)40)
#define PORT_PIN_P73 ((Port_PinType)41)
#define PORT_PIN_P74 ((Port_PinType)42)
#define PORT_PIN_P75 ((Port_PinType)43)
#define PORT_PIN_P76 ((Port_PinType)44)
#define PORT_PIN_P77 ((Port_PinType)45)
#define PORT_PIN_P80 ((Port_PinType)46)
#define PORT_PIN_P81 ((Port_PinType)47)
#define PORT_PIN_P82 ((Port_PinType)48)
#define PORT_PIN_P83 ((Port_PinType)49)
#define PORT_PIN_P84 ((Port_PinType)50)
#define PORT_PIN_P85 ((Port_PinType)51)
#define PORT_PIN_P86 ((Port_PinType)52)
#define PORT_PIN_P87 ((Port_PinType)53)
#define PORT_PIN_P90 ((Port_PinType)54)
#define PORT_PIN_P91 ((Port_PinType)55)
#define PORT_PIN_P92 ((Port_PinType)56)
#define PORT_PIN_P93 ((Port_PinType)57)
#define PORT_PIN_P94 ((Port_PinType)58)
#define PORT_PIN_P95 ((Port_PinType)59)
#define PORT_PIN_P96 ((Port_PinType)60)
#define PORT_PIN_P97 ((Port_PinType)61)
#define PORT_PIN_P120 ((Port_PinType)62)
#define PORT_PIN_P121 ((Port_PinType)63)
#define PORT_PIN_P122 ((Port_PinType)64)
#define PORT_PIN_P123 ((Port_PinType)65)
#define PORT_PIN_P124 ((Port_PinType)66)
#define PORT_PIN_P125 ((Port_PinType)67)
#define PORT_PIN_P126 ((Port_PinType)68)
#define PORT_PIN_P130 ((Port_PinType)69)
#define PORT_PIN_P140 ((Port_PinType)70)

/*
 * Alternate pin functions:
 * - INTP7, TI05, TO05 3V3_Tuner_EN
 */
#define PORT_PIN_P00_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P00_DIRECTION (PORT_PIN_DIR_OUT)
#define PORT_PIN_P00_PULL_RESISTOR (STD_OFF)

/*
 * Alternate pin functions:
 * - P01/TI04/TO04 GPS_3V3_EN
 */
#define PORT_PIN_P01_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P01_DIRECTION (PORT_PIN_DIR_OUT)
#define PORT_PIN_P01_PULL_RESISTOR (STD_ON)

/*
 * Alternate pin functions:
 * - P02/TI06/TO06 MCU_FLMD0
 */
#define PORT_PIN_P02_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P02_DIRECTION (PORT_PIN_DIR_OUT)
#define PORT_PIN_P02_PULL_RESISTOR (STD_OFF)


/*----------------------------------------------------------------------------*\
 *                PORT_1
\*----------------------------------------------------------------------------*/

/* Configuration for pin P10 (User name: PORT_10) */

/*
 * Alternate pin functions:
 * - INTP4, TI00, TO00, CTxD, LTxD1, ~SCK10 TP151
 */
#define PORT_PIN_P10_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P10_DIRECTION (PORT_PIN_DIR_OUT)
#define PORT_PIN_P10_PULL_RESISTOR (STD_ON)
//#define PORT_PIN_P10_PSR (PORT_PIN_PSR_NORMAL)

/* Configuration for pin P11 (User name: PORT_11) */

/*
 * Alternate pin functions:
 * - INTP5, TI02, TO02, SI10, LRxD1, INTPLR1, CRxD TP150
 */
#define PORT_PIN_P11_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P11_DIRECTION (PORT_PIN_DIR_OUT)
#define PORT_PIN_P11_PULL_RESISTOR (STD_ON)

/* Configuration for pin P12 (User name: PORT_12) */

/*
 * Alternate pin functions:
 * - INTP3, SO10, TI16, TO16 ACC_DET
 */
#define PORT_PIN_P12_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P12_DIRECTION (PORT_PIN_DIR_IN)
#define PORT_PIN_P12_PULL_RESISTOR (STD_OFF)
#define PORT_PIN_P12_PSR (PORT_PIN_PSR_NORMAL)

/* Configuration for pin P13 (User name: PORT_13) */

/*
 * Alternate Pin functions:
 * - TI04, TO04, LTxD0 MCU_DEBUG_TX0
 */
#define PORT_PIN_P13_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P13_DIRECTION (PORT_PIN_DIR_OUT)
#define PORT_PIN_P13_PULL_RESISTOR (STD_OFF)

/* Configuration for pin P14 (User name: PORT_14) */

/*
 * Alternate Pin functions:
 * - TI06, TO06, LRxD0, INTPLR0 MCU_DEBUG_RX0
 */
#define PORT_PIN_P14_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P14_DIRECTION (PORT_PIN_DIR_IN)
#define PORT_PIN_P14_PULL_RESISTOR (STD_OFF)

/* Configuration for pin P15 (User name: PORT_15) */

/*
 * Alternate Pin functions:
 * - TI10, TO10, SO00 XF_3V3_EN
 */
#define PORT_PIN_P15_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P15_DIRECTION (PORT_PIN_DIR_OUT)
#define PORT_PIN_P15_PULL_RESISTOR (STD_OFF)

/* Configuration for pin P16 (User name: PORT_16) */

/*
 * Alternate Pin functions:
 * - TI12, TO12, SI00 PWM_TIG
 */
#define PORT_PIN_P16_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P16_DIRECTION (PORT_PIN_DIR_IN)
#define PORT_PIN_P16_PULL_RESISTOR (STD_OFF)

/* Configuration for pin P17 (User name: PORT_17) */

/*
 * Alternate Pin functions:
 * - TI14, TO14, ~SCK00 BACK_TRIG_MCU
 */
#define PORT_PIN_P17_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P17_DIRECTION (PORT_PIN_DIR_OUT)
#define PORT_PIN_P17_PULL_RESISTOR (STD_ON)

/*----------------------------------------------------------------------------*\
 *                PORT_3
\*----------------------------------------------------------------------------*/

/* Configuration for pin P30 (User name: PORT_30) */

/*
 * Alternate pin functions:
 * - INTP2, TI01, TO01,  7180_PWR_EN
 */
#define PORT_PIN_P30_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P30_DIRECTION (PORT_PIN_DIR_OUT)
#define PORT_PIN_P30_PULL_RESISTOR (STD_OFF)
#define PORT_PIN_P30_PSR (PORT_PIN_PSR_NORMAL)

/* Configuration for pin P31 (User name: PORT_31) */

/*
 * Alternate pin functions:
 * - INTP2, TI11, TO11, STOPST  LDO_5V_PGOOD
 */
#define PORT_PIN_P31_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P31_DIRECTION (PORT_PIN_DIR_IN)
#define PORT_PIN_P31_PULL_RESISTOR (STD_OFF)

/* Configuration for pin P32 (User name: PORT_32) */

/*
 * Alternate pin functions:
 * - INTP4, TI13, TO13 CAN_ERRQ#
 */
#define PORT_PIN_P32_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P32_DIRECTION (PORT_PIN_DIR_IN)
#define PORT_PIN_P32_PULL_RESISTOR (STD_OFF)

/*----------------------------------------------------------------------------*\
 *                PORT_4
\*----------------------------------------------------------------------------*/

/* Configuration for pin P40 (User name: PORT_40) */

/*
 * Alternate pin functions:
 * - TOOL0, TI05, TO05 MCU_TOOL0
 */
#define PORT_PIN_P40_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P40_DIRECTION (PORT_PIN_DIR_IN)
#define PORT_PIN_P40_PULL_RESISTOR (STD_OFF)

/* Configuration for pin P41 (User name: PORT_41) */

/*
 * Alternate pin functions:
 * - TOOL1, TI07, TO07 MCU_TOOL1
 */
#define PORT_PIN_P41_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P41_DIRECTION (PORT_PIN_DIR_IN)
#define PORT_PIN_P41_PULL_RESISTOR (STD_OFF)

/* Configuration for pin P42 (User name: PORT_42) */

/*
 * Alternate pin functions:
 * - TxD2, SCL20 MCU_TX2
 */
#define PORT_PIN_P42_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P42_DIRECTION (PORT_PIN_DIR_OUT)
#define PORT_PIN_P42_PULL_RESISTOR (STD_OFF)
#define PORT_PIN_P42_POM (PORT_PIN_POM_NORMAL)

/* Configuration for pin P43 (User name: PORT_43) */

/*
 * Alternate Pin functions:
 * - RxD2, SDA20-I/O, INTPLR2 MCU_RX2
 */
#define PORT_PIN_P43_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P43_DIRECTION (PORT_PIN_DIR_IN)
#define PORT_PIN_P43_PULL_RESISTOR (STD_OFF)
#define PORT_PIN_P43_POM (PORT_PIN_POM_NORMAL)

/* Configuration for pin P44 (User name: PORT_44) */

/*
 * Alternate Pin functions:
 * - RxD2, SDA20-I/O, INTPLR2 VCC_1V8_EN
 */
#define PORT_PIN_P44_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P44_DIRECTION (PORT_PIN_DIR_OUT)
#define PORT_PIN_P44_PULL_RESISTOR (STD_OFF)

/* Configuration for pin P45 (User name: PORT_45) */

/*
 * Alternate Pin functions:
 * - RxD2, SDA20-I/O, INTPLR2 PWM_TIG
 */
#define PORT_PIN_P45_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P45_DIRECTION (PORT_PIN_DIR_OUT)
#define PORT_PIN_P45_PULL_RESISTOR (STD_OFF)

/* Configuration for pin P46(User name: PORT_46) */

/*
 * Alternate Pin functions:
 * - RxD2, SDA20-I/O, INTPLR2 LCD_DIM_PWM_MCU
 */
#define PORT_PIN_P46_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P46_DIRECTION (PORT_PIN_DIR_OUT)
#define PORT_PIN_P46_PULL_RESISTOR (STD_OFF)
/* Configuration for pin P47 (User name: PORT_47) */

/*
 * Alternate Pin functions:
 * - RxD2, SDA20-I/O, INTP8 IR_INT_MCU
 */
#define PORT_PIN_P47_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P47_DIRECTION (PORT_PIN_DIR_IN)
#define PORT_PIN_P47_PULL_RESISTOR (STD_OFF)

/*----------------------------------------------------------------------------*\
 *                PORT_5
\*----------------------------------------------------------------------------*/

/* Configuration for pin P50 (User name: PORT_50) */

/*
 * Alternate pin functions:
 * - INTP3, TI20, TO20 ADV7611_INT_MCU
 */
#define PORT_PIN_P50_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P50_DIRECTION (PORT_PIN_DIR_OUT)
#define PORT_PIN_P50_PULL_RESISTOR (STD_OFF)

/* Configuration for pin P51 (User name: PORT_51) */

/*
 * Alternate pin functions:
 * - TI21, TO21 LCD_BL_EN_MCU
 */
#define PORT_PIN_P51_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P51_DIRECTION (PORT_PIN_DIR_OUT)
#define PORT_PIN_P51_PULL_RESISTOR (STD_OFF)

/* Configuration for pin P52 (User name: PORT_52) */

/*
 * Alternate pin functions:
 * - TI22, TO22, STOPST CAN_STB#
 */
#define PORT_PIN_P52_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P52_DIRECTION (PORT_PIN_DIR_OUT)
#define PORT_PIN_P52_PULL_RESISTOR (STD_OFF)

/* Configuration for pin P53 (User name: PORT_53) */

/*
 * Alternate Pin functions:
 * - TI23, TO23 SYNC
 */
#define PORT_PIN_P53_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P53_DIRECTION (PORT_PIN_DIR_OUT)
#define PORT_PIN_P53_PULL_RESISTOR (STD_OFF)

/* Configuration for pin P54 (User name: PORT_54) */

/*
 * Alternate Pin functions:
 * - TI11/TO11 3V3_STBY_PGOOD
 */
#define PORT_PIN_P54_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P54_DIRECTION (PORT_PIN_DIR_OUT)
#define PORT_PIN_P54_PULL_RESISTOR (STD_OFF)


/* Configuration for pin P55 (User name: PORT_55) */

/*
 * Alternate Pin functions:
 * - TI13/TO13 VCC_3V3_GOOD
 */
#define PORT_PIN_P55_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P55_DIRECTION (PORT_PIN_DIR_OUT)
#define PORT_PIN_P55_PULL_RESISTOR (STD_OFF)


/* Configuration for pin P56 (User name: PORT_56) */

/*
 * Alternate Pin functions:
 * - TI15/TO15 7611_3V3_EN
 */
#define PORT_PIN_P56_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P56_DIRECTION (PORT_PIN_DIR_OUT)
#define PORT_PIN_P56_PULL_RESISTOR (STD_OFF)


/* Configuration for pin P57 (User name: PORT_57) */

/*
 * Alternate Pin functions:
 * - TI17/TO17 7611_1V8_EN
 */
#define PORT_PIN_P57_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P57_DIRECTION (PORT_PIN_DIR_OUT)
#define PORT_PIN_P57_PULL_RESISTOR (STD_OFF)


/*----------------------------------------------------------------------------*\
 *                PORT_6
\*----------------------------------------------------------------------------*/

/* Configuration for pin P60 (User name: PORT_60) */

/*
 * Alternate pin functions:
 * - ~SCK00, SCL11 MCU_I2C1_SCL
 */
#define PORT_PIN_P60_LEVEL_VALUE (STD_HIGH)
#define PORT_PIN_P60_DIRECTION (PORT_PIN_DIR_OUT)
#define PORT_PIN_P60_PULL_RESISTOR (STD_ON)
#define PORT_PIN_P60_PIM (PORT_PIN_PIM_NORMAL)

/* Configuration for pin P61 (User name: PORT_61) */

/*
 * Alternate pin functions:
 * - SI00, SDA11 MCU_I2C1_SDA
 */
#define PORT_PIN_P61_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P61_DIRECTION (PORT_PIN_DIR_IN)
#define PORT_PIN_P61_PULL_RESISTOR (STD_OFF)
#define PORT_PIN_P61_PIM (PORT_PIN_PIM_NORMAL)

/* Configuration for pin P62 (User name: PORT_62) */

/*
 * Alternate pin functions:
 * - SO00 LCD_5V_EN
 */
#define PORT_PIN_P62_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P62_DIRECTION (PORT_PIN_DIR_IN)
#define PORT_PIN_P62_PULL_RESISTOR (STD_OFF)

/* Configuration for pin P63 (User name: PORT_63) */

/*
 * Alternate Pin functions:
 * - ~SSI00 HSD_EN
 */
#define PORT_PIN_P63_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P63_DIRECTION (PORT_PIN_DIR_IN)
#define PORT_PIN_P63_PULL_RESISTOR (STD_ON)
#define PORT_PIN_P63_PIM (PORT_PIN_PIM_NORMAL)

/* Configuration for pin P64 (User name: PORT_64) */

/*
 * Alternate Pin functions:
 * - ~SSI00 AMP_STB#_MCU
 */
#define PORT_PIN_P64_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P64_DIRECTION (PORT_PIN_DIR_OUT)
#define PORT_PIN_P64_PULL_RESISTOR (STD_ON)
#define PORT_PIN_P64_PIM (PORT_PIN_PIM_NORMAL)

/* Configuration for pin P65 (User name: PORT_65) */

/*
 * Alternate Pin functions:
 * - ~SSI00 DIS_1_MCU
 */
#define PORT_PIN_P65_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P65_DIRECTION (PORT_PIN_DIR_OUT)
#define PORT_PIN_P65_PULL_RESISTOR (STD_ON)
#define PORT_PIN_P65_PIM (PORT_PIN_PIM_NORMAL)

/* Configuration for pin P66 (User name: PORT_66) */

/*
 * Alternate Pin functions:
 * - ~SSI00 DIS_2_MCU
 */
#define PORT_PIN_P66_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P66_DIRECTION (PORT_PIN_DIR_OUT)
#define PORT_PIN_P66_PULL_RESISTOR (STD_ON)
#define PORT_PIN_P66_PIM (PORT_PIN_PIM_NORMAL)

/* Configuration for pin P67 (User name: PORT_67) */

/*
 * Alternate Pin functions:
 * - ~SSI00 LCD_LED12V_EN
 */
#define PORT_PIN_P67_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P67_DIRECTION (PORT_PIN_DIR_OUT)
#define PORT_PIN_P67_PULL_RESISTOR (STD_ON)
#define PORT_PIN_P67_PIM (PORT_PIN_PIM_NORMAL)

/*----------------------------------------------------------------------------*\
 *                PORT_7
\*----------------------------------------------------------------------------*/

/* Configuration for pin P70 (User name: PORT_70) */

/*
 * Alternate pin functions:
 * - INTP5, KR0, TI15, TO15 CAN_INTQ#
 */
#define PORT_PIN_P70_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P70_DIRECTION (PORT_PIN_DIR_OUT)
#define PORT_PIN_P70_PULL_RESISTOR (STD_OFF)

/* Configuration for pin P71 (User name: PORT_71) */

/*
 * Alternate pin functions:
 * - INTP6, KR1, TI17, TO17 ADV7180_INTRQ_MCU
 */
#define PORT_PIN_P71_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P71_DIRECTION (PORT_PIN_DIR_OUT)
#define PORT_PIN_P71_PULL_RESISTOR (STD_ON)

/* Configuration for pin P72 (User name: PORT_72) */

/*
 * Alternate pin functions:
 * - KR2, CTxD,  CAN_TX
 */
#define PORT_PIN_P72_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P72_DIRECTION (PORT_PIN_DIR_OUT)
#define PORT_PIN_P72_PULL_RESISTOR (STD_OFF)
#define PORT_PIN_P72_POM (PORT_PIN_POM_NORMAL)

/* Configuration for pin P73 (User name: PORT_73) */

/*
 * Alternate Pin functions:
 * - KR3, CRxD, LRxD1,  CAN_RX
 */
#define PORT_PIN_P73_LEVEL_VALUE (STD_HIGH)
#define PORT_PIN_P73_DIRECTION (PORT_PIN_DIR_IN)
#define PORT_PIN_P73_PULL_RESISTOR (STD_OFF)
#define PORT_PIN_P73_PIM (PORT_PIN_PIM_NORMAL)

/* Configuration for pin P74 (User name: PORT_74) */

/*
 * Alternate Pin functions:
 * - KR4, SO01 J6_FBATT_EN
 */
#define PORT_PIN_P74_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P74_DIRECTION (PORT_PIN_DIR_OUT)
#define PORT_PIN_P74_PULL_RESISTOR (STD_OFF)
#define PORT_PIN_P74_POM (PORT_PIN_POM_NORMAL)
#define PORT_PIN_P74_PSR (PORT_PIN_PSR_NORMAL)

/* Configuration for pin P75 (User name: PORT_75) */

/*
 * Alternate Pin functions:
 * - KR5, SI01 GP6[17]
 */
#define PORT_PIN_P75_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P75_DIRECTION (PORT_PIN_DIR_IN)
#define PORT_PIN_P75_PULL_RESISTOR (STD_OFF)
#define PORT_PIN_P75_PIM (PORT_PIN_PIM_NORMAL)

/* Configuration for pin P76 (User name: PORT_76) */

/*
 * Alternate Pin functions:
 * - KR6, ~SCK01 GP6[20]
 */
#define PORT_PIN_P76_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P76_DIRECTION (PORT_PIN_DIR_IN)
#define PORT_PIN_P76_PULL_RESISTOR (STD_OFF)
#define PORT_PIN_P76_PIM (PORT_PIN_PIM_NORMAL)
#define PORT_PIN_P76_POM (PORT_PIN_POM_NORMAL)
#define PORT_PIN_P76_PSR (PORT_PIN_PSR_NORMAL)

/* Configuration for pin P77 (User name: PORT_77) */

/*
 * Alternate Pin functions:
 * - KR7, ~SSI01 VCC_3V3_EN
 */
#define PORT_PIN_P77_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P77_DIRECTION (PORT_PIN_DIR_OUT)
#define PORT_PIN_P77_PULL_RESISTOR (STD_OFF)
#define PORT_PIN_P77_PIM (PORT_PIN_PIM_NORMAL)

/*----------------------------------------------------------------------------*\
 *                PORT_8
\*----------------------------------------------------------------------------*/

/* Configuration for pin P80 (User name: PORT_80) */

/*
 * Alternate pin functions:
 * - ANI00 VOLT_DET
 */
#define PORT_PIN_P80_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P80_DIRECTION (PORT_PIN_DIR_IN)
#define PORT_PIN_P80_PULL_RESISTOR (STD_OFF)

/* Configuration for pin P81 (User name: PORT_81) */

/*
 * Alternate pin functions:
 * - ANI01 GPS_ANT_DET
 */
#define PORT_PIN_P81_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P81_DIRECTION (PORT_PIN_DIR_IN)
#define PORT_PIN_P81_PULL_RESISTOR (STD_OFF)

/* Configuration for pin P82 (User name: PORT_82) */

/*
 * Alternate pin functions:
 * - ANI02 SWC1
 */
#define PORT_PIN_P82_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P82_DIRECTION (PORT_PIN_DIR_IN)
#define PORT_PIN_P82_PULL_RESISTOR (STD_OFF)

/* Configuration for pin P83 (User name: PORT_83) */

/*
 * Alternate Pin functions:
 * - ANI03 SWC2
 */
#define PORT_PIN_P83_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P83_DIRECTION (PORT_PIN_DIR_IN)
#define PORT_PIN_P83_PULL_RESISTOR (STD_OFF)

/* Configuration for pin P84 (User name: PORT_84) */

/*
 * Alternate Pin functions:
 * - ANI04 Tuner_ANT_DET
 */
#define PORT_PIN_P84_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P84_DIRECTION (PORT_PIN_DIR_IN)
#define PORT_PIN_P84_PULL_RESISTOR (STD_OFF)

/* Configuration for pin P85 (User name: PORT_85) */

/*
 * Alternate Pin functions:
 * - ANI05 AMP_DIAG
 */
#define PORT_PIN_P85_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P85_DIRECTION (PORT_PIN_DIR_IN)
#define PORT_PIN_P85_PULL_RESISTOR (STD_OFF)

/* Configuration for pin P86 (User name: PORT_86) */

/*
 * Alternate Pin functions:
 * - ANI06 CAN_EN
 */
#define PORT_PIN_P86_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P86_DIRECTION (PORT_PIN_DIR_OUT)
#define PORT_PIN_P86_PULL_RESISTOR (STD_OFF)

/* Configuration for pin P87 (User name: PORT_87) */

/*
 * Alternate Pin functions:
 * - ANI07 LDO_5V_EN
 */
#define PORT_PIN_P87_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P87_DIRECTION (PORT_PIN_DIR_OUT)
#define PORT_PIN_P87_PULL_RESISTOR (STD_OFF)

/*----------------------------------------------------------------------------*\
 *                PORT_9
\*----------------------------------------------------------------------------*/

/* Configuration for pin P90 (User name: PORT_90) */

/*
 * Alternate pin functions:
 * - ANI08 ADV7611_RESET_MCU
 */
#define PORT_PIN_P90_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P90_DIRECTION (PORT_PIN_DIR_OUT)
#define PORT_PIN_P90_PULL_RESISTOR (STD_OFF)

/* Configuration for pin P91 (User name: PORT_91) */

/*
 * Alternate pin functions:
 * - ANI09 ADV_7393_RESET_MCU
 */
#define PORT_PIN_P91_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P91_DIRECTION (PORT_PIN_DIR_OUT)
#define PORT_PIN_P91_PULL_RESISTOR (STD_OFF)

/* Configuration for pin P92 (User name: PORT_92) */

/*
 * Alternate pin functions:
 * - ANI10 ADV7180_RESET_MCU
 */
#define PORT_PIN_P92_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P92_DIRECTION (PORT_PIN_DIR_OUT)
#define PORT_PIN_P92_PULL_RESISTOR (STD_OFF)

/* Configuration for pin P93 (User name: PORT_93) */

/*
 * Alternate Pin functions:
 * - ANI11 Tuner_Reset_MCU
 */
#define PORT_PIN_P93_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P93_DIRECTION (PORT_PIN_DIR_OUT)
#define PORT_PIN_P93_PULL_RESISTOR (STD_OFF)

/* Configuration for pin P94 (User name: PORT_94) */

/*
 * Alternate Pin functions:
 * - ANI12 XF_RESET_MCU
 */
#define PORT_PIN_P94_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P94_DIRECTION (PORT_PIN_DIR_OUT)
#define PORT_PIN_P94_PULL_RESISTOR (STD_OFF)

/* Configuration for pin P95 (User name: PORT_95) */

/*
 * Alternate Pin functions:
 * - ANI13 GPS_RESET_MCU
 */
#define PORT_PIN_P95_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P95_DIRECTION (PORT_PIN_DIR_OUT)
#define PORT_PIN_P95_PULL_RESISTOR (STD_OFF)

/* Configuration for pin P96 (User name: PORT_96) */

/*
 * Alternate Pin functions:
 * - ANI14 TP22
 */
#define PORT_PIN_P96_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P96_DIRECTION (PORT_PIN_DIR_IN)
#define PORT_PIN_P96_PULL_RESISTOR (STD_OFF)

/*
 * Alternate Pin functions:
 * - ANI15 TP23
 */
#define PORT_PIN_P97_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P97_DIRECTION (PORT_PIN_DIR_IN)
#define PORT_PIN_P97_PULL_RESISTOR (STD_OFF)

/*----------------------------------------------------------------------------*\
 *                PORT_12
\*----------------------------------------------------------------------------*/

/* Configuration for pin P120 (User name: PORT_120) */

/*
 * Alternate pin functions:
 * - INTP0, EXLVI TP139
 */
#define PORT_PIN_P120_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P120_DIRECTION (PORT_PIN_DIR_IN)
#define PORT_PIN_P120_PULL_RESISTOR (STD_OFF)

/* Configuration for pin P121 (User name: PORT_121) */

/*
 * Alternate pin functions:
 * - X1
 */
#define PORT_PIN_P121_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P121_DIRECTION (PORT_PIN_DIR_IN)
#define PORT_PIN_P121_PULL_RESISTOR (STD_OFF)

/* Configuration for pin P122 (User name: PORT_122) */

/*
 * Alternate pin functions:
 * - X2, EXCLK
 */
#define PORT_PIN_P122_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P122_DIRECTION (PORT_PIN_DIR_IN)
#define PORT_PIN_P122_PULL_RESISTOR (STD_OFF)

/* Configuration for pin P123 (User name: PORT_123) */

/*
 * Alternate Pin functions:
 * - None
 */
#define PORT_PIN_P123_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P123_DIRECTION (PORT_PIN_DIR_IN)
#define PORT_PIN_P123_PULL_RESISTOR (STD_OFF)

/* Configuration for pin P124 (User name: PORT_124) */

/*
 * Alternate Pin functions:
 * - EXCLKS 32.768_CLK
 */
#define PORT_PIN_P124_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P124_DIRECTION (PORT_PIN_DIR_IN)
#define PORT_PIN_P124_PULL_RESISTOR (STD_OFF)

/* Configuration for pin P125 (User name: PORT_125) */

/*
 * Alternate Pin functions:
 * - INTP1, ADTRG, TI03, TO03 ILL_IN_MCU
 */
#define PORT_PIN_P125_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P125_DIRECTION (PORT_PIN_DIR_IN)
#define PORT_PIN_P125_PULL_RESISTOR (STD_OFF)

/* Configuration for pin P126(User name: PORT_126) */

/*
 * Alternate Pin functions:
 * - TI01/TO01 3V3_SIGNAL_EN
 */
#define PORT_PIN_P126_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P126_DIRECTION (PORT_PIN_DIR_OUT)
#define PORT_PIN_P126_PULL_RESISTOR (STD_OFF)

/*----------------------------------------------------------------------------*\
 *                PORT_13
\*----------------------------------------------------------------------------*/

/* Configuration for pin P130 (User name: PORT_130) */

/*
 * Alternate pin functions:
 * - RESOUT TP144
 */
#define PORT_PIN_P130_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P130_DIRECTION (PORT_PIN_DIR_OUT)
#define PORT_PIN_P130_PULL_RESISTOR (STD_OFF)

/*----------------------------------------------------------------------------*\
 *                PORT_14
\*----------------------------------------------------------------------------*/

/* Configuration for pin P140 (User name: PORT_140) */

/*
 * Alternate pin functions:
 * - PCL TP143
 */
#define PORT_PIN_P140_LEVEL_VALUE (STD_LOW)
#define PORT_PIN_P140_DIRECTION (PORT_PIN_DIR_OUT)
#define PORT_PIN_P140_PULL_RESISTOR (STD_OFF)
#define PORT_PIN_P140_PSR (PORT_PIN_PSR_NORMAL)

#define PORT_ADPC_VALUE ((uint8)1)


/* Macros for ports registers value. */

/*----------------------------------------------------------------------------*\
 *                PORT_0
\*----------------------------------------------------------------------------*/
#define PORT_P0_VALUE \
   ((uint8)0x00 \
   | (uint8) ((uint8) PORT_PIN_P00_LEVEL_VALUE << PORT_BIT_OFFSET_0) \
   | (uint8) ((uint8) PORT_PIN_P01_LEVEL_VALUE << PORT_BIT_OFFSET_1)\
   | (uint8) ((uint8) PORT_PIN_P02_LEVEL_VALUE << PORT_BIT_OFFSET_2) )

/* PORT_0 - data direction register value */

#define PORT_PM0_VALUE \
   ((uint8) ((uint8) PORT_PIN_P00_DIRECTION << PORT_BIT_OFFSET_0) \
   | (uint8) ((uint8)PORT_PIN_P01_DIRECTION << PORT_BIT_OFFSET_1) \
   | (uint8) ((uint8)PORT_PIN_P02_DIRECTION << PORT_BIT_OFFSET_2) \
   | (uint8) ((uint8) 1 << PORT_BIT_OFFSET_3) \
   | (uint8) ((uint8) 1 << PORT_BIT_OFFSET_4) \
   | (uint8) ((uint8) 1 << PORT_BIT_OFFSET_5) \
   | (uint8) ((uint8) 1 << PORT_BIT_OFFSET_6) \
   | (uint8) ((uint8) 1 << PORT_BIT_OFFSET_7) )

/* PORT_0 - pull resistor enable register */

#define PORT_PU0_VALUE \
   ((uint8)0x00 \
   | (uint8) ((uint8) PORT_PIN_P00_PULL_RESISTOR << PORT_BIT_OFFSET_0) \
   | (uint8) ((uint8) PORT_PIN_P01_PULL_RESISTOR << PORT_BIT_OFFSET_1) \
   | (uint8) ((uint8) PORT_PIN_P02_PULL_RESISTOR << PORT_BIT_OFFSET_2) )

/*----------------------------------------------------------------------------*\
 *                PORT_1
\*----------------------------------------------------------------------------*/
#define PORT_P1_VALUE \
   ( (uint8) ((uint8) PORT_PIN_P10_LEVEL_VALUE << PORT_BIT_OFFSET_0) \
   | (uint8) ((uint8) PORT_PIN_P11_LEVEL_VALUE << PORT_BIT_OFFSET_1) \
   | (uint8) ((uint8) PORT_PIN_P12_LEVEL_VALUE << PORT_BIT_OFFSET_2) \
   | (uint8) ((uint8) PORT_PIN_P13_LEVEL_VALUE << PORT_BIT_OFFSET_3) \
   | (uint8) ((uint8) PORT_PIN_P14_LEVEL_VALUE << PORT_BIT_OFFSET_4) \
   | (uint8) ((uint8) PORT_PIN_P15_LEVEL_VALUE << PORT_BIT_OFFSET_5) \
   | (uint8) ((uint8) PORT_PIN_P16_LEVEL_VALUE << PORT_BIT_OFFSET_6) \
   | (uint8) ((uint8) PORT_PIN_P17_LEVEL_VALUE << PORT_BIT_OFFSET_7) )

/* PORT_1 - data direction register value */

#define PORT_PM1_VALUE \
   ( (uint8) ((uint8) PORT_PIN_P10_DIRECTION << PORT_BIT_OFFSET_0) \
   | (uint8) ((uint8) PORT_PIN_P11_DIRECTION << PORT_BIT_OFFSET_1) \
   | (uint8) ((uint8) PORT_PIN_P12_DIRECTION << PORT_BIT_OFFSET_2) \
   | (uint8) ((uint8) PORT_PIN_P13_DIRECTION << PORT_BIT_OFFSET_3) \
   | (uint8) ((uint8) PORT_PIN_P14_DIRECTION << PORT_BIT_OFFSET_4) \
   | (uint8) ((uint8) PORT_PIN_P15_DIRECTION << PORT_BIT_OFFSET_5) \
   | (uint8) ((uint8) PORT_PIN_P16_DIRECTION << PORT_BIT_OFFSET_6) \
   | (uint8) ((uint8) PORT_PIN_P17_DIRECTION << PORT_BIT_OFFSET_7) )

/* PORT_1 - pull resistor enable register */

#define PORT_PU1_VALUE \
   ( (uint8) ((uint8) PORT_PIN_P10_PULL_RESISTOR << PORT_BIT_OFFSET_0) \
   | (uint8) ((uint8) PORT_PIN_P11_PULL_RESISTOR << PORT_BIT_OFFSET_1) \
   | (uint8) ((uint8) PORT_PIN_P12_PULL_RESISTOR << PORT_BIT_OFFSET_2) \
   | (uint8) ((uint8) PORT_PIN_P13_PULL_RESISTOR << PORT_BIT_OFFSET_3) \
   | (uint8) ((uint8) PORT_PIN_P14_PULL_RESISTOR << PORT_BIT_OFFSET_4) \
   | (uint8) ((uint8) PORT_PIN_P15_PULL_RESISTOR << PORT_BIT_OFFSET_5) \
   | (uint8) ((uint8) PORT_PIN_P16_PULL_RESISTOR << PORT_BIT_OFFSET_6) \
   | (uint8) ((uint8) PORT_PIN_P17_PULL_RESISTOR << PORT_BIT_OFFSET_7) )

/*----------------------------------------------------------------------------*\
 *                PORT_3
\*----------------------------------------------------------------------------*/
#define PORT_P3_VALUE \
   ((uint8)0x00 \
   | (uint8) ((uint8) PORT_PIN_P30_LEVEL_VALUE << PORT_BIT_OFFSET_0) \
   | (uint8) ((uint8) PORT_PIN_P31_LEVEL_VALUE << PORT_BIT_OFFSET_1) \
   | (uint8) ((uint8) PORT_PIN_P32_LEVEL_VALUE << PORT_BIT_OFFSET_2) )

/* PORT_3 - data direction register value */

#define PORT_PM3_VALUE \
   ((uint8) ((uint8) PORT_PIN_P30_DIRECTION << PORT_BIT_OFFSET_0) \
   | (uint8) ((uint8) PORT_PIN_P31_DIRECTION << PORT_BIT_OFFSET_1) \
   | (uint8) ((uint8) PORT_PIN_P32_DIRECTION << PORT_BIT_OFFSET_2) \
   | (uint8) ((uint8) 1 << PORT_BIT_OFFSET_3) \
   | (uint8) ((uint8) 1 << PORT_BIT_OFFSET_4) \
   | (uint8) ((uint8) 1 << PORT_BIT_OFFSET_5) \
   | (uint8) ((uint8) 1 << PORT_BIT_OFFSET_6) \
   | (uint8) ((uint8) 1 << PORT_BIT_OFFSET_7) )

/* PORT_3 - pull resistor enable register */

#define PORT_PU3_VALUE \
   ((uint8)0x00 \
 | (uint8) ((uint8) PORT_PIN_P30_PULL_RESISTOR << PORT_BIT_OFFSET_0) \
 | (uint8) ((uint8) PORT_PIN_P31_PULL_RESISTOR << PORT_BIT_OFFSET_1) \
 | (uint8) ((uint8) PORT_PIN_P32_PULL_RESISTOR << PORT_BIT_OFFSET_2) )

/*----------------------------------------------------------------------------*\
 *                PORT_4
\*----------------------------------------------------------------------------*/
#define PORT_P4_VALUE \
   ( (uint8) ((uint8) PORT_PIN_P40_LEVEL_VALUE << PORT_BIT_OFFSET_0) \
   | (uint8) ((uint8) PORT_PIN_P41_LEVEL_VALUE << PORT_BIT_OFFSET_1) \
   | (uint8) ((uint8) PORT_PIN_P42_LEVEL_VALUE << PORT_BIT_OFFSET_2) \
   | (uint8) ((uint8) PORT_PIN_P43_LEVEL_VALUE << PORT_BIT_OFFSET_3) \
   | (uint8) ((uint8) PORT_PIN_P44_LEVEL_VALUE << PORT_BIT_OFFSET_4) \
   | (uint8) ((uint8) PORT_PIN_P45_LEVEL_VALUE << PORT_BIT_OFFSET_5) \
   | (uint8) ((uint8) PORT_PIN_P46_LEVEL_VALUE << PORT_BIT_OFFSET_6) \
   | (uint8) ((uint8) PORT_PIN_P47_LEVEL_VALUE << PORT_BIT_OFFSET_7)) 
   
/* PORT_4 - data direction register value */

#define PORT_PM4_VALUE \
   ((uint8) ((uint8) PORT_PIN_P40_DIRECTION << PORT_BIT_OFFSET_0) \
   | (uint8) ((uint8) PORT_PIN_P41_DIRECTION << PORT_BIT_OFFSET_1) \
   | (uint8) ((uint8) PORT_PIN_P42_DIRECTION << PORT_BIT_OFFSET_2) \
   | (uint8) ((uint8) PORT_PIN_P43_DIRECTION << PORT_BIT_OFFSET_3) \
   | (uint8) ((uint8) PORT_PIN_P44_DIRECTION << PORT_BIT_OFFSET_4) \
   | (uint8) ((uint8) PORT_PIN_P45_DIRECTION << PORT_BIT_OFFSET_5) \
   | (uint8) ((uint8) PORT_PIN_P46_DIRECTION << PORT_BIT_OFFSET_6) \
   | (uint8) ((uint8) PORT_PIN_P47_DIRECTION << PORT_BIT_OFFSET_7) )
   
/* PORT_4 - pull resistor enable register */

#define PORT_PU4_VALUE \
   ( (uint8) ((uint8) PORT_PIN_P40_PULL_RESISTOR << PORT_BIT_OFFSET_0) \
   | (uint8) ((uint8) PORT_PIN_P41_PULL_RESISTOR << PORT_BIT_OFFSET_1) \
   | (uint8) ((uint8) PORT_PIN_P42_PULL_RESISTOR << PORT_BIT_OFFSET_2) \
   | (uint8) ((uint8) PORT_PIN_P43_PULL_RESISTOR << PORT_BIT_OFFSET_3) \
   | (uint8) ((uint8) PORT_PIN_P44_PULL_RESISTOR << PORT_BIT_OFFSET_4) \
   | (uint8) ((uint8) PORT_PIN_P45_PULL_RESISTOR << PORT_BIT_OFFSET_5) \
   | (uint8) ((uint8) PORT_PIN_P46_PULL_RESISTOR << PORT_BIT_OFFSET_6) \
   | (uint8) ((uint8) PORT_PIN_P47_PULL_RESISTOR << PORT_BIT_OFFSET_7) )

/* PORT_4 - port output mode register */

#define PORT_POM4_VALUE \
   ((uint8)0x00 \
   | (uint8) ((uint8) PORT_PIN_P42_POM << PORT_BIT_OFFSET_2) \
   | (uint8) ((uint8) PORT_PIN_P43_POM << PORT_BIT_OFFSET_3) )

/*----------------------------------------------------------------------------*\
 *                PORT_5
\*----------------------------------------------------------------------------*/
#define PORT_P5_VALUE \
   ( (uint8) ((uint8) PORT_PIN_P50_LEVEL_VALUE << PORT_BIT_OFFSET_0) \
   | (uint8) ((uint8) PORT_PIN_P51_LEVEL_VALUE << PORT_BIT_OFFSET_1) \
   | (uint8) ((uint8) PORT_PIN_P52_LEVEL_VALUE << PORT_BIT_OFFSET_2) \
   | (uint8) ((uint8) PORT_PIN_P53_LEVEL_VALUE << PORT_BIT_OFFSET_3) \
   | (uint8) ((uint8) PORT_PIN_P54_LEVEL_VALUE << PORT_BIT_OFFSET_4) \
   | (uint8) ((uint8) PORT_PIN_P55_LEVEL_VALUE << PORT_BIT_OFFSET_5) \
   | (uint8) ((uint8) PORT_PIN_P56_LEVEL_VALUE << PORT_BIT_OFFSET_6 )\
   | (uint8) ((uint8) PORT_PIN_P57_LEVEL_VALUE << PORT_BIT_OFFSET_7) )
   
/* PORT_5 - data direction register value */

#define PORT_PM5_VALUE \
   ((uint8) ((uint8) PORT_PIN_P50_DIRECTION << PORT_BIT_OFFSET_0) \
   | (uint8) ((uint8) PORT_PIN_P51_DIRECTION << PORT_BIT_OFFSET_1) \
   | (uint8) ((uint8) PORT_PIN_P52_DIRECTION << PORT_BIT_OFFSET_2) \
   | (uint8) ((uint8) PORT_PIN_P53_DIRECTION << PORT_BIT_OFFSET_3) \
   | (uint8) ((uint8) PORT_PIN_P54_DIRECTION << PORT_BIT_OFFSET_4) \
   | (uint8) ((uint8) PORT_PIN_P55_DIRECTION << PORT_BIT_OFFSET_5) \
   | (uint8) ((uint8) PORT_PIN_P56_DIRECTION << PORT_BIT_OFFSET_6) \
   | (uint8) ((uint8) PORT_PIN_P57_DIRECTION << PORT_BIT_OFFSET_7) )

/* PORT_5 - pull resistor enable register */

#define PORT_PU5_VALUE \
   ( (uint8) ((uint8) PORT_PIN_P50_PULL_RESISTOR << PORT_BIT_OFFSET_0) \
   | (uint8) ((uint8) PORT_PIN_P51_PULL_RESISTOR << PORT_BIT_OFFSET_1) \
   | (uint8) ((uint8) PORT_PIN_P52_PULL_RESISTOR << PORT_BIT_OFFSET_2) \
   | (uint8) ((uint8) PORT_PIN_P53_PULL_RESISTOR << PORT_BIT_OFFSET_3) \
   | (uint8) ((uint8) PORT_PIN_P54_PULL_RESISTOR << PORT_BIT_OFFSET_4) \
   | (uint8) ((uint8) PORT_PIN_P55_PULL_RESISTOR << PORT_BIT_OFFSET_5) \
   | (uint8) ((uint8) PORT_PIN_P56_PULL_RESISTOR << PORT_BIT_OFFSET_6) \
   | (uint8) ((uint8) PORT_PIN_P57_PULL_RESISTOR << PORT_BIT_OFFSET_7) )

/*----------------------------------------------------------------------------*\
 *                PORT_6
\*----------------------------------------------------------------------------*/
#define PORT_P6_VALUE \
   ( (uint8) ((uint8) PORT_PIN_P60_LEVEL_VALUE << PORT_BIT_OFFSET_0) \
   | (uint8) ((uint8) PORT_PIN_P61_LEVEL_VALUE << PORT_BIT_OFFSET_1) \
   | (uint8) ((uint8) PORT_PIN_P62_LEVEL_VALUE << PORT_BIT_OFFSET_2) \
   | (uint8) ((uint8) PORT_PIN_P63_LEVEL_VALUE << PORT_BIT_OFFSET_3) \
   | (uint8) ((uint8) PORT_PIN_P64_LEVEL_VALUE << PORT_BIT_OFFSET_4) \
   | (uint8) ((uint8) PORT_PIN_P65_LEVEL_VALUE << PORT_BIT_OFFSET_5) \
   | (uint8) ((uint8) PORT_PIN_P66_LEVEL_VALUE << PORT_BIT_OFFSET_6) \
   | (uint8) ((uint8) PORT_PIN_P67_LEVEL_VALUE << PORT_BIT_OFFSET_7) )
   
/* PORT_6 - data direction register value */

#define PORT_PM6_VALUE \
   ((uint8) ((uint8) PORT_PIN_P60_DIRECTION << PORT_BIT_OFFSET_0) \
   | (uint8) ((uint8) PORT_PIN_P61_DIRECTION << PORT_BIT_OFFSET_1) \
   | (uint8) ((uint8) PORT_PIN_P62_DIRECTION << PORT_BIT_OFFSET_2) \
   | (uint8) ((uint8) PORT_PIN_P63_DIRECTION << PORT_BIT_OFFSET_3) \
   | (uint8) ((uint8) PORT_PIN_P64_DIRECTION << PORT_BIT_OFFSET_4) \
   | (uint8) ((uint8) PORT_PIN_P65_DIRECTION << PORT_BIT_OFFSET_5) \
   | (uint8) ((uint8) PORT_PIN_P66_DIRECTION << PORT_BIT_OFFSET_6) \
   | (uint8) ((uint8) PORT_PIN_P67_DIRECTION << PORT_BIT_OFFSET_7) )
   
/* PORT_6 - pull resistor enable register */

#define PORT_PU6_VALUE \
   ( (uint8) ((uint8) PORT_PIN_P60_PULL_RESISTOR << PORT_BIT_OFFSET_0) \
   | (uint8) ((uint8) PORT_PIN_P61_PULL_RESISTOR << PORT_BIT_OFFSET_1) \
   | (uint8) ((uint8) PORT_PIN_P62_PULL_RESISTOR << PORT_BIT_OFFSET_2) \
   | (uint8) ((uint8) PORT_PIN_P63_PULL_RESISTOR << PORT_BIT_OFFSET_3) \
   | (uint8) ((uint8) PORT_PIN_P64_PULL_RESISTOR << PORT_BIT_OFFSET_4) \
   | (uint8) ((uint8) PORT_PIN_P65_PULL_RESISTOR << PORT_BIT_OFFSET_5) \
   | (uint8) ((uint8) PORT_PIN_P66_PULL_RESISTOR << PORT_BIT_OFFSET_6) \
   | (uint8) ((uint8) PORT_PIN_P67_PULL_RESISTOR << PORT_BIT_OFFSET_7) )

/* PORT_6 - port input mode register */

#define PORT_PIM6_VALUE \
   ((uint8)0x00 \
   | (uint8) ((uint8) PORT_PIN_P60_PIM << PORT_BIT_OFFSET_0) \
   | (uint8) ((uint8) PORT_PIN_P61_PIM << PORT_BIT_OFFSET_1) \
   | (uint8) ((uint8) PORT_PIN_P63_PIM << PORT_BIT_OFFSET_3) )

/*----------------------------------------------------------------------------*\
 *                PORT_7
\*----------------------------------------------------------------------------*/
#define PORT_P7_VALUE \
   ( (uint8) ((uint8) PORT_PIN_P70_LEVEL_VALUE << PORT_BIT_OFFSET_0) \
   | (uint8) ((uint8) PORT_PIN_P71_LEVEL_VALUE << PORT_BIT_OFFSET_1) \
   | (uint8) ((uint8) PORT_PIN_P72_LEVEL_VALUE << PORT_BIT_OFFSET_2) \
   | (uint8) ((uint8) PORT_PIN_P73_LEVEL_VALUE << PORT_BIT_OFFSET_3) \
   | (uint8) ((uint8) PORT_PIN_P74_LEVEL_VALUE << PORT_BIT_OFFSET_4) \
   | (uint8) ((uint8) PORT_PIN_P75_LEVEL_VALUE << PORT_BIT_OFFSET_5) \
   | (uint8) ((uint8) PORT_PIN_P76_LEVEL_VALUE << PORT_BIT_OFFSET_6) \
   | (uint8) ((uint8) PORT_PIN_P77_LEVEL_VALUE << PORT_BIT_OFFSET_7) )

/* PORT_7 - data direction register value */

#define PORT_PM7_VALUE \
   ((uint8) ((uint8) PORT_PIN_P70_DIRECTION << PORT_BIT_OFFSET_0) \
   | (uint8) ((uint8) PORT_PIN_P71_DIRECTION << PORT_BIT_OFFSET_1) \
   | (uint8) ((uint8) PORT_PIN_P72_DIRECTION << PORT_BIT_OFFSET_2) \
   | (uint8) ((uint8) PORT_PIN_P73_DIRECTION << PORT_BIT_OFFSET_3) \
   | (uint8) ((uint8) PORT_PIN_P74_DIRECTION << PORT_BIT_OFFSET_4) \
   | (uint8) ((uint8) PORT_PIN_P75_DIRECTION << PORT_BIT_OFFSET_5) \
   | (uint8) ((uint8) PORT_PIN_P76_DIRECTION << PORT_BIT_OFFSET_6) \
   | (uint8) ((uint8) PORT_PIN_P77_DIRECTION << PORT_BIT_OFFSET_7) )

/* PORT_7 - pull resistor enable register */

#define PORT_PU7_VALUE \
   ( (uint8) ((uint8) PORT_PIN_P70_PULL_RESISTOR << PORT_BIT_OFFSET_0) \
   | (uint8) ((uint8) PORT_PIN_P71_PULL_RESISTOR << PORT_BIT_OFFSET_1) \
   | (uint8) ((uint8) PORT_PIN_P72_PULL_RESISTOR << PORT_BIT_OFFSET_2) \
   | (uint8) ((uint8) PORT_PIN_P73_PULL_RESISTOR << PORT_BIT_OFFSET_3) \
   | (uint8) ((uint8) PORT_PIN_P74_PULL_RESISTOR << PORT_BIT_OFFSET_4) \
   | (uint8) ((uint8) PORT_PIN_P75_PULL_RESISTOR << PORT_BIT_OFFSET_5) \
   | (uint8) ((uint8) PORT_PIN_P76_PULL_RESISTOR << PORT_BIT_OFFSET_6) \
   | (uint8) ((uint8) PORT_PIN_P77_PULL_RESISTOR << PORT_BIT_OFFSET_7) )

/* PORT_7 - port input mode register */

#define PORT_PIM7_VALUE \
   ((uint8)0x00 \
   | (uint8) ((uint8) PORT_PIN_P73_PIM << PORT_BIT_OFFSET_3) \
   | (uint8) ((uint8) PORT_PIN_P75_PIM << PORT_BIT_OFFSET_5) \
   | (uint8) ((uint8) PORT_PIN_P76_PIM << PORT_BIT_OFFSET_6) \
   | (uint8) ((uint8) PORT_PIN_P77_PIM << PORT_BIT_OFFSET_7) )

/* PORT_7 - port output mode register */

#define PORT_POM7_VALUE \
   ((uint8)0x00 \
   | (uint8) ((uint8) PORT_PIN_P72_POM << PORT_BIT_OFFSET_2) \
   | (uint8) ((uint8) PORT_PIN_P74_POM << PORT_BIT_OFFSET_4) \
   | (uint8) ((uint8) PORT_PIN_P76_POM << PORT_BIT_OFFSET_6) )

/*----------------------------------------------------------------------------*\
 *                PORT_8
\*----------------------------------------------------------------------------*/
#define PORT_P8_VALUE \
   ( (uint8) ((uint8) PORT_PIN_P80_LEVEL_VALUE << PORT_BIT_OFFSET_0) \
   | (uint8) ((uint8) PORT_PIN_P81_LEVEL_VALUE << PORT_BIT_OFFSET_1) \
   | (uint8) ((uint8) PORT_PIN_P82_LEVEL_VALUE << PORT_BIT_OFFSET_2) \
   | (uint8) ((uint8) PORT_PIN_P83_LEVEL_VALUE << PORT_BIT_OFFSET_3) \
   | (uint8) ((uint8) PORT_PIN_P84_LEVEL_VALUE << PORT_BIT_OFFSET_4) \
   | (uint8) ((uint8) PORT_PIN_P85_LEVEL_VALUE << PORT_BIT_OFFSET_5) \
   | (uint8) ((uint8) PORT_PIN_P86_LEVEL_VALUE << PORT_BIT_OFFSET_6) \
   | (uint8) ((uint8) PORT_PIN_P87_LEVEL_VALUE << PORT_BIT_OFFSET_7) )

/* PORT_8 - data direction register value */

#define PORT_PM8_VALUE \
   ((uint8) ((uint8) PORT_PIN_P80_DIRECTION << PORT_BIT_OFFSET_0) \
   | (uint8) ((uint8) PORT_PIN_P81_DIRECTION << PORT_BIT_OFFSET_1) \
   | (uint8) ((uint8) PORT_PIN_P82_DIRECTION << PORT_BIT_OFFSET_2) \
   | (uint8) ((uint8) PORT_PIN_P83_DIRECTION << PORT_BIT_OFFSET_3) \
   | (uint8) ((uint8) PORT_PIN_P84_DIRECTION << PORT_BIT_OFFSET_4) \
   | (uint8) ((uint8) PORT_PIN_P85_DIRECTION << PORT_BIT_OFFSET_5) \
   | (uint8) ((uint8) PORT_PIN_P86_DIRECTION << PORT_BIT_OFFSET_6) \
   | (uint8) ((uint8) PORT_PIN_P87_DIRECTION << PORT_BIT_OFFSET_7) )

/*----------------------------------------------------------------------------*\
 *                PORT_9
\*----------------------------------------------------------------------------*/
#define PORT_P9_VALUE \
   ( (uint8) ((uint8) PORT_PIN_P90_LEVEL_VALUE << PORT_BIT_OFFSET_0) \
   | (uint8) ((uint8) PORT_PIN_P91_LEVEL_VALUE << PORT_BIT_OFFSET_1) \
   | (uint8) ((uint8) PORT_PIN_P92_LEVEL_VALUE << PORT_BIT_OFFSET_2) \
   | (uint8) ((uint8) PORT_PIN_P93_LEVEL_VALUE << PORT_BIT_OFFSET_3) \
   | (uint8) ((uint8) PORT_PIN_P94_LEVEL_VALUE << PORT_BIT_OFFSET_4) \
   | (uint8) ((uint8) PORT_PIN_P95_LEVEL_VALUE << PORT_BIT_OFFSET_5) \
   | (uint8) ((uint8) PORT_PIN_P96_LEVEL_VALUE << PORT_BIT_OFFSET_6) \
   | (uint8) ((uint8) PORT_PIN_P97_LEVEL_VALUE << PORT_BIT_OFFSET_7 ))

/* PORT_9 - data direction register value */

#define PORT_PM9_VALUE \
   ((uint8) ((uint8) PORT_PIN_P90_DIRECTION << PORT_BIT_OFFSET_0) \
   | (uint8) ((uint8) PORT_PIN_P91_DIRECTION << PORT_BIT_OFFSET_1) \
   | (uint8) ((uint8) PORT_PIN_P92_DIRECTION << PORT_BIT_OFFSET_2) \
   | (uint8) ((uint8) PORT_PIN_P93_DIRECTION << PORT_BIT_OFFSET_3) \
   | (uint8) ((uint8) PORT_PIN_P94_DIRECTION << PORT_BIT_OFFSET_4) \
   | (uint8) ((uint8) PORT_PIN_P95_DIRECTION << PORT_BIT_OFFSET_5) \
   | (uint8) ((uint8) PORT_PIN_P96_DIRECTION << PORT_BIT_OFFSET_6) \
   | (uint8) ((uint8) PORT_PIN_P97_DIRECTION<< PORT_BIT_OFFSET_7) )

/*----------------------------------------------------------------------------*\
 *                PORT_12
\*----------------------------------------------------------------------------*/
#define PORT_P12_VALUE \
   ( (uint8) ((uint8) PORT_PIN_P120_LEVEL_VALUE << PORT_BIT_OFFSET_0) \
   | (uint8) ((uint8) PORT_PIN_P121_LEVEL_VALUE << PORT_BIT_OFFSET_1) \
   | (uint8) ((uint8) PORT_PIN_P122_LEVEL_VALUE << PORT_BIT_OFFSET_2) \
   | (uint8) ((uint8) PORT_PIN_P123_LEVEL_VALUE << PORT_BIT_OFFSET_3) \
   | (uint8) ((uint8) PORT_PIN_P124_LEVEL_VALUE << PORT_BIT_OFFSET_4) \
   | (uint8) ((uint8) PORT_PIN_P125_LEVEL_VALUE << PORT_BIT_OFFSET_5) \
   | (uint8) ((uint8) PORT_PIN_P126_LEVEL_VALUE << PORT_BIT_OFFSET_6) )

/* PORT_12 - data direction register value */

#define PORT_PM12_VALUE \
   ((uint8) ((uint8) PORT_PIN_P120_DIRECTION << PORT_BIT_OFFSET_0) \
   | (uint8) ((uint8) PORT_PIN_P121_DIRECTION << PORT_BIT_OFFSET_1) \
   | (uint8) ((uint8) PORT_PIN_P122_DIRECTION << PORT_BIT_OFFSET_2) \
   | (uint8) ((uint8) PORT_PIN_P123_DIRECTION << PORT_BIT_OFFSET_3) \
   | (uint8) ((uint8) PORT_PIN_P124_DIRECTION << PORT_BIT_OFFSET_4) \
   | (uint8) ((uint8) PORT_PIN_P125_DIRECTION << PORT_BIT_OFFSET_5) \
   | (uint8) ((uint8) PORT_PIN_P126_DIRECTION<< PORT_BIT_OFFSET_6) \
   | (uint8) ((uint8) 1 << PORT_BIT_OFFSET_7) )

/* PORT_12 - pull resistor enable register */

#define PORT_PU12_VALUE \
   ( (uint8) ((uint8) PORT_PIN_P120_PULL_RESISTOR << PORT_BIT_OFFSET_0) \
   | (uint8) ((uint8) PORT_PIN_P125_PULL_RESISTOR << PORT_BIT_OFFSET_5) \
   | (uint8) ((uint8) PORT_PIN_P126_PULL_RESISTOR << PORT_BIT_OFFSET_6) )

/*----------------------------------------------------------------------------*\
 *                PORT_13
\*----------------------------------------------------------------------------*/
#define PORT_P13_VALUE \
   ((uint8)0x00 \
   |(uint8) ((uint8) PORT_PIN_P130_LEVEL_VALUE << PORT_BIT_OFFSET_0) )

/*----------------------------------------------------------------------------*\
 *                PORT_14
\*----------------------------------------------------------------------------*/
#define PORT_P14_VALUE \
   ((uint8)0x00 \
   |(uint8) ((uint8) PORT_PIN_P140_LEVEL_VALUE << PORT_BIT_OFFSET_0) )

/* PORT_14 - data direction register value */

#define PORT_PM14_VALUE \
   ((uint8) ((uint8) PORT_PIN_P140_DIRECTION << PORT_BIT_OFFSET_0) \
   | (uint8) ((uint8) 1 << PORT_BIT_OFFSET_1) \
   | (uint8) ((uint8) 1 << PORT_BIT_OFFSET_2) \
   | (uint8) ((uint8) 1 << PORT_BIT_OFFSET_3) \
   | (uint8) ((uint8) 1 << PORT_BIT_OFFSET_4) \
   | (uint8) ((uint8) 1 << PORT_BIT_OFFSET_5) \
   | (uint8) ((uint8) 1 << PORT_BIT_OFFSET_6) \
   | (uint8) ((uint8) 1 << PORT_BIT_OFFSET_7) )

/* PORT_14 - pull resistor enable register */

#define PORT_PU14_VALUE \
   ((uint8)0x00 \
   |(uint8) ((uint8) PORT_PIN_P140_PULL_RESISTOR << PORT_BIT_OFFSET_0) )

/* Port slew rate select register */

#if 0
#define PORT_PSRSEL_VALUE \
   ((uint8)0x00 \
   |(uint8) ((uint8) PORT_PIN_P10_PSR << PORT_BIT_OFFSET_0) \
   |(uint8) ((uint8) PORT_PIN_P12_PSR << PORT_BIT_OFFSET_1) \
   |(uint8) ((uint8) PORT_PIN_P30_PSR << PORT_BIT_OFFSET_2) \
   |(uint8) ((uint8) PORT_PIN_P140_PSR << PORT_BIT_OFFSET_5) )
#else
#define PORT_PSRSEL_VALUE \
   ((uint8)0x00 \
   |(uint8) ((uint8) PORT_PIN_P12_PSR << PORT_BIT_OFFSET_1) \
   |(uint8) ((uint8) PORT_PIN_P30_PSR << PORT_BIT_OFFSET_2) \
   |(uint8) ((uint8) PORT_PIN_P140_PSR << PORT_BIT_OFFSET_5) )
#endif

#endif /* PORT_CFG_H */

