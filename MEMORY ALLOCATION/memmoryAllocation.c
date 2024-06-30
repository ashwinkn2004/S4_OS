#include<stdio.h>

struct block{
    int id, size, allocation, remSize; 
}b[100];

struct process{
    int id, size, blockNo, bremSize;
}p[100];

void readBlock(int limit){
    printf("Enter the Block ID : ");
    for(int i = 0; i < limit; i++){
        scanf("%d",&b[i].id);
    }
    printf("Enter the Size : ");
    for(int i = 0; i < limit; i++){
        scanf("%d",&b[i].size);
        b[i].remSize = b[i].size;
        b[i].allocation = -1;
    }
}

void readProcess(int limit){
    printf("Enter the Process ID : ");
    for(int i = 0; i < limit; i++){
        scanf("%d",&p[i].id);
    }
    printf("Enter the Size : ");
    for(int i = 0; i < limit; i++){
        scanf("%d",&p[i].size);
        p[i].blockNo = -1;
    }
}

void reset(int pLimit, int bLimit){
    for(int i = 0; i < pLimit; i++){
        p[i].blockNo = -1;
    }
    for(int i = 0; i < bLimit; i++){
        b[i].allocation = -1;
        b[i].remSize = b[i].size;
    }
}

void sortA(int limit){
    for(int i = 0; i < limit; i++){
        for(int j = 0; j < limit-1-i; j++){
            if(b[j].size > b[j+1].size){
                struct block temp = b[j];
                b[j] = b[j+1];
                b[j+1] = temp;
            }
        }
    }
}

void sortB(int limit){
    for(int i = 0; i < limit; i++){
        for(int j = 0; j < limit-1-i; j++){
            if(b[j].size < b[j+1].size){
                struct block temp = b[j];
                b[j] = b[j+1];
                b[j+1] = temp;
            }
        }
    }
}

void display(int pLimit, int bLimit){
    printf("PROCESS\tSIZE\tREMSIZE\tBLOCKNO\n");
    for(int i = 0; i < pLimit; i++){
        printf("%d\t%d\t%d\t%d\n",p[i].id, p[i].size, p[i].bremSize, p[i].blockNo);
    }
}

void firstFit(int pLimit, int bLimit){
    for(int i = 0; i < pLimit; i++){
        for(int j = 0; j < bLimit; j++){
            if(b[j].allocation == -1 && p[i].size < b[j].size){
                b[j].allocation = 1;
                b[j].remSize = b[j].size - p[i].size;
                p[i].bremSize = b[j].remSize;
                p[i].blockNo = b[j].id;
                break;
            }
            else p[i].bremSize = 0;
        }
    }
    display(pLimit, bLimit);
}

void bestFit(int pLimit, int bLimit){
    sortA(bLimit);
    firstFit(pLimit, bLimit);
}
void worstFit(int pLimit, int bLimit){
    sortB(bLimit);
    firstFit(pLimit, bLimit);
}
void main(){
    int bLimit, pLimit, ch;
    printf("Enter the total Number of blocks : ");
    scanf("%d",&bLimit);
    readBlock(bLimit);
    printf("Enter the total Number of process : ");
    scanf("%d",&pLimit);
    readProcess(pLimit);
    do{
        printf("1. First Fit\n2. Best Fit\n3. Worst Fit\nEnter the choice :");
        scanf("%d",&ch);
        switch(ch){
            case 1:
            firstFit(pLimit, bLimit);
            reset(pLimit, bLimit);
            break;

            case 2:
            bestFit(pLimit, bLimit);
            reset(pLimit, bLimit);
            break;

            case 3:
            worstFit(pLimit, bLimit);
            reset(pLimit, bLimit);
            break;
        }
    }while(ch != 4);
}
