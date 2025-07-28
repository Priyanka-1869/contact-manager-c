#ifndef CONTACT_MANAGER_H
#define CONTACT_MANAGER_H

#include <stddef.h>

#define POOL_SIZE 1024

typedef struct {
    int id;
    char name[32];
    char phone[16];
    char email[32];
} Contact;

typedef struct {
    unsigned char data[POOL_SIZE];
    unsigned char block_used[POOL_SIZE / sizeof(Contact)];
} MemoryPool;

void init_pool();
void* pool_alloc();
void pool_free(int index);
int get_block_index(void* ptr);
void display_contacts();
void display_pool_status();
void edit_contact(int index);
void compact_memory_pool();
void show_menu();
int is_valid_phone(const char* phone);
int is_valid_email(const char* email);

#endif

