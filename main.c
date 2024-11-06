#include<stdio.h>
#include <stdlib.h>
#include <windows.h>
#include<string.h>
#define EXTENDED -32
#define enter 13
#define ESC 27
#define TAB 9
#define right 77
#define left 75
#define home 71
#define end 79
#define backspace 8
#define delete 83

void gotoxy( int column, int row )
{
    COORD coord;
    coord.X = column;
    coord.Y = row;
    SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
}
void textattr(int i)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
}
char* lineEditor(int _size,int col,int row,int startKey,int endKey)
{
    char *arr=malloc(_size * sizeof(char));
    int first,curr, last;
    first=curr= last=col;
    char *pfirst, *pcurr, *plast;
    pfirst= pcurr=plast=arr;

    int flag=0;
    char ch;
    gotoxy(col,row);

    do
    {
        gotoxy(curr,row);
        ch=getch();
        switch (ch)
        {

        case EXTENDED:
            ch=getch();
            switch(ch)
            {
            case home:
                pcurr=pfirst ;
                curr=first ;

                break;
            case end:
                pcurr=plast;
                curr=last;
                break;
            case left:
                if(pcurr>pfirst)
                {
                    pcurr-- ;
                    curr-- ;
                }
                break;

            case right:
                if(pcurr<plast)
                {
                    pcurr++ ;
                    curr++ ;
                }
                break;

            case delete:
    if (pcurr < plast) {
        char *temp1 = pcurr;

        while (temp1 < plast) {
            *temp1 = *(temp1 + 1);
            temp1++;
        }

        *(plast - 1) = '\0';
        plast--;
        last--;

        gotoxy(curr, 10);
                system("cls") ;
                gotoxy(first, 10);
        printf("%-30s", arr);
    }
    break;


            }
            break;
        case backspace:
            if (pcurr > pfirst)
            {
                pcurr--;
                curr--;
                char *temp = pcurr;
                while (temp < plast)
                {
                    *temp = *(temp + 1);
                    temp++;
                }
                *(plast - 1) = '\0';
                plast--;
                last--;
                gotoxy(curr, row);
                system("cls") ;
                gotoxy(first, row);

                printf("%-30s", arr);
            }
            break;
        case enter:
        case ESC :
            *plast='\0' ;
            flag=1;
            system("cls") ;

            for(int i=0 ; i<30; i++)
            {
                printf("%c", arr[i]);
            }
            break;

        default:
            if(isprint(ch))
            {
                if(pcurr <pfirst+29)
                {
                    *pcurr=ch;
                    printf("%c", ch);
                    pcurr++;
                    curr++;
                    plast++;
                    last++;
                }
            }
            else
            {
                *pcurr=ch;
                *pcurr++;
                curr++;
            }
            break;
        }
    }
    while(flag==0);
    }

int main()
{
    int _size,col,row;
    printf("Enter size: ");
    scanf("%i",&_size);
    printf("Enter row: ");
    scanf("%i",&row);
    printf("Enter col: ");
    scanf("%i",&col);
    char *result=lineEditor(_size,col,row,65,90);
    system("cls");
    printf("Result is %s",result);

    return 0;
}
