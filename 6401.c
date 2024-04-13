#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Mariam Mohamed Bahaa Youssef Elshafei ID 6401 group3 section 2
typedef struct
{
    char *name;
    int starting_time;
    int remaining_time;
} Process;

typedef struct
{
    Process data;
    struct Node* next;
} Node;

typedef struct
{
    Node* head, *tail;
} Queue;

Queue* init()
{
    Queue *q = malloc(sizeof(Queue));
    q -> head = q -> tail = NULL;
    return q;
}

int isEmpty(Queue* q)
{
    if(q->head == NULL)
        return 1;
    return 0;
}

Process dequeue(Queue *q)
{
    Process p;
    Node *temp =  q -> head;
    p = q -> head -> data;
    q -> head = q -> head -> next;
    free(temp);
    if( q -> head == NULL)
        q -> tail = NULL;
    return p;
}

void enqueue(Queue *q, Process val)
{
    Node *n = malloc(sizeof(Node));
    n -> data = val;
    n -> next = NULL;
    if(q -> head == NULL)
        q -> head = q -> tail = n;
    else
        q -> tail -> next = n;
    q -> tail = n;

}

void destroy(Queue *q)
{
    Node *current = malloc(sizeof(Node));
    Node *nextNode = malloc(sizeof(Node));
    current = q -> head;
    while( current != NULL)
    {
        nextNode = current -> next;
        free(current);
        current = nextNode;
    }
    q -> head = q-> tail = NULL;
}

void printQueue(Queue *q)
{
    Node *temp = malloc(sizeof(Node));
    temp = q -> head;
    while(temp != NULL)
    {
        printf("%d\n", temp -> data);
        temp = temp -> next;
    }
}

void RoundRobin(char* filename)
{
    FILE *f=fopen(filename,"r");
    char *token, line[200];
    int totalTime, i=0, j, count=0;
    Process p[100];
    Queue *q = init();
    fscanf(f,"%[^\n]",line);
    token=strtok(line,"=");
    token=strtok(NULL,"=");
    fscanf(f,"\n");
    totalTime = atoi(token);

    while(fgets(line, 200, f)!=NULL)
    {
        p[i].name = malloc(200);
        token = strtok(line," ");
        strcpy(p[i].name,token);
        token = strtok(NULL," ");
        p[i].starting_time = atoi(token);
        token = strtok(NULL," ");
        p[i].remaining_time = atoi(token);
        i++;
        count++;

    }
    fclose(f);

    for(i=0; i<totalTime; i++)
    {
        for(j=0; j<count; j++)
        {
            if(p[j].starting_time == i)
                enqueue(q, p[j]);
        }
        if(!isEmpty(q))
        {
            Process x = dequeue(q);
            if(x.remaining_time>0)
            {
                x.remaining_time=(x.remaining_time)-1;
                if(x.remaining_time == 0)
                    printf("%s \t (%d-->%d) %s aborts\n", x.name, i, i+1, x.name);
                else
                {
                    printf("%s \t (%d-->%d)\n", x.name, i, i+1);
                    enqueue(q, x);
                }
            }
        }
        else
            printf("idle \t (%d-->%d)\n", i, i+1);

    }
    printf("stop");
}

int main()
{
    char filename[261];
    puts("Enter file name or Ctrl+Z to exit:");
    puts("----------------------------------");
    while(fgets(filename, 260, stdin) != NULL)
    {
        filename[strlen(filename)-1]='\0';
        if(fopen(filename,"r"))
            RoundRobin(filename);
        else
        {
            puts("File Not Found!");
            puts("----------------------------------");
        }
        puts("\nEnter file name or Ctrl+Z to exit:");
        puts("----------------------------------");
    }

    return 0;
}
