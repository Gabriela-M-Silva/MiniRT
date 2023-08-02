/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inverting_matrix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 01:31:11 by gde-mora          #+#    #+#             */
/*   Updated: 2023/08/02 19:04:38 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/miniRT.h"

static	int	invert_content(double **new_content, t_matrix *matrix);
static	int	init_new_content(double **new_content, t_matrix *matrix);

t_matrix	*inverting_matrix(t_matrix *matrix)
{
	t_matrix	*new_matrix;
	double		**new_content;

	if (!matrix)
		return (NULL);
	if (are_floats_equal(matrix->determinant, 0.0))
		return (NULL);
	new_content = ft_calloc(matrix->rows + 1, sizeof(double *));
	if (!new_content)
		return (NULL);
	if (!init_new_content(new_content, matrix))
		return (NULL);
	if (!invert_content(new_content, matrix))
		return (NULL);
	new_matrix = create_matrix(new_content, matrix->cols);
	return (new_matrix);
}

static	int	invert_content(double **new_content, t_matrix *matrix)
{
	int			rows;
	int			cols;
	double		cofactor;

	rows = -1;
	while (++rows < matrix->rows)
	{
		cols = -1;
		while (++cols < matrix->cols)
		{
			cofactor = get_cofactor(matrix, rows, cols);
			new_content[cols][rows] = cofactor / matrix->determinant;
			if (are_floats_equal(new_content[cols][rows], -0.0))
				new_content[cols][rows] = 0;
		}
	}
	return (1);
}

static	int	init_new_content(double **new_content, t_matrix *matrix)
{
	int	rows;

	rows = -1;
	while (++rows < matrix->rows)
	{
		new_content[rows] = ft_calloc(matrix->cols, sizeof(double));
		if (!new_content[rows])
		{
			free_array((void **)new_content);
			return (0);
		}
	}
	return (1);
}
