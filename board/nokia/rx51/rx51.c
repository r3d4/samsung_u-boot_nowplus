/*
 * (C) Copyright 2011-2012
 * Pali Rohár <pali.rohar@gmail.com>
 *
 * (C) Copyright 2010
 * Alistair Buxton <a.j.buxton@gmail.com>
 *
 * Derived from Beagle Board and 3430 SDP code:
 * (C) Copyright 2004-2008
 * Texas Instruments, <www.ti.com>
 *
 * Author :
 *	Sunil Kumar <sunilsaini05@gmail.com>
 *	Shashi Ranjan <shashiranjanmca05@gmail.com>
 *
 *	Richard Woodruff <r-woodruff2@ti.com>
 *	Syed Mohammed Khasim <khasim@ti.com>
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
#include <i2c.h>
#include <video_fb.h>
#include <asm/io.h>
#include <asm/bitops.h>
#include <asm/mach-types.h>
#include <asm/arch/mux.h>
#include <asm/arch/sys_proto.h>
#include <asm/arch/mmc_host_def.h>

#include "rx51.h"

DECLARE_GLOBAL_DATA_PTR;

GraphicDevice gdev;

const omap3_sysinfo sysinfo = {
	DDR_STACKED,
	"Nokia RX-51",
	"OneNAND"
};

/*
 * Routine: board_init
 * Description: Early hardware init.
 */
int board_init(void)
{
	gpmc_init(); /* in SRAM or SDRAM, finish GPMC */
	/* board id for Linux */
	gd->bd->bi_arch_number = MACH_TYPE_NOKIA_RX51;
	/* boot param addr */
	gd->bd->bi_boot_params = OMAP34XX_SDRC_CS0 + 0x100;

	return 0;
}

/*
 * Routine: video_hw_init
 * Description: Set up the GraphicDevice depending on sys_boot.
 */
void *video_hw_init(void)
{
	/* fill in Graphic Device */
	gdev.frameAdrs = 0x8f9c0000;
	gdev.winSizeX = 800;
	gdev.winSizeY = 480;
	gdev.gdfBytesPP = 2;
	gdev.gdfIndex = GDF_16BIT_565RGB;
	memset((void *)gdev.frameAdrs, 0, 0xbb800);
	return (void *) &gdev;
}

/*
 * Routine: twl4030_regulator_set_mode
 * Description: Set twl4030 regulator mode over i2c powerbus.
 */
static void twl4030_regulator_set_mode(u8 id, u8 mode)
{
	u16 msg = MSG_SINGULAR(DEV_GRP_P1, id, mode);
	twl4030_i2c_write_u8(TWL4030_CHIP_PM_MASTER, msg >> 8,
			TWL4030_PM_MASTER_PB_WORD_MSB);
	twl4030_i2c_write_u8(TWL4030_CHIP_PM_MASTER, msg & 0xff,
			TWL4030_PM_MASTER_PB_WORD_LSB);
}

/*
 * Routine: misc_init_r
 * Description: Configure board specific parts.
 */
int misc_init_r(void)
{
	char buf[12];
	u8 state;

	/* initialize twl4030 power managment */
	twl4030_power_init();

	/* set VSIM to 1.8V */
	twl4030_pmrecv_vsel_cfg(TWL4030_PM_RECEIVER_VSIM_DEDICATED,
				TWL4030_PM_RECEIVER_VSIM_VSEL_18,
				TWL4030_PM_RECEIVER_VSIM_DEV_GRP,
				TWL4030_PM_RECEIVER_DEV_GRP_P1);

	/* store I2C access state */
	twl4030_i2c_read_u8(TWL4030_CHIP_PM_MASTER, &state,
			TWL4030_PM_MASTER_PB_CFG);

	/* enable I2C access to powerbus (needed for twl4030 regulator) */
	twl4030_i2c_write_u8(TWL4030_CHIP_PM_MASTER, 0x02,
			TWL4030_PM_MASTER_PB_CFG);

	/* set VAUX3, VSIM and VMMC1 state to active - enable eMMC memory */
	twl4030_regulator_set_mode(RES_VAUX3, RES_STATE_ACTIVE);
	twl4030_regulator_set_mode(RES_VSIM, RES_STATE_ACTIVE);
	twl4030_regulator_set_mode(RES_VMMC1, RES_STATE_ACTIVE);

	/* restore I2C access state */
	twl4030_i2c_write_u8(TWL4030_CHIP_PM_MASTER, state,
			TWL4030_PM_MASTER_PB_CFG);

	/* set env variable rx51_kernaddr for calculated address of kernel */
	sprintf(buf, "%#x", rx51_kernaddr);
	setenv("rx51_kernaddr", buf);

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
	MUX_RX51();
}

