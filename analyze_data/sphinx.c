/* -*- c-basic-offset: 4; indent-tabs-mode: nil -*- */
/* ====================================================================
 * Copyright (c) 1999-2010 Carnegie Mellon University.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * This work was supported in part by funding from the Defense Advanced
 * Research Projects Agency and the National Science Foundation of the
 * United States of America, and the CMU Sphinx Speech Consortium.
 *
 * THIS SOFTWARE IS PROVIDED BY CARNEGIE MELLON UNIVERSITY ``AS IS'' AND
 * ANY EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL CARNEGIE MELLON UNIVERSITY
 * NOR ITS EMPLOYEES BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ====================================================================
 *
 */
/*
 * continuous.c - Simple pocketsphinx command-line application to test
 *                both continuous listening/silence filtering from microphone
 *                and continuous file transcription.
 */

/*
 * This is a simple example of pocketsphinx application that uses continuous listening
 * with silence filtering to automatically segment a continuous stream of audio input
 * into utterances that are then decoded.
 * 
 * Remarks:
 *   - Each utterance is ended when a silence segment of at least 1 sec is recognized.
 *   - Single-threaded implementation for portability.
 *   - Uses audio library; can be replaced with an equivalent custom library.
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sphinxbase/err.h>
#include <sphinxbase/ad.h>
#include "pocketsphinx.h"
#include "dispatch.h"

static ps_decoder_t *g_ps;
static cmd_ln_t		*g_config;
static FILE			*g_rawfd;

t_dispatch	g_fn[] = {
	"SEARCH", search_web,
	"CHECK WEATHER", weather_script,
	"SET ALARM", alarm_script,
	"SEND EMAIL", send_email,
	"SEND SMS", send_sms,
	"CHECK HISTORY", check_history,
	"LIGHTS ON", lights_on,
	"LIGHTS OFF", lights_off,
	"LIGHTS FULL", lights_full,
	"LIGHTS DOWN", lights_down,
	"OPEN", open_app,
	"PICKLE", pickle,
	"SET TIMER", set_timer,
	"WHO IS CONNECTED", who_is_connected,
	"WHERE IS CONNECTED", where_is_connected,
	"CHECK TRAFFIC", check_traffic,
	"CHECK EVENTS", check_event,
	"PLAY MUSIC", play_music,
	"HELLO", say_hello,
};

static int			exec_cmd(const char *str)
{
	int		i;

	i = 0;
	while (i < 18)
	{
		if (!strncmp(str, g_fn[i].key, strlen(g_fn[i].key)))
		{
			g_fn[i].fn(str + strlen(g_fn[i].key));
			return (0);
		}
		i++;
	}
	unknown_command(str);
	return (1);
}

static const char	*recognize_from_file(char *path)
{
	int16_t		adbuf[2048];
	const char	*fname;
	const char	*hyp;
	int32_t		k;
	int8_t		utt_started;
	int8_t		in_speech;

	fname = cmd_ln_str_r(g_config, "-infile");
	if ((g_rawfd = fopen(path, "rb")) == NULL)
		E_FATAL_SYSTEM("Failed to open %s for reading", path);
	ps_start_utt(g_ps);
	utt_started = FALSE;
	while ((k = fread(adbuf, sizeof(int16), 2048, g_rawfd)) > 0)
	{
		ps_process_raw(g_ps, adbuf, k, FALSE, FALSE);
		in_speech = ps_get_in_speech(g_ps);
		if (in_speech && !utt_started)
			utt_started = TRUE;
		if (!in_speech && utt_started)
		{
			ps_end_utt(g_ps);
			hyp = ps_get_hyp(g_ps, NULL);
			if (hyp != NULL)
				return (hyp);
			ps_start_utt(g_ps);
			utt_started = FALSE;
		}
	}
	ps_end_utt(g_ps);
	if (utt_started)
	{
		hyp = ps_get_hyp(g_ps, NULL);
		if (hyp != NULL)
			return (hyp);
	}
	fclose(g_rawfd);
	return (NULL);
}

const char			*get_string(char *path)
{
	char const *str;

	g_config = cmd_ln_init(NULL, ps_args(), TRUE,
		"-hmm", MODELDIR "/en-us/en-us",
		"-lm", "analyze_data/model/etc/kift.lm",
		"-dict", "analyze_data/model/etc/kift.dic",
		NULL);
	g_ps = ps_init(g_config);
	if (g_ps == NULL)
	{
		cmd_ln_free_r(g_config);
		return (NULL);
	}
	str = recognize_from_file(path);
	if (exec_cmd(str))
		str = NULL;
	ps_free(g_ps);
	cmd_ln_free_r(g_config);
	return (str);
}

