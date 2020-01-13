/*
** EPITECH PROJECT, 2018
** my_str_isalpha
** File description:
** task10
*/

int	my_str_isalphanum(char const *str)
{
	int i = 0;

	if (str[0] == 0)
		return (1);
	while ((str[i] >= 65 && str[i] <= 90) || \
(str[i] >= 97 && str[i] <= 122) || \
(str[i] >= '0' && str[i] <= '9')) {
		i++;
	}
	if (str[i] == '\0') {
		return (1);
	} else {
		return (0);
	}
}
