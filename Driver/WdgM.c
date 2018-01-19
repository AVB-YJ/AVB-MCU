/*===================================================================*\
 *--------------------------------------------------------------------
 * Module Name:     WdgM.c
 * Created By:      IPM
 * Created Date:    01 Mayl 2010
 * %version:        1 %
 * %cvtype:         csrc %
 * %instance:       ctc_aud_5 %
 * %derived_by:     lzs7ws %
 * %date_modified:  Sat Mar 15 09:48:51 2008 %
 *--------------------------------------------------------------------
 *
 * Description:
 *   This is the manager module for triggering the Watchdog mechanism 
\*===================================================================*/

#include "WdgM.h"
#include "Wdg_36_78K0R_FX3.h"
#include "OS_Task.h"

/*.===================================================================*\
*. FUNCTION: WdgM_Init
*.=====================================================================
*. Return Value:
*.  None
*.
*. Parameters:
*.  None
*.
*. External references: Wdg_36_78K0R_FX3Init()
*.  External variables:
*.   None
*.  File scope variables:
*.   None
*.
*. Description: This initialises the component
*.
\*===================================================================*/

void WdgM_Init(void)
{
    /* Initialise the watch dog registers*/
   Wdg_36_78K0R_FX3Init(NULL_PTR);
}

/*.===================================================================*\
*. FUNCTION: WdgM_Start
*.=====================================================================
*. Return Value:
*. None 
*.
*. Parameters:
*.  None
*.
*. External references: OS_ActivateTask
*.  External variables:
*.   None
*.  File scope variables:
*.   None
*.
*. Description: This Start the component.
*.
\*===================================================================*/

void WdgM_Start(void)
{
   /* Activate the Watch dog task */
  // (void)OS_ActivateTask(OS_Task_Wdg, OS_Task_Wdg_Offset, OS_Task_Wdg_Period);
}

/*.===================================================================*\
*. FUNCTION: WdgM_Refresh
*.=====================================================================
*. Return Value:
*.  0
*.
*. Parameters:
*.  None
*.
*. External references: Wdg_36_78K0R_FX3Trigger()
*.  External variables:
*.   None
*.  File scope variables:
*.   None
*.
*. Description: This refresh the watchdog timer
*.
\*===================================================================*/

void WdgM_Refresh(void)
{
 /* refresh the watchdog timer */
   Wdg_36_78K0R_FX3Trigger();
 
}
