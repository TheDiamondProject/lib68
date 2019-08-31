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

#include <stddef.h>
#include "cpu/mmu.h"
#include "cpu/instruction.h"
#include "cpu/instructions/abcd.h"

// MARK: - Instruction Fetch

struct m68_instruction *m68_fetch_instruction_for_opcode(uint16_t opcode)
{
	struct m68_instruction *instruction = &m68_instruction_table[opcode];
	return instruction->mnemonic ? instruction : NULL;
}

// MARK: - Instruction Look Up Table

struct m68_instruction m68_instruction_table[M68_MAX_AVAILABLE_INSTRUCTIONS] = {

	/* ABCD Dy,Dx */
	[0xC100] = { "ABCD D0,D0", abcd_dn_dn },
	[0xC101] = { "ABCD D1,D0", abcd_dn_dn },
	[0xC102] = { "ABCD D2,D0", abcd_dn_dn },
	[0xC103] = { "ABCD D3,D0", abcd_dn_dn },
	[0xC104] = { "ABCD D4,D0", abcd_dn_dn },
	[0xC105] = { "ABCD D5,D0", abcd_dn_dn },
	[0xC106] = { "ABCD D6,D0", abcd_dn_dn },
	[0xC107] = { "ABCD D7,D0", abcd_dn_dn },
	[0xC108] = { "ABCD -(A0),-(A0)", abcd_m8_m8 },
	[0xC109] = { "ABCD -(A1),-(A0)", abcd_m8_m8 },
	[0xC10A] = { "ABCD -(A2),-(A0)", abcd_m8_m8 },
	[0xC10B] = { "ABCD -(A3),-(A0)", abcd_m8_m8 },
	[0xC10C] = { "ABCD -(A4),-(A0)", abcd_m8_m8 },
	[0xC10D] = { "ABCD -(A5),-(A0)", abcd_m8_m8 },
	[0xC10E] = { "ABCD -(A6),-(A0)", abcd_m8_m8 },
	[0xC10F] = { "ABCD -(A7),-(A0)", abcd_m8_m8 },

	[0xC300] = { "ABCD D0,D1", abcd_dn_dn },
	[0xC301] = { "ABCD D1,D1", abcd_dn_dn },
	[0xC302] = { "ABCD D2,D1", abcd_dn_dn },
	[0xC303] = { "ABCD D3,D1", abcd_dn_dn },
	[0xC304] = { "ABCD D4,D1", abcd_dn_dn },
	[0xC305] = { "ABCD D5,D1", abcd_dn_dn },
	[0xC306] = { "ABCD D6,D1", abcd_dn_dn },
	[0xC307] = { "ABCD D7,D1", abcd_dn_dn },
	[0xC308] = { "ABCD -(A0),-(A1)", abcd_m8_m8 },
	[0xC309] = { "ABCD -(A1),-(A1)", abcd_m8_m8 },
	[0xC30A] = { "ABCD -(A2),-(A1)", abcd_m8_m8 },
	[0xC30B] = { "ABCD -(A3),-(A1)", abcd_m8_m8 },
	[0xC30C] = { "ABCD -(A4),-(A1)", abcd_m8_m8 },
	[0xC30D] = { "ABCD -(A5),-(A1)", abcd_m8_m8 },
	[0xC30E] = { "ABCD -(A6),-(A1)", abcd_m8_m8 },
	[0xC30F] = { "ABCD -(A7),-(A1)", abcd_m8_m8 },

