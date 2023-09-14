
NAME = philo
CFLAGS = -pthread -Wall -Wextra -Werror
RM = rm -rf
CC = cc
SRC = philo.c philo_utils.c philo_norm.c norm_bis.c philo_bis.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:	
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
