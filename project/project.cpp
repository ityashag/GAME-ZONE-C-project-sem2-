#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>

#include <time.h>

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70
#define MENU_WIDTH 20
#define GAP_SIZE 7
#define PIPE_DIF 45

#define MAXSNAKESIZE 100
#define no 30
using namespace std;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;
// HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
// COORD CursorPosition;

int pipePos[3];
int gapPos[3];
int pipeFlag[3];
string bird1[2] = {"\\\\\\", "<\\\\\\=Q"};
string bird2[2] = {"<////=Q", "////"};
int birdPos = 6;
int score = 0;

int rand_pos()
{
        return 1000+(rand()/4);

 }
void gotoxy(int x, int y)
{
        CursorPosition.X = x;
        CursorPosition.Y = y;
        SetConsoleCursorPosition(console, CursorPosition);
}

void setcursor(bool visible, DWORD size)
{
        if (size == 0)
                size = 20;

        CONSOLE_CURSOR_INFO lpCursor;
        lpCursor.bVisible = visible;
        lpCursor.dwSize = size;
        SetConsoleCursorInfo(console, &lpCursor);
}

void genPipe(int ind)
{
        gapPos[ind] = 3 + rand() % 14;
}
void drawPipe(int ind)
{
        if (pipeFlag[ind] == true)
        {
                for (int i = 0; i < gapPos[ind]; i++)
                {
                        gotoxy(WIN_WIDTH - pipePos[ind], i + 1);
                        cout << "***";
                }
                for (int i = gapPos[ind] + GAP_SIZE; i < SCREEN_HEIGHT - 1; i++)
                {
                        gotoxy(WIN_WIDTH - pipePos[ind], i + 1);
                        cout << "***";
                }
        }
}
void erasePipe(int ind)
{
        if (pipeFlag[ind] == true)
        {
                for (int i = 0; i < gapPos[ind]; i++)
                {
                        gotoxy(WIN_WIDTH - pipePos[ind], i + 1);
                        cout << "   ";
                }
                for (int i = gapPos[ind] + GAP_SIZE; i < SCREEN_HEIGHT - 1; i++)
                {
                        gotoxy(WIN_WIDTH - pipePos[ind], i + 1);
                        cout << "   ";
                }
        }
}

void drawBird(int j)
{
        switch (j)
        {
        case 1:
                for (int i = 0; i < 2; i++)
                {
                        gotoxy(i + 2, i + birdPos);
                        cout << bird1[i];
                }
                break;
        case 2:
                for (int i = 0; i < 2; i++)
                {
                        gotoxy(i + 2, i + birdPos);
                        cout << bird2[i];
                }
                break;
        }
}
void eraseBird()
{
        for (int i = 0; i < 2; i++)
        {
                for (int j = 0; j < 6; j++)
                {
                        gotoxy(j + 2, i + birdPos);
                        cout << " ";
                }
        }
}

int collision()
{
        if (pipePos[0] >= 61)
        {
                if (birdPos < gapPos[0] || birdPos > gapPos[0] + GAP_SIZE)
                {
                        return 1;
                }
        }
        return 0;
}

void gameover()
{
        system("cls");
        cout << endl;
        cout<<"\t\t YOUR SCORE IS : "<<score<<endl;
        cout << "\t\t--------------------------\n";
        cout << "\t\t-------- Game Over -------\n";
        cout << "\t\t--------------------------\n";

}
void updateScore()
{

        gotoxy(WIN_WIDTH + 7, 5);
        cout << "Score: " << score << endl;
}

void instructions()
{

        system("cls");
        cout << "Instructions";
        cout << "\n----------------";
        cout << "\n Press spacebar to make bird fly";
        cout << "\n\nPress any key to go back to menu";
        getch();
}

