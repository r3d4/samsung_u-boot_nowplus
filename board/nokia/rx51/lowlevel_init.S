/*
 * (C) Copyright 2011-2012
 * Pali Rohár <pali.rohar@gmail.com>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#define KERNEL_OFFSET 0x40000
#define KERNEL_MAXSIZE 0x200000	/* 2MB */

startaddr:		/* address where should be u-boot after relocation */
	.word CONFIG_SYS_TEXT_BASE

relocaddr:		/* address of this relocaddr section after relocation */
	.word .		/* address of section (calculated at compile time) */

.global rx51_kernaddr
rx51_kernaddr:
kernaddr:		/* stored attached kernel address */
	.word CONFIG_SYS_TEXT_BASE + KERNEL_OFFSET

/*
 * Routine: save_boot_params (called after reset from start.S)
 * Description: Save atag address and attached kernel address.
 *              Move u-boot to address CONFIG_SYS_TEXT_BASE
 */

.global save_boot_params
save_boot_params:	/* function save_boot_params, called after reset */
	adr	r0, relocaddr	/* r0 - address of section relocaddr */
	ldr	r1, relocaddr	/* r1 - address of relocaddr after relocation */
	sub	r0, r0, r1	/* r1 - calculated offset for relocation */
	ldr	r1, startaddr	/* r1 - address of u-boot after relocation */
	add	r0, r0, r1	/* r0 - address where is u-boot now */
				/* (address after relocation + offset) */

	cmp	r0, r1
	bne	reloc	/* relocate if u-boot is not at correct address */
	bx	lr	/* else return (to reset, relocation is not needed) */

reloc:
	add	r2, r0, #KERNEL_OFFSET	/* r2 - address of attached kernel */
					/* (u-boot address + kernel offset) */
	str	r2, kernaddr		/* store kernel address to memory */
	add	r2, r0, #KERNEL_MAXSIZE	/* r2 - address - end of kernel image */
					/* (u-boot address + kernel max size */

loop:
	ldmia	r0!, {r3 - r10}		/* copy from source address (r0) */
	stmia	r1!, {r3 - r10}		/* copy to destination address (r1) */
	cmp	r0, r2
	bne	loop			/* until end of kernel image (r2) */

	ldr	pc, startaddr		/* jump to start section */
/* (where should be u-boot after relocation) and restart u-boot */
