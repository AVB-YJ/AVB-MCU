/*-------------------------------------------------------------------------
 *      Declarations of SFR registers, interrupt and callt vector addresses
 *      for 78K0R microcontroller uPD78F1840_80.
 *
 *      This file can be used by both the 78K0R,
 *      Assembler, A78K0R, and the C/C++ compiler, ICC78K0R.
 *
 *      This header file is generated from the device file:
 *          DF184080.78K
 *          Copyright (C) NEC Corporation 2009
 *          Format version V3.00, File version V1.01
 *-------------------------------------------------------------------------*/

#ifndef __IO78F1840_80_H__
#define __IO78F1840_80_H__

#if !defined(__A78K__) && !defined(__ICC78K__)
  #error "IO78F1840_80.H file for use with 78K Series Assembler or Compiler only"
#endif

#if defined(__A78K__)
  #if __CORE__ != __78K0R__
    #error "IO78F1840_80_EXT.H file for use with A78K0R option --core 78k0r only"
  #endif
#endif
#if defined(__ICC78K__)
  #if __CORE__ != __78K0R__
    #error "IO78F1840_80_EXT.H file for use with ICC78K0R option --core 78k0r only"
  #endif
#endif

#ifdef __IAR_SYSTEMS_ICC__

#pragma language=extended
#pragma system_include

/*----------------------------------------------
 * SFR bits (default names)
 *--------------------------------------------*/

#ifndef __78K_BIT_STRUCTURE__
  #define __78K_BIT_STRUCTURE__
  typedef struct
  {
    unsigned char no0:1;
    unsigned char no1:1;
    unsigned char no2:1;
    unsigned char no3:1;
    unsigned char no4:1;
    unsigned char no5:1;
    unsigned char no6:1;
    unsigned char no7:1;
  } __BITS8;
#endif

/*----------------------------------------------
 *       SFR declarations
 *--------------------------------------------*/

