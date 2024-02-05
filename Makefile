CC=cc
CFLAGS= -Wextra -Wall -Werror -O3 
NAME= fractol
SRC:= burning.c  hooks.c  julia.c  main.c  mandelbrot.c  utils.c cubic_mandelbrot.c
OBJ:=$(SRC:.c=.o)
lib= -lXext -lX11 -lmlx -lm

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(lib)
%.o : %.c fractol.h
	$(CC) $(CFLAGS) -c $< -o $@
clean :
	rm -rf $(OBJ)
fclean : clean
	rm -rf $(NAME)
re : fclean $(NAME)
