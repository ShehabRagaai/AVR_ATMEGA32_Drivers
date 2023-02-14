/********************************************************************************/
/********************************************************************************/
/*****************       Aathur:Shehab Ahmed Ragaai          ********************/
/*****************       Layer:MCAL                          ********************/
/*****************       SWC:EXTI                            ********************/
/*****************       version:1.00                        ********************/
/********************************************************************************/
/********************************************************************************/

#include"STD_TYPES.H"
#include"BIT_MATH.h"
#include"EXTI_register.h"
#include"EXTI_interface.h"
#include"EXTI_config.h"
#include"EXTI_private.h"


void(*Global_pu32INT0Address)(void)=NULL;
void(*Global_pu32INT1Address)(void)=NULL;
void(*Global_pu32INT2Address)(void)=NULL;


void EXTI_Int00Init(void)
{
#if INT0_CONTROLSENSE==LOW_LEVEL
	/*Set Control Sense Of INT0 To LOW LEVEL */
	CLEAR_BIT(MCUCR,MCUCR_ISC00);
	CLEAR_BIT(MCUCR,MCUCR_ISC01);
#elif INT0_CONTROLSENSE==FALLING_EDGE
	/*Set Control Sense Of INT0 To FALLING EDGE */
	CLEAR_BIT(MCUCR,MCUCR_ISC00);
	SET_BIT(MCUCR,MCUCR_ISC01);

#elif INT0_CONTROLSENSE==RASING_EDGE
	/*Set Control Sense Of INT0 To RASING EDGE */
	SET_BIT(MCUCR,MCUCR_ISC00);
	SET_BIT(MCUCR,MCUCR_ISC01);

#elif INT0_CONTROLSENSE==ON_CHANGE
	/*Set Control Sense Of INT0 To ON CHANGE */
	SET_BIT(MCUCR,MCUCR_ISC00);
	CLEAR_BIT(MCUCR,MCUCR_ISC01);



#endif

#if INT0_INIT_STATE==ENABLE
	/*Spacific Interrrupt Enable Of INT0*/
	SET_BIT(GICR,GICR_INT0);
#elif INT0_INIT_STATE==DISABLE
	/*Spacific Interrrupt DISABLE Of INT0*/
	CLEAR_BIT(GICR,GICR_INT0);



#endif



}


void EXTI_Int1Init(void)
{
#if INT1_CONTROLSENSE==LOW_LEVEL
	/*Set Control Sense Of INT1 To LOW LEVEL */
	CLEAR_BIT(MCUCR,MCUCR_ISC10);
	CLEAR_BIT(MCUCR,MCUCR_ISC11);

#elif INT1_CONTROLSENSE==FALLING_EDGE
	/*Set Control Sense Of INT1 To FALLING EDGE */
	CLEAR_BIT(MCUCR,MCUCR_ISC10);
	SET_BIT(MCUCR,MCUCR_ISC11);

#elif INT1_CONTROLSENSE==RASING_EDGE
	/*Set Control Sense Of INT1 To RASING EDGE */
	SET_BIT(MCUCR,MCUCR_ISC10);
	SET_BIT(MCUCR,MCUCR_ISC11);

#elif INT1_CONTROLSENSE==ON_CHANGE
	/*Set Control Sense Of INT1 To ON CHANGE */
	SET_BIT(MCUCR,MCUCR_ISC10);
	CLEAR_BIT(MCUCR,MCUCR_ISC11);



#endif

#if INT1_INIT_STATE==ENABLE
	/*Spacific Interrrupt Enable Of INT1*/
	SET_BIT(GICR,GICR_INT1);

#elif INT1_INIT_STATE==DISABLE
	/*Spacific Interrrupt DISABLE Of INT1*/
	CLEAR_BIT(GICR,GICR_INT1);


#endif
}


void EXTI_Int2Init(void)
{
#if INT2_CONTROLSENSE==FALLING_EDGE
	/*Set Control Sense Of INT2 To FALLING EDGE */
	CLEAR_BIT(MCUCSR,MCUCSR_ISC2);
#elif INT2_CONTROLSENSE==RASING_EDGE
	/*Set Control Sense Of INT2 To RASING EDGE */
	SET_BIT(MCUCSR,MCUCSR_ISC2);


#endif

#if  INT2_INIT_STATE==ENABLE
	/*Spacific Interrrupt Enable Of INT2*/
	SET_BIT(GICR,GICR_INT2);
#elif  INT2_INIT_STATE==DISABLE
	/*Spacific Interrrupt Enable Of INT2*/
	CLEAR_BIT(GICR,GICR_INT2);
#endif
}