extern __saddr __no_init volatile union { unsigned char P0; __BITS8 P0_bit; } @ 0xFFF00;
extern __saddr __no_init volatile union { unsigned char P1; __BITS8 P1_bit; } @ 0xFFF01;
extern __saddr __no_init volatile union { unsigned char P3; __BITS8 P3_bit; } @ 0xFFF03;
extern __saddr __no_init volatile union { unsigned char P4; __BITS8 P4_bit; } @ 0xFFF04;
extern __saddr __no_init volatile union { unsigned char P5; __BITS8 P5_bit; } @ 0xFFF05;
extern __saddr __no_init volatile union { unsigned char P6; __BITS8 P6_bit; } @ 0xFFF06;
extern __saddr __no_init volatile union { unsigned char P7; __BITS8 P7_bit; } @ 0xFFF07;
extern __saddr __no_init volatile union { unsigned char P8; __BITS8 P8_bit; } @ 0xFFF08;
extern __saddr __no_init volatile union { unsigned char P9; __BITS8 P9_bit; } @ 0xFFF09;
extern __saddr __no_init volatile union { unsigned char P12; __BITS8 P12_bit; } @ 0xFFF0C;
extern __saddr __no_init volatile union { unsigned char P13; __BITS8 P13_bit; } @ 0xFFF0D;
extern __saddr __no_init volatile union { unsigned char P14; __BITS8 P14_bit; } @ 0xFFF0E;
extern __saddr __no_init volatile union { unsigned short SDR00; struct { union { unsigned char SDR00L; __BITS8 SDR00L_bit; }; }; } @ 0xFFF10;
extern __saddr __no_init volatile union { unsigned short SDR01; struct { union { unsigned char SDR01L; __BITS8 SDR01L_bit; }; }; } @ 0xFFF12;
extern __saddr __no_init volatile union { unsigned short SDR10; struct { union { unsigned char SDR10L; __BITS8 SDR10L_bit; }; }; } @ 0xFFF14;
extern __saddr __no_init volatile union { unsigned short SDR11; struct { union { unsigned char SDR11L; __BITS8 SDR11L_bit; }; }; } @ 0xFFF16;
extern __saddr __no_bit_access __no_init volatile unsigned short TDR00 @ 0xFFF18;
extern __saddr __no_bit_access __no_init volatile unsigned short TDR01 @ 0xFFF1A;
extern __saddr __no_bit_access __no_init volatile union { unsigned short ADCR; struct { unsigned char :8; const unsigned char ADCRH; }; } @ 0xFFF1E;
extern __sfr __no_init volatile union { unsigned char PM0; __BITS8 PM0_bit; } @ 0xFFF20;
extern __sfr __no_init volatile union { unsigned char PM1; __BITS8 PM1_bit; } @ 0xFFF21;
extern __sfr __no_init volatile union { unsigned char PM3; __BITS8 PM3_bit; } @ 0xFFF23;
extern __sfr __no_init volatile union { unsigned char PM4; __BITS8 PM4_bit; } @ 0xFFF24;
extern __sfr __no_init volatile union { unsigned char PM5; __BITS8 PM5_bit; } @ 0xFFF25;
extern __sfr __no_init volatile union { unsigned char PM6; __BITS8 PM6_bit; } @ 0xFFF26;
extern __sfr __no_init volatile union { unsigned char PM7; __BITS8 PM7_bit; } @ 0xFFF27;
extern __sfr __no_init volatile union { unsigned char PM8; __BITS8 PM8_bit; } @ 0xFFF28;
extern __sfr __no_init volatile union { unsigned char PM9; __BITS8 PM9_bit; } @ 0xFFF29;
extern __sfr __no_init volatile union { unsigned char PM12; __BITS8 PM12_bit; } @ 0xFFF2C;
extern __sfr __no_init volatile union { unsigned char PM14; __BITS8 PM14_bit; } @ 0xFFF2E;
extern __sfr __no_init volatile union { unsigned char ADM0; __BITS8 ADM0_bit; } @ 0xFFF30;
extern __sfr __no_init volatile union { unsigned char ADS; __BITS8 ADS_bit; } @ 0xFFF31;
extern __sfr __no_init volatile union { unsigned char ADSMP; __BITS8 ADSMP_bit; } @ 0xFFF33;
extern __sfr __no_init volatile union { unsigned char IPSEL0; __BITS8 IPSEL0_bit; } @ 0xFFF36;
extern __sfr __no_init volatile union { unsigned char KRM; __BITS8 KRM_bit; } @ 0xFFF37;
extern __sfr __no_init volatile union { unsigned char EGP0; __BITS8 EGP0_bit; } @ 0xFFF38;
extern __sfr __no_init volatile union { unsigned char EGN0; __BITS8 EGN0_bit; } @ 0xFFF39;
extern __sfr __no_init volatile union { unsigned char EGP1; __BITS8 EGP1_bit; } @ 0xFFF3A;
extern __sfr __no_init volatile union { unsigned char EGN1; __BITS8 EGN1_bit; } @ 0xFFF3B;
extern __sfr __no_init volatile union { unsigned char STSEL; __BITS8 STSEL_bit; } @ 0xFFF3C;
extern __sfr __no_init volatile union { unsigned char TIS0; __BITS8 TIS0_bit; } @ 0xFFF3E;
extern __sfr __no_init volatile union { unsigned char TIS1; __BITS8 TIS1_bit; } @ 0xFFF3F;
extern __sfr __no_init volatile union { unsigned char ADM1; __BITS8 ADM1_bit; } @ 0xFFF42;
extern __sfr __no_init volatile union { unsigned short SDR20; struct { union { unsigned char SDR20L; __BITS8 SDR20L_bit; }; }; } @ 0xFFF44;
extern __sfr __no_init volatile union { unsigned short SDR21; struct { union { unsigned char SDR21L; __BITS8 SDR21L_bit; }; }; } @ 0xFFF46;
extern __sfr __no_init volatile union { unsigned short UF0TX; struct { union { unsigned char UF0TXB; __BITS8 UF0TXB_bit; }; }; } @ 0xFFF48;
extern __sfr __no_init volatile union { unsigned short UF0RX; struct { union { unsigned char UF0RXB; __BITS8 UF0RXB_bit; }; }; } @ 0xFFF4A;
extern __sfr __no_init volatile union { unsigned short UF1TX; struct { union { unsigned char UF1TXB; __BITS8 UF1TXB_bit; }; }; } @ 0xFFF4C;
extern __sfr __no_init volatile union { unsigned short UF1RX; struct { union { unsigned char UF1RXB; __BITS8 UF1RXB_bit; }; }; } @ 0xFFF4E;
extern __sfr __no_init volatile union { unsigned char TOS0; __BITS8 TOS0_bit; } @ 0xFFF60;
extern __sfr __no_init volatile union { unsigned char TOS1; __BITS8 TOS1_bit; } @ 0xFFF61;
extern __sfr __no_bit_access __no_init volatile unsigned short TDR02 @ 0xFFF64;
extern __sfr __no_bit_access __no_init volatile unsigned short TDR03 @ 0xFFF66;
extern __sfr __no_bit_access __no_init volatile unsigned short TDR04 @ 0xFFF68;
extern __sfr __no_bit_access __no_init volatile unsigned short TDR05 @ 0xFFF6A;
extern __sfr __no_bit_access __no_init volatile unsigned short TDR06 @ 0xFFF6C;
extern __sfr __no_bit_access __no_init volatile unsigned short TDR07 @ 0xFFF6E;
extern __sfr __no_bit_access __no_init volatile unsigned short TDR10 @ 0xFFF70;
extern __sfr __no_bit_access __no_init volatile unsigned short TDR11 @ 0xFFF72;
extern __sfr __no_bit_access __no_init volatile unsigned short TDR12 @ 0xFFF74;
extern __sfr __no_bit_access __no_init volatile unsigned short TDR13 @ 0xFFF76;
extern __sfr __no_bit_access __no_init volatile unsigned short TDR14 @ 0xFFF78;
extern __sfr __no_bit_access __no_init volatile unsigned short TDR15 @ 0xFFF7A;
extern __sfr __no_bit_access __no_init volatile unsigned short TDR16 @ 0xFFF7C;
extern __sfr __no_bit_access __no_init volatile unsigned short TDR17 @ 0xFFF7E;
extern __sfr __no_bit_access __no_init volatile unsigned short TDR20 @ 0xFFF90;
extern __sfr __no_bit_access __no_init volatile unsigned short TDR21 @ 0xFFF92;
extern __sfr __no_bit_access __no_init volatile unsigned short TDR22 @ 0xFFF94;
extern __sfr __no_bit_access __no_init volatile unsigned short TDR23 @ 0xFFF96;
extern __sfr __no_bit_access __no_init volatile unsigned char CMC @ 0xFFFA0;
extern __sfr __no_init volatile union { unsigned char CSC; __BITS8 CSC_bit; } @ 0xFFFA1;
extern __sfr __no_init volatile const union { unsigned char OSTC; __BITS8 OSTC_bit; } @ 0xFFFA2;
extern __sfr __no_bit_access __no_init volatile unsigned char OSTS @ 0xFFFA3;
extern __sfr __no_init volatile union { unsigned char CKC; __BITS8 CKC_bit; } @ 0xFFFA4;
extern __sfr __no_init volatile union { unsigned char CKS; __BITS8 CKS_bit; } @ 0xFFFA5;
extern __sfr __no_bit_access __no_init volatile const unsigned char RESF @ 0xFFFA8;
extern __sfr __no_init volatile union { unsigned char LVIM; __BITS8 LVIM_bit; } @ 0xFFFA9;
extern __sfr __no_init volatile union { unsigned char LVIS; __BITS8 LVIS_bit; } @ 0xFFFAA;
extern __sfr __no_bit_access __no_init volatile unsigned char WDTE @ 0xFFFAB;
extern __sfr __no_init volatile union { unsigned char WUTMCTL; __BITS8 WUTMCTL_bit; } @ 0xFFFAC;
extern __sfr __no_bit_access __no_init volatile unsigned short WUTMCMP @ 0xFFFAE;
extern __sfr __no_bit_access __no_init volatile unsigned char DSA0 @ 0xFFFB0;
extern __sfr __no_bit_access __no_init volatile unsigned char DSA1 @ 0xFFFB1;
extern __sfr __no_bit_access __no_init volatile union { unsigned short DRA0; struct { unsigned char DRA0L; unsigned char DRA0H; }; } @ 0xFFFB2;
extern __sfr __no_bit_access __no_init volatile union { unsigned short DRA1; struct { unsigned char DRA1L; unsigned char DRA1H; }; } @ 0xFFFB4;
extern __sfr __no_bit_access __no_init volatile union { unsigned short DBC0; struct { unsigned char DBC0L; unsigned char DBC0H; }; } @ 0xFFFB6;
extern __sfr __no_bit_access __no_init volatile union { unsigned short DBC1; struct { unsigned char DBC1L; unsigned char DBC1H; }; } @ 0xFFFB8;
extern __sfr __no_init volatile union { unsigned char DMC0; __BITS8 DMC0_bit; } @ 0xFFFBA;
extern __sfr __no_init volatile union { unsigned char DMC1; __BITS8 DMC1_bit; } @ 0xFFFBB;
extern __sfr __no_init volatile union { unsigned char DRC0; __BITS8 DRC0_bit; } @ 0xFFFBC;
extern __sfr __no_init volatile union { unsigned char DRC1; __BITS8 DRC1_bit; } @ 0xFFFBD;
extern __sfr __no_init volatile union { unsigned char BECTL; __BITS8 BECTL_bit; } @ 0xFFFBE;
extern __sfr __no_init volatile union { unsigned short IF2; struct { union { unsigned char IF2L; __BITS8 IF2L_bit; }; union { unsigned char IF2H; __BITS8 IF2H_bit; }; }; } @ 0xFFFD0;
extern __sfr __no_init volatile union { unsigned short IF3; struct { union { unsigned char IF3L; __BITS8 IF3L_bit; }; union { unsigned char IF3H; __BITS8 IF3H_bit; }; }; } @ 0xFFFD2;
extern __sfr __no_init volatile union { unsigned short MK2; struct { union { unsigned char MK2L; __BITS8 MK2L_bit; }; union { unsigned char MK2H; __BITS8 MK2H_bit; }; }; } @ 0xFFFD4;
extern __sfr __no_init volatile union { unsigned short MK3; struct { union { unsigned char MK3L; __BITS8 MK3L_bit; }; union { unsigned char MK3H; __BITS8 MK3H_bit; }; }; } @ 0xFFFD6;
extern __sfr __no_init volatile union { unsigned short PR02; struct { union { unsigned char PR02L; __BITS8 PR02L_bit; }; union { unsigned char PR02H; __BITS8 PR02H_bit; }; }; } @ 0xFFFD8;
extern __sfr __no_init volatile union { unsigned short PR03; struct { union { unsigned char PR03L; __BITS8 PR03L_bit; }; union { unsigned char PR03H; __BITS8 PR03H_bit; }; }; } @ 0xFFFDA;
extern __sfr __no_init volatile union { unsigned short PR12; struct { union { unsigned char PR12L; __BITS8 PR12L_bit; }; union { unsigned char PR12H; __BITS8 PR12H_bit; }; }; } @ 0xFFFDC;
extern __sfr __no_init volatile union { unsigned short PR13; struct { union { unsigned char PR13L; __BITS8 PR13L_bit; }; union { unsigned char PR13H; __BITS8 PR13H_bit; }; }; } @ 0xFFFDE;
extern __sfr __no_init volatile union { unsigned short IF0; struct { union { unsigned char IF0L; __BITS8 IF0L_bit; }; union { unsigned char IF0H; __BITS8 IF0H_bit; }; }; } @ 0xFFFE0;
extern __sfr __no_init volatile union { unsigned short IF1; struct { union { unsigned char IF1L; __BITS8 IF1L_bit; }; union { unsigned char IF1H; __BITS8 IF1H_bit; }; }; } @ 0xFFFE2;
extern __sfr __no_init volatile union { unsigned short MK0; struct { union { unsigned char MK0L; __BITS8 MK0L_bit; }; union { unsigned char MK0H; __BITS8 MK0H_bit; }; }; } @ 0xFFFE4;
extern __sfr __no_init volatile union { unsigned short MK1; struct { union { unsigned char MK1L; __BITS8 MK1L_bit; }; union { unsigned char MK1H; __BITS8 MK1H_bit; }; }; } @ 0xFFFE6;
extern __sfr __no_init volatile union { unsigned short PR00; struct { union { unsigned char PR00L; __BITS8 PR00L_bit; }; union { unsigned char PR00H; __BITS8 PR00H_bit; }; }; } @ 0xFFFE8;
extern __sfr __no_init volatile union { unsigned short PR01; struct { union { unsigned char PR01L; __BITS8 PR01L_bit; }; union { unsigned char PR01H; __BITS8 PR01H_bit; }; }; } @ 0xFFFEA;
extern __sfr __no_init volatile union { unsigned short PR10; struct { union { unsigned char PR10L; __BITS8 PR10L_bit; }; union { unsigned char PR10H; __BITS8 PR10H_bit; }; }; } @ 0xFFFEC;
extern __sfr __no_init volatile union { unsigned short PR11; struct { union { unsigned char PR11L; __BITS8 PR11L_bit; }; union { unsigned char PR11H; __BITS8 PR11H_bit; }; }; } @ 0xFFFEE;
extern __sfr __no_bit_access __no_init volatile unsigned short MDAL @ 0xFFFF0;
extern __sfr __no_bit_access __no_init volatile unsigned short MULA @ 0xFFFF0;
extern __sfr __no_bit_access __no_init volatile unsigned short MDAH @ 0xFFFF2;
extern __sfr __no_bit_access __no_init volatile unsigned short MULB @ 0xFFFF2;
extern __sfr __no_bit_access __no_init volatile unsigned short MDBH @ 0xFFFF4;
extern __sfr __no_bit_access __no_init volatile const unsigned short MULOH @ 0xFFFF4;
extern __sfr __no_bit_access __no_init volatile unsigned short MDBL @ 0xFFFF6;
extern __sfr __no_bit_access __no_init volatile const unsigned short MULOL @ 0xFFFF6;
extern __sfr __no_init volatile union { unsigned char PMC; __BITS8 PMC_bit; } @ 0xFFFFE;

