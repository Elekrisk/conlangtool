#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <locale.h>
#include <stdarg.h>

#include "dictionary.h"

#define HEADER_SIZE 1

void init(void);
void write_header(WINDOW *window, int rows, int cols, int title_length, char *title);

struct Version
{
	int major;
	int minor;
} version;

struct Menu
{
	int option_count;
	char **options;
	int active;
};

int get_chosen_option(struct Menu *menu, WINDOW *window, int spacing)
{
	werase(window);
	while (TRUE)
	{
		for (int i = 0; i < menu->option_count; ++i)
		{
			if (menu->active == i)
			{
				wattron(window, A_REVERSE);
			}
			mvwprintw(window, i * (spacing + 1), 1, menu->options[i]);
			wattroff(window, A_REVERSE);
		};
		wrefresh(window);
		int ch = getch();
		switch (ch)
		{
			case KEY_UP:
				--(menu->active);
				if (menu->active < 0)
				{
					menu->active = menu->option_count - 1;
				}
				break;
			case KEY_DOWN:
				++(menu->active);
				if (menu->active >= menu->option_count)
				{
					menu->active = 0;
				}
				break;
			case 10:
				return menu->active;
		}
	}
}

void initMenu(struct Menu *menu, int arg_count, ...)
{
	menu->option_count = arg_count;
	menu->options = malloc(arg_count * sizeof(char*));
	va_list arg_list;
	va_start(arg_list, arg_count);
	for (int i = 0; i < arg_count; ++i)
	{
		menu->options[i] = va_arg(arg_list, char*);
	}
	menu->active = 0;
}

int main(void)
{
	version.major = 1;
	version.minor = 0;

	struct Dictionary dict;

	init();

	WINDOW *header;
	WINDOW *main;

	int maxRow, maxCol;
	getmaxyx(stdscr, maxRow, maxCol);

	header = newwin(HEADER_SIZE, maxCol, 0, 0);
	main = newwin(maxRow - HEADER_SIZE, maxCol, 3, 0);

	wattron(header, A_REVERSE);

	int loop = TRUE;
	while (loop)
	{
		write_header(header, HEADER_SIZE, maxCol, 15, "-- Main Menu --");

		struct Menu mainMenu;
		initMenu(&mainMenu, 3, "Create new dictionary", "Load dictionary from file", "Exit");
		int action = get_chosen_option(&mainMenu, main, 1); 
		switch (action)
		{
			case 0:
				write_header(header, 1, maxCol, 20, "-- Edit Word List --");

				struct Menu dictMenu;
				initMenu(&dictMenu, 5, "Edit word list", "Edit field defs", "Save dictionary", "Delete dictionary", "Back to main menu");
				int action = get_chosen_option(&dictMenu, main, 1);
				switch (action)
				{
					case 0:
//						edit_word_list(&dict);
						break;
					case 1:
//						edit_field_defs(&dict);
					case 2:
					case 3:
					case 4:
						break;
				}
				break;
			case 2:
				loop = false;
				break;
			default:
				break;
		}
		
	}
	delwin(header);
	endwin();
	return 0;
}

void write_header(WINDOW *header, int rows, int cols, int title_length, char *title)
{
	for (int i = 0; i < rows * cols; ++i)
	{
		waddch(header, ' ');
	}
	mvwprintw(header, 0, 0, "conlangtool v%d.%d", version.major, version.minor);
	mvwprintw(header, rows / 2, (cols - title_length) / 2, title);
	wrefresh(header);
}

void init(void)
{
	setlocale(LC_ALL, "");
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	printw("INITIALIZING...");
	refresh();
}
