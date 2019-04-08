##
## EPITECH PROJECT, 2019
## for_norme
## File description:
## Makefile
##

NAME		=	a.out

CC		=	gcc

SRCDIR		=	src/
INCDIR		=	include/

SRC		=	$(SRCDIR)main.c \

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
