//THE GAME OF TIC TAC TOE

#include <stdio.h>
#include <stdlib.h>
#include "myArrayFunctions.h"

//FUNCTION TO MAKE A GRID FOR THE X's AND O's
void grid(char B[])
{
    int i, j;
    for(i = 0; i < 3; i++)
    {
        for(j = 0; j < 3; j++)
        {
            if(B[3 * i + j] == 0)
            printf("  ");
            else
            printf("%c ", B[3 * i + j]);
            if(j < 2)
            printf("| ");
        }
        printf("\n");
        if(i < 2)
        printf("-");
        for(j = 0; j < 2; j++)
        {
            if(i < 2)
            printf("-+--");
        }
        printf("\n");
    }
}

//FUNCTION TO DETERMINE THE OUTCOME OF THE GAME, BE IT A DRAW OR A WIN FOR ONE PLAYER
int winner(int i, int A[])
{
    int sum = 0;
    int a, b, c;
    if(i % 2 == 1)
    {
        for(a = 0; a < 4; a++)
        for(b = a + 1; b < 4; b++)
        for(c = b + 1; c < 4; c++)
        {
            sum = - (A[a] + A[b] + A[c]);
            //printf("\nA[%d] + A[%d] + A[%d] = %d + %d + %d = %d\n", a, b, c, A[a], A[b], A[c], sum);
            switch(sum)
            {
                case 111: case 222: case 333: 
                case 6: case 60: case 600:
                case 123: case 321: 
                return 2;
            }
        }
    }
    else
    {
        for(a = 8; a > 3; a--)
        for(b = a - 1; b > 3; b--) 
        for(c = b - 1; c > 3; c--)
        {
            sum = A[a] + A[b] + A[c];
            //printf("\nA[%d] + A[%d] + A[%d] = %d + %d + %d = %d\n", a, b, c, A[a], A[b], A[c], sum);
            switch(sum)
            {
                case 111: case 222: case 333: 
                case 6: case 60: case 600:
                case 123: case 321: 
                return 1;
            }
        }
    }
    return 0;    
}

//BODY
int main()
{
    int LABEL[9] = {1, 10, 100, 2, 20, 200, 3, 30, 300};
    char MOVE[3];
    do
    {
        int ALLMOVES[9];
        char DISPLAY[9] = "123456789";
        system("clear");
        printf("\nNOUGHTS AND CROSSES - MULTIPLAYER\n(Enter x anytime to exit)\n");
        printf("\n\nNote these positions and their numbers...\n\n");
        grid(DISPLAY);
        printf("Refer to these positions through their numbers when you play.");
        
        printf("\n\nPress enter to continue... ");
        fseek(stdin, 0, 0);
        MOVE[0] = getchar();
        if(MOVE[0] == 'x') 
        {
            printf("\nGAME ENDED.\n\n");
            return 0;
        }

        int i, j;
        for(i = 0; i < 9; i++)
        {
            ALLMOVES[i] = 0;
            DISPLAY[i] = 0;
        }
        int move;
        
        printf("\n___________________________\n");
        for(i = 0; i < 9; i++)
        {
            //system("clear");
            printf("\nPlayer %d, your move...\n\n", (i % 2) + 1);
            grid(DISPLAY);
            do
            {
                printf("Go to position ");
                fseek(stdin, 0, 0);
                scanf("%s", MOVE);
                if(MOVE[1])
                {
                    printf("\nHey! This is not a position number.\n\n");
                    j = 1;
                }
                else if(MOVE[0] > 48 && MOVE[0] < 58)
                {
                    move = MOVE[0] - 48;
                    j = linSearch(ALLMOVES, 9, LABEL[move - 1]);
                    j += linSearch(ALLMOVES, 9, LABEL[move - 1] * (-1));
                    if(j > -1)
                    printf("\nHey! Position %d has been filled.\n\n", move); 
                    else
                    j = 0;              
                }
                else if(MOVE[0] == 'x')
                {
                    printf("\nGAME ENDED.\n\n");
                    return 0;
                }
                else
                {
                    printf("\nHey! This is not a position number.\n\n");
                    j = 1;
                }
            } while(j);

            if(i % 2 == 1)
            {
                DISPLAY[move - 1] = 'X';
                ALLMOVES[4] = LABEL[move - 1] * (-1);
            }
            else
            {
                DISPLAY[move - 1] = 'O';
                ALLMOVES[4] = LABEL[move - 1];
            }
            
            selectSort(ALLMOVES, 9, 1);
            printf("___________________________\n");
            if(i > 3)
            {
                j = winner(i, ALLMOVES);
                if(j == 0)
                continue; 
                if(j == 1)
                {
                    //system("clear");
                    printf("___________________________\n");
                    printf("\nGAME OVER! Player 1 wins!\n\n");
                    break; 
                }
                else if(j == 2)
                {
                    //system("clear");
                    printf("___________________________\n");
                    printf("\nGAME OVER! Player 2 wins!\n\n"); 
                    break; 
                } 
            }
        }
        if(i == 9 && j == 0)
        {
            //system("clear");
            printf("___________________________\n");
            printf("\nGAME OVER! It is a draw.\n\n");
        }
        grid(DISPLAY);
        printf("\nPress enter to continue... ");
        fseek(stdin, 0, 0);
        MOVE[0] = getchar();
    } while(MOVE[0] != 'x');
    printf("\nGAME ENDED.\n\n");
    return 0;
}
