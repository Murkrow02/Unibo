main: main.o TranslationTable.o Utils.o SymbolTable.o
	gcc -o assembler main.o TranslationTable.o Utils.o SymbolTable.o

main.o: main.c Headers/TranslationTable.h Headers/Utils.h Headers/SymbolTable.h
	gcc -c main.c
	
TranslationTable.o: TranslationTable.c Headers/TranslationTable.h Headers/Utils.h
	gcc -c TranslationTable.c

SymbolTable.o: SymbolTable.c Headers/SymbolTable.h Headers/Utils.h
	gcc -c SymbolTable.c

Utils.o: Utils.c Headers/Utils.h
	gcc -c Utils.c

clean:
	rm *.o
