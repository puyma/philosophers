# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/01 19:17:04 by mpuig-ma          #+#    #+#              #
#    Updated: 2023/06/29 17:55:15 by mpuig-ma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

AUTHOR		?=	mpuig-ma
NAME		:=	philo
BUILD_DIR	:=	build
SRC_DIR		:=	src

CC			:=	gcc
CFLAGS		:=	-Wall -Werror -Wextra
CFLAGS		+=	-MMD
LDFLAGS		:=	-pthread
#CFLAGS		+=	-g -fsanitize='address,undefined'
INC			:=	-I $(SRC_DIR)
RM			:=	rm -rf

NOSTYLE		:=	\033[0m
STYLE		:=	\033[0;32m

SRC_FILES	:=	$(SRC_DIR)/main.c \
				$(SRC_DIR)/launch.c \
				$(SRC_DIR)/routine.c \
				$(SRC_DIR)/str_utils.c \
				$(SRC_DIR)/time_utils.c

BONUS_FILES	:=	$(SRC_DIR)/main_bonus.c \
				$(SRC_DIR)/launch_bonus.c \
				$(SRC_DIR)/routine_bonus.c \
				$(SRC_DIR)/str_utils.c \
				$(SRC_DIR)/time_utils.c

OBJ_FILES	=	$(SRC_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEP_FILES	=	$(OBJ_FILES:.o=.d)

BOBJ_FILES	=	$(BONUS_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
BDEP_FILES	=	$(BOBJ_FILES:.o=.d)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ_FILES) $(DEP_FILES) $(SRC_DIR)/philosophers.h
	$(CC) $(INC) $(CFLAGS) $(OBJ_FILES) $(LDFLAGS) -o $(NAME)
	@echo "Built $(STYLE)$(basename $@)$(NOSTYLE)"

bonus: $(BOBJ_FILES) $(BDEP_FILES) $(SRC_DIR)/philosophers.h
	$(CC) $(INC) $(CFLAGS) $(BOBJ_FILES) $(LDFLAGS) -o philo_$(basename $@)
	@echo "Built $(STYLE)philo_$(basename $@)$(NOSTYLE)"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(INC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(BUILD_DIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) philo_bonus

re: fclean
	$(MAKE)
