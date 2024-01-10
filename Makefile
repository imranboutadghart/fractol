CC=cc
CFLAGS= -Wextra -Wall -g -O3 
NAME=fractol
SRC:=$(wildcard *.c)
OBJ:=$(SRC:.c=.o)
mlx=$(wildcard *.a)
lib=  -lXext -lX11 -lmlx -lm

all : $(NAME)

$(NAME) : $(OBJ) $(mlx)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(mlx) $(lib)
%.o : %.c fractol.h
	$(CC) $(CFLAGS) -c $< -o $@
test : $(NAME)
	./$(NAME)
clean :
	rm -rf $(OBJ)
fclean : clean
	rm -rf $(NAME)
re : fclean $(NAME)
