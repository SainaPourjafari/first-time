/// khat haye khata(baraye jump)

#include <stdio.h>
#include <string.h>
// #include <limits.h>
#include <stdlib.h>
#include <ctype.h>
// #include<windows.h>  //colors

// colors for errors
void red()
{
    printf("\033[0;31m");
}

void yellow()
{
    printf("\033[0;33m");
}

void whiteB()
{
    printf("\033[1;37m");
}

void reset()
{
    printf("\033[0m");
}

int array[32] = {0};
int sabbat[8] = {2, 2, 2, 2, 2, 2, 2, 2};

//(start)sabbat vaziat ha
void ParityFlag(int result)
{
    int count = 0;
    while (result > 0)
    {

        if (result % 2 == 1)
        {
            count++;
        }

        result /= 2;
    }

    if (count % 2 == 1)
    {
        sabbat[0] = 1;
    }

    else
    {
        sabbat[0] = 0;
    }
}

void ZeroFlag(int result)
{
    if (result == 0)
        sabbat[1] = 1;
    else
        sabbat[1] = 0;
}

void SignFlag(int result)
{
    if (result < 0)
        sabbat[2] = 1;
    else
        sabbat[2] = 0;
}

void OverflowFlagAdd(int result, int a1, int a2)
{
    if ((a1 > 0 && a2 > 0 && result < 0) || (a1 < 0 && a2 < 0 && result > 0))
        sabbat[5] = 1;
    else
        sabbat[5] = 0;
}

void OverflowFlagSub(int result, int a1, int a2)
{
    if ((a1 > 0 && a2 < 0 && result < 0) || (a1 < 0 && a2 > 0 && result > 0))
        sabbat[5] = 1;
    else
        sabbat[5] = 0;
}

void OverflowFlagProduct(int result, int a1, int a2)
{
    if (a1 != 0 && result / a1 != a2)
        sabbat[5] = 1;
    else
        sabbat[5] = 0;
}
//(end)sabbat vaziat ha

//(start)functions
void ADD(int add, int a1, int a2)
{
    array[add] = array[a1] + array[a2];

    ParityFlag(array[add]);
    ZeroFlag(array[add]);
    SignFlag(array[add]);
    OverflowFlagAdd(array[add], array[a1], array[a2]);
}

void SUB(int sub, int a1, int a2)
{
    array[sub] = array[a1] - array[a2];

    ParityFlag(array[sub]);
    ZeroFlag(array[sub]);
    SignFlag(array[sub]);
    OverflowFlagSub(array[sub], array[a1], array[a2]);
}

void AND(int and, int a1, int a2)
{
    array[and] = array[a1] & array[a2];

    ParityFlag(array[and]);
    ZeroFlag(array[and]);
    SignFlag(array[and]);
}

void XOR(int xor, int a1, int a2)
{
    array[xor] = array[a1] ^ array[a2];

    ParityFlag(array[xor]);
    ZeroFlag(array[xor]);
    SignFlag(array[xor]);
}

void OR(int or, int a1, int a2)
{
    array[or] = array[a1] | array[a2];

    ParityFlag(array[or]);
    ZeroFlag(array[or]);
    SignFlag(array[or]);
}

void ADDI(int addi, int a, int imm)
{
    array[addi] = array[a] + imm;

    ParityFlag(array[addi]);
    ZeroFlag(array[addi]);
    SignFlag(array[addi]);
    OverflowFlagAdd(array[addi], array[a], imm);
}

void SUBI(int subi, int a, int imm)
{
    array[subi] = array[a] - imm;

    ParityFlag(array[subi]);
    ZeroFlag(array[subi]);
    SignFlag(array[subi]);
    OverflowFlagSub(array[subi], array[a], imm);
}

void ANDI(int andi, int a, int imm)
{
    array[andi] = array[a] & imm;

    ParityFlag(array[andi]);
    ZeroFlag(array[andi]);
    SignFlag(array[andi]);
}

void XORI(int xori, int a, int imm)
{
    array[xori] = array[a] ^ imm;

    ParityFlag(array[xori]);
    ZeroFlag(array[xori]);
    SignFlag(array[xori]);
}

void ORI(int ori, int a, int imm)
{
    array[ori] = array[a] | imm;

    ParityFlag(array[ori]);
    ZeroFlag(array[ori]);
    SignFlag(array[ori]);
}

void MOV(int rt, int imm)
{
    array[rt] = imm;
    // printf("%d", array[rt]);
}

void SWP(int a1, int a2)
{
    int t = array[a1];
    array[a1] = array[a2];
    array[a2] = t;
}

void DUMP_REGS()
{
    whiteB();
    printf("\n ARRAY:");
    reset();

    for (int i = 0; i < 32; i++)
    {
        printf("%d  ", array[i]);
    }
    whiteB();
    printf("\n SABBAT VAZIAT HA(remember:the value 2 does not matter): ");
    reset();

    for (int i = 0; i < 8; i++)
    {
        printf("%d  ", sabbat[i]);
    }
}

