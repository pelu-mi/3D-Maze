# Make Betty checks silent
.SILENT: betty

# Specify compiler
CC = gcc

# Source files
SRC = src/*.c

# Executable name
NAME = 3D-maze

# RM + flags
RM = rm -f

# Compiler flags
CFLAGS = -O2 -g -Wall -Werror -Wextra -pedantic -Iheaders

# Linker flags
LFLAGS = -lSDL2 -lSDL2_image -lm

# SDL flags
SDLFLAGS = `sdl2-config --cflags --libs`


# Compiles executable
all: $(SRC)
	$(CC) $(SRC) $(CFLAGS) $(LFLAGS) -o $(NAME) $(SDLFLAGS)

# Remove temporary files and executable
clean:
	$(RM) *~ $(NAME)

# Betty checks
betty:
	betty-style --allow-global-variables $(SRC); \
	betty-doc $(SRC)
