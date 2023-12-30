CC=cc
CFLAGS= -Wextra -Wall -O3
NAME=a.out
SRC:=$(wildcard *.c)
OBJ:=$(SRC:.c=.o)
mlx=$(wildcard *.a)
lib=  -lXext -lX11

all : $(NAME)

$(NAME) : $(OBJ) $(mlx)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(mlx) $(lib)
fractol.o : fractol.c fractol.h
	$(CC) $(CFLAGS) -c $< -o $@
test : $(NAME)
	./$(NAME)
clean :
	rm -rf $(OBJ)
fclean : clean
	rm -rf $(NAME)
re : fclean $(NAME)