static unsigned long int twl_wd_time; /* last time of watchdog reset */
static unsigned long int twl_i2c_lock;

/*
 * Routine: hw_watchdog_reset
 * Description: Reset timeout of twl4030 watchdog.
 */
void hw_watchdog_reset(void)
{
	u8 timeout = 0;

	/* do not reset watchdog too often - max every 4s */
	if (get_timer(twl_wd_time) < 4 * CONFIG_SYS_HZ)
		return;

	/* localy lock twl4030 i2c bus */
	if (test_and_set_bit(0, &twl_i2c_lock))
		return;

	/* read actual watchdog timeout */
	twl4030_i2c_read_u8(TWL4030_CHIP_PM_RECEIVER, &timeout,
			TWL4030_PM_RECEIVER_WATCHDOG_CFG);

	/* timeout 0 means watchdog is disabled */
	/* reset watchdog timeout to 31s (maximum) */
	if (timeout != 0)
		twl4030_i2c_write_u8(TWL4030_CHIP_PM_RECEIVER, 31,
				TWL4030_PM_RECEIVER_WATCHDOG_CFG);

	/* store last watchdog reset time */
	twl_wd_time = get_timer(0);

	/* localy unlock twl4030 i2c bus */
	test_and_clear_bit(0, &twl_i2c_lock);
}

/*
 * TWL4030 keypad handler for cfb_console
 */

static const char keymap[] = {
	/* normal */
	'q',  'o',  'p',  ',', '\b',    0,  'a',  's',
	'w',  'd',  'f',  'g',  'h',  'j',  'k',  'l',
	'e',  '.',    0,  '\r',   0,  'z',  'x',  'c',
	'r',  'v',  'b',  'n',  'm',  ' ',  ' ',    0,
	't',    0,    0,    0,    0,    0,    0,    0,
	'y',    0,    0,    0,    0,    0,    0,    0,
	'u',    0,    0,    0,    0,    0,    0,    0,
	'i',    5,    6,    0,    0,    0,    0,    0,
	/* fn */
	'1',  '9',  '0',  '=', '\b',    0,  '*',  '+',
	'2',  '#',  '-',  '_',  '(',  ')',  '&',  '!',
	'3',  '?',  '^', '\r',    0,  156,  '$',  238,
	'4',  '/', '\\',  '"', '\'',  '@',    0,  '<',
	'5',  '|',  '>',    0,    0,    0,    0,    0,
	'6',    0,    0,    0,    0,    0,    0,    0,
	'7',    0,    0,    0,    0,    0,    0,    0,
	'8',   16,   17,    0,    0,    0,    0,    0,
};

static u8 keys[8];
static u8 old_keys[8] = {0, 0, 0, 0, 0, 0, 0, 0};
#define KEYBUF_SIZE 32
static u8 keybuf[KEYBUF_SIZE];
static u8 keybuf_head;
static u8 keybuf_tail;

/*
 * Routine: rx51_kp_init
 * Description: Initialize HW keyboard.
 */
int rx51_kp_init(void)
{
	int ret = 0;
	u8 ctrl;
	ret = twl4030_i2c_read_u8(TWL4030_CHIP_KEYPAD, &ctrl,
		TWL4030_KEYPAD_KEYP_CTRL_REG);

	if (!ret) {
		/* turn on keyboard and use hardware scanning */
		ctrl |= TWL4030_KEYPAD_CTRL_KBD_ON;
		ctrl |= TWL4030_KEYPAD_CTRL_SOFT_NRST;
		ctrl |= TWL4030_KEYPAD_CTRL_SOFTMODEN;
		ret |= twl4030_i2c_write_u8(TWL4030_CHIP_KEYPAD, ctrl,
					TWL4030_KEYPAD_KEYP_CTRL_REG);
		/* enable key event status */
		ret |= twl4030_i2c_write_u8(TWL4030_CHIP_KEYPAD, 0xfe,
					TWL4030_KEYPAD_KEYP_IMR1);
		/* enable interrupt generation on rising and falling */
		/* this is a workaround for qemu twl4030 emulation */
		ret |= twl4030_i2c_write_u8(TWL4030_CHIP_KEYPAD, 0x57,
					TWL4030_KEYPAD_KEYP_EDR);
		/* enable ISR clear on read */
		ret |= twl4030_i2c_write_u8(TWL4030_CHIP_KEYPAD, 0x05,
					TWL4030_KEYPAD_KEYP_SIH_CTRL);
	}
	return ret;
}