void play()
{

        birdPos = 6;
        score = 0;
        pipeFlag[0] = 1;
        pipeFlag[1] = 0;
        pipePos[0] = pipePos[1] = 4;

        system("cls");
        genPipe(0);
        updateScore();

        gotoxy(WIN_WIDTH + 5, 2);
        cout << "FLAPPY BIRD";
        gotoxy(WIN_WIDTH + 6, 4);
        cout << "----------";
        gotoxy(WIN_WIDTH + 6, 6);
        cout << "----------";
        gotoxy(WIN_WIDTH + 7, 12);
        cout << "Control ";
        gotoxy(WIN_WIDTH + 7, 13);
        cout << "-------- ";
        gotoxy(WIN_WIDTH + 2, 14);
        cout << " Spacebar = jump";

        gotoxy(10, 5);
        cout << "Press any key to start";
        getch();
        gotoxy(10, 5);
        cout << "                      ";

        while (1)
        {
                updateScore();
                int y = 1;
                if (kbhit())
                {
                        char ch = getch();
                        if (ch == 32)
                        {
                                if (birdPos > 3)
                                {
                                        birdPos -= 3;

                                        y = 2;
                                }
                        }
                        if (ch == 27)
                        {
                                break;
                        }
                }
                system("cls");
                updateScore();
                drawBird(y);
                drawPipe(0);
                drawPipe(1);
                if (collision() == 1)
                {
                        gameover();
                        return;
                }
                Sleep(100);
                eraseBird();
                erasePipe(0);
                erasePipe(1);
                birdPos += 1;

                if (birdPos > SCREEN_HEIGHT - 2)
                {
                        gameover();
                        return;
                }

                if (pipeFlag[0] == 1)
                        pipePos[0] += 2;

                if (pipeFlag[1] == 1)
                        pipePos[1] += 2;

                if (pipePos[0] >= 40 && pipePos[0] < 42)
                {
                        pipeFlag[1] = 1;
                        pipePos[1] = 4;
                        genPipe(1);
                }
                if (pipePos[0] > 68)
                {
                        score++;
                        Beep(5000, 50);
                        updateScore();
                        pipeFlag[1] = 0;
                        pipePos[0] = pipePos[1];
                        gapPos[0] = gapPos[1];
                }
        }
}

// void gotoxy(int x, int y)
// {
//         CursorPosition.X = x;
//         CursorPosition.Y = y;
//         SetConsoleCursorPosition(console, CursorPosition);
// }
class Point
{
private:
        int x;
        int y;

public:
        Point()
        {
                x = y = 10;
        }
        Point(int x, int y)
        {
                this->x = x;
                this->y = y;
        }
        void SetPoint(int x, int y)
        {
                this->x = x;
                this->y = y;
        }
        int GetX()
        {
                return x;
        }
        int GetY()
        {
                return y;
        }
        void MoveUp()
        {
                y--;
        }
        void MoveDown()
        {
                y++;
        }
        void MoveLeft()
        {
                x--;
        }
        void MoveRight()
        {
                x++;
        }
        void Draw(int i)
        {
                gotoxy(x, y);
                switch (i)
                {
                case 1:
                        cout << "*";
                        break;
                case 2:

                        cout << (char)219;
                        break;
                case 3:

                        cout << (char)262;
                        break;
                }
        }
        void Erase()
        {
                gotoxy(x, y);
                cout << " ";
        }
        void CopyPos(Point *p)
        {
                p->x = x;
                p->y = y;
        }
        void Debug()
        {
                cout << "(" << x << "," << y << ") ";
        }
};

class Snake
{
private:
        Point *cell[MAXSNAKESIZE]; // array of points to represent snake
        int size;                  // current size of snake
        char dir;                  // current direction of snake
        Point fruit;
        Point ob[no];

public:
        Snake()
        {
                size = 1;                   // default size
                cell[0] = new Point(20, 20);// 20,20 is default position
                for (int i = 1; i < MAXSNAKESIZE; i++)
                {
                        cell[i] = NULL;
                }
                fruit.SetPoint(rand() % 50, rand() % 25);
                for (int i = 0; i < no; i++)
                {
                        ob[i].SetPoint(rand() % 50, rand() % 25);
                }
        }

