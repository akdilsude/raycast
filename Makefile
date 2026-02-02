NAME			=	cub3D
SRCS			=	control_identifier.c	\
					frees.c					\
					get_next_line.c			\
					handle_colors.c 		\
					handle_direct.c 		\
					main.c					\
					open_map.c 				\
					parse_path.c  			\
					process_map.c 			\
					process_map2.c 			\
					process_map3.c 			\
					utils.c					\
					init.c					\
					utils2.c				\
					color_and_draw.c		\
					raycasting.c			\
					movement.c				\


OBJS			=	$(SRCS:.c=.o)
RM				=	rm -f
CFLAGS			=	-Wall -Wextra -Werror
CC				=	cc
LIBFT_DIR		= 	./libft
LIBFT 			= 	$(LIBFT_DIR)/libft.a
MINILIBX_DIR	=	minilibx-linux
MINILIBX 		=	$(MINILIBX_DIR)/libmlx.a
LFLAGS 			=	-Lminilibx-linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm


all: $(LIBFT) $(NAME)

$(MINILIBX):
	@make -C $(MINILIBX_DIR)

$(NAME): $(OBJS) $(LIBFT) $(MINILIBX)
		$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MINILIBX) $(LFLAGS) -o $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean: 
	$(RM) $(OBJS)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME) $(OBJS)
	@make -C $(LIBFT_DIR) fclean
	@make -C $(MINILIBX_DIR) clean

re: fclean all

.PHONY: all re clean fclean
