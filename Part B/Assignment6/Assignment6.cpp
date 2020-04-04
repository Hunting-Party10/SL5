 
 
/*
 *Author - Atharva Joshi
 *Reference - Abdul Bari Youtube
 *
 *Assumption minimum cost is the sum of the smallest edges in the graph,This calculation *is done using the reduce function
 *
 * Note this is a dificult code to understand , watch the video mentioned in the Reference for actual working
 * Default test case accepts 5 change it accordingly
 */ 
#include <iostream>
#include<bits/stdc++.h>
#define DEBUG cout<<"Debug\n\n";
#define MAX INT_MAX

using namespace std;
typedef struct Node
{
    int previous_index; //Used to retrieve the previous cost
    int *matrix; // Cost Matrix for a given node
    int cost; // Cost of reduction
    vector<int> unvisited_vertex; // List of other nodes to be explored
    bool dead; // Marked true when cost is greater than upper bound. Will not be explored
    int vertex; // Marks which vertex you are currently exploring
}Node;

class TravellingSalesman {
private:

    int *Graph; // The main matrix containing the original weights
    vector<string> city_names; // List of city names which are mapped to the adj matrix
    int upper_bound; // Maintians upper bound    
    int checkExplorable(vector<Node> &); //Checks if ub is the least value
public:
    TravellingSalesman (int); //Constructor for initializing values and accepting
    void displayGraph(); // Displays the graph
    void solveTSP(const int);// Solved TSP
	int find_city_index(const std::string &); //Finds matrix index from city name
    inline int cost(int *matrix,int i, int j) {return matrix[convert1D(i,j)];} // Returns cost
    inline int convert1D(int i,int j) {    return i * city_names.size() + j; } // 2D to 1D mapper
    int* createcopy(int*,int); // Creates a copy matrix
    int reduce(int*); // Reduces a matrix
    void selectVertex(int *,int,int); //Selects a vertex
    void displayMatrix(int *);
    
};

