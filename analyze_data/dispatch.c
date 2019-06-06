/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 13:26:27 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/06 09:13:19 by juspende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dispatch.h"

void		weather_script(const char *str)
{
	char buff[1048];
	snprintf(buff, sizeof(buff), "osascript script/weather.script %s", str);
	system(buff);
}

void		alarm_script(const char *str)
{
	(void)str;
	system("osascript script/alarm.script");
}

void		unknown_command(const char *str)
{
	(void)str;
	system("osascript script/unknown.script");
}

void		say_hello(const char *str)
{
	(void)str;
	system("osascript script/hello.script");
}

void		send_email(const char *str)
{
	(void)str;
	system("osascript script/send_email.script");
}

void		lights_on(const char *str)
{
	(void)str;
	system("osascript script/lights_on.script");
}

void		lights_off(const char *str)
{
	(void)str;
	system("osascript script/lights_off.script");
}

void		lights_full(const char *str)
{
	(void)str;
	system("osascript script/light_full.script");
}

void		lights_down(const char *str)
{
	(void)str;
	system("osascript script/light_down.script");
}

void		check_traffic(const char *str)
{
	(void)str;
	system("osascript script/check_traffic.script");
}

void		play_music(const char *str)
{
	(void)str;
	system("osascript script/play_music.script");
}

void		search_web(const char *str)
{
	char buff[1048];
	snprintf(buff, sizeof(buff), "osascript script/search_web.script %s", str);
	system(buff);
}

void		check_event(const char *str)
{
	(void)str;
	system("osascript script/check_event.script");
}
