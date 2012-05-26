/*
 * (C) Copyright 2011-2012
 * Pali Rohár <pali.rohar@gmail.com>
 *
 * (C) Copyright 2010
 * Alistair Buxton <a.j.buxton@gmail.com>
 *
 * Derived from Beagle Board code:
 * (C) Copyright 2006-2008
 * Texas Instruments.
 * Richard Woodruff <r-woodruff2@ti.com>
 * Syed Mohammed Khasim <x0khasim@ti.com>
 *
 * Configuration settings for the Nokia RX-51 aka N900.
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __CONFIG_H
#define __CONFIG_H

/*
 * High Level Configuration Options
 */

#define CONFIG_OMAP			/* in a TI OMAP core */
#define CONFIG_OMAP34XX			/* which is a 34XX */
#define CONFIG_OMAP3430			/* which is in a 3430 */
#define CONFIG_OMAP3_NOWPLUS		/* working with RX51 */
#define CONFIG_SYS_L2CACHE_OFF		/* pretend there is no L2 CACHE */

/* It doesn't really matter what we set this to. NOLO will load u-boot.bin
 * in a random place anyway, and we have to copy.
 */
#define CONFIG_SYS_TEXT_BASE	0x80008000

#define CONFIG_SDRC			/* The chip has SDRC controller */

#include <asm/arch/cpu.h>		/* get chip and board defs */
#include <asm/arch/omap3.h>
#include <asm/arch/mem.h>

/*
 * Display CPU and Board information
 */
#define CONFIG_DISPLAY_CPUINFO
#define CONFIG_DISPLAY_BOARDINFO

/* Clock Defines */
#define V_OSCK			26000000	/* Clock output from T2 */
#define V_SCLK			(V_OSCK >> 1)

#undef CONFIG_USE_IRQ				/* no support for IRQs */
#define CONFIG_MISC_INIT_R
//#define CONFIG_SKIP_LOWLEVEL_INIT		/* Samsung SBL setup everything */
#define CONFIG_SKIP_DPLL4_INIT                 /* don't init/change DPLL4: fix display issues */


#define CONFIG_CMDLINE_TAG	/* enable passing kernel command line string */
#define CONFIG_INITRD_TAG			/* enable passing initrd */
#define CONFIG_SETUP_MEMORY_TAGS		/* enable memory tag */

/*
 * Size of malloc() pool
 */
#define CONFIG_ENV_SIZE			(128 << 10)	/* 128 KiB Sector */
#define CONFIG_UBI_SIZE			(512 << 10)	/* 512 KiB Sector */
#define CONFIG_SYS_MALLOC_LEN		(CONFIG_ENV_SIZE + CONFIG_UBI_SIZE + \
					(128 << 10))

/*
 * Hardware drivers
 */

/*
 * NS16550 Configuration
 */
#define V_NS16550_CLK		48000000		/* 48MHz (APLL96/2) */

#define CONFIG_SYS_NS16550
#define CONFIG_SYS_NS16550_SERIAL
#define CONFIG_SYS_NS16550_REG_SIZE	(-4)
#define CONFIG_SYS_NS16550_CLK		V_NS16550_CLK

/*
 * select serial console configuration
 */
#define CONFIG_CONS_INDEX		3
#define CONFIG_SYS_NS16550_COM3		OMAP34XX_UART3
#define CONFIG_SERIAL3			3		/* UART3 on RX-51 */

/* allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE
#define CONFIG_BAUDRATE			115200
#define CONFIG_SYS_BAUDRATE_TABLE {4800, 9600, 19200, 38400, 57600, 115200}
#define CONFIG_MMC
#define CONFIG_GENERIC_MMC
#define CONFIG_OMAP_HSMMC
#define CONFIG_DOS_PARTITION

/* DDR - Samsungs' unknown DDR */
#define CONFIG_OMAP3_SAMSUNG_DDR		1

/* USB */
// #define CONFIG_MUSB_UDC
// #define CONFIG_USB_OMAP3
// #define CONFIG_TWL4030_USB

/* USB device configuration */
// #define CONFIG_USB_DEVICE
// #define CONFIG_USB_TTY

#define CONFIG_USBD_VENDORID		0x04e8
#define CONFIG_USBD_PRODUCTID		0x6601
#define CONFIG_USBD_MANUFACTURER	"Samsung Electronics Co., Ltd"
#define CONFIG_USBD_PRODUCT_NAME	"Samsung GT-I8320"


#define CONFIG_SYS_CONSOLE_IS_IN_ENV
#define CONFIG_SYS_NO_FLASH

