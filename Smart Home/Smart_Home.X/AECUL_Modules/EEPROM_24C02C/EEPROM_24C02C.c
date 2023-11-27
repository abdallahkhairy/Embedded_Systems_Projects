/* 
 * File:   EEPROM_24C02C.c
 * Author: Abdullah Khairy
 *
 * Created on November 12, 2023, 9:50 PM
 */

#include "EEPROM_24C02C.h"

void EEPROM_24C02C_Write_Byte(i2c_address_t EEPROM_Address, i2c_address_t Byte_Address, uint8_t data){
    I2C_Write1ByteRegister(EEPROM_Address, Byte_Address, data);
}
uint8_t EEPROM_24C02C_Read_Byte(i2c_address_t EEPROM_Address, i2c_address_t Byte_Address){
    return I2C_Read1ByteRegister(EEPROM_Address, Byte_Address); 
}