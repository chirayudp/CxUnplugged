# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Object files
OBG = interface.o songs.o albums.o playlists.o log.o

# Final executable name
TARG = cunplugged
	
# Default rule
$(TARG): $(OBG)
	$(CC) $(CFLAGS) $(OBG) -o $(TARG)

# Generic rule for compiling .c into .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBG) $(TARG)
