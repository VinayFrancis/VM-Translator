#include "CodeWriter.h"

using namespace std;

CodeWriter::CodeWriter(string filename)
	{
		
		int strt=filename.find_last_of("/");
		file=filename.substr(strt+1);
		counter=0;
		icall=0;
		write.open(filename+".asm");
	}

	void CodeWriter::bootstrap()
	{
		write<<"@256\n";
		write<<"D=A\n";
		write<<"@SP\n";
		write<<"M=D\n";
		write<<"@SP\n";
		write<<"A=M\n";
		write<<"M=-1\n";
		write<<"@SP\n";
		write<<"M=M+1\n";
		write<<"@SP\n";
		write<<"A=M\n";
		write<<"M=-1\n";
		write<<"@SP\n";
		write<<"M=M+1\n";
		write<<"@SP\n";
		write<<"A=M\n";
		write<<"M=0\n";
		write<<"@SP\n";
		write<<"M=M+1\n";
		write<<"@SP\n";
		write<<"A=M\n";
		write<<"M=-1\n";
		write<<"@SP\n";
		write<<"M=M+1\n";
		write<<"@SP\n";
		write<<"A=M\n";
		write<<"M=0\n";
		write<<"@SP\n";
		write<<"M=M+1\n";
		write<<"@Sys.init\n";
		write<<"0;JMP\n";

	}

	void CodeWriter::writestack_op(string op,string memory,string idx,string fnname)
	{
		write<<"\n//"<<op<<" "<<memory<<" "<<idx<<"\n";
		
			
		if(op=="push")
		{
			if(memory=="constant")
			{
				write<<"@"<<idx<<"\n";
				write<<"D=A\n";
			}
			else if(memory=="local")
				{
					write<<"@"<<idx<<"\n";
					write<<"D=A\n";
					write<<"@LCL\n";
					write<<"A=M+D\n";
					write<<"D=M\n";
				}
			else if(memory=="argument")
				{
					write<<"@"<<idx<<"\n";
					write<<"D=A\n";
					write<<"@ARG\n";
					write<<"A=M+D\n";
					write<<"D=M\n";
				}
			
			else if(memory=="this")
			{
				
				write<<"@"<<idx<<"\n";
				write<<"D=A\n";
				write<<"@THIS\n";
				write<<"A=M+D\n";
				write<<"D=M\n";
			}
			
			else if(memory=="that")
			{	
				write<<"@"<<idx<<"\n";
				write<<"D=A\n";
				write<<"@THAT\n";
				write<<"A=M+D\n";
				write<<"D=M\n";
			}

			else if(memory=="temp")
			{
				write<<"@"<<idx<<"\n";
				write<<"D=A\n";
				write<<"@5\n";
				write<<"A=A+D\n";
				write<<"D=M\n";
			}
			else if(memory=="pointer")
			{
				if(idx=="0")
					write<<"@THIS\n";
				else
					write<<"@THAT\n";
				write<<"D=M\n";
			}
			else if(memory=="static")
			{

				write<<"@"<<fnname<<"."<<idx<<"\n";
				write<<"D=M\n";
			}
			

			write<<"@SP\n";
			write<<"A=M\n";
			write<<"M=D\n";
			write<<"@SP\n";
			write<<"M=M+1\n";

		}
		else
		{
			if(memory=="local")
				{
					write<<"@"<<idx<<"\n";
					write<<"D=A\n";
					write<<"@LCL\n";
					write<<"D=M+D\n";
					
				}
			else if(memory=="argument")
				{
					write<<"@"<<idx<<"\n";
					write<<"D=A\n";
					write<<"@ARG\n";
					write<<"D=M+D\n";
					
				}
			
			else if(memory=="this")
			{
				
				write<<"@"<<idx<<"\n";
				write<<"D=A\n";
				write<<"@THIS\n";
				write<<"D=M+D\n";
				
			}
			
			else if(memory=="that")
			{	
				write<<"@"<<idx<<"\n";
				write<<"D=A\n";
				write<<"@THAT\n";
				write<<"D=M+D\n";
				
			}

			else if(memory=="temp")
			{
				write<<"@"<<idx<<"\n";
				write<<"D=A\n";
				write<<"@5\n";
				write<<"D=A+D\n";
			}
			else if(memory=="pointer")
			{
				if(idx=="0")
					write<<"@THIS\n";
				else
					write<<"@THAT\n";
				write<<"D=A\n";
			}
			else if(memory=="static")
			{

				write<<"@"<<fnname<<"."<<idx<<"\n";
				write<<"D=A\n";
			}

			
			write<<"@R13\n";
			write<<"M=D\n";
			
			write<<"@SP\n";
			write<<"M=M-1\n";
			write<<"A=M\n";
			write<<"D=M\n";
			
			write<<"@R13\n";
			write<<"A=M\n";
			write<<"M=D\n";

			
			
		}
		
	}

	void CodeWriter::writearithmetic(string op)
	{
		

		write<<"\n//"<<op<<"\n";
		write<<"@SP\n";
		write<<"M=M-1\n";
		write<<"A=M\n";
		write<<"D=M\n";

		write<<"A=A-1\n";
		

		if(op=="add")
			write<<"M=M+D\n";
		else
			write<<"M=M-D\n";

	}

	void CodeWriter::writecompare(string op)
	{

		write<<"\n//"<<op<<"\n";
		counter+=1;

		if(op=="eq")
		{
			write<<"@SP\n";
			write<<"M=M-1\n";
			write<<"A=M\n";
			write<<"D=M\n";
			write<<"A=A-1\n";
			write<<"D=M-D\n";
			
			write<<"@EQ."<<counter<<"\n";
			write<<"D;JEQ\n";
			write<<"@SP\n";
			write<<"A=M-1\n";
			write<<"M=0\n";

			write<<"@END.EQ."<<counter<<"\n";
			write<<"0;JMP\n";

			write<<"(EQ."<<counter<<")"<<"\n";
			write<<"@SP\n";
			write<<"A=M-1\n";
			write<<"M=-1\n";

			write<<"(END.EQ."<<counter<<")"<<"\n";


		}
		else if(op=="lt")
		{

			write<<"@SP\n";
			write<<"M=M-1\n";
			write<<"A=M\n";
			write<<"D=M\n";
			write<<"A=A-1\n";
			write<<"D=M-D\n";
			
			write<<"@LT."<<counter<<"\n";
			write<<"D;JLT\n";
			write<<"@SP\n";
			write<<"A=M-1\n";
			write<<"M=0\n";

			write<<"@END.LT."<<counter<<"\n";
			write<<"0;JMP\n";

			write<<"(LT."<<counter<<")"<<"\n";
			write<<"@SP\n";
			write<<"A=M-1\n";
			write<<"M=-1\n";

			write<<"(END.LT."<<counter<<")"<<"\n";
		
		}
		else if(op=="gt")
		{

			write<<"@SP\n";
			write<<"M=M-1\n";
			write<<"A=M\n";
			write<<"D=M\n";
			write<<"A=A-1\n";
			write<<"D=M-D\n";
			
			write<<"@GT."<<counter<<"\n";
			write<<"D;JGT\n";
			write<<"@SP\n";
			write<<"A=M-1\n";
			write<<"M=0\n";

			write<<"@END.GT."<<counter<<"\n";
			write<<"0;JMP\n";

			write<<"(GT."<<counter<<")"<<"\n";
			write<<"@SP\n";
			write<<"A=M-1\n";
			write<<"M=-1\n";

			write<<"(END.GT."<<counter<<")"<<"\n";


		
		}

	}

	void CodeWriter::writeboolop(string op)
	{
		write<<"\n//"<<op<<"\n";
		if(op=="and")
		{
			write<<"@SP\n";
			write<<"M=M-1\n";
			write<<"A=M\n";
			write<<"D=M\n";

			write<<"A=A-1\n";
			write<<"M=M&D\n";

		}

		else if(op=="or")
		{
			write<<"@SP\n";
			write<<"M=M-1\n";
			write<<"A=M\n";
			write<<"D=M\n";

			write<<"A=A-1\n";
			write<<"M=M|D\n";
		}

		else if(op=="not")
		{

			write<<"@SP\n";
			write<<"A=M-1\n";
			
			write<<"M=!M\n";
		}

		else if(op=="neg")
		{

			write<<"@SP\n";
			write<<"A=M-1\n";
			
			write<<"M=-M\n";
		}
	}

	void CodeWriter::writelabel(string op,string labelname,string fnname)
	{
		write<<"("<<fnname<<"$"<<labelname<<")\n";

	}

	void CodeWriter::writejump(string op,string labelname,string fnname)
	{
		if(op=="if-goto")
		{
			write<<"@SP\n";
			write<<"M=M-1\n";
			write<<"A=M\n";
			write<<"D=M\n";

			write<<"@"<<fnname<<"$"<<labelname<<"\n";
			write<<"D;JNE\n";
		}
	
		else if(op=="goto")
		{
			write<<"@"<<fnname<<"$"<<labelname<<"\n";
			write<<"0;JMP\n";
		}
		


	}

	void CodeWriter::writefunction(string op,string fnname,string args)
	{
		write<<"\n//"<<op<<" "<<fnname<<" "<<args<<"\n";
		int localvars = stoi(args);

		write<<"("<<fnname<<")\n";
		while(localvars>0)
		{
			write<<"@SP\n";
			write<<"A=M\n";
			write<<"M=0\n";
			write<<"@SP\n";
			write<<"M=M+1\n";
			localvars--;
		}


	}

	void CodeWriter::writereturn(string op)
	{
			write<<"\n//"<<op<<"\n";
		
		write<<"//to get the endframei.e starting of LCL it is stored in 5\n";
		write<<"@LCL\n";
		write<<"D=M\n";
		write<<"@R13\n";
		write<<"M=D\n";


		write<<"//6 has retAdress\n";
		write<<"@5\n";
		write<<"D=A\n";
		write<<"@R13\n";
		write<<"D=M-D\n";
		write<<"A=D\n";
		write<<"D=M\n";
		write<<"@R14\n";
		write<<"M=D\n";

		write<<"//*ARG = pop()\n";
		write<<"@SP\n";
		write<<"A=M-1\n";
		write<<"D=M\n";
		write<<"@ARG\n";
		write<<"A=M\n";
		write<<"M=D\n";

		write<<"//SP=ARG+1\n";
		write<<"@ARG\n";
		write<<"D=M+1\n";
		write<<"@SP\n";
		write<<"M=D\n";


		write<<"//THAT = *(endFrame – 1)\n";
		write<<"@R13\n";
		write<<"D=M\n";
		write<<"@1\n";
		write<<"D=D-A\n";

		write<<"A=D\n";
		write<<"D=M\n";
		write<<"@THAT\n";
		write<<"M=D\n";

		write<<"//THIS = *(endFrame – 2)\n";
		write<<"@R13\n";
		write<<"D=M\n";
		write<<"@2\n";
		write<<"D=D-A\n";

		write<<"A=D\n";
		write<<"D=M\n";
		write<<"@THIS\n";
		write<<"M=D\n";

		write<<"//ARG = *(endFrame – 3)\n";
		write<<"@R13\n";
		write<<"D=M\n";
		write<<"@3\n";
		write<<"D=D-A\n";

		write<<"A=D\n";
		write<<"D=M\n";
		write<<"@ARG\n";
		write<<"M=D\n";

		write<<"//LCL = *(endFrame – 4)\n";
		write<<"@R13\n";
		write<<"D=M\n";
		write<<"@4\n";
		write<<"D=D-A\n";

		write<<"A=D\n";
		write<<"D=M\n";
		write<<"@LCL\n";
		write<<"M=D\n";

		write<<"@R14\n";
		write<<"A=M\n";
		write<<"0;JMP\n";


	
	}

	void CodeWriter::writecall(string op,string fnname,string nVars)
	{
		icall=icall+1;
		write<<"\n//"<<op<<" "<<fnname<<" "<<nVars<<"\n";
		
		write<<"\n//storing return address\n";
		write<<"@"<<fnname<<"$ret"<<icall<<"\n";
		write<<"D=A\n";
		write<<"@SP\n";
		write<<"A=M\n";
		write<<"M=D\n";
		write<<"@SP\n";
		write<<"M=M+1";

		write<<"\n//storing LCL address\n";
		write<<"@LCL\n";
		write<<"D=M\n";
		write<<"@SP\n";
		write<<"A=M\n";
		write<<"M=D\n";
		write<<"@SP\n";
		write<<"M=M+1";

		write<<"\n//storing ARG address\n";
		write<<"@ARG\n";
		write<<"D=M\n";
		write<<"@SP\n";
		write<<"A=M\n";
		write<<"M=D\n";
		write<<"@SP\n";
		write<<"M=M+1";

		write<<"\n//storing THIS address\n";
		write<<"@THIS\n";
		write<<"D=M\n";
		write<<"@SP\n";
		write<<"A=M\n";
		write<<"M=D\n";
		write<<"@SP\n";
		write<<"M=M+1";

		write<<"\n//storing THAT address\n";
		write<<"@THAT\n";
		write<<"D=M\n";
		write<<"@SP\n";
		write<<"A=M\n";
		write<<"M=D\n";
		write<<"@SP\n";
		write<<"M=M+1";

		write<<"\n//changing LCL address\n";
		write<<"@SP\n";
		write<<"D=M\n";
		write<<"@LCL\n";
		write<<"M=D\n";
		
		write<<"\n//finding SP-5-nvargs \n";
		write<<"@SP\n";
		write<<"D=M\n";
		write<<"@5\n";
		write<<"D=D-A\n";
		write<<"@"<<nVars<<"\n";
		write<<"D=D-A\n";


		write<<"@ARG\n";
		write<<"M=D\n";

		write<<"@"<<fnname<<"\n";
		write<<"0;JMP\n";

		write<<"("<<fnname<<"$ret"<<icall<<")\n";

		
	}
	