/*----------------------------------------------
 *       SFR bit declarations
 *--------------------------------------------*/

#define ADCE              ADM0_bit.no0
#define ADCS              ADM0_bit.no7

#define ADTMD             ADM1_bit.no7

#define HIOSTOP           CSC_bit.no0
#define XTSTOP            CSC_bit.no6
#define MSTOP             CSC_bit.no7

#define MCM0              CKC_bit.no4
#define MCS               CKC_bit.no5
#define CSS               CKC_bit.no6
#define CLS               CKC_bit.no7

#define PCLOE             CKS_bit.no7

#define LVIF              LVIM_bit.no0
#define LVIMD             LVIM_bit.no1
#define LVISEL            LVIM_bit.no2
#define LVION             LVIM_bit.no7

#define WUTMCE            WUTMCTL_bit.no7

#define DS0               DMC0_bit.no5
#define DRS0              DMC0_bit.no6
#define STG0              DMC0_bit.no7

#define DS1               DMC1_bit.no5
#define DRS1              DMC1_bit.no6
#define STG1              DMC1_bit.no7

#define DST0              DRC0_bit.no0
#define DEN0              DRC0_bit.no7

#define DST1              DRC1_bit.no0
#define DEN1              DRC1_bit.no7

#define FLMDPUP           BECTL_bit.no7

