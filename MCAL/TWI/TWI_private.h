/********************************************************************************/
/********************************************************************************/
/*****************       Aathur:Shehab Ahmed Ragaai          ********************/
/*****************       Layer:MCAL                          ********************/
/*****************       SWC:TWI                             ********************/
/*****************       version:1.00                        ********************/
/********************************************************************************/
/********************************************************************************/

#ifndef TWI_PRIVATE_H_
#define TWI_PRIVATE_H_

#define  START_ACK_STATUE                   0X08
#define  MASTER_SLA_W_ACK_STATUE            0X18
#define  Repeat_START_ACK_STATUE            0x10
#define  MASTER_SLA_R_ACK_STATUE            0X40
#define  MASTER_SEND_DATA_ACK_STATUE        0X28
#define  Receive_DATA_ACK_STATUE            0X50
#define  SLAVE_SLA_W_ACK_STATUE             0X60
#define  SLAVE_SLA_R_ACK_STATUE             0XA8
#define  SLAVE_RECEIVE_DATA_ACK_STATUE      0X80
#define  SLAVE_TRANSMIT_DATA_ACK_STATUE     0xB8

#endif
