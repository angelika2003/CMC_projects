#include <stdio.h>

int N;
int move[8][2] = {{1, 2}, {1, -2}, { -1, 2}, { -1, -2}, {2, 1}, {2, -1}, { -2, 1}, { -2, -1}};

void knight_move_board(int board[][N + 4], int B_x, int B_y, int n) {
	int is_possible= 1;

	for (int i = 2; i <= N + 1; ++i) {
		for (int j = 2; j <= N + 1; ++j) {
			if (board[i][j] == n) {
				for (int k = 0; k < 8; ++k) {
					int x = i + move[k][0];
					int y = j + move[k][1];

					if ((x == B_x) && (y == B_y)) {
						printf("%d", n + 1);
						return;
					}

					if (board[x][y] == -1) {
						board[x][y] = n + 1;
						is_possible = 0;
					}
				}
			}
		}
	}

	if (is_possible) {
		printf("-1");
		return;
	}

	knight_move_board(board, B_x, B_y, n + 1);
}

int main(void) {
	scanf("%d", &N);

	int board[N + 4][N + 4];
	for (int i = 0; i < N + 4; ++i) {
		for (int j = 0; j < N + 4; ++j) {
			board[i][j] = -1;
		}
	}

	int A_x, A_y, B_x, B_y;
	scanf("%d %d %d %d", &A_x, &A_y, &B_x, &B_y);

	if ((A_x == B_x) && (A_y == B_y)) {
		printf("0");
		return 0;
	}

	A_x++;
	A_y++;
	B_x++;
	B_y++;

	board[A_x][A_y] = 0;

	knight_move_board(board, B_x, B_y, 0);

	return 0;
}