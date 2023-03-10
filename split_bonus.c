/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhayri <ykhayri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 18:37:37 by ykhayri           #+#    #+#             */
/*   Updated: 2023/03/11 21:34:54 by ykhayri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_par(char *s)
{
	int	n[3];

	n[i] = -1;
	n[w] = 0;
	n[j] = 0;
	while (s[++n[i]])
	{
		if (s[n[i]] == '(')
			n[w]++;
		else if (s[n[i]] == ')')
		{
			n[w]--;
			if (!n[w])
				n[j]++;
		}
		else if (!n[w] && s[n[i]] > 32)
		{
			while (s[n[i]] && s[n[i]] > 32)
				n[i]++;
			n[j]++;
			if (!s[n[i]])
				return (n[j]);
		}
	}
	return (n[j]);
}

static int	word_len(char *s, char *c)
{
	int	i;
	int	active;

	i = 0;
	active = 1;
	if (c[0] == ' ')
	{
		while (s[i] && s[i] != c[1] && s[i] != c[1])
			i++;
	}
	else
	{
		while (active && s[i])
		{
			if (s[i] == '(')
				active++;
			else if (s[i] == ')')
				active--;
			if (!active)
				return (i);
			i++;
		}
	}
	return (i);
}

static void	split_par_help(char **arr, char *s, int n[4])
{
	n[ac]++;
	arr[++n[j]] = my_alloc(word_len(s + n[i], ")") + 1);
	while (n[ac] > 0)
	{
		if (s[++n[i]] == '(')
			n[ac]++;
		else if (s[n[i]] == ')')
		{
			n[ac]--;
			if (!n[ac])
				break ;
		}
		arr[n[j]][++n[w]] = s[n[i]];
	}
	arr[n[j]][++n[w]] = '\0';
}

static void	split_par_help2(char **arr, char *s, int n[4])
{
	arr[++n[j]] = my_alloc(word_len(s + n[i], " (") + 1);
	while (s[n[i]] && s[n[i]] > 32 && s[n[i]] != '(')
		arr[n[j]][++n[w]] = s[n[i]++];
	arr[n[j]][++n[w]] = '\0';
}

char	**split_par(char *s)
{
	char	**arr;
	int		n[4];

	n[i] = -1;
	n[j] = -1;
	n[ac] = 0;
	if (!s || !s[0])
		return (0);
	n[w] = count_par(s);
	arr = (char **) my_alloc(sizeof(char *) * n[w] + 1);
	if (!arr)
		return (0);
	while (s[++n[i]])
	{
		n[w] = -1;
		if (s[n[i]] == '(')
			split_par_help(arr, s, n);
		else if (!n[ac] && s[n[i]] > 32)
			split_par_help2(arr, s, n);
		if (!s[n[i]])
			break ;
	}
	arr[++n[j]] = 0;
	return (arr);
}
