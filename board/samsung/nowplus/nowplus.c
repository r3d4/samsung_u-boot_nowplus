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
#include <asm/arch/gpio.h>
#include <asm/arch/mmc_host_def.h>

#include "nowplus.h"


DECLARE_GLOBAL_DATA_PTR;

GraphicDevice gdev;

const omap3_sysinfo sysinfo = {
	DDR_STACKED,
    "OMAP3 Nowplus board",
	"OneNAND"
};

/*
 * Routine: board_init
 * Description: Early hardware init.
 */
int board_init(void)
{
    /* disabled, already setup by Samung SBL */
	//gpmc_init();

	/* board id for Linux */
	gd->bd->bi_arch_number = MACH_TYPE_OMAP3_NOWPLUS;
	/* boot param addr */
	gd->bd->bi_boot_params = OMAP34XX_SDRC_CS0 + 0x100;

	return 0;
}

void nowplus_lcd_disable(void)
{
    u32 memsize = gdev.winSizeX*gdev.winSizeY*gdev.gdfBytesPP;
    memset((void *)gdev.frameAdrs, 0x00, memsize);

    //disable graphics pipeline
    writel(readl(DISPC_GFX_ATTRIBUTES) & ~(0x1), DISPC_GFX_ATTRIBUTES);

#if 0
     //disable display
    writel(readl(DISPC_CONTROL) & ~0x3, DISPC_CONTROL);
#endif
}
		// u32 l;

		// prcm_offs = OMAP3430_GR_MOD;
		// l = ('B' << 24) | ('M' << 16) | (cmd ? (u8)*cmd : 0);
		// /* Reserve the first word in scratchpad for communicating
		 // * with the boot ROM. A pointer to a data structure
		 // * describing the boot process can be stored there,
		 // * cf. OMAP34xx TRM, Initialization / Software Booting
		 // * Configuration. */
/* get boot mode store in OMAP343X_SCRATCHPAD by linux kernel
 -> can boot direct to recovery

'r':  reboot mode = recovery
'f':  reboot mode = fota
'L':  reboot mode = Lockup
'U':  reboot mode = Lockup
't':  reboot mode = shutdown with TA
'u':  reboot mode = shutdown with USB
'j':  reboot mode = shutdown with JIG
'd':  reboot mode = download

 */
char bootmode_get_cmd()
{
    u32 tmp = readl( OMAP343X_SCRATCHPAD + 4);

    if((tmp>>24&0xff == 'B') && (tmp>>24&0xff == 'M'))
        return tmp&0xff;
    else
        return 0;
}

#ifdef CONFIG_VIDEO
/*
 * Routine: video_hw_init
 * Description: Set up the GraphicDevice depending on sys_boot.
 */
void *video_hw_init(void)
{
    u32 fbaddr;
    u32 BytesPP = 4;    // SBL inits to 24bit color packed to 32bit
    u32 memsize = 800*480*BytesPP;

      //Get framebuffer addr, set by SBL
    fbaddr = readl( DISPC_GFX_BA0);

	/* fill in Graphic Device */
	gdev.frameAdrs = fbaddr;
	gdev.winSizeX = 480;
	gdev.winSizeY = 800;
	gdev.gdfBytesPP = BytesPP;
	gdev.gdfIndex = GDF_32BIT_X888RGB;   //GFXFORMAT: 0x8: RGB 24 (un-packed in 32-bit container)
	memset((void *)gdev.frameAdrs, 0x00, memsize);
	return (void *) &gdev;
}

#ifdef CONFIG_CONSOLE_EXTRA_INFO
void video_get_info_str(int line_number, char *info)
{
    u32 srev = get_cpu_rev();

    switch (line_number) {
    case 2:
        sprintf(info, " Samsung Nowplus Board");
        break;
     case 3:
         sprintf(info, " CPU: TI OMAP rev %d", get_cpu_rev());
        break;
     case 4:
        sprintf(info, " Boot mode: %c", bootmode_get_cmd());
        break;
     case 6:
        sprintf(info, " 2012 - r3d4 edition");
        break;
     default:
        info[0] = 0;
    }
}
#endif
#endif
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
#define EN_MMC1         24
#define CM_ICLKEN1_CORE 0x48004A10
#define CM_FCLKEN1_CORE 0x48004A00
/*
 * Routine: misc_init_r
 * Description: Configure board specific parts.
 */
