/* 
 * File:   EEPROM_24C02C.h
 * Author: Abdullah Khairy
 *
 * Created on November 12, 2023, 9:49 PM
 */

#ifndef EEPROM_24C02C_H
#define	EEPROM_24C02C_H

/* ----------------------------- Section: Includes ----------------------------- */
#include "../../mcc_generated_files/examples/i2c_master_example.h"

/* ----------------------------- Section: Macro Declarations ----------------------------- */

/* ----------------------------- Section: Macro Functions Declarations ----------------------------- */

/* ----------------------------- Section: Data Types Declarations ----------------------------- */

/* ----------------------------- Section: Functions Declarations ----------------------------- */

void EEPROM_24C02C_Write_Byte(i2c_address_t EEPROM_Address, i2c_address_t Byte_Address, uint8_t data);
uint8_t EEPROM_24C02C_Read_Byte(i2c_address_t EEPROM_Address, i2c_address_t Byte_Address);
#endif	/* EEPROM_24C02C_H */

