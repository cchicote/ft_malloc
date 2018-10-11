#include "ft_malloc.h"

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	return (ptr);
}

void	ft_free(void *ptr)
{
	munmap(ptr, 1);
}

void	test_malloc_is_null(char *str_sample, char *str)
{
	if (str_sample == NULL)
		printf("str_sample == NULL\n");
	else
		printf("str_sample != NULL\n");

	if (str == NULL)
		printf("str == NULL\n");
	else
		printf("str != NULL\n");
}

void	test_malloc_then_isnull(char *str_sample, char *str, int size)
{
	str_sample = (char*)malloc((size_t)size);
	str = (char*)ft_malloc((size_t)size);

	printf("Checking if it points on NULL\n");
	test_malloc_is_null(str_sample, str);
	printf("\n");

	free(str_sample);
	free(str);
}

void	test_malloc(char *str_sample, char *str)
{
	int		sizes[] = {0, 10, 100, 1000};
	int 	i = 0;
	
	while (i < 4)
	{
		test_malloc_then_isnull(str_sample, str, sizes[i]);
		
		i++;
	}


}

int		main(void)
{
	char	*str_sample;
	char	*str;

	str_sample = NULL;
	str = NULL;
	test_malloc(str_sample, str);
	return (0);
}
