

#ifndef MEMPOOL_H__
#define MEMPOOL_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct MemoryPool MemoryPool;

MemoryPool* init_memory_pool(int max_nodes, int node_size);

void *pool_alloc_node(MemoryPool *mp);

void pool_free_node(MemoryPool *mp, void *node);

void destroy_memory_pool(MemoryPool *mp);



#endif // end of MEMPOOL_H__

