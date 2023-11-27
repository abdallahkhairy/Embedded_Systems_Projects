/* 
 * File:   ecu_led.c
 * Author: Abdullah Khairy
 *
 * Created on November 28, 2020, 9:51 PM
 */

#include "ecu_led.h"

/**
 * @brief Initialize the assigned pin to be OUTPUT and turn the led OFF or ON.
 * @param led : pointer to the led module configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
Std_ReturnType led_initialize(const led_t *led){
    Std_ReturnType ret = E_OK;
    if(NULL == led){
        ret = E_NOT_OK;
    }
    else{
        
        gpio_pin_intialize(&(led->_led));
    }
    return ret;
}

/**
 * @brief Turn the led on
 * @param led : pointer to the led module configurations
 * @return  Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
Std_ReturnType led_turn_on(const led_t *led){
    Std_ReturnType ret = E_OK;
     if(NULL == led){
         ret = E_NOT_OK;
     }
     else{
         gpio_pin_write_logic((&led->_led), GPIO_HIGH);
     }
    return ret;
}

/**
 * @brief Turn the led off
 * @param led : pointer to the led module configurations
 * @return  Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
Std_ReturnType led_turn_off(const led_t *led){
    Std_ReturnType ret = E_OK;
     if(NULL == led){
         ret = E_NOT_OK;
     }
     else{

         gpio_pin_write_logic((&led->_led), GPIO_LOW);
     }
    return ret;
}

/**
 * @brief Toggle the led
 * @param led : pointer to the led module configurations
 * @return  Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
Std_ReturnType led_turn_toggle(const led_t *led){
    Std_ReturnType ret = E_OK;
     if(NULL == led){
         ret = E_NOT_OK;
     }
     else{
         gpio_pin_toggle_logic((&led->_led));
     }
    return ret;
}
