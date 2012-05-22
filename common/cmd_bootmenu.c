/*
 * (C) Copyright 2011 Pali Rohár <pali.rohar@gmail.com>
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
#include <command.h>
#include <watchdog.h>
#include <linux/string.h>

#ifdef CONFIG_SYS_HUSH_PARSER
#include <hush.h>
#endif

static char *get_option(int n)
{

	char name[] = "bootmenu_\0\0";

	if (n < 0 || n > 99)
		return NULL;

	sprintf(name+9, "%d", n);

	return getenv(name);

}

static char *get_end_of_title(char *str)
{

	if (!str)
		return NULL;

	return strchr(str, '=');

}

static int print_title(char *begin, char *end)
{

	if (!begin || !end || end < begin)
		return 1;

	while (begin != end)
		putc(*(begin++));

	return 0;

}

static int print_entry(int n, int reverse)
{

	char *str = get_option(n);
	char *end = get_end_of_title(str);

	if (!end)
		return 1;

	printf(ANSI_CURSOR_POSITION, n+4, 1);

	if (reverse)
		puts(ANSI_COLOR_REVERSE);

	puts("     ");
	print_title(str, end);
	puts(ANSI_CLEAR_LINE_TO_END);

	if (reverse)
		puts(ANSI_COLOR_RESET);

	return 0;

}

static int print_menu(int active)
{

	int n = 0;

	printf(ANSI_CURSOR_POSITION, 1, 1);
	puts(ANSI_CLEAR_LINE);
	printf(ANSI_CURSOR_POSITION, 2, 1);
	puts("  *** U-Boot BOOT MENU ***");
	puts(ANSI_CLEAR_LINE_TO_END);
	printf(ANSI_CURSOR_POSITION, 3, 1);
	puts(ANSI_CLEAR_LINE);

	while (1) {

		int ret = print_entry(n, n == active ? 1 : 0);

		if (ret == 1)
			break;

		++n;

	}

	printf(ANSI_CURSOR_POSITION, n+4, 1);

	if (n == active)
		puts(ANSI_COLOR_REVERSE);

	puts("     U-Boot console");
	puts(ANSI_CLEAR_LINE_TO_END);

	if (n == active)
		puts(ANSI_COLOR_RESET);

	printf(ANSI_CURSOR_POSITION, n+5, 1);
	puts(ANSI_CLEAR_LINE);
	printf(ANSI_CURSOR_POSITION, n+6, 1);
	puts("  Press Volume +/- to move, CALL to select");
	puts(ANSI_CLEAR_LINE_TO_END);
	printf(ANSI_CURSOR_POSITION, n+7, 1);
	puts(ANSI_CLEAR_LINE);

	return n;

}

int do_bootmenu(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{

	int active = 0;
	int abort = 0;
	int key = 0; /* 0 - NONE, 1 - UP, 2 - DOWN, 3 - SELECT */
	int esc = 0;
	int count = 0;
	int delay = 10;
	int instant = 0;
	char *delay_str = NULL;

	if (argc >= 2)
		delay_str = argv[1];

	if (!delay_str)
		delay_str = getenv("bootmenu_delay");

	if (delay_str)
		delay = (int)simple_strtol(delay_str, NULL, 10);

	if (delay == 0) {

		/* prevent setting U-Boot console as first menu entry */
		if (get_end_of_title(get_option(0)))
			count = 1;

		instant = 1;

	}

	if (delay < 0)
		abort = 1;

	if (!instant) {

		puts(ANSI_CURSOR_HIDE);
		puts(ANSI_CLEAR_CONSOLE);
		printf(ANSI_CURSOR_POSITION, 1, 1);

	}

	while (1) {

		if (abort || delay > 0)
			count = print_menu(active);

		if (!abort) {

			if (delay > 0)
				printf("  Hit any key to stop autoboot: %2d ",
						delay);

			while (delay > 0) {

				int i;

				for (i = 0; i < 100; ++i) {

					if (tstc()) {

						abort = 1;
						key = getc();

						if (key == '\e') {
							esc = 1;
							key = 0;
						} else if (key == '\r')
							key = 3;
						else
							key = 0;

						break;

					}

					WATCHDOG_RESET();
					udelay(10000);

				}

				if (abort)
					break;

				--delay;
				printf("\b\b\b%2d ", delay);

			}

			if (delay <= 0)
				key = 3;

		} else {

			while (!tstc()) {

				WATCHDOG_RESET();
				udelay(10000);

			}

			key = getc();

			if (esc == 0) {

				if (key == '\e') {
					esc = 1;
					key = 0;
				}

			} else if (esc == 1) {

				if (key == '[') {
					esc = 2;
					key = 0;
				} else
					esc = 0;

			} else if (esc == 2 || esc == 3) {

				if (esc == 2 && key == '1') {
					esc = 3;
					key = 0;
				} else
					esc = 0;

				if (key == 'A')
					key = 1;
				else if (key == 'B')
					key = 2;
				else
					key = 0;

			}

			if (key == '\r')
				key = 3;

		}

		if (key == 1) {

			if (active > 0)
				--active;

		} else if (key == 2) {

			if (active < count)
				++active;

		} 
         else if (key == 3) {

			char *str;
			char *end;

			putc('\n');

			if (!instant) {

				puts(ANSI_CURSOR_SHOW);
				puts(ANSI_CLEAR_CONSOLE);
				printf(ANSI_CURSOR_POSITION, 1, 1);

			}

			WATCHDOG_RESET();

			/* last entry is always U-Boot console */
			if (active == count) {

				puts("Starting U-Boot console\n\n");
				return 0;

			}

			str = get_option(active);
			end = get_end_of_title(str);

			if (!end) {

				printf("Invalid Boot Menu entry %d\n", active);
				puts("Starting U-Boot console\n\n");
				return 0;

			}

			if (!end[1]) {

				printf("Invalid Boot Menu entry %d: ", active);
				print_title(str, end);
				puts("\nStarting U-Boot console\n\n");
				return 0;

			}

			printf("Booting Boot Menu entry %d: ", active);
			print_title(str, end);
			puts(" ...\n\n");

#ifndef CONFIG_SYS_HUSH_PARSER
			run_command(end+1, 0);
#else
			parse_string_outer(end+1, FLAG_PARSE_SEMICOLON |
					FLAG_EXIT_FROM_LOOP);
#endif

			printf("\nFailed booting Boot Menu entry %d: ", active);
			print_title(str, end);
			puts("\nStarting U-Boot console\n\n");
			return 0;

		}

	}

	/* never happends */
	return 1;

}

U_BOOT_CMD(
	bootmenu, 2, 1, do_bootmenu,
	"ANSI terminal bootmenu",
	"[delay]\n"
	"    - show ANSI terminal bootmenu with autoboot delay (default 10s)"
);
