##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## Makefile
##

CC = g++

SRC = $(shell find . -name "*.cpp")

NAME = MyGKrellm

OBJ = $(SRC:.cpp=.o)

CXXFLAGS = -Wall -Wextra -Werror

SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system

all: $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(SFML_FLAGS) -lncurses

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

