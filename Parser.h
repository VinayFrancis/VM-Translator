#ifndef Parser_H
#define Parser_H
#include<iostream>
#include <fstream>
#include<string>
#include<cstring>
#include<sstream>
class Parser
{

private:
	std::ifstream parse;
	std::string current;
	std::istringstream iss;
	std::string word;
	
public:
	
	
	void open_file(std::string inputfile);
	bool hasmorecommands();
	void advance();
  std::string commandtype();
  std::string arg1();
  bool startswith(std::string s);
	
};

#endif