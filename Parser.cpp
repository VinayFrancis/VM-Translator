#include<iostream>
#include <fstream>
#include<string>
#include<cstring>
#include<sstream>
#include "Parser.h"

using namespace std;

void Parser :: open_file(string inputfile)
{
  parse.open(inputfile);
}


bool Parser :: hasmorecommands()
	{
		if(!parse.eof())
		{
			
			return true;
		}
		
		parse.close();
		return false;
	}

void Parser :: advance()
	{
	 

      		if(getline(parse,current))
      		{ 
      			while(!parse.eof() && startswith(current))
      			{

      				getline(parse, current);
      			}
      			
      			
      		}
      		
    }


string Parser :: commandtype()
    {
    	
    	iss.clear();
    	iss.str(current);
    

    	if(iss>>word)
    	{
    		iss.clear();
    		iss.str(current);
    		
    		if(!word.compare("push") || !word.compare("pop"))
    			return "stack_op";
    		else if(!word.compare("add") || !word.compare("sub"))
    			return "arithmetic";
    		else if(!word.compare("eq") || !word.compare("lt") || !word.compare("gt"))
    			return "compare";
    		else if(!word.compare("and") || !word.compare("or") || !word.compare("neg") || !word.compare("not"))
    			return "boolop";
        else if(!word.compare("label"))
          return "label";
        else if(!word.compare("if-goto") || !word.compare("goto"))
          return "jump";
        else if(!word.compare("function"))
          return "function";
         else if(!word.compare("return"))
          return "return";
        else if(!word.compare("call"))
          return "call";
        else
    			return " ";
    	}
    	else
    		return " ";
     	
    }

string Parser :: arg1()
    {
    	iss>>word;
    	return word;
    }

    bool  Parser :: startswith(string s)
	{
	if (s.substr(0,2).compare("//")==0 || s.empty())
		return true;
	return false; 
	}	

