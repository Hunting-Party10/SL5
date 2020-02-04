#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <map>
#include <string>
#include <unistd.h>
#include <fstream>

using namespace std;

class Pass2
{
	char *filename,*sym,*lit;
	typedef struct sym_table {
		char lc[10];
		char symbol[10];
	}sym_table;

	typedef struct literal_table{
		char lc[10];
		char literal[10];
	}literal_table;
	std::vector<sym_table> symbol_table;
	std::vector<literal_table> lit_table;


public:
	Pass2 (char *file,char *s,char *l){
    filename = new char[strlen(file)];
		sym = new char[strlen(s)];
		lit = new char[strlen(l)];
    strcpy(filename,file);
		strcpy(sym,s);
		strcpy(lit,l);
    FILE *f = fopen(filename,"a");
    fclose(f);
		f = fopen(sym,"a");
		fclose(f);
		f = fopen(lit,"a");
		fclose(f);
    import();
  }

	bool passTwo();
	void import();
	int search_symbol(int);
	int search_literal(int);
	void display();

};

void Pass2::display(/* arguments */) {
	for (size_t i = 0; i < lit_table.size(); i++) {
		std::cout <<lit_table[i].literal<<" "<< lit_table[i].lc << '\n';
	}

}

void Pass2::import(){
	char word1[25],word2[25];
	FILE *f = fopen(sym,"r");
	sym_table s;
	while(fscanf(f,"%s %s",word1,word2) == 2)
	{
		strcpy(s.lc,word1);
		strcpy(s.symbol,word2);
		symbol_table.push_back(s);
	}
	fclose(f);

	literal_table l;
	FILE *f2 = fopen(lit,"r");
	while(fscanf(f2,"%s %s",word1,word2) == 2)
	{
		strcpy(l.lc,word1);
		strcpy(l.literal,word2);
		lit_table.push_back(l);
	}
	fclose(f2);
}

int Pass2::search_symbol(int index)
{
	int lc;
	sscanf(symbol_table[index].lc,"%d",&lc);
	return lc;
}

int Pass2::search_literal(int index){
	int lc;
	sscanf(lit_table[index].lc,"%d",&lc);
	return lc;
}


bool Pass2::passTwo()
{

	FILE *f = fopen(filename,"r");
  FILE *output = fopen("machine_code","w");
	std::cout << "Files opened" << '\n';
  char word1[10],word2[10],word3[10],word4[10];
	char print1[10],print2[10];
	int index;
	while (fscanf(f,"%s %s %s %s",word1,word2,word3,word4) == 4) {
		std::cout << "For Line " <<word1<<" "<<word2<<" "<<word3<<" "<<word4<< '\n';
		if(word2[1] == 'I')
	{
		int i = 3;
		while(word3[i] != ')'){
			print1[i-3] = word3[i];
			i++;
		}
		print1[i-3] = '\0';
		sscanf(print1,"%d",&index);
		switch (word3[1]) {
			case 'R':
				break;
			case 'S':
				index = search_symbol(index);
				sprintf(print1,"%d",index);
				break;
			default :
				print1[0] = word3[1];
				print1[1] = '\0';
		}

		if (word4[0] != '-') {
			i = 3;
			while(word4[i] != ')'){
			print2[i-3] = word4[i];
			std::cout << word4[i] << ' ';
			i++;
			}
			print2[i-3] = '\0';
			std::cout << print2 << '\n';
			sscanf(print2,"%d",&index);
			switch (word4[1]) {
				case 'R':
					break;
				case 'S':
					index = search_symbol(index);
					sprintf(print2,"%d",index);
					break;
				case 'L':
					index = search_literal(index);
					sprintf(print2,"%d",index);
					break;
				default :
					std::cout << "Error Illegal Syntax" << '\n';
			}
		}
		else
			print2[0] = '\0';
		fprintf(output, "%s %c%c %s %s\n",word1,word2[4],word2[5],print1,print2 );
	}
	else
	{
		if(word3[1] == 'S')
			fprintf(output, "%s 00 00 00\n",word1 );
		else
			fprintf(output, "%s 00 00 %s\n",word1,lit_table[((int)word3[3]-48 -1)].literal);
	}
	}
	fclose(f);
	fclose(output);
	display();
	return true;
}

int main(int argc, char *argv[])
{
	Pass2 p(argv[1],argv[2],argv[3]);
	p.passTwo();
	return 0;
}
