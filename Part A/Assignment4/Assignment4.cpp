#include <iostream>
#include <fstream>
#include <string.h>
#include <map>
#include <vector>
using namespace std;

class LexicalAnalyzer
{
private:
	char *filename;
	map<string, int> terminal_table;
	typedef struct UST
	{
		int index;
		string symbol;
		string type;
	}UST;
	
	vector<string> literal_table,symbol_table;
	std::vector<UST> ust;
public:
	LexicalAnalyzer(char *file);
	bool Analyze();
	void display();
};

void LexicalAnalyzer::display()
{
	cout<<"Display UST\nIndex    Symbol    Type\n";
	for(int i = 0;i<ust.size();i++)
		cout<<ust[i].index<<"    "<<ust[i].symbol<<"    "<<ust[i].type<<"\n";
	

	for (int i = 0; i < literal_table.size(); ++i)
	{
		/* code */
	}

}

bool LexicalAnalyzer::Analyze(){
	fstream input(filename, ios::in);

	while(input.eof() != true)
	{
		int pointer1 = 0,pointer2 = 1;
		string line,word;
		getline(input,line);
		cout<<line<<"\n";
		while(pointer2 <= line.length())
		{
			word = line.substr(pointer1,pointer2);
			cout<<"Current Word : "<<word<<"\n";
			UST u;
			if(terminal_table[word] != 0)
			{
				//Word is a Terminal
				
				u.index = terminal_table[word];
				u.symbol = word;
				u.type = "TERM";
				ust.push_back(u);
				pointer1 = pointer2 ;
			}
			else if(terminal_table[line.substr(pointer2,pointer2+1)] != 0)
			{
				//Add to Symbol table0
				if(ust[ust.size() -1].type.compare("TERM") == 0 )
				{
					literal_table.push_back(word);
					u.index = literal_table.size()-1;
					u.type = "LITERAL";
					u.symbol = word;
					ust.push_back(u);
				}
				else
				{
					symbol_table.push_back(word);
					u.index = symbol_table.size()-1;
					u.type = "Identifier";
					u.symbol = word;
					ust.push_back(u);
				}
				pointer1 = pointer2 ;	
			}

			pointer2 ++;
		}
		if(pointer1 + 1 != pointer2)
		{
			cout<<"Syntax Error\n";
			return false;
		}
	}
	return true;
}


LexicalAnalyzer::LexicalAnalyzer(char *file)
{
	filename = new char[strlen(file)];
	strcpy(filename,file);
	fstream f(filename,ios::app);
	f.close();
	f.open("terminal", ios::in);
	while(f.eof() != true)
	{
		int value;
		string key;
		f>>value>>key;
		terminal_table[key] = value;
	}
}

int main(int argc, char *argv[])
{
	LexicalAnalyzer l(argv[1]);
	l.Analyze();
	l.display();
	return 0;
}