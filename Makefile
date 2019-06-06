CC				= gcc
RM				= rm -f
SERVER			= server
CFLAGS			= -Wall -Wextra -Werror -g -I includes/
INCLUDES		= -I includes -L$(HOME)/.brew/Cellar/cmu-pocketsphinx/HEAD-80d8e28/lib/ -L$(HOME)/.brew/Cellar/cmu-sphinxbase/HEAD-562d047/lib/ -lpocketsphinx -lsphinxbase -lsphinxad -lpthread -lm -lblas -llapack
EXEC_PKG		= `pkg-config --cflags pocketsphinx sphinxbase`
FLAGS_SPHINX	= -DMODELDIR=\"`pkg-config --variable=modeldir pocketsphinx`\" `pkg-config --libs pocketsphinx sphinxbase`

BASE			= server.c socket.c receive.c signal.c
REQUEST			= request.c method.c post_content.c post_form.c post_multipart.c

FIELD			= field_accept.c field_content_length.c field_content_type.c\
					field_expect.c field_host.c
FIELDS			= fields.c $(FIELD)

RESPONSE		= response.c protocol.c content_type.c ft_free.c\
					response_error.c response_success.c

QUEUE			= queue_init.c node_init.c dequeue.c enqueue.c\
					is_empty.c peek.c
LIBFT			= strdel.c concat.c get_file_content.c $(addprefix queue/, $(QUEUE))
API				= demo.c sendaudio.c
SPHINX			= sphinx.c

REQUEST_FCT		= $(addprefix request/, $(REQUEST) $(FIELDS))
RESPONSE_FCT	= $(addprefix response/, $(RESPONSE))
LIBFT_FCT		= $(addprefix libft/, $(LIBFT))
SPHINX_FCT		= $(addprefix analyze_data/, $(SPHINX))
API_FCT			= $(addprefix api/, $(API))
FUNCTIONS		= $(addprefix srcs/, $(BASE) $(REQUEST_FCT) $(RESPONSE_FCT)\
				  $(LIBFT_FCT)) $(API_FCT) $(SPHINX_FCT)
OBJECTS			= $(FUNCTIONS:.c=.o)

.PHONY: all clean fclean re

all: $(SERVER)

$(SERVER): $(FUNCTIONS:.c=.o)
	@$(CC) $(CFLAGS) $(INCLUDES) $^ -o $(SERVER)

srcs/request/*.o:
	@$(CC) $(CFLAGS) $(INCLUDES) -c srcs/request/*.c -o $@

srcs/*.o:
	@$(CC) $(CLFAGS) $(INCLUDES) -c srcs/*.c -o $@

srcs/response/*.o:
	@$(CC) $(CFLAGS) $(INCLUDES) -c srcs/response/*.c -o $@

analyze_data/sphinx.o:
	gcc -c `pkg-config --cflags pocketsphinx sphinxbase` -DMODELDIR=\"`pkg-config --variable=modeldir pocketsphinx`\" `pkg-config --libs pocketsphinx sphinxbase` analyze_data/sphinx.c -o $@

analyze_data/dispatch.c:
	@$(CC) $(CFLAGS) $(INCLUDES) -c analyze_data/dispatch.c -o $@

api/*.o:
	@$(CC) $(CFLAGS) $(INCLUDES) -c srcs/api/*.c -o $@

srcs/libft/*.o:
	@$(CC) $(CFLAGS) $(INCLUDES) -c srcs/libft/*.c -o $@

srcs/libft/queue/*.o:
	@$(CC) $(CFLAGS) $(INCLUDES) -c srcs/libft/queue*.c -o $@

clean:
	@$(RM) $(FUNCTIONS:.c=.o)

fclean: clean
	@$(RM) $(SERVER)

re: fclean all
