/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 13:26:27 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/11 19:45:22 by juspende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dispatch.h"

#if defined(__APPLE__) && defined(__MACH__)
void weather_script(const char *str)
{
	char buff[1048];

	snprintf(buff, sizeof(buff), "osascript script/weather.script %s", str);
	system(buff);
	system("say Here is the weather");
}
#else
void weather_script(const char *str)
{
	char buff[1048];

	snprintf(buff, sizeof(buff), "curl wttr.in/%s", str);
	system(buff);
	system("say Here is the weather");
}
#endif

void alarm_script(const char *str)
{
	(void)str;
#if defined(__APPLE__) && defined(__MACH__)
	system("osascript script/alarm.script");
	system("say I opened the application for you");
#endif
}

void check_history(const char *str)
{
	(void)str;
	system("open .history.txt");
}

void unknown_command(const char *str)
{
	(void)str;
#if defined(__APPLE__) && defined(__MACH__)
	system("osascript script/unknown.script");
#else
	system("say I do not understand");
#endif
}

void say_hello(const char *str)
{
	(void)str;
#if defined(__APPLE__) && defined(__MACH__)
	system("osascript script/hello.script");
#endif
}

void send_email(const char *str)
{
	(void)str;
#if defined(__APPLE__) && defined(__MACH__)
	system("osascript script/send_email.script");
	system("say I opened the application for you");
#endif
}

void lights_on(const char *str)
{
	(void)str;
#if defined(__APPLE__) && defined(__MACH__)
	system("osascript script/lights_on.script");
	system("say I increased the lights");
#endif
}

void lights_off(const char *str)
{
	(void)str;
#if defined(__APPLE__) && defined(__MACH__)
	system("osascript script/lights_off.script");
	system("say I decreased the lights");
#endif
}

void lights_full(const char *str)
{
	(void)str;
#if defined(__APPLE__) && defined(__MACH__)
	system("osascript script/light_full.script");
	system("say `I increased the lights`");
#endif
}

void lights_down(const char *str)
{
	(void)str;
#if defined(__APPLE__) && defined(__MACH__)
	system("osascript script/light_down.script");
	system("say I decreased the lights");
#endif
}

void check_traffic(const char *str)
{
	(void)str;
#if defined(__APPLE__) && defined(__MACH__)
	system("osascript script/check_traffic.script");
	system("say Here you can check the traffic");
#else
	system("open \"https://www.waze.com/livemap\"");
	system("say Here you can check the traffic");
#endif
}

void play_music(const char *str)
{
	(void)str;
#if defined(__APPLE__) && defined(__MACH__)
	system("osascript script/play_music.script");
	system("say Please, choose your music");
#else
	system("open \"https://www.youtube.com/results?search_query=music\"");
	system("say  Please, choose your music");
#endif
}

#if defined(__APPLE__) && defined(__MACH__)
void search_web(const char *str)
{
	char buff[1048];

	snprintf(buff, sizeof(buff), "osascript script/search_web.script %s", str);
	system(buff);
	system("say I asked my friend Google for you");
}
#else
void search_web(const char *str)
{
	char buff[1048];

	snprintf(buff, sizeof(buff), "open \"http:\/\/www.google.com/search?q=%s", str);
	system(buff);
	system("say I asked my friend Google for you");
}
#endif

void check_event(const char *str)
{
	(void)str;
#if defined(__APPLE__) && defined(__MACH__)
	system("osascript script/check_event.script");
	system("say I opened your calendar so you can see your future events");
#endif
}

#if defined(__APPLE__) && defined(__MACH__)
void open_app(const char *str)
{
	char buff[1048];

	snprintf(buff, sizeof(buff), "osascript script/open.script %s", str);
	system(buff);
	system("say I opened the application");
}
#else
void open_app(const char *str)
{
	(void)str;
}
#endif

void set_timer(const char *str)
{
	(void)str;
#if defined(__APPLE__) && defined(__MACH__)
	system("osascript script/set_timer.script");
	system("say `I opened the application for you`");
#endif
}

void who_is_connected(const char *str)
{
	(void)str;
#if defined(__APPLE__) && defined(__MACH__)
	system("osascript script/who_connected.script");
#endif
}

void where_is_connected(const char *str)
{
	(void)str;
#if defined(__APPLE__) && defined(__MACH__)
	system("osascript script/where_connected.script");
#endif
}

void send_sms(const char *str)
{
	(void)str;
#if defined(__APPLE__) && defined(__MACH__)
	system("osascript script/sms.script");
#endif
}

void pickle(const char *str)
{
	(void)str;
	system("play audio/pickle.wav");
}
