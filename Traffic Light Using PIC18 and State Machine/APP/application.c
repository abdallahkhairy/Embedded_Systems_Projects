/*
 * File:   application.c
 * Author: Abdullah Khairy
 *
 * Created on August 24, 2023, 10:38 PM
 */

#include "application.h"
#define WAITING_TIME    20
#define READY_TIME      5
#define TIME_FINISHED   0

//Different state of Traffic Light 
typedef enum{
    CARS_MOVE_PEDESTRIANS_WAIT_STATE = 0,
    PEDESTRIAN_MOVE_CARS_WAIT_STATE,
    CARS_READY_TO_MOVE_PEDESTRIANS_STOP_STATE,
    PEDESTRIANS_READY_TO_MOVE_CARS_STOP_STATE
}traffic_light_state_t;

//Different type events
typedef enum{
    TIME_OF_CARS_MOVE_FINISHED_EVENT = 0,
    TIME_OF_PEDESTRAINS_MOVE_FINISHED_EVENT,
    READY_TIME_OF_CARS_TO_MOVE_FINISHED_EVENT,
    READY_TIME_OF_PEDESTRIANS_TO_MOVE_FINISHED_EVENT
}traffic_light_event_t;
//Prototype of eventhandlers
traffic_light_state_t TimeOfCarsMoveFinishedHandler(void);
traffic_light_state_t TimeOfPedestriansMoveFinishedHandler(void);
traffic_light_state_t ReadyTimeOfCarsToMoveFinishedHandler(void);
traffic_light_state_t ReadyTimeOfPedestriansToMoveFinishedHandler(void);


void TMR0_DefualtInterruptHandler(void);
void Int0_APP_ISR(void);

timer0_t timer0 = {
    .TMR0_InterruptHandler = TMR0_DefualtInterruptHandler,
    .prescaler_enable = TIMER0_PRESCALER_ENABLE_CFG,
    //.prescaler_value = TIMER0_PRESCALER_DIV_BY_32, // for 1 sec timing
    .prescaler_value = TIMER0_PRESCALER_DIV_BY_16,  // 300 ms to quick debugging
    .timer0_counter_edge = TIMER0_COUNTER_RISING_EDGE_CFG,
    .timer0_mode = TIMER0_TIMER_MODE,
    //.timer0_preload_value = 3036, // for 1 sec timing
    .timer0_preload_value = 28036, // 300 ms to quick debugging
    .timer0_register_size = TIMER0_16BIT_REGISTER_MODE,
};

interrupt_INTx_t int0_obj = {.EXT_InterruptHandler = Int0_APP_ISR,
                             .edge = INTERRUPT_RISING_EDGE,
                             .priority = INTERRUPT_HIGH_PRIORITY,
                             .source = INTERRUPT_EXTERNAL_INT0,
                             .mcu_pin.port = PORTB_INDEX,
                             .mcu_pin.pin = GPIO_PIN0,
                             .mcu_pin.direction = GPIO_DIRECTION_INPUT};

traffic_light_event_t traffic_light_event ;
traffic_light_event_t next_traffic_light_event ;
uint8 seven_seg_cnt = 0;
Std_ReturnType ret = E_NOT_OK;
traffic_light_state_t  traffic_light_state;
traffic_light_state_t  next_state;
int main() {
  application_initialize();
  /*
     initial state is car moving and function used here instead of enum value
   * to reduce code size only
   * traffic_light_event = READY_TIME_OF_CARS_TO_MOVE_FINISHED_EVENT to start
   * at cars move state
   * 
   */
  traffic_light_state = CARS_READY_TO_MOVE_PEDESTRIANS_STOP_STATE; // first state is assumed cars to move
  traffic_light_event = READY_TIME_OF_CARS_TO_MOVE_FINISHED_EVENT;
  next_traffic_light_event = traffic_light_event;
  while (1) {
    ret = seven_segement_write_number(&seg1, seven_seg_cnt / 10);
    ret = seven_segement_write_number(&seg2, seven_seg_cnt % 10);
    switch(traffic_light_state){
        case CARS_MOVE_PEDESTRIANS_WAIT_STATE:
            if(TIME_OF_CARS_MOVE_FINISHED_EVENT == traffic_light_event){
                traffic_light_state = TimeOfCarsMoveFinishedHandler();
            }
        break;
        case PEDESTRIAN_MOVE_CARS_WAIT_STATE:
            if(TIME_OF_PEDESTRAINS_MOVE_FINISHED_EVENT == traffic_light_event){
                traffic_light_state = TimeOfPedestriansMoveFinishedHandler();
            }
        break;
        case CARS_READY_TO_MOVE_PEDESTRIANS_STOP_STATE:
            if(READY_TIME_OF_CARS_TO_MOVE_FINISHED_EVENT == traffic_light_event){
                traffic_light_state = ReadyTimeOfCarsToMoveFinishedHandler();
            }
        break;
        case PEDESTRIANS_READY_TO_MOVE_CARS_STOP_STATE:
            if(READY_TIME_OF_PEDESTRIANS_TO_MOVE_FINISHED_EVENT == traffic_light_event){
                traffic_light_state = ReadyTimeOfPedestriansToMoveFinishedHandler();
            }
        break;
        default:
            break;
        }
  }

  return (EXIT_SUCCESS);
}

