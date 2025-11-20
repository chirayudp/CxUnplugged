CC = gcc
CFLAGS = -Wall -Wextra -std=c11

OBJS = interface.o songs.o albums.o playlists.o log.o

TARG = cunplugged

$(TARG): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARG)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARG)
