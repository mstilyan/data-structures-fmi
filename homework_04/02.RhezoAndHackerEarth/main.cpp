#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

typedef unsigned long long ll;

struct pairhash
{
	template <typename T>
	std::size_t operator()(const std::pair<T, T> &x) const
	{
		return std::hash<T>()(x.first) ^ std::hash<T>()(x.second);
	}
};

ll timer = 0;
void DFS(const ll node, const vector<vector<ll>>& graph, vector<bool>& visited, vector<ll>& low,
	vector<ll>& discovery_time, vector<ll>& parent,
	unordered_set<pair<ll, ll>, pairhash>& bridges)
{
	discovery_time[node] = low[node] = ++timer;
	visited[node] = true;

	for (ll child : graph[node])
	{
		if (!visited[child])
		{
			parent[child] = node;
			DFS(child, graph, visited, low, discovery_time, parent, bridges);
			low[node] = min(low[child], low[node]);

			if (low[child] > discovery_time[node])
			{
				bridges.insert(make_pair(node, child));
				bridges.insert(make_pair(child, node));
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
	ll nodes_count, edges_count;
	cin >> nodes_count >> edges_count;

	vector<vector<ll>> graph(nodes_count);
	vector<bool> visited(nodes_count, false);
	vector<ll> parent(nodes_count, -1);
	vector<ll> low(nodes_count, INT32_MAX);
	vector<ll> discovery_time(nodes_count);
	unordered_set<pair<ll, ll>, pairhash> bridges;
	vector<pair<ll, ll>> edges(edges_count);

	for (size_t i = 0; i < edges_count; i++)
	{
		int v1, v2;
		cin >> v1 >> v2;

		graph[v1 - 1].push_back(v2 - 1);
		graph[v2 - 1].push_back(v1 - 1);
		edges[i] = make_pair(v1 - 1, v2 - 1);
	}

	for (int node = 0; node < nodes_count; ++node)
	{
		DFS(node, graph, visited, low, discovery_time, parent, bridges);
	}


	int queries_count;
	cin >> queries_count;
	for (int i = 0; i < queries_count; ++i)
	{
		ll currEdge;
		cin >> currEdge;

		bool edge_is_bridge = bridges.find(edges[currEdge - 1]) != bridges.end();
		cout << (edge_is_bridge ? "Unhappy" : "Happy") << endl;

	}

	return 0;
}