        void AddCell(int x, int y)
        {
                cell[size++] = new Point(x, y);
                Beep(5000, 50);
        }
        void TurnUp()
        {
                dir = 'w'; // w is control key for turning upward
        }
        void TurnDown()
        {
                dir = 's'; // w is control key for turning downward
        }
        void TurnLeft()
        {
                dir = 'a'; // w is control key for turning left
        }
        void TurnRight()
        {
                dir = 'd'; // w is control key for turning right
        }
        int Move()
        {
                // Clear screen
                system("cls");
                cout << "\t\t\t\t\t\tYOUR SCORE : " << size-1;

                // making snake body follow its head
                for (int i = size - 1; i > 0; i--)
                {
                        cell[i - 1]->CopyPos(cell[i]);
                }

                // turning snake's head
                switch (dir)
                {
                case 'w':
                        cell[0]->MoveUp();
                        break;
                case 's':
                        cell[0]->MoveDown();
                        break;
                case 'a':
                        cell[0]->MoveLeft();
                        break;
                case 'd':
                        cell[0]->MoveRight();
                        break;
                }

                // Collision with fruit
                for (int i = 0; i < no; i++)
                {
                        if (ob[i].GetX() == fruit.GetX() && ob[i].GetY() == fruit.GetY())
                        {
                                fruit.SetPoint(rand() % 50, rand() % 25);
                        }
                }
                for (int i = 0; i < no; i++)
                {
                        if (ob[i].GetX() == cell[0]->GetX() && ob[i].GetY() == cell[0]->GetY())
                        {
                                return 0;
                        }
                }
                if (fruit.GetX() == cell[0]->GetX() && fruit.GetY() == cell[0]->GetY())
                {
                        AddCell(0, 0);
                        fruit.SetPoint(rand() % 50, rand() % 25);
                }

                // drawing snake
                for (int i = 0; i < size; i++)
                        cell[i]->Draw(1);
                fruit.Draw(3);

                for (int i = 0; i < no; i++)
                {
                        ob[i].Draw(2);
                }

                // Debug();

                Sleep(100);
                return 1;
        }
        int get_size(){
                return size;

        }
        
        void Debug()
        {
                for (int i = 0; i < size; i++)
                {
                        cell[i]->Debug();
                }
        }
};

