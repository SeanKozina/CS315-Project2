/*
Created By: Sean Kozina
11/2/2022
CS 315 Project 2

Header for Screen Class: this class is used to create a screen by passing
in a row and size that will create a 2dVector. The Borders are set to '-1' 
to demonstate out of bounds for the worm.


*/


#include <iostream>
#include <vector>




using namespace std;


class Screen{
	public:
		//constructors/deconstructors
		Screen(int row, int column);

		vector <vector<int>> getScreen();

		void setFoodVal(int foodValue); //getters and setters
		int getFoodVal();

		void makeFree(std::pair<int,int>, int currIndex); //make c a free empty cell
	
		void wormOccupy(std::pair<int,int> headPair); //make c occupied by the worm

		bool isFreeSpace(std::pair<int,int> headPair); //return true if c is free, false if occupied

		std::pair<int,int>  getRandomFreeCell(); //randomly select and return a free cell to place the snack in

		void printScreen();

	private:

		std::vector<pair<int,int>> freeCellsForSnack;       //inverse list to place snack 
		vector<vector<int>> theScreen;     //2d vector of cell represents the screen;
		int lastIndex;
		int foodVal;
		std::pair<int,int> foodPos;

};
