

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mempool.h"

// ==========================================
// 内存池结构体定义
// ==========================================
struct MemoryPool {
    void *pool_buffer;    // 指向一次性申请的超大连续内存块
    void **free_list;     // 回收站（空闲链表栈），用于存放被 free 的节点指针
    int node_size;	  // one node occupy spaces
    int max_nodes;          // 内存池容量上限
    int next_available;     // 大内存块中下一个未被使用的节点下标
    int free_top;           // 回收站栈顶指针
};


MemoryPool* init_memory_pool(int max_nodes, int node_size)
{
    MemoryPool *mp = (MemoryPool *)malloc(sizeof(MemoryPool));
    if (!mp) return NULL;

    mp->node_size = node_size;
    mp->max_nodes = max_nodes;
    mp->next_available = 0;
    mp->free_top = 0;

    mp->pool_buffer = (void *)malloc(node_size * max_nodes);
    mp->free_list = (void **)malloc(sizeof(void *) * max_nodes);

    memset(mp->pool_buffer, 0, node_size * max_nodes);
    memset(mp->free_list, 0, sizeof(void *) * max_nodes);

    if (!mp->pool_buffer || !mp->free_list) 
    {
        if (mp->pool_buffer) free(mp->pool_buffer);
        if (mp->free_list) free(mp->free_list);
        free(mp);
        return NULL;
    }
    return mp;
}

void *pool_alloc_node(MemoryPool *mp) 
{
    if (mp->free_top > 0) 
    {
        mp->free_top--;
        return mp->free_list[mp->free_top];
    }

    if (mp->next_available < mp->max_nodes) 
    {
        void *node = (void *)(((char *)mp->pool_buffer) + mp->next_available * mp->node_size);
        mp->next_available++;
        return node;
    }

    return NULL;
}

void pool_free_node(MemoryPool *mp, void *node) 
{
    if (!node) return;

    mp->free_list[mp->free_top] = node;
    mp->free_top++;
}

void destroy_memory_pool(MemoryPool *mp) 
{
    if (!mp) return;
    free(mp->pool_buffer);
    free(mp->free_list);
    free(mp);
}


#if 0
int main(int argc, char *argv[])
{
#define MAX_NODES	1024
#define NODE_SIZE	sizeof(float)

	MemoryPool *pool = NULL;
	float *p = NULL;

	pool = init_memory_pool(MAX_NODES, NODE_SIZE);
	if (pool == NULL)
	{
		printf("create pool failed\n");
		exit(0);
	}

	for (int i = 0; i < MAX_NODES; i++)
	{
		p = (float *)pool_alloc_node(pool);
		*p = i * 1.0;
		printf("i: %d, value: %f\n", i, *p);
		pool_free_node(pool, p);
	}

	destroy_memory_pool(pool);

	exit(0);
}

#endif

