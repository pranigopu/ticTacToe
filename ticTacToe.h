#include <stdio.h>
#include <stdlib.h>

//Table of contents 
/*
0. GLOBAL VARIABLES
1. MAKING THE GRID
2. USER INPUT 
3. TO CHECK THE GRID FOR OPPORTUNITIES AND THREATS AND FILL ACCORDINGLY
4. SIMPLY FILL AN EMPTY POSITION
5. THE INTEGRATED FUNCTION FOR THE COMPUTER'S MOVE
6. NON-ESSENTIAL FUNCTIONS
*/

//0. GLOBAL VARIABLES
int twoPlayer = 0;
char D[10]; //To be changed for most of the program
int P[9] = {0, 1, 2, 30, 31, 32, 60, 61, 62}; //Never changes ever
char C[3] = "OX"; //Never changes once determined
FILE *fp;

//1. MAKING THE GRID
void grid() 
{
    int i, j, option = 1;
    for(i = 0; i < 3; i++)
    {
        for(j = 0; j < 3; j++)
        {
            if(D[3 * i + j] == 0)
            {
                printf("  ");
            }
            else
            {
                printf("%c ", D[3 * i + j]);
            }
            if(j < 2)
            {
                printf("| ");
            }
        }
        printf("\n"); 
        if(i < 2)
        {
            printf("-");
        }
        for(j = 0; j < 2; j++)
        {
            if(i < 2)
            {
                printf("-+--");
            }
        }
        printf("\n");
    }
}

//2. USER INPUT 
int input(int player)
{
    char IN[2];
    int a, b;
    
    printf("____________________________________\n\nYour move...\n\n");
    grid();
    while(1)
    {
        if(twoPlayer)
            printf("Player %d's move\n", - (player - 2));
        printf("Go to position ");
        fseek(stdin, 0, 0);
        scanf("%s", IN);
        if(IN[1])
            printf("\nHey! This is not a position number.\n\n");
        else if(IN[0] > 48 && IN[0] < 58)
        {
            a = IN[0]- 49; //i.e. INPUT[0]- 48 - 1;
            if(D[a] == 0)
            {
                D[a] = C[player]; 
                break;
            }
            else
                printf("\nHey! Position %d has been filled.\n\n", a + 1);         
        }
        else if(IN[0] == 'x' && IN[1] == 0)
        {
            printf("\nGAME ENDED.\n\n");
            return -1;
        }
        else
            printf("\nHey! This is not a position number.\n\n");
    }
    return 0;
}

//3. TO CHECK THE GRID FOR OPPORTUNITIES AND THREATS AND FILL ACCORDINGLY
int checkfill(int a, int b, int option)
{
    int pa = P[a];
    int pb = P[b];
    if(D[a] != D[b])
        return 5;
    if(!D[a] || !D[b])
        return 0; 
    int j, k;
    int r, s, u;
    if(pa / 10 == pb / 10) //Row same
    {
        j = pa / 10;
        k = 1;
        u = j + 3;
    }
    else if(pa % 10 == pb % 10) //Column same
    {
        j = pa % 10;
        k = 3;
        u = j + 7;
    }
    else if((pa / 10 + pa % 10) % 2 + (pb / 10 + pb % 10) % 2 == 0) //Diagonal same
    {
        if(pa == 0 || pb == 0 || pa == 62 || pb == 62)
        {
            j = 0;
            k = 4;
            u = 10;
        }
        else if(pa == 2 || pb == 2 || pa == 60 || pb == 60)
        {
            j = 2;
            k = 2;
            u = 8;
        }
    }
    else
        return 6;
    switch(option)
    {
        case 1: 
        case 2:
        if(twoPlayer)
            option--;
        for(r = j; r < u; r += k)
        {
            if(r == a || r == b)
                continue;
            if(D[r] == D[a] && D[a] == C[option])
                return option + 1;
        }
        break;

        case 3:
        for(r = j; r < u; r += k)
        {
            if(r == a || r == b)
                continue;
            else if(D[r] == 0)
            {
                if(D[a] == C[0])
                {
                    D[r] = C[0];
                    return 3;
                }
            }
        }
        break;
        
        case 4:
        for(r = j; r < u; r += k)
        {
            if(r == a || r == b)
                continue;
            else if(D[r] == 0)
            {
                if(D[a] == C[1])
                {
                    D[r] = C[0];
                    return 4;
                }
            }
        }
        break;
    } 
    if(option < 3)
        return 6;
    else
        return 5;      
}

