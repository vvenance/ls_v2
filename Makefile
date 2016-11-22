# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvenance <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/22 10:51:36 by vvenance          #+#    #+#              #
#    Updated: 2016/11/22 10:51:40 by vvenance         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC_FLAGS     = -Wall -Wextra -Werror

SRCS		= ft_ls.c init.c get_opt.c utils.c get_args.c files.c

SRCS_O		= $(SRCS:.c=.o)

NAME		= ft_ls

CC		    = GCC

I_LIBFT 	= -Ilibft

LIBFT 		= -Llibft $(I_LIBFT) -lft

all:	$(NAME)


$(NAME): $(SRCS_O)
			@make -C libft
			@$(CC) $(CC_FLAGS) -o $(NAME) $^ -I . $(LIBFT)
			@echo "$(NAME) has been successfuly done :)"

%.o: $(SRC_DIR)%.c
	@$(CC) $(CC_FLAGS) -I$ . -o $@ -c $< $(I_LIBFT)

re: fclean all


clean:
		@make clean -C libft
		@rm -f $(SRCS_O)

fclean: clean
		@rm -f $(NAME)
		@make fclean -C libft
