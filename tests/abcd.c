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
#include "cpu/instructions/abcd.h"

#if defined(UNIT_TEST)

TEST_CASE(ABCD, DataRegisters_ExtendBitClear_NoCarry_NoneZero_CorrectResult)
{
	// Configure the operation in memory
	m68_mmu_initialise();

	uint8_t *ptr = m68_mmu_page_alloc(0x0000);
	*(ptr + 0) = 0xC1;
	*(ptr + 1) = 0x01;

	// Configure the CPU registers.
	CPU68.PC.value = 0x0000;
	CPU68.D[0].value = 0x46;
	CPU68.D[1].value = 0x28;
	CPU68.CCR.bitmask.user.Z = 1;
	CPU68.CCR.bitmask.user.X = 0;

	// Perform the operation and check if the results are as expected.
	abcd_dn_dn();

	ASSERT_EQ(CPU68.D[0].value, 0x46);
	ASSERT_EQ(CPU68.D[1].value, 0x74);
	ASSERT_EQ(CPU68.CCR.bitmask.user.X, 0);
	ASSERT_EQ(CPU68.CCR.bitmask.user.Z, 0);
	ASSERT_EQ(CPU68.CCR.bitmask.user.C, 0);
}

TEST_CASE(ABCD, DataRegisters_ExtendBitSet_NoCarry_NoneZero_CorrectResult)
{
	// Configure the operation in memory
	m68_mmu_initialise();

	uint8_t *ptr = m68_mmu_page_alloc(0x0000);
	*(ptr + 0) = 0xC1;
	*(ptr + 1) = 0x01;

	// Configure the CPU registers.
	CPU68.PC.value = 0x0000;
	CPU68.D[0].value = 0x46;
	CPU68.D[1].value = 0x28;
	CPU68.CCR.bitmask.user.Z = 1;
	CPU68.CCR.bitmask.user.X = 1;

	// Perform the operation and check if the results are as expected.
	abcd_dn_dn();

	ASSERT_EQ(CPU68.D[0].value, 0x46);
	ASSERT_EQ(CPU68.D[1].value, 0x75);
	ASSERT_EQ(CPU68.CCR.bitmask.user.X, 0);
	ASSERT_EQ(CPU68.CCR.bitmask.user.Z, 0);
	ASSERT_EQ(CPU68.CCR.bitmask.user.C, 0);
}

TEST_CASE(ABCD, DataRegisters_ExtendBitClear_Carry_NoneZero_CorrectResult)
{
	// Configure the operation in memory
	m68_mmu_initialise();

	uint8_t *ptr = m68_mmu_page_alloc(0x0000);
	*(ptr + 0) = 0xC1;
	*(ptr + 1) = 0x01;

	// Configure the CPU registers.
	CPU68.PC.value = 0x0000;
	CPU68.D[0].value = 0x91;
	CPU68.D[1].value = 0x10;
	CPU68.CCR.bitmask.user.Z = 1;
	CPU68.CCR.bitmask.user.X = 0;

	// Perform the operation and check if the results are as expected.
	abcd_dn_dn();

	ASSERT_EQ(CPU68.D[0].value, 0x91);
	ASSERT_EQ(CPU68.D[1].value, 0x01);
	ASSERT_EQ(CPU68.CCR.bitmask.user.X, 1);
	ASSERT_EQ(CPU68.CCR.bitmask.user.Z, 0);
	ASSERT_EQ(CPU68.CCR.bitmask.user.C, 1);
}

TEST_CASE(ABCD, DataRegisters_ExtendBitSet_Carry_NoneZero_CorrectResult)
{
	// Configure the operation in memory
	m68_mmu_initialise();

	uint8_t *ptr = m68_mmu_page_alloc(0x0000);
	*(ptr + 0) = 0xC1;
	*(ptr + 1) = 0x01;

	// Configure the CPU registers.
	CPU68.PC.value = 0x0000;
	CPU68.D[0].value = 0x90;
	CPU68.D[1].value = 0x10;
	CPU68.CCR.bitmask.user.Z = 1;
	CPU68.CCR.bitmask.user.X = 1;

	// Perform the operation and check if the results are as expected.
	abcd_dn_dn();

	ASSERT_EQ(CPU68.D[0].value, 0x90);
	ASSERT_EQ(CPU68.D[1].value, 0x01);
	ASSERT_EQ(CPU68.CCR.bitmask.user.X, 1);
	ASSERT_EQ(CPU68.CCR.bitmask.user.Z, 0);
	ASSERT_EQ(CPU68.CCR.bitmask.user.C, 1);
}

