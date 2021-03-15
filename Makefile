##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Makefile for the ex00
##

DIR_CLI		=	client/

SRC_CLI		=	$(DIR_CLI)main.c				\
			$(DIR_CLI)client.c				\
			$(DIR_CLI)tools.c				\
			$(DIR_CLI)split.c				\
			$(DIR_CLI)parsing.c				\
			$(DIR_CLI)initialisation.c			\
			$(DIR_CLI)prompt.c				\
			$(DIR_CLI)unauthorized.c			\
			$(DIR_CLI)$(DIR_CMD)$(DIR_FEA)help.c		\
			$(DIR_CLI)$(DIR_CMD)$(DIR_FEA)logout.c		\
			$(DIR_CLI)$(DIR_CMD)$(DIR_FEA)login.c		\
			$(DIR_CLI)$(DIR_CMD)$(DIR_FEA)users.c		\
			$(DIR_CLI)$(DIR_CMD)$(DIR_FEA)send.c		\
			$(DIR_CLI)$(DIR_CMD)$(DIR_FEA)subscribe.c	\
			$(DIR_CLI)$(DIR_CMD)$(DIR_FEA)messages.c	\
			$(DIR_CLI)$(DIR_CMD)$(DIR_FEA)subscribed.c	\
			$(DIR_CLI)$(DIR_CMD)$(DIR_FEA)unsubscrib.c	\
			$(DIR_CLI)$(DIR_CMD)$(DIR_FEA)user.c		\
			$(DIR_CLI)$(DIR_CMD)$(DIR_FEA)use.c		\
			$(DIR_CLI)$(DIR_CMD)$(DIR_FEA)list.c		\
			$(DIR_CLI)$(DIR_CMD)$(DIR_FEA)create.c		\
			$(DIR_CLI)$(DIR_CMD)$(DIR_FEA)info.c

OBJ_CLI		=	$(SRC_CLI:.c=.o)

NAM_CLI		=	myteams_cli

DIR_SER		=	server/

DIR_CMD		=	commands/

DIR_USE		=	use/

DIR_FEA		=	features/

DIR_CRE		=	create/

DIR_INF		=	info/

DIR_LIS		=	list/

SRC_SER		=	$(DIR_SER)main.c				\
			$(DIR_SER)server.c				\
			$(DIR_SER)connection.c				\
			$(DIR_SER)tools.c				\
			$(DIR_SER)parsing.c				\
			$(DIR_SER)clear.c				\
			$(DIR_SER)send.c				\
			$(DIR_SER)split.c				\
			$(DIR_SER)read.c				\
			$(DIR_SER)file.c				\
			$(DIR_SER)folder.c				\
			$(DIR_SER)save.c				\
			$(DIR_SER)select.c				\
			$(DIR_SER)strcat.c				\
			$(DIR_SER)$(DIR_CMD)$(DIR_USE)use.c		\
			$(DIR_SER)$(DIR_CMD)$(DIR_USE)channel.c		\
			$(DIR_SER)$(DIR_CMD)$(DIR_USE)thread.c		\
			$(DIR_SER)$(DIR_CMD)$(DIR_USE)team.c		\
			$(DIR_SER)$(DIR_CMD)$(DIR_LIS)channel.c		\
			$(DIR_SER)$(DIR_CMD)$(DIR_LIS)replie.c		\
			$(DIR_SER)$(DIR_CMD)$(DIR_LIS)thread.c		\
			$(DIR_SER)$(DIR_CMD)$(DIR_LIS)team.c		\
			$(DIR_SER)$(DIR_CMD)$(DIR_CRE)create.c		\
			$(DIR_SER)$(DIR_CMD)$(DIR_CRE)team.c		\
			$(DIR_SER)$(DIR_CMD)$(DIR_CRE)channel.c		\
			$(DIR_SER)$(DIR_CMD)$(DIR_CRE)thread.c		\
			$(DIR_SER)$(DIR_CMD)$(DIR_FEA)help.c		\
			$(DIR_SER)$(DIR_CMD)$(DIR_INF)info.c		\
			$(DIR_SER)$(DIR_CMD)$(DIR_INF)team.c		\
			$(DIR_SER)$(DIR_CMD)$(DIR_INF)channel.c		\
			$(DIR_SER)$(DIR_CMD)$(DIR_INF)thread.c		\
			$(DIR_SER)$(DIR_CMD)$(DIR_INF)user.c		\
			$(DIR_SER)$(DIR_CMD)$(DIR_LIS)list.c		\
			$(DIR_SER)$(DIR_CMD)$(DIR_FEA)login.c		\
			$(DIR_SER)$(DIR_CMD)$(DIR_FEA)logout.c		\
			$(DIR_SER)$(DIR_CMD)$(DIR_FEA)messages.c	\
			$(DIR_SER)$(DIR_CMD)$(DIR_FEA)subscribe.c	\
			$(DIR_SER)$(DIR_CMD)$(DIR_FEA)subscribed.c	\
			$(DIR_SER)$(DIR_CMD)$(DIR_FEA)unsubscrib.c	\
			$(DIR_SER)$(DIR_CMD)$(DIR_FEA)user.c		\
			$(DIR_SER)$(DIR_CMD)$(DIR_FEA)users.c

