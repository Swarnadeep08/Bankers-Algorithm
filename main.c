// C program to implement safety algorithm (banker's algorithm)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct process
{
    int max[10];
    int allocated[10];
    int need[10];
};

int num_process, num_resources;

void showProcessInfo(struct process p[num_process])
{
    printf("\nPID\tMaximum\t\tAllocated\tNeed\n");
    for(int i=0; i<num_process; i++)
    {
        printf("P[%d]\t", i+1);
        for(int j=0; j<num_resources; j++)
            printf("%d ", p[i].max[j]);
        printf("\t\t");
        for(int j=0; j<num_resources; j++)
            printf("%d ", p[i].allocated[j]);
        printf("\t\t");
        for(int j=0; j<num_resources; j++)
            printf("%d ", p[i].need[j]);
        printf("\n");
    }
}

bool isSafeState(struct process p[num_process], int available[num_resources], int safeSeq[num_process])
{
    bool finish[num_process];
    int work[num_resources];
    for(int i=0; i<num_process; i++)
        finish[i] = false;
    for(int i=0; i<num_resources; i++)
        work[i] = available[i];

    bool proceed = true;
    int k=0;
    while(proceed)
    {
        proceed = false;
        for(int i=0; i<num_process; i++){
            if(finish[i]==false)
            {
                bool flag = true;
                for(int j=0; j<num_resources; j++){
                    if(p[i].need[j] <= work[j]){
                        continue;
                    }
                    else{
                        flag = false;
                        break;
                    }
                }
                if(flag==false)
                    continue; //check for next process

                //else update work
                for(int j=0; j<num_resources; j++)
                    work[j] += p[i].allocated[j];

                finish[i] = true;
                safeSeq[k++] = i;
                proceed = true;
            }
        } // end of outer for loop
    } // end of outer while loop

    int i;
    for(i=0; i<num_process && finish[i]==true; i++){
        continue;
    }
    if(i==num_process)
        return true;
    else
        return false;

}

int main()
{
    int i, j;
    printf("Enter the number of processes: ");
    scanf("%d", &num_process);
    printf("Enter the number of resources: ");
    scanf("%d", &num_resources);

    int available[num_resources];
    int safeSeq[num_process];
    // array of structure containing process info
    struct process p[num_process];

    printf("----------------- Enter details of process ------------------\n");
    for(i=0; i<num_process; i++){
        printf("Enter details of process P[%d]\n", i+1);
        printf("Enter maximum need: ");
        for(j=0; j<num_resources; j++){
            scanf("%d", &p[i].max[j]);
        }
        printf("Enter no. of resources available: ");
        for(j=0; j<num_resources; j++){
            scanf("%d", &p[i].allocated[j]);
        }
        for(j=0; j<num_resources; j++){
            p[i].need[j] = p[i].max[j] - p[i].allocated[j];
        }
        printf("\n");
    }

    printf("Enter available resources: ");
    for(i=0; i<num_resources; i++)
        scanf("%d", &available[i]);

    showProcessInfo(p);

    if(isSafeState(p, available, safeSeq))
    {
        printf("\nSystem is in SAFE state\n");
        printf("SAFE sequence is: ");
        for(i=0; i<num_process; i++){
            printf("P[%d]-> ", safeSeq[i]+1);
        }
        printf("\n\n");
    }
    else
        printf("\nSystem is in UNSAFE state\n");

    return 0;
}