TEST_CASE(ABCD, DataRegisters_ExtendBitSet_Carry_Zero_CorrectResult)
{
	// Configure the operation in memory
	m68_mmu_initialise();

	uint8_t *ptr = m68_mmu_page_alloc(0x0000);
	*(ptr + 0) = 0xC1;
	*(ptr + 1) = 0x01;

	// Configure the CPU registers.
	CPU68.PC.value = 0x0000;
	CPU68.D[0].value = 0x90;
	CPU68.D[1].value = 0x10;
	CPU68.CCR.bitmask.user.Z = 1;
	CPU68.CCR.bitmask.user.X = 0;

	// Perform the operation and check if the results are as expected.
	abcd_dn_dn();

	ASSERT_EQ(CPU68.D[0].value, 0x90);
	ASSERT_EQ(CPU68.D[1].value, 0x00);
	ASSERT_EQ(CPU68.CCR.bitmask.user.X, 1);
	ASSERT_EQ(CPU68.CCR.bitmask.user.Z, 1);
	ASSERT_EQ(CPU68.CCR.bitmask.user.C, 1);
}

// MARK: - ABCD -(An),-(An)

TEST_CASE(ABCD, IndirectMemory_ExtendBitClear_NoCarry_NoneZero_CorrectResult)
{
	// Configure the operation in memory
	m68_mmu_initialise();

	uint8_t *ptr = m68_mmu_page_alloc(0x0000);
	*(ptr + 0) = 0xC1;
	*(ptr + 1) = 0x09;
	*(ptr + 0x0F) = 0x46;
	*(ptr + 0x1F) = 0x28;

	// Configure the CPU registers.
	CPU68.PC.value = 0x0000;
	CPU68.A[0].value = 0x10;
	CPU68.A[1].value = 0x20;
	CPU68.CCR.bitmask.user.Z = 1;
	CPU68.CCR.bitmask.user.X = 0;

	// Perform the operation and check if the results are as expected.
	abcd_m8_m8();

	ASSERT_EQ(*(ptr + 0x0F), 0x46);
	ASSERT_EQ(*(ptr + 0x1F), 0x74);
	ASSERT_EQ(CPU68.A[0].value, 0x0F);
	ASSERT_EQ(CPU68.A[1].value, 0x1F);
	ASSERT_EQ(CPU68.CCR.bitmask.user.X, 0);
	ASSERT_EQ(CPU68.CCR.bitmask.user.Z, 0);
	ASSERT_EQ(CPU68.CCR.bitmask.user.C, 0);
}

TEST_CASE(ABCD, IndirectMemory_ExtendBitSet_NoCarry_NoneZero_CorrectResult)
{
	// Configure the operation in memory
	m68_mmu_initialise();

	uint8_t *ptr = m68_mmu_page_alloc(0x0000);
	*(ptr + 0) = 0xC1;
	*(ptr + 1) = 0x09;
	*(ptr + 0x0F) = 0x46;
	*(ptr + 0x1F) = 0x28;

	// Configure the CPU registers.
	CPU68.PC.value = 0x0000;
	CPU68.A[0].value = 0x10;
	CPU68.A[1].value = 0x20;
	CPU68.CCR.bitmask.user.Z = 1;
	CPU68.CCR.bitmask.user.X = 1;

	// Perform the operation and check if the results are as expected.
	abcd_m8_m8();

	ASSERT_EQ(*(ptr + 0x0F), 0x46);
	ASSERT_EQ(*(ptr + 0x1F), 0x75);
	ASSERT_EQ(CPU68.A[0].value, 0x0F);
	ASSERT_EQ(CPU68.A[1].value, 0x1F);
	ASSERT_EQ(CPU68.CCR.bitmask.user.X, 0);
	ASSERT_EQ(CPU68.CCR.bitmask.user.Z, 0);
	ASSERT_EQ(CPU68.CCR.bitmask.user.C, 0);
}

