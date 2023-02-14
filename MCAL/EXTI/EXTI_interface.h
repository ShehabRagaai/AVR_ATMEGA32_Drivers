/********************************************************************************/
/********************************************************************************/
/*****************       Aathur:Shehab Ahmed Ragaai          ********************/
/*****************       Layer:MCAL                          ********************/
/*****************       SWC:EXTI                            ********************/
/*****************       version:1.00                        ********************/
/********************************************************************************/
/********************************************************************************/

#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_
#define LOW_LEVEL    1
#define FALLING_EDGE 2
#define RISING_EDGE  3
#define ON_CHANGE    4

#define ENABLE     1
#define DISABLE    2

#define INT0 0
#define INT1 1
#define INT2 2





void EXTI_Int00Init(void);
void EXTI_Int1Init(void);
void EXTI_Int2Init(void);
u8 EXIT_u8SetControlSense(u8 Copy_u8Sense,u8 copy_u8INT);
u8 EXIT_u8EnableState(u8 copy_u8INT);
u8 EXIT_u8Disablestate(u8 copy_u8INT);

u8 EXIT_u8INT0TakeAddress(void (*copy_pvINT0Address)(void));
u8 EXIT_u8INT1TakeAddress(void (*copy_pvINT1Address)(void));
u8 EXIT_u8INT2TakeAddress(void (*copy_pvINT2Address)(void));




#endif
