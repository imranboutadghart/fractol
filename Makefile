CC=cc
CFLAGS= -Wextra -Wall -O3 -I. -Iminilibx-linux
NAME= fractol
SRC:= burning.c  hooks.c  julia.c  main.c  mandelbrot.c  utils.c
SRC:=$(patsubst %, src/%, $(SRC))
OBJ:=$(patsubst src/%.c, obj/%.o, $(SRC))
lib= -Lminilibx-linux -lmlx -lXext -lX11 -lm
MLX=minilibx-linux/libmlx.a

all : $(MLX) $(NAME)

$(MLX) :
	make -C minilibx-linux

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
	make clean -C minilibx-linux

re : fclean $(NAME)

test : all
	./$(NAME) m

.PHONY : all clean fclean re objdir
