#include "../../libs/unity/unity.h"
#include "../../../src/minishell.h"

static int	return_null = 0;

__attribute__((weak)) char *getcwd(char *buf, size_t size)
{
	(void)size;
	if (return_null) return (NULL);

    strcpy(buf, "mocked_cwd");
	return (buf);
}

void setUp(void) {
    //printf("Setting up...\n");
}

void tearDown(void) {
    //printf("Tearing down...\n");
}


void test_cwd_state_set(void)
{
	t_state state;
	state.command_status = 0;
	set_cwd(&state);
	TEST_ASSERT_EQUAL_STRING("mocked_cwd", state.cwd);
}

void test_cwd_state_set_with_error(void)
{
	t_state state;
	state.command_status = 1;
	return_null = 1;
	set_cwd(&state);
	TEST_ASSERT_EQUAL_STRING("Unknown", state.cwd);
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_cwd_state_set);
	RUN_TEST(test_cwd_state_set_with_error);
	return UNITY_END();
}