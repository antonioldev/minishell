#include "../../libs/unity/unity.h"
#include "../../../src/minishell.h"


void setUp(void) {
    //printf("Setting up...\n");
}

void tearDown(void) {
    //printf("Tearing down...\n");
}

void test_free_args_array(void)
{
	t_token_list tokens;
	char **args;
	int length = 2;

	args = (char **)malloc((length + 1) * sizeof(char *));
	args[0] = ft_strdup("arg-1");
	args[1] = ft_strdup("arg-2");
	tokens.args = args;

	TEST_ASSERT_EQUAL_STRING("arg-1", tokens.args[0]);
	TEST_ASSERT_EQUAL_STRING("arg-2", tokens.args[1]);
	free_args_array(&tokens);

	TEST_ASSERT_NULL(tokens.args);
}

void test_free_allocation_malloc(void)
{
	char **args;
	char **args_2;
	int length = 2;
	
	t_redir *infile_1 = malloc(sizeof(t_redir));
    infile_1->fd = 1;
    infile_1->token = WORD;
    infile_1->found = 1;
    infile_1->value = strdup("infile_1");
    infile_1->next = NULL;

	t_redir *outfile_1 = malloc(sizeof(t_redir));
    outfile_1->fd = 1;
    outfile_1->token = WORD;
    outfile_1->found = 1;
    outfile_1->value = strdup("outfile_1");
    outfile_1->next = NULL;

	args = (char **)malloc((length + 1) * sizeof(char *));
	args[0] = ft_strdup("arg-1");
	args[1] = ft_strdup("arg-2");

	t_token_list *t1 = (t_token_list *)malloc(sizeof(t_token_list));
	t1->value = ft_strdup("test-t1");
	t1->token = WORD;
	t1->path = ft_strdup("test-path-1");
	t1->infile = infile_1;
	t1->outfile = outfile_1;
	t1->args = args;

    t_redir *infile_2 = malloc(sizeof(t_redir));
    infile_2->fd = 1;
    infile_2->token = WORD;
    infile_2->found = 1;
    infile_2->value = strdup("infile_2");
    infile_2->next = NULL;

    t_redir *outfile_2 = malloc(sizeof(t_redir));
    outfile_2->fd = 1;
    outfile_2->token = WORD;
    outfile_2->found = 1;
    outfile_2->value = strdup("outfile_2");
    outfile_2->next = NULL;

	t_token_list *t2 = (t_token_list *)malloc(sizeof(t_token_list));
	t2->value = ft_strdup("test-t2");
	t2->token = SQUOTE;
	t2->path = ft_strdup("test-path-2");
	t2->infile = infile_2;
	t2->outfile = outfile_2;
	args_2 = (char **)malloc((length + 1) * sizeof(char *));
	args_2[0] = ft_strdup("2-arg-1");
	args_2[1] = ft_strdup("2-arg-2");
	t2->args = args_2;

	t_token_list *t3 = (t_token_list *)malloc(sizeof(t_token_list));
	t3->value = ft_strdup("test-t3");
	t3->token = DQUOTE;
	t3->path = ft_strdup("test-path-3");

	t_token_list *t4 = (t_token_list *)malloc(sizeof(t_token_list));
	t4->value = ft_strdup("test-t4");
	t4->token = LESS;
	t4->path = NULL;

	t1->next = t2;
	t2->next = t3;
	t3->next = t4;

	free_allocation_malloc(t1, NULL);

	TEST_ASSERT_NULL(t1->value);
	TEST_ASSERT_NULL(t1->path);
	TEST_ASSERT_NULL(t1->infile);
	TEST_ASSERT_NULL(t1->outfile);
	TEST_ASSERT_NULL(t1->args);

	TEST_ASSERT_NULL(t2->value);
	TEST_ASSERT_NULL(t2->path);
	TEST_ASSERT_NULL(t2->infile);
	TEST_ASSERT_NULL(t2->outfile);
	TEST_ASSERT_NULL(t2->args);

	TEST_ASSERT_NULL(t3->value);
	TEST_ASSERT_NULL(t3->path);
	TEST_ASSERT_NULL(t3->infile);
	TEST_ASSERT_NULL(t3->outfile);
	TEST_ASSERT_NULL(t3->args);

	TEST_ASSERT_NOT_NULL(t4->value);
	TEST_ASSERT_NULL(t4->path);
	TEST_ASSERT_NULL(t4->infile);
	TEST_ASSERT_NULL(t4->outfile);
	TEST_ASSERT_NULL(t4->args);
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_free_args_array);
	RUN_TEST(test_free_allocation_malloc);
	return UNITY_END();
}
