/********************************************************************************/
/********************************************************************************/
/*****************       Aathur:Shehab Ahmed Ragaai          ********************/
/*****************       Layer:MCAL                          ********************/
/*****************       SWC:UART                            ********************/
/*****************       version:1.00                        ********************/
/********************************************************************************/
/********************************************************************************/
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"UART_register.h"
#include"UART_config.h"
#include"UART_private.h"
#include"UART_interface.h"


u8 Global_u8StateRecive=IDEL;
u8 Global_u8StateSend=IDEL;
u8*Global_u8RecieveData;
u8*Global_u8AsynSendData;
u8 Global_u8SendData;
u8 Global_u8TypeOfSending;
u8 Global_u8TypeOfReceive;
u8 Global_u8Size;
u8* Gloabl_u8ReceiveDataAsynch;


void (*Global_PvNotifacationReceive)(void)=NULL;
void (*Global_PvNotifacationSend)(void)=NULL;



void UART_voidInit(void)
{

	/*1 bit stop,No parity,Asynchronous,8 bit data*/
	//UCSRC=0b10000110;
	u8 Local_u8Value=0;
	SET_BIT(Local_u8Value,UCSRC_URSEL);
	SET_BIT(Local_u8Value,UCSRC_UCSZ0);
	SET_BIT(Local_u8Value,UCSRC_UCSZ1);
	UCSRC=Local_u8Value;
	CLEAR_BIT(UCSRB,UCSRB_UCSZ2);


	/*9600 Bit/sec*/

	UBRRL=51;

	/*Transmite Enable And Receive Enable*/
	SET_BIT(UCSRB,UCSRB_TXEN);
	SET_BIT(UCSRB,UCSRB_RXEN);

}
u8 UART_u8SendCharSynch(u8 Copy_u8Data)
{
	u8 Local_u8ErrorState=0;
	u8 Local_u8Counter=0;



	while(GET_BIT(UCSRA,UCSRA_UDRE)==0 && Local_u8Counter<TIME_OUT)
	{
		Local_u8Counter++;
	}
	if(Local_u8Counter==TIME_OUT)
	{
		Local_u8ErrorState=1;
	}
	else
	{
		UDR=Copy_u8Data;
	}

	return  Local_u8ErrorState=0;
}
u8 UART_u8ReciveCharSynch(u8*Copy_PuRecieveData)
{
	u8 Local_u8ErrorState=0;
	u8 Local_u8Counter=0;

	while(GET_BIT(UCSRA,UCSRA_RXC)==0 &&Local_u8Counter<TIME_OUT)
	{
		Local_u8Counter++;
	}

	if(Local_u8Counter==TIME_OUT)
	{
		Local_u8ErrorState=1;
	}
	else
	{
		*Copy_PuRecieveData=UDR;
	}

	return Local_u8ErrorState;

}

u8 UART_u8ReceiveCharASynch(u8*Copy_u8Data,void (*copy_PvNotifacation)(void))
{
	u8 Local_u8ErrorState=0;
	Global_u8TypeOfReceive=Char;

	if(Global_u8StateRecive==BUSY)
	{
		Local_u8ErrorState=1;
	}

	else
	{
		Global_u8StateRecive=BUSY;
		Global_u8RecieveData=Copy_u8Data;
		Global_PvNotifacationReceive=copy_PvNotifacation;
		/*RX Interrupt Enable*/
		SET_BIT(UCSRB,UCSRB_RXCIE);
	}

	return Local_u8ErrorState;
}


u8 UART_u8SendCharASynch(u8 Copy_u8Data,void (*copy_PvNotifacation)(void))
{
	u8 Local_u8ErrorState=0;
	Global_u8TypeOfSending=Char;


	if(Global_u8StateSend==BUSY)
	{
		Local_u8ErrorState=1;
	}

	else
	{
		Global_u8StateSend=BUSY;
		Global_u8SendData=Copy_u8Data;
		Global_PvNotifacationSend=copy_PvNotifacation;
		/*Register Empty Interrupt Enable*/
		SET_BIT(UCSRB,UCSRB_UDRIE);
	}

	return Local_u8ErrorState;

}


