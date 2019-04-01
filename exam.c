#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct node{
    char color;
    struct node * next;
} node;

node* createNode(char col){
    node* temp = malloc(sizeof(node));
    temp->next = NULL;
    temp->color = col;
    return temp;
}

void addBack(node** head, char col){
    if((*head)==NULL){
        (*head) = createNode(col);
    }else{
        node* temp = createNode(col);
        node* current = (*head);
        while(current->next != NULL){
            current = current->next;
        }
        current->next = temp;
    }
}

void addFront(node** head, char col){
    if((*head)==NULL){
        (*head) = createNode(col);
    }else{
        node* newHead = createNode(col);
        node* oldHead = (*head);
        (*head) = newHead;
        newHead->next = oldHead;
    }
}

void addPosition(node** head, int pos, char col){
    int curpos = 1;
    node* current = (*head);

    while(curpos != pos){
        current = current->next;
        curpos++;
    }

    node* tempnew = createNode(col);

    tempnew->next = current->next;
    current->next = tempnew;
}

void reverseNode(node** head){
    node* current = (*head);
    node* freeHead = (*head);
    char temp[1024] = {0};
    int count = 0;
    while(current->next != NULL){
        temp[count] = current->color;
        count++;
        current = current->next;
    }
    temp[count] = current->color;

    node* newHead = createNode(current->color);
    count--; //Da der erste wert ja in vorheriger Zeile schon gesetzt wurde
    while(count>=0){
        addBack(&newHead, temp[count]);
        count--;
    }
    while(freeHead->next!=NULL){
        node* temp = freeHead->next;
        free(freeHead);
        freeHead=temp;
    }
    free(freeHead);
    (*head) = newHead;
    //free old *head
    //set old *head

}

void delPosition(node** head, int pos){
    int curpos = 1;
    node* current = (*head);
    node* before = NULL;

    while(curpos != pos){
        before = current;
        current = current->next;
        curpos++;
    }
    before->next = current->next;
    free(current);
    current=NULL;
}



void printList(node** head){
    node* current = (*head);
    printf("Lichterkette:");
    while(current->next != NULL){
        printf(" %c -", current->color);
        current = current->next;
    }
    printf(" %c\n", current->color);
}

int main()
{
    node* head = NULL;
    char menuInput = ' ';
    int running = 1;
    while(running){
        printf("m: ");
        scanf(" %c", &menuInput);
        char internalInput = ' ';
        int position = 2;

        switch(menuInput){
        case 'e':
            while(1){
                printf("l: ");
                scanf(" %c",&internalInput);
                if(internalInput == '0'){
                    break;
                }
                addBack(&head, internalInput);
            }
            break;
        case 'a':
            while(1){
                printf("l: ");
                scanf(" %c",&internalInput);
                if(internalInput == '0'){
                    break;
                }
                addFront(&head, internalInput);
            }
            break;
        case 'i':
            printf("p: ");
            scanf("%d",&position);
            printf("l: ");
            scanf(" %c", &internalInput);
            addPosition(&head, position, internalInput);
            break;
        case 'l':
            printf("p: ");
            scanf("%d",&position);
            delPosition(&head, position);
            break;
        case 'u':
            reverseNode(&head);
            break;
        case 'x':
            running = 0;
            //Gegen Speicher Error: alles wieder freigeben
            //Programm endet sowieso
            node* current = head;
            while(current->next!=NULL){
                node* temp = current->next;
                free(current);
                current = temp;
            }
            free(current);

            break;
        }
        if(running==1){
            printList(&head);
        }
    }
    return 0;
}