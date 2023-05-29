/*
Created By: Sean Kozina
11/2/2022
CS 315 Project 2

Implementation for Screen Class: this class is used to create a screen by passing
in a row and size that will create a 2dVector. The Borders are set to '-1'
to demonstate out of bounds for the worm.


*/






#include "Screen.hpp"





//constructor
Screen::Screen(int row, int column){
	foodVal = rand() % 9 + 1;   //sets random value between 1-9
	lastIndex = 0;
	freeCellsForSnack.resize((row - 2)  * (column - 2)); //resizes to max possible freeSpaces
	
	theScreen.resize(row);

	for (int i = 0; i < row; i++){
		theScreen.at(i).resize(column);
		for(int j = 0; j < column; j++){
			if(i == 0 || i == row - 1 || j == 0 || j == column - 1){
				theScreen.at(i).at(j) = -1;	
			}
			else{   //instantiates entire screen for 0 - max size ignoring borders
				theScreen.at(i).at(j) = lastIndex;
				std::pair <int,int> newPair;
				newPair.first = i;
				newPair.second = j; 
				freeCellsForSnack.at(lastIndex) = newPair; 
				lastIndex++;
			}
		}
	}
	lastIndex--;
}




//returns screen
vector<vector<int>> Screen::getScreen(){
	return theScreen;
}




//returns food value
int Screen::getFoodVal(){
	return foodVal;
}




//sets foodvalue
void Screen::setFoodVal(int newFoodVal){
	foodVal = newFoodVal;
}





//sets screen and freespace indexes to have slots occupied by worm using -1 
void Screen::wormOccupy(std::pair<int, int> headPair) {
	int tempIndex;
	tempIndex = theScreen.at(headPair.first).at(headPair.second);
	freeCellsForSnack.at(tempIndex) = freeCellsForSnack.at(lastIndex);
	freeCellsForSnack.at(lastIndex) = headPair;	
	theScreen.at(headPair.first).at(headPair.second) = -1;
	theScreen.at(freeCellsForSnack.at(tempIndex).first).at(freeCellsForSnack.at(tempIndex).second) = tempIndex; 
	lastIndex--;
}





//returns a random cell
std::pair<int, int>  Screen::getRandomFreeCell() {
	int randomInt = rand() % freeCellsForSnack.size() + 1;
	return freeCellsForSnack.at(randomInt);
}




//free the current cell and its index  
void Screen::makeFree(std::pair<int, int> tailPair, int currIndex) {
	freeCellsForSnack.at(currIndex) = freeCellsForSnack.at(lastIndex);
	freeCellsForSnack.at(lastIndex).first = tailPair.first;
	freeCellsForSnack.at(lastIndex).second = tailPair.second;
	lastIndex++;
	theScreen.at(tailPair.first).at(tailPair.second) = lastIndex;
}




//returns true if space is free false if not
bool Screen::isFreeSpace(std::pair<int, int> headPair) {
	if (theScreen.at(headPair.first).at(headPair.second) == -1) {
		return false;
	}
	else return true;
}





void Screen::printScreen() {
	for (int i = 0; i < size(theScreen); i++) {
		for (int j = 0; j < size(theScreen); j++) {
			cout << theScreen.at(i).at(j) << " ";
		}
		cout << endl;
	}
}
