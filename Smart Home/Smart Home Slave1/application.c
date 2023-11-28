/* 
 * File:   application.c
 * Author: Abdullah Khairy
 *
 */

#include "application.h"

void lcd_write(void);
void MSSP_I2C_DefaultInterruptHandler(void);

mssp_i2c_t i2c_obj = {
    .i2c_cfg.i2c_mode = I2C_MSSP_SLAVE_MODE,
    .i2c_cfg.i2c_slave_address = 0x10,
    .i2c_cfg.i2c_general_call = I2C_GENERAL_CALL_DISABLE,
    .i2c_cfg.i2c_mode_cfg = I2C_SLAVE_MODE_7BIT_ADDRESS,
    .i2c_cfg.i2c_SMBus_control = I2C_SMBus_DISABLE,
    .i2c_cfg.i2c_slew_rate = I2C_SLEW_RATE_DISABLE,
    .i2c_cfg.i2c_general_call = I2C_GENERAL_CALL_DISABLE,
    .I2C_DefaultInterruptHandler = MSSP_I2C_DefaultInterruptHandler,
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
uint8 slave1_rec_data = ZERO_INIT;
uint32 eeprom_1_byte = ZERO_INIT;
uint32 eeprom_2_byte = ZERO_INIT;

int main() { 
    Std_ReturnType ret  = E_NOT_OK;
    application_initialize();


    while(1){
        if(slave1_rec_data > 35){
            ret = dc_motor_move_right(&dc_motor_1);
        }else{
            ret = dc_motor_stop(&dc_motor_1);
        }
    }
    return (EXIT_SUCCESS);
}

void application_initialize(void){
    Std_ReturnType ret = E_NOT_OK;
    ecu_layer_init();
    ret = MSSP_I2C_Init(&i2c_obj);
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

void MSSP_I2C_DefaultInterruptHandler(void){
    /* Holds clock low (clock stretch) */
    I2C_CLOCK_STRETCH_ENABLE();
    if((SSPSTATbits.R_nW == 0) && (SSPSTATbits.D_nA == 0)){ /* Master Will Write Data, So i need to read it */
        uint8 dummy_buffer = SSPBUF; /* Read The Last Byte To Clear The Buffer */
        while(!SSPSTATbits.BF);
        slave1_rec_data = SSPBUF; /* read data */
    }
    else if(SSPSTATbits.R_nW == 1){ /* Master needs to read Data, So i need to write it */
        
    }
    else { /* Nothing */ }
    /* Releases clock */
    I2C_CLOCK_STRETCH_DISABLE();
}