#define TMIF05            IF2L_bit.no0
#define TMIF06            IF2L_bit.no1
#define TMIF07            IF2L_bit.no2
#define KRIF              IF2L_bit.no3
#define PIF6              IF2L_bit.no3
#define PIF7              IF2L_bit.no4
#define C0ERRIF           IF2L_bit.no5
#define C0WUPIF           IF2L_bit.no6
#define C0RECIF           IF2L_bit.no7

#define C0TRXIF           IF2H_bit.no0
#define TMIF10            IF2H_bit.no1
#define TMIF11            IF2H_bit.no2
#define TMIF12            IF2H_bit.no3
#define TMIF13            IF2H_bit.no4
#define MDIF              IF2H_bit.no5
#define IICIF20           IF2H_bit.no6
#define STIF2             IF2H_bit.no6
#define SRIF2             IF2H_bit.no7

#define PIFR2             IF3L_bit.no0
#define TMIF14            IF3L_bit.no1
#define TMIF15            IF3L_bit.no2
#define TMIF16            IF3L_bit.no3
#define TMIF17            IF3L_bit.no4
#define TMIF20            IF3L_bit.no5
#define TMIF21            IF3L_bit.no6
#define TMIF22            IF3L_bit.no7

#define TMIF23            IF3H_bit.no0
#define DMAIF2            IF3H_bit.no3
#define DMAIF3            IF3H_bit.no4

#define TMMK05            MK2L_bit.no0
#define TMMK06            MK2L_bit.no1
#define TMMK07            MK2L_bit.no2
#define KRMK              MK2L_bit.no3
#define PMK6              MK2L_bit.no3
#define PMK7              MK2L_bit.no4
#define C0ERRMK           MK2L_bit.no5
#define C0WUPMK           MK2L_bit.no6
#define C0RECMK           MK2L_bit.no7

#define C0TRXMK           MK2H_bit.no0
#define TMMK10            MK2H_bit.no1
#define TMMK11            MK2H_bit.no2
#define TMMK12            MK2H_bit.no3
#define TMMK13            MK2H_bit.no4
#define MDMK              MK2H_bit.no5
#define IICMK20           MK2H_bit.no6
#define STMK2             MK2H_bit.no6
#define SRMK2             MK2H_bit.no7

