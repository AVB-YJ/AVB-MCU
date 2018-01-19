/*===========================================================================================*\
 * PREPROCESSOR DIRECTIVES
\*============================================================================*/

/* INCLUDE DIRECTIVES FOR STANDARD HEADERS -----------------------------------*/
#include "Port.h"

/* PRQA S 5087 EOF
 * MISRA RULE 19.1 VIOLATION:
 * #include added at several places to meet the requirements of Memory mapping.
 */
#define PORT_START_SEC_VAR_8BIT
#define PORT_STOP_SEC_VAR_8BIT
#define PORT_START_SEC_CODE

#include "MemMap.h"

/*===========================================================================================*\
 * FUNCTION: Port_Init()
 * For detailed explanation on the exported functions see Port.h file.
\*============================================================================*/
FUNC(void, PORT_CODE) Port_Init
(
   P2CONST(Port_ConfigType, PORT_CONST, PORT_APPL_CONST) ConfigPtr
)
{
      /* Port 0: value, direction and Pull-Up */
      P0   = PORT_P0_VALUE;
      PM0  = PORT_PM0_VALUE;
      PU0  = PORT_PU0_VALUE;
   
      /* Port 1: value, direction and Pull-Up */
      P1   = PORT_P1_VALUE;
      PM1  = PORT_PM1_VALUE;
      PU1  = PORT_PU1_VALUE;

      /* Port3: value, direction and Pull-Up */
      P3   = PORT_P3_VALUE;
      PM3  = PORT_PM3_VALUE;
      PU3  = PORT_PU3_VALUE;

      /* Port 4: value, direction, Pull-Up and Port output mode */
      P4   = PORT_P4_VALUE;
      PM4  = PORT_PM4_VALUE;
      PU4  = PORT_PU4_VALUE;
	  POM4 = PORT_POM4_VALUE;

	  /* Port 5: value, direction and Pull-Up */
      P5   = PORT_P5_VALUE;
      PM5  = PORT_PM5_VALUE;
      PU5  = PORT_PU5_VALUE;
	  
      /* Port 6: value, direction, Pull-Up and Port input mode */
      P6   = PORT_P6_VALUE;
      PM6  = PORT_PM6_VALUE;
      PU6  = PORT_PU6_VALUE;
      PIM6 = PORT_PIM6_VALUE;

      /* Port 7: value, direction, Pull-Up, Port Input and Port output mode */
      P7   = PORT_P7_VALUE;
      PM7  = PORT_PM7_VALUE;
      PU7  = PORT_PU7_VALUE;
      PIM7 = PORT_PIM7_VALUE;
      POM7 = PORT_POM7_VALUE;

      /* Port 8: value and direction */
      P8   = PORT_P8_VALUE;
      PM8  = PORT_PM8_VALUE;

      /* Port 9: value and direction  */
      P9   = PORT_P9_VALUE;
      PM9  = PORT_PM9_VALUE;
	  
      /* Port 12: value, direction and Pull-Up */
      P12  = PORT_P12_VALUE;
      PM12 = PORT_PM12_VALUE;
      PU12 = PORT_PU12_VALUE;

      /* Port 13: value */
      P13  = PORT_P13_VALUE;

      /* Port 14: value, direction and Pull-Up */
      P14  = PORT_P14_VALUE;
      PM14 = PORT_PM14_VALUE;
      PU14 = PORT_PU14_VALUE;

      /* Port output slew rate select register */
      PSRSEL = PORT_PSRSEL_VALUE;
      
      /* Set init value fot ADPC - A/D port configuration register */
      ADCEN = 1;
      ADPC = PORT_ADPC_VALUE;
      ADCEN = 0;
}

