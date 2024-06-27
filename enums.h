/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:52:40 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/27 11:57:58 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_H
# define ENUMS_H

typedef enum s_mode_io
{
	DOUBLE,
	SINGLE
}	t_mode_io;

typedef enum redir
{
	IN,
	OUT
}	t_redir_io;

typedef enum operation
{
	END,
	KEEP,
	DELIMITER,
	SKIP,
}	t_operation;

typedef enum path_status
{
	IS_VALID,
	IS_DIR,
	CMD_NOT_FOUND,
	PERMISSION_DENIED,
	NOT_EXIST,
	WRITE_RIGHTS,
	READ_RIGHTS,

}	t_path_status;

#endif