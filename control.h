#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cstdio>
#include<conio.h>
#include <cctype>
#include <fstream>
#include "myHeader.h"
using namespace std;
//////////////////////////////////////////////////
long long score; // player score
long long multiplier; // multiplier
long long numOfBadFoods; // number of bad foods
double interval; // seconds of interval between two frames
long long highScore; // high score
/////////////////////////////////////////////////////////////////
class frame {
    arrayClass<char> screen;
    arrayClass<int> snake;
    pos food, badFood[1000];
    pos head;
    Q trail; // trail of the snake is stored in a queue
    //char currentCommand;
public:
    frame();
    void drawFrame();
    void updateFood();
    bool snakeControl(char command);
    bool gameOver(pos x); // returns true if game is over
    bool foodEaten(pos x); // returns true if food is eaten
};

frame::frame() : screen(22, 81), snake(22, 80) // constructor
{
    for(int i = 10; i <= 20; i++) {
        snake.setVal(11, i) = 1; // primary size of snake
        pos temp;
        temp.setPos(11, i);
        trail.store(temp);
    }

    head.setPos(11, 20); // primary position of head

    // determine primary position for foods
    updateFood();

   // currentCommand = 'D'; // makes the snake move right primarily

} // end of constructor

void frame::drawFrame()
{
    for(int i=0; i<80; i++)
    {
        screen.setVal(0, i) = screen.setVal(21, i) = '.';
    }

    for(int i=1; i<21; i++)
    {
        screen.setVal(i, 0) = screen.setVal(i, 79) = '.';
        for(int j=1; j<79; j++) screen.setVal(i, j) = ' ';
    }
    // empty screen drawn

   // insert food into the screen
   screen.setVal(food.row, food.col) = '$';
   // insert bad foods into the screen
   for(int i = 0; i < numOfBadFoods; i++) screen.setVal(badFood[i].row, badFood[i].col) = '!';

    // insert snake into the screen
    for(int i = 0; i < 21; i++) {
        for(int j = 0; j < 79; j++)
        {
            if(snake.getVal(i, j)) screen.setVal(i, j) = '#';
        }
    } // snake inserted

    for(int i = 0; i < 22; i++) cout << screen.p[i]; // drawing frame

    cout << "SCORE: " << score << "\t\t\t\tPREVIOUS HIGH SCORE: "<< highScore;
    cout << "\nLEVEL: " << multiplier -1;
} // end of drawFrame()

void frame::updateFood()
{
    srand(time(NULL));
    while(1)
    {
        food.row = 1 + rand() % 20;
        food.col = 1 + rand() % 78;

        if(!snake.getVal(food.row, food.col)) break;
    }
    // bad foods
    int i = 0;
    int j;

    while(i < numOfBadFoods)
    {
        badFood[i].row = 1 + rand() % 20;
        badFood[i].col = 1 + rand() % 78;

        if(!snake.getVal(badFood[i].row, badFood[i].col)  && food != badFood[i]) {
            i++;
            for(j = i-2; j >=0; j--)
                if(badFood[i-1] == badFood[j]) i--;
        }
    }
   // lul();

} // end of updateFood()

bool frame::snakeControl(char command)
{
    pos temp;
    bool foodFlag = false;

    //if(currentCommand != command) currentCommand = command;

    switch(command){
    case 'W': // command to move snake up
        head.setPos(head.row - 1, head.col);
        if(gameOver(head)) return false;
        if(foodEaten(head)) {
            updateFood();
            foodFlag = true;
        }
        snake.setVal(head.row, head.col) = 1;
        temp.setPos(head.row, head.col);
        trail.store(temp);
        break;
    case 'A': // command to move snake left
        head.setPos(head.row, head.col - 1);
        if(gameOver(head)) return false;
        if(foodEaten(head)) {
            updateFood();
            foodFlag = true;
        }
        snake.setVal(head.row, head.col ) = 1;
        temp.setPos(head.row, head.col);
        trail.store(temp);
        break;
    case 'S': // command to move snake down
        head.setPos(head.row + 1, head.col);
        if(gameOver(head)) return false;
        if(foodEaten(head)) {
            updateFood();
            foodFlag = true;
        }
        snake.setVal(head.row, head.col) = 1;
        temp.setPos(head.row, head.col);
        trail.store(temp);
        break;
    case 'D': // command to move snake right
        head.setPos(head.row, head.col + 1);
        if(gameOver(head)) return false;
        if(foodEaten(head)) {
            updateFood();
            foodFlag = true;
        }
        snake.setVal(head.row, head.col ) = 1;
        temp.setPos(head.row, head.col);
        trail.store(temp);
        break;
    } // end of switch
    ///////////////////////head calculated///////////////////////////////////
    if(!foodFlag) { // if food is eaten, tail increases
        temp = trail.retrieve();
        snake.setVal(temp.row, temp.col) = 0;
    }
    ////////////////////////tail calculated//////////////////////////////////////
    return true;
} // end of snakeControl()