u8 EXIT_u8SetControlSense(u8 Copy_u8Sense,u8 copy_u8INT)
{
	u8 Error_u8State=0;
	if(copy_u8INT<=INT2 )
	{
		if(copy_u8INT==INT0)
		{
			switch(Copy_u8Sense)
			{
			case  LOW_LEVEL:
				CLEAR_BIT(MCUCR,MCUCR_ISC00);
				CLEAR_BIT(MCUCR,MCUCR_ISC01);
				break;

			case  FALLING_EDGE:
				CLEAR_BIT(MCUCR,MCUCR_ISC00);
				SET_BIT(MCUCR,MCUCR_ISC01);
				break;

			case  RISING_EDGE:
				SET_BIT(MCUCR,MCUCR_ISC00);
				SET_BIT(MCUCR,MCUCR_ISC01);
				break;

			case  ON_CHANGE:
				SET_BIT(MCUCR,MCUCR_ISC00);
				CLEAR_BIT(MCUCR,MCUCR_ISC01);
				break;
			default:
				Error_u8State=1;
				break;


			}



		}

		else if(copy_u8INT==INT1)
		{
			switch(Copy_u8Sense)
			{
			case  LOW_LEVEL:
				CLEAR_BIT(MCUCR,MCUCR_ISC10);
				CLEAR_BIT(MCUCR,MCUCR_ISC11);

				break;

			case  FALLING_EDGE:
				CLEAR_BIT(MCUCR,MCUCR_ISC10);
				SET_BIT(MCUCR,MCUCR_ISC11);

				break;

			case  RISING_EDGE:
				SET_BIT(MCUCR,MCUCR_ISC10);
				SET_BIT(MCUCR,MCUCR_ISC11);
				break;

			case  ON_CHANGE:
				SET_BIT(MCUCR,MCUCR_ISC10);
				CLEAR_BIT(MCUCR,MCUCR_ISC11);
				break;


			default:
				Error_u8State=1;
				break;

			}


		}

		else if(copy_u8INT==INT2)
		{
			switch(Copy_u8Sense)
			{

			case  FALLING_EDGE:
				CLEAR_BIT(MCUCSR,MCUCSR_ISC2);

				break;

			case  RISING_EDGE:
				SET_BIT(MCUCSR,MCUCSR_ISC2);
				break;



			default:
				Error_u8State=1;
				break;

			}

		}



	}

	else
	{
		Error_u8State=1;
	}

	return Error_u8State;
}


u8 EXIT_u8EnableState(u8 copy_u8INT)
{
	u8 Error_u8State=0;
	if(copy_u8INT<=INT2 )
	{
		if(copy_u8INT==INT0)
		{
			SET_BIT(GICR,GICR_INT0);
		}

		else if(copy_u8INT==INT1)
		{
			SET_BIT(GICR,GICR_INT1);
		}
		else if(copy_u8INT==INT2)
		{
			SET_BIT(GICR,GICR_INT2);
		}
	}

	else
	{
		Error_u8State=1;
	}
	return Error_u8State;

}
u8 EXIT_u8Disablestate(u8 copy_u8INT)
{
	u8 Error_u8State=0;
	if(copy_u8INT<=INT2 )
	{
		if(copy_u8INT==INT0)
		{
			CLEAR_BIT(GICR,GICR_INT0);
		}

		else if(copy_u8INT==INT1)
		{
			CLEAR_BIT(GICR,GICR_INT1);
		}
		else if(copy_u8INT==INT2)
		{
			CLEAR_BIT(GICR,GICR_INT2);
		}
	}

	else
	{
		Error_u8State=1;
	}
	return Error_u8State;
}

u8 EXIT_u8INT0TakeAddress(void(*copy_pvINT0Address)(void))
{
	u8 Error_u8State=0;

	if(copy_pvINT0Address!=NULL)
		Global_pu32INT0Address=copy_pvINT0Address;
	else
		Error_u8State=1;

	return Error_u8State;

}

u8 EXIT_u8INT1TakeAddress(void(*copy_pvINT1Address)(void))
{
	u8 Error_u8State=0;

	if(copy_pvINT1Address!=NULL)
		Global_pu32INT1Address=copy_pvINT1Address;
	else
		Error_u8State=1;

	return Error_u8State;
}

u8 EXIT_u8INT2TakeAddress(void(*copy_pvINT2Address)(void))
{
	u8 Error_u8State=0;

	if(copy_pvINT2Address!=NULL)
		Global_pu32INT2Address=copy_pvINT2Address;
	else
		Error_u8State=1;

	return Error_u8State;
}

void __vector_1 (void)__attribute__((signal));
void __vector_1 (void)
{
	Global_pu32INT0Address();
}

void __vector_2 (void)__attribute__((signal));
void __vector_2 (void)
{
	Global_pu32INT1Address();
}

void __vector_3 (void)__attribute__((signal));
void __vector_3 (void)
{
	Global_pu32INT2Address();
}