/* OneNand support is disabled, because U-Boot image is too big */
/* Uncomment next line to enable it */
/* #define ONENAND_SUPPORT */

/* commands to include */
#include <config_cmd_default.h>

#define CONFIG_CMD_EXT2			/* EXT2 Support */
#define CONFIG_CMD_EXT4			/* EXT4 Support */
#define CONFIG_CMD_FAT			/* FAT support */

#define CONFIG_CMD_I2C			/* I2C serial bus support */
#define CONFIG_CMD_MMC			/* MMC support */
#define CONFIG_CMD_GPIO			/* Enable gpio command */

#define CONFIG_CMDLINE_EDITING		/* add command line history */
#define CONFIG_AUTO_COMPLETE		/* add autocompletion support */

#define CONFIG_CMD_BOOTMENU		/* ANSI terminal Boot Menu */
#define CONFIG_CMD_CLEAR		/* ANSI terminal clear screen command */

#ifdef ONENAND_SUPPORT
#define CONFIG_CMD_ONENAND		/* NAND support */
#define CONFIG_CMD_MTDPARTS		/* mtd parts support */
#define CONFIG_CMD_UBI			/* UBI Support */
#define CONFIG_CMD_UBIFS		/* UBIFS Support */
#endif

#undef CONFIG_CMD_FPGA			/* FPGA configuration Support */
#undef CONFIG_CMD_IMI			/* iminfo */
#undef CONFIG_CMD_NET			/* bootp, tftpboot, rarpboot */
#undef CONFIG_CMD_NFS			/* NFS support */

#define CONFIG_OMAP3_SPI
#define CONFIG_HARD_I2C
#define CONFIG_SYS_I2C_SPEED		100000
#define CONFIG_SYS_I2C_SLAVE		1
#define CONFIG_SYS_I2C_BUS		0
#define CONFIG_SYS_I2C_BUS_SELECT	1
#define CONFIG_DRIVER_OMAP34XX_I2C	1

/*
 * TWL4030
 */
#define CONFIG_TWL4030_POWER
#define CONFIG_TWL4030_LED
#define CONFIG_TWL4030_KEYPAD

/*
 * Board NAND Info.
 */
#ifdef ONENAND_SUPPORT
#define PISMO1_NAND_SIZE		GPMC_SIZE_128M
#define PISMO1_ONEN_SIZE		GPMC_SIZE_128M
#define CONFIG_SYS_ONENAND_BASE		ONENAND_MAP
#define CONFIG_MTD_DEVICE
#define CONFIG_MTD_PARTITIONS
#define CONFIG_RBTREE
#define CONFIG_LZO
#define MTDIDS_DEFAULT			"onenand0=onenand"
#define MTDPARTS_DEFAULT		"mtdparts=onenand:128k(bootloader)," \
					"384k(config),256k(log),2m(kernel)," \
					"2m(initfs),-(rootfs)"
#else
#define MTDPARTS_DEFAULT
#endif

/* Watchdog support */
#define CONFIG_HW_WATCHDOG

/*
 * Framebuffer
 */
/* Video console */
#define CONFIG_VIDEO
#define CONFIG_CFB_CONSOLE
#define CONFIG_CFB_CONSOLE_ANSI	 /* Enable ANSI escape codes in framebuffer */
#define CONFIG_VIDEO_LOGO
#define CONFIG_VIDEO_BMP_LOGO
#define CONFIG_VIDEO_SW_CURSOR
#define CONFIG_CONSOLE_EXTRA_INFO
// #define CONFIG_VGA_AS_SINGLE_DEVICE
//#define CONFIG_SPLASH_SCREEN

/* functions for cfb_console */
#define VIDEO_KBD_INIT_FCT		nowplus_kp_init()
#define VIDEO_TSTC_FCT			nowplus_kp_tstc
#define VIDEO_GETC_FCT			nowplus_kp_getc
#ifndef __ASSEMBLY__
int nowplus_kp_init(void);
int nowplus_kp_tstc(void);
int nowplus_kp_getc(void);
#endif
//disable LCD controller to hide frambuffer garbage 
// #define DISABLE_LCD             nowplus_lcd_disable()
// #ifndef __ASSEMBLY__
// void nowplus_lcd_disable(void);
// #endif

