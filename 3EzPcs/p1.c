#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct d {
    int x = 0;
    struct d *next;
} nodeD;

nodeD *Add(nodeD *head, int i){
    nodeD *newHead = (nodeD *)malloc(sizeof(nodeD));
    newHead->x = i;
    newHead->next = head;
    return newHead;

};

void liste(){
    nodeD *head = NULL;
    head = (nodeD *)malloc(sizeof(nodeD));
    for(int i = 1; i <= 100; i++){
        head = Add(head, i);
        printf("%d\n", head->x);
    }
    nodeD *h = head;
    while(h != NULL){
        printf("%d\n", h->x);
        h = h->next;
    }
};

int main(int argc, char *argv[]){
    pid_t x;
    for(int i = 0; i <= 2; i++){
        x = fork();
        printf("%d\n", x);
    }
    liste();
    return 0;

}

