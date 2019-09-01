/* Copyright (c) 2019 Tom Hancocks, The Diamond Project
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdint.h>

#if !defined(lib68_CPU)
#define lib68_CPU

/* A union representing a standard 32-bit register in the Motorola 68000
 * series CPU. */
typedef union {
	uint32_t	value;
	uint8_t 	byte[4];
	uint16_t	word[2];
} m68_register32_t;

/* This structure represents the internal state of a Motorola 68000 series
 * CPU. */
struct M68000 {
	/* Data Registers */
	m68_register32_t D[8];
	
	/* Address Registers */
	m68_register32_t A[8];

	/* Control Register - PC */
	m68_register32_t PC;
	
	/* Control Register - SR/CCR */
	union {
		uint16_t value;
		struct {
			struct {
				uint8_t C:1;
				uint8_t V:1;
				uint8_t Z:1;
				uint8_t N:1;
				uint8_t X:1;
				uint8_t _1:3;
			} user;
			struct {
				uint8_t IPM:3; 	/* Interrupt Priority Mask */
				uint8_t _1:1;
				uint8_t IS:1;  	/* Interrupt/Master State */
				uint8_t S:1;	/* Supervisor/User State */
				uint8_t TE:2;	/* Trace Enable */
			} mask;
		} bitmask;
	} CCR;

	/* Supervisor Only Registers */
	m68_register32_t AC0, AC1;
	m68_register32_t ACUSR;
	m68_register32_t CAAR;
	m68_register32_t DACR0, DACR1;
	m68_register32_t DFC;
	m68_register32_t DTT0, DTT1;
	m68_register32_t IACR0, IACR1;
	m68_register32_t ITT0, ITT1;
	m68_register32_t MSP;
	m68_register32_t SFC;
	m68_register32_t SSP, ISP;
	m68_register32_t TT0, TT1;
	m68_register32_t VBR;

	/* Supervisor Only Register - Related to Paged Memory Management */
	union {
		uint32_t value;
		struct {
			uint8_t FC_MASK:3;	/* Function Code Mask */
			uint8_t _1:1;
			uint8_t FC_BASE:3;	/* Function Code Base */
			uint8_t _2:1;
			uint8_t RWM:1;		/* Read / Write Mask */
			uint8_t RW:1;		/* Read / Write */
			uint8_t CI:1;		/* Cache Inhibit */
			uint8_t _3:4;		
			uint8_t E:1; 		/* Enable */
			uint8_t ADDRESS_MASK;
			uint8_t ADDRESS_BASE;
		} mask;	
	} AC;
	m68_register32_t CAL;
	m68_register32_t CRP;
	m68_register32_t DRP;
	m68_register32_t PCSR;
	m68_register32_t PMMUSR;
	m68_register32_t MMUSR;
	m68_register32_t SCC;
	m68_register32_t SRP;
	m68_register32_t TC;
	m68_register32_t URP;
	m68_register32_t VAL;	
};

extern struct M68000 CPU68;

#endif