
all: main1 main2 main3 main4 main5 main6


main1: main1.o music_notes_converter.o compare_files.o Decompress.o percent_match.o Compress.o 
	gcc -o main1 main1.o music_notes_converter.o -lmpg123 -lm compare_files.o Decompress.o percent_match.o Compress.o 

main2: main2.o music_notes_converter.o compare_files.o Decompress.o percent_match.o Compress.o 
	gcc -o main2 main2.o music_notes_converter.o -lmpg123 -lm compare_files.o Decompress.o percent_match.o Compress.o 

main3: main3.o music_notes_converter.o compare_files.o Decompress.o percent_match.o Compress.o 
	gcc -o main3 main3.o music_notes_converter.o -lmpg123 -lm compare_files.o Decompress.o percent_match.o Compress.o

# Targets without mpg123 dependency
main4: main4.o compare_files.o Decompress.o percent_match.o Compress.o
	gcc -o main4 main4.o compare_files.o Decompress.o percent_match.o Compress.o -lm

main5: main5.o music_notes_converter.o compare_files.o Decompress.o percent_match.o Compress.o
	gcc -o main5 main5.o music_notes_converter.o -lmpg123 -lm compare_files.o Decompress.o percent_match.o Compress.o

main6: main6.o music_notes_converter.o compare_files.o Decompress.o percent_match.o Compress.o
	gcc -o main6 main6.o music_notes_converter.o -lmpg123 -lm compare_files.o Decompress.o percent_match.o Compress.o


main1.o: main1.c
	gcc -c main1.c

main2.o: main2.c
	gcc -c main2.c

main3.o: main3.c
	gcc -c main3.c

main4.o: main4.c
	gcc -c main4.c

main5.o: main5.c
	gcc -c main5.c

main6.o: main6.c
	gcc -c main6.c
# Clean up object files and executables
clean:
	rm -f *.o main1 main2 main3 main4 main5 main6 

