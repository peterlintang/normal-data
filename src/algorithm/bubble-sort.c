
#include <stdio.h>
#include <stdlib.h>

/**
 * 冒泡排序函数
 * @param arr 待排序数组
 * @param n   数组长度
 */
void bubble_sort(void **arr, int n, int (*cmp)(void *, void *)) 
{
    int i, j;
    void *temp = NULL;

    for (i = 0; i < n - 1; i++) 
    {
        for (j = 0; j < n - 1 - i; j++) 
	{
            if (cmp(arr[j], arr[j + 1]) > 0) 
	    {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

#if 0
static int cmp(void *priv_a, void *priv_b)
{
	int a = (int)priv_a;
	int b = (int)priv_b;

	if (a > b)
		return 1;
	else if (a < b)
		return -1;
	else
		return 0;
}

int main(int argc, char *argv[]) 
{
    void **arr = NULL;;
    int n = 18;

    if (argc == 2)
    {
	n = atoi(argv[1]);
    }

    arr = (void **)calloc(n, sizeof(void *));
    for (int i = 0; i < n; i++) 
    {
	arr[i] = (void *)(random() % n);
	printf("%d ", (int)arr[i]);
    }
    printf("\n");

    bubble_sort(arr, n, cmp);

    for (int i = 0; i < n; i++) 
    {
        printf("%d ", (int)arr[i]);
    }
    printf("\n");

    return 0;
}
#endif

