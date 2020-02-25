#include <iostream>
#include<bits/stdc++.h>
#define MAX INT_MAX

class TravellingSalesman {
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

    std::vector<Graph> G;
    typedef struct TSPutil
    {
        int cost;
        std::vector<int> vertices;
    }TSPutil;
    typedef struct MEMO
    {
        int weight;
        int prev_vertex;
    }MEMO;
public:
    TravellingSalesman (int);
    void displayGraph();
    bool solveTSP();
	int find_city_index(const std::string &);
    void displayShortest(TSPutil &);
    void solve(TSPutil &,int);
    int cost(int, int);
};

void TravellingSalesman::displayShortest(TSPutil &solution)
{
    std::cout<<"Shortest Path is :"<<solution.cost<<"\n";
    for(int i = solution.vertices.size() -1; i<0;i++)
    {
        std::cout<<G[solution.vertices[i]].city<<" -> ";
    }
    std::cout<<G[solution.vertices.size() -1 ].city<<"\n\n";
    
}

int TravellingSalesman::cost(int i,int j)
{
    for(int k =0; k< G[i].edges.size(); k ++)
        if(G[i].edges[k].index == j)
            return G[i].edges[k].weight;
    return MAX;
}

void TravellingSalesman::solve(TSPutil &sol,int start_index)
{
const int num_cities = G.size();
    MEMO memo[num_cities ][num_cities];
    
    for(int i=0;i<num_cities;i++)
        for(int j=0;j<num_cities;j++)
            memo[i][j].weight = MAX;
    
    for(int i = 0; i < num_cities;i++)
    {
        for(int j = 0;j < num_cities;j++)
        {
            if(j != start_index)
            {
                if(i == 0){
                    memo[i][j].weight = cost(start_index,j);
                    memo[i][j].prev_vertex = -1; //signifies last vertex before cycle 
                }
                else
                {
                    int min = MAX;
                    int prev_vertex = -1;
                    for(int k =0; k < num_cities; k++)
                    {
                        if(k != start_index && cost(k,j) != MAX && min > cost(k,j) + memo[i-1][j].weight)
                        {
                            min = cost(k,j) + memo[i-1][k].weight;
                            prev_vertex = k;
                        }
                    }
                    memo[i][j].weight = min;
                    memo[i][j].prev_vertex = prev_vertex;
                }
            }
        }
    }
    

    //Tracing the possible shortest path with start vertex 
    sol.vertices.push_back(start_index);
    int min = MAX;
    int vertex = -1;
    for(int i =0;i<num_cities;i++)
    {
        if(min > memo[num_cities -  1][i].weight + cost(start_index,i)){
            sol.cost = memo[num_cities - 1][i].weight + cost(start_index,i);
            vertex = i;
        }
    }
    
    for(int i = num_cities -2 ;i >= 0; i--){
        if(vertex == -1)
            break;
        std::cout<<i<< " "<<vertex<<"\n";
//         sol.vertices.push_back(memo[i][vertex].prev_vertex);
//         vertex = memo[i][vertex].prev_vertex;
   }
   std::cout<<"\n\n\n"<<sol.cost;
}

bool TravellingSalesman::solveTSP()
{
    const int num_cities = G.size();
    std::vector<TSPutil> solution;
    for(int i = 0;i < num_cities;i++)
    {
        TSPutil sol;
        sol.cost = 0;
        solve(sol,i);
        solution.push_back(sol);
        
    }
    
    int min = 0;
    for(int i =1;i<solution.size();i++)
        if(solution[min].cost > solution[i].cost)
            min = i;
    
    displayShortest(solution[min]);
  
}

void TravellingSalesman::displayGraph()
{
  for (std::vector<Graph> :: iterator i = G.begin() ; i != G.end(); i++){
    std::cout << "For City "<<i->city<< '\n';
    for(std::vector<Edge> :: iterator j = i->edges.begin(); j != i->edges.end(); j++)
    	std::cout<<"Neighbor :"<<G[j->index].city<<" Distance :"<<j->weight<<"\n";
    std::cout<<"\n";
  }
}

TravellingSalesman::TravellingSalesman(int n)
{
  Graph v;
  Edge e;
  for (size_t i = 0; i < n; i++){
    v.vertex = i;
    std::cout << "Enter City Name ["<< i << "]:";
    std::cin>>v.city;
    G.push_back(v);
  }
	int N;
	std::cout<<"Enter Number of Edges:";
	std::cin>>N;
	while(N--)
	{
		std::string source,destination;
		int wt;
		std::cin>>source>>destination>>wt;
		e.index = find_city_index(destination);
		e.weight = wt;
		G[find_city_index(source)].edges.push_back(e);
	}
}

int TravellingSalesman::find_city_index(const std::string &city)
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

int main()
{
    int n;
    std::cout<<"Enter Number of Cities:";
    std::cin>>n;
    TravellingSalesman ts(n);
    ts.displayGraph();
    ts.solveTSP();
    return 0;
}


