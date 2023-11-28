/* 
 * File:   RealTimeClockDS1307.c
 * Author: Abdullah Khairy
 *
 * Created on November 12, 2023, 6:40 PM
 */

#include "RealTimeClockDS1307.h"

static RealTimeClockDS1307_t RealTimeClockDS1307;
static uint8_t RealTimeClockDS1307_Pack[19];

RealTimeClockDS1307_t RealTimeClockDS1307_Get_Date_time(const mssp_i2c_t *i2c_obj, uint8 slave_add, uint8 *slave_ack){
    Std_ReturnType ret = E_OK;
    ret  = MSSP_I2C_EXT_Device_Read_1_Byte(&i2c_obj, slave_add, 0x00, &(RealTimeClockDS1307._Seconds), &slave_ack);
    ret  = MSSP_I2C_EXT_Device_Read_1_Byte(&i2c_obj, slave_add, 0x01, &(RealTimeClockDS1307._Minutes), &slave_ack);
    ret  = MSSP_I2C_EXT_Device_Read_1_Byte(&i2c_obj, slave_add, 0x02, &(RealTimeClockDS1307._Hours), &slave_ack);
    ret  = MSSP_I2C_EXT_Device_Read_1_Byte(&i2c_obj, slave_add, 0x04, &(RealTimeClockDS1307._Day), &slave_ack);
    ret  = MSSP_I2C_EXT_Device_Read_1_Byte(&i2c_obj, slave_add, 0x05, &(RealTimeClockDS1307._Month), &slave_ack);
    ret  = MSSP_I2C_EXT_Device_Read_1_Byte(&i2c_obj, slave_add, 0x06, &(RealTimeClockDS1307._Year), &slave_ack);
    return RealTimeClockDS1307;
}

void Print_RealTimeClockDS1307(RealTimeClockDS1307_t RTC){
    RealTimeClockDS1307_Pack[0] = ((RTC._Day>>4) + '0');
    RealTimeClockDS1307_Pack[1] = ((RTC._Day & 0x0F) + '0');
    RealTimeClockDS1307_Pack[2] = '-';
    RealTimeClockDS1307_Pack[3] = ((RTC._Month>>4) + '0');
    RealTimeClockDS1307_Pack[4] = ((RTC._Month & 0x0F) + '0');
    RealTimeClockDS1307_Pack[5] = '-';
    RealTimeClockDS1307_Pack[6] = ((RTC._Year>>4) + '0');
    RealTimeClockDS1307_Pack[7] = ((RTC._Year & 0x0F) + '0');
    RealTimeClockDS1307_Pack[8] = ' ';
    RealTimeClockDS1307_Pack[9] = ((RTC._Hours>>4) + '0');
    RealTimeClockDS1307_Pack[10] = ((RTC._Hours & 0x0F) + '0');
    RealTimeClockDS1307_Pack[11] = ':';
    RealTimeClockDS1307_Pack[12] = ((RTC._Minutes>>4) + '0');
    RealTimeClockDS1307_Pack[13] = ((RTC._Minutes & 0x0F) + '0');
    RealTimeClockDS1307_Pack[14] = ':';
    RealTimeClockDS1307_Pack[15] = ((RTC._Seconds>>4) + '0');
    RealTimeClockDS1307_Pack[16] = ((RTC._Seconds & 0x0F) + '0');
    RealTimeClockDS1307_Pack[17] = '\r';
    EUSART_ASYNC_WriteStringNonBlocking("Date : ");
    EUSART_ASYNC_WriteStringNonBlocking(RealTimeClockDS1307_Pack);
}
