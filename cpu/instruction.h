/*
 * Copyright (c) 2019 Tom Hancocks, The Diamond Project
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
#include <sys/types.h>

#if !defined(lib68_InstructionLookup)
#define lib68_InstructionLookup

#define M68_MAX_AVAILABLE_INSTRUCTIONS	0x10000

/* Instruction Definition Structure 
 * This helps with lookup of instruction implementation functions and mnemonics
 * for easy identification. */
struct m68_instruction {
	const char *mnemonic;
	void(*imp)(void);
};

/* Instruction Look Up Table 
 * This table is defined else where, but the symbol is globally accessible. 
 * This is primarily for test purposes. */
extern struct m68_instruction m68_instruction_table[M68_MAX_AVAILABLE_INSTRUCTIONS];

/* Fetch the Instruction Structure for the instruction denoted by the opcode. */
struct m68_instruction *m68_fetch_instruction_for_opcode(uint16_t);

#endif