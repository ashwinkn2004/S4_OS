#include<stdio.h>

int head, limit, arr[100], headMovement = 0, currentHead;

void track(){
    currentHead = head;
    printf("%d",currentHead);
    for(int i = 0; i < limit; i++){
        headMovement += abs(currentHead - arr[i]);
        currentHead = arr[i];
        printf(" -> %d",currentHead);
    }
    printf("\nHead Movement = %d\n",headMovement);
}

void main(){
    printf("Enter the Head : ");
    scanf("%d",&head);
    printf("Enter the limit of elements : ");
    scanf("%d",&limit);
    printf("Enter the elements : ");
    for(int i = 0; i < limit; i++){
        scanf("%d",&arr[i]);
    }
    track();
}
