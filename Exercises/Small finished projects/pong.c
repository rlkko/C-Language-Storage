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
#define BOX_SIZE 2
#define FPS 50

//maybe the boxes will be dynamic i can remove and add more?
typedef struct box {
	int width = BOX_SIZE;
	bool active = false;
	int* coord = NULL;
}Box;

struct {
	int x, y, tail, head;
	char body_symbol;
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
	paddle.x = WIDTH / 2;
	paddle.y = HEIGHT - 2;
	paddle.tail = 1;
	paddle.head = 6;

	int* start_pos = &Field[paddle.y][paddle.x - paddle.head];

	//Build paddle
	for (int i = paddle.tail; i <= paddle.head; i++)
		*start_pos++ = i;

	//setup ball properties
	ball.x = paddle.x - (paddle.head / 2);
	ball.y = paddle.y - 2;
	ball.speed_multiplier = 1;

	// Position = initial position + speed * multiplier
	ball.velocity = 1 * ball.speed_multiplier;

	ball.symbol = 15; // ☼

	//place ball
	Field[ball.y][ball.x] = -1;

	//TO DO: BOXES, i dont feel like doing it
}

void print() {
	const int CHAR_PADDLE = 178; //▓
	const int CHAR_EMPTY = ' ';
	const int CHAR_BOX = 251; // ░

	for (int render_y_pos = 0; render_y_pos < HEIGHT; render_y_pos++) {
		unsigned char curr_ch = 0;

		for (int render_x_pos = 0; render_x_pos < WIDTH; render_x_pos++) {
			int* curr_pixel = *(Field + render_y_pos) + render_x_pos;

			//box render code ( -2 )
			if (*curr_pixel == -2)
				curr_ch = CHAR_BOX;

			//Visual limits for the user
			if (render_x_pos == WIDTH - 1)
				printf("%c", '|');

			if (!(*curr_pixel))
				curr_ch = CHAR_EMPTY;

			//Ball render code ( -1 )
			if (*curr_pixel == -1)
				curr_ch = ball.symbol;

			//Paddle render properties
			if (*curr_pixel >= paddle.tail && *curr_pixel <= paddle.head + 1)
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
	//this loop looks for tails removes them
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (Field[i][j] == paddle.tail) {
				Field[i][j] = 0;
			}
		}
	}

	//the tail is calculated by the difference between
	//tail and head, subtract tail to grow paddle
	paddle.tail++;
}

void movement() {
	//make it so it also works with caps lock ON
	var = handle_input();
	var = tolower(var);

	switch (var) {
	case 'a':

		//TO DO: MOVE SIZE SPACES TO THE RIGHT AND MAKE COLLISION SYSTEM
		//change cordinate
		paddle.x--;
		paddle.head++;

		//tail--
		//head--
		//middle--

		if (paddle.x <= 0) paddle.x = 0;
		// summon new paddle part
		Field[paddle.y][paddle.x] = paddle.head;

		//delete old paddle part
		update();
		break;
	case 'd':
		//change cordinate
		paddle.x++;
		paddle.head++;

		// summon new paddle part
		Field[paddle.y][paddle.x] = paddle.head;

		//delete old paddle part
		update();
		break;
	}
}

inline int get_paddle_size() {
	//subtracted paddle by 1 to compensate for the one being rendered
	return paddle.head - (paddle.tail - 1);
}

void gameover() {
	//end game loop
	game_status = true;

	//clear screen and show message
	system("cls");
	printf("\tGAME OVER ! ! 1! !");
}

void update_ball() {
	//delete old ball
	Field[ball.y][ball.x] = 0;

	//top limit
	if (ball.y >= 1) {
		ball.velocity = -ball.velocity;
	}

	//bottom limit / game over
	if (ball.y == HEIGHT) {
		gameover();
	}

	//left limit
	if (ball.x >= 1)ball.velocity = -ball.velocity;

	//right limit
	if (ball.x >= WIDTH - 2)
		ball.velocity = -ball.velocity;

	//checks hit with paddle
	const int size = get_paddle_size();
	const int paddle_left = paddle.x;
	const int paddle_right = paddle.x - size;
	const int paddle_middle = paddle.x - (size / 2);

	if (ball.y == paddle.y - 1) {
		if (ball.x == paddle_middle)
			ball.velocity = -ball.velocity;

		if (ball.x > paddle_middle && ball.x <= paddle_left) {
			ball_direction = left;
			ball.x -= ball.velocity;
		}

		if (ball.x < paddle_middle && ball.x >= paddle_right) {
			ball_direction = right;
			ball.velocity = -ball.velocity;
		}
	}

	//change cordinates/puts the ball running
	ball.y -= ball.velocity;

	switch (ball_direction) {
	case left:
		ball.x += ball.velocity;
		break;
	case right:
		ball.x -= ball.velocity;
		break;
	}

	if (ball.x == -1 && ball.y == -1)
	{
		ball.y = 1;
		ball.x = 1;
		ball.velocity = -ball.velocity;
	}

	//summon new ball
	Field[ball.y][ball.x] = -1;
}

void draw() {
	print();
	Sleep(FPS);
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
		logic();
	}

	return 0;
}