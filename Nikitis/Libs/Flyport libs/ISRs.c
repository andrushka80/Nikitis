#include "HWlib.h"
#include "Hilo.h"
#include "INTlib.h"


extern void (*isr_int2)();
extern void (*isr_int3)();
extern void (*isr_int4)(); 

unsigned int StkAddrLo;  // order matters
unsigned int StkAddrHi;

/* this definition will signal an TRAP which needs address print for debugging*/
#define TRAP_ISR __attribute__((no_auto_psv,__interrupt__(__preprologue__( \
 "mov #_StkAddrHi,w1\n\tpop [w1--]\n\tpop [w1++]\n\tpush [w1--]\n\tpush [w1++]"))))

/****************************************************************************
  SECTION 	ISR (Interrupt Service routines)
****************************************************************************/
void __attribute__((interrupt, auto_psv)) _U1RXInterrupt(void)
{
	UARTRxInt(1);
}

void __attribute__((interrupt, auto_psv)) _U2RXInterrupt(void)
{
#if UART_PORTS >= 2
	UARTRxInt(2);
#endif
}

void __attribute__((interrupt, auto_psv)) _U3RXInterrupt(void)
{
#if UART_PORTS >= 3
	UARTRxInt(3);
#endif
}

void __attribute__((interrupt, auto_psv)) _U4RXInterrupt(void)
{
#if defined (FLYPORTGPRS)
    GSMRxInt();
#endif
}


void __attribute__((interrupt, auto_psv)) _DefaultInterrupt(void)
{
	_dbgwrite("!!! Default interrupt handler !!!\r\n" );
	Reset();
}

void __attribute__((interrupt, auto_psv)) _OscillatorFail(void)
{
	_dbgwrite("!!! Oscillator Fail interrupt handler !!!\r\n" );
	Reset();
}
void TRAP_ISR _AddressError(void)
{

	char dbgMsg[40];
	
	sprintf(dbgMsg,"%x\n",StkAddrHi);
	_dbgwrite(dbgMsg);
	sprintf(dbgMsg,"%x\n",StkAddrLo);
	_dbgwrite(dbgMsg);

	
	//_dbgwrite("!!! Address Error interrupt handler !!!\r\n" );
	Reset();
}
void __attribute__((interrupt, auto_psv)) _StackError(void)
{
	_dbgwrite("!!! Stack Error interrupt handler !!!\r\n" );
	Reset();
}
void __attribute__((interrupt, auto_psv)) _MathError(void)
{
	_dbgwrite("!!! Math Error interrupt handler !!!\r\n" );
	Reset();
}

void __attribute__((interrupt, auto_psv)) _INT2Interrupt(void) 
{
	// Reset interrupt 
	IFS1bits.INT2IF = 0;
	isr_int2();
	 
}

void __attribute__((interrupt, auto_psv)) _INT3Interrupt(void) 
{ 
	// Reset interrupt 
	IFS3bits.INT3IF = 0; 
	isr_int3();
}

void __attribute__((interrupt, auto_psv)) _INT4Interrupt(void) 
{ 
	// Reset interrupt 
	IFS3bits.INT4IF = 0; 
	isr_int4();
}
