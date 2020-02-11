#include <iostream>
#include <stdlib.h>
#include<stdio.h>
#include <string.h>
#include <vector>
#include <map>
#include <string>
#include<unistd.h>
#include<fstream>
#define LITERAL_SIZE 1
using namespace std;
class Pass1 {
private:
  char *filename;
  typedef struct mnemonic_struct{
    char code[10];
    char mnemonic_class[10];
    int mnemonic_size;
  }mnemonic_struct;
  map<std::string,mnemonic_struct> mnemonic_codes,register_codes,conditional_codes;
  typedef struct sym_table {
    char lc[10];
    char symbol[10];
  }sym_table;

  typedef struct literal_table{
    char lc[10];
    char literal[10];
  }literal_table;

  typedef struct PoolTable{
    int index;
    char literal[10];
  }PoolTable;

  typedef struct LiteralPool{
    int index;
    char literal[10];
  }LiteralPool;

  std::vector<sym_table> symbol_table;
  std::vector<literal_table> lit_table;
  std::vector<PoolTable> pool;
  std::vector<LiteralPool> literal_pool;
public:
  Pass1 (char *file){
    filename = new char[strlen(file)];
    strcpy(filename,file);
    FILE *f = fopen(filename,"a");
    fclose(f);
    assign_mnemonics();
  }
  bool passOne();
  int operand(char *word);
  void assign_mnemonics();
  int search_symbol(char *word);
  void display_symbol_table();
  void display_pool_table();
  void display_literal_table();
};

void Pass1::display_symbol_table()
{
  cout<<"Writing Symbol Table\n";
  fstream f;
  f.open("sym_table",ios::out);
  for(int i = 0; i<symbol_table.size();i++)
    f<< symbol_table[i].lc << ' '<<symbol_table[i].symbol<<"\n";
    f.close();
}

void Pass1::display_pool_table(){
  std::cout << "Displaying Pool Table" << '\n';
  for(int i = 0; i<pool.size();i++)
    std::cout <<pool[i].index<<" "<<pool[i].literal<< '\n';
}

void Pass1::display_literal_table() {
  /* code */
  std::cout << "Writing Literal Table" << '\n';
  fstream f;
  f.open("lit_table",ios::out);
  for(int i = 0; i<lit_table.size();i++)
    f<<lit_table[i].lc<<" "<<lit_table[i].literal<< '\n';
  f.close();
}

int Pass1::search_symbol(char *word)
{
	for(int i = 0 ; i< symbol_table.size();i++)
		if(strcmp(symbol_table[i].symbol,word) == 0)
			return i;
	return -1;
}

