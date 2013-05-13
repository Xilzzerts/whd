CC = gcc
CFLAGS = -Wall

out.o : rio.o main.o whd.o
	$(CC) $(CFLAGS) $^ -o $@


rio.o : rio/rio.c rio/rio.h
	$(CC) $(CFALGS) -c $< -o $@

main.o : main.c headerc.h whd.h
	$(CC) $(CFLAGS) -c $< -o $@

whd.o : whd.c headerc.h whd.h rio/rio.h
	$(CC) $(CFLAGS) -c $< -o $@ -lpthread

.PHONY : clean
clean : 
	rm *.o