#define PMKR2             MK3L_bit.no0
#define TMMK14            MK3L_bit.no1
#define TMMK15            MK3L_bit.no2
#define TMMK16            MK3L_bit.no3
#define TMMK17            MK3L_bit.no4
#define TMMK20            MK3L_bit.no5
#define TMMK21            MK3L_bit.no6
#define TMMK22            MK3L_bit.no7

#define TMMK23            MK3H_bit.no0
#define DMAMK2            MK3H_bit.no3
#define DMAMK3            MK3H_bit.no4

#define TMPR005           PR02L_bit.no0
#define TMPR006           PR02L_bit.no1
#define TMPR007           PR02L_bit.no2
#define KRPR0             PR02L_bit.no3
#define PPR06             PR02L_bit.no3
#define PPR07             PR02L_bit.no4
#define C0ERRPR0          PR02L_bit.no5
#define C0WUPPR0          PR02L_bit.no6
#define C0RECPR0          PR02L_bit.no7

#define C0TRXPR0          PR02H_bit.no0
#define TMPR010           PR02H_bit.no1
#define TMPR011           PR02H_bit.no2
#define TMPR012           PR02H_bit.no3
#define TMPR013           PR02H_bit.no4
#define MDPR0             PR02H_bit.no5
#define IICPR020          PR02H_bit.no6
#define STPR02            PR02H_bit.no6
#define SRPR02            PR02H_bit.no7

#define PPR0R2            PR03L_bit.no0
#define TMPR014           PR03L_bit.no1
#define TMPR015           PR03L_bit.no2
#define TMPR016           PR03L_bit.no3
#define TMPR017           PR03L_bit.no4
#define TMPR020           PR03L_bit.no5
#define TMPR021           PR03L_bit.no6
#define TMPR022           PR03L_bit.no7

#define TMPR023           PR03H_bit.no0
#define DMAPR02           PR03H_bit.no3
#define DMAPR03           PR03H_bit.no4

#define TMPR105           PR12L_bit.no0
#define TMPR106           PR12L_bit.no1
#define TMPR107           PR12L_bit.no2
#define KRPR1             PR12L_bit.no3
#define PPR16             PR12L_bit.no3
#define PPR17             PR12L_bit.no4
#define C0ERRPR1          PR12L_bit.no5
#define C0WUPPR1          PR12L_bit.no6
#define C0RECPR1          PR12L_bit.no7

#define C0TRXPR1          PR12H_bit.no0
#define TMPR110           PR12H_bit.no1
#define TMPR111           PR12H_bit.no2
#define TMPR112           PR12H_bit.no3
#define TMPR113           PR12H_bit.no4
#define MDPR1             PR12H_bit.no5
#define IICPR120          PR12H_bit.no6
#define STPR12            PR12H_bit.no6
#define SRPR12            PR12H_bit.no7

#define PPR1R2            PR13L_bit.no0
#define TMPR114           PR13L_bit.no1
#define TMPR115           PR13L_bit.no2
#define TMPR116           PR13L_bit.no3
#define TMPR117           PR13L_bit.no4
#define TMPR120           PR13L_bit.no5
#define TMPR121           PR13L_bit.no6
#define TMPR122           PR13L_bit.no7

#define TMPR123           PR13H_bit.no0
#define DMAPR12           PR13H_bit.no3
#define DMAPR13           PR13H_bit.no4

#define WDTIIF            IF0L_bit.no0
#define LVIIF             IF0L_bit.no1
#define PIF0              IF0L_bit.no2
#define PIF1              IF0L_bit.no3
#define PIF2              IF0L_bit.no4
#define PIF3              IF0L_bit.no5
#define PIF4              IF0L_bit.no6
#define PIF5              IF0L_bit.no7

#define CLMIF             IF0H_bit.no0
#define CSIIF00           IF0H_bit.no1
#define CSIIF01           IF0H_bit.no2
#define DMAIF0            IF0H_bit.no3
#define DMAIF1            IF0H_bit.no4
#define WUTMIF            IF0H_bit.no5
#define FLIF              IF0H_bit.no6
#define LTIF0             IF0H_bit.no7

#define LRIF0             IF1L_bit.no0
#define LSIF0             IF1L_bit.no1
#define PIFLR0            IF1L_bit.no2
#define PIF8              IF1L_bit.no3
#define TMIF00            IF1L_bit.no4
#define TMIF01            IF1L_bit.no5
#define TMIF02            IF1L_bit.no6
#define TMIF03            IF1L_bit.no7

#define ADIF              IF1H_bit.no0
#define LTIF1             IF1H_bit.no1
#define LRIF1             IF1H_bit.no2
#define LSIF1             IF1H_bit.no3
#define PIFLR1            IF1H_bit.no4
#define CSIIF10           IF1H_bit.no5
#define IICIF11           IF1H_bit.no6
#define TMIF04            IF1H_bit.no7

#define WDTIMK            MK0L_bit.no0
#define LVIMK             MK0L_bit.no1
#define PMK0              MK0L_bit.no2
#define PMK1              MK0L_bit.no3
#define PMK2              MK0L_bit.no4
#define PMK3              MK0L_bit.no5
#define PMK4              MK0L_bit.no6
#define PMK5              MK0L_bit.no7

#define CLMMK             MK0H_bit.no0
#define CSIMK00           MK0H_bit.no1
#define CSIMK01           MK0H_bit.no2
#define DMAMK0            MK0H_bit.no3
#define DMAMK1            MK0H_bit.no4
#define WUTMMK            MK0H_bit.no5
#define FLMK              MK0H_bit.no6
#define LTMK0             MK0H_bit.no7

