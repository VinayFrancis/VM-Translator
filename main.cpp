#include "parser.h"
#include "CodeWriter.h"
#include <dirent.h>
using namespace std;


int main(int arg, char ** directory)
{
	
	string folder=directory[1];
	string folder1;
	int strt=folder.find_last_of("/");
	folder1=folder+"/"+folder.substr(strt+1);
	

	DIR *dr;
   	struct dirent *en;
   	int pos;
   	string file;
   	string op;
	string memory;
	string idx;
	string cdtype;
	string fnname;
	string filename;
   	dr = opendir(folder.c_str()); //open all directory
   	if (dr) 
   	{
   		CodeWriter translate(folder1);
   		translate.bootstrap();
   		Parser parser;
   		while ((en = readdir(dr)) != NULL) 
   		{
   			file=en->d_name;
   			
      		pos=file.find(".");
      		if(file.substr(pos+1)=="vm")
      			
      			{
      				pos=file.find(".");
      				filename=file.substr(0,pos);
      				
      				file = folder+"/"+file;
      				parser.open_file(file);
     
					
					

					
					while(parser.hasmorecommands())
					{
						parser.advance();

						cdtype=parser.commandtype();
						

						if(!cdtype.compare("stack_op"))
							{
								op=parser.arg1();
								memory=parser.arg1();
								idx=parser.arg1();
								translate.writestack_op(op,memory,idx,filename);
								
								
							}
						else if(!cdtype.compare("arithmetic"))
							{
								op=parser.arg1();
								translate.writearithmetic(op);
										
							}
						else if(!cdtype.compare("compare"))
							{
								op=parser.arg1();
								translate.writecompare(op);
										
							}
						else if(!cdtype.compare("boolop"))
							{
								op=parser.arg1();
								translate.writeboolop(op);
										
							}
						else if(!cdtype.compare("label"))
						{
							op=parser.arg1();
							memory=parser.arg1();
							translate.writelabel(op,memory,fnname);
						}
						else if(!cdtype.compare("jump"))
						{
							op=parser.arg1();
							memory=parser.arg1();
							translate.writejump(op,memory,fnname);
						}

						else if(!cdtype.compare("function"))
						{
							op=parser.arg1();
							fnname=parser.arg1();
							idx=parser.arg1();
							translate.writefunction(op,fnname,idx);
						}
						else if(!cdtype.compare("return"))
						{
							op=parser.arg1();
							translate.writereturn(op);
						}
						else if(!cdtype.compare("call"))
						{
							op=parser.arg1();
							fnname=parser.arg1();
							idx=parser.arg1();
							translate.writecall(op,fnname,idx);
						}
						else
							continue;
					
					}
					

      			}
      }
      closedir(dr); 
   }

	return 0;
}