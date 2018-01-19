/*-------------------------------------------------------------------------
 *      Declarations of extended SFR registers for 78K0R microcontroller uPD78F1840_80.
 *
 *      This file can be used by both the 78K0R,
 *      Assembler, A78K0R, and the C/C++ compiler, ICC78K0R.
 *
 *      This header file is generated from the device file:
 *          DF184080.78K
 *          Copyright (C) NEC Corporation 2009
 *          Format version V3.00, File version V1.01
 *-------------------------------------------------------------------------*/

#ifndef __IO78F1840_80_EXT_H__
#define __IO78F1840_80_EXT_H__

#if !defined(__A78K__) && !defined(__ICC78K__)
  #error "IO78F1840_80_EXT.H file for use with 78K Series Assembler or Compiler only"
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
 *       Extended SFR declarations
 *--------------------------------------------*/

extern __near __no_bit_access __no_init volatile unsigned char ADPC @ 0xF0017;
extern __near __no_init volatile union { unsigned char PU0; __BITS8 PU0_bit; } @ 0xF0030;
extern __near __no_init volatile union { unsigned char PU1; __BITS8 PU1_bit; } @ 0xF0031;
extern __near __no_init volatile union { unsigned char PU3; __BITS8 PU3_bit; } @ 0xF0033;
extern __near __no_init volatile union { unsigned char PU4; __BITS8 PU4_bit; } @ 0xF0034;
extern __near __no_init volatile union { unsigned char PU5; __BITS8 PU5_bit; } @ 0xF0035;
extern __near __no_init volatile union { unsigned char PU6; __BITS8 PU6_bit; } @ 0xF0036;
extern __near __no_init volatile union { unsigned char PU7; __BITS8 PU7_bit; } @ 0xF0037;
extern __near __no_init volatile union { unsigned char PU12; __BITS8 PU12_bit; } @ 0xF003C;
extern __near __no_init volatile union { unsigned char PU14; __BITS8 PU14_bit; } @ 0xF003E;
extern __near __no_init volatile union { unsigned char PIM6; __BITS8 PIM6_bit; } @ 0xF0046;
extern __near __no_init volatile union { unsigned char PIM7; __BITS8 PIM7_bit; } @ 0xF0047;
extern __near __no_init volatile union { unsigned char POM4; __BITS8 POM4_bit; } @ 0xF0054;
extern __near __no_init volatile union { unsigned char POM7; __BITS8 POM7_bit; } @ 0xF0057;
extern __near __no_init volatile union { unsigned char NFEN0; __BITS8 NFEN0_bit; } @ 0xF0060;
extern __near __no_init volatile union { unsigned char NFEN1; __BITS8 NFEN1_bit; } @ 0xF0061;
extern __near __no_init volatile union { unsigned char NFEN2; __BITS8 NFEN2_bit; } @ 0xF0062;
extern __near __no_init volatile union { unsigned char NFEN3; __BITS8 NFEN3_bit; } @ 0xF0063;
extern __near __no_init volatile union { unsigned char LVIOUT; __BITS8 LVIOUT_bit; } @ 0xF0067;
extern __near __no_init volatile union { unsigned char PSRSEL; __BITS8 PSRSEL_bit; } @ 0xF006F;
extern __near __no_init volatile union { unsigned char GUARD; __BITS8 GUARD_bit; } @ 0xF0070;
extern __near __no_bit_access __no_init volatile unsigned char WDTSELF @ 0xF0071;
extern __near __no_init volatile union { unsigned char IAWCTL; __BITS8 IAWCTL_bit; } @ 0xF0074;
extern __near __no_bit_access __no_init volatile unsigned char IAWRAM @ 0xF0075;
extern __near __no_bit_access __no_init volatile unsigned char IAWFLASH @ 0xF0076;
extern __near __no_bit_access __no_init volatile unsigned char DSA2 @ 0xF0080;
extern __near __no_bit_access __no_init volatile unsigned char DSA3 @ 0xF0081;
extern __near __no_bit_access __no_init volatile union { unsigned short DRA2; struct { unsigned char DRA2L; unsigned char DRA2H; }; } @ 0xF0082;
extern __near __no_bit_access __no_init volatile union { unsigned short DRA3; struct { unsigned char DRA3L; unsigned char DRA3H; }; } @ 0xF0084;
extern __near __no_bit_access __no_init volatile union { unsigned short DBC2; struct { unsigned char DBC2L; unsigned char DBC2H; }; } @ 0xF0086;
extern __near __no_bit_access __no_init volatile union { unsigned short DBC3; struct { unsigned char DBC3L; unsigned char DBC3H; }; } @ 0xF0088;
extern __near __no_init volatile union { unsigned char DMC2; __BITS8 DMC2_bit; } @ 0xF008A;
extern __near __no_init volatile union { unsigned char DMC3; __BITS8 DMC3_bit; } @ 0xF008B;
extern __near __no_init volatile union { unsigned char DRC2; __BITS8 DRC2_bit; } @ 0xF008C;
extern __near __no_init volatile union { unsigned char DRC3; __BITS8 DRC3_bit; } @ 0xF008D;
extern __near __no_init volatile union { unsigned char DMCALL; __BITS8 DMCALL_bit; } @ 0xF008F;
extern __near __no_bit_access __no_init volatile const unsigned short MDCL @ 0xF00E0;
extern __near __no_bit_access __no_init volatile const unsigned short MDCH @ 0xF00E2;
extern __near __no_init volatile union { unsigned char MDUC; __BITS8 MDUC_bit; } @ 0xF00E8;
extern __near __no_init volatile union { unsigned char PER0; __BITS8 PER0_bit; } @ 0xF00F0;
extern __near __no_init volatile union { unsigned char PER1; __BITS8 PER1_bit; } @ 0xF00F1;
extern __near __no_init volatile union { unsigned char PCKSEL; __BITS8 PCKSEL_bit; } @ 0xF00F2;
extern __near __no_init volatile union { unsigned char OSMC; __BITS8 OSMC_bit; } @ 0xF00F3;
extern __near __no_init volatile const union { unsigned char PLLSTS; __BITS8 PLLSTS_bit; } @ 0xF00F6;
extern __near __no_init volatile union { unsigned char PLLCTL; __BITS8 PLLCTL_bit; } @ 0xF00F7;
extern __near __no_bit_access __no_init volatile unsigned short HIOTRM @ 0xF00F8;
extern __near __no_bit_access __no_init volatile unsigned char LIOTRM @ 0xF00FA;
extern __near __no_init volatile union { unsigned char POCRES; __BITS8 POCRES_bit; } @ 0xF00FB;
extern __near __no_init volatile union { unsigned char STPSTC; __BITS8 STPSTC_bit; } @ 0xF00FC;
extern __near __no_bit_access __no_init volatile const unsigned char BCDADJ @ 0xF00FE;
extern __near __no_init volatile const union { unsigned short SSR00; struct { union { unsigned char SSR00L; __BITS8 SSR00L_bit; }; }; } @ 0xF0100;
extern __near __no_init volatile const union { unsigned short SSR01; struct { union { unsigned char SSR01L; __BITS8 SSR01L_bit; }; }; } @ 0xF0102;
extern __near __no_init volatile union { unsigned short SIR00; struct { union { unsigned char SIR00L; __BITS8 SIR00L_bit; }; }; } @ 0xF0104;
extern __near __no_init volatile union { unsigned short SIR01; struct { union { unsigned char SIR01L; __BITS8 SIR01L_bit; }; }; } @ 0xF0106;
extern __near __no_bit_access __no_init volatile unsigned short SMR00 @ 0xF0108;
extern __near __no_bit_access __no_init volatile unsigned short SMR01 @ 0xF010A;
extern __near __no_bit_access __no_init volatile unsigned short SCR00 @ 0xF010C;
extern __near __no_bit_access __no_init volatile unsigned short SCR01 @ 0xF010E;
extern __near __no_init volatile const union { unsigned short SE0; struct { union { unsigned char SE0L; __BITS8 SE0L_bit; }; }; } @ 0xF0110;
extern __near __no_init volatile union { unsigned short SS0; struct { union { unsigned char SS0L; __BITS8 SS0L_bit; }; }; } @ 0xF0112;
extern __near __no_init volatile union { unsigned short ST0; struct { union { unsigned char ST0L; __BITS8 ST0L_bit; }; }; } @ 0xF0114;
extern __near __no_init volatile union { unsigned short SPS0; struct { union { unsigned char SPS0L; __BITS8 SPS0L_bit; }; }; } @ 0xF0116;
extern __near __no_bit_access __no_init volatile unsigned short SO0 @ 0xF0118;
extern __near __no_init volatile union { unsigned short SOE0; struct { union { unsigned char SOE0L; __BITS8 SOE0L_bit; }; }; } @ 0xF011A;
extern __near __no_init volatile union { unsigned short SOL0; struct { union { unsigned char SOL0L; __BITS8 SOL0L_bit; }; }; } @ 0xF0120;
extern __near __no_init volatile union { unsigned short SSE0; struct { union { unsigned char SSE0L; __BITS8 SSE0L_bit; }; }; } @ 0xF0122;
extern __near __no_init volatile const union { unsigned short SSR10; struct { union { unsigned char SSR10L; __BITS8 SSR10L_bit; }; }; } @ 0xF0130;
extern __near __no_init volatile const union { unsigned short SSR11; struct { union { unsigned char SSR11L; __BITS8 SSR11L_bit; }; }; } @ 0xF0132;
extern __near __no_init volatile union { unsigned short SIR10; struct { union { unsigned char SIR10L; __BITS8 SIR10L_bit; }; }; } @ 0xF0134;
extern __near __no_init volatile union { unsigned short SIR11; struct { union { unsigned char SIR11L; __BITS8 SIR11L_bit; }; }; } @ 0xF0136;
extern __near __no_bit_access __no_init volatile unsigned short SMR10 @ 0xF0138;
extern __near __no_bit_access __no_init volatile unsigned short SMR11 @ 0xF013A;
extern __near __no_bit_access __no_init volatile unsigned short SCR10 @ 0xF013C;
extern __near __no_bit_access __no_init volatile unsigned short SCR11 @ 0xF013E;
extern __near __no_init volatile const union { unsigned short SE1; struct { union { unsigned char SE1L; __BITS8 SE1L_bit; }; }; } @ 0xF0140;
extern __near __no_init volatile union { unsigned short SS1; struct { union { unsigned char SS1L; __BITS8 SS1L_bit; }; }; } @ 0xF0142;
extern __near __no_init volatile union { unsigned short ST1; struct { union { unsigned char ST1L; __BITS8 ST1L_bit; }; }; } @ 0xF0144;
extern __near __no_init volatile union { unsigned short SPS1; struct { union { unsigned char SPS1L; __BITS8 SPS1L_bit; }; }; } @ 0xF0146;
extern __near __no_bit_access __no_init volatile unsigned short SO1 @ 0xF0148;
extern __near __no_init volatile union { unsigned short SOE1; struct { union { unsigned char SOE1L; __BITS8 SOE1L_bit; }; }; } @ 0xF014A;
extern __near __no_init volatile union { unsigned short SOL1; struct { union { unsigned char SOL1L; __BITS8 SOL1L_bit; }; }; } @ 0xF0150;
extern __near __no_init volatile union { unsigned short SOL2; struct { union { unsigned char SOL2L; __BITS8 SOL2L_bit; }; }; } @ 0xF0158;
extern __near __no_init volatile const union { unsigned short SSR20; struct { union { unsigned char SSR20L; __BITS8 SSR20L_bit; }; }; } @ 0xF0160;
extern __near __no_init volatile const union { unsigned short SSR21; struct { union { unsigned char SSR21L; __BITS8 SSR21L_bit; }; }; } @ 0xF0162;
extern __near __no_init volatile union { unsigned short SIR20; struct { union { unsigned char SIR20L; __BITS8 SIR20L_bit; }; }; } @ 0xF0164;
extern __near __no_init volatile union { unsigned short SIR21; struct { union { unsigned char SIR21L; __BITS8 SIR21L_bit; }; }; } @ 0xF0166;
extern __near __no_bit_access __no_init volatile unsigned short SMR20 @ 0xF0168;
extern __near __no_bit_access __no_init volatile unsigned short SMR21 @ 0xF016A;
extern __near __no_bit_access __no_init volatile unsigned short SCR20 @ 0xF016C;
extern __near __no_bit_access __no_init volatile unsigned short SCR21 @ 0xF016E;
extern __near __no_init volatile const union { unsigned short SE2; struct { union { unsigned char SE2L; __BITS8 SE2L_bit; }; }; } @ 0xF0170;
extern __near __no_init volatile union { unsigned short SS2; struct { union { unsigned char SS2L; __BITS8 SS2L_bit; }; }; } @ 0xF0172;
extern __near __no_init volatile union { unsigned short ST2; struct { union { unsigned char ST2L; __BITS8 ST2L_bit; }; }; } @ 0xF0174;
extern __near __no_init volatile union { unsigned short SPS2; struct { union { unsigned char SPS2L; __BITS8 SPS2L_bit; }; }; } @ 0xF0176;
extern __near __no_bit_access __no_init volatile unsigned short SO2 @ 0xF0178;
extern __near __no_init volatile union { unsigned short SOE2; struct { union { unsigned char SOE2L; __BITS8 SOE2L_bit; }; }; } @ 0xF017A;
extern __near __no_bit_access __no_init volatile const unsigned short TCR00 @ 0xF0180;
extern __near __no_bit_access __no_init volatile const unsigned short TCR01 @ 0xF0182;
extern __near __no_bit_access __no_init volatile const unsigned short TCR02 @ 0xF0184;
extern __near __no_bit_access __no_init volatile const unsigned short TCR03 @ 0xF0186;
extern __near __no_bit_access __no_init volatile const unsigned short TCR04 @ 0xF0188;
extern __near __no_bit_access __no_init volatile const unsigned short TCR05 @ 0xF018A;
extern __near __no_bit_access __no_init volatile const unsigned short TCR06 @ 0xF018C;
extern __near __no_bit_access __no_init volatile const unsigned short TCR07 @ 0xF018E;
extern __near __no_bit_access __no_init volatile unsigned short TMR00 @ 0xF0190;
extern __near __no_bit_access __no_init volatile unsigned short TMR01 @ 0xF0192;
extern __near __no_bit_access __no_init volatile unsigned short TMR02 @ 0xF0194;
extern __near __no_bit_access __no_init volatile unsigned short TMR03 @ 0xF0196;
extern __near __no_bit_access __no_init volatile unsigned short TMR04 @ 0xF0198;
extern __near __no_bit_access __no_init volatile unsigned short TMR05 @ 0xF019A;
extern __near __no_bit_access __no_init volatile unsigned short TMR06 @ 0xF019C;
extern __near __no_bit_access __no_init volatile unsigned short TMR07 @ 0xF019E;
extern __near __no_init volatile const union { unsigned short TSR00; struct { union { unsigned char TSR00L; __BITS8 TSR00L_bit; }; }; } @ 0xF01A0;
extern __near __no_init volatile const union { unsigned short TSR01; struct { union { unsigned char TSR01L; __BITS8 TSR01L_bit; }; }; } @ 0xF01A2;
extern __near __no_init volatile const union { unsigned short TSR02; struct { union { unsigned char TSR02L; __BITS8 TSR02L_bit; }; }; } @ 0xF01A4;
extern __near __no_init volatile const union { unsigned short TSR03; struct { union { unsigned char TSR03L; __BITS8 TSR03L_bit; }; }; } @ 0xF01A6;
extern __near __no_init volatile const union { unsigned short TSR04; struct { union { unsigned char TSR04L; __BITS8 TSR04L_bit; }; }; } @ 0xF01A8;
extern __near __no_init volatile const union { unsigned short TSR05; struct { union { unsigned char TSR05L; __BITS8 TSR05L_bit; }; }; } @ 0xF01AA;
extern __near __no_init volatile const union { unsigned short TSR06; struct { union { unsigned char TSR06L; __BITS8 TSR06L_bit; }; }; } @ 0xF01AC;
extern __near __no_init volatile const union { unsigned short TSR07; struct { union { unsigned char TSR07L; __BITS8 TSR07L_bit; }; }; } @ 0xF01AE;
extern __near __no_init volatile const union { unsigned short TE0; struct { union { unsigned char TE0L; __BITS8 TE0L_bit; }; }; } @ 0xF01B0;
extern __near __no_init volatile union { unsigned short TS0; struct { union { unsigned char TS0L; __BITS8 TS0L_bit; }; }; } @ 0xF01B2;
extern __near __no_init volatile union { unsigned short TT0; struct { union { unsigned char TT0L; __BITS8 TT0L_bit; }; }; } @ 0xF01B4;
extern __near __no_bit_access __no_init volatile unsigned short TPS0 @ 0xF01B6;
extern __near __no_init volatile union { unsigned short TO0; struct { union { unsigned char TO0L; __BITS8 TO0L_bit; }; }; } @ 0xF01B8;
extern __near __no_init volatile union { unsigned short TOE0; struct { union { unsigned char TOE0L; __BITS8 TOE0L_bit; }; }; } @ 0xF01BA;
extern __near __no_init volatile union { unsigned short TOL0; struct { union { unsigned char TOL0L; __BITS8 TOL0L_bit; }; }; } @ 0xF01BC;
extern __near __no_init volatile union { unsigned short TOM0; struct { union { unsigned char TOM0L; __BITS8 TOM0L_bit; }; }; } @ 0xF01BE;
extern __near __no_bit_access __no_init volatile const unsigned short TCR10 @ 0xF01C0;
extern __near __no_bit_access __no_init volatile const unsigned short TCR11 @ 0xF01C2;
extern __near __no_bit_access __no_init volatile const unsigned short TCR12 @ 0xF01C4;
extern __near __no_bit_access __no_init volatile const unsigned short TCR13 @ 0xF01C6;
extern __near __no_bit_access __no_init volatile const unsigned short TCR14 @ 0xF01C8;
extern __near __no_bit_access __no_init volatile const unsigned short TCR15 @ 0xF01CA;
extern __near __no_bit_access __no_init volatile const unsigned short TCR16 @ 0xF01CC;
extern __near __no_bit_access __no_init volatile const unsigned short TCR17 @ 0xF01CE;
extern __near __no_bit_access __no_init volatile unsigned short TMR10 @ 0xF01D0;
extern __near __no_bit_access __no_init volatile unsigned short TMR11 @ 0xF01D2;
extern __near __no_bit_access __no_init volatile unsigned short TMR12 @ 0xF01D4;
extern __near __no_bit_access __no_init volatile unsigned short TMR13 @ 0xF01D6;
extern __near __no_bit_access __no_init volatile unsigned short TMR14 @ 0xF01D8;
extern __near __no_bit_access __no_init volatile unsigned short TMR15 @ 0xF01DA;
extern __near __no_bit_access __no_init volatile unsigned short TMR16 @ 0xF01DC;
extern __near __no_bit_access __no_init volatile unsigned short TMR17 @ 0xF01DE;
extern __near __no_init volatile const union { unsigned short TSR10; struct { union { unsigned char TSR10L; __BITS8 TSR10L_bit; }; }; } @ 0xF01E0;
extern __near __no_init volatile const union { unsigned short TSR11; struct { union { unsigned char TSR11L; __BITS8 TSR11L_bit; }; }; } @ 0xF01E2;
extern __near __no_init volatile const union { unsigned short TSR12; struct { union { unsigned char TSR12L; __BITS8 TSR12L_bit; }; }; } @ 0xF01E4;
extern __near __no_init volatile const union { unsigned short TSR13; struct { union { unsigned char TSR13L; __BITS8 TSR13L_bit; }; }; } @ 0xF01E6;
extern __near __no_init volatile const union { unsigned short TSR14; struct { union { unsigned char TSR14L; __BITS8 TSR14L_bit; }; }; } @ 0xF01E8;
extern __near __no_init volatile const union { unsigned short TSR15; struct { union { unsigned char TSR15L; __BITS8 TSR15L_bit; }; }; } @ 0xF01EA;
extern __near __no_init volatile const union { unsigned short TSR16; struct { union { unsigned char TSR16L; __BITS8 TSR16L_bit; }; }; } @ 0xF01EC;
extern __near __no_init volatile const union { unsigned short TSR17; struct { union { unsigned char TSR17L; __BITS8 TSR17L_bit; }; }; } @ 0xF01EE;
extern __near __no_init volatile const union { unsigned short TE1; struct { union { unsigned char TE1L; __BITS8 TE1L_bit; }; }; } @ 0xF01F0;
extern __near __no_init volatile union { unsigned short TS1; struct { union { unsigned char TS1L; __BITS8 TS1L_bit; }; }; } @ 0xF01F2;
extern __near __no_init volatile union { unsigned short TT1; struct { union { unsigned char TT1L; __BITS8 TT1L_bit; }; }; } @ 0xF01F4;
extern __near __no_bit_access __no_init volatile unsigned short TPS1 @ 0xF01F6;
extern __near __no_init volatile union { unsigned short TO1; struct { union { unsigned char TO1L; __BITS8 TO1L_bit; }; }; } @ 0xF01F8;
extern __near __no_init volatile union { unsigned short TOE1; struct { union { unsigned char TOE1L; __BITS8 TOE1L_bit; }; }; } @ 0xF01FA;
extern __near __no_init volatile union { unsigned short TOL1; struct { union { unsigned char TOL1L; __BITS8 TOL1L_bit; }; }; } @ 0xF01FC;
extern __near __no_init volatile union { unsigned short TOM1; struct { union { unsigned char TOM1L; __BITS8 TOM1L_bit; }; }; } @ 0xF01FE;
extern __near __no_bit_access __no_init volatile const unsigned short TCR20 @ 0xF0200;
extern __near __no_bit_access __no_init volatile const unsigned short TCR21 @ 0xF0202;
extern __near __no_bit_access __no_init volatile const unsigned short TCR22 @ 0xF0204;
extern __near __no_bit_access __no_init volatile const unsigned short TCR23 @ 0xF0206;
extern __near __no_bit_access __no_init volatile unsigned short TMR20 @ 0xF0210;
extern __near __no_bit_access __no_init volatile unsigned short TMR21 @ 0xF0212;
extern __near __no_bit_access __no_init volatile unsigned short TMR22 @ 0xF0214;
extern __near __no_bit_access __no_init volatile unsigned short TMR23 @ 0xF0216;
extern __near __no_init volatile const union { unsigned short TSR20; struct { union { unsigned char TSR20L; __BITS8 TSR20L_bit; }; }; } @ 0xF0220;
extern __near __no_init volatile const union { unsigned short TSR21; struct { union { unsigned char TSR21L; __BITS8 TSR21L_bit; }; }; } @ 0xF0222;
extern __near __no_init volatile const union { unsigned short TSR22; struct { union { unsigned char TSR22L; __BITS8 TSR22L_bit; }; }; } @ 0xF0224;
extern __near __no_init volatile const union { unsigned short TSR23; struct { union { unsigned char TSR23L; __BITS8 TSR23L_bit; }; }; } @ 0xF0226;
extern __near __no_init volatile const union { unsigned short TE2; struct { union { unsigned char TE2L; __BITS8 TE2L_bit; }; }; } @ 0xF0230;
extern __near __no_init volatile union { unsigned short TS2; struct { union { unsigned char TS2L; __BITS8 TS2L_bit; }; }; } @ 0xF0232;
extern __near __no_init volatile union { unsigned short TT2; struct { union { unsigned char TT2L; __BITS8 TT2L_bit; }; }; } @ 0xF0234;
extern __near __no_bit_access __no_init volatile unsigned short TPS2 @ 0xF0236;
extern __near __no_init volatile union { unsigned short TO2; struct { union { unsigned char TO2L; __BITS8 TO2L_bit; }; }; } @ 0xF0238;
extern __near __no_init volatile union { unsigned short TOE2; struct { union { unsigned char TOE2L; __BITS8 TOE2L_bit; }; }; } @ 0xF023A;
extern __near __no_init volatile union { unsigned short TOL2; struct { union { unsigned char TOL2L; __BITS8 TOL2L_bit; }; }; } @ 0xF023C;
extern __near __no_init volatile union { unsigned short TOM2; struct { union { unsigned char TOM2L; __BITS8 TOM2L_bit; }; }; } @ 0xF023E;
extern __near __no_init volatile union { unsigned char UF0CTL0; __BITS8 UF0CTL0_bit; } @ 0xF0240;
extern __near __no_init volatile union { unsigned char UF0OPT0; __BITS8 UF0OPT0_bit; } @ 0xF0241;
extern __near __no_bit_access __no_init volatile unsigned short UF0CTL1 @ 0xF0242;
extern __near __no_init volatile union { unsigned char UF0OPT1; __BITS8 UF0OPT1_bit; } @ 0xF0244;
extern __near __no_init volatile union { unsigned char UF0OPT2; __BITS8 UF0OPT2_bit; } @ 0xF0245;
extern __near __no_bit_access __no_init volatile const unsigned short UF0STR @ 0xF0246;
extern __near __no_bit_access __no_init volatile unsigned short UF0STC @ 0xF0248;
extern __near __no_init volatile union { unsigned short UF0WTX; struct { union { unsigned char UF0WTXB; __BITS8 UF0WTXB_bit; }; }; } @ 0xF024A;
extern __near __no_bit_access __no_init volatile unsigned char UF0ID @ 0xF024E;
extern __near __no_bit_access __no_init volatile unsigned char UF0BUF0 @ 0xF024F;
extern __near __no_bit_access __no_init volatile unsigned char UF0BUF1 @ 0xF0250;
extern __near __no_bit_access __no_init volatile unsigned char UF0BUF2 @ 0xF0251;
extern __near __no_bit_access __no_init volatile unsigned char UF0BUF3 @ 0xF0252;
extern __near __no_bit_access __no_init volatile unsigned char UF0BUF4 @ 0xF0253;
extern __near __no_bit_access __no_init volatile unsigned char UF0BUF5 @ 0xF0254;
extern __near __no_bit_access __no_init volatile unsigned char UF0BUF6 @ 0xF0255;
extern __near __no_bit_access __no_init volatile unsigned char UF0BUF7 @ 0xF0256;
extern __near __no_bit_access __no_init volatile unsigned char UF0BUF8 @ 0xF0257;
extern __near __no_bit_access __no_init volatile unsigned short UF0BUCTL @ 0xF0258;
extern __near __no_init volatile union { unsigned char UF1CTL0; __BITS8 UF1CTL0_bit; } @ 0xF0260;
extern __near __no_init volatile union { unsigned char UF1OPT0; __BITS8 UF1OPT0_bit; } @ 0xF0261;
extern __near __no_bit_access __no_init volatile unsigned short UF1CTL1 @ 0xF0262;
extern __near __no_init volatile union { unsigned char UF1OPT1; __BITS8 UF1OPT1_bit; } @ 0xF0264;
extern __near __no_init volatile union { unsigned char UF1OPT2; __BITS8 UF1OPT2_bit; } @ 0xF0265;
extern __near __no_bit_access __no_init volatile const unsigned short UF1STR @ 0xF0266;
extern __near __no_bit_access __no_init volatile unsigned short UF1STC @ 0xF0268;
extern __near __no_init volatile union { unsigned short UF1WTX; struct { union { unsigned char UF1WTXB; __BITS8 UF1WTXB_bit; }; }; } @ 0xF026A;
extern __near __no_bit_access __no_init volatile unsigned char UF1ID @ 0xF026E;
extern __near __no_bit_access __no_init volatile unsigned char UF1BUF0 @ 0xF026F;
extern __near __no_bit_access __no_init volatile unsigned char UF1BUF1 @ 0xF0270;
extern __near __no_bit_access __no_init volatile unsigned char UF1BUF2 @ 0xF0271;
extern __near __no_bit_access __no_init volatile unsigned char UF1BUF3 @ 0xF0272;
extern __near __no_bit_access __no_init volatile unsigned char UF1BUF4 @ 0xF0273;
extern __near __no_bit_access __no_init volatile unsigned char UF1BUF5 @ 0xF0274;
extern __near __no_bit_access __no_init volatile unsigned char UF1BUF6 @ 0xF0275;
extern __near __no_bit_access __no_init volatile unsigned char UF1BUF7 @ 0xF0276;
extern __near __no_bit_access __no_init volatile unsigned char UF1BUF8 @ 0xF0277;
extern __near __no_bit_access __no_init volatile unsigned short UF1BUCTL @ 0xF0278;
extern __near __no_bit_access __no_init volatile union { unsigned short ADCR0; struct { unsigned char :8; const unsigned char ADCR0H; }; } @ 0xF0280;
extern __near __no_bit_access __no_init volatile union { unsigned short ADCR1; struct { unsigned char :8; const unsigned char ADCR1H; }; } @ 0xF0282;
extern __near __no_bit_access __no_init volatile union { unsigned short ADCR2; struct { unsigned char :8; const unsigned char ADCR2H; }; } @ 0xF0284;
extern __near __no_bit_access __no_init volatile union { unsigned short ADCR3; struct { unsigned char :8; const unsigned char ADCR3H; }; } @ 0xF0286;
extern __near __no_bit_access __no_init volatile union { unsigned short ADCR4; struct { unsigned char :8; const unsigned char ADCR4H; }; } @ 0xF0288;
extern __near __no_bit_access __no_init volatile union { unsigned short ADCR5; struct { unsigned char :8; const unsigned char ADCR5H; }; } @ 0xF028A;
extern __near __no_bit_access __no_init volatile union { unsigned short ADCR6; struct { unsigned char :8; const unsigned char ADCR6H; }; } @ 0xF028C;
extern __near __no_bit_access __no_init volatile union { unsigned short ADCR7; struct { unsigned char :8; const unsigned char ADCR7H; }; } @ 0xF028E;
extern __near __no_bit_access __no_init volatile union { unsigned short ADCR8; struct { unsigned char :8; const unsigned char ADCR8H; }; } @ 0xF0290;
extern __near __no_bit_access __no_init volatile union { unsigned short ADCR9; struct { unsigned char :8; const unsigned char ADCR9H; }; } @ 0xF0292;
extern __near __no_bit_access __no_init volatile union { unsigned short ADCR10; struct { unsigned char :8; const unsigned char ADCR10H; }; } @ 0xF0294;
extern __near __no_bit_access __no_init volatile union { unsigned short ADCR11; struct { unsigned char :8; const unsigned char ADCR11H; }; } @ 0xF0296;
extern __near __no_bit_access __no_init volatile union { unsigned short ADCR12; struct { unsigned char :8; const unsigned char ADCR12H; }; } @ 0xF0298;
extern __near __no_bit_access __no_init volatile union { unsigned short ADCR13; struct { unsigned char :8; const unsigned char ADCR13H; }; } @ 0xF029A;
extern __near __no_bit_access __no_init volatile union { unsigned short ADCR14; struct { unsigned char :8; const unsigned char ADCR14H; }; } @ 0xF029C;
extern __near __no_bit_access __no_init volatile union { unsigned short ADCR15; struct { unsigned char :8; const unsigned char ADCR15H; }; } @ 0xF029E;
extern __near __no_init volatile const union { unsigned char DFLST; __BITS8 DFLST_bit; } @ 0xF04F0;
extern __near __no_bit_access __no_init volatile unsigned short CGMCTRL @ 0xF05C0;
extern __near __no_bit_access __no_init volatile unsigned short CGMABT @ 0xF05C6;
extern __near __no_bit_access __no_init volatile unsigned char CGMABTD @ 0xF05C8;
extern __near __no_bit_access __no_init volatile unsigned char CGMCS @ 0xF05CE;
extern __near __no_bit_access __no_init volatile unsigned short CMASK1L @ 0xF05D0;
extern __near __no_bit_access __no_init volatile unsigned short CMASK1H @ 0xF05D2;
extern __near __no_bit_access __no_init volatile unsigned short CMASK2L @ 0xF05D4;
extern __near __no_bit_access __no_init volatile unsigned short CMASK2H @ 0xF05D6;
extern __near __no_bit_access __no_init volatile unsigned short CMASK3L @ 0xF05D8;
extern __near __no_bit_access __no_init volatile unsigned short CMASK3H @ 0xF05DA;
extern __near __no_bit_access __no_init volatile unsigned short CMASK4L @ 0xF05DC;
extern __near __no_bit_access __no_init volatile unsigned short CMASK4H @ 0xF05DE;
extern __near __no_bit_access __no_init volatile unsigned short CCTRL @ 0xF05E0;
extern __near __no_bit_access __no_init volatile unsigned char CLEC @ 0xF05E2;
extern __near __no_bit_access __no_init volatile const unsigned char CINFO @ 0xF05E3;
extern __near __no_bit_access __no_init volatile const unsigned short CERC @ 0xF05E4;
extern __near __no_bit_access __no_init volatile unsigned short CIE @ 0xF05E6;
extern __near __no_bit_access __no_init volatile unsigned short CINTS @ 0xF05E8;
extern __near __no_bit_access __no_init volatile unsigned char CBRP @ 0xF05EA;
extern __near __no_bit_access __no_init volatile unsigned short CBTR @ 0xF05EC;
extern __near __no_bit_access __no_init volatile const unsigned char CLIPT @ 0xF05EE;
extern __near __no_bit_access __no_init volatile unsigned short CRGPT @ 0xF05F0;
extern __near __no_bit_access __no_init volatile const unsigned char CLOPT @ 0xF05F2;
extern __near __no_bit_access __no_init volatile unsigned short CTGPT @ 0xF05F4;
extern __near __no_bit_access __no_init volatile unsigned short CTS @ 0xF05F6;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB0100; struct { unsigned char CMDB000; unsigned char CMDB100; }; } @ 0xF0600;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB2300; struct { unsigned char CMDB200; unsigned char CMDB300; }; } @ 0xF0602;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB4500; struct { unsigned char CMDB400; unsigned char CMDB500; }; } @ 0xF0604;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB6700; struct { unsigned char CMDB600; unsigned char CMDB700; }; } @ 0xF0606;
extern __near __no_bit_access __no_init volatile unsigned char CMDLC00 @ 0xF0608;
extern __near __no_bit_access __no_init volatile unsigned char CMCONF00 @ 0xF0609;
extern __near __no_bit_access __no_init volatile unsigned short CMIDL00 @ 0xF060A;
extern __near __no_bit_access __no_init volatile unsigned short CMIDH00 @ 0xF060C;
extern __near __no_bit_access __no_init volatile unsigned short CMCTRL00 @ 0xF060E;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB0101; struct { unsigned char CMDB001; unsigned char CMDB101; }; } @ 0xF0610;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB2301; struct { unsigned char CMDB201; unsigned char CMDB301; }; } @ 0xF0612;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB4501; struct { unsigned char CMDB401; unsigned char CMDB501; }; } @ 0xF0614;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB6701; struct { unsigned char CMDB601; unsigned char CMDB701; }; } @ 0xF0616;
extern __near __no_bit_access __no_init volatile unsigned char CMDLC01 @ 0xF0618;
extern __near __no_bit_access __no_init volatile unsigned char CMCONF01 @ 0xF0619;
extern __near __no_bit_access __no_init volatile unsigned short CMIDL01 @ 0xF061A;
extern __near __no_bit_access __no_init volatile unsigned short CMIDH01 @ 0xF061C;
extern __near __no_bit_access __no_init volatile unsigned short CMCTRL01 @ 0xF061E;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB0102; struct { unsigned char CMDB002; unsigned char CMDB102; }; } @ 0xF0620;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB2302; struct { unsigned char CMDB202; unsigned char CMDB302; }; } @ 0xF0622;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB4502; struct { unsigned char CMDB402; unsigned char CMDB502; }; } @ 0xF0624;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB6702; struct { unsigned char CMDB602; unsigned char CMDB702; }; } @ 0xF0626;
extern __near __no_bit_access __no_init volatile unsigned char CMDLC02 @ 0xF0628;
extern __near __no_bit_access __no_init volatile unsigned char CMCONF02 @ 0xF0629;
extern __near __no_bit_access __no_init volatile unsigned short CMIDL02 @ 0xF062A;
extern __near __no_bit_access __no_init volatile unsigned short CMIDH02 @ 0xF062C;
extern __near __no_bit_access __no_init volatile unsigned short CMCTRL02 @ 0xF062E;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB0103; struct { unsigned char CMDB003; unsigned char CMDB103; }; } @ 0xF0630;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB2303; struct { unsigned char CMDB203; unsigned char CMDB303; }; } @ 0xF0632;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB4503; struct { unsigned char CMDB403; unsigned char CMDB503; }; } @ 0xF0634;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB6703; struct { unsigned char CMDB603; unsigned char CMDB703; }; } @ 0xF0636;
extern __near __no_bit_access __no_init volatile unsigned char CMDLC03 @ 0xF0638;
extern __near __no_bit_access __no_init volatile unsigned char CMCONF03 @ 0xF0639;
extern __near __no_bit_access __no_init volatile unsigned short CMIDL03 @ 0xF063A;
extern __near __no_bit_access __no_init volatile unsigned short CMIDH03 @ 0xF063C;
extern __near __no_bit_access __no_init volatile unsigned short CMCTRL03 @ 0xF063E;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB0104; struct { unsigned char CMDB004; unsigned char CMDB104; }; } @ 0xF0640;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB2304; struct { unsigned char CMDB204; unsigned char CMDB304; }; } @ 0xF0642;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB4504; struct { unsigned char CMDB404; unsigned char CMDB504; }; } @ 0xF0644;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB6704; struct { unsigned char CMDB604; unsigned char CMDB704; }; } @ 0xF0646;
extern __near __no_bit_access __no_init volatile unsigned char CMDLC04 @ 0xF0648;
extern __near __no_bit_access __no_init volatile unsigned char CMCONF04 @ 0xF0649;
extern __near __no_bit_access __no_init volatile unsigned short CMIDL04 @ 0xF064A;
extern __near __no_bit_access __no_init volatile unsigned short CMIDH04 @ 0xF064C;
extern __near __no_bit_access __no_init volatile unsigned short CMCTRL04 @ 0xF064E;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB0105; struct { unsigned char CMDB005; unsigned char CMDB105; }; } @ 0xF0650;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB2305; struct { unsigned char CMDB205; unsigned char CMDB305; }; } @ 0xF0652;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB4505; struct { unsigned char CMDB405; unsigned char CMDB505; }; } @ 0xF0654;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB6705; struct { unsigned char CMDB605; unsigned char CMDB705; }; } @ 0xF0656;
extern __near __no_bit_access __no_init volatile unsigned char CMDLC05 @ 0xF0658;
extern __near __no_bit_access __no_init volatile unsigned char CMCONF05 @ 0xF0659;
extern __near __no_bit_access __no_init volatile unsigned short CMIDL05 @ 0xF065A;
extern __near __no_bit_access __no_init volatile unsigned short CMIDH05 @ 0xF065C;
extern __near __no_bit_access __no_init volatile unsigned short CMCTRL05 @ 0xF065E;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB0106; struct { unsigned char CMDB006; unsigned char CMDB106; }; } @ 0xF0660;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB2306; struct { unsigned char CMDB206; unsigned char CMDB306; }; } @ 0xF0662;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB4506; struct { unsigned char CMDB406; unsigned char CMDB506; }; } @ 0xF0664;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB6706; struct { unsigned char CMDB606; unsigned char CMDB706; }; } @ 0xF0666;
extern __near __no_bit_access __no_init volatile unsigned char CMDLC06 @ 0xF0668;
extern __near __no_bit_access __no_init volatile unsigned char CMCONF06 @ 0xF0669;
extern __near __no_bit_access __no_init volatile unsigned short CMIDL06 @ 0xF066A;
extern __near __no_bit_access __no_init volatile unsigned short CMIDH06 @ 0xF066C;
extern __near __no_bit_access __no_init volatile unsigned short CMCTRL06 @ 0xF066E;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB0107; struct { unsigned char CMDB007; unsigned char CMDB107; }; } @ 0xF0670;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB2307; struct { unsigned char CMDB207; unsigned char CMDB307; }; } @ 0xF0672;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB4507; struct { unsigned char CMDB407; unsigned char CMDB507; }; } @ 0xF0674;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB6707; struct { unsigned char CMDB607; unsigned char CMDB707; }; } @ 0xF0676;
extern __near __no_bit_access __no_init volatile unsigned char CMDLC07 @ 0xF0678;
extern __near __no_bit_access __no_init volatile unsigned char CMCONF07 @ 0xF0679;
extern __near __no_bit_access __no_init volatile unsigned short CMIDL07 @ 0xF067A;
extern __near __no_bit_access __no_init volatile unsigned short CMIDH07 @ 0xF067C;
extern __near __no_bit_access __no_init volatile unsigned short CMCTRL07 @ 0xF067E;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB0108; struct { unsigned char CMDB008; unsigned char CMDB108; }; } @ 0xF0680;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB2308; struct { unsigned char CMDB208; unsigned char CMDB308; }; } @ 0xF0682;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB4508; struct { unsigned char CMDB408; unsigned char CMDB508; }; } @ 0xF0684;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB6708; struct { unsigned char CMDB608; unsigned char CMDB708; }; } @ 0xF0686;
extern __near __no_bit_access __no_init volatile unsigned char CMDLC08 @ 0xF0688;
extern __near __no_bit_access __no_init volatile unsigned char CMCONF08 @ 0xF0689;
extern __near __no_bit_access __no_init volatile unsigned short CMIDL08 @ 0xF068A;
extern __near __no_bit_access __no_init volatile unsigned short CMIDH08 @ 0xF068C;
extern __near __no_bit_access __no_init volatile unsigned short CMCTRL08 @ 0xF068E;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB0109; struct { unsigned char CMDB009; unsigned char CMDB109; }; } @ 0xF0690;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB2309; struct { unsigned char CMDB209; unsigned char CMDB309; }; } @ 0xF0692;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB4509; struct { unsigned char CMDB409; unsigned char CMDB509; }; } @ 0xF0694;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB6709; struct { unsigned char CMDB609; unsigned char CMDB709; }; } @ 0xF0696;
extern __near __no_bit_access __no_init volatile unsigned char CMDLC09 @ 0xF0698;
extern __near __no_bit_access __no_init volatile unsigned char CMCONF09 @ 0xF0699;
extern __near __no_bit_access __no_init volatile unsigned short CMIDL09 @ 0xF069A;
extern __near __no_bit_access __no_init volatile unsigned short CMIDH09 @ 0xF069C;
extern __near __no_bit_access __no_init volatile unsigned short CMCTRL09 @ 0xF069E;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB0110; struct { unsigned char CMDB010; unsigned char CMDB110; }; } @ 0xF06A0;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB2310; struct { unsigned char CMDB210; unsigned char CMDB310; }; } @ 0xF06A2;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB4510; struct { unsigned char CMDB410; unsigned char CMDB510; }; } @ 0xF06A4;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB6710; struct { unsigned char CMDB610; unsigned char CMDB710; }; } @ 0xF06A6;
extern __near __no_bit_access __no_init volatile unsigned char CMDLC10 @ 0xF06A8;
extern __near __no_bit_access __no_init volatile unsigned char CMCONF10 @ 0xF06A9;
extern __near __no_bit_access __no_init volatile unsigned short CMIDL10 @ 0xF06AA;
extern __near __no_bit_access __no_init volatile unsigned short CMIDH10 @ 0xF06AC;
extern __near __no_bit_access __no_init volatile unsigned short CMCTRL10 @ 0xF06AE;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB0111; struct { unsigned char CMDB011; unsigned char CMDB111; }; } @ 0xF06B0;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB2311; struct { unsigned char CMDB211; unsigned char CMDB311; }; } @ 0xF06B2;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB4511; struct { unsigned char CMDB411; unsigned char CMDB511; }; } @ 0xF06B4;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB6711; struct { unsigned char CMDB611; unsigned char CMDB711; }; } @ 0xF06B6;
extern __near __no_bit_access __no_init volatile unsigned char CMDLC11 @ 0xF06B8;
extern __near __no_bit_access __no_init volatile unsigned char CMCONF11 @ 0xF06B9;
extern __near __no_bit_access __no_init volatile unsigned short CMIDL11 @ 0xF06BA;
extern __near __no_bit_access __no_init volatile unsigned short CMIDH11 @ 0xF06BC;
extern __near __no_bit_access __no_init volatile unsigned short CMCTRL11 @ 0xF06BE;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB0112; struct { unsigned char CMDB012; unsigned char CMDB112; }; } @ 0xF06C0;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB2312; struct { unsigned char CMDB212; unsigned char CMDB312; }; } @ 0xF06C2;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB4512; struct { unsigned char CMDB412; unsigned char CMDB512; }; } @ 0xF06C4;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB6712; struct { unsigned char CMDB612; unsigned char CMDB712; }; } @ 0xF06C6;
extern __near __no_bit_access __no_init volatile unsigned char CMDLC12 @ 0xF06C8;
extern __near __no_bit_access __no_init volatile unsigned char CMCONF12 @ 0xF06C9;
extern __near __no_bit_access __no_init volatile unsigned short CMIDL12 @ 0xF06CA;
extern __near __no_bit_access __no_init volatile unsigned short CMIDH12 @ 0xF06CC;
extern __near __no_bit_access __no_init volatile unsigned short CMCTRL12 @ 0xF06CE;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB0113; struct { unsigned char CMDB013; unsigned char CMDB113; }; } @ 0xF06D0;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB2313; struct { unsigned char CMDB213; unsigned char CMDB313; }; } @ 0xF06D2;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB4513; struct { unsigned char CMDB413; unsigned char CMDB513; }; } @ 0xF06D4;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB6713; struct { unsigned char CMDB613; unsigned char CMDB713; }; } @ 0xF06D6;
extern __near __no_bit_access __no_init volatile unsigned char CMDLC13 @ 0xF06D8;
extern __near __no_bit_access __no_init volatile unsigned char CMCONF13 @ 0xF06D9;
extern __near __no_bit_access __no_init volatile unsigned short CMIDL13 @ 0xF06DA;
extern __near __no_bit_access __no_init volatile unsigned short CMIDH13 @ 0xF06DC;
extern __near __no_bit_access __no_init volatile unsigned short CMCTRL13 @ 0xF06DE;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB0114; struct { unsigned char CMDB014; unsigned char CMDB114; }; } @ 0xF06E0;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB2314; struct { unsigned char CMDB214; unsigned char CMDB314; }; } @ 0xF06E2;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB4514; struct { unsigned char CMDB414; unsigned char CMDB514; }; } @ 0xF06E4;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB6714; struct { unsigned char CMDB614; unsigned char CMDB714; }; } @ 0xF06E6;
extern __near __no_bit_access __no_init volatile unsigned char CMDLC14 @ 0xF06E8;
extern __near __no_bit_access __no_init volatile unsigned char CMCONF14 @ 0xF06E9;
extern __near __no_bit_access __no_init volatile unsigned short CMIDL14 @ 0xF06EA;
extern __near __no_bit_access __no_init volatile unsigned short CMIDH14 @ 0xF06EC;
extern __near __no_bit_access __no_init volatile unsigned short CMCTRL14 @ 0xF06EE;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB0115; struct { unsigned char CMDB015; unsigned char CMDB115; }; } @ 0xF06F0;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB2315; struct { unsigned char CMDB215; unsigned char CMDB315; }; } @ 0xF06F2;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB4515; struct { unsigned char CMDB415; unsigned char CMDB515; }; } @ 0xF06F4;
extern __near __no_bit_access __no_init volatile union { unsigned short CMDB6715; struct { unsigned char CMDB615; unsigned char CMDB715; }; } @ 0xF06F6;
extern __near __no_bit_access __no_init volatile unsigned char CMDLC15 @ 0xF06F8;
extern __near __no_bit_access __no_init volatile unsigned char CMCONF15 @ 0xF06F9;
extern __near __no_bit_access __no_init volatile unsigned short CMIDL15 @ 0xF06FA;
extern __near __no_bit_access __no_init volatile unsigned short CMIDH15 @ 0xF06FC;
extern __near __no_bit_access __no_init volatile unsigned short CMCTRL15 @ 0xF06FE;

