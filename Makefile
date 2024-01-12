CC=cc
CFLAGS= -Wextra -Wall -Werror -O3 
NAME= fractol
SRC:= burning.c  hooks.c  julia.c  main.c  mandelbrot.c  utils.c cubic_mandelbrot.c
OBJ:=$(SRC:.c=.o)
lib= -lXext -lX11 -lmlx -lm

all : $(NAME)

$(NAME) : $(OBJ) $(mlx)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(mlx) $(lib)
%.o : %.c fractol.h
	$(CC) $(CFLAGS) -c $< -o $@
test : $(NAME)
	./$(NAME) $(p1) $(p2) $(p3)
	make clean
clean :
	rm -rf $(OBJ)
fclean : clean
	rm -rf $(NAME)
re : fclean $(NAME)
