#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 
char ans[100]=""; 
unsigned int start_addr; 

void print_memmap()
{ 
  printf("printing memory map...\n"); 
  int i=0; 
  while(ans[i]!='\0')
  { 
      printf("%06x: ",start_addr); 
      int count=4; 
      while(count>0)
      { 
        for(int j=0;j<8;j++)
        { 
          printf("%c",ans[i++]); 
          if(ans[i]=='\0')
          { 
              printf("X"); 
          } 
        } 
        printf(" "); 
        count--; 
        start_addr+=4; 
      }
      printf("\n"); 
  } 
} 

int main()
{ 
    FILE *fp1; 
    char inputline[100];   // read data from file
    char *token; //for tokeninzing
    
    fp1=fopen("object_program.txt","r"); 
    fscanf(fp1,"%s",inputline); 
                                    //starting address extraction.... 
    
    if(inputline[0]=='H')
    { 
        token=strtok(inputline,"^");  //H
        for(int i=0;i<2;i++)            // skip the name to reach the starting addres
            token=strtok(NULL,"^"); 
    } 
    else 
    { 
        printf("Invalid file format!!!"); 
        exit(1); 
    } 
    
    
    unsigned int addr=strtol(token,NULL,16); 
    
    printf("Starting address: %04X\n",addr);
    
    start_addr=addr; 
    
    while(fscanf(fp1,"%s",inputline)!=EOF)
    { 
        if(inputline[0]=='T')
        { 
            char *token2=strtok(inputline,"^");  
            token2=strtok(NULL,"^"); 
            unsigned int text_addr=strtol(token2,NULL,16); 
             
            if(text_addr>addr) //to print XX
            { 
                for(int i=addr;i<text_addr;i++)
                { 
                    printf("%04X : X X \n",addr++); 
                    strcat(ans,"XX"); 
                }
            
            } 
            char *len=strtok(NULL,"^"); 
            while((token2=strtok(NULL,"^"))!=NULL)
                 { 
                    //printf("%s\n",token2);  
                    int j=0; 
                    while(token2[j]!='\0')
                    { 
                        printf("%04X : %c %c \n",addr++,token2[j],token2[j+1]); 
                        // This is to store the data into an array for printing it later.
                        int temp=strlen(ans); 
                        ans[temp]=token2[j]; 
                        ans[temp+1]=token2[j+1]; 
                        ans[temp+2]='\0'; 
                        
                        j+=2; 
                    }
                     
                 }
            
        } 
        else if(inputline[0]=='E')
        { 
            printf("End record reached.."); 
        } 
        else
        { 
            printf("INVALID FILE FORMAT...."); 
            exit(1); 
        }
        
    } 
    print_memmap(); 
} 


/*
sample input 

H^COPY^001000^00002F 
T^001004^15^04040C^00040F^E00412^3003EE^08041
T^001015^06^0B0B0B^120012 
E^001000

*/