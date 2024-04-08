
#include "fractol.h"

//inicialize all the variables needed for creating the window window and returns 1 on error
int	initiate(t_vars *v)
{
	v->mlx = mlx_init();
	if (!v->mlx)
		return (1);
	v->win = mlx_new_window(v->mlx, WIDTH, HEIGHT, "fractol");
	if (!v->win)
		return (1);
	v->img.img = mlx_new_image(v->mlx, WIDTH, HEIGHT);
	if (!v->img.img)
	{
		mlx_destroy_window(v->mlx, v->win);
		mlx_destroy_display(v->mlx);
		return (1);
	}
	v->img.addr = mlx_get_data_addr(v->img.img, &(v->img.bpp), \
				&(v->img.ll), &(v->img.endian));
	v->xoff = WIDTH / 2;
	v->yoff = HEIGHT / 2;
	v->zoom = 2;
	v->max_iter = MAX_ITER;
	return (0);
}

//this function parses only two arguments and gives default values 
//to julia (not specified) and returns 1 on error

static int	parse_two_args(char **av, t_vars *v)
{
	if (ft_strncmp(av[1], "m", 2))
		v->t = MANDELBROT;
	else if (ft_strncmp(av[1], "j", 2))
	{
		v->t = JULIA;
		v->juliax = -0.59;
		v->juliay = 0.54;
		v->max_iter = 10;
	}
	else if (ft_strncmp(av[1], "b", 2))
		v->t = BURNINGSHIP;
	else
		return (1);
	return (0);
}

void	parse_args(int ac, char **av, t_vars *v, int error)
{
	static char	s[] = "Usuage:\n./fractol [m]       (mandelbrot)\
		\n./fractol [b]       (burning ship)\
		\n./fractol [j [x y]] (julia with optional starting coordinates)\n";

	if (error)
	{
		write(2, s, sizeof(s) * sizeof(char));
		exit(1);
	}
	if (2 == ac && !parse_two_args(av, v));
	else if (4 == ac && ft_strncmp(av[1], "j", 2))
	{
		v->t = JULIA;
		v->juliax = ft_atof(av[2]);
		v->juliay = ft_atof(av[3]);
	}
	else
		parse_args(ac, av, v, 1);
}

void	select_set(t_vars *v)
{
	static char	s[] = "error: v->t value is incorrect";

	if (MANDELBROT == v->t)
		return (create_img_mandelbrot(v));
	if (JULIA == v->t)
		return (create_img_julia(v));
	if (BURNINGSHIP == v->t)
		return (create_img_burning(v));
	write(2, s, sizeof(s) * sizeof(char));
	exit(1);
}

int	main(int ac, char **av)
{
	t_vars	v;

	//parser
	parse_args(ac, av, &v, 0);

	//if the iniciation of variables returned an error
	if (initiate(&v))
		return (1);

	//selects which fractal to draw
	select_set(&v);

	//function to create an event listener to the keyboard
	mlx_key_hook(v.win, keyhook, &v);

	//function to create an event listener to the mouse
	mlx_mouse_hook(v.win, mousehook, &v);

	//an loop hook kinda like a game loop that is always running
	mlx_loop_hook(v.mlx, change_color, &v);

	//creating an exit (red button in top of the window) hook
	mlx_hook(v.win, 17, 0, finish, &v);

	//creating a event listener for mouse move
	mlx_hook(v.win, 6, 1L << 8, julia_mouse, &v);

	//this function is the one that keeps calling the loop hook
	mlx_loop(v.mlx);
}
