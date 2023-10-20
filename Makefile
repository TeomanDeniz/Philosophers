# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdeniz <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/20 10:48:13 by hdeniz            #+#    #+#              #
#    Updated: 2023/10/20 10:48:15 by hdeniz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# https://nafuka11.github.io/philosophers-visualizer/

CC			=	gcc
# [COMPILER]

FLAGS		=	-Wall -Wextra -Werror -pthread #-fsanitize=thread -g
# [COMPILER FLAGS]

MAIN_FLAGS	=	-Wall -Wextra -Werror -pthread #-fsanitize=thread -g
# [COMPILER FLAGS]

# [MAIN]
	MAIN_EXE	=	"philo.exe"
	# [EXECUTABLE PROGRAM NAME]

	NAME		=	./philo/main.a
	# [COMPILED LIBRARY FILE'S NAME (STATIC LINK LIBRARY)]

	MAIN		=	./philo/main.c
	# [MAIN PRODUCT TO COMPILE]

	SRC			=	./philo/functions/ft_msleep.c \
					./philo/functions/get_time.c \
					./philo/functions/ft_atoi.c \
					./philo/functions/check_args.c \
					./philo/functions/fill_the_arguments.c \
					./philo/functions/create_threads.c \
					./philo/functions/thread_philo.c \
					./philo/functions/free_everything.c \
					./philo/functions/kill_checker.c
	# [FILES TO COMPILE]

	OBJ			=	$(eval OBJ := $$(SRC:.c=.o))$(OBJ)
	# [.c FILE NAMES TO .o]
# [MAIN]

# [BONUS]
	BONUS_EXE	=	"philo_bonus.exe"
	# [EXECUTABLE PROGRAM NAME]

	BONUS_NAME	=	./philo_bonus/main_bonus.a
	# [COMPILED BONUS LIBRARY FILE'S NAME (STATIC LINK LIBRARY)]

	BONUS		=	./philo_bonus/main_bonus.c
	# [BONUS FILE]

	BONUS_SRC	=	./philo_bonus/functions/check_args.c \
					./philo_bonus/functions/fill_the_arguments.c \
					./philo_bonus/functions/free_everything.c \
					./philo_bonus/functions/create_process/create_process.c \
					./philo_bonus/functions/create_process/print_massage.c \
					./philo_bonus/functions/create_process/process_philo.c \
					./philo_bonus/functions/create_process/sem/sem_set_end.c \
					./philo_bonus/functions/create_process/sem/sem_sub_total_eaten_meal.c \
					./philo_bonus/functions/create_process/threads/check_end.c \
					./philo_bonus/functions/create_process/threads/sub_total_eaten_meal.c \
					./philo_bonus/functions/create_process/threads/update_starving.c \
					./philo_bonus/functions/libft/ft_atoi.c \
					./philo_bonus/functions/libft/ft_msleep.c \
					./philo_bonus/functions/libft/get_time.c
	# [BONUS FILES TO COMPILE]

	BONUS_OBJ	=	$(eval BONUS_OBJ := $$(BONUS_SRC:.c=.o))$(BONUS_OBJ)
	# [.c FILE NAMES TO .o]
# [BONUS]

# ANIMATION VARIABLES
N_FILES		:=	0
FILES_N		:=	0
# ANIMATION VARIABLES

# ANIMATION
define progress_bar
	$(eval PBAR := $(shell echo $(1)*100/$(2)*100/100 | bc))
	$(eval PDONE := $(shell echo $(PBAR)*4/10 | bc))
	$(eval PLEFT := $(shell echo 40-$(PDONE) | bc))
	$(eval PSEQ := $(shell seq 0 1 $(PLEFT) 2>/dev/null))
	$(eval PEMPTY := $(shell if [ "$(1)" -ne "$(2)" ]; then printf "░%.0s" $(PSEQ); fi))
	$(eval PFILL := $(shell printf "█%.0s" $(shell seq 1 $(PDONE))))
	@printf "\r $(shell tput setaf 11)[$(shell tput setaf 14)$(PFILL)$(PEMPTY)$(shell tput setaf 11)] $(PBAR)%% - $(shell tput setaf 10)[$(1)/$(2)]$(shell tput setaf 11) [$(shell tput setaf 13)$(3)$(shell tput setaf 11)]                                    "
