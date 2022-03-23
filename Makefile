# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/08 17:26:54 by rgelin            #+#    #+#              #
#    Updated: 2022/03/23 16:27:30 by jvander-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3d

#-------------------SOURCES PATH----------------------

UTILS		=	./utils/
SOURCES		=	./srcs/

#-------------------COMPILATION----------------------

CC			=	gcc
# FLAGS		=	-Wall -Werror -Wextra
MLX_FLAGS	=	-lmlx -framework OpenGL -framework AppKit

#-------------------SOURCES FILES----------------------

SRCS		=	$(SOURCES)main.c \
				$(SOURCES)parsing.c \
				$(SOURCES)error.c \
				$(SOURCES)rayTracking.c \
				$(SOURCES)rayTracking_utils.c \
				$(SOURCES)check_map.c \
				$(SOURCES)movments.c \
				$(SOURCES)movments2.c \


SRCS_UTILS	=	$(UTILS)get_pos_player.c \
				$(UTILS)convert_color.c \

#-------------------OBJECTS----------------------

OBJS		=	$(SRCS:.c=.o)

OBJS_UTILS	=	$(SRCS_UTILS:.c=.o)

LIB_MLX		=	libmlx.dylib

LIBFT		=	./libft/libft.a

#-------------------COLORS----------------------

RED			=	\x1b[31m

YELLOW		=	\x1b[33m

GREEN		=	\x1b[32m

NO_COLOR	=	\x1b[0m


#-------------------RULES-----------------------
%.o: %.c
		@printf "$(YELLOW)Generating cub3d objects... %-33.33s\r$(NO_COLOR)" $@
		@$(CC) $(FLAGS) -Imlx -c $< -o $@

$(NAME):	$(OBJS) $(OBJS_UTILS)
			@echo "\n"
			@make -C ./libft
			@echo "$(GREEN)\nCompiling mlx...\n$(NO_COLOR)"
			@make -C minilibx
			@cp ./minilibx/libmlx.dylib ./
			@echo "$(GREEN)\nCompiling cub3d...$(NO_COLOR)"
			@$(CC) $(FLAGS) $(MLX_FLAGS) $(OBJS) $(OBJS_UTILS) $(LIB_MLX) $(LIBFT) -o $(NAME)
			@echo "\nEnjoy!"

all:	$(NAME)

bonus:	$(NAME)

clean:
		@echo "$(RED)Deleting objects...\n$(NO_COLOR)"
		@make clean -C ./libft
		@make clean -C minilibx
		@rm -f $(OBJS) $(OBJS_UTILS)

fclean:	clean
		@echo "$(RED)Deleting executables...\n$(NO_COLOR)"
		@rm -rf $(LIBFT)
		@rm -rf $(LIB_MLX)
		@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean bonus re