#define LRMK0             MK1L_bit.no0
#define LSMK0             MK1L_bit.no1
#define PMKLR0            MK1L_bit.no2
#define PMK8              MK1L_bit.no3
#define TMMK00            MK1L_bit.no4
#define TMMK01            MK1L_bit.no5
#define TMMK02            MK1L_bit.no6
#define TMMK03            MK1L_bit.no7

#define ADMK              MK1H_bit.no0
#define LTMK1             MK1H_bit.no1
#define LRMK1             MK1H_bit.no2
#define LSMK1             MK1H_bit.no3
#define PMKLR1            MK1H_bit.no4
#define CSIMK10           MK1H_bit.no5
#define IICMK11           MK1H_bit.no6
#define TMMK04            MK1H_bit.no7

#define WDTIPR0           PR00L_bit.no0
#define LVIPR0            PR00L_bit.no1
#define PPR00             PR00L_bit.no2
#define PPR01             PR00L_bit.no3
#define PPR02             PR00L_bit.no4
#define PPR03             PR00L_bit.no5
#define PPR04             PR00L_bit.no6
#define PPR05             PR00L_bit.no7

#define CLMPR0            PR00H_bit.no0
#define CSIPR000          PR00H_bit.no1
#define CSIPR001          PR00H_bit.no2
#define DMAPR00           PR00H_bit.no3
#define DMAPR01           PR00H_bit.no4
#define WUTMPR0           PR00H_bit.no5
#define FLPR0             PR00H_bit.no6
#define LTPR00            PR00H_bit.no7

#define LRPR00            PR01L_bit.no0
#define LSPR00            PR01L_bit.no1
#define PPR0LR0           PR01L_bit.no2
#define PPR08             PR01L_bit.no3
#define TMPR000           PR01L_bit.no4
#define TMPR001           PR01L_bit.no5
#define TMPR002           PR01L_bit.no6
#define TMPR003           PR01L_bit.no7

#define ADPR0             PR01H_bit.no0
#define LTPR01            PR01H_bit.no1
#define LRPR01            PR01H_bit.no2
#define LSPR01            PR01H_bit.no3
#define PPR0LR1           PR01H_bit.no4
#define CSIPR010          PR01H_bit.no5
#define IICPR011          PR01H_bit.no6
#define TMPR004           PR01H_bit.no7

#define WDTIPR1           PR10L_bit.no0
#define LVIPR1            PR10L_bit.no1
#define PPR10             PR10L_bit.no2
#define PPR11             PR10L_bit.no3
#define PPR12             PR10L_bit.no4
#define PPR13             PR10L_bit.no5
#define PPR14             PR10L_bit.no6
#define PPR15             PR10L_bit.no7

#define CLMPR1            PR10H_bit.no0
#define CSIPR100          PR10H_bit.no1
#define CSIPR101          PR10H_bit.no2
#define DMAPR10           PR10H_bit.no3
#define DMAPR11           PR10H_bit.no4
#define WUTMPR1           PR10H_bit.no5
#define FLPR1             PR10H_bit.no6
#define LTPR10            PR10H_bit.no7

#define LRPR10            PR11L_bit.no0
#define LSPR10            PR11L_bit.no1
#define PPR1LR0           PR11L_bit.no2
#define PPR18             PR11L_bit.no3
#define TMPR100           PR11L_bit.no4
#define TMPR101           PR11L_bit.no5
#define TMPR102           PR11L_bit.no6
#define TMPR103           PR11L_bit.no7

#define ADPR1             PR11H_bit.no0
#define LTPR11            PR11H_bit.no1
#define LRPR11            PR11H_bit.no2
#define LSPR11            PR11H_bit.no3
#define PPR1LR1           PR11H_bit.no4
#define CSIPR110          PR11H_bit.no5
#define IICPR111          PR11H_bit.no6
#define TMPR104           PR11H_bit.no7

#define MAA               PMC_bit.no0

#pragma language=default

#endif /* __IAR_SYSTEMS_ICC__ */

#ifdef __IAR_SYSTEMS_ASM__

/*----------------------------------------------
 *       SFR declarations
 *--------------------------------------------*/

