#include<stdio.h>

struct process{
    int pid, at, bt, ct, tat, wt;
}p[100];

int n, sum_tat = 0, sum_wt = 0;
float avg_tat = 0, avg_wt = 0;

void arrivalSort(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n-1-i; j++){
            if(p[j].at > p[j+1].at){
                struct process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}

void avgCalc(){
    avg_tat = (float)sum_tat / n;
    avg_wt = (float)sum_wt / n;
    printf("Avg TAT = %.1f\nAvg WT = %.1f\n",avg_tat, avg_wt);
}

void calculateTimes(){
    p[0].ct = p[0].bt;
    for(int i = 1; i < n; i++){
        p[i].ct = p[i-1].ct + p[i].bt;
    }
    for(int i = 0; i < n; i++){
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        sum_wt += p[i].wt;
        sum_tat += p[i].tat;
    }
}

void display(){
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
}

void ghanttChart(){
    printf("Chantt Chart\n");
    for(int i = 0; i < n*4; i++){
        printf("----");
    }
    printf("\n|");
    for(int i = 0; i < n; i++){
        printf("\tP%d\t|",p[i].pid);
    }
    printf("\n");
    for(int i = 0; i < n*4; i++){
        printf("----");
    }
    printf("\n0");
    for(int i = 0; i < n; i++){
        printf("\t\t%d",p[i].ct);
    }
    printf("\n");
}

void main(){
    printf("Enter the number of process : ");
    scanf("%d",&n);
    for(int i = 0; i < n; i++){
        printf("Enter the process id, arrival time and burst time : ");
        scanf("%d%d%d",&p[i].pid, &p[i].at, &p[i].bt);
    }
    arrivalSort();
    calculateTimes();
    display();
    ghanttChart();
    avgCalc();
}