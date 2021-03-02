#pragma once

using u32 = unsigned;

#define REG_DISPCNT *(u32*)0x4000000
#define MODE_0 0x0
#define BG0_ENABLE 0x100


#if	defined	( __thumb__ )
#define	SystemCall(Number)	 __asm ("SWI	  "#Number"\n" :::  "r0", "r1", "r2", "r3")
#else
#define	SystemCall(Number)	 __asm ("SWI	  "#Number"	<< 16\n" :::"r0", "r1", "r2", "r3")
#endif

/*! \fn void VBlankIntrWait()
    \brief waits for a vertical blank interrupt to occur.
*/
static inline
void VBlankIntrWait()	{ SystemCall(5); }


typedef enum irqMASKS {
	IRQ_VBLANK	=	(1<<0),		/*!< vertical blank interrupt mask */
	IRQ_HBLANK	=	(1<<1),		/*!< horizontal blank interrupt mask */
	IRQ_VCOUNT	=	(1<<2),		/*!< vcount match interrupt mask */
	IRQ_TIMER0	=	(1<<3),		/*!< timer 0 interrupt mask */
	IRQ_TIMER1	=	(1<<4),		/*!< timer 1 interrupt mask */
	IRQ_TIMER2	=	(1<<5),		/*!< timer 2 interrupt mask */
	IRQ_TIMER3	=	(1<<6),		/*!< timer 3 interrupt mask */
	IRQ_SERIAL	=	(1<<7),		/*!< serial interrupt mask */
	IRQ_DMA0	=	(1<<8),		/*!< DMA 0 interrupt mask */
	IRQ_DMA1	=	(1<<9),		/*!< DMA 1 interrupt mask */
	IRQ_DMA2	=	(1<<10),	/*!< DMA 2 interrupt mask */
	IRQ_DMA3	=	(1<<11),	/*!< DMA 3 interrupt mask */
	IRQ_KEYPAD	=	(1<<12),	/*!< Keypad interrupt mask */
	IRQ_GAMEPAK	=	(1<<13)		/*!< horizontal blank interrupt mask */
} irqMASK;

typedef void ( * IntFn)(void);

void irqInit();
IntFn *irqSet(irqMASK mask, IntFn function);
void irqEnable(int mask);