P0         DEFINE  0xFFF00
P1         DEFINE  0xFFF01
P3         DEFINE  0xFFF03
P4         DEFINE  0xFFF04
P5         DEFINE  0xFFF05
P6         DEFINE  0xFFF06
P7         DEFINE  0xFFF07
P8         DEFINE  0xFFF08
P9         DEFINE  0xFFF09
P12        DEFINE  0xFFF0C
P13        DEFINE  0xFFF0D
P14        DEFINE  0xFFF0E
SDR00      DEFINE  0xFFF10
SDR00L     DEFINE  0xFFF10
SDR01      DEFINE  0xFFF12
SDR01L     DEFINE  0xFFF12
SDR10      DEFINE  0xFFF14
SDR10L     DEFINE  0xFFF14
SDR11      DEFINE  0xFFF16
SDR11L     DEFINE  0xFFF16
TDR00      DEFINE  0xFFF18
TDR01      DEFINE  0xFFF1A
ADCR       DEFINE  0xFFF1E
ADCRH      DEFINE  0xFFF1F
PM0        DEFINE  0xFFF20
PM1        DEFINE  0xFFF21
PM3        DEFINE  0xFFF23
PM4        DEFINE  0xFFF24
PM5        DEFINE  0xFFF25
PM6        DEFINE  0xFFF26
PM7        DEFINE  0xFFF27
PM8        DEFINE  0xFFF28
PM9        DEFINE  0xFFF29
PM12       DEFINE  0xFFF2C
PM14       DEFINE  0xFFF2E
ADM0       DEFINE  0xFFF30
ADS        DEFINE  0xFFF31
ADSMP      DEFINE  0xFFF33
IPSEL0     DEFINE  0xFFF36
KRM        DEFINE  0xFFF37
EGP0       DEFINE  0xFFF38
EGN0       DEFINE  0xFFF39
EGP1       DEFINE  0xFFF3A
EGN1       DEFINE  0xFFF3B
STSEL      DEFINE  0xFFF3C
TIS0       DEFINE  0xFFF3E
TIS1       DEFINE  0xFFF3F
ADM1       DEFINE  0xFFF42
SDR20      DEFINE  0xFFF44
SDR20L     DEFINE  0xFFF44
SDR21      DEFINE  0xFFF46
SDR21L     DEFINE  0xFFF46
UF0TX      DEFINE  0xFFF48
UF0TXB     DEFINE  0xFFF48
UF0RX      DEFINE  0xFFF4A
UF0RXB     DEFINE  0xFFF4A
UF1TX      DEFINE  0xFFF4C
UF1TXB     DEFINE  0xFFF4C
UF1RX      DEFINE  0xFFF4E
UF1RXB     DEFINE  0xFFF4E
TOS0       DEFINE  0xFFF60
TOS1       DEFINE  0xFFF61
TDR02      DEFINE  0xFFF64
TDR03      DEFINE  0xFFF66
TDR04      DEFINE  0xFFF68
TDR05      DEFINE  0xFFF6A
TDR06      DEFINE  0xFFF6C
TDR07      DEFINE  0xFFF6E
TDR10      DEFINE  0xFFF70
TDR11      DEFINE  0xFFF72
TDR12      DEFINE  0xFFF74
TDR13      DEFINE  0xFFF76
TDR14      DEFINE  0xFFF78
TDR15      DEFINE  0xFFF7A
TDR16      DEFINE  0xFFF7C
TDR17      DEFINE  0xFFF7E
TDR20      DEFINE  0xFFF90
TDR21      DEFINE  0xFFF92
TDR22      DEFINE  0xFFF94
TDR23      DEFINE  0xFFF96
CMC        DEFINE  0xFFFA0
CSC        DEFINE  0xFFFA1
OSTC       DEFINE  0xFFFA2
OSTS       DEFINE  0xFFFA3
CKC        DEFINE  0xFFFA4
CKS        DEFINE  0xFFFA5
RESF       DEFINE  0xFFFA8
LVIM       DEFINE  0xFFFA9
LVIS       DEFINE  0xFFFAA
WDTE       DEFINE  0xFFFAB
WUTMCTL    DEFINE  0xFFFAC
WUTMCMP    DEFINE  0xFFFAE
DSA0       DEFINE  0xFFFB0
DSA1       DEFINE  0xFFFB1
DRA0       DEFINE  0xFFFB2
DRA0L      DEFINE  0xFFFB2
DRA0H      DEFINE  0xFFFB3
DRA1       DEFINE  0xFFFB4
DRA1L      DEFINE  0xFFFB4
DRA1H      DEFINE  0xFFFB5
DBC0       DEFINE  0xFFFB6
DBC0L      DEFINE  0xFFFB6
DBC0H      DEFINE  0xFFFB7
DBC1       DEFINE  0xFFFB8
DBC1L      DEFINE  0xFFFB8
DBC1H      DEFINE  0xFFFB9
DMC0       DEFINE  0xFFFBA
DMC1       DEFINE  0xFFFBB
DRC0       DEFINE  0xFFFBC
DRC1       DEFINE  0xFFFBD
BECTL      DEFINE  0xFFFBE
IF2        DEFINE  0xFFFD0
IF2L       DEFINE  0xFFFD0
IF2H       DEFINE  0xFFFD1
IF3        DEFINE  0xFFFD2
IF3L       DEFINE  0xFFFD2
IF3H       DEFINE  0xFFFD3
MK2        DEFINE  0xFFFD4
MK2L       DEFINE  0xFFFD4
MK2H       DEFINE  0xFFFD5
MK3        DEFINE  0xFFFD6
MK3L       DEFINE  0xFFFD6
MK3H       DEFINE  0xFFFD7
PR02       DEFINE  0xFFFD8
PR02L      DEFINE  0xFFFD8
PR02H      DEFINE  0xFFFD9
PR03       DEFINE  0xFFFDA
PR03L      DEFINE  0xFFFDA
PR03H      DEFINE  0xFFFDB
PR12       DEFINE  0xFFFDC
PR12L      DEFINE  0xFFFDC
PR12H      DEFINE  0xFFFDD
PR13       DEFINE  0xFFFDE
PR13L      DEFINE  0xFFFDE
PR13H      DEFINE  0xFFFDF
IF0        DEFINE  0xFFFE0
IF0L       DEFINE  0xFFFE0
IF0H       DEFINE  0xFFFE1
IF1        DEFINE  0xFFFE2
IF1L       DEFINE  0xFFFE2
IF1H       DEFINE  0xFFFE3
MK0        DEFINE  0xFFFE4
MK0L       DEFINE  0xFFFE4
MK0H       DEFINE  0xFFFE5
MK1        DEFINE  0xFFFE6
MK1L       DEFINE  0xFFFE6
MK1H       DEFINE  0xFFFE7
PR00       DEFINE  0xFFFE8
PR00L      DEFINE  0xFFFE8
PR00H      DEFINE  0xFFFE9
PR01       DEFINE  0xFFFEA
PR01L      DEFINE  0xFFFEA
PR01H      DEFINE  0xFFFEB
PR10       DEFINE  0xFFFEC
PR10L      DEFINE  0xFFFEC
PR10H      DEFINE  0xFFFED
PR11       DEFINE  0xFFFEE
PR11L      DEFINE  0xFFFEE
PR11H      DEFINE  0xFFFEF
MDAL       DEFINE  0xFFFF0
MULA       DEFINE  0xFFFF0
MDAH       DEFINE  0xFFFF2
MULB       DEFINE  0xFFFF2
MDBH       DEFINE  0xFFFF4
MULOH      DEFINE  0xFFFF4
MDBL       DEFINE  0xFFFF6
MULOL      DEFINE  0xFFFF6
PMC        DEFINE  0xFFFFE