void DUMP_REGS_F()
{
    FILE *file;
    file = fopen("regs.txt", "w");

    fprintf(file, "array:");
    for (int i = 0; i < 32; i++)
    {
        fprintf(file, "%d ", array[i]);
    }

    fprintf(file, "\nsabbat vaziat ha:");
    for (int i = 0; i < 8; i++)
    {
        fprintf(file, "%d ", sabbat[i]);
    }
}

void INPUT()
{
    scanf("%d", &array[0]);
}

void OUTPUT()
{
    printf("%d", array[0]);
}

void DIV(int a1, int a2)
{
    int kharejghesmat, baghimande;
    kharejghesmat = array[a1] / array[a2];
    baghimande = array[a1] % array[a2];
    array[a1] = kharejghesmat;
    array[a2] = baghimande;

    ParityFlag(array[a1]);
    ZeroFlag(array[a1]);
    SignFlag(array[a1]);
}

void MULL(int a1, int a2)
{
    int product = array[a1] * array[a2];

    int temp1 = 15;
    int temp2 = 240;
    array[a1] = product & temp2;
    array[a2] = product & temp1;

    array[a1] = array[a1] >> 4;

    ParityFlag(product);
    ZeroFlag(product);
    SignFlag(product);
    OverflowFlagProduct(product, array[a1], array[a2]);
}

int stack[50];
void PUSH(int n)
{
    for (int i = 0; i < 50; i++)
    {
        stack[i + 1] = stack[i];
    }
    stack[0] = sabbat[n];
}

void POP(int n)
{
    sabbat[n] = stack[0];
    for (int i = 0; i < 50; i++)
    {
        stack[i] = stack[i + 1];
    }
}
//(end)functions

//(start)Errors
int errorAndis(int a, int b, int c, char dastoor[])
{
    int checkAndis = 1;
    if (a < 0 || b < 0 || c < 0)
    {
        red();
        printf("Error...you have negative arguement in %s", dastoor);
        reset();
        checkAndis = 0;
    }
    if (a > 31 || b > 31 || c > 31)
    {
        red();
        printf("Error...you have arguement more than 31 in %s(your array can only have 32 elements)", dastoor);
        reset();
        checkAndis = 0;
    }

    return checkAndis;
}

