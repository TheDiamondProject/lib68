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

#include "cpu/mmu.h"
#include <stdio.h>
#include <stdlib.h>

#define MMU_PAGE_DIR_MAX_ENTRIES	1024
#define MMU_PAGE_TABLE_MAX_ENTRIES 	1024

// MARK: - Initialisation & Destruction

int m68_mmu_initialise(void)
{
	/* Ensure the prior page directory is destroyed first */
	// m68_mmu_destroy();

	/* Initialise the page directory, and setup the initial page table and 
	 * page, to ensure we have at least 4KiB of accessible memory. */
	MMU_PAGE_DIR = calloc(MMU_PAGE_DIR_MAX_ENTRIES, sizeof(union m68_mmu_page_table_entry));
	if (MMU_PAGE_DIR == NULL) {
		return 1;
	}
	m68_mmu_page_alloc(0x00000000);

	return 0;
}

void m68_mmu_destroy(void)
{
	if ( MMU_PAGE_DIR ) {
		/* Iterate over all tables and then over all tables and release 
		 * everything. */
		for (int i = 0; i < MMU_PAGE_DIR_MAX_ENTRIES; ++i) {
			/* Skip if the table is not present in the directory */
			if (!MMU_PAGE_DIR[i].field.present) {
				continue;
			}

			/* Fetch the page table */
			union m68_mmu_page_entry *PAGE_TABLE = (void *)(MMU_PAGE_DIR[i].field.address << 4);

			/* Iterate over all pages in the table */
			for (int j = 0; j < MMU_PAGE_TABLE_MAX_ENTRIES; ++j) {
				if (!PAGE_TABLE[i].field.present) {
					continue;
				}

				/* Fetch the page */
				void *PAGE = (void *)(PAGE_TABLE[i].field.address << 4);
				free(PAGE);
			}

			free(PAGE_TABLE);
		}

		free(MMU_PAGE_DIR);
		MMU_PAGE_DIR = NULL;
	}
}

// MARK: - Page Management

void *m68_mmu_page_alloc(uint32_t address)
{
	union m68_mmu_page_entry *table = NULL;
	void *page = NULL;

	/* First determine the page table and the page that the address relates
	 * to. */
	uint32_t dir_idx = (address >> 22) & 0x3FF;
	uint32_t table_idx = (address >> 12) & 0x3FF;

	/* Now check if a table already exists. If not create it. To do this we need
	 * to request an allocation for the page and then ensure it is aligned to a
	 * 16 byte boundary. */
	if (!MMU_PAGE_DIR[dir_idx].field.present) {
		table = calloc(MMU_PAGE_TABLE_MAX_ENTRIES + 4, sizeof(union m68_mmu_page_entry));
		uintptr_t address = (uintptr_t)table;
		if (address & 0xF) {
			address = ((address + 0x10) & ~0xF);
			table = (void *)address;
		}

		MMU_PAGE_DIR[dir_idx].field.address = (address >> 2) & ~0xF;
		MMU_PAGE_DIR[dir_idx].field.present = 1;
	} else {
		table = (void *)(MMU_PAGE_DIR[dir_idx].field.address << 2);
	}

	/* Now check for the presence of the desired page in the table. If the page
	 * is not there then allocate it. */
	if (!table[table_idx].field.present) {
		page = calloc(0x1000, 1);
		uintptr_t address = (uintptr_t)page;
		if (address & 0xF) {
			address = ((address + 0x10) & ~0xF);
			page = (void *)address;
		}

		table[table_idx].field.address = (address >> 2) & ~0xF;
		table[table_idx].field.present = 1;
	} else {
		page = (void *)(table[table_idx].field.address << 2);
	}

	return page;
}