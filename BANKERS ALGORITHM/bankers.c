#include <stdio.h>

int allocation[100][100], need[100][100], available[100], max[100][100], flag, work[100], finished[100], safe[100], count, pros, res;
int pno, req[100];

void read() {
    printf("Enter the number of processes: ");
    scanf("%d", &pros);
    printf("Enter the number of resources: ");
    scanf("%d", &res);

    printf("Enter the allocation matrix: ");
    for (int i = 0; i < pros; i++) {
        for (int j = 0; j < res; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter the max matrix: ");
    for (int i = 0; i < pros; i++) {
        for (int j = 0; j < res; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    for (int i = 0; i < pros; i++) {
        for (int j = 0; j < res; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    printf("Enter the available resources: ");
    for (int i = 0; i < res; i++) {
        scanf("%d", &available[i]);
    }
}

void display() {
    printf("Need matrix:\n");
    for (int i = 0; i < pros; i++) {
        for (int j = 0; j < res; j++)
            printf("%d ", need[i][j]);
        printf("\n");
    }
}

void bankers() {
    display();
    count = 0;
    for (int i = 0; i < pros; i++) {
        finished[i] = 0;
    }
    for (int i = 0; i < res; i++) {
        work[i] = available[i];
    }
    while (count < pros) {
        flag = 1;
        for (int i = 0; i < pros; i++) {
            if (finished[i] == 0) {
                flag = 0;
                for (int j = 0; j < res; j++) {
                    if (need[i][j] > work[j]) {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0) {
                    safe[count++] = i;
                    for (int k = 0; k < res; k++) {
                        work[k] += allocation[i][k];
                    }
                    finished[i] = 1;
                }
            }
        }
        if (flag == 1) {
            break;
        }
    }
    if (count == pros) {
        printf("Safe sequence: ");
        for (int i = 0; i < pros - 1; i++) {
            printf("P%d -> ", safe[i] + 1);
        }
        printf("P%d\n", safe[pros - 1] + 1);
    } else {
        printf("System is not in a safe state\n");
    }
}

void request() {
    printf("Enter the request process: ");
    scanf("%d", &pno);
    pno--;
    printf("Enter the request sequence: ");
    for (int i = 0; i < res; i++) {
        scanf("%d", &req[i]);
    }
    flag = 0;
    for (int i = 0; i < res; i++) {
        if (req[i] > available[i]) {
            flag = 1;
            break;
        }
    }
    if (flag == 0) {
        for (int i = 0; i < res; i++) {
            available[i] -= req[i];
            allocation[pno][i] += req[i];
            need[pno][i] -= req[i];
        }
        printf("Request can be allocated\n");
        bankers();
        for (int i = 0; i < res; i++) {
            available[i] += req[i];
            allocation[pno][i] -= req[i];
            need[pno][i] += req[i];
        }
    } else {
        printf("Request cannot be allocated\n");
    }
}

void main() {
    read();
    bankers();
    request();
}