void Pass1::assign_mnemonics() {
  mnemonic_struct s;
  s.mnemonic_size = 1;
  strcpy(s.code , "01");
  strcpy(s.mnemonic_class , "AD");
  mnemonic_codes["start"] = s;
  strcpy(s.code , "02");
  strcpy(s.mnemonic_class , "AD");
  mnemonic_codes["end"] = s;
  strcpy(s.code , "03");
  strcpy(s.mnemonic_class , "AD");
  mnemonic_codes["origin"] = s;
  strcpy(s.code , "04");
  strcpy(s.mnemonic_class , "AD");
  mnemonic_codes["eql"] = s;
  strcpy(s.code , "05");
  strcpy(s.mnemonic_class , "AD");
  mnemonic_codes["ltorg"] = s;
  strcpy(s.code , "01");
  strcpy(s.mnemonic_class , "DL");
  mnemonic_codes["dc"] = s;
  strcpy(s.code , "02");
  strcpy(s.mnemonic_class , "DL");
  mnemonic_codes["ds"] = s;
  strcpy(s.code , "00");
  strcpy(s.mnemonic_class , "IS");
  mnemonic_codes["stop"] = s;
  strcpy(s.code , "01");
  strcpy(s.mnemonic_class , "IS");
  mnemonic_codes["add"] = s;
  strcpy(s.code , "02");
  strcpy(s.mnemonic_class , "IS");
  mnemonic_codes["sub"] = s;
  strcpy(s.code , "03");
  strcpy(s.mnemonic_class , "IS");
  mnemonic_codes["mult"] = s;
  strcpy(s.code , "04");
  strcpy(s.mnemonic_class , "IS");
  mnemonic_codes["mover"] = s;
  strcpy(s.code , "05");
  strcpy(s.mnemonic_class , "IS");
  mnemonic_codes["movem"] = s;
  strcpy(s.code , "06");
  strcpy(s.mnemonic_class , "IS");
  mnemonic_codes["comp"] = s;
  strcpy(s.code , "07");
  strcpy(s.mnemonic_class , "IS");
  mnemonic_codes["bc"] = s;
  strcpy(s.code , "08");
  strcpy(s.mnemonic_class , "IS");
  mnemonic_codes["div"] = s;
  strcpy(s.code , "09");
  strcpy(s.mnemonic_class , "IS");
  mnemonic_codes["read"] = s;
  strcpy(s.code , "10");
  strcpy(s.mnemonic_class , "IS");
  mnemonic_codes["print"] = s;
  //Adding Register Codes
  strcpy(s.code , "1");
  strcpy(s.mnemonic_class , "R");
  register_codes["areg"] = s;
  strcpy(s.code , "2");
  strcpy(s.mnemonic_class , "R");
  register_codes["breg"] = s;
  strcpy(s.code , "3");
  strcpy(s.mnemonic_class , "R");
  register_codes["creg"] = s;
  strcpy(s.code , "4");
  strcpy(s.mnemonic_class , "R");
  register_codes["dreg"] = s;
  //Adding Condition codes
  strcpy(s.code , "1");
  strcpy(s.mnemonic_class , "Condi");
  conditional_codes["lt"] = s;
  strcpy(s.code , "2");
  strcpy(s.mnemonic_class , "Condi");
  conditional_codes["le"] = s;
  strcpy(s.code , "3");
  strcpy(s.mnemonic_class , "Condi");
  conditional_codes["eq"] = s;
  strcpy(s.code , "4");
  strcpy(s.mnemonic_class , "Condi");
  conditional_codes["gt"] = s;
  strcpy(s.code , "5");
  strcpy(s.mnemonic_class , "Condi");
  conditional_codes["ge"] = s;
  strcpy(s.code , "6");
  strcpy(s.mnemonic_class , "Condi");
  conditional_codes["any"] = s;
}


