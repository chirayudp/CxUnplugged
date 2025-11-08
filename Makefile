# Compiler to use
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Target program name
TARGET = cunplugged

# Source files
OBJS = main.o songs.o

# Rule to build final program
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Rule to compile .c -> .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(TARGET) $(OBJS)