/*----------------------------------------------
 *       Extended SFR bit declarations
 *--------------------------------------------*/

#define GDCSC             GUARD_bit.no0
#define GDPLL             GUARD_bit.no1
#define GDLTRM            GUARD_bit.no2
#define GDLVI             GUARD_bit.no5
#define GDIAW             GUARD_bit.no6
#define GDWDT             GUARD_bit.no7

#define IAWEN             IAWCTL_bit.no7

#define DS2               DMC2_bit.no5
#define DRS2              DMC2_bit.no6
#define STG2              DMC2_bit.no7

#define DS3               DMC3_bit.no5
#define DRS3              DMC3_bit.no6
#define STG3              DMC3_bit.no7

#define DST2              DRC2_bit.no0
#define DEN2              DRC2_bit.no7

#define DST3              DRC3_bit.no0
#define DEN3              DRC3_bit.no7

#define DWAITALL          DMCALL_bit.no0
#define DPRMOD            DMCALL_bit.no7

#define DIVST             MDUC_bit.no0
#define DIVMODE           MDUC_bit.no7

#define TAU0EN            PER0_bit.no0
#define TAU1EN            PER0_bit.no1
#define TAU2EN            PER0_bit.no2
#define SAU0EN            PER0_bit.no3
#define SAU1EN            PER0_bit.no4
#define LIN0EN            PER0_bit.no5
#define LIN1EN            PER0_bit.no6
#define ADCEN             PER0_bit.no7