TEST_CASE(ABCD, IndirectMemory_ExtendBitClear_Carry_NoneZero_CorrectResult)
{
	// Configure the operation in memory
	m68_mmu_initialise();

	uint8_t *ptr = m68_mmu_page_alloc(0x0000);
	*(ptr + 0) = 0xC1;
	*(ptr + 1) = 0x09;
	*(ptr + 0x0F) = 0x91;
	*(ptr + 0x1F) = 0x10;

	// Configure the CPU registers.
	CPU68.PC.value = 0x0000;
	CPU68.A[0].value = 0x10;
	CPU68.A[1].value = 0x20;
	CPU68.CCR.bitmask.user.Z = 1;
	CPU68.CCR.bitmask.user.X = 0;

	// Perform the operation and check if the results are as expected.
	abcd_m8_m8();

	ASSERT_EQ(*(ptr + 0x0F), 0x91);
	ASSERT_EQ(*(ptr + 0x1F), 0x01);
	ASSERT_EQ(CPU68.A[0].value, 0x0F);
	ASSERT_EQ(CPU68.A[1].value, 0x1F);
	ASSERT_EQ(CPU68.CCR.bitmask.user.X, 1);
	ASSERT_EQ(CPU68.CCR.bitmask.user.Z, 0);
	ASSERT_EQ(CPU68.CCR.bitmask.user.C, 1);
}

TEST_CASE(ABCD, IndirectMemory_ExtendBitSet_Carry_NoneZero_CorrectResult)
{
	// Configure the operation in memory
	m68_mmu_initialise();

	uint8_t *ptr = m68_mmu_page_alloc(0x0000);
	*(ptr + 0) = 0xC1;
	*(ptr + 1) = 0x09;
	*(ptr + 0x0F) = 0x90;
	*(ptr + 0x1F) = 0x10;

	// Configure the CPU registers.
	CPU68.PC.value = 0x0000;
	CPU68.A[0].value = 0x10;
	CPU68.A[1].value = 0x20;
	CPU68.CCR.bitmask.user.Z = 1;
	CPU68.CCR.bitmask.user.X = 1;

	// Perform the operation and check if the results are as expected.
	abcd_m8_m8();

	ASSERT_EQ(*(ptr + 0x0F), 0x90);
	ASSERT_EQ(*(ptr + 0x1F), 0x01);
	ASSERT_EQ(CPU68.A[0].value, 0x0F);
	ASSERT_EQ(CPU68.A[1].value, 0x1F);
	ASSERT_EQ(CPU68.CCR.bitmask.user.X, 1);
	ASSERT_EQ(CPU68.CCR.bitmask.user.Z, 0);
	ASSERT_EQ(CPU68.CCR.bitmask.user.C, 1);
}

TEST_CASE(ABCD, IndirectMemory_ExtendBitSet_Carry_Zero_CorrectResult)
{
	// Configure the operation in memory
	m68_mmu_initialise();

	uint8_t *ptr = m68_mmu_page_alloc(0x0000);
	*(ptr + 0) = 0xC1;
	*(ptr + 1) = 0x09;
	*(ptr + 0x0F) = 0x90;
	*(ptr + 0x1F) = 0x10;

	// Configure the CPU registers.
	CPU68.PC.value = 0x0000;
	CPU68.A[0].value = 0x10;
	CPU68.A[1].value = 0x20;
	CPU68.CCR.bitmask.user.Z = 1;
	CPU68.CCR.bitmask.user.X = 0;

	// Perform the operation and check if the results are as expected.
	abcd_m8_m8();

	ASSERT_EQ(*(ptr + 0x0F), 0x90);
	ASSERT_EQ(*(ptr + 0x1F), 0x00);
	ASSERT_EQ(CPU68.A[0].value, 0x0F);
	ASSERT_EQ(CPU68.A[1].value, 0x1F);
	ASSERT_EQ(CPU68.CCR.bitmask.user.X, 1);
	ASSERT_EQ(CPU68.CCR.bitmask.user.Z, 1);
	ASSERT_EQ(CPU68.CCR.bitmask.user.C, 1);
}

#endif