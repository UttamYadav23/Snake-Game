# Snake-Game
In this code we use gotoxy function this function 
help to move coursor any where we whant in the console .
  void gotoxy(int r,int c)  
    {
        COORD coord;
        coord.X=c;
        coord.Y=r;
        SetConsoleCursorPosition(GetStHandle(STD_OUTPUT_HANDLE),coord);
    }

r = row (uper aur niche position)
c = coloumn (life-right position)
COORD = <windows.h> k buil in function h ye ye coursor ke position store karta h ye 
coord.X=c; Coursor left ya right kaha hoga ,coloum nnumber
coord.Y=r; Coursor uper ya neeche kaha hoga , row nnumber
GetStHandle(STD_OUTPUT_HANDLE)
    Console Screen ka handle deta hai
SetConsoleCursorPosition
    Coursr ko exact (row, coloum ) position par move kar deta hai 

*********************************************************************************************
We hidde the coursor fron the screen for better look so we use <window.h>
built in function which store all coursor settings 
void hideCursor()
{
    CONSOLE_CURSOR_INFO cursor;
    cursor.dwSize = 1;
    cursor.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}

void hideCursor() function name 
CONSOLE_CURSOR_INFO is a windows API structure h jo coursor ke setting ko store karta hai
cursore is a variable which store this API
cursor.dwSize = 1; assign the size of Coursor
cursor.bVisible = FALSE;  Assign the visibelity of the coursor 
SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor); command for handeking the coursor and size of the coursor

***********************************************************************************
fruit ko box k ander kaise appear kare iske liye hum use karange 
wall heigh 20
print 0 to 19
snake move 1 to 18
we need fruit range 1 to 17 kyu ke computer reminder kabhe bhe divisor she bada nahi ho sakta h 

fruitx = rand() %(height-2)+1;
 example :-
 randon number genrate 20  height =20 
 rand(20) % (20-2)+1  
 rand(20) % 18+1     20%18 =2 
 2 + 1 now random number is 3 
 fruitx position is 3
