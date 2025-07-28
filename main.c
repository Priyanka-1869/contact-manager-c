// main.c
#include <stdio.h>
#include "contact_manager.h"

int main() {
    init_pool();
    int choice;

    while (1) {
        show_menu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        if (choice == 1) {
            Contact* c = (Contact*)pool_alloc();
            if (c) {
                printf("Enter Contact ID: ");
                scanf("%d", &c->id);

                printf("Enter Name: ");
                scanf(" %31[^\n]", c->name);

                char phone[16];
                do {
                    printf("Enter Phone (10 digits): ");
                    scanf(" %15s", phone);
                } while (!is_valid_phone(phone));
                strcpy(c->phone, phone);

                char email[32];
                do {
                    printf("Enter Email: ");
                    scanf(" %31s", email);
                } while (!is_valid_email(email));
                strcpy(c->email, email);

                int index = get_block_index(c);
                printf("Contact added at index %d\n", index);
            }
        } else if (choice == 2) {
            display_contacts();
        } else if (choice == 3) {
            int index;
            printf("Enter contact index to delete: ");
            scanf("%d", &index);
            pool_free(index);
        } else if (choice == 4) {
            int index;
            printf("Enter contact index to edit: ");
            scanf("%d", &index);
            edit_contact(index);
        } else if (choice == 5) {
            compact_memory_pool();
        } else if (choice == 6) {
            display_pool_status();
        } else if (choice == 7) {
            printf("Exiting Contact Manager. Goodbye!\n");
            break;
        } else {
            printf("Invalid option. Try again.\n");
        }
    }

    return 0;
}
