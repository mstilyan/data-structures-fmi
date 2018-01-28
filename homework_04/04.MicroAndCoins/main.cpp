#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

int nodes;
int edges;

bool isConnected(vector<vector<int>>& graph);
bool containsHamiltonianPath(bool graph[11][11]);
bool getNextPermutation(vector<int>& permutation);
bool isConnected_helper(vector<vector<int>>& graph, vector<bool>& visited, int visitedNodesCount, int currNode);

int main(int argc, char* argv[])
{
	int graphsCount;
	cin >> graphsCount;

	for (int i = 0; i < graphsCount; ++i)
	{
		cin >> nodes >> edges;
		bool graph[11][11] = { false };
		//vector<vector<int>> graph(nodes);
		
		for (int i = 0; i < edges; ++i)
		{
			int v1, v2;
			cin >> v1 >> v2;

			graph[v1][v2] = true;
			graph[v2][v1] = true;

			/*graph[v1 - 1].push_back(v2 - 1);
			graph[v2 - 1].push_back(v1 - 1);*/
		}

		//cout << (isConnected(graph) ? "Yes" : "No") << endl;
		cout << (containsHamiltonianPath(graph) ? "Yes" : "No") << endl;
	}
	return 0;
}

bool isConnected(vector<vector<int>>& graph)
{
	vector<bool> visited(nodes);
	return isConnected_helper(graph, visited, 0, 0);
}

bool isConnected_helper(vector<vector<int>>& graph, vector<bool>& visited, int visitedNodesCount, int currNode)
{
	visited[currNode] = true;

	if (visitedNodesCount == nodes)
		return true;

	bool isConnected = false;
	for (auto child : graph[currNode])
	{
		if (!visited[child])
		{
			isConnected |= isConnected_helper(graph, visited, visitedNodesCount + 1, child);
		}
	}

	visited[currNode] = false;
	return isConnected;
}

bool containsHamiltonianPath(bool graph[11][11])
{
	vector<int> path(nodes);
	iota(path.begin(), path.end(), 1);

	do
	{
		bool pathIsHamiltonian = true;
		for (int i = 0; i < path.size() - 1; ++i)
		{
			if (!graph[path[i]][path[i + 1]])
			{
				pathIsHamiltonian = false;
				break;
			}
		}

		if (pathIsHamiltonian) return true;
	}
	while (/*next_permutation(path.begin(), path.end())*/ getNextPermutation(path));

	return false;
}

bool getNextPermutation(vector<int>& permutation)
{
	bool argIsLastPermutation = true;
	//Find the highest index i such that s[i] < s[i+1].
	//If no such index exists, the permutation is the last permutation.
	int i;
	for (i = permutation.size() - 2; i >= 0; i--)
	{
		if (permutation[i] < permutation[i + 1])
		{
			argIsLastPermutation = false;
			break;
		}
	}

	if (argIsLastPermutation) return false;

	//Find the highest index j > i such that s[j] > s[i].
	//Such a j must exist, since i+1 is such an index.
	int j;
	for (j = permutation.size() - 1; j >= 0; --j)
	{
		if (permutation[i] < permutation[j])
		{
			break;
		}
	}

	//Swap s[i] with s[j]
	int temp = permutation[i];
	permutation[i] = permutation[j];
	permutation[j] = temp;

	//Reverse the order of all of the elements after index i till the last element.
	int k = i + 1;
	int m = permutation.size() - 1;
	
	while (k < m)
	{
		int temp = permutation[k];
		permutation[k] = permutation[m];
		permutation[m] = temp;
		++k;
		--m;
	}

	return true;
}