#include "type.h"
#include "PLAN_MEMOIRE.h"
#include "Init_TSS.h"


void Charge_Segment_Code(void* P_Code)
{
    Copier_Memoire((BYTE*)BASE_CODE_USER, (BYTE*)P_Code, 1000);
    
}
//------------------------------------------------------------------------------
