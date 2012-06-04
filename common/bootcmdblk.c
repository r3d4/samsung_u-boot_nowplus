/*
 * (C) Copyright 2010
 * Texas Instruments, <www.ti.com>
 * sebastien griffoul <s-griffoul@ti.com> 
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
#include <bootcmdblk.h>
#include <mmc.h>

#ifdef CONFIG_RECOVERYCMD

/* Global data */
int  bootcmdblk;


/*************************************************************************
 *  parse_bootloader_message
 *
 *  
 ************************************************************************/
bootcmdblk_cmd bootcmdblk_parse_cmd(void)
{
	bootcmdblk_cmd	cmd;

	printf("Parsing Bootloader Control Command (BCB)");
    
    switch(bootmode_get_cmd())
    {
        case 'r':
            printf(" ----> Recovery mode\n");
            cmd = BOOTCMDBLK_RECOVERY;	
            break;
        case 'b':
            printf(" ----> Bootloader mode\n"); //should show bootloader to user
            cmd = BOOTCMDBLK_BOOTLOADER;	
            break;
       default:
       		printf("----> No valid command: performing normal boot\n");
            cmd = BOOTCMDBLK_NORMAL;	
            break;
    }

	return cmd;
}
#endif /* CONFIG_READ_BCB */
