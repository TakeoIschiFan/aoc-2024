#include "ht.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define FNV_BASIS 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

u64 fnv_hash(u64 key) {
    u64 hash = FNV_BASIS;

    unsigned char* ptr = (unsigned char*)&key;
    for (size_t i = 0; i < sizeof(key); i++) {
        hash ^= (u64)ptr[i];
        hash *= FNV_PRIME;
    }
    return hash;
}

ht_table* ht_create(void) {
    ht_table* table = calloc(1, sizeof(ht_table));
    table->length = 0;
    table->capacity = HT_INITIAL_CAPACITY;

    table->entries = calloc(table->capacity, sizeof(ht_entry*));

    return table;
}

void ht_free(ht_table* table) {
    // Free all entries in the hash table
    for (u64 i = 0; i < table->capacity; i++) {
        ht_entry* entry = table->entries[i];
        while (entry != NULL) {
            ht_entry* next = entry->next;
            free(entry);
            entry = next;
        }
    }

    free(table->entries);
    free(table);
}

void ht_insert(ht_table* table, u64 key, u64 value) {
    if ((float)table->length / table->capacity > 0.75) {
        ht_resize(table);
    }

    unsigned long hash = fnv_hash(key);
    long index = hash % table->capacity;

    ht_entry* new_entry = malloc(sizeof(ht_entry));
    new_entry->key = key;
    new_entry->value = value;
    new_entry->next = NULL;

    ht_entry* existing_entry = table->entries[index];
    if (existing_entry == NULL) {
        table->entries[index] = new_entry;
    } else {
        while (existing_entry->next != NULL) {
            existing_entry = existing_entry->next;
        }
        existing_entry->next = new_entry;
    }

    table->length++;
}

bool ht_find(ht_table* table, u64 key, u64* location) {
    u64 hash = fnv_hash(key);
    u64 index = hash % table->capacity;

    ht_entry* entry = table->entries[index];
    while (entry != NULL) {
        if (entry->key == key) {
            *location = entry->value;
            return true;
        }
        entry = entry->next;
    }
    return false;
}

void ht_resize(ht_table* table) {
    printf("need to resize hash table \n");
    u64 new_capacity = table->capacity * 2;
    ht_entry** new_entries = calloc(new_capacity, sizeof(ht_entry*));

    for (u64 i = 0; i < table->capacity; i++) {
        ht_entry* entry = table->entries[i];
        while (entry != NULL) {
            u64 hash = fnv_hash(entry->key);
            u64 index = hash % new_capacity;

            ht_entry* new_entry = malloc(sizeof(ht_entry));
            new_entry->key = entry->key;
            new_entry->value = entry->value;
            new_entry->next = new_entries[index];
            new_entries[index] = new_entry;

            entry = entry->next;
        }
    }

    free(table->entries);
    table->entries = new_entries;
    table->capacity = new_capacity;
}