class person
{
public:
        int game_card;
        string name;
        float amount;
        static int count;
        void get()
        {
                string st;
                fflush(stdin);
                cout << "\nENTER YOUR NAME : ";
                getline(cin, st);
                fflush(stdin);
                name = st;
                game_card = rand_pos();
                cout << "ENTER AMOUNT TO DEPOSITE [EACH GAME CAST 50 RUPEES]: ";

                cin >> amount;
                while (amount < 50)
                {
                        cout << "THE AMOUNT IS INSUFFICIENT TO PLAY GAME \n ";
                        float b;
                        cout << "ADD AMOUNT : ";
                        cin >> b;
                        amount += b;
                }

                cout << "SIR/MAM YOU GAME ZONE CARD NUMBER IS : " << game_card;

                count++;
        }
        string get_name()
        {
                return name;
        }
        void red_amount()
        {
                if (amount < 50)
                {
                        throw 'a';
                }
                amount -= 50;
        }
        float get_amount()
        {
                return amount;
        }
        void add_amount()
        {

                cout << "\nENTER AMOUNT TO ENTER : ";
                float j;
                cin >> j;
                amount += j;
                cout << "\n YOUR CURRENT AMOUNT IS : " << amount;
        }
};
void getinfo(person &s)
{

        ofstream fout;
        fout.open("info.txt", ios::app);

        fout.write((char *)&s, sizeof(s));
        fout.close();
}
// void display()
// {
//         person s;
//         ifstream fin;
//         fin.open("info.txt", ios::app);
//         fin.read((char *)&s, sizeof(s));
//         while (fin)
//         {
//                 cout << s.game_card << " ";
//                 fflush(stdin);
//                 cout << s.name << " ";
//                 fflush(stdin);
//                 cout << s.amount << "\n";
//                 fin.read((char *)&s, sizeof(s));
//         }
//         fin.close();
// }
person getcard()
{
        person s;
        fstream fin;
        fin.open("info.txt", ios::in);
        fin.read((char *)&s, sizeof(s));

        cout << "ENTER YOUR CARD NUMBER  : ";
        int n;
        cin >> n;

        while (!fin.eof())
        {

                if (s.game_card == n)
                {
                        //cout<<s.name;
                        return s;
                }
                fin.read((char *)&s, sizeof(s));
        }
        fin.close();
        cout << "ENTERED CARD NUMBER IS NOT AVAILABLE IN OUT DATA \n";
}
void update_info(person &p)
{
        person s;
        fstream fin;
        fin.open("info.txt",ios::app|ios::out|ios::in);
        fin.read((char *)&s, sizeof(s));
        int count = 0;
        streampos pointer;

        while (!fin.eof())
        {

                if (s.game_card == p.game_card)
                {
                        count = 1;
                        pointer = fin.tellp();

                        break;
                }
                fin.read((char *)&s, sizeof(s));
        }

        if (count == 1)
        {
                pointer -= sizeof(s);
                fin.seekp(pointer, ios::beg);
                fin.write((char *)&p, sizeof(p));
        }
        
        fin.close();
        cout << "ENTERED CARD NUMBER IS NOT AVAILABLE IN OUT DATA \n";
}
int person::count = 0;
void game_zone()
{
        system("cls");
        cout << "\n";
        cout << "           *******                     *******\n";
        cout << "       ******************************************\n";
        cout << "      ********************************************\n";
        cout << "     ************************************    ******\n";
        cout << "    *******    **************************    *******\n";
        cout << "   ********    **************************************\n";
        cout << "  *****            ******************    *****    ****\n";
        cout << "  *****            ******************    *****    ****\n";
        cout << "  *********    ***************************************\n";
        cout << "  *********    ***************************    ********\n";
        cout << "  ****************************************    ********\n";
        cout << "  ****************************************************\n";
        cout << "  **********                                **********\n";
        cout << "   ********                                  ********\n";
        cout << "    ******                                    ******\n";

        cout << "                  WELCOME TO GAME ZONE\n\n\n\n\n";
}
void instructions_snake()
{

        system("cls");
        cout << "Instructions";
        cout << "\n----------------";
        cout << "\n press [W/w] to move up";
        cout << "\n press [S/s] to move down";
        cout << "\n press [A/a] to move left";
        cout << "\n press [D/d] to move right";
        cout << "\n\nPress any key to go back to menu";
        getch();
}
void snake_g()
{
        srand((unsigned)time(NULL));

        // Testing snake

        Snake snake;
        char op = 'l';
        int mm;
        int game = 1;
        int count = 0;
        int uu = 1;
        do
        {
                system("cls");
                gotoxy(10, 5);
                cout << " -------------------------- ";
                gotoxy(10, 6);
                cout << " |      sanke game      | ";
                gotoxy(10, 7);
                cout << " --------------------------\n";
                cout << "\t\t1. Start Game"
                     << "\n";
                cout << "\t\t2. Instructions\n";
                cout << "\t\t3. Quit\n";
                cout << "\t\tSelect option: ";
                char op = getche();

                if (op == '1')
                {
                        do
                        {
                                if (kbhit())
                                {
                                        op = getch();
                                }
                                switch (op)
                                {
                                case 'w':
                                case 'W':
                                        snake.TurnUp();
                                        break;

                                case 's':
                                case 'S':
                                        snake.TurnDown();
                                        break;

                                case 'a':
                                case 'A':
                                        snake.TurnLeft();
                                        break;

                                case 'd':
                                case 'D':
                                        snake.TurnRight();
                                        break;
                                }
                                mm = snake.Move();
                        } while (op != 'e' && mm == 1);

                        count++;
                }
                else if (op == '2')
                        instructions_snake();
                else if (op == '3')
                        uu = 0;

        } while (uu && count == 0);


        system("cls");
        cout << " GAME OVER \n ";
        cout<<"your score is "<<snake.get_size()-1<<endl;

}
void bird_g()
{

        setcursor(0, 0);
        srand(time(0));

        //	play();
        int count = 0;
        int uu = 1;
        do
        {
                system("cls");
                gotoxy(10, 5);
                cout << " -------------------------- ";
                gotoxy(10, 6);
                cout << " |      Flappy Bird       | ";
                gotoxy(10, 7);
                cout << " --------------------------\n";
                cout << "\t\t1. Start Game"
                     << "\n";
                cout << "\t\t2. Instructions\n";
                cout << "\t\t3. Quit\n";
                cout << "\t\tSelect option: ";
                char op = getche();

                if (op == '1')
                {
                        play();
                        count++;
                }
                else if (op == '2')
                        instructions();
                else if (op == '3')
                        uu = 0;

        } while (uu && count == 0);
}