//4. SIMPLY FILL AN EMPTY POSITION
int justfill(int a, int b, int option)
{
    int r, s, u;
    if(option == 5)
    {
        int n;
        int pa = P[a];
        int pb = P[b];
        if(!((D[a] == 0 || D[b] == 0) && (D[a] != D[b])))
            return -1; 
        else if(D[a] == C[1] || D[b] == C[1])
            return -1;
        else if(D[a] != 0)
            n = a;
        else if(D[b] != 0)
            n = b;
        int j, k;
        if(pa / 10 == pb / 10) //Row same
        {
            j = pa / 10;
            k = 1;
            u = j + 3;
        }
        else if(pa % 10 == pb % 10) //Column same
        {
            j = pa % 10;
            k = 3;
            u = j + 7;
        }
        else if((pa / 10 + pa % 10) % 2 + (pb / 10 + pb % 10) % 2 == 0) //Diagonal same
        {
            if(pa == 0 || pb == 0 || pa == 62 || pb == 62)
            {
                j = 0;
                k = 4;
            }
            else if(pa == 2 || pb == 2 || pa == 60 || pb == 60)
            {
                j = 2;
                k = 2;
            }
            u = 2 * k + 1;
        }
        else
            return 6;
        s = 0;
        for(r = j; r < u; r += k)
        {
            if(r == n)
                continue;
            if(D[r] == 0)
            {
                s++;
                pb = r;
            }
        } 
        if(s == 2) 
        {
            D[pb] = C[0];
            s = 0;
        }
        else
            s = -1;
    }
    else if(option == 6)
    {
        int i;
        for(i = 0; i < 9; i++)
        {
            if(D[i] == 0)
            {
                D[i] = C[0];
                s = 0;
                break;
            }
            else 
                s = -1;
        }
        
    }
    return s;
}

//5. THE INTEGRATED FUNCTION FOR THE COMPUTER'S MOVE
int move()
{
    int i, j, k, a = 0, b = 0;
    int last = 5;
    if(twoPlayer)
        last = 3;
    for(k = 1; k < last; k++)
    for(i = 0; i < 9; i++)
    for(j = 0; j < 9; j++)
    {
        if(j == i)
            continue;
        a = checkfill(i, j, k);
        if(a > 0 && a < last)
            return a;
        if(a == 0)
            b++;
    }
    if(b > 0 && !twoPlayer)
    {
        for(k = 5; k < 7; k++)
        for(i = 0; i < 9; i++)
        for(j = 0; j < 9; j++)
        {
            if(j == i)
                continue;
            a = justfill(i, j, k);
            if(a == 0)
                return 0;
        }
    }
    if(!twoPlayer)
        return 5;
    return 0;
}

//6. NON-ESSENTIAL FUNCTIONS
void display()
{
    int i;
    printf("\n");
    for(i = 0; i < 9; i++)
    printf("%c\t", D[i]);
    printf("\n");
}
 
int justcheck()
{
    int i, j, k, a = 0, b = 0;
    for(k = 1; k < 3; k++)
    for(i = 0; i < 9; i++)
    for(j = 0; j < 9; j++)
    {
        if(j == i)
            continue;
        a = checkfill(i, j, k);
        if(a > 0 && a < 3)
            return a;
        if(a == 0)
            return 0;
    }
    return 0;
}
