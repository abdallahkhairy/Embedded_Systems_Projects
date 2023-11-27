/* 
 * File:   TempSensor_TC74.h
 * Author: Abdullah Khairy
 *
 * Created on November 12, 2023, 10:37 PM
 */

#ifndef TEMPSENSOR_TC74_H
#define	TEMPSENSOR_TC74_H

/* ----------------------------- Section: Includes ----------------------------- */
#include "../../mcc_generated_files/examples/i2c_master_example.h"

/* ----------------------------- Section: Macro Declarations ----------------------------- */

/* ----------------------------- Section: Macro Functions Declarations ----------------------------- */

/* ----------------------------- Section: Data Types Declarations ----------------------------- */

/* ----------------------------- Section: Functions Declarations ----------------------------- */
uint8_t TempSensor_TC74_Read_Temp(i2c_address_t TC74_Address);

#endif	/* TEMPSENSOR_TC74_H */