void TravellingSalesman::displayMatrix(int *m)
{
    for(int i =0;i<city_names.size();i++)
    {
        for(int j = 0;j<city_names.size();j++)
        {
            if(m[convert1D(i,j)] == MAX)
                cout<<"inf ";
            else
                cout<<m[convert1D(i,j)]<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n\n";
}

/*
 * Returns the minimum index which can be explorable . -1 if nothing is explorable
 * 
 */
int TravellingSalesman::checkExplorable(vector<Node> &tree)
{
    int min = upper_bound;
    int index = -1;
    for(int i =0;i<tree.size();i++)
        if(tree[i].cost < min && tree[i].dead == false)
            index = i;
    
    if(index != -1)
        return index;
    return -1;
}   

/*
 * Selecting a vertex makes all its outgoing edges infinity
 */
void TravellingSalesman::selectVertex(int *matrix,int i,int j)
{
    matrix[convert1D(j,i)] = MAX;
    for(int k = 0;k<city_names.size();k++)
    {
        matrix[convert1D(i,k)] = MAX;
        matrix[convert1D(k,j)] = MAX;
    }
}

/*
 * 
 * Reduction
 * Bacically returning the sum of least edges and canceling them from the matrix
 */

int TravellingSalesman::reduce(int *matrix)
{
    //Reduce Rows
    int cost = 0;
    for(int i =0;i<city_names.size();i++)
    {
        int min = MAX;
        for(int j = 0;j<city_names.size();j++)
            if(min > matrix[convert1D(i,j)])
                min = matrix[convert1D(i,j)];
        if(min != MAX && min != 0){
            for(int j = 0;j<city_names.size();j++){
                if(matrix[convert1D(i,j)] != MAX)
                    matrix[convert1D(i,j)] =  matrix[convert1D(i,j)] - min;
            }
        cost+=min;
        }
    }
    
    //Reduce cols
    for(int i =0;i<city_names.size();i++)
    {
        int min = MAX;
        for(int j = 0;j<city_names.size();j++)
            if(min > matrix[convert1D(j,i)])
                min = matrix[convert1D(j,i)];
        if(min != MAX && min != 0){
            for(int j = 0;j<city_names.size();j++){
                if(matrix[convert1D(j,i)] != MAX)
                    matrix[convert1D(j,i)] =  matrix[convert1D(j,i)] - min;
                
            }
        cost+=min;
            
        }
    }
    
    return cost;
}

/*
 * Creates copy of a matrix
 * We requre multiple copies to maintain reductions
 */
int* TravellingSalesman::createcopy(int* source,int n)
{
    
    int *temp;
    temp = (int *)malloc(n * n * sizeof(int));
    for(int i = 0;i<n;i++)
        for(int j = 0;j<n;j++)
            temp[convert1D(i,j)] = source[convert1D(i,j)];
    
    return temp;
}

int TravellingSalesman::find_city_index(const std::string &city)
{
    //Finds index in the graph ds of the given city name
	int i = 0;
	for(std::vector<string> :: iterator vertex_iterator = city_names.begin(); vertex_iterator != city_names.end(); vertex_iterator++)
	{
        //cout<<*vertex_iterator<<"\n";
		if(!city.compare(*vertex_iterator))
			return i;
		i++;
	}
	return -1;
}

void TravellingSalesman::displayGraph()
{
    for(int i =0;i<city_names.size();i++)
    {
        cout<<"For city "<<city_names[i]<<"\n";
        for(int j =0;j<city_names.size();j++)
            cout<<city_names[i]<<"->"<<city_names[j]<<"="<<Graph[convert1D(i,j)]<<"\n";
        cout<<"\n";
    }
}

TravellingSalesman::TravellingSalesman(int n)
{
    string city;
    fstream f("Testcase.txt",ios::in);
    if(f.fail())
        exit(1);
    for (size_t i = 0; i < n; i++){
        std::cout << "Enter City Name ["<< i << "]:";
        f>>city;
        cout<<city<<"\n";
        city_names.push_back(city);
    }
   //Initialize adjecency matrix 
    Graph = (int *)malloc(n * n * sizeof(int));
    for(int i =0;i<city_names.size();i++)
        for(int j =0;j<city_names.size();j++)
            Graph[convert1D(i,j)] = MAX;
    
    //accept vertices
    int N = city_names.size() * (city_names.size() - 1) ;
    
	while(N--)
	{
		std::string source,destination;
		int wt;
		f>>source>>destination>>wt;
		Graph[convert1D(find_city_index(source),find_city_index(destination))] = wt;
	}
    upper_bound = MAX;
}

/*
 * Solves tsp, generates state space tree and picks minimum node on each iteration . Updates The upper bound on reaching the leaf.
 */

void TravellingSalesman::solveTSP(int source)
{
    Node start; // Initial Node
    start.matrix = createcopy(Graph,city_names.size());
    start.cost = reduce(start.matrix);
    start.previous_index = -1;
    start.vertex = source;
    start.dead = false;
    
    for(int i =0;i<city_names.size();i++) // Pushing all vertices into the first node except the source
        if(i != source)
            start.unvisited_vertex.push_back(i);
        
    vector <Node> explore; //List of explorable vertices
    explore.push_back(start);
    int min_node;
    cout<<"Starting TSP\n";
    while(checkExplorable(explore) != -1)
    {
        min_node = checkExplorable(explore);
        
        explore[min_node].dead = true; //Fail safe just in case
            
        bool reached_leaf = false; // Use this to mark whether a leaf was reached at 
        
        while(!reached_leaf) //Redundant Condition
        {
            //Iterate over a list of unselected vertices
            for(vector<int>:: iterator i = explore[min_node].unvisited_vertex.begin(); i !=  explore[min_node].unvisited_vertex.end(); i++) 
            {
                //Mark as Dead so that it is not picked again
                explore[min_node].dead = true;
                
                //Initialize Node
                Node cur;
                cur.matrix = createcopy(explore[min_node].matrix,city_names.size());
                selectVertex(cur.matrix,explore[min_node].vertex,*i); // Select a vertex *i
                cur.matrix[convert1D(*i,source)] = MAX; // To avoid going back to source;
                cur.cost = explore[min_node].cost + cost(explore[min_node].matrix,explore[min_node].vertex,*i) + reduce(cur.matrix) ; //Cost of new node along with reduction
                cur.dead = false; // Do not mark as dead unless it is a leaf
                cur.previous_index = min_node; // Link to maintain route
                cur.vertex = *i; // Maintians which vertex this node represents
                cur.unvisited_vertex = explore[min_node].unvisited_vertex; //Copy unvisited list , will modify it later

                //Copy the unvisited vector from parent and remove itself(The vertex) from it 
                for(int j = 0;j<cur.unvisited_vertex.size();j++){
                    if(cur.unvisited_vertex[j] == *i)
                    {
                        cur.unvisited_vertex.erase(cur.unvisited_vertex.begin() + j); //Removes itself from the parents unvisited list and uses it as its own
                        break;
                    }
                }
                if(cur.unvisited_vertex.size() == 0){
                 //When there is node left to visit, it signifies leaf node has been reached. Breaking out to check with upper bound.
                    cur.dead = true;
                    reached_leaf = true;
                    explore.push_back(cur);
                    min_node = explore.size() - 1;
                    break;
                }
                //Push this node into a list of explorable nodes
                explore.push_back(cur);
            }

            if(reached_leaf == true)
                break;//Breaking to compare with upper bound
            
            //Find next minimum node to explore
            int min_cost = MAX;
            for(int i =0;i<explore.size();i++)
                if(min_cost > explore[i].cost && explore[i].dead == false){
                    min_cost = explore[i].cost;
                    min_node = i;
                }
        }
        
        //Compare with upper bound 
        if(upper_bound > explore[min_node].cost)
            upper_bound = explore[min_node].cost;
    }
    
    
    //Display Path
    cout<<"Tour Cost :"<<upper_bound<<"\n";
    cout<<"Printing Cycle\n";
    cout<<city_names[source];
    while(min_node != -1)
    {
        cout<<"->"<<city_names[explore[min_node].vertex];
        min_node = explore[min_node].previous_index;
    }
}

int main()
{
    int n;
    std::cout<<"Enter Number of Cities(Enter 5 if you havent changed the test case):";
    std::cin>>n;
    cout<<"Using test case file denoted by Testcase.txt, the input will be scanned\n";
    TravellingSalesman ts(n);
    ts.displayGraph();
    string name;
    cout<<"Enter Source City:";
    cin>>name;
    cout<<"\n"
    ts.solveTSP(ts.find_city_index(name));
    return 0;
}
