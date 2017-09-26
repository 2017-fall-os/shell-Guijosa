all: shell

shell: shell.o mytoc.o
	cc -o $@ $^
shell.o: shell.c mytoc.h
	cc -c -g shell.c
mytoc.o: mytoc.c 
	cc -c -g mytoc.c
clean:
	rm -f *.o *~ shell