	[0xC500] = { "ABCD D0,D2", abcd_dn_dn },
	[0xC501] = { "ABCD D1,D2", abcd_dn_dn },
	[0xC502] = { "ABCD D2,D2", abcd_dn_dn },
	[0xC503] = { "ABCD D3,D2", abcd_dn_dn },
	[0xC504] = { "ABCD D4,D2", abcd_dn_dn },
	[0xC505] = { "ABCD D5,D2", abcd_dn_dn },
	[0xC506] = { "ABCD D6,D2", abcd_dn_dn },
	[0xC507] = { "ABCD D7,D2", abcd_dn_dn },
	[0xC508] = { "ABCD -(A0),-(A2)", abcd_m8_m8 },
	[0xC509] = { "ABCD -(A1),-(A2)", abcd_m8_m8 },
	[0xC50A] = { "ABCD -(A2),-(A2)", abcd_m8_m8 },
	[0xC50B] = { "ABCD -(A3),-(A2)", abcd_m8_m8 },
	[0xC50C] = { "ABCD -(A4),-(A2)", abcd_m8_m8 },
	[0xC50D] = { "ABCD -(A5),-(A2)", abcd_m8_m8 },
	[0xC50E] = { "ABCD -(A6),-(A2)", abcd_m8_m8 },
	[0xC50F] = { "ABCD -(A7),-(A2)", abcd_m8_m8 },

	[0xC700] = { "ABCD D0,D3", abcd_dn_dn },
	[0xC701] = { "ABCD D1,D3", abcd_dn_dn },
	[0xC702] = { "ABCD D2,D3", abcd_dn_dn },
	[0xC703] = { "ABCD D3,D3", abcd_dn_dn },
	[0xC704] = { "ABCD D4,D3", abcd_dn_dn },
	[0xC705] = { "ABCD D5,D3", abcd_dn_dn },
	[0xC706] = { "ABCD D6,D3", abcd_dn_dn },
	[0xC707] = { "ABCD D7,D3", abcd_dn_dn },
	[0xC708] = { "ABCD -(A0),-(A3)", abcd_m8_m8 },
	[0xC709] = { "ABCD -(A1),-(A3)", abcd_m8_m8 },
	[0xC70A] = { "ABCD -(A2),-(A3)", abcd_m8_m8 },
	[0xC70B] = { "ABCD -(A3),-(A3)", abcd_m8_m8 },
	[0xC70C] = { "ABCD -(A4),-(A3)", abcd_m8_m8 },
	[0xC70D] = { "ABCD -(A5),-(A3)", abcd_m8_m8 },
	[0xC70E] = { "ABCD -(A6),-(A3)", abcd_m8_m8 },
	[0xC70F] = { "ABCD -(A7),-(A3)", abcd_m8_m8 },

	[0xC900] = { "ABCD D0,D4", abcd_dn_dn },
	[0xC901] = { "ABCD D1,D4", abcd_dn_dn },
	[0xC902] = { "ABCD D2,D4", abcd_dn_dn },
	[0xC903] = { "ABCD D3,D4", abcd_dn_dn },
	[0xC904] = { "ABCD D4,D4", abcd_dn_dn },
	[0xC905] = { "ABCD D5,D4", abcd_dn_dn },
	[0xC906] = { "ABCD D6,D4", abcd_dn_dn },
	[0xC907] = { "ABCD D7,D4", abcd_dn_dn },
	[0xC908] = { "ABCD -(A0),-(A4)", abcd_m8_m8 },
	[0xC909] = { "ABCD -(A1),-(A4)", abcd_m8_m8 },
	[0xC90A] = { "ABCD -(A2),-(A4)", abcd_m8_m8 },
	[0xC90B] = { "ABCD -(A3),-(A4)", abcd_m8_m8 },
	[0xC90C] = { "ABCD -(A4),-(A4)", abcd_m8_m8 },
	[0xC90D] = { "ABCD -(A5),-(A4)", abcd_m8_m8 },
	[0xC90E] = { "ABCD -(A6),-(A4)", abcd_m8_m8 },
	[0xC90F] = { "ABCD -(A7),-(A4)", abcd_m8_m8 },

