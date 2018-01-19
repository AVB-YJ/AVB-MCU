#ifdef POLYSPACE


#include "OS_Cfg.h"
extern int random_int(void);
extern void IrqVector_CANRx(void);
extern void IrqVector_CANTx(void);
extern void IrqVector_SysTick(void);
extern void IrqVector_CANErr(void);
extern void IrqVector_Adc(void);
extern void IrqVector_FreeRunningTimer(void);

uint8_t ItAllInterrupt = 0;


void OS_EnableAllInterrupts(void)
{
    ItAllInterrupt = 1;
}

void OS_DisableAllInterrupts(void)
{
    ItAllInterrupt = 0;
}

void pst_it1(void)
{
        while (random_int())
        {
                if (random_int() && ItAllInterrupt && (ADMK== 0)) IrqVector_Adc();
        }
}

void pst_it2(void)
{
        while (random_int())
        {
                if (random_int() && ItAllInterrupt  && (C0ERRMK == 0)) IrqVector_CANErr();
        }
}
void pst_it3(void)
{
        while (random_int())
        {
        if (random_int() && ItAllInterrupt && (C0RECMK == 0)) IrqVector_CANRx();
        }
}
void pst_it4(void)
{
        while (random_int())
        {
                if (random_int() && ItAllInterrupt  && (C0TRXMK == 0)) IrqVector_CANTx();             
        }
}

void pst_it5(void)
{
        while (random_int())
        {
        if (random_int() && ItAllInterrupt && (TMMK21 == 0)) IrqVector_SysTick();
        }
      
}

void pst_it6(void)
{
        while (random_int())
        {
        if (random_int() && ItAllInterrupt && (TMMK20 == 0)) IrqVector_FreeRunningTimer();
        }
      
}
#endif

