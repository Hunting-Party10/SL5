/*
 * Author - Atharva Joshi 
 * Recursive Descent Parser
 * 
 * Declare-->Type var ;
 * Type-->int | float | char
 * var--> id,var | id
 * 
 * 
 *
 */

#include<iostream>
#include<bits/stdc++.h>

using namespace std;

    
class RDP{
    int start;
    int stop;
    string exp;
public:
   RDP();
   bool evaluate(string);
   bool declare();
   bool type();
   bool var();
};

RDP::RDP()
{
    start = 0;
    stop = 1;
}

/*
 * 
 * Uses start variable
 */


bool RDP::declare()
{
    if(!type()) return false;
    cout<<"------------------\n";
    if(!var()) return false;
    if(exp[stop] == ';' && exp[stop+1] == '$')return true;
    return false;
}

/*
 * 
 * Detects Type
 */


bool RDP::type()
{
    while(stop < exp.length())
    {
        cout<<"Current word("<<start<<","<<stop<<"):"<<exp.substr(start,stop)<<"\n";
        if(((exp.substr(start,stop)).compare("int") == 0 || (exp.substr(start,stop)).compare("float") == 0 ||(exp.substr(start,stop)).compare("char") == 0) && exp[stop] == ' ')
        {
            cout<<"Detected Type!\n\n\n";
            start = stop++;
            return true;
        }
        stop++;
    }
    return false;
    
}

/*
 * 
 * Detects Variable
 */

bool RDP::var()
{
    while(stop < exp.length())
    {
        cout<<"Current word("<<start<<","<<stop<<"):"<<exp.substr(start,stop)<<"\n";
        if((exp.substr(start,stop)).compare("id"))
        {
            if(exp[stop] == ' '){
                cout<<"Detected Last Variable!\n\n\n";
                start = stop;
                stop ++;
                return true;
            }
            else if(exp[stop] == ',')
            {
                cout<<"Making Recursive Call!\n\n\n";
                start = stop+1;
                stop ++;
                return var();
            }
        }
        stop ++;
    }
}

bool RDP::evaluate(string expression)
{
    exp = expression;
    declare();
}

int main()
{
    string exp;
    cout<<"Enter Expression:";
    getline(cin,exp);
    exp += '$';
    RDP r;
    if(r.evaluate(exp) == true)
        cout<<"Grammar is Valid\n";
    else
        cout<<"Grammar is Invalid\n";
}
