NAME1			= client
NAME2			= server

SRC				=	server.c	\
					client.c \

SRCDIR			= src
OBJDIR			= obj
OBJ				= $(addprefix $(OBJDIR)/,$(notdir $(SRC:.c=.o)))
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror

$(NAME1):		$(OBJ) | $(NAME2)
				$(CC) obj/client.o -o client

$(NAME2):		$(OBJ)
				$(CC) obj/server.o -o server

$(OBJDIR):			
				mkdir -p $@

$(OBJDIR)/%.o:	%.c | $(OBJDIR)
				$(CC) -c -MD $< -o $@

include $(wildcard $(OBJDIR)/*.d)

all:			$(NAME1)

clean:	
				rm -rf $(OBJDIR)

fclean:			clean
				rm -rf client server

re:				fclean all

.PHONY:			all clean fclean re
