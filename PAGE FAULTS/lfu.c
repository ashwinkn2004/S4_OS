#include<stdio.h>

int limit, refString[100], frames, count, flag, frmArr[10], pageFault, freqArr[10];

void read(){
    printf("Enter the total number of elements : ");
    scanf("%d",&limit);
    printf("Enter the elements : ");
    for(int i = 0; i < limit; i++){
        scanf("%d",&refString[i]);
    }
    printf("Enter the frames : ");
    scanf("%d",&frames);
}

void reset(){
    count = 0;
    pageFault = 0;
    for(int i = 0; i < frames; i++){
        frmArr[i] = -1;
    }
}

void lfu(){
    reset();
    for(int i = 0; i < limit; i++){
        flag = 0;
        for(int j = 0; j < frames; j++){
            if(frmArr[j] == refString[i]){
                flag = 1;
                freqArr[j]++;
                break;
            }
        }
        if(flag == 0){
            int minFreq = freqArr[0];
            int minIndex = 0;
            for(int j = 1; j < frames; j++){
                if(freqArr[j] < minFreq){
                    minFreq = freqArr[j];
                    minIndex = j;
                }
            }
            frmArr[minIndex] = refString[i];
            freqArr[minIndex]++;
            pageFault++;
        }
        printf("%d  ->  ",refString[i]);
        for(int k = 0; k < frames; k++){
            printf("%d  ",frmArr[k]);
        }
        printf("\n");
    }
    printf("Page Faults = %d\n",pageFault);
}

void main(){
    read();
    lru();
}