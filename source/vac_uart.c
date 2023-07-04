//--thanhcm3--12--06--23--

#include "header_files.h"
uint8_t buf_test[100];
uint8_t buff_cnt =0;

void USER_UART2_IRQHandler(void)
{
    uint8_t data;

    /* If new data arrived. */
    if ((kUART_RxDataRegFullFlag | kUART_RxOverrunFlag) & UART_GetStatusFlags(USER_UART2))
    {
        data = UART_ReadByte(USER_UART2);
        
        buf_test[buff_cnt++] = data;

    }
    SDK_ISR_EXIT_BARRIER;
}