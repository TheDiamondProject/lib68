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

#if !defined(lib68_MemoryManagementUnit)
#define lib68_MemoryManagementUnit

union m68_mmu_page_table_entry {
	uintptr_t value;
	struct {
		uintptr_t present:1;
		uintptr_t dirty:1;
		uintptr_t reserved:2;
		uintptr_t address:60;
	} field __attribute__((packed));
};

union m68_mmu_page_entry {
	uintptr_t value;
	struct {
		uintptr_t present:1;
		uintptr_t dirty:1;
		uintptr_t reserved:2;
		uintptr_t address:60;
	} field __attribute__((packed));
};

extern union m68_mmu_page_table_entry *MMU_PAGE_DIR;

/* Initialise memory with the specified number of bytes. As there can only be
 * a single memory structure, it is initialised into a global variable.
 * Returns 0 on success. */
int m68_mmu_initialise(void);

/* Destroy memory. This is part of the clean up process for a given emulation 
 * instance. */
void m68_mmu_destroy(void);

/* Allocate the page at the specified memory address if it isn't already 
 * allocated. */
void *m68_mmu_page_alloc(uint32_t address);

/* Write byte to the specified address. */
void m68_mmu_write_byte(uint32_t address, uint8_t value);

/* Write word to the specified address. */
void m68_mmu_write_word(uint32_t address, uint16_t value);

/* Write long to the specified address. */
void m68_mmu_write_long(uint32_t address, uint32_t value);

#endif