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

#include "cpu/instruction.h"
#include "cpu/instructions/abcd.h"

void abcd_dn_dn(void)
{
	union m68_abcd_opcode opcode = { m68_mmu_read_word(CPU68.PC.value) };
	uint8_t Rx = opcode.field.Rx;
	uint8_t Ry = opcode.field.Ry;
	uint8_t Vx = CPU68.D[Rx].byte[0];
	uint8_t Vy = CPU68.D[Ry].byte[0];
	uint8_t X = CPU68.CCR.bitmask.user.X;

	uint8_t r = Vx + Vy + X;
	uint8_t bc = ((Vx & Vy) | (~r & Vx) | (~r & Vy)) & 0x88;
	uint8_t dc = (((r + 0x66) ^ r) & 0x110) >> 1;
	uint8_t corf = (bc | dc) - ((bc | dc) >> 2);
	uint8_t rr = r + corf;

	CPU68.D[Ry].byte[0] = rr;
	     
	CPU68.CCR.bitmask.user.C = (bc | (r & ~rr)) >> 7;
	CPU68.CCR.bitmask.user.X = CPU68.CCR.bitmask.user.C;
	CPU68.CCR.bitmask.user.V = (~r && r) >> 7;
	CPU68.CCR.bitmask.user.Z &= (rr == 0);
	CPU68.CCR.bitmask.user.N = rr >> 7;
}