int main(int argc, char *argv[])
{
    int checkAllLine = 0;
    int countJmp = 0;

    int countW = 0; //
    char buffer[1000];

    FILE *voroodi;
    if (argc < 2)
    {
        printf("the file name is: in.txt\n");
        voroodi = fopen("in.txt", "r");
    }
    else
    {
        printf("the file name is: %s\n", argv[1]);
        voroodi = fopen(argv[1], "r");
    }

    while (fscanf(voroodi, "%[^\n]\ns", buffer) != EOF)
    {
        checkAllLine++;
    }

    rewind(voroodi);

    while (fscanf(voroodi, "%[^\n]\ns", buffer) != EOF)
    {
        int a1, a2, a3;
        countW++; //
        for (int i = 0; i < sizeof(buffer); i++)
        {
            buffer[i] = toupper(buffer[i]);
        }

        char dastoor[15] = {'\0'};
        int j;
        for (j = 0; buffer[j] != ' '; j++)
        {
            dastoor[j] = buffer[j];
        }
        // dastoor[j+1] ='\0' ;

        if (strcmp(dastoor, "EXIT") == 0)
        {
            exit(0);
        }

        else if (strcmp(dastoor, "ADD") == 0)
        {
            sscanf(buffer, "ADD S%d, S%d, S%d", &a3, &a1, &a2);
            if (errorAndis(a3, a1, a2, dastoor) == 1)
                ADD(a3, a1, a2);
        }

        else if (strcmp(dastoor, "SUB") == 0)
        {

            sscanf(buffer, "SUB S%d, S%d, S%d", &a3, &a1, &a2);
            if (errorAndis(a3, a1, a2, dastoor) == 1)
                SUB(a3, a1, a2);
        }

        else if (strcmp(dastoor, "AND") == 0)
        {

            sscanf(buffer, "AND S%d, S%d, S%d", &a3, &a1, &a2);
            if (errorAndis(a3, a1, a2, dastoor) == 1)
                AND(a3, a1, a2);
        }

        else if (strcmp(dastoor, "XOR") == 0)
        {

            sscanf(buffer, "XOR S%d, S%d, S%d", &a3, &a1, &a2);
            if (errorAndis(a3, a1, a2, dastoor) == 1)
                XOR(a3, a1, a2);
        }

        else if (strcmp(dastoor, "OR") == 0)
        {

            sscanf(buffer, "OR S%d, S%d, S%d", &a3, &a1, &a2);
            if (errorAndis(a3, a1, a2, dastoor) == 1)
                OR(a3, a1, a2);
        }

        else if (strcmp(dastoor, "ADDI") == 0)
        {

            sscanf(buffer, "ADDI S%d, S%d, %d", &a3, &a1, &a2);
            if (errorAndis(a3, a1, 0, dastoor) == 1)
                ADDI(a3, a1, a2);
        }

        else if (strcmp(dastoor, "SUBI") == 0)
        {

            sscanf(buffer, "SUBI S%d, S%d, %d", &a3, &a1, &a2);
            if (errorAndis(a3, a1, 0, dastoor) == 1)
                SUBI(a3, a1, a2);
        }

        else if (strcmp(dastoor, "ANDI") == 0)
        {

            sscanf(buffer, "ANDI S%d, S%d, %d", &a3, &a1, &a2);
            if (errorAndis(a3, a1, 0, dastoor) == 1)
                ANDI(a3, a1, a2);
        }

        else if (strcmp(dastoor, "XORI") == 0)
        {

            sscanf(buffer, "XORI S%d, S%d, %d", &a3, &a1, &a2);
            if (errorAndis(a3, a1, 0, dastoor) == 1)
                XORI(a3, a1, a2);
        }

        else if (strcmp(dastoor, "ORI") == 0)
        {

            sscanf(buffer, "ORI S%d, S%d, %d", &a3, &a1, &a2);
            if (errorAndis(a3, a1, 0, dastoor) == 1)
                ORI(a3, a1, a2);
        }

        else if (strcmp(dastoor, "MOV") == 0)
        {

            if (buffer[8] == 'S' || buffer[9] == 'S')
            {
                sscanf(buffer, "MOV S%d, S%d", &a1, &a2);
                if (errorAndis(0, a1, a2, dastoor) == 1)
                    MOV(a1, array[a2]);
            }
            else
            {

                sscanf(buffer, "MOV S%d, %d", &a1, &a2);
                if (errorAndis(0, a1, 0, dastoor) == 1)
                    MOV(a1, a2);
            }
        }

        else if (strcmp(dastoor, "SWP") == 0)
        {

            sscanf(buffer, "SWP S%d, S%d", &a1, &a2);
            if (errorAndis(0, a1, a2, dastoor) == 1)
                SWP(a1, a2);
        }

        else if (strcmp(dastoor, "DUMP_REGS") == 0)
        {
            DUMP_REGS();
        }

        else if (strcmp(dastoor, "DUMP_REGS_F") == 0)
        {
            DUMP_REGS_F();
        }

        else if (strcmp(dastoor, "INPUT") == 0)
        {
            INPUT();
        }

        else if (strcmp(dastoor, "OUTPUT") == 0)
        {
            OUTPUT();
        }

        else if (strcmp(dastoor, "JMP") == 0)
        {
            countJmp++;
            if (countJmp > 5)
            {
                yellow();
                printf("you had a loop because of jump command so we ended this chookh after a few times!");
                reset();
                fscanf(voroodi, "%[^\n]\n", buffer);
            }
            else
            {
                int countL = 1, countCH = 0;

                sscanf(buffer, "JMP %d", &a1);
               
                if(a1<=0)
                {
                    red();
                    printf("Error...your lines start from 1 !");
                    reset();
                }

                else if(a1>checkAllLine)
                {
                    red();
                    printf("Error...you only have %d lines!",checkAllLine);
                    reset();
                }

                else
                {
                    rewind(voroodi);
                    while (countL != a1)
                    {
                        countCH++;
                        if (fgetc(voroodi) == '\n')
                            countL++;
                    }
                    fseek(voroodi, countCH + 1, SEEK_SET);
                    fscanf(voroodi, "%[^\n]\n", buffer);

                    for (j = 0; buffer[j] != ' '; j++)
                    {
                        dastoor[j] = buffer[j];
                    }
                    dastoor[j] = '\0';

                    // if(imm>countW)
                    // {

                    // }
                }
                
            }
        }

        else if (strcmp(dastoor, "SKIE") == 0)
        {

            sscanf(buffer, "SKIE S%d, S%d", &a1, &a2);
            if (errorAndis(0, a1, a2, dastoor) == 1)
            {
                if (array[a1] == array[a2])
                {
                    countW++; //
                    fscanf(voroodi, "%[^\n]\n", buffer);

                    //     for(j=0;buffer[j] !=' ';j++)
                    //     {
                    //         dastoor[j]=buffer[j];
                    //     }
                    //    // dastoor[j]='\0';
                }
            }
        }

        else if (strcmp(dastoor, "MULL") == 0)
        {

            sscanf(buffer, "MULL S%d, S%d", &a1, &a2);
            if (errorAndis(0, a1, a2, dastoor) == 1)
                MULL(a1, a2);
        }

        else if (strcmp(dastoor, "DIV") == 0)
        {

            sscanf(buffer, "DIV S%d, S%d", &a1, &a2);
            if (errorAndis(0, a1, a2, dastoor) == 1)
                DIV(a1, a2);
        }

        else if (strcmp(dastoor, "POP") == 0)
        {

            sscanf(buffer, "POP S%d", &a1);
            if (errorAndis(0, a1, 0, dastoor) == 1)
                POP(a1);
        }

        else if (strcmp(dastoor, "PUSH") == 0)
        {

            sscanf(buffer, "PUSH S%d", &a1);
            if (errorAndis(0, a1, 0, dastoor) == 1)
                PUSH(a1);
        }

        else
        {
            red();
            printf("line %d:wrong input,error in command.\n", countW);
            reset();
        }
    }

    fclose(voroodi);

    return (0);
}