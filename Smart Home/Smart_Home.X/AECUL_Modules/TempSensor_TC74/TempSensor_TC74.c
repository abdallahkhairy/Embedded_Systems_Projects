/* 
 * File:   TempSensor_TC74.c
 * Author: Abdullah Khairy
 *
 * Created on November 12, 2023, 10:38 PM
 */

#include "TempSensor_TC74.h"

uint8_t TempSensor_TC74_Read_Temp(i2c_address_t TC74_Address){
    return I2C_Read1ByteRegister(TC74_Address, 0x00);
}
