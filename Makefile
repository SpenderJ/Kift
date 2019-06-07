CC				= gcc
RM				= rm -f
SERVER			= server
CFLAGS			= -Wall -Wextra -Werror -g
INCLUDES		= -I includes/ -I analyze_data/

LIBRARIES		= -L$(HOME)/.brew/Cellar/cmu-pocketsphinx/HEAD-80d8e28/lib\
				  -L$(HOME)/.brew/Cellar/cmu-sphinxbase/HEAD-562d047/lib\
				  -lpocketsphinx -lsphinxbase -lsphinxad -lpthread -lm -lblas -llapack

EXEC_PKG		= `pkg-config --cflags pocketsphinx sphinxbase`
FLAGS_SPHINX	= -DMODELDIR=\"`pkg-config --variable=modeldir pocketsphinx`\"\
				  `pkg-config --libs pocketsphinx sphinxbase`

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
SPHINX			= sphinx.c dispatch.c

REQUEST_FCT		= $(addprefix request/, $(REQUEST) $(FIELDS))
RESPONSE_FCT	= $(addprefix response/, $(RESPONSE))
LIBFT_FCT		= $(addprefix libft/, $(LIBFT))
SPHINX_FCT		= $(addprefix analyze_data/, $(SPHINX))
API_FCT			= $(addprefix api/, $(API))
FUNCTIONS		= $(addprefix srcs/, $(BASE)  $(REQUEST_FCT) $(RESPONSE_FCT)\
				  $(LIBFT_FCT)) $(SPHINX_FCT) $(API_FCT)
OBJECTS			= $(FUNCTIONS:.c=.o)

.PHONY: all clean fclean re

all: $(SERVER)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(SERVER): $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $(SERVER) $(LIBRARIES)

analyze_data/sphinx.o:
	$(CC) -c $(EXEC_PKG) $(FLAGS_SPHINX) analyze_data/sphinx.c -o $@

clean:
	@$(RM) $(OBJECTS)

fclean: clean
	@$(RM) $(SERVER)

re: fclean all
