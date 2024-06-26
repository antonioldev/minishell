NAME    		= minishell
CC      		= gcc
LFLAGS  		= -lgcov
CFLAGS  		= -g -Wall -Wextra -Werror

ifdef COV
    CFLAGS += -fprofile-arcs -ftest-coverage
endif

MAIN_SRCS	=	src/main.c \
			src/prompt/manage_input.c \
			src/prompt/handler.c \
			src/prompt/utils.c \
			src/signals/handler.c \
			src/state/init.c \
			src/state/allocate_pipe_memory.c \
			src/token/check_input.c \
			src/token/check_sintax.c \
			src/token/tokenize.c \
			src/token/find_string.c \
			src/token/find_dollar.c \
			src/token/set_command_structure.c \
			src/token/add_path_to_cmd.c \
			src/token/manage_empty_node.c \
			src/token/find_redirections.c \
			src/token/find_redirection_helper.c \
			src/token/create_args_array.c \
			src/token/wildcard/handler.c \
			src/token/wildcard/list.c \
			src/token/wildcard/utils.c \
			src/token/split_complex_command.c \
			src/token/manage_list/token_list_1.c \
			src/token/manage_list/file_list_1.c \
			src/variables/find_env_vars.c \
			src/variables/replace_env_vars.c \
			src/variables/delete_env_var.c \
			src/variables/manage_list/var_list_1.c \
			src/clean/remove_unwanted_nodes.c \
			src/clean/free_fd_malloc.c \
			src/clean/free_malloc.c \
			src/clean/free_wildcard.c \
			src/error/error.c \
			src/execute/execute.c \
			src/execute/execute_helper.c \
			src/execute/open_fd.c \
			src/execute/open_fd_helper.c \
			src/execute/set_redirection.c \
			src/execute/built_in/handler.c \
			src/execute/built_in/cd_cmd.c \
			src/execute/built_in/exit_cmd.c \
			src/execute/built_in/env_cmd.c \
			src/execute/built_in/export_cmd.c \
			src/execute/built_in/export_helper.c \
			src/execute/built_in/unset_cmd.c \
			src/execute/built_in/echo_cmd.c \
			src/execute/built_in/pwd_cmd.c \

TEST_SRCS := $(shell find tests/unit/ -type f -name '*_test.c')
TEST_EXES = $(TEST_SRCS:.c=)

COVERAGE_FILES = *.gcda *.gcno *.info coverage_report

MAIN_OBJS = $(MAIN_SRCS:%.c=$(OBJ_F)%.o)
TEST_OBJS = $(filter-out $(OBJ_F)src/main.o, $(MAIN_OBJS))

LIBFT = ./libs/libft
LIBFT_LIB = $(LIBFT)/libft.a
LIB_FLAGS = -lreadline -ltinfo

UNITY_ROOT = tests/libs/unity
UNITY_SRCS = $(UNITY_ROOT)/unity.c
UNITY_OBJS = $(UNITY_SRCS:.c=.o)

OBJ_F   = ./objs/
RM      = rm -rf

GREEN   = \033[0;32m
RESET   = \033[0m

all: $(NAME)

$(NAME): $(MAIN_OBJS)
	@printf "\n"
	@make -C $(LIBFT)
	@printf "$(GREEN)==> Libft compiled ✅\n\n$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME) $(MAIN_OBJS) $(LIBFT_LIB) $(LIB_FLAGS)
	@printf "$(GREEN)==> Minishell compiled ✅\n\n$(RESET)"

$(OBJ_F)%.o: %.c
	@printf "\033[0;33mGenerating minishell objects... %-33.33s\r" $@
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

libft:
	make -C $(LIBFT)

test: $(NAME) $(TEST_EXES)

$(UNITY_ROOT)/%.o: $(UNITY_ROOT)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_EXES): % : %.c $(UNITY_OBJS)
	$(CC) $(CFLAGS) -I$(UNITY_ROOT) -Isrc -o $@ $< $(UNITY_OBJS) $(TEST_OBJS) \
	$(LIBFT_LIB) $(LIB_FLAGS) $(LFLAGS)

run_tests: re test $(TEST_EXES)
	@for test in $^; do \
		echo Running $$test; \
		./$$test; \
	done

coverage: run_tests
	lcov --rc branch_coverage=1 --capture --directory . --output-file coverage.info
	lcov --rc branch_coverage=1 --remove coverage.info 'tests/libs/*' --output-file coverage_filtered.info
	genhtml --rc branch_coverage=1 coverage_filtered.info --output-directory coverage_report

coverage_clean:
	$(RM) $(COVERAGE_FILES) $(COVERAGE_DIR) coverage_report/ tests/libs/*/*.gcda tests/libs/*/*.gcno tests/unit/*/*.gcda tests/unit/*/*.gcno

clean: coverage_clean
	make clean -C $(LIBFT)
	@printf "$(GREEN)==> Libft Cleaned✅\n\n$(RESET)"
	$(RM) $(OBJ_F)* $(TEST_EXES) $(UNITY_OBJS)
	@printf "$(GREEN)==> Minishell Cleaned ✅\n\n$(RESET)"

fclean: clean coverage_clean
	make fclean -C $(LIBFT)
	$(RM) $(NAME)
	@printf "$(GREEN)==> Minishell fully cleaned ✅\n\n$(RESET)"

re: fclean all

norminette:
	norminette src/ libs/

.PHONY: all clean fclean re libft test run_tests coverage coverage_clean