#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node *next;
}Node;

void append(Node **head, int value){
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data=value;
    newNode->next=NULL;

    if (*head == NULL){
        *head = newNode;
    }
    else{
        Node *temp = *head;
        while (temp -> next != NULL){
            temp = temp->next;
        }
        temp->next=newNode;
    }
}

void deleteNode(Node **head, int value){
    Node *temp = *head, *prev = NULL;

    if (temp != NULL && temp -> data == value){
        *head = temp->next;
        free(temp);
        return;
    }
    while (temp != NULL && temp->data != value){
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) return;

    prev->next = temp->next;
    free(temp);
}

void printList(Node *head){
    Node *temp = head;
    while(temp!=NULL){
        printf("%d -> ", temp->data);
        temp=temp->next;
    }
    printf("NULL\n");
}

int main(){
    Node *head = NULL;
    append(&head, 1);
    append(&head, 2);
    append(&head, 3);
    printf("초기 리스트: ");
    printList(head);

    // 노드 삭제
    deleteNode(&head, 2);
    printf("2 삭제 후 리스트: ");
    printList(head);

    // 노드 추가
    append(&head, 4);
    printf("4 추가 후 리스트: ");
    printList(head);

    return 0;
}