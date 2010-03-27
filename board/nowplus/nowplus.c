/*
 * (C) Copyright 2004-2008
 * Texas Instruments, <www.ti.com>
 *
 * Author :
 *	Sunil Kumar <sunilsaini05@gmail.com>
 *	Shashi Ranjan <shashiranjanmca05@gmail.com>
 *
 * Derived from Beagle Board and 3430 SDP code by
 *	Richard Woodruff <r-woodruff2@ti.com>
 *	Syed Mohammed Khasim <khasim@ti.com>
 *
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
#include <common.h>
#include <twl4030.h>
#include <asm/io.h>
#include <asm/arch/mux.h>
#include <asm/arch/sys_proto.h>
#include <asm/arch/gpio.h>
#include <asm/mach-types.h>
#include "nowplus.h"

/*
 * Routine: board_init
 * Description: Early hardware init.
 */
int board_init(void)
{
	DECLARE_GLOBAL_DATA_PTR;

	gpmc_init(); /* in SRAM or SDRAM, finish GPMC */
	/* board id for Linux */
	gd->bd->bi_arch_number = 1641;
	/* boot param addr */
	gd->bd->bi_boot_params = (OMAP34XX_SDRC_CS0 + 0x100);

	return 0;
}

/*
 * Routine: misc_init_r
 * Description: Configure board specific parts
 */
int misc_init_r(void)
{
	struct gpio *gpio1_base = (struct gpio *)OMAP34XX_GPIO1_BASE;
	struct gpio *gpio4_base = (struct gpio *)OMAP34XX_GPIO4_BASE;
	struct gpio *gpio5_base = (struct gpio *)OMAP34XX_GPIO5_BASE;
	struct gpio *gpio6_base = (struct gpio *)OMAP34XX_GPIO6_BASE;

	twl4030_power_init();

	/*
	 * GPIO1:21 -> gpio_021 (WiFi IRQ)
	 * GPIO1:22 -> gpio_022 (TWL5030 MSECURE)
	 * GPIO4:03 -> gpio_099 (LCD reg. reset)
	 * GPIO5:23 -> gpio_151 (RGB LED enable)
	 * GPIO5:27 -> gpio_155 (moviNAND enable)
	 * GPIO6:00 -> gpio_160 (WiFi enable)
	 * GPIO6:01 -> gpio_161 (LCD id enable)
	 * GPIO6:10 -> gpio_170 (MLCD reset)
	 */

	/* GPIO 1 */
	writel(~(GPIO22), &gpio1_base->oe);
	writel(GPIO22, &gpio1_base->setdataout);

	/* GPIO 4 */
	writel(~(GPIO3), &gpio4_base->oe);

	/* GPIO 5 */
	writel(~(GPIO23 | GPIO27), &gpio5_base->oe);
	writel(GPIO27, &gpio5_base->setdataout);

	/* GPIO 6 */
	writel(~(GPIO0 | GPIO1 | GPIO10), &gpio6_base->oe);
	writel(GPIO0, &gpio6_base->setdataout);
	//writel(GPIO10, &gpio6_base->cleardataout);

	dieid_num_r();

	return 0;
}

/*
 * Routine: set_muxconf_regs
 * Description: Setting up the configuration Mux registers specific to the
 *		hardware. Many pins need to be moved from protect to primary
 *		mode.
 */
void set_muxconf_regs(void)
{
	MUX_NOWPLUS();
}
