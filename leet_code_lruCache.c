#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAP_CAP 1024

typedef struct l_node {
    struct l_node* next;
    int key, val;
    struct l_node* prev;
} ListNode;

typedef struct list {
    ListNode* head;
    ListNode* tail;
} List;

typedef struct l_map {
    ListNode *map;
} ListMapping;

typedef struct {
    List cache;
    ListMapping* map;
    int currSz;
    int capacity;
} LRUCache;

void makeEmptyList(List* lst)
{
    lst->head = lst->tail = NULL;
}

bool isEmptyList(List lst)
{
    return !lst.head && !lst.tail;
}

ListNode* makeNewNode(int key, int val)
{
    ListNode* node = (ListNode*) malloc(sizeof(ListNode));
    node->val = val;
    node->key = key;
    node->next = node->prev = NULL;
    return node;
}

ListMapping* getListMapping(int capacity)
{
    ListMapping* map = (ListMapping*) calloc(capacity, sizeof(ListMapping));
    return map;
}

void insertToMap(ListMapping* map, int key, ListNode* node)
{
    map[key].map = node;
}

void insertToTail(List* lst, ListNode* node)
{

    if (isEmptyList(*lst)) {
        lst->tail = lst->head = node;
    } else {
        node->prev = lst->tail;
        lst->tail->next = node;
        lst->tail = node;
        node->next = NULL;
    }
}

void removeNode(List* lst, ListNode* node)
{
    if (lst->head == node && lst->tail == node)
        return;
    if (lst->head == node) {
        lst->head = lst->head->next;
        lst->head->prev = NULL;
    } else if (lst->tail == node) {
        lst->tail = node->prev;
        lst->tail->next = NULL;
    } else {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
}

LRUCache* lRUCacheCreate(int capacity)
{
    LRUCache* cache = (LRUCache*) malloc(sizeof(LRUCache));
    cache->map = getListMapping(MAP_CAP);
    makeEmptyList(&cache->cache);
    cache->capacity = capacity;
    cache->currSz = 0;
    return cache;
}

int lRUCacheGet(LRUCache* obj, int key)
{
    ListNode* node = obj->map[key].map;
    int res = -1;

    if (node != NULL) {
        res = node->val;
        removeNode(&obj->cache, node);
        insertToTail(&obj->cache, node);
    }

    return res;
}

ListNode* getNodeFromMap(ListMapping* map, int key)
{
    if (map[key].map == NULL) {
        return NULL;
    } else {
        return map[key].map;
    }
}

void nullifyMapKey(ListMapping* map, int key)
{
    map[key].map = NULL;
}

void lRUCachePut(LRUCache* obj, int key, int value)
{
    ListNode* node = getNodeFromMap(obj->map, key);

    if (node != NULL) {
        removeNode(&obj->cache, node);
        node->val = value;
        insertToTail(&obj->cache, node);
    } else {
        if (obj->currSz == obj->capacity) {
            nullifyMapKey(obj->map, obj->cache.head->key);
            if (obj->cache.head == obj->cache.tail) {
                makeEmptyList(&obj->cache);
            } else {
                obj->cache.head = obj->cache.head->next;
            }
            node = makeNewNode(key, value);
            insertToMap(obj->map, key, node);
            insertToTail(&obj->cache, node);
        } else {
            node = makeNewNode(key, value);
            insertToMap(obj->map, key, node);
            insertToTail(&obj->cache, node);
            obj->currSz++;
        }
    }
}

void lRUCacheFree(LRUCache* obj)
{
    for (int i = 0; i < MAP_CAP; i++) {
        if (obj->map[i].map != NULL)
            free(obj->map[i].map);
    }
    free(obj->map);
    free(obj);
}

void test1()
{
    LRUCache *newCache = lRUCacheCreate(2);

    lRUCachePut(newCache, 1, 1);
    lRUCachePut(newCache, 2, 2);
    printf("%d\n", lRUCacheGet(newCache, 1));

    lRUCachePut(newCache, 3, 3);
    printf("%d\n", lRUCacheGet(newCache, 2));

    lRUCachePut(newCache, 4, 4);
    printf("%d\n", lRUCacheGet(newCache, 1));
    printf("%d\n", lRUCacheGet(newCache, 3));
    printf("%d\n", lRUCacheGet(newCache, 4));
    lRUCacheFree(newCache);
    puts("================ End test 1 ================");
}

void test2()
{
    LRUCache *newCache = lRUCacheCreate(1);

    lRUCachePut(newCache, 2, 1);
    printf("%d\n", lRUCacheGet(newCache, 2));

    lRUCachePut(newCache, 3, 2);
    printf("%d\n", lRUCacheGet(newCache, 2));
    printf("%d\n", lRUCacheGet(newCache, 3));
    lRUCacheFree(newCache);
    puts("================ End test 2 ================");
}

void test3()
{
    LRUCache *newCache = lRUCacheCreate(2);

    printf("%d\n", lRUCacheGet(newCache, 2));

    lRUCachePut(newCache, 2, 6);
    printf("%d\n", lRUCacheGet(newCache, 1));

    lRUCachePut(newCache, 1, 5);
    lRUCachePut(newCache, 1, 2);

    printf("%d\n", lRUCacheGet(newCache, 1));
    printf("%d\n", lRUCacheGet(newCache, 2));
    lRUCacheFree(newCache);
    puts("================ End test 3 ================");
}

void test4()
{
    LRUCache *newCache = lRUCacheCreate(1);

    printf("%d\n", lRUCacheGet(newCache, 6));
    printf("%d\n", lRUCacheGet(newCache, 8));

    lRUCachePut(newCache, 12, 1);
    printf("%d\n", lRUCacheGet(newCache, 2));

    lRUCachePut(newCache, 15, 11);
    lRUCachePut(newCache, 5, 2);
    lRUCachePut(newCache, 1, 15);
    lRUCachePut(newCache, 4, 2);
    printf("%d\n", lRUCacheGet(newCache, 5));
    lRUCachePut(newCache, 15, 15);
    lRUCacheFree(newCache);
    puts("================ End test 4 ================");
}

int main()
{
    test1();
    test2();
    test3();
    test4();

    return 0;
}
