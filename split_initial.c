/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_initial.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhayri <ykhayri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:31:10 by abouabra          #+#    #+#             */
/*   Updated: 2023/03/07 21:50:04 by ykhayri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/get_next_line.h"
#include "minishell.h"

int	has_separator(char c, char c1)
{
	if (c == '|' || (c == '&' && c1 == '&'))
		return (1);
	return (0);
}

static int	count_words(char *s)
{
	int		i;
	int		phrase_count;

	i = -1;
	phrase_count = 0;
	while (++i < ft_strlen(s))
	{
		if (s[i] == '|' && s[i + 1] != '|')
			phrase_count++;
		else if (s[i] == '&' && s[i + 1] == '&')
		{
			phrase_count++;
			i++;
		}
		else if (s[i] == '|' && s[i + 1] == '|')
		{
			phrase_count++;
			i++;
		}
	}
	phrase_count++;
	return (phrase_count);
}

static void	split_cases(int n[3], int ph_len, char *s, char **phrases)
{
	if (has_separator(s[n[i]], s[n[i] + 1]))
	{
		ph_len = n[i] - n[j];
		phrases[n[k]] = (char *)my_alloc((ph_len + 1) * sizeof(char));
		ft_memcpy(phrases[n[k]], s + n[j], ph_len);
		phrases[n[k]][ph_len] = '\0';
	}
	if (s[n[i]] == '|' && s[n[i] + 1] != '|')
	{
		n[k]++;
		n[j] = n[i] + 1;
	}
	else if (s[n[i]] == '&' && s[n[i] + 1] == '&')
	{
		n[k]++;
		n[j] = n[i] + 2;
		n[i]++;
	}
	else if (s[n[i]] == '|' && s[n[i] + 1] == '|')
	{
		n[k]++;
		n[j] = n[i] + 2;
		n[i]++;
	}
}

static int	check_validity(char **phrases, int phrase_count)
{
	int	i;

	i = -1;
	while (phrases[++i])
	{
		if (!phrases[i][0] || !ft_strtrim(phrases[i], " \t\n")[0])
		{
			if (phrase_count > 1)
				custom_exit(2);
			else
				return (0);
		}
	}
	return (1);
}

char	**initial_split(t_args *vars, char *s)
{
	int		n[3];
	int		phrase_count;
	int		ph_len;
	char	**phrases;

	n[i] = -1;
	n[j] = 0;
	n[k] = 0;
	ph_len = 0;
	phrase_count = count_words(s);
	vars->command_count = phrase_count;
	phrases = (char **)my_alloc((phrase_count + 1) * sizeof(char *));
	while (++n[i] < ft_strlen(s))
		split_cases(n, ph_len, s, phrases);
	ph_len = n[i] - n[j];
	phrases[n[k]] = (char *)my_alloc((ph_len + 1) * sizeof(char));
	ft_memcpy(phrases[n[k]], s + n[j], ph_len);
	phrases[n[k]][ph_len] = '\0';
	n[k]++;
	phrases[n[k]] = NULL;
	if (!check_validity(phrases, phrase_count))
		return (NULL);
	return (phrases);
}
