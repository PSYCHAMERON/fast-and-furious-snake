#include "control.h"
/////////////////////////////////////////////////////////

int main()
{
    gameControl snake;
    snake.welcome();

    char choice;
    do {
        snake.play();
        do{
        cout << "Do you want to play again? (y/n)\n";
        choice = toupper(getch());
        }while(choice != 'Y' && choice != 'N');

        if(choice == 'Y') {
            snake.reset();
            system("CLS");
        }
    }while(choice != 'N');

    cout << "\nGOOD BYE!";

    while(true)
    {
        getch();
    }

    return 0;
}
