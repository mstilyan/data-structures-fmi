/*
 * Нека имате двумерна матрица, която представя разположението на ябълки една до друга.
 * Матрицата може да съдържа следните стойности:
 * 0 - няма ябълка
 * 1 - ябълката на тази позиция е прясна
 * 2 - ябълката на тази позиция е гнила
 * 
 * Приемаме, че всяка една ябълка може да развали ябълките, които се намират от четирите й страни.
 * Реализирайте алгоритъм, който:
 * 	 а) проверява дали в даден момент всички ябълки ще се развалят
 * 	 б) ако приемем за единица времето, необходимо на текущо загнилите ябълки да развалят съседите си,
 * 	 то колко единици време ще са необходими на всички ябълки да бъдат развалени.
 * 	 
 * Пример: {2, 1, 0, 2, 1}
 * 		   {1, 0, 1, 2, 1}
 * 		   {1, 0, 0, 2, 1}
 */
#include <iostream>
#include <queue>
using namespace std;

const int ROWS = 3;
const int COLS = 5;

int fresh_apples_counter = 0;
int total_rotting_time = INT32_MAX;

int MOVES_COUNT = 4;
int row_moves[] = { 0, 0, 1, -1 };
int col_moves[] = { 1, -1, 0, 0 };

int matrix[ROWS][COLS] =
{ { 2, 1, 0, 2, 1 },
  { 1, 0, 1, 2, 1 },
  { 1, 0, 0, 2, 1 } };

bool bfs();
bool is_in_range(int row, int col);

int main(int argc, char* argv[])
{
	if (bfs())
	{
		cout << "All apples are rotten. Needed time: " << total_rotting_time << endl;
	}
	else
	{
		cout << "Not all apples are rotten. Fresh apples count: " << fresh_apples_counter << endl;
	}
}

bool is_in_range(int row, int col)
{
	return row >= 0 && row < ROWS && col >= 0 && col < COLS;
}

bool bfs()
{
	//pairs represent matrix cells of rotten apples and time of rotting
	//cell (row * ROWS + col)
	queue<pair<int, int>> rotten_apples;

	for (int row = 0; row < ROWS; ++row)
	{
		for (int col = 0; col < COLS; ++col)
		{
			if (matrix[row][col] == 2) //apple is rotten
			{
				int cell = row * COLS + col;
				rotten_apples.push(make_pair(cell, 0));
			}
			else if (matrix[row][col] == 1) //apple is fresh
			{
				fresh_apples_counter++;
			}
		}
	}

	while (!rotten_apples.empty())
	{
		int curr_cell = rotten_apples.front().first;
		int curr_time = rotten_apples.front().second;
		int curr_row = curr_cell / COLS;
		int curr_col = curr_cell % COLS;

		if (fresh_apples_counter == 0)
		{
			total_rotting_time = rotten_apples.back().second;
			return true;
		}

		for (int move = 0; move < MOVES_COUNT; ++move)
		{
			int new_row = curr_row + row_moves[move];
			int new_col = curr_col + col_moves[move];

			if (is_in_range(new_row, new_col) && matrix[new_row][new_col] == 1)
			{
				fresh_apples_counter--;
				matrix[new_row][new_col] = 2;
				rotten_apples.push(make_pair(new_row * COLS + new_col, curr_time + 1));
			}
		}

		rotten_apples.pop();
	}

	return false;
}
