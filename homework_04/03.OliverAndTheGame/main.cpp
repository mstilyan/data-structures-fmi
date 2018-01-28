#include <vector>
#include <iostream>

using namespace std;

const int NODES_MAX_COUNT = 100001;
vector<int> graph[NODES_MAX_COUNT];
int pre[NODES_MAX_COUNT];
int pos[NODES_MAX_COUNT];

const int MOVE_TOWARDS = 0;
const int MOVE_AWAY = 1;

int timer = 1;
void DFS(int node)
{
	pre[node] = timer++;

	for (int adj : graph[node])
	{
		DFS(adj);
	}

	pos[node] = timer++;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int nodes;
	cin >> nodes;

	for (int i = 0; i < nodes - 1; ++i)
	{
		int parent, child;
		cin >> parent >> child;
		graph[parent].push_back(child);
	}

	DFS(1);

	int queriesCount;
	cin >> queriesCount;

	for (size_t i = 0; i < queriesCount; i++)
	{
		int move, startNode, endNode;
		cin >> move >> endNode >> startNode;

		if (move == MOVE_TOWARDS)
		{
			if (pre[startNode] > pre[endNode] && pos[startNode] < pos[endNode])
				cout << "YES\n";
			else
				cout << "NO\n";
		}
		else if (move == MOVE_AWAY)
		{
			if (pre[startNode] < pre[endNode] && pos[startNode] > pos[endNode])
				cout << "YES\n";
			else
				cout << "NO\n";
		}
	}

	return 0;
}