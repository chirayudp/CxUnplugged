# Compiler and flags
CC = gcc
cflags = -Wall -Wextra -std=c11

# Object files
objects = interface.o songs.o albums.o playlists.o

# Final executable name
targ = cunplugged
	
# Default rule
$(targ): $(objects)
	$(CC) $(cflags) $(objects) -o $(targ)

# Generic rule for compiling .c into .o
%.o: %.c
	$(CC) $(cflags) -c $< -o $@

# Clean up
clean:
	rm -f $(objects) $(targ)