/* Environment information */
#define CONFIG_EXTRA_ENV_SETTINGS \
	"mtdparts=" MTDPARTS_DEFAULT "\0" \
	"usbtty=cdc_acm\0" \
	"stdin=vga\0" \
	"stdout=vga\0" \
	"stderr=vga\0" \
	"setcon=setenv stdin ${con};" \
		"setenv stdout ${con};" \
		"setenv stderr ${con}\0" \
	"sercon=setenv con serial; run setcon\0" \
	"usbcon=setenv con usbtty; run setcon\0" \
	"vgacon=setenv con vga; run setcon\0" \
	"power=gpio input 24\0" \
	"switchmmc=mmc dev ${mmcnum}\0" \
	"kernaddr=0x82008000\0" \
	"initrdaddr=0x85008000\0" \
	"scriptaddr=0x87008000\0" \
    "fileload=${mmctype}load mmc ${mmcnum}:${mmcpart} " \
		"${loadaddr} ${mmcfile}\0" \
	"kernload=setenv loadaddr ${kernaddr};" \
		"setenv mmcfile ${mmckernfile};" \
		"run fileload\0" \
	"initrdload=setenv loadaddr ${initrdaddr};" \
		"setenv mmcfile ${mmcinitrdfile};" \
		"run fileload\0" \
	"scriptload=setenv loadaddr ${scriptaddr};" \
		"setenv mmcfile ${mmcscriptfile};" \
		"run fileload\0" \
     "scriptboot=echo Running ${mmcscriptfile} from mmc " \
		"${mmcnum}:${mmcpart} ...; source ${scriptaddr}\0" \
	"kernboot=echo Booting ${mmckernfile} from mmc " \
		"${mmcnum}:${mmcpart} ...; bootm ${kernaddr}\0" \
	"kerninitrdboot=echo Booting ${mmckernfile} ${mmcinitrdfile} from mmc "\
		"${mmcnum}:${mmcpart} ...; bootm ${kernaddr} ${initrdaddr}\0" \
	"attachboot=echo Booting attached kernel image ...;" \
		"bootm ${nowplus_kernaddr}\0" \
 	"attachboot_limo=echo Booting attached Limo kernel image ...;" \
		"setenv atagaddr 0x80000100;" \
		"bootm ${nowplus_kernaddr}\0" \
   "trymmcscriptboot=if run switchmmc; then " \
            "if run scriptload; then " \
                "run scriptboot;" \
            "fi;" \
        "fi\0" \
	"trymmckernboot=if run switchmmc; then " \
			"if run kernload; then " \
				"run kernboot;" \
			"fi;" \
		"fi\0" \
	"trymmckerninitrdboot=if run switchmmc; then " \
			"if run initrdload; then " \
				"if run kernload; then " \
					"run kerninitrdboot;" \
				"fi;" \
			"fi; " \
		"fi\0" \
    "trymmcpartboot=setenv mmcscriptfile boot/boot.scr; run trymmcscriptboot;" \
		"setenv mmckernfile boot/uImage; run trymmckernboot\0" \
	"trymmcallpartboot=setenv mmcpart 1; run trymmcpartboot;" \
		"setenv mmcpart 2; run trymmcpartboot;" \
		"setenv mmcpart 3; run trymmcpartboot;" \
		"setenv mmcpart 4; run trymmcpartboot\0" \
	"trymmcboot=if run switchmmc; then " \
			"setenv mmctype fat;" \
			"run trymmcallpartboot;" \
			"setenv mmctype ext2;" \
			"run trymmcallpartboot;" \
			"setenv mmctype ext4;" \
			"run trymmcallpartboot;" \
		"fi\0" \
	"emmcboot=setenv mmcnum 1; run trymmcboot\0" \
	"sdboot=setenv mmcnum 0; run trymmcboot\0" \
   	"mmcboot=echo Booting from mmc ...;" \
        "setenv mmcnum 0;setenv mmcpart 2;setenv mmctype ext2;" \
		"run trymmcpartboot\0" \
    "recovboot=echo Booting recovery ...;" \
        "setenv bootargs root=31:1 rootfstype=yaffs2 " \
        "mem=256M init=/init rootwait " \
        "videoout=omap_vout omap_vout.video1_numbuffers=6 " \
        "omap_vout.vid1_static_vrfb_alloc=y omapfb.vram=\"0:4M\";" \
		"run attachboot\0" \
    "nandboot=echo Booting from internal nand ...;" \
        "setenv bootargs root=31:2 rootfstype=yaffs2 " \
        "mem=256M init=/init rootwait " \
        "videoout=omap_vout omap_vout.video1_numbuffers=6 " \
        "omap_vout.vid1_static_vrfb_alloc=y omapfb.vram=\"0:4M\";" \
		"run attachboot\0" \
    "menucmd=bootmenu\0" \
	"bootmenu_0=SD card=run mmcboot\0" \
    "bootmenu_1=Nand=run nandboot\0" \
	"bootmenu_2=Recovery=run recovboot\0" \
	"bootmenu_3=U-Boot boot order=boot\0" \
	"bootmenu_delay=10\0" \
    ""

