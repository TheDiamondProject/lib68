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
#include "cpu/mmu.h"

#if defined(UNIT_TEST)

TEST_CASE(MMU, AllocateSamePageReturnsSameAddress)
{
	m68_mmu_initialise();

	void *a = m68_mmu_page_alloc(0x1500);
	void *b = m68_mmu_page_alloc(0x1700);

	ASSERT_EQ(a, b);
}

TEST_CASE(MMU, AllocateDifferentPageReturnsDifferentAddress)
{
	m68_mmu_initialise();

	void *a = m68_mmu_page_alloc(0x1500);
	void *b = m68_mmu_page_alloc(0x2500);

	ASSERT_NEQ(a, b);
}

TEST_CASE(MMU, WriteByteToMemory)
{
	m68_mmu_initialise();

	uint8_t *page = m68_mmu_page_alloc(0x0000);
	m68_mmu_write_byte(0x3, 0xCD);

	ASSERT_EQ(page[3], 0xCD);
}

TEST_CASE(MMU, WriteWordToMemory)
{
	m68_mmu_initialise();

	uint16_t *page = m68_mmu_page_alloc(0x0000);
	m68_mmu_write_word(0x0, 0xDEAD);

	ASSERT_EQ(page[0], 0xDEAD);
}

TEST_CASE(MMU, WriteLongToMemory)
{
	m68_mmu_initialise();

	uint32_t *page = m68_mmu_page_alloc(0x0000);
	m68_mmu_write_long(0x0, 0xDEADBEEF);

	ASSERT_EQ(page[0], 0xDEADBEEF);
}

#endif