/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_pathutils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carfern2 <carfern2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:44:37 by carfern2          #+#    #+#             */
/*   Updated: 2025/05/30 12:24:40 by carfern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

static char	*check_directories(char *cmd, char **paths)
{
	int		i;
	char	*full_path;
	int		len;

	i = 0;
	while (paths[i])
	{
		len = ft_strlen(paths[i]) + ft_strlen(cmd) + 2;
		full_path = malloc(sizeof(char) * len);
		if (!full_path)
			return (NULL);
		ft_strlcpy(full_path, paths[i],len);
		ft_strlcat(full_path, "/", len);
		ft_strlcat(full_path, cmd, len);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

static void free_paths(char **paths)
{
    int i = 0;
    if (!paths)
        return;
    while (paths[i])
    {
        free(paths[i]);
        i++;
    }
    free(paths);
}

static char **get_paths_from_env(void)
{
    char *path_env;
    char *path_dup;
    char **paths;

    path_env = getenv("PATH");
    if (!path_env)
        return (NULL);
    path_dup = ft_strdup(path_env);
    if (!path_dup)
        return (NULL);
    paths = ft_split(path_dup, ':');
    free(path_dup);
    return (paths);
}

char *get_executable_path(char *cmd)
{
    char *cmd_path;
    char **paths;
    char *default_paths[3];

    default_paths[0] = "/bin";
    default_paths[1] = "/usr/bin";
    default_paths[2] = NULL;

    paths = get_paths_from_env();
    if (!paths)
        return (check_directories(cmd, default_paths));
    cmd_path = check_directories(cmd, paths);
    free_paths(paths);
    if (cmd_path)
        return (cmd_path);
    return (check_directories(cmd, default_paths));
}
