/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 13:27:04 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/06 16:26:11 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPATCH_H
# define DISPATCH_H

#include <stdlib.h>
#include <stdio.h>

typedef void (*t_exec_fn)(const char *str);

typedef struct		s_dispatch
{
	const char		*key;
	t_exec_fn		fn;
}					t_dispatch;

void				weather_script(const char *str);
void				alarm_script(const char *str);
void				unknown_command(const char *str);
void				say_hello(const char *str);
void				send_email(const char *str);
void				lights_on(const char *str);
void				check_history(const char *str);
void				lights_off(const char *str);
void				lights_full(const char *str);
void				lights_down(const char *str);
void				search_web(const char *str);
void				check_traffic(const char *str);
void				play_music(const char *str);
void 				check_event(const char *str);
void				open_app(const char *str);
void				set_timer(const char *str);
void				send_sms(const char *str);
void				who_is_connected(const char *str);
void				where_is_connected(const char *str);
void				pickle(const char *str);

# endif