bool frame::gameOver(pos x)
{
    // game is over if the snake hits its body
    for(int i = 0; i < 21; i++)
        for(int j = 0; j < 80; j++)
            if(snake.getVal(i, j))
                if(x.row == i && x.col == j) return true;
    ////////////////////////////////////////////////
    // game is also over when the snake hits the barrier
    if(x.col == 0) {
        for(int i = 0; i < 22; i++) if(x.row == i) return true;
    } // end of if

    if(x.col == 79) {
        for(int i = 0; i < 22; i++) if(x.row == i) return true;
    } // end of if

    if(x.row == 0) {
        for(int i = 0; i < 80; i++) if(x.col == i) return true;
    } // end of if

    if(x.row == 21) {
        for(int i = 0; i < 80; i++) if(x.col == i) return true;
    } // end of if
    return false;
} // end of gameOver()

bool frame::foodEaten(pos x)
{
    if(food == x)
    {
        score  += multiplier;
        updateFood();
        return true;
    }

    for(int i = 0; i < numOfBadFoods + 1; i++) {
        if(badFood[i] == x)
        {
            score  -= multiplier;
            updateFood();
            return true;
        }
    }
    return false;
}
///////////////////end of frame class////////////////////////////////////////
class gameControl {
    long long pointsToNextLevel;
public:
    gameControl() {
        reset();
    }
    void check(frame& o);
    void welcome();
    void play();
    void reset(); // reset everything
};

void gameControl::welcome()
{
    delayClass ob;
    cout << "\n\n\n\n\t     PAGLAGHORA GAMES presents...\n\n";
    cout << "\t\t\tFAST & FURIOUS SNAKE";
    ob.freeze(3.0);
    system("CLS");
    cout << "Control the snake using W, A, S, D\nEat '$', but avoid '!'\n";
    ob.resetTimer();
    ob.freeze(5);
    system("CLS");
} // end of welcome()

void gameControl::check(frame& o)
{

    if(score >= pointsToNextLevel) { // increase the difficulty depending on score
        pointsToNextLevel = pointsToNextLevel + multiplier + 10;
        if(multiplier < 25) multiplier++;
        if(numOfBadFoods < 25) {
            numOfBadFoods++;
            o.updateFood();
        }
        if(interval > 0.09) interval -= 0.01;
    }
}

void gameControl::play()
{
    frame game;
    delayClass ob;
    char cc = 'D'; // current command
    char command;

    while(1)
    {
        game.drawFrame();
        ob.freeze(interval);
        if(kbhit()) { // take input
            command = toupper(getch());
            if(command == 'W' || command == 'A' || command == 'S' || command == 'D')
                if((cc == 'D' && command != 'A') || (cc == 'W' && command != 'S') || (cc == 'A' && command != 'D') || (cc == 'S' && command != 'W'))
                    cc = command;
        }

        if(!game.snakeControl(cc)) { // when game is over
            system("CLS");
            ob.resetTimer();
            for(int i = 0; i < 3; i++) {
                ob.freeze(0.5);
                ob.resetTimer();
                game.drawFrame();
                ob.freeze(0.5);
                ob.resetTimer();
                system("CLS");
            }
            cout << "Game Over!\nYour score: " << score << "\n\n";
            if(score > highScore) {
                ofstream ohs("D:\\FAST & FURIOUS SNAKE.exe");
                ohs << score;
                ohs.close();
                cout << "\n\nCONGRATULATIONS!! It's the high score!\n\n";
            }
            break;
        }
        system("CLS");
        ob.resetTimer();
        check(game);
    } // end of while

} // end of play()

void gameControl::reset()
{
    score =  0;
    multiplier = 2;
    numOfBadFoods = 5;
    interval = 0.3;
    pointsToNextLevel = 10;

    //read high score from a file
    ifstream ihs("D:\\FAST & FURIOUS SNAKE.exe");

    if(!ihs) { // if for the first time
        ofstream ohs("D:\\FAST & FURIOUS SNAKE.exe");
        highScore = 0;
        ohs << highScore;
        ohs.close();
    }

    else {
        ihs >> highScore;
    }
    ihs.close();
}
//////////////////////end of gameControl class///////////////////////////////

