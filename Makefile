CC = g++
CFLAGS = -Wall -g

output: main.o Parser.o CodeWriter.o
	$(CC) $(CFLAGS) main.o Parser.o CodeWriter.o -o output

main.o: main.cpp Parser.h
	$(CC) $(CFLAGS) -c main.cpp

Parser.o: Parser.cpp Parser.h
	$(CC) $(CFLAGS) -c Parser.cpp


CodeWriter.o: CodeWriter.cpp CodeWriter.h
	$(CC) $(CFLAGS) -c CodeWriter.cpp


clean:
	rm *.o output

help:
	@echo "enter make to get executable file "
	@echo "make clean to delete the object and output files"
	@echo "then enter 'output' and as command line input give the vm directory"
	@echo "a asm file will be created in the folder which contains the VM file" 

