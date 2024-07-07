#include<stdio.h>

struct process {
    int at, bt, dbt, ct, tat, wt, pid;
}p[100];
struct chart{
    int pid, ct;
}chart[100];

int limit, ts, runtime = 0;
int selected[100], counter = 0, flag = 0;
int q[100], front = 0, rear = 0;
int cnt = 0;


void read(){
    printf("Enter the limit : ");
    scanf("%d",&limit);
    for(int i = 0; i < limit; i++){
        printf("Enter the AT, BT : ");
        scanf("%d%d",&p[i].at, &p[i].bt);
        p[i].dbt = p[i].bt;
        p[i].pid = i;
    }
    printf("Enter the time slice : ");
    scanf("%d",&ts);
}

void sort(){
    for(int i = 0; i < limit; i++){
        for(int j = 0; j < limit-1-i; j++){
            if(p[j].at > p[j+1].at){
                struct process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}

void roundRobin(){
    int i = 0;
    while(front <= rear){
        if(p[q[front]].bt <= ts){
            runtime += p[q[front]].bt;
            p[q[front]].ct = runtime;
            p[q[front]].bt = 0;
            chart[cnt].pid = p[q[front]].pid;
            chart[cnt].ct = p[q[front]].ct;
            cnt++;
        }
        else{
            runtime += ts;
            p[q[front]].bt -= ts;
            chart[cnt].pid = p[q[front]].pid;
            chart[cnt].ct = p[q[front]].ct;
            cnt++;
        }
        for(int i = 0; i < limit; i++){
            if(p[i].at <= runtime){
                flag = 0;
                for(int j = 0; j <= counter; j++){
                    if(p[i].pid == selected[j]) flag = 1;
                }
                if(flag == 0){
                    q[++rear] = p[i].pid;
                    selected[++counter] = p[i].pid;
                }
            }
        }
        if(p[q[front]].bt != 0){
            q[++rear] = p[q[front]].pid;
        }
        front++;
    }
}

void calculate(){
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i = 0; i < limit; i++){
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].dbt, p[i].ct, p[i].tat, p[i].wt);
    }
}

void ghantChart(){
    printf("Chantt Chart\n");
    for(int i = 0; i < cnt*4; i++){
        printf("----");
    }
    printf("\n|");
    for(int i = 0; i < cnt; i++){
        printf("\tP%d\t|",chart[i].pid+1);
    }
    printf("\n");
    for(int i = 0; i < cnt*4; i++){
        printf("----");
    }
    printf("\n0");
    for(int i = 0; i < cnt; i++){
        printf("\t\t%d",chart[i].ct);
    }
    printf("\n");
}


void main(){
    read();
    sort();
    selected[counter] = p[0].pid;
    q[rear] = p[0].pid;
    roundRobin();
    calculate();
    ghantChart();
}