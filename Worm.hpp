/*
Created By: Sean Kozina
11/2/2022
CS 315 Project 2

Header for Worm Class: this class is used to create a worm with a circular q data structure
by passing in a row and column to create the size that allocate to the maximum number of spaces.
Using food/foodless move the worm will move around the screen and grow when it eats food based on inputs
from the user

*/



#include <iostream>
#include <vector>

using namespace std;




class Worm{

	public:
	//constructor/deconstructor
	Worm(std::pair<int,int> rowColumnPair);

	//getters and setters

	void setScore(int newScore);
	int getScore();

	void setFoodValue(int newFoodVal);
	int getFoodValue();

	void setHasFood(bool newHasFood);
	bool getHasFood();

	void setIsDead(bool newIsDead);
	bool getIsDead();

	void foodlessMove(char keyPress);
	void foodMove(char keyPress);

	int getHead();//if head -1 =-1 get size -1 else return body.at(head-1)
	int getTail();

	
	std::vector<std::pair<int,int>> getBody();
	std::vector<int> getIndexes();


	private:
	//helper function
        bool isValidChar(char inputChar);
	int score;    //number of eaten or size of -1
	std::vector<std::pair<int,int>> body;   //all positions of worm
	std::vector<int>indexes;                    
	int foodValue;
	bool hasFood;
	bool isDead;
	int head;
	int tail;
};
