/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 13:26:27 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/06 15:04:07 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dispatch.h"

void		weather_script(const char *str)
{
	char buff[1048];

	snprintf(buff, sizeof(buff), "osascript script/weather.script %s", str);
	system(buff);
	system("say Here is the weather");
}

void		alarm_script(const char *str)
{
	(void)str;
	system("osascript script/alarm.script");
	system("say I opened the application for you");
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
	system("say I opened the application for you");
}

void		lights_on(const char *str)
{
	(void)str;
	system("osascript script/lights_on.script");
	system("say I increased the lights");
}

void		lights_off(const char *str)
{
	(void)str;
	system("osascript script/lights_off.script");
	system("say I decreased the lights");
}

void		lights_full(const char *str)
{
	(void)str;
	system("osascript script/light_full.script");
	system("say `I increased the lights`");
}

void		lights_down(const char *str)
{
	(void)str;
	system("osascript script/light_down.script");
	system("say I decreased the lights");
}

void		check_traffic(const char *str)
{
	(void)str;
	system("osascript script/check_traffic.script");
	system("say Here you can check the traffic");
}

void		play_music(const char *str)
{
	(void)str;
	system("osascript script/play_music.script");
	system("say Please, choose your music");
}

void		search_web(const char *str)
{
	char buff[1048];

	snprintf(buff, sizeof(buff), "osascript script/search_web.script %s", str);
	system(buff);
	system("say I asked my friend Google for you");
}

void		check_event(const char *str)
{
	(void)str;
	system("osascript script/check_event.script");
	system("say I opened your calendar so you can see your future events");
}

void		open_app(const char *str)
{
	char buff[1048];

	snprintf(buff, sizeof(buff), "osascript script/open.script %s", str);
	system(buff);
	system("say I opened the application");
}

void		set_timer(const char *str)
{
	(void)str;
	system("osascript script/set_timer.script");
	system("say `I opened the application for you`");
}

void		who_is_connected(const char *str)
{
	(void)str;
	system("osascript script/who_connected.script");
}

void		where_is_connected(const char *str)
{
	(void)str;
	system("osascript script/where_connetcted.script");
}

void		send_sms(const char *str)
{
	(void)str;
	system("osascript script/sms.script");
}
