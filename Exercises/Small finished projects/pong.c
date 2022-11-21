// snake_game.C
// made by rikko
#include <stdio.h>
#include <conio.h>
#include <ctime>

// To clear the screen
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

#define PADDLE_HEIGHT HEIGHT - 1
#define HEIGHT 30
#define WIDTH 60
#define BOX_SIZE 2
#define FPS 99

//maybe the boxes will be dynamic i can remove and add more?
typedef struct box {
	int width = BOX_SIZE;
	bool active = false;
	int* coord = NULL;
}Box;

struct {
	int* left, * right;
	int y, size, int_symbol;
} paddle;

struct {
	int x, y, velocity, speed_multiplier;
	char symbol;
} ball;

enum hit_direction { left, right, none };
hit_direction ball_direction = none;

//general purpose variables
bool game_status = false;
int var;

//2D environment
int Field[HEIGHT][WIDTH] = { 0 };

void init() {
	//setup basic properties
	paddle.size = 5;
	paddle.int_symbol = 1;

	//setup paddle positions to be used later
	//paddle.spawn_pos = &Field[HEIGHT][WIDTH / 2];
	paddle.left = Field[HEIGHT - 1] + ((WIDTH / 2) - 1);
	paddle.right = paddle.left + paddle.size;

	//Build paddle in the array
	int* ch_placement_index = paddle.left;
	for (int i = 1; ch_placement_index != paddle.right; ch_placement_index++, i++) {
		*ch_placement_index = paddle.int_symbol;
	}

	//TO DO: BOXES, i dont feel like doing it
}
void print() {
	int curr_ch = 0;

	const int CHAR_PADDLE = 178; //▓
	const int CHAR_EMPTY = ' ';
	const int CHAR_BOX = 251; // ░

	for (int render_y_pos = 0; render_y_pos < HEIGHT; render_y_pos++) {
		for (int render_x_pos = 0; render_x_pos < WIDTH; render_x_pos++) {
			int* curr_pixel = &Field[render_y_pos][render_x_pos];

			//box render code ( -2 )
			if (*curr_pixel == -2)
				curr_ch = CHAR_BOX;

			//Visual limits for the user
			if (render_x_pos == WIDTH)
				printf("%c", '|');

			if (!(*curr_pixel))
				curr_ch = CHAR_EMPTY;

			//Paddle render properties
			if (*curr_pixel == paddle.int_symbol)
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

void movement() {
	var = handle_input();
	var = tolower(var);

	switch (var) {
	case 'a':

		if (paddle.left <= Field[PADDLE_HEIGHT])
			return;

		//delete old position
		*paddle.right = 0;

		//change cordinate
		paddle.left -= 1;
		paddle.right -= 1;

		//place block at new position
		*paddle.left = 1;

		break;
	case 'd':

		if (paddle.right >= Field[PADDLE_HEIGHT] + (WIDTH - 1))
			return;

		// delete old position
		*paddle.left = 0;

		//change cordinate
		paddle.left += 1;
		paddle.right += 1;

		//place block at new position
		*paddle.right = 1;

		break;
	}
}

void gameover() {
	//end game loop
	game_status = true;

	//clear screen and show message
	system("cls");
	printf("\tGAME OVER ! ! 1! !");
}

//void update_ball() {
//	//delete old ball
//	Field[ball.y][ball.x] = 0;
//
//	//top limit
//	if (ball.y >= 1) {
//		ball.velocity = -ball.velocity;
//	}
//
//	//bottom limit / game over
//	if (ball.y == HEIGHT) {
//		gameover();
//	}
//
//	//left limit
//	if (ball.x >= 1)ball.velocity = -ball.velocity;
//
//	//right limit
//	if (ball.x >= WIDTH - 2)
//		ball.velocity = -ball.velocity;
//
//	//checks hit with paddle
//	const int size = get_paddle_size();
//	const int paddle_left = paddle.x;
//	const int paddle_right = paddle.x - size;
//	const int paddle_middle = paddle.x - (size / 2);
//
//	if (ball.y == paddle.y - 1) {
//		if (ball.x == paddle_middle)
//			ball.velocity = -ball.velocity;
//
//		if (ball.x > paddle_middle && ball.x <= paddle_left) {
//			ball_direction = left;
//			ball.x -= ball.velocity;
//		}
//
//		if (ball.x < paddle_middle && ball.x >= paddle_right) {
//			ball_direction = right;
//			ball.velocity = -ball.velocity;
//		}
//	}
//
//	//change cordinates/puts the ball running
//	ball.y -= ball.velocity;
//
//	switch (ball_direction) {
//	case left:
//		ball.x += ball.velocity;
//		break;
//	case right:
//		ball.x -= ball.velocity;
//		break;
//	}
//
//	if (ball.x == -1 && ball.y == -1)
//	{
//		ball.y = 1;
//		ball.x = 1;
//		ball.velocity = -ball.velocity;
//	}
//
//	//summon new ball
//	Field[ball.y][ball.x] = -1;
//}

void draw() {
	print();
	Sleep(FPS);
	resetscreen();
}

void input() {
	movement();
}

//void logic() {
//	update_ball();
//}

int
main()
{
	init();
	while (game_status == false) {
		draw();
		input();
		//logic();
	}

	return 0;
}