	[0xCB00] = { "ABCD D0,D5", abcd_dn_dn },
	[0xCB01] = { "ABCD D1,D5", abcd_dn_dn },
	[0xCB02] = { "ABCD D2,D5", abcd_dn_dn },
	[0xCB03] = { "ABCD D3,D5", abcd_dn_dn },
	[0xCB04] = { "ABCD D4,D5", abcd_dn_dn },
	[0xCB05] = { "ABCD D5,D5", abcd_dn_dn },
	[0xCB06] = { "ABCD D6,D5", abcd_dn_dn },
	[0xCB07] = { "ABCD D7,D5", abcd_dn_dn },
	[0xCB08] = { "ABCD -(A0),-(A5)", abcd_m8_m8 },
	[0xCB09] = { "ABCD -(A1),-(A5)", abcd_m8_m8 },
	[0xCB0A] = { "ABCD -(A2),-(A5)", abcd_m8_m8 },
	[0xCB0B] = { "ABCD -(A3),-(A5)", abcd_m8_m8 },
	[0xCB0C] = { "ABCD -(A4),-(A5)", abcd_m8_m8 },
	[0xCB0D] = { "ABCD -(A5),-(A5)", abcd_m8_m8 },
	[0xCB0E] = { "ABCD -(A6),-(A5)", abcd_m8_m8 },
	[0xCB0F] = { "ABCD -(A7),-(A5)", abcd_m8_m8 },

	[0xCD00] = { "ABCD D0,D6", abcd_dn_dn },
	[0xCD01] = { "ABCD D1,D6", abcd_dn_dn },
	[0xCD02] = { "ABCD D2,D6", abcd_dn_dn },
	[0xCD03] = { "ABCD D3,D6", abcd_dn_dn },
	[0xCD04] = { "ABCD D4,D6", abcd_dn_dn },
	[0xCD05] = { "ABCD D5,D6", abcd_dn_dn },
	[0xCD06] = { "ABCD D6,D6", abcd_dn_dn },
	[0xCD07] = { "ABCD D7,D6", abcd_dn_dn },
	[0xCD08] = { "ABCD -(A0),-(A6)", abcd_m8_m8 },
	[0xCD09] = { "ABCD -(A1),-(A6)", abcd_m8_m8 },
	[0xCD0A] = { "ABCD -(A2),-(A6)", abcd_m8_m8 },
	[0xCD0B] = { "ABCD -(A3),-(A6)", abcd_m8_m8 },
	[0xCD0C] = { "ABCD -(A4),-(A6)", abcd_m8_m8 },
	[0xCD0D] = { "ABCD -(A5),-(A6)", abcd_m8_m8 },
	[0xCD0E] = { "ABCD -(A6),-(A6)", abcd_m8_m8 },
	[0xCD0F] = { "ABCD -(A7),-(A6)", abcd_m8_m8 },

	[0xCF00] = { "ABCD D0,D7", abcd_dn_dn },
	[0xCF01] = { "ABCD D1,D7", abcd_dn_dn },
	[0xCF02] = { "ABCD D2,D7", abcd_dn_dn },
	[0xCF03] = { "ABCD D3,D7", abcd_dn_dn },
	[0xCF04] = { "ABCD D4,D7", abcd_dn_dn },
	[0xCF05] = { "ABCD D5,D7", abcd_dn_dn },
	[0xCF06] = { "ABCD D6,D7", abcd_dn_dn },
	[0xCF07] = { "ABCD D7,D7", abcd_dn_dn },
	[0xCF08] = { "ABCD -(A0),-(A7)", abcd_m8_m8 },
	[0xCF09] = { "ABCD -(A1),-(A7)", abcd_m8_m8 },
	[0xCF0A] = { "ABCD -(A2),-(A7)", abcd_m8_m8 },
	[0xCF0B] = { "ABCD -(A3),-(A7)", abcd_m8_m8 },
	[0xCF0C] = { "ABCD -(A4),-(A7)", abcd_m8_m8 },
	[0xCF0D] = { "ABCD -(A5),-(A7)", abcd_m8_m8 },
	[0xCF0E] = { "ABCD -(A6),-(A7)", abcd_m8_m8 },
	[0xCF0F] = { "ABCD -(A7),-(A7)", abcd_m8_m8 },

};
