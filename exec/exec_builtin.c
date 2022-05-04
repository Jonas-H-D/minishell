#include "../minishell.h"

int	is_builtin(char *cmd)
{
	if (cmd == NULL)
		return (0);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd, "env"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	return (0);
}

int	exec_builtin(char **tab_cmd, t_info *liste, int fd)
{
	if (!ft_strcmp(tab_cmd[0], "exit"))
		ft_exit(tab_cmd, liste);
	else if (!ft_strcmp(tab_cmd[0], "pwd") || !ft_strcmp(tab_cmd[0], "PWD"))
		current_dir(fd);
	else if (!ft_strcmp(tab_cmd[0], "cd"))
		ft_cd(tab_cmd, liste);
	else if (!ft_strcmp(tab_cmd[0], "echo") || !ft_strcmp(tab_cmd[0], "ECHO"))
		ft_echo(tab_cmd, fd);
	else if (!ft_strcmp(tab_cmd[0], "env") || !ft_strcmp(tab_cmd[0], "ENV"))
		my_env(liste->liste, fd);
	else if (!ft_strcmp(tab_cmd[0], "unset"))//no redir stdout
		ft_unset(&liste->liste, tab_cmd[1]);
	else if (!ft_strcmp(tab_cmd[0], "export"))
		ft_export(tab_cmd, liste->liste, liste, fd);
	return (0);
}
