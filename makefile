
NAME = philo
CFLAGS =  -g -pthread -Wall -Wextra -Werror
RM = rm -rf
CC = cc
SRC = philo.c philo_utils.c philo_norm.c norm_bis.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -o $(NAME)
	@echo ---program linked---

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:	
	@$(RM) $(OBJ)
	@echo ---objects cleaned---

fclean: clean
	@$(RM) $(NAME)
	@echo ---program cleaned---

re: fclean all

.PHONY: all clean fclean re