#define CONFIG_PREBOOT \
 		"setenv mmcnum 0; setenv mmcpart 1; setenv mmctype fat;" \
		"setenv mmcscriptfile bootmenu.scr;" \
		"run trymmcscriptboot;"

#define CONFIG_PREMONITOR \
	"echo Extra commands:;" \
	"echo run sercon - Use serial port for control.;" \
	"echo run usbcon - Use usbtty for control.;" \
	"echo run vgacon - Use framebuffer/keyboard.;" \
	"echo run sdboot - Boot from SD card slot.;" \
	"echo run emmcboot - Boot internal eMMC memory.;" \
	"echo run attachboot - Boot attached kernel image.;" \
	"echo"
 /*
    "bdinfo;" \
    "echo mm devices: ; mmc list; mmc dev;" \
    "ext2load mmc 0:2 0x84008000 boot/uImage;" \
*/
#define CONFIG_BOOTCOMMAND \
	"run mmcboot;" \
	"echo"
 
/*
#define CONFIG_BOOTCOMMAND \
	"run attachboot;" \
	"echo"
*/
/*    
#define CONFIG_BOOTCOMMAND \
		"bootm 0x86C30000"
*/

#define CONFIG_MENUCMD


/*
 * Miscellaneous configurable options
 */
#define CONFIG_SYS_LONGHELP			/* undef to save memory */
#define CONFIG_SYS_HUSH_PARSER			/* use "hush" command parser */
#define CONFIG_SYS_PROMPT_HUSH_PS2	"> "
#define CONFIG_SYS_PROMPT		"Samsung Nowplus # "
#define CONFIG_SYS_CBSIZE		256	/* Console I/O Buffer Size */
/* Print Buffer Size */
#define CONFIG_SYS_PBSIZE		(CONFIG_SYS_CBSIZE + \
						sizeof(CONFIG_SYS_PROMPT) + 16)
#define CONFIG_SYS_MAXARGS		16	/* max number of command args */
/* Boot Argument Buffer Size */
#define CONFIG_SYS_BARGSIZE		(CONFIG_SYS_CBSIZE)

#define CONFIG_SYS_MEMTEST_START	(OMAP34XX_SDRC_CS0)
#define CONFIG_SYS_MEMTEST_END		(OMAP34XX_SDRC_CS0 + 0x01F00000)/*31MB*/

/* default load address */
#define CONFIG_SYS_LOAD_ADDR		(OMAP34XX_SDRC_CS0)

/*
 * OMAP3 has 12 GP timers, they can be driven by the system clock
 * (12/13/16.8/19.2/38.4MHz) or by 32KHz clock. We use 13MHz (V_SCLK).
 * This rate is divided by a local divisor.
 */
#define CONFIG_SYS_TIMERBASE		(OMAP34XX_GPT2)
#define CONFIG_SYS_PTV			2	/* Divisor: 2^(PTV+1) => 8 */
#define CONFIG_SYS_HZ			1000

/*-----------------------------------------------------------------------
 * Stack sizes
 *
 * The stack sizes are set up in start.S using the settings below
 */
#define CONFIG_STACKSIZE		(128 << 10) /* regular stack 128 KiB */

/*-----------------------------------------------------------------------
 * Physical Memory Map
 */
#define CONFIG_NR_DRAM_BANKS	2
#define PHYS_SDRAM_1			OMAP34XX_SDRC_CS0
#define PHYS_SDRAM_1_SIZE	    (32 << 20)	/* at least 32 MiB */
#define PHYS_SDRAM_2		    OMAP34XX_SDRC_CS1


/*-----------------------------------------------------------------------
 * FLASH and environment organization
 */

#define CONFIG_ENV_IS_NOWHERE

#define CONFIG_SYS_SDRAM_BASE		PHYS_SDRAM_1
#define CONFIG_SYS_INIT_RAM_ADDR	0x4020f800
#define CONFIG_SYS_INIT_RAM_SIZE	0x800
#define CONFIG_SYS_INIT_SP_ADDR		(CONFIG_SYS_INIT_RAM_ADDR + \
			CONFIG_SYS_INIT_RAM_SIZE - GENERATED_GBL_DATA_SIZE)

#endif /* __CONFIG_H */
