#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int timer = 0;
void DFS(int node, const vector<vector<int>>& graph, vector<bool>& visited, vector<int>& low,
	vector<int>& discovery_time, vector<bool>& articulation_point, vector<int>& parent)
{
	discovery_time[node] = low[node] = ++timer;
	visited[node] = true;

	int children_counter = 0;
	for (const int child : graph[node])
	{
		if (!visited[child])
		{
			children_counter++;
			parent[child] = node;
			DFS(child, graph, visited, low, discovery_time, articulation_point, parent);
			low[node] = min(low[node], low[child]);

			if (parent[node] == -1 && children_counter > 1)
			{
				articulation_point[node] = true;
			}
			else if (parent[node] != -1 && discovery_time[node] <= low[child])
			{
				articulation_point[node] = true;
			}
		}
		else if (parent[node] != child)
		{
			low[node] = min(low[node], discovery_time[child]);
		}
	}
}

int main(int argc, char* argv[])
{
	int nodes, edges;
	cin >> nodes >> edges;

	vector<vector<int>> graph(nodes);
	vector<bool> visited(nodes, false);
	vector<bool> articulation_point(nodes, false);
	vector<int> edges_count(nodes, 0);
	vector<int> parent(nodes, -1);
	vector<int> discovery_time(nodes);
	vector<int> low(nodes, INT32_MAX);

	for (int i = 0; i < edges; ++i)
	{
		int v1, v2;
		cin >> v1 >> v2;

		graph[v1 - 1].push_back(v2 - 1);
		graph[v2 - 1].push_back(v1 - 1);
		edges_count[v1 - 1]++;
		edges_count[v2 - 1]++;
	}

	for (int node = 0; node < nodes; ++node)
	{
		DFS(node, graph, visited, low, discovery_time, articulation_point, parent);
	}

	int queries_count;
	cin >> queries_count;

	for (int i = 0; i < queries_count; ++i)
	{
		int node;
		cin >> node;

		if (articulation_point[node - 1])
		{
			cout << "Satisfied " << edges_count[node - 1] << endl;
		}
		else
		{
			cout << "Not Satisfied" << endl;
		}
	}

	return 0;
}
