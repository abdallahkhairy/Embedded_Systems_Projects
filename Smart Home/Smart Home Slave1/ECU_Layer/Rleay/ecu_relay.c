/* 
 * File:   ecu_relay.c
 * Author: Abdullah Khairy
 *
 * Created on January 7, 2023, 10:22 PM
 */

#include "ecu_relay.h"

/**
 * @brief Initialize the assigned pin to be OUTPUT and turn the relay OFF or ON.
 * @param _relay pointer to the relay module configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
Std_ReturnType relay_initialize(const relay_t *_relay){
    Std_ReturnType ret = E_OK;
    if(NULL == _relay){
        ret = E_NOT_OK;
    }
    else{
        gpio_pin_intialize(&(_relay->relay_pin));
    }
    return ret;
}

/**
 * @brief Turn the relay on
 * @param _relay pointer to the relay module configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
Std_ReturnType relay_turn_on(const relay_t *_relay){
    Std_ReturnType ret = E_OK;
    if(NULL == _relay){
        ret = E_NOT_OK;
    }
    else{
        gpio_pin_write_logic(&(_relay->relay_pin) , GPIO_HIGH);
    }
    return ret;
}

/**
 * @brief Turn the relay off
 * @param _relay pointer to the relay module configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
Std_ReturnType relay_turn_off(const relay_t *_relay){
    Std_ReturnType ret = E_OK;
    if(NULL == _relay){
        ret = E_NOT_OK;
    }
    else{
        gpio_pin_write_logic(&(_relay->relay_pin) , GPIO_LOW);
    }
    return ret;
}
