#include <stdio.h>
#include <stdlib.h>

struct node {
    int pid, at, bt, ct, tat, wt;
    struct node* next;
    struct node* prev;
};

struct node* Create(int n) {
    struct node* head = NULL;
    struct node* temp = NULL;

    for (int i = 0; i < n; i++) {
        struct node* newNode = (struct node*)malloc(sizeof(struct node));
        newNode->pid = i + 1;
        printf("\nProcess - %d\n\n", i + 1);
        printf("Burst Time: ");
        scanf("%d", &newNode -> bt);
        
        if (head == NULL) {
            head = temp = newNode;
            newNode -> next = newNode -> prev = NULL;
        }
		else {
            temp->next = newNode;
            newNode->prev = temp;
            newNode->next = NULL;
            temp = newNode;
        }
    }
    return head;
}
void findWT(struct node* head) {
    struct node* temp = head;
    while (temp != NULL) {
        if (temp == head)
            temp -> wt = 0;
		else {
            struct node* prevNode = temp->prev;
            temp -> wt = (prevNode->at) + (prevNode->bt) + (prevNode->wt) - (temp->at);
            if (temp->wt < 0)
				temp->wt = 0;
        }
        temp = temp->next;
    }
}

void findTATandCT(struct node* head) {
    struct node* temp = head;
    while (temp != NULL) {
        temp->tat = temp->bt + temp->wt;
        temp->ct = temp->at + temp->tat;
        temp = temp->next;
    }
}

void display(struct node* head, int n) {
    struct node* ptr = head;
    float total_wt = 0;
    float total_tat = 0;

    printf("\n------------------- FCFS -------------------");
    printf("\nPID\tAT\tBT\tCT\tWT\tTAT\n");
    printf("-------------------------------------------\n");
    while (ptr != NULL) {
        total_wt += ptr->wt;
        total_tat += ptr->tat;
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", ptr->pid, ptr->at, ptr->bt, ptr->ct, ptr->wt, ptr->tat);
        ptr = ptr->next;
    }
    printf("-------------------------------------------\n");

    printf("\nAverage Waiting Time: %.2f ms", total_wt / n);
    printf("\nAverage Turn Around Time: %.2f ms", total_tat / n);
}

void main() {
    printf("First Come, First Serve CPU Scheduling\n");
    printf("--------------------------------------\n\n");
    printf("Enter The Total Number of Processes: ");
    int n;
    scanf("%d", &n);

    struct node* head = Create(n);
    findWT(head);
    findTATandCT(head);
    display(head, n);
}
