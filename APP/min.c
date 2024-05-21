/*
 * min.c

 *
 *  Created on: Mar 18, 2024
 *      Author: User
 */
#include <util/delay.h>
#include "STD_TYPES.h"
#include "LCD_Interface.h"
#include "DIO_Interface.h"
#include "KPD_Interface.h"
#include <stdlib.h>
#define MAX  100
int stack[MAX];
u8 infix[MAX];
u8 postfix[MAX];
u32 top=-1;
u8 counter=0;

/************prototypes***************/
void push(u64 x);
u64 pop(void);
u32 isEmpty(void);
void inTOPOST();
u32 precedence(u8 symbol);
void print_PostFix();
u32 post_eval();
u32 space(u32);

/**************************/
int main()
{
	LCD_voidInit();
	KPD_Init();
	u8 local_u8input=NOTPRESSED;
	u8 i=0;
	u32 result=0;
	while(1)
	{
		local_u8input=KPD_u8GetPressed();
		if(local_u8input!=NOTPRESSED)
		{
			LCD_voidSetPosition(0,i);
			if((local_u8input =='+')||(local_u8input=='-')||(local_u8input=='*')||(local_u8input=='/')||(local_u8input=='(')||(local_u8input==')'))
			{
				LCD_voidSendData(local_u8input);
			}
			else
			{
				LCD_voidSendNumber(local_u8input-'0');
			}
			infix[counter]=local_u8input;
			i++;
			counter++;
			if(local_u8input == '=')
			{
				LCD_voidSetPosition(0,i-1);
				LCD_voidSendData('=');

				inTOPOST();
				result=post_eval();
				LCD_voidSendNumber(result);
			}
			if(local_u8input== (u8)'?')
			{
				result=0;
				LCD_voidSetPosition(0,0);
				LCD_voidClearScreen();
				i=0;
			}
		}

	}
}

void push (u64 val)
{
	if(top == MAX -1 ){
		return;
	}
	top++;
	stack[top]=val;
}

u64 pop (void)
{
	u32 val;
	if (top==-1){
		exit(1);
	}

	val=stack[top];
	top=top-1;
	return val;
}
void print_PostFix()
{
	u8 i=0;
	LCD_voidClearScreen();
	LCD_voidSetPosition(0,0);
	LCD_voidSendString((u8*)"Postfix =");
	LCD_voidSetPosition(1,0);
	while(postfix[i]){
		LCD_voidSendNumber(postfix[i++]-'0');
	}
	_delay_ms(1000);
}
u32 precedence(u8 symbol){
	switch(symbol){
	case '^':
		return '3';
	case '/':
	case '*':
		return '2';
	case '+':
	case'-':
		return '1';
	default :
		return 0;
	}
}
void inTOPOST(){
	u32 i,j=0;
	u8 symbol,next;
	for(i=0;i<5;i++){
		symbol=infix[i];
		if(!space(symbol))
		{
			switch(symbol)
			{
			case '(':
				push(symbol);
				break;
			case ')':
				while((next=pop()) !='(')
					postfix[j++]=next;
				break;
			case '*':
			case '/':
			case '+':
			case '-':
			case '^':
				while(! isEmpty()&& precedence(stack[top])>=precedence(symbol))
					postfix[j++]=pop();
				push(symbol);
				break;
			default :
				postfix[j++]=symbol;
			}
		}
	}
	while(!isEmpty())
		postfix[j++]=pop();
	postfix[j]='\0';
}

u32 isEmpty(void)
{
	if(top==-1)
		return 1;
	else
		return 0;
}

u32 space(u32 c)
{
	if(c==' '|| c=='\t')
		return 1;
	else
		return 0;
}

u32 post_eval()
{
	u32 i;
	u32 a,b;
	for(i=0;i<5;i++)
	{
		if(postfix[i]>= '0'&& postfix[i]<='9')
		{
			push(postfix[i]-'0');
		}
		else
		{
			a=pop();
			b=pop();
			switch(postfix[i])
			{
			case '+':push(b+a); break;
			case '-':push(b-a); break;
			case '*':push(b*a); break;
			case '/':push(b/a); break;
			}
		}
	}
	return pop();
}

