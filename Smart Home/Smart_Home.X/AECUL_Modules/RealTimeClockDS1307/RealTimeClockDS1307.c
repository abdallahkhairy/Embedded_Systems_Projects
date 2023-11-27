/* 
 * File:   RealTimeClockDS1307.c
 * Author: Abdullah Khairy
 *
 * Created on November 12, 2023, 6:40 PM
 */

#include "RealTimeClockDS1307.h"

static RealTimeClockDS1307_t RealTimeClockDS1307;
static uint8_t RealTimeClockDS1307_Pack[19];

RealTimeClockDS1307_t RealTimeClockDS1307_Get_Date_time(void){
    RealTimeClockDS1307._Seconds = I2C_Read1ByteRegister(0xD0, 0x00);
    RealTimeClockDS1307._Minutes = I2C_Read1ByteRegister(0xD0, 0x01);
    RealTimeClockDS1307._Hours = I2C_Read1ByteRegister(0xD0, 0x02);
    RealTimeClockDS1307._Day = I2C_Read1ByteRegister(0xD0, 0x04);
    RealTimeClockDS1307._Month = I2C_Read1ByteRegister(0xD0, 0x05);
    RealTimeClockDS1307._Year = I2C_Read1ByteRegister(0xD0, 0x06);
    return RealTimeClockDS1307;
}

void Print_RealTimeClockDS1307(void){
    RealTimeClockDS1307_Pack[0] = ((RealTimeClockDS1307._Day>>4) + '0');
    RealTimeClockDS1307_Pack[1] = ((RealTimeClockDS1307._Day & 0x0F) + '0');
    RealTimeClockDS1307_Pack[2] = '-';
    RealTimeClockDS1307_Pack[3] = ((RealTimeClockDS1307._Month>>4) + '0');
    RealTimeClockDS1307_Pack[4] = ((RealTimeClockDS1307._Month & 0x0F) + '0');
    RealTimeClockDS1307_Pack[5] = '-';
    RealTimeClockDS1307_Pack[6] = ((RealTimeClockDS1307._Year>>4) + '0');
    RealTimeClockDS1307_Pack[7] = ((RealTimeClockDS1307._Year & 0x0F) + '0');
    RealTimeClockDS1307_Pack[8] = ' ';
    RealTimeClockDS1307_Pack[9] = ((RealTimeClockDS1307._Hours>>4) + '0');
    RealTimeClockDS1307_Pack[10] = ((RealTimeClockDS1307._Hours & 0x0F) + '0');
    RealTimeClockDS1307_Pack[11] = ':';
    RealTimeClockDS1307_Pack[12] = ((RealTimeClockDS1307._Minutes>>4) + '0');
    RealTimeClockDS1307_Pack[13] = ((RealTimeClockDS1307._Minutes & 0x0F) + '0');
    RealTimeClockDS1307_Pack[14] = ':';
    RealTimeClockDS1307_Pack[15] = ((RealTimeClockDS1307._Seconds>>4) + '0');
    RealTimeClockDS1307_Pack[16] = ((RealTimeClockDS1307._Seconds & 0x0F) + '0');
    RealTimeClockDS1307_Pack[17] = '\r';
    UARTLoggingDebugData_Send_String("Date : ");
    UARTLoggingDebugData_Send_String(RealTimeClockDS1307_Pack);
}
