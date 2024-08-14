assembler: transitions.o assembler.o secondEncoding.o checkCommands.o symbols.o writeFiles.o encodeCheck.o tables.o bits.o structs.h constants.h main.h
	gcc -g -Wall -ansi -pedantic transitions.o assembler.o secondEncoding.o checkCommands.o writeFiles.o symbols.o encodeCheck.o tables.o bits.o -o assembler -lm
assembler.o: assembler.c structs.h constants.h
	gcc -c -Wall -ansi -pedantic assembler.c -o assembler.o
transitions.o: transitions.c structs.h encoder.h constants.h main.h write.h
	gcc -c -Wall -ansi -pedantic transitions.c -o transitions.o
secondEncoding.o: secondEncoding.c structs.h encoder.h constants.h main.h
	gcc -c -Wall -ansi -pedantic secondEncoding.c -o secondEncoding.o
checkCommands.o: checkCommands.c structs.h encoder.h constants.h main.h
	gcc -c -Wall -ansi -pedantic checkCommands.c -o checkCommands.o -lm
symbols.o: symbols.c structs.h constants.h main.h
	gcc -c -Wall -ansi -pedantic symbols.c -o symbols.o
writeFiles.o: writeFiles.c structs.h encoder.h constants.h main.h
	gcc -c -Wall -ansi -pedantic writeFiles.c -o writeFiles.o
encodeCheck.o: encodeCheck.c structs.h encoder.h constants.h
	gcc -c -Wall -ansi -pedantic encodeCheck.c -o encodeCheck.o
tables.o: tables.c structs.h constants.h
	gcc -c -Wall -ansi -pedantic tables.c -o tables.o
bits.o: bits.c structs.h constants.h main.h
	gcc -c -Wall -ansi -pedantic bits.c -o bits.o