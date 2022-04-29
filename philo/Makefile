NAME	=	philo
SRCS	=	main.c\
			allocate_resources.c\
			check_grave.c\
			clear_all.c\
			daily_routine.c\
			ft_atou.c\
			input_to_info.c\
			monitor.c\
			philo_forks.c\
			utils.c
INCS	=	constant.h\
			philo.h\
			utils.h
INC_DIR	=	-I./incs

OBJ_DIR	=	objs
OBJS	=	$(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
CFLAGS	=	-Wall -Werror -Wextra -fsanitize=thread -g
VPATH	=	$(shell ls -R)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o : %.c $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC_DIR)

clean :
	rm -rf $(OBJ_DIR)

fclean :
	$(MAKE) clean
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

reclean:
	$(MAKE) re
	$(MAKE) clean

.PHONY: clean fclean re reclean all