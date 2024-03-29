#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* previous;
    struct Node* next;
};


struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory Allocation Failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->previous = NULL;
    newNode->next = NULL;
    return newNode;
}


void insertAtBegin(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head != NULL) {
        (*head)->previous = newNode;
    }
    newNode->next = *head;
    *head = newNode;
}


void insertAtPosition(struct Node** head, int data, int position) {
    if (position < 0) {
        printf("Invalid Position.\n");
        return;
    }

    if (position == 0) {
        insertAtBegin(head, data);
        return;
    }

    struct Node* newNode = createNode(data);
    struct Node* current = *head;
    int currentPosition = 0;

    while (currentPosition < position - 1 && current != NULL) {
        current = current->next;
        currentPosition++;
    }

    if (current == NULL) {
        printf("Invalid Position.\n");
        return;
    }

    newNode->next = current->next;
    newNode->previous = current;
    if (current->next != NULL) {
        current->next->previous = newNode;
    }
    current->next = newNode;
}


void insertAtEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
    newNode->previous = current;
}


int deleteFromBegin(struct Node** head) {
    if (*head == NULL) {
        printf("List is Empty.\n");
        return -1;
    }
    struct Node* temp = *head;
    int deletedValue = temp->data;
    *head = (*head)->next;
    if (*head != NULL) {
        (*head)->previous = NULL;
    }
    free(temp);
    return deletedValue;
}


int deleteFromPosition(struct Node** head, int position) {
    if (*head == NULL) {
        printf("List is Empty.\n");
        return -1;
    }
    if (position < 0) {
        printf("Invalid Position.\n");
        return -1;
    }
    if (position == 0) {
        return deleteFromBegin(head);
    }
    struct Node* current = *head;
    int currentPosition = 0;
    while (current != NULL && currentPosition < position) {
        current = current->next;
        currentPosition++;
    }
    if (current == NULL) {
        printf("Invalid Position.\n");
        return -1;
    }
    int deletedValue = current->data;
    if (current->previous != NULL) {
        current->previous->next = current->next;
    }
    if (current->next != NULL) {
        current->next->previous = current->previous;
    }
    free(current);
    return deletedValue;
}


int deleteFromEnd(struct Node** head) {
    if (*head == NULL) {
        printf("List is Empty.\n");
        return -1;
    }
    struct Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    int deletedValue = current->data;
    if (current->previous != NULL) {
        current->previous->next = NULL;
    } else {
        *head = NULL;
    }
    free(current);
    return deletedValue;
}


void traverse(struct Node* head) {
    if (head == NULL) {
        printf("List is Empty.\n");
        return;
    }
    struct Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}


int search(struct Node* head, int value) {
    struct Node* current = head;
    int position = 0;
    while (current != NULL) {
        if (current->data == value) {
            return position;
        }
        current = current->next;
        position++;
    }
    return -1;
}


void displayMenu() {
    printf("\n");
    printf("1. Insert At Begin\n");
    printf("2. Insert At Position\n");
    printf("3. Insert At End\n");
    printf("4. Delete From Begin\n");
    printf("5. Delete From Position\n");
    printf("6. Delete From End\n");
    printf("7. Traverse\n");
    printf("8. Search\n");
    printf("9. Exit\n");
    printf("Enter your choice: ");
}


int main() {
    int choice;
    struct Node* head = NULL;
    while (1) {
        displayMenu();
        scanf("%d", &choice);
        int value, position, deletedValue;
        switch (choice) {
            case 1:
                printf("Enter Value to Insert at Begin of Linked List: ");
                scanf("%d", &value);
                insertAtBegin(&head, value);
                break;
            case 2:
                printf("Enter Value to Insert into Position of Linked List: ");
                scanf("%d", &value);
                printf("Enter Position of Linked List: ");
                scanf("%d", &position);
                insertAtPosition(&head, value, position);
                break;
            case 3:
                printf("Enter Value to Insert at End of Linked List: ");
                scanf("%d", &value);
                insertAtEnd(&head, value);
                break;
            case 4:
                deletedValue = deleteFromBegin(&head);
                if (deletedValue != -1)
                    printf("Data Item '%d' is Deleted from Begin of List\n", deletedValue);
                break;
            case 5:
                printf("Enter Position of Linked List: ");
                scanf("%d", &position);
                deletedValue = deleteFromPosition(&head, position);
                if (deletedValue != -1)
                    printf("Data Item '%d' is Deleted from '%d' Position of List\n", deletedValue, position);
                break;
            case 6:
                deletedValue = deleteFromEnd(&head);
                if (deletedValue != -1)
                    printf("Data Item '%d' is Deleted from End of List\n", deletedValue);
                break;
            case 7:
                traverse(head);
                break;
            case 8:
                int value;
                printf("Enter Element to Search in Linked List: ");
                scanf("%d", &value);
                int position = search(head, value);
                if (position != -1) {
                    printf("Data Item '%d' Found at '%d' position of Linked List.\n", value, position);
                } else {
                    printf("Data Item '%d'  Not Found in Linked List.\n", value);
                }
                break;
            case 9:
                printf("Exiting.....\n");
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}
