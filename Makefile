CC=cc
CFLAGS= -Wextra -Wall -O3 -I. 
NAME= fractol
SRC:= burning.c  hooks.c  julia.c  main.c  mandelbrot.c  utils.c
SRC:=$(patsubst %, src/%, $(SRC))
OBJ:=$(patsubst src/%.c, obj/%.o, $(SRC))
lib= -lmlx -lXext -lX11 -lm

all : $(NAME)

$(NAME) : objdir $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(lib)

obj/%.o : src/%.c fractol.h
	$(CC) $(CFLAGS) -c $< -o $@

objdir :
	mkdir -p obj

clean :
	rm -rf $(OBJ)
	rmdir obj

fclean : clean
	rm -rf $(NAME)

re : fclean $(NAME)

test : all
	./$(NAME) m

.PHONY : all clean fclean re objdir
