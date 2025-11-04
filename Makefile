CFLAGS = -O2 -g -Wall -Wextra

dbi: memfrob.o 
	$(CC) $(CFLAGS) memfrob.o -o memfrob

install: memfrob
	@sudo mkdir -p /usr/local/bin
	@sudo cp memfrob /usr/local/bin && echo "memfrob installed at /usr/local/bin/memfrob"

uninstall:
	@sudo rm -f /usr/local/bin/memfrob

clean:
	rm -f memfrob *.o