void application_initialize(void) {
  Std_ReturnType ret = E_NOT_OK;
  ecu_layer_init();
  ret = Timer0_Init(&timer0);
  ret = Interrupt_INTx_Init(&int0_obj);
}

void TMR0_DefualtInterruptHandler(void) {
  if(TIME_FINISHED == seven_seg_cnt){
    /* if to handle start conditions not to clear lcd on start after screen first state */
    if(traffic_light_event != next_traffic_light_event){ 
        ret = lcd_4bit_clear(&lcd_1);
        traffic_light_event = next_traffic_light_event;
    }else{/* Nothing */}
    switch(traffic_light_event){
          case TIME_OF_CARS_MOVE_FINISHED_EVENT:
            seven_seg_cnt = READY_TIME;
            next_traffic_light_event = READY_TIME_OF_PEDESTRIANS_TO_MOVE_FINISHED_EVENT;
          break;
          case TIME_OF_PEDESTRAINS_MOVE_FINISHED_EVENT:
            seven_seg_cnt = READY_TIME;
            next_traffic_light_event = READY_TIME_OF_CARS_TO_MOVE_FINISHED_EVENT;
          break;
          case READY_TIME_OF_CARS_TO_MOVE_FINISHED_EVENT:
            seven_seg_cnt = WAITING_TIME;
            next_traffic_light_event = TIME_OF_CARS_MOVE_FINISHED_EVENT;
          break;
          case READY_TIME_OF_PEDESTRIANS_TO_MOVE_FINISHED_EVENT:
            seven_seg_cnt = WAITING_TIME;
            next_traffic_light_event = TIME_OF_PEDESTRAINS_MOVE_FINISHED_EVENT;
          break;
          default:
              break;
          }
    }
  else{ /* NoThing */}
  seven_seg_cnt--;
}

void Int0_APP_ISR(void) {
    if(traffic_light_state != PEDESTRIANS_READY_TO_MOVE_CARS_STOP_STATE){
        ret = led_turn_off(&led_green_car);
        ret = led_turn_off(&led_red_people);
        seven_seg_cnt = 0;
        ret = lcd_4bit_clear(&lcd_1);
        traffic_light_state = PEDESTRIANS_READY_TO_MOVE_CARS_STOP_STATE; 
        traffic_light_event = READY_TIME_OF_PEDESTRIANS_TO_MOVE_FINISHED_EVENT;
        next_traffic_light_event = traffic_light_event;
    }
}
traffic_light_state_t TimeOfCarsMoveFinishedHandler(void){
    ret = led_turn_on(&ready_yellow);
    ret = led_turn_off(&led_green_car);
    ret = led_turn_off(&led_red_people);
    ret = lcd_4bit_send_string_pos(&lcd_1, 1, 1,"Pedestrians be Ready ");
    ret = lcd_4bit_send_string_pos(&lcd_1, 2, 1,"To MOVE =>=>");
    ret = lcd_4bit_send_string_pos(&lcd_1, 3, 1,"Cars be ");
    ret = lcd_4bit_send_string_pos(&lcd_1, 4, 1,"Ready to STOP!!");
    return PEDESTRIANS_READY_TO_MOVE_CARS_STOP_STATE;
}
traffic_light_state_t TimeOfPedestriansMoveFinishedHandler(void){
    
    ret = led_turn_on(&ready_yellow);
    ret = led_turn_off(&led_green_people);
    ret = led_turn_off(&led_red_car);
    ret = lcd_4bit_send_string_pos(&lcd_1, 1, 1,"Cars be Ready ");
    ret = lcd_4bit_send_string_pos(&lcd_1, 2, 1,"To [ MOVE ] =>=>");
    ret = lcd_4bit_send_string_pos(&lcd_1, 3, 1,"Pedestrians be ");
    ret = lcd_4bit_send_string_pos(&lcd_1, 4, 1,"Ready to STOP!!");
    return CARS_READY_TO_MOVE_PEDESTRIANS_STOP_STATE;
}
traffic_light_state_t ReadyTimeOfCarsToMoveFinishedHandler(void){
    ret = led_turn_on(&led_green_car);
    ret = led_turn_on(&led_red_people);
    ret = led_turn_off(&ready_yellow);
    ret = lcd_4bit_send_string_pos(&lcd_1, 2, 1,"Cars MOVE =>=>");
    ret = lcd_4bit_send_string_pos(&lcd_1, 3, 1,"Pedestrians STOP!! ");
    return CARS_MOVE_PEDESTRIANS_WAIT_STATE;
}
traffic_light_state_t ReadyTimeOfPedestriansToMoveFinishedHandler(void){
    ret = led_turn_on(&led_green_people);
    ret = led_turn_on(&led_red_car);
    ret = led_turn_off(&ready_yellow);
    ret = lcd_4bit_send_string_pos(&lcd_1, 2, 1,"Pedestrian MOVE =>=>");
    ret = lcd_4bit_send_string_pos(&lcd_1, 3, 1,"Cars STOP!! ");
    return PEDESTRIAN_MOVE_CARS_WAIT_STATE;
}