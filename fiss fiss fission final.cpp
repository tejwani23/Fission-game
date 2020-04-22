
#include <stdio.h>
#include <conio.h>
#include "conio.h"
#include <stdlib.h>
//========================================================================
#ifndef inc
#define inc
int prev[12][12];
struct stack1{
int top;
int *a[100];
}m1;


void prin(int (*b)[12]);
void init(int (*b)[12]);
void copyprev(int (*b)[12]);
int diff(int (*b)[12]);
void blaststar(int (*b)[12],int i,int j);
int check(int (*b)[12]);
void starvic();
void cirvic();
void blastcircle(int (*b)[12],int i,int j);
void intro();//checks for end of game, return 5 if game is over; else 0;
#endif // inc

///////////////////////////////////////////////////////////////////////////////////////////
int* pop(){
    int *arr=m1.a[m1.top];
    m1.top--;
    return arr;
}
void push(int * arr){
    m1.top++;
    m1.a[m1.top]=arr;
}
void undo(int (*b)[12]){
    if(m1.top==-1){
        printf("Undo list are empty please make a move\n");
        return;
    }
    int *arr=pop();
    int i=0,j=0;
    for(i=0;i<12;i++){
        for(j=0;j<12;j++){
            b[i][j]=*(arr + i*12 + j);
        }
     }
     printf("Undo Done");
     prin(b);
    return;
}

void stackentry(int (*b)[12]){
     int *arr = (int *)malloc(12 * 12 * sizeof(int));
     int i=0,j=0;
     for(i=0;i<12;i++){
        for(j=0;j<12;j++){
            *(arr + i*12 + j)=b[i][j];
        }
     }
     push(arr);
}
//////////////////////////////////////////////////////////
//MAIN
//----------------------------------------------------------------------------------------------------

  int main()
  { m1.top=-1;
      int b[12][12];  //Array Creation
      int ch=0;
       init(b);    //Array Injtialization
       int turn=0;
       int choice;
       intro();
       printf("Press 1 to play the multiplayer game or any other button to quit.\n");
       scanf("%d", &choice);
       if(choice != 1)
        exit(1);
       else
        system("cls");
       prin(b);
       int chances=0;
       int a, c;
            initial:
                stackentry(b);
            printf("Player 1.\n");
            printf("Please enter your choice for i and j starting from 1 to 10.\n");
            scanf("%d %d", &a, &c);
            while(a>10 || a<1 || c >10 || c<1)
            {   printf("Invalid values. Retry. \n");
                goto initial;

            }
            b[a][c]=1;
            system("cls");
            prin(b);
            int y=0;
            printf("press 0 to undo or any other key to continue");
            scanf("%d",&y);
            if(y==0){
                printf("how many moves you want to undo");
                int t,q;
                scanf("%d",&t);
                for(q=0;q<t;q++){
                undo(b);}
                goto initial;
            }
            stackentry(b);
            do{
            printf("Player 2.\n");
            printf("Please enter your choice for i and j starting from 1 to 10.\n");
            scanf("%d %d", &a, &c);
            if(a>10 || a<1 || c >10 || c<1)
            {
                printf("Invalid values. Retry. \n");
                continue;
            }
            if(b[a][c]==0){
            b[a][c]=5;
            system("cls");
            prin(b);
            printf("press 0 to undo or any other key to continue");
            scanf("%d",&y);
            if(y==0){
                printf("how many moves you want to undo");
                int t,q;
                scanf("%d",&t);
                for(q=0;q<t;q++){
                undo(b);}
                continue;
            }
            break;
            }
            else{
                printf("Invalid values. You cannot select an enemy block directly. Retry. \n");
                continue;
            }

            }while(1);
         //Turn Checker
        do{
                stackentry(b);
            printf("Player %d.\n", (turn%2+1));
            printf("Please enter your choice for i and j starting from 1 to 10.\n");
            scanf("%d %d", &a, &c);
            if(a>10 || a<1 || c >10 || c<1)
            {
                printf("Invalid values. Retry. \n");
                continue;
            }
            if(turn%2 ==0 && (b[a][c] >=5 && b[a][c] <=8))
            {
                printf("Invalid input. You cannot select an enemy block directly. Retry. \n");
                continue;
            }
            if(turn%2 ==1 && (b[a][c] >=1 && b[a][c] <=4))
            {
                printf("Invalid input. You cannot select an enemy block directly. Retry. \n");
                continue;
            }
            if(turn %2 ==1 && b[a][c]==0)
            {
                b[a][c]=5;
            }
            else{
                    b[a][c]= b[a][c]+1;
            }
           // ---------------------------------------------------------------------------------------------
          //star
                 chances= chances +1;
                 copyprev(b);
                 if(turn%2 == 0)
                 {
                     copyprev(b);
                 for(int i=1;i<=10;i++)
                 {
                     for(int j=1;j<=10;j++)
                     {
                         if(((i ==1  && j==1)|| (i ==1  && j==10)|| (i ==10  && j==1)|| (i ==10  && j==10)) && b[i][j]==2)
                            {blaststar(b, i, j);
                            i=1;
                            j=0;
                            }
                         else if((((i==1 || i==10)&&(j>1 && j<10)) || ((j==1 || j==10)&&(i>1 && i<10))) && b[i][j]==3)
                            {blaststar(b, i, j);
                            i=1;
                            j=0;
                            }
                         else if(((i>1 && i<10))&& ((j>1)&&(j<10)) && b[i][j]==4)
                            {blaststar(b, i, j);
                            i=1;
                            j=0;
                            }
                         //   else
                     }
                 }
                // prin(b);
                 printf("press 0 to undo or any other key to continue");
            scanf("%d",&y);
         if(y==0){
                printf("how many moves you want to undo");
                int t,q;
                scanf("%d",&t);
                for(q=0;q<t;q++){
                undo(b);}

                continue;
            }
            system("cls");
            prin(b);
                 ++turn;

             }

                //===========================================================================================
           //circle
             else
             {
                 copyprev(b);
                 for(int i=1;i<=10;i++)
                 {
                     for(int j=1;j<=10;j++)
                     {
                         if(((i ==1  && j==1)|| (i ==1  && j==10)|| (i ==10  && j==1)|| (i ==10  && j==10)) && b[i][j]==6)
                            {blastcircle(b, i, j);
                            i=1;
                            j=0;
                            }
                         else if((((i==1 || i==10)&&(j>1 && j<10)) || ((j==1 || j==10)&&(i>1 && i<10))) && b[i][j]==7)
                            {blastcircle(b, i, j);
                            i=1;
                            j=0;
                            }
                         else if(((i>1 && i<10))&& ((j>1)&&(j<10)) && b[i][j]==8)
                            {blastcircle(b, i, j);
                            i=1;
                            j=0;
                            }
                         //   else
                     }
                 }
                 //prin(b);
                 printf("press 0 to undo or any other key to continue");
            scanf("%d",&y);
                 if(y==0){
                printf("how many moves you want to undo");
                int t,q;
                scanf("%d",&t);
                for(q=0;q<t;q++){
                undo(b);}
                continue;
            }
            system("cls");
            prin(b);
                 ++turn;
             }
                //===========================================================================================
            ch= check(b);

            system("cls");
            prin(b);
        }while((ch != 4 &&  ch != 6));
        if(ch==4)
            cirvic();
        else starvic();
        getch();
    return 0;
  }

