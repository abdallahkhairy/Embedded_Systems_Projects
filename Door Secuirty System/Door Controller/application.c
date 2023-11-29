/* 
 * File:   application.c
 * Author: Abdullah Khairy
 *
 */

#include "application.h"

uint8 check_password_ctrl(void);

void EUSART_RxDefaultInterruptHandler (void);
void Timer0_DefaultInterruptHandler(void);
void unlock_door(void);

usart_t usart_obj ={
    .baudrate = 9600,
    .baudrate_gen_gonfig = BAUDRATE_ASYN_8BIT_lOW_SPEED,   
    .usart_tx_cfg.usart_tx_enable = EUSART_ASYNCHRONOUS_TX_ENABLE,
    .usart_tx_cfg.usart_tx_interrupt_enable = EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE,
    .usart_tx_cfg.usart_tx_9bit_enable = EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE,
    .usart_rx_cfg.usart_rx_enable = EUSART_ASYNCHRONOUS_RX_ENABLE,
    .usart_rx_cfg.usart_rx_interrupt_enable = EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE,
    .usart_rx_cfg.usart_rx_9bit_enable = EUSART_ASYNCHRONOUS_9Bit_RX_DISABLE,
    .EUSART_TxDefaultInterruptHandler = NULL,
    .EUSART_RxDefaultInterruptHandler = EUSART_RxDefaultInterruptHandler,
    .EUSART_FramingErrorHandler = NULL,
    .EUSART_OverrunErrorHandler = NULL
};

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

timer0_t timer_obj = {
    .TMR0_InterruptHandler = Timer0_DefaultInterruptHandler,
    .priority = INTERRUPT_LOW_PRIORITY,
    .timer0_mode = TIMER0_TIMER_MODE,
    .prescaler_enable = TIMER0_PRESCALER_ENABLE_CFG,
    .prescaler_value = TIMER0_PRESCALER_DIV_BY_32,
    .timer0_preload_value = 3036, // 1 sec
    .timer0_register_size =TIMER0_16BIT_REGISTER_MODE
            
};

pin_config_t buzzer = {
    .port = PORTC_INDEX,
    .pin = GPIO_PIN2,
    .direction = GPIO_DIRECTION_OUTPUT,
    .logic = GPIO_LOW
};

uint8 slave_ack = ZERO_INIT;
uint8 keypad_value = ZERO_INIT;
uint8 uart_choice = ZERO_INIT;
uint32 eeprom_value1 = ZERO_INIT;
uint8 rec_counter = ZERO_INIT;
uint8 rec_falg = ZERO_INIT;
uint8 timer0_falg = ZERO_INIT;
uint8 timer0_falg_deinit = ZERO_INIT;
uint8 open_door_falg = ZERO_INIT;
uint8 close_door__falg = ZERO_INIT;
uint8 action = ZERO_INIT;
uint8 user_received_password[6];

/* For Setting Default Password  */
//uint8 default_password[6] ="123456";
uint8 saved_password[6];
uint8 ret_password[6];
uint8 no_of_tries = 0; 

