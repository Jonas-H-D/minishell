#include "../minishell.h"

char	*ft_strjoin_whit_space(char *s1, char const *s2)
{
	char	*dst;
	size_t	len;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	i = -1;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2) + 2;
	dst = malloc(len * sizeof(char));
	if (!dst)
		return (NULL);
	while (s1[++i])
		dst[i] = s1[i];
	dst[i++] = ' ';//
	while (s2[j])
		dst[i++] = s2[j++];
	dst[i] = '\0';
	free (s1);
	return (dst);
}

char	*ft_strjoin_whit_int(char *s1,int n)
{
	char	*dst;
	char	*s2;
	size_t	len;
	int		i;
	int		j;

	s2 = ft_itoa(n);
	if (!s1 || !s2)
		return (NULL);
	i = -1;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2) + 2;
	dst = malloc(len * sizeof(char));
	if (!dst)
		return (NULL);
	while (s1[++i])
		dst[i] = s1[i];
	dst[i++] = '_';
	while (s2[j])
		dst[i++] = s2[j++];
	dst[i] = '\0';
	free (s2);
	return (dst);
}