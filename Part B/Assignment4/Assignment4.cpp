#include <iostream>
#include<bits/stdc++.h>
#define MAX INT_MAX

using namespace std;
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
    bool solveTSP(const int);
	int find_city_index(const std::string &);
    void displayShortest(TSPutil &);
    int cost(int, int);
};

void TravellingSalesman::displayShortest(TSPutil &solution)
{
    std::cout<<"Shortest Path is :"<<solution.cost<<"\n";
    for(int i = 0; i<solution.vertices.size() ;i++)
    {
        if(i == solution.vertices.size() -1)
            std::cout<<G[solution.vertices[i]].city;
        else
            std::cout<<G[solution.vertices[i]].city<<" -> ";
    }
    
    cout<<"\n\n";
}

int TravellingSalesman::cost(int i,int j)
{
    for(int k =0; k< G[i].edges.size(); k ++)
        if(G[i].edges[k].index == j)
            return G[i].edges[k].weight;
    return MAX;
}

bool TravellingSalesman::solveTSP(const int startVertex)
{
    const int num_cities = G.size();
    TSPutil solution;
    MEMO memo[num_cities][num_cities];
    for(int i=0;i<num_cities;i++)
        for(int j=0;j<num_cities;j++)
            memo[i][j].weight = MAX;
    
        
    //Initializing every leaf of the tree    
    vector<vector<int>> vertex(num_cities-1);
    for(int i = 0;i<num_cities - 1;i++){
        for(int j = 0;j<num_cities;j++)
            if(j != startVertex)
                vertex[i].push_back(j);
    }
    
    
    
    for(int i = 0;i <num_cities;i++)
    {
        if(i == 0)
        {
            //Base Case direct assignment of last node
            for(int k =0;k<vertex.size();k++)
            {
               memo[i][vertex[k][k]].weight = cost(startVertex,vertex[k][k]);
               memo[i][vertex[k][k]].prev_vertex = vertex[k][k];
               vertex[k].erase(vertex[k].begin() + k);
            }
        }
        else
        {
            int c = 0;
            //For every sub tree
            for(int k =0;k<vertex.size();k++)
            {
                int min = MAX;
                int index = -1;
                //finds the next min node
                for(int j = 0;j<vertex[k].size();j++)
                {   
                    if(c == startVertex)
                        c++;
                    if(min > memo[i - 1][c].weight + cost(vertex[k][j],memo[i - 1][c].prev_vertex))
                    {
                        min = memo[i - 1][c].weight + cost(vertex[k][j],memo[i - 1][c].prev_vertex);
                        index = j;
                    }
                }
                memo[i][c].weight = min;
                memo[i][c].prev_vertex = vertex[k][index];
                vertex[k].erase(vertex[k].begin() + index);
                c++;
            }
           
        }
    }
    
    for(int i =0;i<num_cities;i++)
    {
        //Building the last node from the start vertex
        if(i == startVertex)
            continue;
        memo[num_cities -1][i].weight = memo[num_cities -2][i].weight + cost(memo[num_cities -2][i].prev_vertex,startVertex);
        memo[num_cities -1][i].prev_vertex = startVertex;
    }
    
    int min= MAX;
    int start = -1;
    
    //Finds minimum path
    for(int i =0;i<num_cities;i++)
    {
        if(min> memo[num_cities -1][i].weight)
        {
            min = memo[num_cities -1][i].weight;
            start = i;
        }
    }
    /*
     * 
     * 
     * 
     * Uncomment to view memo table
    for(int i=0;i<num_cities;i++){
        for(int j=0;j<num_cities;j++)
            cout<<memo[i][j].weight<<"-";
        
        cout<<"\n";
    }
        
    */
    TSPutil tp;
    tp.cost = min;
    tp.vertices.push_back(startVertex);
    //Building path
    for(int i =0;i<num_cities;i++)
        tp.vertices.push_back(memo[i][start].prev_vertex);
    //Display Path
    displayShortest(tp);
    return true;
}

TravellingSalesman::TravellingSalesman(int n)
{
    //Constructor to init
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
    //Finds index in the graph ds of the given city name
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
    //ts.displayGraph();
    cout<<"Enter Start City:";
    string s;
    cin>>s;
    ts.solveTSP(find_city_index(s));
    return 0;
}


