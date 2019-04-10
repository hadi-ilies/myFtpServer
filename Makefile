##
## EPITECH PROJECT, 2019
## for_norme
## File description:
## Makefile
##

NAME		=	myftp

CC		=	gcc

SRCDIR		=	src/
COMMANDDIR	=	$(SRCDIR)command/
INCDIR		=	include/

SRC		=	$(SRCDIR)main.c \
			$(SRCDIR)network.c \
			$(SRCDIR)split.c \
			$(SRCDIR)socket.c \
			$(COMMANDDIR)user_command.c \
			$(COMMANDDIR)pass_command.c \
			$(COMMANDDIR)noop_command.c \
			$(COMMANDDIR)quit_command.c \
			$(COMMANDDIR)cwd_command.c \
			$(COMMANDDIR)pwd_command.c \
			$(COMMANDDIR)cdup_command.c \
			$(COMMANDDIR)help_command.c \

OBJ		=	$(SRC:.c=.o)

CFLAGS		+=	-I $(INCDIR)
CFLAGS		+=	-std=gnu11 -Wall -Wextra

all		:	$(NAME)

$(NAME)		:	$(OBJ)
			@$(CC) -o $(NAME) $(OBJ)

clean		:
			@rm -f $(OBJ)

fclean		:	clean
			@rm -f $(NAME)

re		:	fclean all

debug		:	CFLAGS += -g3
debug		:	re
