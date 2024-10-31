//Pass 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
    FILE *fp1,*fp2,*fp3,*fp4,*fp5;
    int loc,flag,flag1,length;
    char label[100],opcode[100],operand[100],locctr[100];
    char sym[100],val1[100],op[100],val2[100];
    int start;
    fp1=fopen("optab.txt","r");
    fp2=fopen("sampleip.txt","r");
    fp3=fopen("intermediate.txt","w");
    fp4=fopen("length.txt","w");
    fp5=fopen("symtab.txt","w");
    
    fscanf(fp2,"%s\t%s\t%s",label,opcode,operand);
    
    if(strcmp(opcode,"START")==0)
    {
        start=strtol(operand,NULL,16);
        loc=start;
        fprintf(fp3,"%s\t%s\t%s\n",label,opcode,operand);
        fscanf(fp2,"%s\t%s\t%s",label,opcode,operand);
    }
    printf("LOC |\tLABEL |\tOPCODE|\tOPERAND |\n-------------------------------\n");
    while(strcmp(opcode,"END")!=0)
    {
        if(strcmp("**",label)!=0)
        {
            while(fscanf(fp5,"%s\t%s",sym,val1)!=EOF)
            {
                if(strcmp(sym,label)==0)
                {
                    flag=1;
                    break;
                }
            }
            if(flag==0)
            {
                fprintf(fp5,"\n%s\t%04X",label,loc);
            }
        }
        
        fprintf(fp3,"%04X\t%s\t%s\t%s\n",loc,label,opcode,operand);
        printf("%04X\t%s\t%s\t%s\n",loc,label,opcode,operand);
            
        if(strcmp(opcode," ")!=0)
        {
            while(fscanf(fp1,"%s\t%s",op,val2)!=EOF)
            {
                if(strcmp(opcode,op)==0)
                {
                    flag1=1;
                    loc=loc+3;
                    break;
                }
            }
            rewind(fp1);
            if(flag1==0)
            {
                if(strcmp(opcode,"WORD")==0)
                    loc=loc+3;
                else if(strcmp(opcode,"BYTE")==0)
                {
                    int len=strlen(operand)-3;
                    loc=loc+len;
                }
                else if(strcmp(opcode,"RESB")==0)
                {
                    loc=loc+strtol(operand,NULL,10);
                }
                else if(strcmp(opcode,"RESW")==0)
                {
                    loc=loc+(3*strtol(operand,NULL,16));
                }
                
            }
            
            fscanf(fp2,"%s\t%s\t%s",label,opcode,operand);
            flag=0;
            flag1=0;
        }
    }
    fprintf(fp3,"%04X\t%s\t%s\t%s",loc,label,opcode,operand);
    printf("%04X\t%s\t%s\t%s\n",loc,label,opcode,operand);
    length=loc-start;
    fprintf(fp4,"%04X",length);
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    fclose(fp5);
}

/*
sampleinput.txt
BUFTOREC	START	3000
WRREC	LDX	ZERO
WLOOP	TD	OUTPUT
**	JEO	WLOOP
**	LDCH	BUFFER,X
**	WD	OUTPUT
**	TIX	LENGTH
**  JLT WLOOP
OUTPUT	BYTE	X'05'
ZERO	WORD	0
BUFFER	RESB	4096
LENGTH	RESW	1
**	END	WRREC



question 1 is above and question 2 is below.
each of them have different solutions.
at a time only one question will work since its written to work till END of the code.


COPY    START   2000
**  LDA ALPHA
**  ADD BETA
**  STA GAMMA
BETA    WORD    3
ALPHA   EQU *
GAMMA   RESW    1
**      END


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
3017	ZERO	WORD	0
301A	BUFFER	RESB	4096
401A	LENGTH	RESW	1
401D	**	END	WRREC

question 1 above and question 2 below
on running only one output should be obtained

COPY	START	2000
2000	**	LDA	ALPHA
2003	**	ADD	BETA
2006	**	STA	GAMMA
2009	BETA	WORD	3
200C	ALPHA	EQU	*
200C	GAMMA	RESW	1
200F	**	END	BUFTOREC

length.txt
101D   //length of 1st question

000F   //length of 2nd question

symtab.txt
// symtab of 1st question
WRREC	3000
WLOOP	3003
OUTPUT	3015
ZERO	3017
BUFFER	301A
LENGTH	401A

//symtab of 2nd question
BETA	2009
ALPHA	200C
GAMMA	200C
*/