//----------------------------------------------------------------------------

void init(int (*b)[12])
{
    for(int i=0;i<12;i++)
    {
        for(int j=0;j<12;j++)
            b[i][j] = 0;
    }
}
//DISPLAY...
//----------------------------------------------------------------------
void prin(int (*b)[12])
{
    int i=0,j=0,k=0;
for(i=1; i<=10;i++)
    printf("  --");
printf("\n");
for(i=1; i<= 10;i++)
{ printf("| ");
    for(j=1;j<=10;j++){
    if(b[i][j]!=0)
    { if(b[i][j]>=5 && b[i][j]<=8)
        printf("%d@ |",b[i][j]%4);
        else if(b[i][j]>=1 && b[i][j]<=4)
            printf("%d* |",b[i][j]);
    }

    else
        printf("   |");
    }

    printf("\n");
    for(k=0; k<=9;k++)
    printf("  --");
    printf("\n");
}
}


//BlAST
//---------------------------------------------------------------------------------
void blaststar(int (*b)[12],int i,int j)
{
    b[i][j]=0;
    ///////////
    if(b[i-1][j]<=4 || b[i-1][j]==7)
       {b[i-1][j]=(b[i-1][j]+1);}
    else
        {b[i-1][j]=(b[i-1][j]+1)%4;}
        ///////////////////
    if(b[i+1][j]<=4 || b[i+1][j]==7)
       {b[i+1][j]=(b[i+1][j]+1);}
    else
        {b[i+1][j]=(b[i+1][j]+1)%4;}
        /////////////////
    if(b[i][j-1]<=4 || b[i][j-1]==7)
       {b[i][j-1]=(b[i][j-1]+1);}
    else
        {b[i][j-1]=(b[i][j-1]+1)%4;}
        /////////////////////////
    if(b[i][j+1]<=4 || b[i][j+1]==7)
       {b[i][j+1]=(b[i][j+1]+1);}
    else
        {b[i][j+1]=(b[i][j+1]+1)%4;}

}

