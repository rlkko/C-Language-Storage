// snake_game.C
// made by rikko
#include <stdio.h>
#include <conio.h>
#include <ctime>

// To clear the screen
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

#define HEIGHT 30
#define WIDTH 60

typedef struct ball {
	int x, y;
	char symbol;
}Ball;


int x, y, tail, head, var, dir = 'd';

int Field[HEIGHT][WIDTH] = { 0 };
bool game_status = false;
Ball ball;

void init() {
	//setup basic properties
	x = WIDTH / 2, y = HEIGHT - 2, tail = 1, head = 5;
	int* start_pos = &Field[y][x - head];

	//Build paddle
	for (int i = tail; i <= head; i++)
		*start_pos++ = i;

	//setup ball initial position
	ball.x = x - (head / 2);
	ball.y = y - 2;

	ball.symbol = 15; // ☼
	Field[ball.y][ball.x] = -1;
}

void print() {
	const char CHAR_PADDLE = 178; //▓
	const char CHAR_EMPTY = ' ';

	for (int render_y_pos = 0; render_y_pos < HEIGHT; render_y_pos++) {
		char curr_ch = 0;

		for (int render_x_pos = 0; render_x_pos < WIDTH; render_x_pos++) {
			int* curr_pixel = *(Field + render_y_pos) + render_x_pos;

			//Visual limits for the user
			if (render_x_pos == WIDTH - 1)
				printf("%c", '|');

			if (!(*curr_pixel))
				curr_ch = CHAR_EMPTY;

			//Ball render code ( -1 )
			if (*curr_pixel == -1)
				curr_ch = ball.symbol;

			//Paddle render properties
			if (*curr_pixel >= tail && *curr_pixel <= head)
				curr_ch = CHAR_PADDLE;

			printf("%c", curr_ch);
		}
		putc('\n', stdout);
	}
}

void resetscreen() {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Position = { 0,0 };

	SetConsoleCursorPosition(hOut, Position);
}

//Simple function to control the user input
int handle_input() {
	if (_kbhit())
		return _getch();

	return -1;
}

void update() {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (Field[i][j] == tail) {
				Field[i][j] = 0;
			}
		}
	}

	//update new tail
	tail++;
}

void movement() {
	//make it so it also works with caps lock ON
	var = handle_input();
	var = tolower(var);

	switch (var) {
	case 'a':
		x--;
		head++;
		if (x <= 0) x = 0;
		Field[y][x] = head;
		update();
		break;
	case 'd':
		x++;
		head++;
		Field[y][x] = head;
		update();
		break;
	}


}

void update_ball() {
	Field[ball.y][ball.x] = 0;

	if (ball.y == 1)ball.y++;
	else ball.y--;

	if (ball.x == 0)ball.x++;

	if (ball.x == WIDTH)
		ball.x--;


	Field[ball.y][ball.x] = -1;
}

void draw() {
	print();
	Sleep(50);
	resetscreen();
}

void input() {
	movement();
}

void logic() {
	update_ball();

}

int
main()
{
	init();
	while (game_status == false) {
		draw();
		input();
		Sleep(50);
		logic();
	}

	return 0;
}