
#ifndef  BIT_MATH_H_
#define  BIT_MATH_H_

#define REGISTER_SIZE		8


#define SET_BIT(Reg ,Bit)		(Reg|=(1<<Bit))
#define CLR_BIT(Reg ,Bit)		(Reg&=~(1<<Bit))
#define GET_BIT(Reg ,Bit)		((Reg>>Bit)&1)
#define TOG_BIT(Reg ,Bit)		(Reg^=(1<<Bit))

#define ROR(Reg , num)			((Reg>>num) | (Reg<<(REGISTER_SIZE -num)))
#define ROL(Reg , num)			((Reg<<num) | (Reg>>(REGISTER_SIZE -num)))


#endif   /*End of file : BIT_MATH.h*/