#define DFLEN             PER1_bit.no0
#define WUTEN             PER1_bit.no1
#define SAU2EN            PER1_bit.no3

#define WUTMCKE           PCKSEL_bit.no2
#define CANMCKE           PCKSEL_bit.no4

#define SELPLLS           PLLSTS_bit.no3
#define LOCK              PLLSTS_bit.no7

#define PLLON             PLLCTL_bit.no0
#define SELPLL            PLLCTL_bit.no2

#define STPSEL            STPSTC_bit.no0
#define STPLV             STPSTC_bit.no4
#define STPOEN            STPSTC_bit.no7

#define UF0RXE            UF0CTL0_bit.no5
#define UF0TXE            UF0CTL0_bit.no6

#define UF0BTT            UF0OPT0_bit.no5
#define UF0BRT            UF0OPT0_bit.no6
#define UF0BRF            UF0OPT0_bit.no7

#define UF0EBC            UF0OPT1_bit.no5

#define UF0ITS            UF0OPT2_bit.no0

#define UF1RXE            UF1CTL0_bit.no5
#define UF1TXE            UF1CTL0_bit.no6

#define UF1BTT            UF1OPT0_bit.no5
#define UF1BRT            UF1OPT0_bit.no6
#define UF1BRF            UF1OPT0_bit.no7