static void rx51_kp_fill(u8 k, u8 mods)
{
	if (!(mods & 2) && (k == 18 || k == 31 || k == 33 || k == 34)) {
		/* cursor keys, without fn */
		keybuf[keybuf_tail++] = '\e';
		keybuf_tail %= KEYBUF_SIZE;
		keybuf[keybuf_tail++] = '[';
		keybuf_tail %= KEYBUF_SIZE;
		if (k == 18) /* up */
			keybuf[keybuf_tail++] = 'A';
		else if (k == 31) /* left */
			keybuf[keybuf_tail++] = 'D';
		else if (k == 33) /* down */
			keybuf[keybuf_tail++] = 'B';
		else if (k == 34) /* right */
			keybuf[keybuf_tail++] = 'C';
		keybuf_tail %= KEYBUF_SIZE;
		return;
	}

	if (mods & 2) { /* fn */
		k = keymap[k+64];
	} else {
		k = keymap[k];
		if (mods & 1) { /* ctrl */
			if (k >= 'a' && k <= 'z')
				k -= 'a' - 1;
		}
		if (mods & 4) { /* shift */
			if (k >= 'a' && k <= 'z')
				k += 'A' - 'a';
			else if (k == '.')
				k = ':';
			else if (k == ',')
				k = ';';
		}
	}
	keybuf[keybuf_tail++] = k;
	keybuf_tail %= KEYBUF_SIZE;
}

/*
 * Routine: rx51_kp_tstc
 * Description: Test if key was pressed (from buffer).
 */
int rx51_kp_tstc(void)
{
	u8 c, r, dk, i;
	u8 intr;
	u8 mods;

	/* localy lock twl4030 i2c bus */
	if (test_and_set_bit(0, &twl_i2c_lock))
		return 0;

	/* twl4030 remembers up to 2 events */
	for (i = 0; i < 2; i++) {

		/* check interrupt register for events */
		twl4030_i2c_read_u8(TWL4030_CHIP_KEYPAD, &intr,
				TWL4030_KEYPAD_KEYP_ISR1+(2*i));

		if (intr&1) { /* got an event */

			/* read the key state */
			i2c_read(TWL4030_CHIP_KEYPAD,
				TWL4030_KEYPAD_FULL_CODE_7_0, 1, keys, 8);

			/* cut out modifier keys from the keystate */
			mods = keys[4] >> 4;
			keys[4] &= 0x0f;

			for (c = 0; c < 8; c++) {

				/* get newly pressed keys only */
				dk = ((keys[c] ^ old_keys[c])&keys[c]);
				old_keys[c] = keys[c];

				/* fill the keybuf */
				for (r = 0; r < 8; r++) {
					if (dk&1)
						rx51_kp_fill((c*8)+r, mods);
					dk = dk >> 1;
				}

			}

		}

	}

	/* localy unlock twl4030 i2c bus */
	test_and_clear_bit(0, &twl_i2c_lock);

	return (KEYBUF_SIZE + keybuf_tail - keybuf_head)%KEYBUF_SIZE;
}

/*
 * Routine: rx51_kp_getc
 * Description: Get last pressed key (from buffer).
 */
int rx51_kp_getc(void)
{
	keybuf_head %= KEYBUF_SIZE;
	while (!rx51_kp_tstc()) {
		udelay(1);
		hw_watchdog_reset();
	}
	return keybuf[keybuf_head++];
}

/*
 * Routine: board_mmc_init
 * Description: Initialize mmc devices.
 */
int board_mmc_init(bd_t *bis)
{
	omap_mmc_init(0);
	omap_mmc_init(1);
	return 0;
}
