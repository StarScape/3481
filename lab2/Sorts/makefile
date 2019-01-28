CC=gcc -ggdb

sort: sort.o bubbleSort.o mergeSort.o quickSort.o 
	$(CC) sort.o bubbleSort.o mergeSort.o quickSort.o -o Sort

bubbleSort.o: bubbleSort.c bubbleSort.h 
mergeSort.o: mergeSort.c mergeSort.h
quickSort.o: quickSort.c quickSort.h
sort.o: sort.c bubbleSort.h mergeSort.h quickSort.h types.h

clean:
	rm -f *.o
