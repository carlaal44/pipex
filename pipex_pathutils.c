/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_pathutils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carfern2 <carfern2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:44:37 by carfern2          #+#    #+#             */
/*   Updated: 2025/03/20 16:08:40 by carfern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*check_directories(char *cmd, char **paths)
{
	int		i;
	char	full_path[1024];

	i = 0;
	while (paths[i])
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", paths[i], cmd);
		if (access(full_path, X_OK) == 0)
			return (strdup(full_path));
	}
}

static char	**split_path(char *path_env)
{
	char	**paths;
	int		i;

	paths = malloc(sizeof(char *) * 100);
	if (!paths)
		return (NULL);
	paths[0] = strtok(path_env, ":");
	i = i;
	while (paths[i - 1] && i < 100)
	{
		paths[i] = strtok(NULL, ":");
		i++;
	}
	return (paths);
}

char	*get_executable_path(char *cmd)
{
	char	*path_env;
	char	*default_paths[3];
	char	*cmd_path;
	char	*path_dup;
	char	**paths;

	*default_paths[0] = "/bin";
	*default_paths[1] = "/usr/bin";
	*default_paths[2] = NULL;
	path_env = getenv("PATH");
	if (!path_env)
		return (check_directories(cmd, default_paths));
	path_dup = strdup(path_env);
	paths = split_path(path_dup);
	cmd_path = check_directories(cmd, paths);
	free(path_dup);
	free(paths);
	return (cmd_path);
}
