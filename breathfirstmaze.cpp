#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <functional>
#include "maze.h"
using namespace std;

BreadthFirst::BreadthFirst() : Maze::Maze() {
	init();
	queue.push({ maze, x, y }); // �������� ť�� ����
}

void BreadthFirst::init() {
	for (int i = 0; i < row; i++) {
		vector<int> tmp;
		for (int j = 0; j < col; j++) {
			tmp.push_back(0);
		}
		visited.push_back(tmp);
	}
	visited[x][y] = 1; // �������� �湮��
	maze[x][y] = "*";
}

int BreadthFirst::find() {

	if (queue.empty() || isDone()) return 1;

	vector<vector<int>> tmp;
	item maze_tmp;

	// pop
	maze_tmp = top();
	int dx = maze_tmp.x;
	int dy = maze_tmp.y;
	x = dx;
	y = dy;
	save(maze_tmp.maze);
	pop();
	cout << x << ", " << y << " : " << maze_tmp.g << " + " << maze_tmp.h << " = " <<  maze_tmp.f << endl;
	
	// ������ �ֵ� visited=false �� ť������
	if (dx - 1 >= 0 && maze[dx - 1][dy] == "." && visited[dx - 1][dy] == 0) 
		drawMaze(dx - 1, dy, maze_tmp);
	if (dx + 1 < row && maze[dx + 1][dy] == "." && visited[dx + 1][dy] == 0)
		drawMaze(dx+1, dy, maze_tmp);
	if (dy - 1 >= 0 && maze[dx][dy - 1] == "." && visited[dx][dy - 1] == 0)
		drawMaze(dx, dy - 1, maze_tmp);
	if (dy + 1 < col && maze[dx][dy + 1] == "." && visited[dx][dy + 1] == 0) 
		drawMaze(dx, dy+1, maze_tmp);

	return 0;
}

void BreadthFirst::save(vector<vector<string>> &n) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			maze[i][j] = n[i][j];
		}
	}
}

void BreadthFirst::drawMaze(int dx, int dy, item maze_tmp) {
	vector<vector<string>> maze_ineer_tmp = maze_tmp.maze;
	visited[dx][dy] = 1;
	maze_ineer_tmp[dx][dy] = "*";
	queue.push({ maze_ineer_tmp ,dx,dy});
}


item BreadthFirst::top() {
	return queue.front();
}

void BreadthFirst::pop() {
	queue.pop();
}