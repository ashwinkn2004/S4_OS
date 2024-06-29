#include<stdio.h>

int head, limit, arr[100], headMovement = 0, currentHead, ch, index, value, maxVal, minVal = 0;

void sort(){
    for(int i = 0; i < limit; i++){
        for(int j = 0; j < limit-1-i; j++){
            if(arr[j] > arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void trackLeft(){
    for(int i = index ; i > 0; i--){
        headMovement += abs(currentHead - arr[i]);
        currentHead = arr[i];
        printf(" -> %d", currentHead);
    }
}

void trackRight(){
    for(int i = index; i < limit; i++){
        headMovement += abs(currentHead - arr[i]);
        currentHead = arr[i];
        printf(" -> %d", currentHead);
    }
}

void track(){
    int i;
    currentHead = head;
    printf("%d",currentHead);
    index;
    for(i = 0; i < limit; i++){
        if(arr[i] > head){
            index = i;
            break;
        }
    }
    if(ch == 0){
        trackLeft();
        printf(" -> %d",minVal);
        headMovement += abs(currentHead - minVal);
        currentHead = minVal;
        trackRight();
    }
    else{
        trackRight();
        printf(" -> %d",maxVal);
        headMovement += abs(currentHead - maxVal);
        currentHead = maxVal;
        trackLeft();
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
    printf("Enter the max limit : ");
    scanf("%d",&value);
    maxVal = value - 1;
    printf("Track side ? 0(leaft) | 1(right) : ");
    scanf("%d",&ch);
    sort();
    track();
}
