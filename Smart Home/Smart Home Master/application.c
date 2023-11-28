/* 
 * File:   application.c
 * Author: Abdullah Khairy
 *
 */

#include "application.h"

void lcd_write(void);


mssp_i2c_t i2c_obj = {
    .i2c_clock = 100000,
    .i2c_cfg.i2c_mode = I2C_MSSP_MASTER_MODE,
    .i2c_cfg.i2c_mode_cfg = I2C_MASTER_MODE_DEFINED_CLOCK,
    .i2c_cfg.i2c_SMBus_control = I2C_SMBus_DISABLE,
    .i2c_cfg.i2c_slew_rate = I2C_SLEW_RATE_DISABLE,
    .I2C_DefaultInterruptHandler = NULL,
    .I2C_Report_Receive_Overflow = NULL,
    .I2C_Report_Write_Collision = NULL
};

usart_t usart_obj = {
    .baudrate = 9600,
    .baudrate_gen_gonfig = BAUDRATE_ASYN_8BIT_lOW_SPEED,
    
    .usart_tx_cfg.usart_tx_enable = EUSART_ASYNCHRONOUS_TX_ENABLE,
    .usart_tx_cfg.usart_tx_interrupt_enable = EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE,
    .usart_tx_cfg.usart_tx_9bit_enable = EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE,

    .usart_rx_cfg.usart_rx_enable = EUSART_ASYNCHRONOUS_RX_ENABLE,
    .usart_rx_cfg.usart_rx_interrupt_enable = EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE,
    .usart_rx_cfg.usart_rx_9bit_enable = EUSART_ASYNCHRONOUS_9Bit_RX_DISABLE,
    
    .EUSART_TxDefaultInterruptHandler = NULL,
    .EUSART_RxDefaultInterruptHandler = NULL,
    .EUSART_FramingErrorHandler = NULL,
    .EUSART_OverrunErrorHandler = NULL
            

};

RealTimeClockDS1307_t RealTimeClockDS1307;
uint8 slave_ack = ZERO_INIT;
uint8 keypad_value = ZERO_INIT;
uint8 temp_value = ZERO_INIT;
uint32 eeprom_1_byte = ZERO_INIT;
uint32 eeprom_2_byte = ZERO_INIT;


void MSSP_I2C_Send_1_Byte(uint8 slave_add, uint8 _data){
    Std_ReturnType ret = E_NOT_OK;
    ret = MSSP_I2C_Master_Send_Start(&i2c_obj);
    ret = MSSP_I2C_Master_Write_Blocking(&i2c_obj, slave_add, &slave_ack);
    ret = MSSP_I2C_Master_Write_Blocking(&i2c_obj, _data, &slave_ack);
    ret = MSSP_I2C_Master_Send_Stop(&i2c_obj);
}

int main() { 
    Std_ReturnType ret  = E_NOT_OK;
    application_initialize();

    ret = MSSP_I2C_EXT_Device_Write_1_Byte(&i2c_obj, 0xA2, 0x08, 5, &slave_ack);
    ret = MSSP_I2C_EXT_Device_Write_1_Byte(&i2c_obj, 0xA6, 0x08, 6, &slave_ack);
    ret = MSSP_I2C_EXT_Device_Read_1_Byte(&i2c_obj, 0xA2, 0x08, &eeprom_1_byte, &slave_ack);
    ret = MSSP_I2C_EXT_Device_Read_1_Byte(&i2c_obj, 0xA6, 0x08, &eeprom_2_byte, &slave_ack);
    while(1){
        RealTimeClockDS1307 = RealTimeClockDS1307_Get_Date_time(&i2c_obj, 0xD0, &slave_ack);
        Print_RealTimeClockDS1307(RealTimeClockDS1307);
        temp_value = MSSP_I2C_EXT_Device_Read_1_Byte(&i2c_obj, 0x9E, 0x00, &temp_value, &slave_ack);
        MSSP_I2C_Send_1_Byte(0x10, temp_value);
    }
    return (EXIT_SUCCESS);
}

void application_initialize(void){
    Std_ReturnType ret = E_NOT_OK;
    ecu_layer_init();
    ret = MSSP_I2C_Init(&i2c_obj);
    ret = EUSART_ASYNC_Init(&usart_obj);
}



void lcd_write(void){
    Std_ReturnType ret  = E_NOT_OK;
    uint8 not_pressed = '\0';
    if(not_pressed != keypad_value){
        ret = lcd_4bit_send_char_data(&lcd_1, keypad_value);
        keypad_value = not_pressed;
        __delay_ms(500);
    }else{ /* Nothing */}
}

