/* 
 * File:   RealTimeClockDS1307.h
 * Author: Abdullah Khairy
 *
 * Created on November 12, 2023, 6:39 PM
 */

#ifndef REALTIMECLOCKDS1307_H
#define	REALTIMECLOCKDS1307_H

/* ----------------------------- Section: Includes ----------------------------- */
#include "../../mcc_generated_files/mcc.h"
#include "../../mcc_generated_files/examples/i2c_master_example.h"
#include "../../AECUL_Modules/UARTLoggingDebugData/UARTLoggingDebugData.h"
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
RealTimeClockDS1307_t RealTimeClockDS1307_Get_Date_time(void);
void Print_RealTimeClockDS1307(void);

#endif	/* REALTIMECLOCKDS1307_H */

