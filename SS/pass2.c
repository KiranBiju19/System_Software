//Pass 2

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main()
{
    FILE *fp1,*fp2,*fp3,*fp4,*fp5,*fp6;
    char label[100],opcode[100],operand[100],objcode[100],len[100],loc[100],strt[100];
    fp1=fopen("intermediate.txt","r");
    fp2=fopen("symtab.txt","r");
    fp3=fopen("optab.txt","r");
    fp4=fopen("length.txt","r");
    fp5=fopen("final.txt","w");
    fp6=fopen("assembler.txt","w");
    
    fscanf(fp1,"%s\t%s\t%s",label,opcode,operand);
    if(strcmp(opcode,"START")==0)
    {
        fprintf(fp5,"%s\t%s\t%s\n",label,opcode,operand);
        strcpy(strt, operand);
        
    }
    fscanf(fp4,"%s",len);
    fprintf(fp6,"H^%s^%s^%s\n",label,operand,len);
    fprintf(fp6,"T^%s^ ",strt);
    fscanf(fp1,"%s\t%s\t%s\t%s",loc,label,opcode,operand);
    char r1[100],v1[100],r2[100],v2[100];
    int flag1=0,flag2=0;
    while(strcmp(opcode,"END")!=0)
    {
        //symtab
        rewind(fp2);
        flag1=0, flag2=0;
        strcpy(v1,"0000");
        strcpy(v2,"0000");
        while(fscanf(fp2,"%s\t%s",r1,v1) != EOF)
        {
            if(strcmp(operand,r1)==0)
            {
                flag1=1;
                break;
            }
        }
        if(!flag1)
        {
           strcpy(v1, "0000");
        }
        
        //optab
        rewind(fp3);
        while(fscanf(fp3,"%s\t%s",r2,v2) != EOF)
        {
            if(strcmp(opcode,r2)==0)
            {
                flag2=1;
                break;
            }
            
        }
        
        if(!flag2)
        {
            if (strcmp(opcode, "WORD") == 0) 
            {
                strcpy(v2,operand);
                //printf("%s",v2);
            }
            
            else if (strcmp(opcode, "BYTE") == 0) 
            {
                if (operand[0] == 'X') 
                {
                    strncpy(v2, operand + 2, strlen(operand) - 3);
                    v2[strlen(operand) - 3] = '\0';
                } 
                else if (operand[0] == 'C') 
                {
                    strcpy(r2, "");
                    for (int i = 2; i < strlen(operand) - 1; i++)
                    {
                        char hex[3];
                        sprintf(hex, "%02X", operand[i]);
                        strcat(r2, hex);
                    }
                }
            }
            else if(strcmp(opcode,"RESW")==0 || strcmp(opcode,"RESB")==0 || strcmp(opcode,"END")==0)
            {
                strcpy(v1," ");
                strcpy(v2," ");
            }
        }
        fprintf(fp5,"%s\t%s\t%s\t%s\t%s%s\n",loc,label,opcode,operand,v2,v1);
        printf("%s\t%s\t%s\t%s\t%s%s\n",loc,label,opcode,operand,v2,v1);
        fscanf(fp1,"%s\t%s\t%s\t%s",loc,label,opcode,operand);
        if(strcmp(v2," ")!=0 && strcmp(v1," ")!=0)
            fprintf(fp6,"^%s%s",v2,v1);
    }
    fprintf(fp6,"\nE^%s",strt);
    
}



/*
intermediate.txt
BUFTOREC	START	3000
3000	WRREC	LDX	ZERO
3003	WLOOP	TD	OUTPUT
3006	**	JEO	WLOOP
3009	**	LDCH	BUFFER,X
300C	**	WD	OUTPUT
300F	**	TIX	LENGTH
3012	**	JLT	WLOOP
3015	OUTPUT	BYTE	X'05'
3016	ZERO	WORD	0
3019	BUFFER	RESB	4096
4019	LENGTH	RESW	1
401C	**	END	WRREC


optab.txt
LDA	00
LDX	04
ADD	18
COMP	28
DIV	24
JEO	30
JGT	34
JLT 38
LDCH	50
MUL	20
RD	D8
STA	0C
STCH	54
STX	10
SUB	1C
TD	E0
TIX	2C
WD	DC

symtab.txt
WRREC	3000
WLOOP	3003
OUTPUT	3015
ZERO	3016
BUFFER	3019
LENGTH	4019

length.txt
101C

assembler.txt
H^BUFTOREC^3000^101C
T^3000^27^043016^E03015^303003^500000^DC3015^2C4019^383003^050000^00000
E^3000

////you can use %06X in printf for printing hexa decimal digits in 6 didgits and %04X for printing 
////4 digits in hexadecimal

final.txt
BUFTOREC	START	3000
3000	WRREC	LDX	ZERO	043016
3003	WLOOP	TD	OUTPUT	E03015
3006	**	JEO	WLOOP	303003
3009	**	LDCH	BUFFER,X	500000
300C	**	WD	OUTPUT	DC3015
300F	**	TIX	LENGTH	2C4019
3012	**	JLT	WLOOP	383003
3015	OUTPUT	BYTE	X'05'	050000
3016	ZERO	WORD	0	00000
3019	BUFFER	RESB	4096	  
4019	LENGTH	RESW	1
*/