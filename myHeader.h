#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cstdio>
#include<conio.h>
using namespace std;
//////////////////////////////////////////////////////////
// this class is so 'cold' that it freezes things
class delayClass {
    clock_t startTime, curTime;
public:
    delayClass() { startTime = clock(); }
    void resetTimer() {  startTime = clock(); } // function to reset the timer
    bool delay(double delayTime)
    {

        curTime = clock() ;
        if((double)(curTime - startTime)/CLOCKS_PER_SEC>=delayTime)
        {
            return true;
        } // return true if time is up

        return false; // return false if time to spare
    }

    void freeze(double t)
    {
        while(!delay(t)) {

        }
    }
};
/////////////////////////end of delayClass//////////////////////////////////
template <typename classType>
class arrayClass {
    int row, column;
public:
    classType **p;
    arrayClass(int r, int c);
    classType& setVal(int r, int c)  { return p[r][c]; }
    classType getVal(int r, int c) { return p[r][c]; }
};

template<typename classType>
arrayClass<classType>::arrayClass(int r, int c)
{
    row = r;
    column = c;

    p = new classType*[row];

    for(int i = 0; i < row; i++) p[i] = new classType[column];
    // memory allocated

    // initializing
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < column; j++) p[i][j] = 0;
    }
}
/////////////////////////////end of arrayClass/////////////////////////////////
class pos {
public:
    int row, col; // row and column
    pos() { row = col = 0; }
    void setPos(int r, int c) { row = r; col = c; }
    bool operator==(pos x) { return ((row == x.row) && (col == x.col) ); }
    bool operator!=(pos x) { return ((row != x.row) && (col != x.col) ); }
};
//////////////////////////end of pos class////////////////////////////////////////
class Q {
    Q *head;
    Q *tail;
    Q *next;
    pos ob;
public:
    Q();
    void store(pos x);
    pos retrieve();
};

Q::Q()
{
    head = tail = next = NULL;
}

void Q::store(pos x)
{
    Q *item;

    item = new Q;
    if(!item) {
        cout << "Allocation error\n";
        exit(1);
    }

    item->ob = x;

    if(tail) tail->next = item;
    tail = item;
    item->next = NULL;
    if(!head) head = tail;
}

pos Q::retrieve()
{
    pos i;
    Q *p;

    if(!head) { // queue is empty
        pos temp;
        temp.setPos(-1, -1);
        return temp;
    }

    i = head->ob;
    p = head;
    head = head->next;
    delete p;

    return i;
}
///////////////////////end of Q class//////a queue///////////////////////////////
