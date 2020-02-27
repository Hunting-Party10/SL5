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
	
	vector<string> literal_table,identifier_table;
	std::vector<UST> ust;
public:
	LexicalAnalyzer(char *file);
	bool Analyze();
    bool testIdentifier(string,int&,int&);
    bool testLiteral(string, int&, int&);
    inline int testKeyword(string word){return terminal_table[word];}
	void display();
    void removeSpace(string&);
    int searchIdentifier(string);
};

int LexicalAnalyzer::searchIdentifier(string l)
{
    for(int i =0;i<identifier_table.size();i++)
        if(identifier_table[i].compare(l) == 0)
            return i;
    return -1;
}

void LexicalAnalyzer::removeSpace(string &line)
{
    string temp ;
    for(int i = 0;i<line.size();i++)
    {
        if(line[i] != ' ')
            temp += line[i];
    }
    line = temp;
}

bool LexicalAnalyzer::testIdentifier(string word,int &pos1, int &pos2)
{
    int prev_token = testKeyword(ust[ust.size() - 1].symbol);
    int next_token = testKeyword(word.substr(pos1+pos2,1));
    string w = word.substr(pos1,pos2);
    if(w[0] - 48 <= 10)
        return false;
    if(prev_token != 0 && next_token != 0)
        return true;
    return false;
}

bool LexicalAnalyzer::testLiteral(string word,int &pos1,int &pos2)
{
    int prev_token = testKeyword(ust[ust.size() - 1].symbol);
    int next_token = testKeyword(word.substr(pos1+pos2,1));
    string w = word.substr(pos1,pos2);
    if((prev_token == 13 || prev_token == 5 || prev_token == 6 || prev_token == 25 ||prev_token == 19 || prev_token == 7) && (next_token == 10 || next_token == 11 ||next_token == 8))// Checking for numbers
    {
        int flag =0;
        for(int i=0;i<w.size();i++)
        {
            if(w[i] - 48 > 10)
                flag = 1;
        }
        if(flag == 0)
            return true;
    } 
    if(prev_token == 24 && next_token == 24 ) //string enclosed in quotes
        return true;
        
    return false;
}

void LexicalAnalyzer::display()
{
	cout<<"Displaying UST\nIndex    Symbol    Type\n";
	for(int i = 0;i<ust.size();i++)
		cout<<ust[i].index<<"    "<<ust[i].symbol<<"    "<<ust[i].type<<"\n";
	
    cout<<"\n\n\n\nDisplaying Identifier table\nIndex    Symbol\n";
    for (int i = 0; i < identifier_table.size(); ++i)
	{
		cout<<i<<"    "<<identifier_table[i]<<"\n";
	}
	cout<<"\n\n\n\nDisplaying Literal table\nIndex    Symbol\n";
	for (int i = 0; i < literal_table.size(); ++i)
	{
		cout<<i<<"    "<<literal_table[i]<<"\n";
	}

}

bool LexicalAnalyzer::Analyze(){
	fstream input(filename, ios::in);

	while(input.eof() != true)
	{
		int pointer1 = 0,len = 1;
		string line;
		getline(input,line);
        //removeSpace(line);
        cout<<"For Line :"<<line<<"\n";
		while(pointer1 + len  <= line.length())
		{
            cout<<"Current Word "<<"("<<pointer1<<","<<len<<")"<<" :"<<line.substr(pointer1,len)<<"\n";
			if((line.substr(pointer1, len)).compare(" ") == 0)
            {
                pointer1++;
                continue;
            }
            if(testKeyword(line.substr(pointer1,len)))
            {
                UST u;
                cout<<"Detected Terminal "<<"("<<pointer1<<","<<len<<")"<<" :"<<line.substr(pointer1,len)<<"\n\n\n";
                u.symbol = line.substr(pointer1,len);
                u.type = "TERM";
                u.index = testKeyword(line.substr(pointer1,len));
                ust.push_back(u);
                pointer1 += len;
                len = 1;
                continue;
            }
            if(testLiteral(line,pointer1,len))
            {
                UST u;
                cout<<"Detected Literal "<<"("<<pointer1<<","<<len<<")"<<" :"<<line.substr(pointer1,len)<<"\n\n\n";
                u.symbol = line.substr(pointer1,len);
                u.type = "LITERAL";
                literal_table.push_back(u.symbol);
                u.index = literal_table.size() -1;
                ust.push_back(u);
                pointer1 += len;
                len = 1;
                continue;
            }
            if(testIdentifier(line,pointer1,len))
            {
                UST u;
                cout<<"Detected Identifier "<<"("<<pointer1<<","<<len<<")"<<" :"<<line.substr(pointer1,len)<<"\n\n\n";
                
                u.symbol = line.substr(pointer1,len);
                u.type = "IDENTIFIER";
                u.index = searchIdentifier(u.symbol);
                if(u.index == -1)
                {
                    identifier_table.push_back(u.symbol);
                    u.index = identifier_table.size() -1;
                }
                ust.push_back(u);
                pointer1 += len;
                len = 1;
                continue;
            }
            
            len++;
        }
		if(pointer1 != line.length())
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
