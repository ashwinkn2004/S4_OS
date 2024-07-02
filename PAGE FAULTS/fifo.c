
#include <stdio.h>

int limit, refString[100], frames, frmArr[10], found, pageFault, count;

void read() {
    printf("Enter the number of elements : ");
    scanf("%d", &limit);
    printf("Enter the elements : ");
    for (int i = 0; i < limit; i++) {
        scanf("%d", &refString[i]);
    }
    printf("Enter the total number of frames : ");
    scanf("%d", &frames);
}

void reset(){
    pageFault = 0;
    count = 0;
    for(int i = 0; i < limit; i++){
        frmArr[i] = -1;
    }
}

void fifo() {
    reset();
    printf("\nFIFO\n");
    for (int i = 0; i < limit; i++) {
        found = 0;
        for (int j = 0; j < frames; j++) {
            if (frmArr[j] == refString[i]) {
                found = 1;
                break;
            }
        }
        if (found == 0) {
            frmArr[count] = refString[i];
            count = (count + 1) % frames;
            pageFault++;
        }
        printf("%d ->  ", refString[i]);
        for (int k = 0; k < frames; k++) {
            printf("%d  ", frmArr[k]);
        }
        printf("\n");
    }
    printf("Total Number of page faults = %d\n", pageFault);
}

void main() {
    read();
    fifo();
}
