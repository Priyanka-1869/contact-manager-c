#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include "contact_manager.h"

#define BLOCK_SIZE sizeof(Contact)
#define NUM_BLOCKS (POOL_SIZE / BLOCK_SIZE)

static MemoryPool pool;

void init_pool() {
    memset(pool.data, 0, sizeof(pool.data));
    memset(pool.block_used, 0, sizeof(pool.block_used));
    printf("Contact Manager Initialized: %d blocks of %lu bytes each.\n", NUM_BLOCKS, BLOCK_SIZE);
}

void* pool_alloc() {
    for (int i = 0; i < NUM_BLOCKS; i++) {
        if (!pool.block_used[i]) {
            pool.block_used[i] = 1;
            return &pool.data[i * BLOCK_SIZE];
        }
    }
    printf("No available memory blocks!\n");
    return NULL;
}

void pool_free(int index) {
    if (index < 0 || index >= NUM_BLOCKS || !pool.block_used[index]) {
        printf("Invalid index or block already free.\n");
        return;
    }
    pool.block_used[index] = 0;
    memset(&pool.data[index * BLOCK_SIZE], 0, BLOCK_SIZE);
    printf("Contact at index %d deleted.\n", index);
}

int get_block_index(void* ptr) {
    uintptr_t offset = (uintptr_t)ptr - (uintptr_t)pool.data;
    return offset / BLOCK_SIZE;
}

void display_contacts() {
    printf("\nSaved Contacts:\n");
    for (int i = 0; i < NUM_BLOCKS; i++) {
        if (pool.block_used[i]) {
            Contact* c = (Contact*)&pool.data[i * BLOCK_SIZE];
            printf("Index %d: ID=%d, Name=%s, Phone=%s, Email=%s\n", i, c->id, c->name, c->phone, c->email);
        }
    }
}

void display_pool_status() {
    int used = 0;
    printf("\nMemory Pool Status:\n");
    for (int i = 0; i < NUM_BLOCKS; i++) {
        printf("Block %2d: %s\n", i, pool.block_used[i] ? "Used" : "Free");
        if (pool.block_used[i]) used++;
    }
    printf("Total: %d | Used: %d | Free: %d\n", NUM_BLOCKS, used, NUM_BLOCKS - used);
}

void edit_contact(int index) {
    if (index < 0 || index >= NUM_BLOCKS || !pool.block_used[index]) {
        printf("Invalid or unallocated index.\n");
        return;
    }

    Contact* c = (Contact*)&pool.data[index * BLOCK_SIZE];
    printf("Editing Contact at index %d:\n", index);
    printf("Current: ID=%d, Name=%s, Phone=%s, Email=%s\n", c->id, c->name, c->phone, c->email);

    printf("Enter new ID: ");
    scanf("%d", &c->id);
    printf("Enter new Name: ");
    scanf(" %31[^\n]", c->name);

    char phone[16];
    do {
        printf("Enter new Phone (10 digits): ");
        scanf(" %15s", phone);
    } while (!is_valid_phone(phone));
    strcpy(c->phone, phone);

    char email[32];
    do {
        printf("Enter new Email: ");
        scanf(" %31s", email);
    } while (!is_valid_email(email));
    strcpy(c->email, email);

    printf("Contact updated.\n");
}
===
void compact_memory_pool() {
    int target = 0;
    for (int current = 0; current < NUM_BLOCKS; current++) {
        if (pool.block_used[current]) {
            if (current != target) {
                memcpy(&pool.data[target * BLOCK_SIZE], &pool.data[current * BLOCK_SIZE], BLOCK_SIZE);
                pool.block_used[target] = 1;
                pool.block_used[current] = 0;
            }
            target++;
        }
    }
    printf("Memory pool compacted.\n");
}

void show_menu() {
    printf("\n******Contact Manager******\n");
    printf("1. Add New Contact\n");
    printf("2. View All Contacts\n");
    printf("3. Delete Contact (by index)\n");
    printf("4. Edit Contact (by index)\n");
    printf("5. Compact Memory Pool\n");
    printf("6. Pool Status\n");
    printf("7. Exit\n");
    printf("Choose option: ");
}

int is_valid_phone(const char* phone) {
    if (strlen(phone) != 10) return 0;
    for (int i = 0; i < 10; i++) {
        if (!isdigit(phone[i])) return 0;
    }
    return 1;
}

int is_valid_email(const char* email) {
    int has_at = 0, has_dot = 0;
    for (int i = 0; email[i] != '\0'; i++) {
        if (email[i] == '@') has_at = 1;
        else if (email[i] == '.') has_dot = 1;
        else if (!isalnum(email[i]) && email[i] != '_' && email[i] != '-') return 0;
    }
    return has_at && has_dot;
}

