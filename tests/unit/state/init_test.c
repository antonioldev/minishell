#include "../../libs/unity/unity.h"
#include "../../../src/minishell.h"

__attribute__((weak)) char *getenv(const char *key)
{
	if (strcmp(key, "TEST_KEY") == 0)
		return ("test-value");
	if (strcmp(key, "SECOND_KEY") == 0)
		return ("second-value");
	return (NULL);
}

void setUp(void) {
    //printf("Setting up...\n");
}

void tearDown(void) {
    //printf("Tearing down...\n");
}

void test_init_state_correctly_without_env_vars(void)
{
    t_state state;

	char **envp;
	envp = NULL;
    init_state(&state, envp, 0, NULL);

	TEST_ASSERT_NULL(state.var_list);
	TEST_ASSERT_EQUAL_INT(0, state.command_status);
	TEST_ASSERT_NULL(state.token_list);
	TEST_ASSERT_EQUAL_INT(0, state.number_commands);
	TEST_ASSERT_EQUAL_INT(1, state.run);
	TEST_ASSERT_EQUAL_INT(3, state.original_stdin);
	TEST_ASSERT_EQUAL_INT(4, state.original_stdout);
	TEST_ASSERT_EQUAL_INT(5, state.null_fd);
}

void test_init_state_correctly_with_env_vars(void)
{
    t_state state;

	char *envp[] = {"TEST_KEY=test-value", "SECOND_KEY=second-value", "THIRD_KEY=", NULL};
    init_state(&state, envp, 0, NULL);

	TEST_ASSERT_EQUAL_INT(0, state.command_status);
	TEST_ASSERT_EQUAL_STRING("TEST_KEY", state.var_list->key);
	TEST_ASSERT_EQUAL_STRING("test-value", state.var_list->value);

	TEST_ASSERT_EQUAL_STRING("SECOND_KEY", state.var_list->next->key);
	TEST_ASSERT_EQUAL_STRING("second-value", state.var_list->next->value);
	
	TEST_ASSERT_EQUAL_STRING("THIRD_KEY", state.var_list->next->next->key);
	TEST_ASSERT_EQUAL_STRING("", state.var_list->next->next->value);
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_init_state_correctly_without_env_vars);
	RUN_TEST(test_init_state_correctly_with_env_vars);
	return UNITY_END();
}