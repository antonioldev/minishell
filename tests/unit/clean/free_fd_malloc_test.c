#include "../../libs/unity/unity.h"
#include "../../../src/minishell.h"

int close_function_calls = 0;


__attribute__((weak)) int	close(int __fd)
{
	(void)__fd;
	close_function_calls++;
	return (1);
}

void setUp(void) {
    close_function_calls = 0;
}

void tearDown(void) {
    //printf("Tearing down...\n");
}

void test_clean_redirection(void)
{
    t_token token = WORD;

    t_redir *infile_1 = malloc(sizeof(t_redir));
    infile_1->fd = 3;
    infile_1->token = token;
    infile_1->found = 1;
    infile_1->value = strdup("infile_1");
    infile_1->next = NULL;

    t_redir *infile_2 = malloc(sizeof(t_redir));
    infile_2->fd = 4;
    infile_2->token = token;
    infile_2->found = 1;
    infile_2->value = strdup("infile_2");
    infile_2->next = NULL;

    infile_1->next = infile_2;

    t_redir *outfile_1 = malloc(sizeof(t_redir));
    outfile_1->fd = 6;
    outfile_1->token = token;
    outfile_1->found = 1;
    outfile_1->value = strdup("outfile_1");
    outfile_1->next = NULL;

    t_redir *outfile_2 = malloc(sizeof(t_redir));
    outfile_2->fd = 8;
    outfile_2->token = token;
    outfile_2->found = 1;
    outfile_2->value = strdup("outfile_2");
    outfile_2->next = NULL;

    outfile_1->next = outfile_2;

    t_token_list command = { .infile = infile_1, .outfile = outfile_1, .next = NULL };

    free_redirection(&command.infile, &command.outfile);

    TEST_ASSERT_EQUAL_INT(4, close_function_calls);
    TEST_ASSERT_NULL(command.infile);
    TEST_ASSERT_NULL(command.outfile);
}

void test_clean_redirection_without_close(void)
{
    t_token token = WORD;

    t_redir *infile_1 = malloc(sizeof(t_redir));
    infile_1->fd = 1;
    infile_1->token = token;
    infile_1->found = 1;
    infile_1->value = strdup("infile_1");
    infile_1->next = NULL;

    t_redir *infile_2 = malloc(sizeof(t_redir));
    infile_2->fd = 1;
    infile_2->token = token;
    infile_2->found = 1;
    infile_2->value = strdup("infile_2");
    infile_2->next = NULL;

    infile_1->next = infile_2;

    t_redir *outfile_1 = malloc(sizeof(t_redir));
    outfile_1->fd = 1;
    outfile_1->token = token;
    outfile_1->found = 1;
    outfile_1->value = strdup("outfile_1");
    outfile_1->next = NULL;

    t_redir *outfile_2 = malloc(sizeof(t_redir));
    outfile_2->fd = 1;
    outfile_2->token = token;
    outfile_2->found = 1;
    outfile_2->value = strdup("outfile_2");
    outfile_2->next = NULL;

    outfile_1->next = outfile_2;

    t_token_list command = { .infile = infile_1, .outfile = outfile_1, .next = NULL };

    free_redirection(&command.infile, &command.outfile);

    TEST_ASSERT_EQUAL_INT(0, close_function_calls);
    TEST_ASSERT_NULL(command.infile);
    TEST_ASSERT_NULL(command.outfile);
}

void test_free_all_memory_simple_command(void)
{
    t_state state;
    char *envp[] = {"TEST_KEY=test-value", "SECOND_KEY=second-value", "THIRD_KEY=", NULL};

    init_state(&state, envp, 0, NULL);
    state.input = ft_strdup("echo 123");
    manage_input(&state);
    t_state *p = &state;
    allocate_pipe_memory(&p);

    free_all_memory(&state);

    TEST_ASSERT_NULL(state.token_list);
    TEST_ASSERT_NULL(state.input);
    TEST_ASSERT_NULL(state.pipes);
    TEST_ASSERT_NULL(state.pids);
    TEST_ASSERT_NULL(state.var_list);
    TEST_ASSERT_NULL(state.path_env);
    TEST_ASSERT_NULL(state.segments);
    TEST_ASSERT_NULL(state.segments);
}

void test_free_all_memory_pipe_command(void)
{
    t_state state;
    char *envp[] = {"TEST_KEY=test-value", "SECOND_KEY=second-value", "THIRD_KEY=", NULL};

    init_state(&state, envp, 0, NULL);
    state.input = ft_strdup("echo 123 | echo 44");
    manage_input(&state);
    t_state *p = &state;
    allocate_pipe_memory(&p);

    free_all_memory(&state);

    TEST_ASSERT_NULL(state.token_list);
    TEST_ASSERT_NULL(state.input);
    TEST_ASSERT_NULL(state.pipes);
    TEST_ASSERT_NULL(state.pids);
    TEST_ASSERT_NULL(state.var_list);
    TEST_ASSERT_NULL(state.path_env);
    TEST_ASSERT_NULL(state.segments);
}

void test_free_all_memory_with_operator_command(void)
{
    t_state state;
    char *envp[] = {"TEST_KEY=test-value", "SECOND_KEY=second-value", "THIRD_KEY=", NULL};

    init_state(&state, envp, 0, NULL);
    state.input = ft_strdup("echo 123 && echo 44");
    manage_input(&state);
    t_state *p = &state;
    allocate_pipe_memory(&p);

    free_all_memory(&state);

    TEST_ASSERT_NULL(state.token_list);
    TEST_ASSERT_NULL(state.input);
    TEST_ASSERT_NULL(state.pipes);
    TEST_ASSERT_NULL(state.pids);
    TEST_ASSERT_NULL(state.var_list);
    TEST_ASSERT_NULL(state.path_env);
    TEST_ASSERT_NULL(state.segments);
}

void test_free_all_memory_with_empty_command(void)
{
    t_state state;
    char *envp[] = {"TEST_KEY=test-value", "SECOND_KEY=second-value", "THIRD_KEY=", NULL};

    init_state(&state, envp, 0, NULL);
    state.input = ft_strdup("");
    manage_input(&state);
    t_state *p = &state;
    allocate_pipe_memory(&p);

    free_all_memory(&state);

    TEST_ASSERT_NULL(state.token_list);
    TEST_ASSERT_NULL(state.input);
    TEST_ASSERT_NULL(state.pipes);
    TEST_ASSERT_NULL(state.pids);
    TEST_ASSERT_NULL(state.var_list);
    TEST_ASSERT_NULL(state.path_env);
    TEST_ASSERT_NULL(state.segments);
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_clean_redirection);
	RUN_TEST(test_clean_redirection_without_close);
	RUN_TEST(test_free_all_memory_simple_command);
	RUN_TEST(test_free_all_memory_pipe_command);
	RUN_TEST(test_free_all_memory_with_operator_command);
	RUN_TEST(test_free_all_memory_with_empty_command);
	return UNITY_END();
}