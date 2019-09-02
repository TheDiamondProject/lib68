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

#include <libUnit/unit.h>
#include "cpu/cpu.h"
#include "cpu/mmu.h"
#include "cpu/instruction.h"

#if defined(UNIT_TEST)

TEST_CASE(InstructionLookup, FetchCorrectOpcodeFromMemory)
{
	m68_mmu_initialise();

	uint8_t *page = m68_mmu_page_alloc(0x0000);
	page[10] = 0xCB;
	page[11] = 0x05;

	CPU68.PC.value = 0x000A;

	struct m68_instruction *abcd = m68_fetch_instruction();
	ASSERT_NEQ(abcd, NULL);
	ASSERT_NEQ(abcd->imp, NULL);
	ASSERT_EQ_STR(abcd->mnemonic, "ABCD D5,D5");
}

TEST_CASE(InstructionLookup, InvalidOpcode)
{
	struct m68_instruction *ins = m68_fetch_instruction_for_opcode(0xFFFF);
	ASSERT_EQ(ins, NULL);
}

TEST_CASE(InstructionLookup, ValidABCD)
{
	struct m68_instruction *abcd = m68_fetch_instruction_for_opcode(0xCB05);
	ASSERT_NEQ(abcd, NULL);
	ASSERT_NEQ(abcd->imp, NULL);
	ASSERT_EQ_STR(abcd->mnemonic, "ABCD D5,D5");
}

#endif