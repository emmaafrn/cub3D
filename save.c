/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:02:25 by efarin            #+#    #+#             */
/*   Updated: 2021/04/28 13:02:27 by efarin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned char	*create_bitmap_file_header(int file_size)
{
	static unsigned char	file_header[] = {
		0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
	};

	file_header[0] = (unsigned char)('B');
	file_header[1] = (unsigned char)('M');
	file_header[2] = (unsigned char)(file_size);
	file_header[3] = (unsigned char)(file_size >> 8);
	file_header[4] = (unsigned char)(file_size >> 16);
	file_header[5] = (unsigned char)(file_size >> 24);
	file_header[10] = (unsigned char)(14 + 40);
	return (file_header);
}

unsigned char	*create_bitmap_info_header(t_state *state)
{
	static unsigned char	info_header[] = {
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0,
		0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
	};

	info_header[0] = (unsigned char)(40);
	info_header[4] = (unsigned char)(state->parse.Rx >> 0);
	info_header[5] = (unsigned char)(state->parse.Rx >> 8);
	info_header[6] = (unsigned char)(state->parse.Rx >> 16);
	info_header[7] = (unsigned char)(state->parse.Rx >> 24);
	info_header[8] = (unsigned char)(state->parse.Ry >> 0);
	info_header[9] = (unsigned char)(state->parse.Ry >> 8);
	info_header[10] = (unsigned char)(state->parse.Ry >> 16);
	info_header[11] = (unsigned char)(state->parse.Ry >> 24);
	info_header[12] = (unsigned char)(1);
	info_header[14] = (unsigned char)(state->bits_per_pixel);
	return (info_header);
}

void	write_img(int fd, t_state *state)
{
	int		x;
	int		y;

	x = state->parse.Ry;
	while (x-- > 0)
	{
		y = -1;
		while (++y < state->parse.Rx)
			write(fd, state->addr + (x * state->line_length + y * (state->bits_per_pixel / 8)) \
			, state->bits_per_pixel / 8);
	}
}

void	save_bmp(const char *filename, t_state *state)
{
	int		fd;
	int		img_size;
	int		file_size;

	img_size = state->parse.Rx * 4 * state->parse.Ry;
	file_size = img_size + (40 + 14);
	close(open(filename, O_RDONLY | O_CREAT, S_IRWXU));
	fd = open(filename, O_RDWR);
	if (fd < 0)
	{
		printf("Error\n");
		wrdestroy();
		exit(0);
	}
	write(fd, create_bitmap_file_header(file_size), 14);
	write(fd, create_bitmap_info_header(state), 40);
	write_img(fd, state);
	close(fd);
	printf("Image generated!!\n");
	wrdestroy();
	exit(0);
}
