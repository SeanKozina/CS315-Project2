/*
Created By: Sean Kozina
11/2/2022
CS 315 Project 2


Instaniates all classes and creates the game. User passes in game size,if valid
games starts and is run until the user dies(hits wall or itself).


*/






#include <iostream> 
#include <string>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sgtty.h>
#include <curses.h>
#include <signal.h>
#include <cassert>
#include "Screen.hpp"
#include "Worm.hpp"
#include "getChar.hpp"

using namespace std;


const int startingWormSize = 8;   //the worms starting size at beginning of the game


void startup( void );
void terminate( int num );



//runs entire game based off size user inputs
int main(int argc, char** argv){
	if(argc == 3){
	int row = stoi(argv[1]);
	int column = stoi(argv[2]);

	if((row < 9 || row > 25)||(column < 9 || column > 80)){
		cerr << "Command line inputs not in correct range";
		exit(-1000);
	}

	row += 2;
	column += 2;


	startup();

	move(0,0);
	addstr("Worm");
	for(int i = 0; i <column -1; i++){
		addch(' ');
	}
	int lastCol = column + 5;
	move(0 , lastCol);
	addstr("Score: 0");	
	move(1,0);



	for(int i = 0; i < row; i++){
		for(int j = 0; j < column; j++){
			if (i == 0 || i == row - 1) {
                                mvaddch( i, j, '*');
                        }
                        else if (j == 0 || j == column - 1) {
                                mvaddch( i, j, '*');
                        }
                        else if (i > 0 && j > 0) {
                                mvaddch( i, j, ' ');
                        }
	
		}
	}
	
	refresh();
	


	std::pair <int,int> wormsStartingLocation;
        wormsStartingLocation.first = row;
        wormsStartingLocation.second = column;
        Worm theWorm(wormsStartingLocation);
	Screen theScreen(row,column);
	
	std::pair <int,int> startingSnackCell = theScreen.getRandomFreeCell();
	mvaddch(startingSnackCell.first,startingSnackCell.second,'f');

        for(int i = 0; i < startingWormSize - 1; i++){
                theWorm.foodMove('d');
		if(!theScreen.isFreeSpace(theWorm.getBody().at(theWorm.getHead()))){
			cerr << "try incresing size of colums by 1";
		}
		theScreen.wormOccupy(theWorm.getBody().at(theWorm.getHead()));
                mvaddch(wormsStartingLocation.first / 2, i + wormsStartingLocation.second/ 2 - 2,'o'); 
		refresh();
        }       
	mvaddch( wormsStartingLocation.first/2 ,startingWormSize - 1 + wormsStartingLocation.second/2 - 2,'@');
	refresh();
	int foodcounter = theScreen.getFoodVal();
	while(!theWorm.getIsDead()){
		char inputChar = getchar();
		std::vector<std::pair<int,int>> wormBody;
		if(theWorm.getBody().at(theWorm.getHead()) == startingSnackCell){
			theWorm.setHasFood(true);
			theWorm.setScore(theWorm.getScore() + theScreen.getFoodVal());
			foodcounter = foodcounter + theScreen.getFoodVal();
			theScreen.setFoodVal(rand() % 9 + 1);
			
                        startingSnackCell = theScreen.getRandomFreeCell();
                        mvaddch(startingSnackCell.first,startingSnackCell.second, ('f'));
		}
		if(theWorm.getHasFood()){
			theWorm.foodMove(inputChar);
			wormBody = theWorm.getBody();
			if(!theScreen.isFreeSpace(wormBody.at(theWorm.getHead()))){
				theWorm.setIsDead(true);
				cout << "the worm is dead" << endl;
			}
			else{
				theScreen.wormOccupy(wormBody.at(theWorm.getHead()));
                                mvaddch(wormBody.at(theWorm.getHead()-1).first,wormBody.at(theWorm.getHead()-1).second, 'o');
                                mvaddch(wormBody.at(theWorm.getHead()).first , wormBody.at(theWorm.getHead()).second, '@');
				foodcounter--;
				if(foodcounter == 0){
					theWorm.setHasFood(false);
				}
			}
		}

		else{
			theWorm.foodlessMove(inputChar);
			wormBody = theWorm.getBody();
			if(!theScreen.isFreeSpace(wormBody.at(theWorm.getHead()))){
				theWorm.setIsDead(true);	
                                cout << "the worm is dead" << endl;
			}
			else{
				theScreen.wormOccupy(wormBody.at(theWorm.getHead()));
				theScreen.makeFree(wormBody.at(theWorm.getTail()), theWorm.getTail());
                        	mvaddch(wormBody.at(theWorm.getTail() - 1).first,wormBody.at(theWorm.getTail()-1).second,' ');
				mvaddch(wormBody.at(theWorm.getHead()-1).first, wormBody.at(theWorm.getHead()-1).second, 'o');
				mvaddch(wormBody.at(theWorm.getHead()).first , wormBody.at(theWorm.getHead()).second, '@');
			
			}
		}

		refresh();
	}
	move(0,lastCol);
	cout << "Your Score was: " << theWorm.getScore();

	terminate(0);
	}else{
		cerr << "invalid inputs:";
		exit(1);
	}
	return(0);

}






//stops the curse window
void terminate( int num ){
     mvcur( 0, COLS - 1, LINES - 1, 0 );
     clear();
     refresh();
     endwin();
}






void startup( void ){
     initscr();     /* activate the curses */
     curs_set(0);   /* do not display the cursor */
     clear();       /* clear the screen that curses provides */
     noecho();      /* prevent the input chars to be echoed to the screen */
     cbreak();      /* change the stty so that characters are delivered to the
                       program as they are typed--no need to hit the return key!*/
}

