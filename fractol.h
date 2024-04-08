#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <mlx.h>
# include <math.h>
# include <unistd.h>

//defining the width and height and inicial zoom of the window
# define WIDTH 1600
# define HEIGHT 1000
# define ZOOM 200

//defining the keys to move (for linux)
# define UP    65362
# define DOWN  65364
# define LEFT  65361
# define RIGHT 65363
# define MAX_ZOOM 4194304
# define MAX_ITER 50

//defining fractals
# define MANDELBROT 0
# define JULIA 1
# define BURNINGSHIP 2

//struct for the window's images informations
typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		ll;
	int		endian;
}				t_data;

//struct to pass as parameter to functions holds most informations needed
typedef struct s_vars
{
	t_data	img;
	void	*mlx;
	void	*win;
	
	//julia variables if the type is set to julia
	double	juliax;
	double	juliay;

	//zoom gets multiplied by ZOOM macro
	long	zoom;

	//x and y offsets from the (0, 0)
	int		xoff;
	int		yoff;

	//iterations to not overcalculate(it provides depth if it is large)
	int		max_iter;

	//type
	char	t;
}			t_vars;

//this function parses and selects which set to draw
void	select_set(t_vars *v);

//this function is a parser except when called with 1 in last arg it exits with usuage message
void	parse_args(int ac, char **av, t_vars *v, int error);

//these function create the fractal
//they all call mlx_put_image_to_window before returning to push the image that has been drawn to the window
void	create_img_julia(t_vars *v);
void	create_img_mandelbrot(t_vars *v);
void	create_img_burning(t_vars *v);

//this function puts a color in a pixel
void	put_in_pixel(t_data *img, int x, int y, int c);

//this hooks to the mouse and it is the one responsible for the zoom
int		mousehook(int button, int x, int y, t_vars *v);

//same but for keys and it is responsible for moving the window
int		keyhook(int keycode, t_vars *v);

//these gets called on repeat and it does the psychedelic effects
int		change_color(t_vars *v);
void	shift_color(t_data *img, double i, double j);

//this is for mouse moving in julia (note: it is pretty slow, a little faster in macs than linux though)
int		julia_mouse(int x, int y, t_vars *v);

//this function clears evrrything at the end
int		finish(t_vars *v);

//utinlities
int		ft_strncmp(char *s1, char *s2, size_t n);
double	ft_atof(char *s);

#endif //FRACTOL_H
