//Indexed allocation
 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node
{
    int data;
    struct node* strt;
    char name[100];
    int otloc[100];
};
struct node hrdisk[100];
struct node * start=NULL;
char cname[100]; 
int csize,nme=0,count,len,i,j=0,f;

void insert()
{
    printf("Enter the file name: ");
    scanf("%s", cname);
    printf("Enter the size of the file: ");
    scanf("%d", &csize);

    count = 0;

    // Check if enough free space exists
    for (int i = 0; i < 100; i++)
        if (hrdisk[i].data == -1)
            count++;
    j=0;
    if (count >= csize)
    {
        printf("\nFile represented using:- %d", ++nme);
        printf("\nFile allocation possible\n");

        struct node *previous = NULL;
        struct node *start = NULL;
        f=-1;
        for (len = csize, i = 0; len > 0; i++)
        {
            if (hrdisk[i].data == -1)
            {
                if (f==-1)
                    f=i;
                hrdisk[f].otloc[j++]=i;
                hrdisk[i].data = nme;       // Assign the unique file number
                //hrdisk[i].otloc[i] = NULL;      // Initialize the link to NULL
                strcpy(hrdisk[i].name, cname); // Copy the file name
                len--; // Decrease the length remaining to be allocated
                
                // If this is the first block of the file, mark it as the start
                if (start == NULL)
                {
                    start = &hrdisk[i];  // First block of the file
                }
               
                printf("%d--",i);
            }
        }

        printf("\nFile successfully allocated with start block at index: %ld\n", start - hrdisk);
        return;
    }
    else
    {
        printf("\nFile allocation not possible\n");
        return;
    }
}
void search()
{
    char fname[100];
    printf("\nPlease enter the file name to search: ");
    scanf("%s", fname);
    
    int i;
    for (i = 0; i < 100; i++)
    {
        if (strcmp(fname, hrdisk[i].name) == 0)
            break;  // Found the file, exit the loop
    }
    
    if (i == 100)  // If loop completes without finding the file
    {
        printf("\nFile not found!\n");
        return;
    }
    
    struct node* temp = &hrdisk[i];
    printf("\nFile '%s' is allocated at the following locations: ", fname);
    for(int j=0;j<100;j++)
    {
        if(hrdisk[i].otloc[j]!=0)
            printf("\n%d-->%d\n",i,hrdisk[i].otloc[j]);
    }
    
    printf("\n");
}


void ran()
{
    int n;
    printf("\nEnter the number of times random function should work: ");
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        int r=rand()%100;    //random value between 100 and 0 is generated
        if(hrdisk[r].data!=1)       //checks if the space is already occupied by any file or not
        {
            hrdisk[r].data=0;   // allocate the location data and name
            strcpy(hrdisk[r].name,"~");
    
        }
    }
}
void display()
{
    for(int i=0;i<100;)
    {
        for(int j=0;j<5;j++)
        {
            printf("[%s]\t",hrdisk[i].name);
            printf("%d\t[",hrdisk[i].data);
            for(int k=0;k<5;k++)
             printf("%d,",hrdisk[i].otloc[k]);
            printf("]\t");
            i=i+1;
        }
        printf("\n");
    }
}


int main()
{
    
    for(int i=0;i<100;i++)
    {
        hrdisk[i].data=-1;
        strcpy(hrdisk[i].name," ");
    }
    int ch;
    do
    {
    printf("\n\n\tMENU\n1.Insert\n2.Display\n3.Search\n4.Random\n\tEnter your choice:\t");
    scanf("%d",&ch);
    printf("\n");
    switch(ch)
    {
        case 1:insert(); break;
        case 2: display(); break;
        case 3: search(); break;
        case 4: ran(); break;
        case 5: break;
    }
        
    }while(ch!=5);
}