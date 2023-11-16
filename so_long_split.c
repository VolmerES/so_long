/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelorme <jdelorme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:16:48 by jdelorme          #+#    #+#             */
/*   Updated: 2023/11/16 18:36:42 by jdelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*            || PARTE DE CODIGO DEL JUEGO ||								
 ! Comprobacion de que el mapa es de extension .ber 							
 * Funcion de lectura del mapa con GNL										
 ! Comprobacion que el mapa contenga P, E, C y las paredes sean 1 			
 ! Hacer que al presionar "X" tecla se mueva hacia esa posicion 				
 ! Funcion para contar los pasos reales que da el jugador 					
 ! Que el jugador no pueda entrar dentro de las paredes */						

#include "mlx/mlx.h"
#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <fcntl.h>
#include "libft/libft.h"

# define KEY_ESC		53
# define KEY_W			13
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2
# define ARROW_UP		126
# define ARROW_DOWN		125
# define ARROW_LEFT		123
# define ARROW_RIGHT	124

typedef struct s_vars
{
	void	*mlx;
	void	*mlx_win;
}				t_vars;

typedef struct s_game
{
	char	*game;
	char 	*map_line;
	char	**map_matrix;
	int		map_x;
	int		map_y;
	int		p_y;
	int		p_x;
}				t_game;

void	ft_error(char *error)
{
	ft_putstr_fd (error, 1);
	exit (1);
}
int	ft_path_cross_checker(t_game *game)
{
// ! 
}
void	ft_check_for_path(t_game *game)
{
	// ! Reservar espacio para hacer una copia de mi mapa, para rellenarla de unos ya quqe la vamos a destrozar
	// ! Mientras haya contenido en mi matriz hacer una copia con strdup
	// ! 
	ft_path_cross_checker(game) != 1)
		
}

void	ft_check_for_elements(t_game *game)
{
	int y;
	int j;
	int k;
	int e;
	int x;

	y = -1;
	j = 0;
	k = 0;
	e = 0;
	while (game->map_matrix[++y])
	{
		x = -1;
		while (game->map_matrix[y][++x])
		{
			if (game->map_matrix[y][x] == 'C')
				j++;
			if (game->map_matrix[y][x] == 'E')
				k++;
			if (game->map_matrix[y][x] == 'P')
				e++;
		}
	}
	if (j != 1 || k != 1 || e != 1)
		ft_error("Error: Invalid Map (Not enough elements)");
}

void	ft_check_for_characters(t_game *game)
{
	int	x;
	int y;
	
	x = -1;
	y = -1;
	while (game->map_matrix[++y])
	{
		x = -1;
		while (game->map_matrix[y][++x]) 
		{
			if (game->map_matrix[y][x] == 'P')
			{
				game->p_x = x;
				game->p_y = y;
			}
			if (((game->map_matrix[y][x] != 'C'
					&& game->map_matrix[y][x] != 'E' &&
					game->map_matrix[y][x] != 'P' && game->map_matrix[y][x] != '1' &&
					game->map_matrix[y][x] != '0')))
			{
				ft_error("Error: Invalid map (Invalid characters)");
			}
		}
	}
}

void	ft_check_for_walls(t_game *game)
{
	int	x;
	int y;
	
	y = -1;
	printf("%i \n", game->map_y);
	while (game->map_matrix[++y])
	{
		x = -1;
		while (game->map_matrix[y][++x])
		{
			if (game->map_matrix[0][x] != '1'|| game->map_matrix[game->map_y - 1][x] != '1')
				ft_error("ERROR ONE");
			else if (game->map_matrix[y][0] != '1' || game->map_matrix[y][game->map_x - 1] != '1')
				ft_error("error two");
		}
	}
}
void	ft_check_for_rectangle(t_game *game)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	game->map_x = ft_strlen(game->map_matrix[j]);
	j = -1;
	while(game->map_matrix[++j])
	{
		if(game->map_x != ft_strlen(game->map_matrix[j]))
			ft_error("square");
	}
	game->map_y = j;
}

void	ft_check_valid_map(t_game *game)
{
	ft_check_for_elements(game);
	ft_check_for_characters(game);
	ft_check_for_rectangle(game);
	ft_check_for_walls(game);
	// ft_check_for_path(game);
}
char	**ft_split_the_map(t_game *game)
{
	game->map_matrix = ft_split(game->map_line, '\n');
	return(game->map_matrix);
}
void	ft_read_map(t_game *game)
{
	int		fd;
	char	readed;
	// ! Llamar a funcion para verificar si es .bER
	
	fd = open("./Maps/map.ber", O_RDONLY);
	game->map_line = malloc((BUFFER_SIZE) * sizeof(char));
	readed = read(fd, game->map_line, BUFFER_SIZE);
	if (readed == -1)
		ft_error("READMAP ERROR");
	game->map_line[readed] = '\0';
	printf("%s \n", game->map_line);
	close(fd);
	ft_split_the_map(game);
	ft_check_valid_map(game);
}

int	ft_deal_key(int key, t_vars *vars)
{
	if (key == KEY_A)
		printf("Ha presionado A \n");
	if (key == KEY_W)
		printf("Ha presionado W \n");
	if (key == KEY_S)
		printf("Ha presionado S \n");
	if (key == KEY_D)
		printf("Ha presionado D \n");
	if (key == ARROW_RIGHT)
		printf("Ha presionado DERECHA \n");
	if (key == ARROW_LEFT)
		printf("Ha presionado IZQUIERDA \n");
	if (key == ARROW_DOWN)
		printf("Ha presionado ABAJO \n");
	if (key == ARROW_UP)
		printf("Ha presionado ARRIBA \n");
	if (key == KEY_ESC)
	{
		printf("Ha presionado ESC \n");
		mlx_destroy_window(vars->mlx, vars->mlx_win);
		exit (1);
	}
	return 0;
}

int	ft_close(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->mlx_win);
	exit (1);
	return (0);
}

int	main(void)
{
	t_game	game;
	t_vars	vars;
	
	vars.mlx = mlx_init();
	vars.mlx_win = mlx_new_window(vars.mlx, 1080, 1080, "so_long");
	mlx_key_hook(vars.mlx_win, ft_deal_key, &vars);
	mlx_hook(vars.mlx_win, 17, 0, ft_close, &vars);
	ft_read_map(&game);
	// ! mlx_loop_hook(vars.mlx, &ft_steps, &vars);
	mlx_loop(vars.mlx);
	return 0;
}
