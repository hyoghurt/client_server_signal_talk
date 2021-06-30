NAME1			= client
NAME2			= server

SRC_S			=	src/server.c	\
					src/ft_strdup.c	\
					src/ft_strlen.c	\
					src/ft_atoi.c	\
					src/ft_itoa.c	\

SRC_C			=	src/client.c	\
					src/ft_strdup.c	\
					src/ft_strlen.c	\
					src/ft_atoi.c	\
					src/ft_itoa.c	\

SRCDIR			= src
OBJDIR			= obj
OBJ_S			= $(addprefix $(OBJDIR)/,$(notdir $(SRC_S:.c=.o)))
OBJ_C			= $(addprefix $(OBJDIR)/,$(notdir $(SRC_C:.c=.o)))
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror

$(NAME1):		$(OBJ_C) | $(NAME2)
				$(CC) $(OBJ_C) -o $(NAME1)

$(NAME2):		$(OBJ_S)
				$(CC) $(OBJ_S) -o $(NAME2)

$(OBJDIR):			
				mkdir -p $@

$(OBJDIR)/%.o:	$(SRCDIR)/%.c | $(OBJDIR)
				$(CC) -I. -c -MD $< -o $@

include $(wildcard $(OBJDIR)/*.d)

all:			$(NAME1)

clean:	
				rm -rf $(OBJDIR)

fclean:			clean
				rm -rf client server

re:				fclean all

.PHONY:			all clean fclean re
