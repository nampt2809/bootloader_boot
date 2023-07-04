//--thanhcm3--12--06--23--


#include "header_files.h"

///1. timer_init================================================================

uint8_t init_timer(FTM_Type *base,IRQn_Type interrupt,uint32_t timer_period_ms){
  uint8_t  err = NO_ERR;
  ftm_config_t ftmInfo;
  
  /* Fill in the FTM config struct with the default settings */
  FTM_GetDefaultConfig(&ftmInfo);
  
  /* Calculate the clock division based on the timer period frequency to be obtained */
  ftmInfo.prescale =
    FTM_CalculateCounterClkDiv(base, 1000000U / (timer_period_ms*1000), FTM_SOURCE_CLOCK);
  ;
  //ftmInfo.faultMode =  kFTM_Fault_AllChnlsAuto;
  /* Initialize FTM module */
  FTM_Init(base, &ftmInfo);
  
  /* Set timer period */
  FTM_SetTimerPeriod(base,
                     USEC_TO_COUNT(timer_period_ms*1000, FTM_SOURCE_CLOCK / (1U << ftmInfo.prescale)));
  
  FTM_EnableInterrupts(base, kFTM_TimeOverflowInterruptEnable);
  
  EnableIRQ(interrupt);
  
  FTM_StartTimer(base, kFTM_SystemClock);
  
  return err;
}


///2 .
void USER_FTM2_HANDLER(void)
{
    /* Clear interrupt flag.*/
    FTM_ClearStatusFlags(USER_FTM2_BASEADDR, kFTM_TimeOverflowFlag);
    //code here;
    //ftm_isr_flag = true;
    //__DSB();
}