#makefile for TP_Lab_5_Console_Application
run: bin/TP_Lab_5_Console_Application
	./bin/TP_Lab_5_Console_Application
bin/TP_Lab_5_Console_Application: obj/db_functions.o obj/main.o  
	gcc -l sqlite3 -o bin/TP_Lab_5_Console_Application obj/db_functions.o obj/main.o
obj/db_functions.o: src/db_functions.c
	gcc -l sqlite3 -c src/db_functions.c -o obj/db_functions.o 
obj/main.o: src/main.cS
	gcc -l sqlite3 -c src/main.c -o obj/main.o 