endef
# ANIMATION

a: all
all: $(NAME)

%.o: %.c
	$(eval FILES_N := $(shell echo $(FILES_N)+1 | bc))
	$(call progress_bar,$(FILES_N),$(N_FILES),$<)
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME): files_n_calculator $(OBJ)
	@ar -rcs $(NAME) $(OBJ)
	@echo ""
	@echo ""
	@echo " $(shell tput setab 2)$(shell tput setaf 15)$(NAME) Done !$(shell tput sgr0)"
	@echo ""
	@if [ -a $(MAIN) ]; \
	then \
		$(CC) $(FLAGS) $(MAIN) $(NAME) $(MAIN_FLAGS) -o $(MAIN:.c=); \
		mv "$(MAIN:.c=)" "./$(MAIN_EXE)"; \
		echo " $(shell tput setab 2)$(shell tput setaf 15)$(MAIN) Done !$(shell tput sgr0)" ; \
		echo "" ; \
	fi;

c: clean
clear: clear
clean:
	@rm -f $(OBJ)
	@rm -f $(BONUS_OBJ)
	@echo ""
	@echo " $(shell tput setaf 15)$(shell tput setab 1)Clearing Objective Files$(shell tput sgr0)"
	@echo ""

fc: fclean
fclear: fclean
fclean: clean
	@if [ -a $(NAME) ]; \
	then \
		rm -f $(NAME) ; \
		echo "" ; \
		echo " $(shell tput setab 1)$(shell tput setaf 11)$(NAME)$(shell tput setaf 15) deleted$(shell tput sgr0)" ; \
		echo "" ; \
	fi;
	@if [ -a $(BONUS_NAME) ]; \
	then \
		rm -f $(BONUS_NAME) ; \
		echo "" ; \
		echo " $(shell tput setab 1)$(shell tput setaf 11)$(BONUS_NAME)$(shell tput setaf 15) deleted$(shell tput sgr0)" ; \
		echo "" ; \
	fi;
	@if [ -a $(MAIN_EXE) ]; \
	then \
		rm -f $(MAIN_EXE) ; \
		echo "" ; \
		echo " $(shell tput setab 1)$(shell tput setaf 11)$(MAIN_EXE)$(shell tput setaf 15) deleted$(shell tput sgr0)" ; \
		echo "" ; \
	fi;
	@if [ -a $(BONUS_EXE) ]; \
	then \
		rm -f $(BONUS_EXE) ; \
		echo "" ; \
		echo " $(shell tput setab 1)$(shell tput setaf 11)$(BONUS_EXE)$(shell tput setaf 15) deleted$(shell tput sgr0)" ; \
		echo "" ; \
	fi;

n: norminette
norm: norminette
norminette:
	@echo ""
	@echo " $(shell tput setab 10)$(shell tput setaf 0)Checking Norminette Rules $(shell tput sgr0)"
	@norminette ./philo
	@norminette ./philo_bonus
	@echo ""
	@echo " $(shell tput setab 11)$(shell tput setaf 0)Checking Header Norminette Rules $(shell tput sgr0)"
	@norminette -R CheckDefine *.h

b: bonus
bonus: mlx files_n_calculator_bonus $(BONUS_OBJ)
	@ar -rcs $(BONUS_NAME) $(BONUS_OBJ)
	@$(CC) $(FLAGS) $(BONUS) $(BONUS_NAME) $(MLX) $(MAIN_FLAGS) -o $(BONUS:.c=)
	@mv "$(BONUS:.c=)" "./$(BONUS_EXE)"
	@echo " $(shell tput setab 2)$(shell tput setaf 15)$(BONUS) Done !$(shell tput sgr0)"
	@echo ""

files_n_calculator:
	@echo "$(shell tput sgr0)"
	@echo ""
	$(eval FILES_N := 0)
	$(eval N_FILES := $(shell echo $(SRC) | wc -w | sed "s/ //g" | bc))

files_n_calculator_bonus:
	@echo "$(shell tput sgr0)"
	@echo ""
	$(eval FILES_N := 0)
	$(eval N_FILES := $(shell echo $(BONUS_SRC) | wc -w | sed "s/ //g" | bc))

r: fclean all
re: fclean all

.PHONY: all a clean clear c fclean fclear fc re r norminette norm n bonus b mlx
