#include<stdio.h>

int limit, refString[100], frames, count, flag, frmArr[10], pageFault;
int hit;
float hitRatio, faultRatio;

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
    hit = 0;
    hitRatio = 0;
    faultRatio = 0;
    for(int i = 0; i < frames; i++){
        frmArr[i] = -1;
    }
}
void display(){
    hit = limit - pageFault;
    hitRatio = (float)hit/limit * 100;
    faultRatio = 100-hitRatio;
    printf("Hits = %d\nPage Faults = %d\nHitratio = %.2f, Faultratio = %.2f\n",hit, pageFault, hitRatio, faultRatio);
}
void fifo(){
    reset();
    printf("\nFIFO\n");
    for(int i = 0; i < limit; i++){
        flag = 0;
        for(int j = 0; j < frames; j++){
            if(frmArr[j] == refString[i]){
                flag = 1;
                break;
            }
        }
        if(flag == 0){
            frmArr[count] = refString[i];
            count = (count+1)%frames;
            pageFault++;
        }
        printf("%d  ->  ",refString[i]);
        for(int k = 0; k < frames; k++){
            printf("%d ",frmArr[k]);
        }
        printf("\n");
    }
    display();
}

void lru(){
    reset();
    printf("\nLRU\n");
    int lru[frames];
    for(int j = 0; j < frames; j++){
        lru[j]=-1;
    }
    for(int i = 0; i < limit; i++){
        flag = 0;
        for(int j = 0; j < frames; j++){
            if(frmArr[j] == refString[i]){
                flag = 1;
                lru[j] = i;
                break;
            }
        }
        if(flag == 0){
            int min = 0;
            for(int j = 1; j < frames; j++){
                if(lru[j] < lru[min]){
                    min = j;
                }
            }
            frmArr[min] = refString[i];
            lru[min] = i;
            pageFault++;
        }
        printf("%d  ->  ",refString[i]);
        for(int k = 0; k < frames; k++){
            printf("%d ",frmArr[k]);
        }
        printf("\n");
    }display();
}
void lfu(){
    reset();
    printf("\nLFU\n");
    int freqArr[frames];
    for(int i = 0; i < frames; i++){
        freqArr[i] = 0;
    }
    int loadTime[frames];
    for(int i = 0; i < frames; i++){
        loadTime[i] = -1;
    }
    for(int i = 0; i < limit; i++){
        flag = 0;
        for(int j = 0; j < frames; j++){
            if(refString[i] == frmArr[j]){
                flag = 1;
                freqArr[j]++;
                break;
            }
        }
        if(flag == 0){
            int minIndex = 0;
            int minFreq = freqArr[0];
            for(int j = 1; j < frames; j++){
                if(freqArr[j] < minFreq){
                    minFreq = freqArr[j];
                    minIndex = j;
                }
                else if( freqArr[j] == minFreq){
                    if(loadTime[j] < loadTime[minIndex]){
                        minIndex = j;
                    }
                }
            }
            frmArr[minIndex] = refString[i];
            freqArr[minIndex] = 1;
            loadTime[minIndex] = i;
            pageFault++;
        }
        printf("%d  ->  ",refString[i]);
        for(int k = 0; k < frames; k++){
            printf("%d ",frmArr[k]);
        }
        printf("\n");
    }display();
}
void optimal(){
    reset();
    printf("\nOPTIMAL\n");
    int optimal[frames];
    for(int j = 0; j < frames; j++){
        optimal[j]=0;
    }
    for(int i = 0; i < limit; i++){
        flag = 0;
        for(int j = 0; j < frames; j++){
            if(refString[i] == frmArr[j]){
                flag = 1;
                break;
            }
        }
        if(flag == 0){
            int replace = 0;
            int far = -1;
            for(int j = 0; j < frames; j++){
                int found = 0;
                for(int k = i+1; k < limit; k++){
                    if(frmArr[j] == refString[k]){
                        found = 1;
                        optimal[j] = k;
                        break;
                    }
                }
                if(found == 0){
                    replace = j;
                    break;
                }
                if(optimal[j] > far){
                    far = optimal[j];
                    replace = j;
                }
            }
        }
    }
}
void main(){
    read();
    fifo();
    lru();
    lfu();
    optimal();
}