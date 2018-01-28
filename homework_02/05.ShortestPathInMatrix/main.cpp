/*
 * Имате матрица с нули и единици. Нулите са непроходими квадратчета, 
 * а единиците са проходими като от едно квадратче може да се отиде до всяко 
 * от 8-те съседни квадратчета, ако е ненулево.
 * Намерете дали съществува път между две клетки в матрицата и ако има такъв изведете най-кратктия.
 * 
 * Пример:
 * { {1, 1, 0, 0, 1},
 * {0, 1, 1, 0, 1},
 * {1, 0, 1, 0, 1},
 * {0, 1, 1, 0, 1},
 * {1, 0, 1, 1, 1}};
 * Път между (1,1) и (2,4) - (1,1),(2,2),(3,2),(4,2),(4,3),(3,4),(2,4)
 */

#include <iostream>
#include <queue>
#include <numeric>
using namespace std;

const int ROWS = 5;
const int COLS = 5;
const int MOVES_COUNT = 8;

int matrix[ROWS][COLS] =
{ { 1, 1, 0, 0, 1 },
  { 0, 1, 1, 0, 1 },
  { 1, 0, 1, 0, 1 },
  { 0, 1, 1, 0, 1 },
  { 1, 0, 1, 1, 1 } };

//cell (row * COLS + col)
int prev_cell[ROWS * COLS];

int col_moves[MOVES_COUNT] = { 0, 0, 1, 1, 1, -1, -1, -1 };
int row_moves[MOVES_COUNT] = { 1, -1, 0, 1, -1, 0, 1, -1 };

bool is_in_range(int row, int col);
bool bfs(int start_row, int start_col, int end_row, int end_col);
void print_shortest_path(int start_row, int start_col, int end_row, int end_col);

int main(int argc, char* argv[])
{
	std::fill_n(prev_cell, ROWS * COLS, -1);

	if (bfs(0, 0, 2, 4))
	{
		print_shortest_path(0, 0, 2, 4);
		cout << endl;
	}
	else
	{
		cout << "No path from (0, 0) to (2, 4)" << endl;
	}
}

bool bfs(int start_row, int start_col, int end_row, int end_col)
{
	queue<int> q;
	q.push(start_row * COLS + start_col);

	while (!q.empty())
	{
		int curr_cell = q.front();
		q.pop();

		int curr_row = curr_cell / COLS;
		int curr_col = curr_cell % COLS;

		if (curr_row == end_row && curr_col == end_col)
			return true;

		for (int move = 0; move < MOVES_COUNT; ++move)
		{
			int new_row = curr_row + row_moves[move];
			int new_col = curr_col + col_moves[move];
			int new_cell = new_row * COLS + new_col;

			if (is_in_range(new_row, new_col) && matrix[new_row][new_col] == 1)
			{
				q.push(new_cell);
				matrix[new_row][new_col] = 0;
				prev_cell[new_cell] = curr_cell;
			}
		}
	}

	return false;
}

void print_shortest_path(int start_row, int start_col, int end_row, int end_col)
{
	if (start_row == end_row && start_col == end_col)
	{
		cout << "(" << start_row << "," << start_col << ")";
		return;
	}

	int cell = end_row * ROWS + end_col;
	int prev = prev_cell[cell];

	print_shortest_path(start_row, start_col, prev / ROWS, prev % COLS);
	cout << "(" << end_row << "," << end_col << ")";
}

bool is_in_range(int row, int col)
{
	return row >= 0 && row < ROWS && col >= 0 && col < COLS;
}
