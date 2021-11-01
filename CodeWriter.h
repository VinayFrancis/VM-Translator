#ifndef CodeWriter_H
#define CodeWriter_H
#include<iostream>
#include <fstream>
#include<string>
#include<cstring>
#include<sstream>

class CodeWriter
{
private:
	std::ofstream write;
	std::string file;
	int counter;
	int icall;

public:
	CodeWriter(std::string filename);
	
	void bootstrap();
	void writestack_op(std::string op,std::string memory,std::string idx,std :: string fnname);
	
	void writearithmetic(std::string op);
	
	void writecompare(std::string op);
	
	void writeboolop(std::string op);

	void writelabel(std::string op,std::string memory,std::string fnname);

	void writejump(std::string op,std::string memory,std::string fnname);

	void writefunction(std::string op,std::string fnname, std::string args);


	void writereturn(std::string op);

	void writecall(std::string op,std::string fnname,std::string nVars);
	
};

#endif