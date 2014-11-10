#include <ncurses.h>
#include <stdlib.h>

int main() {
	int ch;
	char* buf = malloc(1024 * sizeof(char));
	initscr(); // Initialize curses mode
	keypad(stdscr, TRUE);
	cbreak();
	noecho();
	ch = getch();
	if(ch == KEY_UP) {
		printw("Up key pressed");
	} else {
		echo();
	}
	refresh();
	getch();
	getch();
	getch();
	endwin();
	return 0;
}