/*
*******************************************************************************
* Copyright(C) 2008, 2010 Renesas Electronics Corporation
* RENESAS ELECTRONICS CONFIDENTIAL AND PROPRIETARY
* This program must be used solely for the purpose for which
* it was furnished by Renesas Electronics Corporation. No part of this
* program may be reproduced or disclosed to others, in any
* form, without the prior written permission of Renesas Electronics
* Corporation. 
*
* This device driver was created by Applilet3 for 78K0R/Fx3
* Filename:	CG_timer_user.c
* Abstract:	This file implements device driver for TAU module.
* APIlib:	Applilet3 for 78K0R/Fx3 V2.01 [22 Oct 2010]
* Device:	uPD78F1840_80
* Compiler:	IAR Systems icc78k0r
* Creation date:	2015/4/2
* Created By:       Henson.li
*******************************************************************************
*/

/*
*******************************************************************************
** Include files
*******************************************************************************
*/
#include "CG_macrodriver.h"
#include "TIMER.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/*
*******************************************************************************
**  Global define
*******************************************************************************
*/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function is INTTM12 interrupt service routine.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
#pragma vector = INTTM12_vect
__interrupt void MD_INTTM12(void)
{
	/* Start user code. Do not edit comment generated here */
	/* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