bool Pass1::passOne(){
  FILE *f = fopen(filename,"r");
  FILE *output = fopen("output","w");
  char word1[10],word2[10],word3[10],word4[10];

  /*
  TODO
  Perform pass 1 analysis and generate intermediate code.
  Generate Symbol Table, Pool Table, Literal Table and IC.
  Note map returns empty "" if key not found

  lt -1
  le -2
  eq -3
  gt -4
  ge -5
  any -6

*/


	//part 1 from start to end

	if(fscanf(f,"%s %s %s %s",word1,word2,word3,word4) == 4)
	{	if(strcmp(word2,"start") != 0)
		{
			std::cout<<"Error :Start statement missing\n";
			return false;
		}
	}

	int count = atoi(word3);

	int wflag3,wflag4,bflag = 0;
	while (fscanf(f,"%s %s %s %s",word1,word2,word3,word4) == 4){
    std::cout << "For line :" <<word1<<" "<<word2<<" "<<word3<<" "<<word4<<" "<< '\n';
    sym_table s;
  	mnemonic_struct m,n,o;
    wflag3 = 0;
    wflag4 = 0;
    int i;
	 	//Handling word 1 which is either a - or label
	 	if(strcmp(word1,"-") != 0){
	 		sprintf(s.lc ,"%d", count);
	 		strcpy(s.symbol,word1);
	 		symbol_table.push_back(s);
      std::cout << "Lable "<<word1<< " Encountered" << '\n';

	 	}
    else
    {
      std::cout << word1<<" is Empty" << '\n';
    }
	 	//Word 2 which is always an instruction
	 	m = mnemonic_codes[word2];
	 	if(strcmp(m.code,"") == 0 && strcmp(word2,"org") != 0){
	 		std::cout<<"Error:Illegal Instruction '"<<word2<<"'";
	 		fclose(f);
  		fclose(output);
	 		return false;
	 	}
	 	if(strcmp(word2,"org") == 0)
	 	{
      std::cout << "ORG Encountered changing lc" << '\n';
      if(strcmp(word4,"-") == 0){
        count = atoi(word3);
      }
	 		else
      {

        i = search_symbol(word3);
        if (i == -1) {
          std::cout << "Error: Unidentified Symbol:"<<word3 << '\n';
          return false;
        }
        int add;
        char a[10];
        size_t j;
        //std::cout <<strlen(word4)<< '\n';
        for ( j = 1; j < strlen(word4); j++)
          a[j-1] = word4[j];
        a[j-1] = '\0';

        sscanf(a,"%d",&add);
        count = atoi(symbol_table[i].lc) + add;
      }
	 		continue;
		}
    if(strcmp(word2,"bc") == 0){
      wflag3=1;
      std::cout << "Branch Condition Encountered changing flag" << '\n';
    }

    if (strcmp(word2,"ltorg") == 0) {

      std::cout << "ltorg detected, shifting all literals" << '\n';
      PoolTable p;
      literal_table l ;
      p.index = literal_pool[0].index;
      std::cout << literal_pool[0].literal << '\n';
      strcpy(p.literal,literal_pool[0].literal);
      pool.push_back(p);
      int lc = count;
      for (size_t i = 0; i < literal_pool.size(); i++) {
        sprintf(l.lc,"%d",count);
        count += LITERAL_SIZE;
        strcpy(l.literal,literal_pool[i].literal);
        lit_table.push_back(l);
      }
      display_literal_table();
      literal_pool.clear();
      m = mnemonic_codes[word2];
      fprintf(output, "%d (%s,%s)\n",lc,m.mnemonic_class,m.code);
      continue;
    }

    if (strcmp(word2,"stop") == 0) {
      bflag = 1;
      std::cout << "Stop Encountered Exiting Phase 1" << '\n';
      break;
    }
    	//Word 3 which is a symbol,label,register,can be lt gt ...
    if (wflag3 == 1) {
      //Handling for Branch condition.
      n = conditional_codes[word3];
      //std::cout << n.mnemonic_class<< '\n';
      if (strcmp(n.code,"") == 0) {
        std::cout << "Error:Illegal Condition " <<word3<<'\n';
        fclose(f);
    		fclose(output);
        return false;
      }
      std::cout << "Valid Condition detected finding jump symbol" << '\n';
      if(search_symbol(word4) == -1)
      {
        std::cout << "Error: Label '"<<word4 << "' does not Exist";
        fclose(f);
        fclose(output);
        return false;
      }
      else
      {

        sprintf(o.code,"%d",search_symbol(word4));
        strcpy(o.mnemonic_class , "S");
        cout<<"Label "<<word4<<"  is at "<<o.code<<" index";
      }
      //Branch Handling End
    }
    else
    {
      //Handling for regular instruction
      std::cout << "Handling for regular instruction" << '\n';
      n = register_codes[word3];
  		if(strcmp(n.code,"") == 0 )
  		{
        std::cout << "operand "<< word3<<" Not A register" << '\n';
  		/*
  		forward reference has occured
  		*/
  			if(search_symbol(word3) == -1)
  			{
          std::cout << "Adding "<<word3<<" to Symbol table" << '\n';
  				sprintf(s.lc ,"%d",count);
  	 			strcpy(s.symbol,word3);
  	 			symbol_table.push_back(s);
  			}

  			sprintf(n.code,"%d",search_symbol(word3));
  			strcpy(n.mnemonic_class,"S");
        cout<<"Label "<<word3<<" is at "<<search_symbol(word3)<<" index";
        //Handling Second operand
      }
      if (strcmp(word4,"-") != 0) {
        o = register_codes[word4];
        if(strcmp(o.code,"") == 0 )
        {
        /*
        forward reference has occured for second operand or it is a literal
        */
          if (word4[0] != '=') {
            if(search_symbol(word4) == -1)
            {
              std::cout << "Adding "<<word4<<" to Symbol table" << '\n';
              sprintf(s.lc ,"%d", count);
              strcpy(s.symbol,word4);
              symbol_table.push_back(s);
            }

            sprintf(o.code,"%d",search_symbol(word4));
            cout<<"Label "<<word4<<"  is at "<<o.code<<" index";
            strcpy(o.mnemonic_class ,"S");
          }
          else
          {
            //Handle for Literal
            std::cout << "Literal detected adding to pool" << '\n';
            LiteralPool l;
            l.index = lit_table.size();
            strcpy(l.literal,word4);
            literal_pool.push_back(l);
            strcpy(o.mnemonic_class,"L");
            sprintf(o.code,"%lu",literal_pool.size()-1);

          }
        }
      }
      else
        wflag4 = 1;

    }
    fprintf(output, "%d (%s,%s) ",count,m.mnemonic_class,m.code);
    if(wflag3 == 1)
      fprintf(output, "(%s)",n.code );
    else
      fprintf(output, "(%s,%s)",n.mnemonic_class,n.code );

    if (wflag4 == 1)
      fprintf(output, "\n" );
    else
      fprintf(output, " (%s,%s)\n",o.mnemonic_class,o.code );
    count += m.mnemonic_size ;
  }
  //Handling after stop
  std::cout << "Starting Phase 2" << '\n';
  while (fscanf(f,"%s %s %s %s",word1,word2,word3,word4) == 4) {
    std::cout << "For line :" <<word1<<" "<<word2<<" "<<word3<<" "<<word4<<" "<< '\n';
    mnemonic_struct m,n;
    if(strcmp(word1,"-") != 0)
    {
      
      int size = 0;
      int add = search_symbol(word1);
      m = mnemonic_codes[word2];
      if (word3[0] == '\'') {
        //literal allocated
        //Handle for Literal
        LiteralPool l;
        l.index = lit_table.size();
        strcpy(l.literal,word3);
        literal_pool.push_back(l);
        size = 1;
        strcpy(n.mnemonic_class,"C");
        sprintf(n.code,"%lu",l.index + literal_pool.size());
      }
      else
      {
        //Size allocated
        size = atoi(word3);
        strcpy(n.mnemonic_class,"S");
        sprintf(n.code,"%d",add);
      //  n.mnemonic_class,""
      }
      sprintf(symbol_table[add].lc,"%d",count+size);
      count+=size;
      fprintf(output, "%d (%s,%s) (%s,%s)\n",count++,m.mnemonic_class,m.code,n.mnemonic_class,n.code);
    }
    else
    {
      if (strcmp(word2,"end") != 0) {
        std::cout << "Error: End Statement Missing" << '\n';
        return false;
      }
      PoolTable p;
      literal_table l ;
      p.index = literal_pool[0].index;
      strcpy(p.literal,literal_pool[0].literal);
      pool.push_back(p);
      int lc = count;
      for (size_t i = 0; i < literal_pool.size(); i++) {
        sprintf(l.lc,"%d",count);
        count += LITERAL_SIZE;
        strcpy(l.literal,literal_pool[i].literal);
        lit_table.push_back(l);
      }
      literal_pool.clear();
      m = mnemonic_codes[word2];
      fprintf(output, "%d (%s,%s)\n",lc,m.mnemonic_class,m.code);
      break;
    }
  }


  display_pool_table();
  std::cout << "\n\n\n" << '\n';
  display_literal_table();
  std::cout << "\n\n\n" << '\n';
  display_symbol_table();
  std::cout << "\n\n\n" << '\n';
	fclose(f);
  fclose(output);
  return true;
}

int main(int argc, char const *argv[]) {
  char filename[25];
  strcpy(filename,argv[1]);
  Pass1 p(filename);
  p.passOne();
  //if(p.passOne() == true)
  //  std::cout << "Pass 1 code has been generated" << '\n';
  //else
  //  std::cout << "Error" << '\n';
  return 0;
}