OBJ_SER		=	$(SRC_SER:.c=.o)

NAM_SER		=	myteams_server

DIR_BON		=	bonus/

SRC_BON		=	$(DIR_BON)main.c

OBJ_BON		=	$(SRC_BON:.c=.o)

NAM_BON		=	myteams_bonus

DIR_TES		=	tests/

SRC_TES		=	$(DIR_TES)test.c

OBJ_TES		=	$(SRC_TES:.c=.o)

NAM_TES		=	myteams_tests

CFLAGS		=	-I./include -Wall -Wextra

LLIB		=	-L./libs/myteams -lmyteams -luuid

CC		=	gcc

RM		=	rm -f

LIB_CRITERION	=	-lcriterion --coverage

%.o: %.c
		@$(CC) $(CFLAGS) -c $< -o $@
		@printf "[\033[0;32mCompilation\033[0m] % 40s\n" $< | tr ' ' '.'

all:		client server

server:		$(OBJ_SER)
		@printf "[\033[0;33mBuild\033[0m] % 46s\n" $(NAM_SER) | tr ' ' '.'
		@$(CC) -o $(NAM_SER) $(OBJ_SER) $(LLIB)

client:		$(OBJ_CLI)
		@printf "[\033[0;33mBuild\033[0m] % 46s\n" $(NAM_CLI) | tr ' ' '.'
		@$(CC) -o $(NAM_CLI) $(OBJ_CLI) $(LLIB)

bonus:		$(OBJ_BON)
		@printf "[\033[0;33mBuild\033[0m] % 46s\n" $(NAM_BON) | tr ' ' '.'
		@$(CC) -o $(NAM_BON) $(OBJ_BON)

tests_run:	$(OBJ_TES)
		@$(CC) $(CFLAGS) -o $(NAM_TES) $(SRC_TES) $(LIB_CRITERION)
		@$(RM) $(OBJ_TES)
		@./$(NAME_TES) --verbose

clean:
		@printf "[\033[0;31mDeleted\033[0m] % 44s\n" $(NAM_SER) | tr ' ' '.'
		@printf "[\033[0;31mDeleted\033[0m] % 44s\n" $(NAM_CLI) | tr ' ' '.'
		@printf "[\033[0;31mDeleted\033[0m] % 44s\n" $(NAM_BON) | tr ' ' '.'
		@printf "[\033[0;31mDeleted\033[0m] % 44s\n" $(OBJ_SER) | tr ' ' '.'
		@printf "[\033[0;31mDeleted\033[0m] % 44s\n" $(OBJ_CLI) | tr ' ' '.'
		@printf "[\033[0;31mDeleted\033[0m] % 44s\n" $(OBJ_BON) | tr ' ' '.'
		@$(RM) $(NAM_SER)
		@$(RM) $(NAM_CLI)
		@$(RM) $(NAM_BON)
		@$(RM) $(OBJ_SER)
		@$(RM) $(OBJ_CLI)
		@$(RM) $(OBJ_BON)

tests_clean:
		@printf "[\033[0;31mDeleted\033[0m] % 44s\n" $(NAM_TES) | tr ' ' '.'
		@$(RM) $(NAM_TES)
		@$(RM) *.gcda
		@$(RM) *.gcno

fclean:		clean tests_clean

re:		fclean all

debug:		CFLAGS	+=	-g3
debug:		re

.PHONY:		tests_run tests_clean fclean re