//--------------------------------------------------------------------------
void blastcircle(int (*b)[12],int i,int j){
    b[i][j]=0;

    if(b[i-1][j]>=5 && b[i-1][j]<=8)
        b[i-1][j]++;
    else
        b[i-1][j]= b[i-1][j] + 5;

    if(b[i+1][j]>=5 && b[i+1][j]<=8)
        b[i+1][j]++;
    else
        b[i+1][j]= b[i+1][j] + 5;

    if(b[i][j-1]>=5 && b[i][j-1]<=8)
        b[i][j-1]++;
    else
        b[i][j-1]= b[i][j-1] + 5;

    if(b[i][j+1]>=5 && b[i][j+1]<=8)
        b[i][j+1]++;
    else
        b[i][j+1]= b[i][j+1] + 5;
}


//check
//-----------------------------------------------------------------------------
int check(int (*b)[12])
{
    int c1=0, c2=0;
    for(int i=1;i<=10;i++)
    {
        for(int j=1;j<=10;j++)
        {
            if(b[i][j]>=1 && b[i][j]<=4 )
                c1++;
            if(b[i][j]>=5 && b[i][j]<=8 )
                c2++;
        }
    }
        if(c1==0 && c2!=0)
            return 4;
        else if(c2==0 && c1!=0)
            return 6;
        else
             return 0;
}
//--------------------------------------------------------------------------------------
void copyprev(int (*b)[12]){
for(int i=0;i<12;i++)
{
    for(int j=0;j<12;j++)
    {
        prev[i][j]= b[i][j];

    }
}
}

//--------------------------------------------------------------------------------------
int diff(int (*b)[12]){
for(int i=0;i<12;i++)
{
    for(int j=0;j<12;j++)
    {
        if(prev[i][j]!= b[i][j])
            return 1;
    }
}
return 0;
}

void intro()
{
    printf("\n");
    printf(" ________  _____   ______    ______   \n");
    printf("|_   __  ||_   _|.' ____ \\ .' ____ \\  \n");
    printf("  | |_ \\_|  | |  | (___ \\_|| (___ \\_| \n");
    printf("  |  _|     | |   _.____`.  _.____`.  \n");
    printf(" _| |_     _| |_ | \\____) || \\____) | \n");
    printf("|_____|   |_____| \\______.' \\______.' \n");
         printf("\n");
          printf(" ________  _____   ______    ______   \n");
    printf("|_   __  ||_   _|.' ____ \\ .' ____ \\  \n");
    printf("  | |_ \\_|  | |  | (___ \\_|| (___ \\_| \n");
    printf("  |  _|     | |   _.____`.  _.____`.  \n");
    printf(" _| |_     _| |_ | \\____) || \\____) | \n");
    printf("|_____|   |_____| \\______.' \\______.' \n");
         printf("\n");

    printf(" ________  _____   ______    ______   _____   ___   ____  _____  \n");
    printf("|_   __  ||_   _|.' ____ \\ .' ____ \\ |_   _|.'   `.|_   \|_   _| \n");
    printf("  | |_ \\_|  | |  | (___ \\_|| (___ \\_|  | | /  .-.  \\ |   \\ | |   \n");
    printf("  |  _|     | |   _.____`.  _.____`.   | | | |   | | | |\\ \\| |   \n");
    printf(" _| |_     _| |_ | \\____) || \\____) | _| |_\\  `-'  /_| |_\\   |_  \n");
    printf("|_____|   |_____| \\______.' \\______.'|_____|`.___.'|_____|\\____| \n");

    printf("\n");

}

void cirvic()
{
    system("cls");
    printf("\n");
    printf("   __  __ ___   __  __   ___   \n");
    printf(" ,'_/ / // o |,'_/ / /  / _/   \n");
    printf("/ /_ / //  ,'/ /_ / /_ / _/    \n");
    printf("|__//_//_/`_\\|__//___//___/    \n");
    printf("\n");
    printf("  _   __ __ _  __  ___         \n");
    printf(" ///7/ // // |/ /,' _/         \n");
    printf("| V V // // || /_\ `.          \n");
    printf("|_n_,'/_//_/|_//___,'          \n");
    printf("\n");

}



void starvic()
{
    system("cls");
    printf("\n");
    printf("    ___ _____  _   ___ \n");
    printf("  ,' _//_  _/.' \ / o |\n");
    printf(" _\\ `.  / / / o //  ,' \n");
    printf("/___,' /_/ /_n_//_/`_\\ \n");
    printf("\n");
    printf("  _   __ __ _  __  ___         \n");
    printf(" ///7/ // // |/ /,' _/         \n");
    printf("| V V // // || /_\ `.          \n");
    printf("|_n_,'/_//_/|_//___,'          \n");
    printf("\n");


    printf("\n");

}