int main()
{
        int n = 1;
        // int y=9;
        while (n)
        {
                game_zone();

                person p;
                int check_card = 0;
                cout << "\n DO YOU HAVE CARD [Y/N]: ";
                
                char g;
                cin >> g;
                switch (g)
                {
                case 'y':
                case 'Y':
                        p = getcard();
                        check_card = 1;
                        break;
                case 'n':
                case 'N':
                        p.get();

                        break;
                }

                cout << "\n HELLO " << p.get_name() << " !!\n";
                int o = 1;
                while (o)
                {
                        try
                        {
                                cout << " \nWITH WHICH ANIMAL DO YOU WANT TO PLAY . \n";
                                cout << " 1. BIRD  \n";
                                cout << " 2. SNAKE \n";
                                cout << " 3. EXIT \n";
                                int choise;
                                cin >> choise;
                                while (choise < 1 || choise > 3)
                                {
                                        cout << "INVALID CHOISE : REENTER YOUR CHOISE : ";
                                        cin >> choise;
                                }

                                switch (choise)
                                {
                                case 1:
                                        p.red_amount();
                                        bird_g();
                                        // game
                                        break;

                                case 2:
                                        p.red_amount();
                                        snake_g();

                                        // game
                                        break;
                                case 3:
                                        cout << "ENTER \n1 FOR ANOTHER PERSON TO ENTER.\n2 FOR EXIT THE WHOLE GAME : ";
                                        int h;
                                        cin >> h;
                                        while (h < 1 || h > 2)
                                        {
                                                cout << "INVALID CHOISE : REENTER YOUR CHOISE : ";
                                                cin >> h;
                                        }
                                        switch (h)
                                        {
                                        case 1:
                                                o = 0;
                                                if (check_card == 0)
                                                {
                                                        getinfo(p);
                                                }
                                                else
                                                {
                                                        update_info(p);
                                                }

                                                // display();

                                                break;
                                        case 2:
                                                n = 0;
                                                o = 0;
                                                if (check_card == 0)
                                                {
                                                        getinfo(p);
                                                }
                                                else
                                                {
                                                        update_info(p);
                                                }
                                                // display();
                                                system("cls");

                                                cout << "SPEND A GOOD TIME WITH YOU \nHOPE TO SEE YOU NEXT TIME!!\n";
                                        }
                                }
                        }
                        catch (char a)
                        {
                                cout << "INSUFFICIENT AMOUNT IN YOUR CARD \n";
                                cout << "WANT TO PLAY MORE : [Y/N] \n";
                                char t;
                                cin >> t;
                                switch (t)
                                {
                                case 'y':
                                case 'Y':
                                        float f;
                                        cout << "YOU HAVE TO DEPOSITE ATLEAST : " << 50.0 - (p.get_amount()) << "\n";
                                        p.add_amount();

                                        break;
                                case 'n':
                                case 'N':
                                        cout << "SPEND A GOOD TIME WITH YOU \nHOPE TO SEE YOU NEXT TIME!!\n";
                                        cout << "ENTER \n1 FOR ANOTHER PERSON TO ENTER.\n2 FOR EXIT THE WHOLE GAME : ";
                                        int h;
                                        cin >> h;
                                        while (h < 1 || h > 2)
                                        {
                                                cout << "INVALID CHOISE : REENTER YOUR CHOISE : ";
                                                cin >> h;
                                        }
                                        switch (h)
                                        {
                                        case 1:
                                                o = 0;
                                                if (check_card == 0)
                                                {
                                                        getinfo(p);
                                                }
                                                else
                                                {
                                                        update_info(p);
                                                }
                                                // display();
                                                break;
                                        case 2:
                                                n = 0;
                                                o = 0;
                                                if (check_card == 0)
                                                {
                                                        getinfo(p);
                                                }
                                                else
                                                {
                                                        update_info(p);
                                                }
                                                // display();
                                                system("cls");

                                                cout << "SPEND A GOOD TIME WITH YOU \nHOPE TO SEE YOU NEXT TIME!!\n";
                                                break;
                                        }
                                }
                        }
                }
        }
}