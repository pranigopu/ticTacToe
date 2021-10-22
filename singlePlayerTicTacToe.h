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
*/

//0. GLOBAL VARIABLES
char D[10]; //The display; to be changed for most of the program
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
                printf("  ");
            else
                printf("%c ", D[3 * i + j]);
            if(j < 2)
                printf("| ");
        }
        printf("\n"); 
        if(i < 2)
            printf("-");
        for(j = 0; j < 2; j++)
            if(i < 2)
            {
                printf("-+--");
            }
        printf("\n");
    }
}

//2. USER INPUT 
int input()
{
    char IN[2];
    int a, b;
    
    printf("____________________________________\n\nYour move...\n\n");
    grid();
    while(1)
    {
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
                D[a] = C[1]; 
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
        case 1: //Checks if player won
        for(r = j; r < u; r += k)
        {
            if(r == a || r == b)
                continue;
            if(D[r] == D[a] && D[a] == C[1])
                return 1;
        }
        break;

        case 2: //Checks if computer can win
        for(r = j; r < u; r += k)
        {
            if(r == a || r == b)
                continue;
            if(D[r] == 0 && D[a] == C[0])
            {
                D[r] = C[0];
                return 2;
            }
        }
        break;
        
        case 3: //Checks if player can win
        for(r = j; r < u; r += k)
        {
            if(r == a || r == b)
                continue;
            if(D[r] == 0)
            {
                if(D[a] == C[1])
                {
                    D[r] = C[0];
                    return 3;
                }
            }
        }
        break;
    } 
    return 4; //Either the grid is too empty, or it is a draw    
}

//4. SIMPLY FILL AN EMPTY POSITION
int justfill(int a, int b, int option)
{
    int r, s, u;
    if(option == 4) //Checks if computer can line two of its marks in one line
    {
        int n;
        int pa = P[a];
        int pb = P[b];
        //For the function to cross the next condition, one position should be non-null, while the other should be null
        if(!((D[a] == 0 || D[b] == 0) && (D[a] != D[b])))
            return -1; 
        if(D[a] == C[1] || D[b] == C[1])
            return -1;
        if(D[a] != 0)
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
    else if(option == 5) //If the grid is too empty and the computer must just fill any blank
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
    for(k = 1; k < 4; k++)
    for(i = 0; i < 9; i++)
    for(j = 0; j < 9; j++)
    {
        if(j == i)
            continue;
        a = checkfill(i, j, k);
        if(a > 0 && a < 4) //Game over OR move performed by computer
            return a;
        if(a == 0)  //Checks if the two positions just checked were both empty
            b++;    //If yes, b is incremented. 
                    //This indicates if the next loop should be run or not, in case this loop ends without returning any value
    }
    if(b > 0)
    {
        for(k = 4; k < 6; k++) //Option continuity! It was not logically necessary for k to start at 4, however...
        for(i = 0; i < 9; i++)
        for(j = 0; j < 9; j++)
        {
            if(j == i)
                continue;
            if(justfill(i, j, k) == 0)
                return 0;
        }
    }
    return 4;
}
