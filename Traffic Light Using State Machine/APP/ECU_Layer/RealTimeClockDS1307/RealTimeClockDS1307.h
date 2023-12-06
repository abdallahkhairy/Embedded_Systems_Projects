/* 
 * File:   RealTimeClockDS1307.h
 * Author: Abdullah Khairy
 *
 * Created on November 12, 2023, 6:39 PM
 */

#ifndef REALTIMECLOCKDS1307_H
#define	REALTIMECLOCKDS1307_H

/* ----------------------------- Section: Includes ----------------------------- */
#include "pic18f4620.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "../../MCAL_Layer/I2C/hal_i2c.h"

/* ----------------------------- Section: Macro Declarations ----------------------------- */

/* ----------------------------- Section: Macro Functions Declarations ----------------------------- */

/* ----------------------------- Section: Data Types Declarations ----------------------------- */
typedef struct{
    uint8_t _Hours;
    uint8_t _Minutes;
    uint8_t _Seconds;
    uint8_t _Year;
    uint8_t _Month;
    uint8_t _Day;
}RealTimeClockDS1307_t;
/* ----------------------------- Section: Functions Declarations ----------------------------- */
RealTimeClockDS1307_t RealTimeClockDS1307_Get_Date_time(const mssp_i2c_t *i2c_obj, uint8 slave_add, uint8 *slave_ack);
void Print_RealTimeClockDS1307(RealTimeClockDS1307_t RTC);

#endif	/* REALTIMECLOCKDS1307_H */

