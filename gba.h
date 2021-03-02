#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned short u16;
typedef unsigned u32;


#define REG_DISPCNT *(u32*)0x4000000
#define MODE_0 0x0
#define BG0_ENABLE 0x100
#define MEM_BG_PALETTE ((u16*)(0x05000000))


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


enum RESET_FLAG {
	RESET_EWRAM		=	(1<<0),	/*!< Clear 256K on-board WRAM			*/
	RESET_IWRAM		=	(1<<1),	/*!< Clear 32K in-chip WRAM				*/
	RESET_PALETTE	=	(1<<2),	/*!< Clear Palette						*/
	RESET_VRAM		=	(1<<3),	/*!< Clear VRAM							*/
	RESET_OAM		=	(1<<4),	/*!< Clear OAM							*/
	RESET_SIO		=	(1<<5),	/*!< Switches to general purpose mode	*/
	RESET_SOUND		=	(1<<6),	/*!< Reset Sound registers				*/
	RESET_OTHER		=	(1<<7)	/*!< all other registers				*/
};

typedef enum RESET_FLAG RESET_FLAGS;
void RegisterRamReset(int ResetFlags);


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


__attribute__((section(".iwram"), long_call)) void
memcpy32(void* dst, const void* src, unsigned wcount);
void memcpy16(void* dst, const void* src, unsigned hwcount);

#ifdef __cplusplus
}	   // extern "C"
#endif