void UART_u8SendStringSynch(u8*Copy_u8Data)
{
	u8 Local_Counter=0;
	while(Copy_u8Data[Local_Counter]!='\0')
	{
		UART_u8SendCharSynch(Copy_u8Data[Local_Counter]);

		Local_Counter++;
	}

}

void UART_u8ReceiveStringSynch(u8 *Copy_P8ReceiveData,u8 Copy_u8Size)
{
	u8 Local_Counter=0;
	while(Local_Counter<Copy_u8Size)
	{
		UART_u8ReciveCharSynch(&Copy_P8ReceiveData[Local_Counter]);
		Local_Counter++;
	}
}

u8 UART_u8SendStringASynch(u8*Copy_Pu8Data,void (*copy_PvNotifacation)(void))
{
	 Global_u8TypeOfSending=STRING;
	u8 Local_ErrorState=0;
	if(Global_u8StateSend==BUSY)
	{
		Local_ErrorState=1;
	}
	else
	{
		Global_u8StateSend=BUSY;
		Global_u8AsynSendData=Copy_Pu8Data;
		Global_PvNotifacationSend=copy_PvNotifacation;
		/*Register Empty Interrupt Enable*/
		SET_BIT(UCSRB,UCSRB_UDRIE);
	}
	return Local_ErrorState;
}

u8 UART_u8ReceiveStringASynch(u8 *Copy_P8ReceiveData,u8 Copy_u8Size,void (*copy_PvNotifacation)(void))
{
	u8 Local_u8ErrorState=0;
	Global_u8TypeOfReceive=STRING;
	if(Global_u8StateRecive==BUSY)
	{
		Local_u8ErrorState=1;
	}
	else
	{
		Global_u8StateRecive=BUSY;
		Gloabl_u8ReceiveDataAsynch=Copy_P8ReceiveData;
		Global_u8Size=Copy_u8Size;
		Global_PvNotifacationReceive=copy_PvNotifacation;
		/*RX Interrupt Enable*/
		SET_BIT(UCSRB,UCSRB_RXCIE);

	}

	return Local_u8ErrorState;

}




void __vector_13 (void)__attribute((signal));
void __vector_13 (void)
{
	static u8 Local_u8Counter1=0;
	if(Global_u8TypeOfReceive==Char)
	{
		*Global_u8RecieveData=UDR;
		Global_u8StateRecive=IDEL;
		/*RX Interrupt Disable*/
		CLEAR_BIT(UCSRB,UCSRB_RXCIE);
		Global_PvNotifacationReceive();
	}

	else if(Global_u8TypeOfReceive==STRING)
	{
		Gloabl_u8ReceiveDataAsynch[Local_u8Counter1]=UDR;
		if(Local_u8Counter1==Global_u8Size)
		{
			Global_u8StateRecive=IDEL;
			/*RX Interrupt Disable*/
			CLEAR_BIT(UCSRB,UCSRB_RXCIE);
			Global_PvNotifacationReceive();
			Local_u8Counter1=0;
		}
		else
		{

			Local_u8Counter1++;
		}
	}
}

void __vector_14 (void)__attribute((signal));
void __vector_14 (void)
{
	static u8 Local_u8Counter2=0;
	if(Global_u8TypeOfSending==Char)
	{
		UDR=Global_u8SendData;
		Global_u8StateSend=IDEL;
		/*Empty Register Interrupt Disable*/
		CLEAR_BIT(UCSRB,UCSRB_UDRIE);
		Global_PvNotifacationSend();
	}

	else if(Global_u8TypeOfSending==STRING)
	{
		if(Global_u8AsynSendData[Local_u8Counter2]=='\0')
		{
			Global_u8StateSend=IDEL;
			/*Empty Register Interrupt Disable*/
			CLEAR_BIT(UCSRB,UCSRB_UDRIE);
			Global_PvNotifacationSend();
			Local_u8Counter2=0;
		}
		else
		{
			UDR=Global_u8AsynSendData[Local_u8Counter2];
			Local_u8Counter2++;

		}
	}
}


