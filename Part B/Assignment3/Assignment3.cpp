#include <iostream>
#include<bits/stdc++.h>
#define MAX INT_MAX

class BellmanFord {
private:
  typedef struct Edge
  {
    int index;
    int weight;
  }Edge;
  typedef struct Graph
  {
    int vertex;
    std::string city;
    std::vector<Edge> edges;
  }Graph;
  typedef struct BFutil
  {
  	int weight;
  	int vertex;
	}BFutil;
  std::vector<Graph> G;
  BFutil *wt;
public:
  BellmanFord (int);
  void displayGraph();
	bool solveBF(const std::string &);
	int find_city_index(const std::string &);
	bool relax(int,int,int);
	void displayShortest(const std::string &);
};

void BellmanFord::displayShortest(const std::string &destination)
{
	int dest_index = find_city_index(destination);
	int temp = dest_index;
	if(wt[dest_index].weight == MAX)
	{
		std::cout<<destination<<" is not reachable\n";
		return;
	}
	std::vector<int> path;
	while(wt[dest_index].vertex != dest_index)
	{
		path.push_back(dest_index);
		dest_index = wt[dest_index].vertex;
	}
	path.push_back(dest_index);
	std::cout<<"Path is\n";
	for(int i = path.size() -1 ; i >= 0; i--)
	{
		if(i != 0)
			std::cout<<G[path[i]].city<<"->";
		else
			std::cout<<G[path[i]].city;
	}
	std::cout<<"Distance is :"<<wt[temp].weight<<"\n";
	
}

int BellmanFord::find_city_index(const std::string &city)
{
	int i = 0;
	for(std::vector<Graph> :: iterator vertex_iterator = G.begin(); vertex_iterator != G.end(); vertex_iterator++)
	{
		if(!city.compare(vertex_iterator->city))
			return i;
		i++;
	}
	return -1;
}

bool BellmanFord::relax(int u,int v,int w)
{
	if(wt[v].weight > w + wt[u].weight)
	{
		wt[v].weight = w + wt[u].weight;
		wt[v].vertex = G[u].vertex;
		return true;
	}
	return false;
}

bool BellmanFord::solveBF(const std::string &source)
{
	wt[find_city_index(source)].weight = 0;
	wt[find_city_index(source)].vertex = find_city_index(source);
	for(size_t i = 0; i<= G.size(); i++)
	{
		std::vector<Graph> :: iterator vertex_iterator = G.begin();
		while(vertex_iterator != G.end())
		{
			std::vector<Edge> :: iterator edge_iterator = vertex_iterator->edges.begin();
			while(edge_iterator != vertex_iterator->edges.end())
			{
				relax(vertex_iterator->vertex,edge_iterator->index,edge_iterator->weight);
				edge_iterator++;
			}
			vertex_iterator++;
		}
	}
	std::vector<Graph> :: iterator vertex_iterator = G.begin();
	while(vertex_iterator != G.end())
	{
		std::vector<Edge> :: iterator edge_iterator = vertex_iterator->edges.begin();
		while(edge_iterator != vertex_iterator->edges.end())
		{
			if(relax(vertex_iterator->vertex,edge_iterator->index,edge_iterator->weight) == true)
				return false;
			edge_iterator++;
		}
		vertex_iterator++;
	}
	return true;
}


void BellmanFord::displayGraph()
{
  for (std::vector<Graph> :: iterator i = G.begin() ; i != G.end(); i++){
    std::cout << "For City "<<i->city<< '\n';
    for(std::vector<Edge> :: iterator j = i->edges.begin(); j != i->edges.end(); j++)
    	std::cout<<"Neighbor :"<<G[j->index].city<<" Distance :"<<j->weight<<"\n";
    std::cout<<"\n";
  }
}

BellmanFord::BellmanFord(int n)
{
  Graph v;
  Edge e;
  for (size_t i = 0; i < n; i++){
    v.vertex = i;
    std::cout << "Enter City Name ["<< i << "]:";
    std::cin>>v.city;
    G.push_back(v);
  }

  for (std::vector<Graph> :: iterator i = G.begin(); i != G.end(); i++) {
    std::cout << "For " << (i->city) <<'\n';
    std::vector<Graph> :: iterator j = G.begin();
    while(j != G.end()){
    	if(j == i){
    		j++;
    		continue;
    	}
    		
      std::cout << "Is it connected to "<<j->city << "?(Y/Any):";
      char c;
      std::cin>>c;
      if(c == 'Y')
      {
        std::cout << "Enter Distance:";
        e.index = j->vertex;
        std::cin>>e.weight;
        i->edges.push_back(e);
      }
      j++;
    }
  }
  wt = new BFutil[G.size()];
  for(size_t i=0; i<G.size();i++)
  {
  	wt[i].weight = MAX;
  	wt[i].vertex = -1;
  }
}

int main(int argc, char const *argv[]) {
  int V;
  std::cout << "Enter Number of Cities:";
  std::cin >> V;
  BellmanFord bf(V);
  bf.displayGraph();
  std::string source,destination;
  std::cout<<"Enter Starting City :";
  std::cin>>source;
   std::cout<<"Enter Destination City :";
  std::cin>>destination;
  if(bf.solveBF(source))
	{
  	bf.displayShortest(destination);
	}
	else
		std::cout<<"Negetive Edge Cycle exists in the graph, Shortest Path cannot be found\n";
  return 0;
}
