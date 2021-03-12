#include "singlePlayerXsAndOs.h"  
void referrencegrid() 
{
    char A[10] = "123456789";
    int i, j, option = 1;
    for(i = 0; i < 3; i++)
    {
        for(j = 0; j < 3; j++)
        {
            if(A[3 * i + j] == 0)
            {
                printf("  ");
            }
            else
            {
                printf("%c ", A[3 * i + j]); 
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

int main()
{
    START:
    system("clear");
    printf("\nXs AND Os - SINGLEPLAYER\n(Enter x anytime to exit)\n\n");
    referrencegrid();
    printf("\nNote the position numbers, and use them to fill the position you want.\n\n");
    int h, i;
    char option;
    option = 0;
    for(i = 0; i < 9; i++)
    {
        D[i] = 0; 
    }
    printf("Enter 1 to play first\n"); 
    printf("Enter anything else to play second\n");  
    fseek(stdin, 0, 0);
    switch(getchar())
    {
        case 'x':
        printf("\nGAME ENDED.\n\n");
        return 0;

        case '1':
        h = 1;
        C[0] = 'X';
        C[1] = 'O';
        break;

        default:
        h = 0;
        C[0] = 'O';
        C[1] = 'X';
    }

        printf("\nYou are %c.\n", C[1]);

    //THE GAME BEGINS
    for(i = h; i < 10 + h; i++)
    {
        int x;
        if(i % 2 && i < 9 + h)
        {
            x = input();
            if(x == -1)
                return 0;
        }
        else
            x = move();
        switch(x)
        {
            case 1:
            printf("____________________________________\n____________________________________\n\nYou win!\n\n");
            printf("\t\t^ ^\n\t\t O\n\n");
            grid();
            printf("\nWant to play again? If yes, press enter... ");
            fseek(stdin, 0, 0);
            if(getchar() != 'x')
                goto START;
            printf("\n\n");
            return 0;

            case 2:
            printf("____________________________________\n____________________________________\n\nComupter wins!\n\n");
            printf("\t\to <\n\t\t U\n\n");
            grid();
            printf("\nWant to play again? If yes, enter anything except x... ");
            fseek(stdin, 0, 0);
            if(getchar() != 'x')
            {
                fclose(fp);
                goto START;
            }
            printf("\n\n");
            return 0;

            case 4:
            printf("____________________________________\n____________________________________\n\nDraw\n\n");
            printf("\t\to o\n\t\t -\n\n");
            grid();
            printf("\nWant to play again? If yes, enter anything except x... ");
            fseek(stdin, 0, 0);
            if(getchar() != 'x')
            {
                fclose(fp);
                goto START;
            }
            printf("\n\n");
            return 0;
        }
        printf("\n");
    }
    printf("____________________________________\n____________________________________\n\nDraw\n\n");
    printf("\t\to o\n\t\t -\n\n");
    grid();
    printf("\nWant to play again? If yes, enter anything except x... ");
    fseek(stdin, 0, 0);
    if(getchar() != 'x')
    {
        fclose(fp);
        goto START;
    }
    printf("\n\n");
    return 0;
}