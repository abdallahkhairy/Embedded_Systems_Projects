/* 
 * File:   UARTLoggingDebugData.c
 * Author: Abdullah Khairy
 *
 * Created on November 12, 2023, 8:09 PM
 */

#include "UARTLoggingDebugData.h"

void UARTLoggingDebugData_Send_String(uint8_t *_str){
    while(*_str != '\0'){
        EUSART_Write(*_str++);
    }
}