#endif /* __IAR_SYSTEMS_ASM__ */

/*----------------------------------------------
 *       Interrupt vector addresses
 *--------------------------------------------*/

#define RST_vect                 (0x00)
#define INTWDTI_vect             (0x04)
#define INTLVI_vect              (0x06)
#define INTP0_vect               (0x08)
#define INTP1_vect               (0x0A)
#define INTP2_vect               (0x0C)
#define INTP3_vect               (0x0E)
#define INTP4_vect               (0x10)
#define INTP5_vect               (0x12)
#define INTCLM_vect              (0x14)
#define INTCSI00_vect            (0x16)
#define INTCSI01_vect            (0x18)
#define INTDMA0_vect             (0x1A)
#define INTDMA1_vect             (0x1C)
#define INTWUTM_vect             (0x1E)
#define INTFL_vect               (0x20)
#define INTLT0_vect              (0x22)
#define INTLR0_vect              (0x24)
#define INTLS0_vect              (0x26)
#define INTPLR0_vect             (0x28)
#define INTP8_vect               (0x2A)
#define INTTM00_vect             (0x2C)
#define INTTM01_vect             (0x2E)
#define INTTM02_vect             (0x30)
#define INTTM03_vect             (0x32)
#define INTAD_vect               (0x34)
#define INTLT1_vect              (0x36)
#define INTLR1_vect              (0x38)
#define INTLS1_vect              (0x3A)
#define INTPLR1_vect             (0x3C)
#define INTCSI10_vect            (0x3E)
#define INTIIC11_vect            (0x40)
#define INTTM04_vect             (0x42)
#define INTTM05_vect             (0x44)
#define INTTM06_vect             (0x46)
#define INTTM07_vect             (0x48)
#define INTKR_vect               (0x4A)
#define INTP6_vect               (0x4A)
#define INTP7_vect               (0x4C)
#define INTC0ERR_vect            (0x4E)
#define INTC0WUP_vect            (0x50)
#define INTC0REC_vect            (0x52)
#define INTC0TRX_vect            (0x54)
#define INTTM10_vect             (0x56)
#define INTTM11_vect             (0x58)
#define INTTM12_vect             (0x5A)
#define INTTM13_vect             (0x5C)
#define INTMD_vect               (0x5E)
#define INTIIC20_vect            (0x60)
#define INTST2_vect              (0x60)
#define INTSR2_vect              (0x62)
#define INTPR2_vect              (0x64)
#define INTTM14_vect             (0x66)
#define INTTM15_vect             (0x68)
#define INTTM16_vect             (0x6A)
#define INTTM17_vect             (0x6C)
#define INTTM20_vect             (0x6E)
#define INTTM21_vect             (0x70)
#define INTTM22_vect             (0x72)
#define INTTM23_vect             (0x74)
#define INTDMA2_vect             (0x7A)
#define INTDMA3_vect             (0x7C)
#define BRK_I_vect               (0x7E)

/*----------------------------------------------
 *       Callt vector addresses
 *--------------------------------------------*/

#define CALLT_80_vect            (0x80)
#define CALLT_82_vect            (0x82)
#define CALLT_84_vect            (0x84)
#define CALLT_86_vect            (0x86)
#define CALLT_88_vect            (0x88)
#define CALLT_8A_vect            (0x8A)
#define CALLT_8C_vect            (0x8C)
#define CALLT_8E_vect            (0x8E)
#define CALLT_90_vect            (0x90)
#define CALLT_92_vect            (0x92)
#define CALLT_94_vect            (0x94)
#define CALLT_96_vect            (0x96)
#define CALLT_98_vect            (0x98)
#define CALLT_9A_vect            (0x9A)
#define CALLT_9C_vect            (0x9C)
#define CALLT_9E_vect            (0x9E)
#define CALLT_A0_vect            (0xA0)
#define CALLT_A2_vect            (0xA2)
#define CALLT_A4_vect            (0xA4)
#define CALLT_A6_vect            (0xA6)
#define CALLT_A8_vect            (0xA8)
#define CALLT_AA_vect            (0xAA)
#define CALLT_AC_vect            (0xAC)
#define CALLT_AE_vect            (0xAE)
#define CALLT_B0_vect            (0xB0)
#define CALLT_B2_vect            (0xB2)
#define CALLT_B4_vect            (0xB4)
#define CALLT_B6_vect            (0xB6)
#define CALLT_B8_vect            (0xB8)
#define CALLT_BA_vect            (0xBA)
#define CALLT_BC_vect            (0xBC)
#define CALLT_BE_vect            (0xBE)

#endif /* __IO78F1840_80_H__ */