int main() { 
    Std_ReturnType ret  = E_NOT_OK;
    application_initialize();
    /* For Setting Default Password */
//    for (uint8 i = 0; i < 6; i++) {
//       ret = MSSP_I2C_EXT_Device_Write_1_Byte(&i2c_obj, 0xA2, 0x00+i, default_password[i], &slave_ack);
//    }

    for (uint8 i = 0; i < 6; i++) {
        ret = MSSP_I2C_EXT_Device_Read_1_Byte(&i2c_obj, 0xA2, 0x00+i, &ret_password[i], &slave_ack);
    }

    while(1){
        switch(action){
            case 1:
                if(1 == check_password_ctrl()){
                    unlock_door();
                    EUSART_ASYNC_WriteByteNonBlocking('Y');
                    no_of_tries = 0;
                    gpio_pin_write_logic(&buzzer, GPIO_LOW);
                }
                else {
                    no_of_tries++;
                    EUSART_ASYNC_WriteByteNonBlocking('N');
                    if(3 == no_of_tries){
                        gpio_pin_write_logic(&buzzer, GPIO_HIGH);
                    }else{/* Nothing */}
                }
                action =0;  
            break;
            case 2:
                if(1 == check_password_ctrl()){
                    no_of_tries =0;
                    EUSART_ASYNC_WriteByteNonBlocking('K');
                    no_of_tries = 0;
                    gpio_pin_write_logic(&buzzer, GPIO_LOW);
                }
                else {
                    no_of_tries++;
                    EUSART_ASYNC_WriteByteNonBlocking('N');
                    if(3 == no_of_tries){
                        gpio_pin_write_logic(&buzzer, GPIO_HIGH);
                    }else{/* Nothing */}
                }
                action =0;  
            break;
            case 3:
                for (uint8 i = 0; i < 6; i++) {
                    ret = MSSP_I2C_EXT_Device_Write_1_Byte(&i2c_obj, 0xA2, 0x00+i, user_received_password[i], &slave_ack);
                }

                for (uint8 i = 0; i < 6; i++) {
                    ret = MSSP_I2C_EXT_Device_Read_1_Byte(&i2c_obj, 0xA2, 0x00+i, &ret_password[i], &slave_ack);
                }
                action =0;  
            break;
            default:;
        }
    }
    return (EXIT_SUCCESS);
}

void application_initialize(void){
    Std_ReturnType ret = E_NOT_OK;
    ecu_layer_init();
    ret = EUSART_ASYNC_Init(&usart_obj);
    ret = MSSP_I2C_Init(&i2c_obj);
    ret = Timer0_Init(&timer_obj);
    ret = gpio_pin_intialize(&buzzer);
    TIMER0_MODULE_DISABLE();
}

/**
 * Compare Two Passwords
 * @return 
 */
uint8 check_password_ctrl(void){
    for (uint8 i = 0; i < 6; i++) {
        if( user_received_password[i] != ret_password[i]){
            return 0;
        }
    }
    return 1;
}

/**
 * Open the door by Motor rotate right
 * wait 3 seconds till full open
 * wait 7 seconds in full open state
 * rotate motor left   
 * wait 3 seconds till full close
 */
void unlock_door(void){
    dc_motor_move_right(&dc_motor_1);
    TIMER0_MODULE_ENABLE();
    timer0_falg =0;
    timer0_falg_deinit = 0;
}

void EUSART_RxDefaultInterruptHandler (void){
    Std_ReturnType ret = E_NOT_OK;
    ret = EUSART_ASYNC_ReadByteNonBlocking(&uart_choice);
    if( 'e' == uart_choice){
        rec_falg = 1;
    }else if('c' == uart_choice){
        rec_falg = 2;
    }
    else if('s' == uart_choice){
        rec_falg = 3;
    }
    else{ /* to be .. */}
    if( 1 == rec_falg){
        if('e' != uart_choice){
            user_received_password[rec_counter++] = uart_choice;
        }else{ /* Nothing */}
        if(6 == rec_counter){
            rec_counter =0;
            action = rec_falg;
        }else{ /* Nothing */}
    }else if(2 == rec_falg){
        if('c' != uart_choice){
            user_received_password[rec_counter++] = uart_choice;
        }else{ /* Nothing */}
        if(6 == rec_counter){
            rec_counter =0;
            action = rec_falg;
        }else{ /* Nothing */}
    }else if(3 == rec_falg){
        if('s' != uart_choice){
            user_received_password[rec_counter++] = uart_choice;
        }else{ /* Nothing */}
        if(6 == rec_counter){
            rec_counter =0;
            action = rec_falg;
        }else{ /* Nothing */}
    }else{ /* Nothing*/}
}

void Timer0_DefaultInterruptHandler(void){
    timer0_falg++;
    if(10 == timer0_falg){
        dc_motor_move_left(&dc_motor_1);
        timer0_falg=0;
        timer0_falg_deinit = 1;
    }
    else if (3 == timer0_falg){
        dc_motor_stop(&dc_motor_1);
        if(1 == timer0_falg_deinit){
            TIMER0_MODULE_DISABLE();
        }else{ /* Nothing */}
    }else{ /* Nothing */}
}