int misc_init_r(void)
{

	struct gpio *gpio5_base = (struct gpio *)OMAP34XX_GPIO5_BASE;
	struct control_prog_io *prog_io_base = (struct control_prog_io *)OMAP34XX_CTRL_BASE;

	char buf[12];
	u8 state;
    u32 oe;
    u32 dat;

    /*enable MMC CLKs */
    // writel(readl(CM_ICLKEN1_CORE) |(1<<EN_MMC1), CM_ICLKEN1_CORE);  // enable interface clk
    // writel(readl(CM_FCLKEN1_CORE) |(1<<EN_MMC1), CM_FCLKEN1_CORE);  // enable functional clk

	/* initialize twl4030 power managment */
	twl4030_power_init();

    // oe = readl(&gpio5_base->oe);
    // dat = readl(&gpio5_base->setdataout);
    //switch to OMAP USB
    // writel(readl(&gpio5_base->setdataout) & ~(GPIO150), &gpio5_base->setdataout);   // lo
    // writel(readl(&gpio5_base->oe) & ~(GPIO150), &gpio5_base->oe);                   //output

	/* set env variable nowplus_kernaddr for calculated address of kernel */
	sprintf(buf, "%#x", nowplus_kernaddr);
	setenv("nowplus_kernaddr", buf);

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
// only mux additional pins used by u-boot (MMC, ...)
// basic pin muxing already done by Samsung SBL
// we do complete muxing at kernel
	MUX_NOWPLUS();
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
   KEY_FRONT,           KEY_PHONE,      KEY_EXIT,
   KEY_SEARCH,          0,              KEY_VOLUMEUP,
   KEY_CAMERA_FOCUS,    KEY_CAMERA,     KEY_VOLUMEDOWN
};

static u8 keys[8];
static u8 old_keys[8] = {0, 0, 0, 0, 0, 0, 0, 0};
#define KEYBUF_SIZE 32
static u8 keybuf[KEYBUF_SIZE];
static u8 keybuf_head;
static u8 keybuf_tail;

/*
 * Routine: nowplus_kp_init
 * Description: Initialize HW keyboard.
 */
int nowplus_kp_init(void)
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

static void nowplus_kp_fill(u8 k)
{
	if ((k == 5 || k == 8)) {
		/* volume keys */
		keybuf[keybuf_tail++] = '\e';
		keybuf_tail %= KEYBUF_SIZE;
		keybuf[keybuf_tail++] = '[';
		keybuf_tail %= KEYBUF_SIZE;
		if (k == 5) /* up */
			keybuf[keybuf_tail++] = 'A';
		else  /* down */
			keybuf[keybuf_tail++] = 'B';
		keybuf_tail %= KEYBUF_SIZE;
		return;
	}
	keybuf[keybuf_tail++] = keymap[k];
	keybuf_tail %= KEYBUF_SIZE;
}

/*
 * Routine: nowplus_kp_tstc
 * Description: Test if key was pressed (from buffer).
 */
int nowplus_kp_tstc(void)
{
	u8 c, r, dk, i;
	u8 intr;

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

			for (c = 0; c < 3; c++) {

				/* get newly pressed keys only */
				dk = ((keys[c] ^ old_keys[c])&keys[c]);
				old_keys[c] = keys[c];

				/* fill the keybuf */
				for (r = 0; r < 3; r++) {
					if (dk&1)
						nowplus_kp_fill((c*3)+r);
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
 * Routine: nowplus_kp_getc
 * Description: Get last pressed key (from buffer).
 */
int nowplus_kp_getc(void)
{
	keybuf_head %= KEYBUF_SIZE;
	while (!nowplus_kp_tstc()) {
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
	//omap_mmc_init(1);
	return 0;
}
