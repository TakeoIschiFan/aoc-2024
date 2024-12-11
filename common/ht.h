#pragma once

#include <stdbool.h>
#define HT_INITIAL_CAPACITY 1000000

#define u64 unsigned long long

typedef struct ht_entry {
    u64 key;
    u64 value;
    struct ht_entry* next;
} ht_entry;

typedef struct {
    ht_entry** entries; // Pointer to an array of ht_entry pointers
    u64 capacity;
    u64 length;
} ht_table;

ht_table* ht_create(void);
void ht_insert(ht_table* table, u64 key, u64 value);
bool ht_find(ht_table* table, u64 key, u64* location);
void ht_resize(ht_table* table);
void ht_free(ht_table* table);