/*===========================================================================================*\
 * FUNCTION: Port_SetPinDirection()
 * For detailed explanation on the exported functions see Port.h file.
\*============================================================================*/
void  Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction)
{
	switch (Pin)
	{
		/*=============================PORT 0 =============================*/
		case PORT_PIN_P00:
			PM0_bit.no0 = (uint8)Direction;
			break;
		case PORT_PIN_P01:
			PM0_bit.no1 = (uint8)Direction;
			break;
		case PORT_PIN_P02:
			PM0_bit.no2 = (uint8)Direction;
			break;	 
		
		/*=============================PORT 1 =============================*/
		
		case PORT_PIN_P10:
			PM1_bit.no0 = (uint8)Direction;
			break;
		case PORT_PIN_P11:
			PM1_bit.no1 = (uint8)Direction;
			break;
		case PORT_PIN_P12:
			PM1_bit.no2 = (uint8)Direction;
			break;
		case PORT_PIN_P13:
			PM1_bit.no3 = (uint8)Direction;
			break;
		case PORT_PIN_P14:
			PM1_bit.no4 = (uint8)Direction;
			break;
		case PORT_PIN_P15:
			PM1_bit.no5 = (uint8)Direction;
			break;
		case PORT_PIN_P16:
			PM1_bit.no6 = (uint8)Direction;
			break;
		case PORT_PIN_P17:
			PM1_bit.no7 = (uint8)Direction;
			break;
		case PORT_PIN_P30:
			PM3_bit.no0 = (uint8)Direction;
			break;
		case PORT_PIN_P31:
			PM3_bit.no1 = (uint8)Direction;
			break;
		case PORT_PIN_P32:
			PM3_bit.no2 = (uint8)Direction;
			break;
		case PORT_PIN_P40:
			PM4_bit.no0 = (uint8)Direction;
			break;
		case PORT_PIN_P41:
			PM4_bit.no1 = (uint8)Direction;
			break;
		case PORT_PIN_P42:
			PM4_bit.no2 = (uint8)Direction;
			break;
		case PORT_PIN_P43:
			PM4_bit.no3 = (uint8)Direction;
			break;
		case PORT_PIN_P44:
			PM4_bit.no4 = (uint8)Direction;
			break;
		case PORT_PIN_P45:
			PM4_bit.no5 = (uint8)Direction;
			break;
		case PORT_PIN_P46:
			PM4_bit.no6 = (uint8)Direction;
			break;
		case PORT_PIN_P47:
			PM4_bit.no7 = (uint8)Direction;
			break;
		case PORT_PIN_P50:
			PM5_bit.no0 = (uint8)Direction;
			break;
		case PORT_PIN_P51:
			PM5_bit.no1 = (uint8)Direction;
			break;
		case PORT_PIN_P52:
			PM5_bit.no2 = (uint8)Direction;
			break;
		case PORT_PIN_P53:
			PM5_bit.no3 = (uint8)Direction;
			break;
		case PORT_PIN_P54:
			PM5_bit.no4 = (uint8)Direction;
			break;
		case PORT_PIN_P55:
			PM5_bit.no5 = (uint8)Direction;
			break;
		case PORT_PIN_P56:
			PM5_bit.no6 = (uint8)Direction;
			break;
		case PORT_PIN_P57:
			PM5_bit.no7 = (uint8)Direction;
			break;
		
		/*=============================PORT 6 =============================*/
		
		case PORT_PIN_P60:
			PM6_bit.no0 = (uint8)Direction;
			break;
		case PORT_PIN_P61:
			PM6_bit.no1 = (uint8)Direction;
			break;
		case PORT_PIN_P62:
			PM6_bit.no2 = (uint8)Direction;
			break;
		case PORT_PIN_P63:
			PM6_bit.no3 = (uint8)Direction;
			break;
		case PORT_PIN_P64:
			PM6_bit.no4 = (uint8)Direction;
			break;
		case PORT_PIN_P65:
			PM6_bit.no5 = (uint8)Direction;
			break;
		case PORT_PIN_P66:
			PM6_bit.no6 = (uint8)Direction;
			break;
		case PORT_PIN_P67:
			PM6_bit.no7 = (uint8)Direction;
			break;
		
		/*=============================PORT 7 =============================*/
		
		case PORT_PIN_P70:
			PM7_bit.no0 = (uint8)Direction;
			break;
		case PORT_PIN_P71:
			PM7_bit.no1 = (uint8)Direction;
			break;
		case PORT_PIN_P72:
			PM7_bit.no2 = (uint8)Direction;
			break;
		case PORT_PIN_P73:
			PM7_bit.no3 = (uint8)Direction;
			break;
		case PORT_PIN_P74:
			PM7_bit.no4 = (uint8)Direction;
			break;
		case PORT_PIN_P75:
			PM7_bit.no5 = (uint8)Direction;
			break;
		case PORT_PIN_P76:
			PM7_bit.no6 = (uint8)Direction;
			break;
		case PORT_PIN_P77:
			PM7_bit.no7 = (uint8)Direction;
			break;
		
		/*=============================PORT 8 =============================*/
		
		case PORT_PIN_P80:
			PM8_bit.no0 = (uint8)Direction;
			break;
		case PORT_PIN_P81:
			PM8_bit.no1 = (uint8)Direction;
			break;
		case PORT_PIN_P82:
			PM8_bit.no2 = (uint8)Direction;
			break;
		case PORT_PIN_P83:
			PM8_bit.no3 = (uint8)Direction;
			break;
		case PORT_PIN_P84:
			PM8_bit.no4 = (uint8)Direction;
			break;
		case PORT_PIN_P85:
			PM8_bit.no5 = (uint8)Direction;
			break;		
		case PORT_PIN_P86:
			PM8_bit.no6 = (uint8)Direction;
			break;
		case PORT_PIN_P87:
			PM8_bit.no7 = (uint8)Direction;
			break;
		
		/*=============================PORT 9 =============================*/
		
		case PORT_PIN_P90:
			PM9_bit.no0 = (uint8)Direction;
			break;
		case PORT_PIN_P91:
			PM9_bit.no1 = (uint8)Direction;
			break;
		case PORT_PIN_P92:
			PM9_bit.no2 = (uint8)Direction;
			break;
		case PORT_PIN_P93:
			PM9_bit.no3 = (uint8)Direction;
			break;
		case PORT_PIN_P94:
			PM9_bit.no4 = (uint8)Direction;
			break;
		case PORT_PIN_P95:
			PM9_bit.no5 = (uint8)Direction;
			break;
		case PORT_PIN_P96:
			PM9_bit.no6 = (uint8)Direction;
			break;
		case PORT_PIN_P97:
			PM9_bit.no7 = (uint8)Direction;
			break;
		
		/*=============================PORT 12 =============================*/
		
		case PORT_PIN_P120:
			PM12_bit.no0 = (uint8)Direction;
			break;
		case PORT_PIN_P121:
			PM12_bit.no1 = (uint8)Direction;
			break;
		case PORT_PIN_P122:
			PM12_bit.no2 = (uint8)Direction;
			break;
		case PORT_PIN_P123:
			PM12_bit.no3 = (uint8)Direction;
			break;
		case PORT_PIN_P124:
			PM12_bit.no4 = (uint8)Direction;
			break;
		case PORT_PIN_P125:
			PM12_bit.no5 = (uint8)Direction;
			break;
		case PORT_PIN_P126:
			PM12_bit.no6 = (uint8)Direction;
			break;
		
		/*=============================PORT 14 =============================*/
		
		case PORT_PIN_P140:
			PM14_bit.no0 = (uint8)Direction;
			break;
		
		/*=============================DEFAULT =============================*/
		
		default:
			break;
	}
}