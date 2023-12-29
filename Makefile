CC=cc
CFLAGS= -Wextra -Wall -O3 
NAME=a.out
SRC:=$(wildcard *.c)
OBJ:=$(SRC:.c=.o)
mlx=$(wildcard *.a)
lib=  -lXext -lX11

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(mlx) $(lib)
test : $(NAME)
	./$(NAME)
clean :
	rm -rf $(OBJ)
fclean : clean
	rm -rf $(NAME)
re : fclean $(NAME)
