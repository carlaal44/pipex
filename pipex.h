/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carfern2 <carfern2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 09:12:19 by carfern2          #+#    #+#             */
/*   Updated: 2025/05/30 12:32:10 by carfern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_pipex
{
	int		fd[2];
	int		status;
	int		outfile_fd;
	int		infile_fd;
	char	*cmd;
	char	**envp;
}	t_pipex;

char 			*get_executable_path(char *cmd);
void			setup_parent_execution(t_pipex *data);
char			**prepare_args(char *cmd);
void			setup_parent(int *fd, int outfile_fd);
void			setup_child(int *fd);
void			execute_parent(t_pipex *data, char *outfile);
void 			execute_child(int *fd, char *cmd, char **envp, int infile_fd);
void			create_pipe(int *fd);
int				open_outfile(char *outfile);



#endif
