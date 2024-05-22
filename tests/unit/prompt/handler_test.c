#include "../../libs/unity/unity.h"
#include "../../../src/minishell.h"

void set_cwd(t_state *state)
{
    strcpy(state->cwd, "mocked_cwd");
}

void setUp(void) {
    //printf("Setting up...\n");
}

void tearDown(void) {
    //printf("Tearing down...\n");
}

void test_prompt_generation_command_status_1(void)
{
    t_state state;
    state.command_status = 1;
    set_cwd(&state);

    char *result = get_prompt(&state);
    TEST_ASSERT_EQUAL_STRING("\x01\x1B[31m\x02\x01\x1B[31m\x02-> \x01\x1B[36m\x02mocked_cwd\x01\x1B[0m\x02 ", result);
}

void test_prompt_generation_command_status_0(void)
{
    t_state state;
    state.command_status = 0;
    set_cwd(&state);

    char *result = get_prompt(&state);
    TEST_ASSERT_EQUAL_STRING("\x01\x1B[32m\x02\x01\x1B[32m\x02-> \x01\x1B[36m\x02mocked_cwd\x01\x1B[0m\x02 ", result);
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_prompt_generation_command_status_1);
	RUN_TEST(test_prompt_generation_command_status_0);
	return UNITY_END();
}