#define UF1EBC            UF1OPT1_bit.no5

#define UF1ITS            UF1OPT2_bit.no0

#define DFRDY             DFLST_bit.no0

#pragma language=default

#endif /* __IAR_SYSTEMS_ICC__ */

#ifdef __IAR_SYSTEMS_ASM__

/*----------------------------------------------
 *       Extended SFR declarations
 *--------------------------------------------*/

ADPC       DEFINE  0xF0017
PU0        DEFINE  0xF0030
PU1        DEFINE  0xF0031
PU3        DEFINE  0xF0033
PU4        DEFINE  0xF0034
PU5        DEFINE  0xF0035
PU6        DEFINE  0xF0036
PU7        DEFINE  0xF0037
PU12       DEFINE  0xF003C
PU14       DEFINE  0xF003E
PIM6       DEFINE  0xF0046
PIM7       DEFINE  0xF0047
POM4       DEFINE  0xF0054
POM7       DEFINE  0xF0057
NFEN0      DEFINE  0xF0060
NFEN1      DEFINE  0xF0061
NFEN2      DEFINE  0xF0062
NFEN3      DEFINE  0xF0063
LVIOUT     DEFINE  0xF0067
PSRSEL     DEFINE  0xF006F
GUARD      DEFINE  0xF0070
WDTSELF    DEFINE  0xF0071
IAWCTL     DEFINE  0xF0074
IAWRAM     DEFINE  0xF0075
IAWFLASH   DEFINE  0xF0076
DSA2       DEFINE  0xF0080
DSA3       DEFINE  0xF0081
DRA2       DEFINE  0xF0082
DRA2L      DEFINE  0xF0082
DRA2H      DEFINE  0xF0083
DRA3       DEFINE  0xF0084
DRA3L      DEFINE  0xF0084
DRA3H      DEFINE  0xF0085
DBC2       DEFINE  0xF0086
DBC2L      DEFINE  0xF0086
DBC2H      DEFINE  0xF0087
DBC3       DEFINE  0xF0088
DBC3L      DEFINE  0xF0088
DBC3H      DEFINE  0xF0089
DMC2       DEFINE  0xF008A
DMC3       DEFINE  0xF008B
DRC2       DEFINE  0xF008C
DRC3       DEFINE  0xF008D
DMCALL     DEFINE  0xF008F
MDCL       DEFINE  0xF00E0
MDCH       DEFINE  0xF00E2
MDUC       DEFINE  0xF00E8
PER0       DEFINE  0xF00F0
PER1       DEFINE  0xF00F1
PCKSEL     DEFINE  0xF00F2
OSMC       DEFINE  0xF00F3
PLLSTS     DEFINE  0xF00F6
PLLCTL     DEFINE  0xF00F7
HIOTRM     DEFINE  0xF00F8
LIOTRM     DEFINE  0xF00FA
POCRES     DEFINE  0xF00FB
STPSTC     DEFINE  0xF00FC
BCDADJ     DEFINE  0xF00FE
SSR00      DEFINE  0xF0100
SSR00L     DEFINE  0xF0100
SSR01      DEFINE  0xF0102
SSR01L     DEFINE  0xF0102
SIR00      DEFINE  0xF0104
SIR00L     DEFINE  0xF0104
SIR01      DEFINE  0xF0106
SIR01L     DEFINE  0xF0106
SMR00      DEFINE  0xF0108
SMR01      DEFINE  0xF010A
SCR00      DEFINE  0xF010C
SCR01      DEFINE  0xF010E
SE0        DEFINE  0xF0110
SE0L       DEFINE  0xF0110
SS0        DEFINE  0xF0112
SS0L       DEFINE  0xF0112
ST0        DEFINE  0xF0114
ST0L       DEFINE  0xF0114
SPS0       DEFINE  0xF0116
SPS0L      DEFINE  0xF0116
SO0        DEFINE  0xF0118
SOE0       DEFINE  0xF011A
SOE0L      DEFINE  0xF011A
SOL0       DEFINE  0xF0120
SOL0L      DEFINE  0xF0120
SSE0       DEFINE  0xF0122
SSE0L      DEFINE  0xF0122
SSR10      DEFINE  0xF0130
SSR10L     DEFINE  0xF0130
SSR11      DEFINE  0xF0132
SSR11L     DEFINE  0xF0132
SIR10      DEFINE  0xF0134
SIR10L     DEFINE  0xF0134
SIR11      DEFINE  0xF0136
SIR11L     DEFINE  0xF0136
SMR10      DEFINE  0xF0138
SMR11      DEFINE  0xF013A
SCR10      DEFINE  0xF013C
SCR11      DEFINE  0xF013E
SE1        DEFINE  0xF0140
SE1L       DEFINE  0xF0140
SS1        DEFINE  0xF0142
SS1L       DEFINE  0xF0142
ST1        DEFINE  0xF0144
ST1L       DEFINE  0xF0144
SPS1       DEFINE  0xF0146
SPS1L      DEFINE  0xF0146
SO1        DEFINE  0xF0148
SOE1       DEFINE  0xF014A
SOE1L      DEFINE  0xF014A
SOL1       DEFINE  0xF0150
SOL1L      DEFINE  0xF0150
SOL2       DEFINE  0xF0158
SOL2L      DEFINE  0xF0158
SSR20      DEFINE  0xF0160
SSR20L     DEFINE  0xF0160
SSR21      DEFINE  0xF0162
SSR21L     DEFINE  0xF0162
SIR20      DEFINE  0xF0164
SIR20L     DEFINE  0xF0164
SIR21      DEFINE  0xF0166
SIR21L     DEFINE  0xF0166
SMR20      DEFINE  0xF0168
SMR21      DEFINE  0xF016A
SCR20      DEFINE  0xF016C
SCR21      DEFINE  0xF016E
SE2        DEFINE  0xF0170
SE2L       DEFINE  0xF0170
SS2        DEFINE  0xF0172
SS2L       DEFINE  0xF0172
ST2        DEFINE  0xF0174
ST2L       DEFINE  0xF0174
SPS2       DEFINE  0xF0176
SPS2L      DEFINE  0xF0176
SO2        DEFINE  0xF0178
SOE2       DEFINE  0xF017A
SOE2L      DEFINE  0xF017A
TCR00      DEFINE  0xF0180
TCR01      DEFINE  0xF0182
TCR02      DEFINE  0xF0184
TCR03      DEFINE  0xF0186
TCR04      DEFINE  0xF0188
TCR05      DEFINE  0xF018A
TCR06      DEFINE  0xF018C
TCR07      DEFINE  0xF018E
TMR00      DEFINE  0xF0190
TMR01      DEFINE  0xF0192
TMR02      DEFINE  0xF0194
TMR03      DEFINE  0xF0196
TMR04      DEFINE  0xF0198
TMR05      DEFINE  0xF019A
TMR06      DEFINE  0xF019C
TMR07      DEFINE  0xF019E
TSR00      DEFINE  0xF01A0
TSR00L     DEFINE  0xF01A0
TSR01      DEFINE  0xF01A2
TSR01L     DEFINE  0xF01A2
TSR02      DEFINE  0xF01A4
TSR02L     DEFINE  0xF01A4
TSR03      DEFINE  0xF01A6
TSR03L     DEFINE  0xF01A6
TSR04      DEFINE  0xF01A8
TSR04L     DEFINE  0xF01A8
TSR05      DEFINE  0xF01AA
TSR05L     DEFINE  0xF01AA
TSR06      DEFINE  0xF01AC
TSR06L     DEFINE  0xF01AC
TSR07      DEFINE  0xF01AE
TSR07L     DEFINE  0xF01AE
TE0        DEFINE  0xF01B0
TE0L       DEFINE  0xF01B0
TS0        DEFINE  0xF01B2
TS0L       DEFINE  0xF01B2
TT0        DEFINE  0xF01B4
TT0L       DEFINE  0xF01B4
TPS0       DEFINE  0xF01B6
TO0        DEFINE  0xF01B8
TO0L       DEFINE  0xF01B8
TOE0       DEFINE  0xF01BA
TOE0L      DEFINE  0xF01BA
TOL0       DEFINE  0xF01BC
TOL0L      DEFINE  0xF01BC
TOM0       DEFINE  0xF01BE
TOM0L      DEFINE  0xF01BE
TCR10      DEFINE  0xF01C0
TCR11      DEFINE  0xF01C2
TCR12      DEFINE  0xF01C4
TCR13      DEFINE  0xF01C6
TCR14      DEFINE  0xF01C8
TCR15      DEFINE  0xF01CA
TCR16      DEFINE  0xF01CC
TCR17      DEFINE  0xF01CE
TMR10      DEFINE  0xF01D0
TMR11      DEFINE  0xF01D2
TMR12      DEFINE  0xF01D4
TMR13      DEFINE  0xF01D6
TMR14      DEFINE  0xF01D8
TMR15      DEFINE  0xF01DA
TMR16      DEFINE  0xF01DC
TMR17      DEFINE  0xF01DE
TSR10      DEFINE  0xF01E0
TSR10L     DEFINE  0xF01E0
TSR11      DEFINE  0xF01E2
TSR11L     DEFINE  0xF01E2
TSR12      DEFINE  0xF01E4
TSR12L     DEFINE  0xF01E4
TSR13      DEFINE  0xF01E6
TSR13L     DEFINE  0xF01E6
TSR14      DEFINE  0xF01E8
TSR14L     DEFINE  0xF01E8
TSR15      DEFINE  0xF01EA
TSR15L     DEFINE  0xF01EA
TSR16      DEFINE  0xF01EC
TSR16L     DEFINE  0xF01EC
TSR17      DEFINE  0xF01EE
TSR17L     DEFINE  0xF01EE
TE1        DEFINE  0xF01F0
TE1L       DEFINE  0xF01F0
TS1        DEFINE  0xF01F2
TS1L       DEFINE  0xF01F2
TT1        DEFINE  0xF01F4
TT1L       DEFINE  0xF01F4
TPS1       DEFINE  0xF01F6
TO1        DEFINE  0xF01F8
TO1L       DEFINE  0xF01F8
TOE1       DEFINE  0xF01FA
TOE1L      DEFINE  0xF01FA
TOL1       DEFINE  0xF01FC
TOL1L      DEFINE  0xF01FC
TOM1       DEFINE  0xF01FE
TOM1L      DEFINE  0xF01FE
TCR20      DEFINE  0xF0200
TCR21      DEFINE  0xF0202
TCR22      DEFINE  0xF0204
TCR23      DEFINE  0xF0206
TMR20      DEFINE  0xF0210
TMR21      DEFINE  0xF0212
TMR22      DEFINE  0xF0214
TMR23      DEFINE  0xF0216
TSR20      DEFINE  0xF0220
TSR20L     DEFINE  0xF0220
TSR21      DEFINE  0xF0222
TSR21L     DEFINE  0xF0222
TSR22      DEFINE  0xF0224
TSR22L     DEFINE  0xF0224
TSR23      DEFINE  0xF0226
TSR23L     DEFINE  0xF0226
TE2        DEFINE  0xF0230
TE2L       DEFINE  0xF0230
TS2        DEFINE  0xF0232
TS2L       DEFINE  0xF0232
TT2        DEFINE  0xF0234
TT2L       DEFINE  0xF0234
TPS2       DEFINE  0xF0236
TO2        DEFINE  0xF0238
TO2L       DEFINE  0xF0238
TOE2       DEFINE  0xF023A
TOE2L      DEFINE  0xF023A
TOL2       DEFINE  0xF023C
TOL2L      DEFINE  0xF023C
TOM2       DEFINE  0xF023E
TOM2L      DEFINE  0xF023E
UF0CTL0    DEFINE  0xF0240
UF0OPT0    DEFINE  0xF0241
UF0CTL1    DEFINE  0xF0242
UF0OPT1    DEFINE  0xF0244
UF0OPT2    DEFINE  0xF0245
UF0STR     DEFINE  0xF0246
UF0STC     DEFINE  0xF0248
UF0WTX     DEFINE  0xF024A
UF0WTXB    DEFINE  0xF024A
UF0ID      DEFINE  0xF024E
UF0BUF0    DEFINE  0xF024F
UF0BUF1    DEFINE  0xF0250
UF0BUF2    DEFINE  0xF0251
UF0BUF3    DEFINE  0xF0252
UF0BUF4    DEFINE  0xF0253
UF0BUF5    DEFINE  0xF0254
UF0BUF6    DEFINE  0xF0255
UF0BUF7    DEFINE  0xF0256
UF0BUF8    DEFINE  0xF0257
UF0BUCTL   DEFINE  0xF0258
UF1CTL0    DEFINE  0xF0260
UF1OPT0    DEFINE  0xF0261
UF1CTL1    DEFINE  0xF0262
UF1OPT1    DEFINE  0xF0264
UF1OPT2    DEFINE  0xF0265
UF1STR     DEFINE  0xF0266
UF1STC     DEFINE  0xF0268
UF1WTX     DEFINE  0xF026A
UF1WTXB    DEFINE  0xF026A
UF1ID      DEFINE  0xF026E
UF1BUF0    DEFINE  0xF026F
UF1BUF1    DEFINE  0xF0270
UF1BUF2    DEFINE  0xF0271
UF1BUF3    DEFINE  0xF0272
UF1BUF4    DEFINE  0xF0273
UF1BUF5    DEFINE  0xF0274
UF1BUF6    DEFINE  0xF0275
UF1BUF7    DEFINE  0xF0276
UF1BUF8    DEFINE  0xF0277
UF1BUCTL   DEFINE  0xF0278
ADCR0      DEFINE  0xF0280
ADCR0H     DEFINE  0xF0281
ADCR1      DEFINE  0xF0282
ADCR1H     DEFINE  0xF0283
ADCR2      DEFINE  0xF0284
ADCR2H     DEFINE  0xF0285
ADCR3      DEFINE  0xF0286
ADCR3H     DEFINE  0xF0287
ADCR4      DEFINE  0xF0288
ADCR4H     DEFINE  0xF0289
ADCR5      DEFINE  0xF028A
ADCR5H     DEFINE  0xF028B
ADCR6      DEFINE  0xF028C
ADCR6H     DEFINE  0xF028D
ADCR7      DEFINE  0xF028E
ADCR7H     DEFINE  0xF028F
ADCR8      DEFINE  0xF0290
ADCR8H     DEFINE  0xF0291
ADCR9      DEFINE  0xF0292
ADCR9H     DEFINE  0xF0293
ADCR10     DEFINE  0xF0294
ADCR10H    DEFINE  0xF0295
ADCR11     DEFINE  0xF0296
ADCR11H    DEFINE  0xF0297
ADCR12     DEFINE  0xF0298
ADCR12H    DEFINE  0xF0299
ADCR13     DEFINE  0xF029A
ADCR13H    DEFINE  0xF029B
ADCR14     DEFINE  0xF029C
ADCR14H    DEFINE  0xF029D
ADCR15     DEFINE  0xF029E
ADCR15H    DEFINE  0xF029F
DFLST      DEFINE  0xF04F0
CGMCTRL    DEFINE  0xF05C0
CGMABT     DEFINE  0xF05C6
CGMABTD    DEFINE  0xF05C8
CGMCS      DEFINE  0xF05CE
CMASK1L    DEFINE  0xF05D0
CMASK1H    DEFINE  0xF05D2
CMASK2L    DEFINE  0xF05D4
CMASK2H    DEFINE  0xF05D6
CMASK3L    DEFINE  0xF05D8
CMASK3H    DEFINE  0xF05DA
CMASK4L    DEFINE  0xF05DC
CMASK4H    DEFINE  0xF05DE
CCTRL      DEFINE  0xF05E0
CLEC       DEFINE  0xF05E2
CINFO      DEFINE  0xF05E3
CERC       DEFINE  0xF05E4
CIE        DEFINE  0xF05E6
CINTS      DEFINE  0xF05E8
CBRP       DEFINE  0xF05EA
CBTR       DEFINE  0xF05EC
CLIPT      DEFINE  0xF05EE
CRGPT      DEFINE  0xF05F0
CLOPT      DEFINE  0xF05F2
CTGPT      DEFINE  0xF05F4
CTS        DEFINE  0xF05F6
CMDB0100   DEFINE  0xF0600
CMDB000    DEFINE  0xF0600
CMDB100    DEFINE  0xF0601
CMDB2300   DEFINE  0xF0602
CMDB200    DEFINE  0xF0602
CMDB300    DEFINE  0xF0603
CMDB4500   DEFINE  0xF0604
CMDB400    DEFINE  0xF0604
CMDB500    DEFINE  0xF0605
CMDB6700   DEFINE  0xF0606
CMDB600    DEFINE  0xF0606
CMDB700    DEFINE  0xF0607
CMDLC00    DEFINE  0xF0608
CMCONF00   DEFINE  0xF0609
CMIDL00    DEFINE  0xF060A
CMIDH00    DEFINE  0xF060C
CMCTRL00   DEFINE  0xF060E
CMDB0101   DEFINE  0xF0610
CMDB001    DEFINE  0xF0610
CMDB101    DEFINE  0xF0611
CMDB2301   DEFINE  0xF0612
CMDB201    DEFINE  0xF0612
CMDB301    DEFINE  0xF0613
CMDB4501   DEFINE  0xF0614
CMDB401    DEFINE  0xF0614
CMDB501    DEFINE  0xF0615
CMDB6701   DEFINE  0xF0616
CMDB601    DEFINE  0xF0616
CMDB701    DEFINE  0xF0617
CMDLC01    DEFINE  0xF0618
CMCONF01   DEFINE  0xF0619
CMIDL01    DEFINE  0xF061A
CMIDH01    DEFINE  0xF061C
CMCTRL01   DEFINE  0xF061E
CMDB0102   DEFINE  0xF0620
CMDB002    DEFINE  0xF0620
CMDB102    DEFINE  0xF0621
CMDB2302   DEFINE  0xF0622
CMDB202    DEFINE  0xF0622
CMDB302    DEFINE  0xF0623
CMDB4502   DEFINE  0xF0624
CMDB402    DEFINE  0xF0624
CMDB502    DEFINE  0xF0625
CMDB6702   DEFINE  0xF0626
CMDB602    DEFINE  0xF0626
CMDB702    DEFINE  0xF0627
CMDLC02    DEFINE  0xF0628
CMCONF02   DEFINE  0xF0629
CMIDL02    DEFINE  0xF062A
CMIDH02    DEFINE  0xF062C
CMCTRL02   DEFINE  0xF062E
CMDB0103   DEFINE  0xF0630
CMDB003    DEFINE  0xF0630
CMDB103    DEFINE  0xF0631
CMDB2303   DEFINE  0xF0632
CMDB203    DEFINE  0xF0632
CMDB303    DEFINE  0xF0633
CMDB4503   DEFINE  0xF0634
CMDB403    DEFINE  0xF0634
CMDB503    DEFINE  0xF0635
CMDB6703   DEFINE  0xF0636
CMDB603    DEFINE  0xF0636
CMDB703    DEFINE  0xF0637
CMDLC03    DEFINE  0xF0638
CMCONF03   DEFINE  0xF0639
CMIDL03    DEFINE  0xF063A
CMIDH03    DEFINE  0xF063C
CMCTRL03   DEFINE  0xF063E
CMDB0104   DEFINE  0xF0640
CMDB004    DEFINE  0xF0640
CMDB104    DEFINE  0xF0641
CMDB2304   DEFINE  0xF0642
CMDB204    DEFINE  0xF0642
CMDB304    DEFINE  0xF0643
CMDB4504   DEFINE  0xF0644
CMDB404    DEFINE  0xF0644
CMDB504    DEFINE  0xF0645
CMDB6704   DEFINE  0xF0646
CMDB604    DEFINE  0xF0646
CMDB704    DEFINE  0xF0647
CMDLC04    DEFINE  0xF0648
CMCONF04   DEFINE  0xF0649
CMIDL04    DEFINE  0xF064A
CMIDH04    DEFINE  0xF064C
CMCTRL04   DEFINE  0xF064E
CMDB0105   DEFINE  0xF0650
CMDB005    DEFINE  0xF0650
CMDB105    DEFINE  0xF0651
CMDB2305   DEFINE  0xF0652
CMDB205    DEFINE  0xF0652
CMDB305    DEFINE  0xF0653
CMDB4505   DEFINE  0xF0654
CMDB405    DEFINE  0xF0654
CMDB505    DEFINE  0xF0655
CMDB6705   DEFINE  0xF0656
CMDB605    DEFINE  0xF0656
CMDB705    DEFINE  0xF0657
CMDLC05    DEFINE  0xF0658
CMCONF05   DEFINE  0xF0659
CMIDL05    DEFINE  0xF065A
CMIDH05    DEFINE  0xF065C
CMCTRL05   DEFINE  0xF065E
CMDB0106   DEFINE  0xF0660
CMDB006    DEFINE  0xF0660
CMDB106    DEFINE  0xF0661
CMDB2306   DEFINE  0xF0662
CMDB206    DEFINE  0xF0662
CMDB306    DEFINE  0xF0663
CMDB4506   DEFINE  0xF0664
CMDB406    DEFINE  0xF0664
CMDB506    DEFINE  0xF0665
CMDB6706   DEFINE  0xF0666
CMDB606    DEFINE  0xF0666
CMDB706    DEFINE  0xF0667
CMDLC06    DEFINE  0xF0668
CMCONF06   DEFINE  0xF0669
CMIDL06    DEFINE  0xF066A
CMIDH06    DEFINE  0xF066C
CMCTRL06   DEFINE  0xF066E
CMDB0107   DEFINE  0xF0670
CMDB007    DEFINE  0xF0670
CMDB107    DEFINE  0xF0671
CMDB2307   DEFINE  0xF0672
CMDB207    DEFINE  0xF0672
CMDB307    DEFINE  0xF0673
CMDB4507   DEFINE  0xF0674
CMDB407    DEFINE  0xF0674
CMDB507    DEFINE  0xF0675
CMDB6707   DEFINE  0xF0676
CMDB607    DEFINE  0xF0676
CMDB707    DEFINE  0xF0677
CMDLC07    DEFINE  0xF0678
CMCONF07   DEFINE  0xF0679
CMIDL07    DEFINE  0xF067A
CMIDH07    DEFINE  0xF067C
CMCTRL07   DEFINE  0xF067E
CMDB0108   DEFINE  0xF0680
CMDB008    DEFINE  0xF0680
CMDB108    DEFINE  0xF0681
CMDB2308   DEFINE  0xF0682
CMDB208    DEFINE  0xF0682
CMDB308    DEFINE  0xF0683
CMDB4508   DEFINE  0xF0684
CMDB408    DEFINE  0xF0684
CMDB508    DEFINE  0xF0685
CMDB6708   DEFINE  0xF0686
CMDB608    DEFINE  0xF0686
CMDB708    DEFINE  0xF0687
CMDLC08    DEFINE  0xF0688
CMCONF08   DEFINE  0xF0689
CMIDL08    DEFINE  0xF068A
CMIDH08    DEFINE  0xF068C
CMCTRL08   DEFINE  0xF068E
CMDB0109   DEFINE  0xF0690
CMDB009    DEFINE  0xF0690
CMDB109    DEFINE  0xF0691
CMDB2309   DEFINE  0xF0692
CMDB209    DEFINE  0xF0692
CMDB309    DEFINE  0xF0693
CMDB4509   DEFINE  0xF0694
CMDB409    DEFINE  0xF0694
CMDB509    DEFINE  0xF0695
CMDB6709   DEFINE  0xF0696
CMDB609    DEFINE  0xF0696
CMDB709    DEFINE  0xF0697
CMDLC09    DEFINE  0xF0698
CMCONF09   DEFINE  0xF0699
CMIDL09    DEFINE  0xF069A
CMIDH09    DEFINE  0xF069C
CMCTRL09   DEFINE  0xF069E
CMDB0110   DEFINE  0xF06A0
CMDB010    DEFINE  0xF06A0
CMDB110    DEFINE  0xF06A1
CMDB2310   DEFINE  0xF06A2
CMDB210    DEFINE  0xF06A2
CMDB310    DEFINE  0xF06A3
CMDB4510   DEFINE  0xF06A4
CMDB410    DEFINE  0xF06A4
CMDB510    DEFINE  0xF06A5
CMDB6710   DEFINE  0xF06A6
CMDB610    DEFINE  0xF06A6
CMDB710    DEFINE  0xF06A7
CMDLC10    DEFINE  0xF06A8
CMCONF10   DEFINE  0xF06A9
CMIDL10    DEFINE  0xF06AA
CMIDH10    DEFINE  0xF06AC
CMCTRL10   DEFINE  0xF06AE
CMDB0111   DEFINE  0xF06B0
CMDB011    DEFINE  0xF06B0
CMDB111    DEFINE  0xF06B1
CMDB2311   DEFINE  0xF06B2
CMDB211    DEFINE  0xF06B2
CMDB311    DEFINE  0xF06B3
CMDB4511   DEFINE  0xF06B4
CMDB411    DEFINE  0xF06B4
CMDB511    DEFINE  0xF06B5
CMDB6711   DEFINE  0xF06B6
CMDB611    DEFINE  0xF06B6
CMDB711    DEFINE  0xF06B7
CMDLC11    DEFINE  0xF06B8
CMCONF11   DEFINE  0xF06B9
CMIDL11    DEFINE  0xF06BA
CMIDH11    DEFINE  0xF06BC
CMCTRL11   DEFINE  0xF06BE
CMDB0112   DEFINE  0xF06C0
CMDB012    DEFINE  0xF06C0
CMDB112    DEFINE  0xF06C1
CMDB2312   DEFINE  0xF06C2
CMDB212    DEFINE  0xF06C2
CMDB312    DEFINE  0xF06C3
CMDB4512   DEFINE  0xF06C4
CMDB412    DEFINE  0xF06C4
CMDB512    DEFINE  0xF06C5
CMDB6712   DEFINE  0xF06C6
CMDB612    DEFINE  0xF06C6
CMDB712    DEFINE  0xF06C7
CMDLC12    DEFINE  0xF06C8
CMCONF12   DEFINE  0xF06C9
CMIDL12    DEFINE  0xF06CA
CMIDH12    DEFINE  0xF06CC
CMCTRL12   DEFINE  0xF06CE
CMDB0113   DEFINE  0xF06D0
CMDB013    DEFINE  0xF06D0
CMDB113    DEFINE  0xF06D1
CMDB2313   DEFINE  0xF06D2
CMDB213    DEFINE  0xF06D2
CMDB313    DEFINE  0xF06D3
CMDB4513   DEFINE  0xF06D4
CMDB413    DEFINE  0xF06D4
CMDB513    DEFINE  0xF06D5
CMDB6713   DEFINE  0xF06D6
CMDB613    DEFINE  0xF06D6
CMDB713    DEFINE  0xF06D7
CMDLC13    DEFINE  0xF06D8
CMCONF13   DEFINE  0xF06D9
CMIDL13    DEFINE  0xF06DA
CMIDH13    DEFINE  0xF06DC
CMCTRL13   DEFINE  0xF06DE
CMDB0114   DEFINE  0xF06E0
CMDB014    DEFINE  0xF06E0
CMDB114    DEFINE  0xF06E1
CMDB2314   DEFINE  0xF06E2
CMDB214    DEFINE  0xF06E2
CMDB314    DEFINE  0xF06E3
CMDB4514   DEFINE  0xF06E4
CMDB414    DEFINE  0xF06E4
CMDB514    DEFINE  0xF06E5
CMDB6714   DEFINE  0xF06E6
CMDB614    DEFINE  0xF06E6
CMDB714    DEFINE  0xF06E7
CMDLC14    DEFINE  0xF06E8
CMCONF14   DEFINE  0xF06E9
CMIDL14    DEFINE  0xF06EA
CMIDH14    DEFINE  0xF06EC
CMCTRL14   DEFINE  0xF06EE
CMDB0115   DEFINE  0xF06F0
CMDB015    DEFINE  0xF06F0
CMDB115    DEFINE  0xF06F1
CMDB2315   DEFINE  0xF06F2
CMDB215    DEFINE  0xF06F2
CMDB315    DEFINE  0xF06F3
CMDB4515   DEFINE  0xF06F4
CMDB415    DEFINE  0xF06F4
CMDB515    DEFINE  0xF06F5
CMDB6715   DEFINE  0xF06F6
CMDB615    DEFINE  0xF06F6
CMDB715    DEFINE  0xF06F7
CMDLC15    DEFINE  0xF06F8
CMCONF15   DEFINE  0xF06F9
CMIDL15    DEFINE  0xF06FA
CMIDH15    DEFINE  0xF06FC
CMCTRL15   DEFINE  0xF06FE

#endif /* __IAR_SYSTEMS_ASM__ */

#endif /* __IO78F1840_80_EXT_H__ */
