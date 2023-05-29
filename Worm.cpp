/*
Created By: Sean Kozina
11/2/2022
CS 315 Project 2

Implementaion for Worm Class: this class is used to create a worm with a circular q data structure
by passing in a row and column to create the size that allocate to the maximum number of spaces.
Using food/foodless move the worm will move around the screen and grow when it eats food based on inputs
from the user

*/


#include "Worm.hpp"



//constructor
Worm::Worm(std::pair<int, int> rowColumnPair){
	//resizes both arrays to account for the maximum number of squares
	indexes.resize((rowColumnPair.first) * (rowColumnPair.second) - 2);
	body.resize((rowColumnPair.first) * (rowColumnPair.second) - 2);
	//sets first cell to the very middle cells
	body.at(0).first = rowColumnPair.first/2;
	body.at(0).second = (rowColumnPair.second/2) -2;

	score = 0;
	foodValue = 0; //later function updates random 1-9
	hasFood = false;
	isDead = false;
	head = 1;
	tail = 1;
}





//returns score
int Worm::getScore(){
	return score;
}




//sets score
void Worm::setScore(int newScore){
	score = newScore;
}




//returns food value
int Worm::getFoodValue(){
	return foodValue;
}



//sets food value
void Worm::setFoodValue(int newFoodVal){
	foodValue = newFoodVal;
}



//returns if the worm has food
bool Worm::getHasFood(){
	return hasFood;
}




//sets has food to true or false
void Worm::setHasFood(bool newHasFood){
	hasFood = newHasFood;
}




//returns if the worm is dead or not
bool Worm::getIsDead(){
	return isDead;
}




//sets the worm to dead or not
void Worm::setIsDead(bool newIsDead){
	isDead = newIsDead;
}




//returns the head in a circular q
int Worm::getHead(){
	if(head - 1 == -1){
		return body.size() - 1;
	}
	return head - 1;
}




//returns the tail in the circular q
int Worm::getTail() {
	if (tail - 1 == -1) {
		return body.size() - 1;
	}
	return tail - 1;
}





//returns the body of the worm
std::vector<std::pair<int,int>> Worm::getBody(){
	return body;
}




//returns the indexes of the worm
std::vector<int> Worm::getIndexes(){
	return indexes;
}




//moves the worm in the direcetion pressed by the user deletes the last item adds one to head
void Worm::foodlessMove(char charecterInput){
	foodMove(charecterInput);
	tail++;
	if(tail>=size(body)){
		tail = 0;
	}
}




//moves the worm in the direction pressed by the user adds one to head
void Worm::foodMove(char charecterInput){
	if(isValidChar(charecterInput)){
		if (charecterInput == 'a') {     //move left
			body.at(head) = body.at(getHead());
			body.at(head).second--;
		}
		else if (charecterInput == 'd') {//move right
			body.at(head) = body.at(getHead());
			body.at(head).second++;
		}
		else if (charecterInput == 'w') {//move up
			body.at(head) = body.at(getHead());
			body.at(head).first--;
		}
		else if (charecterInput == 's') { //move down
			body.at(head) = body.at(getHead());
			body.at(head).first++;
		}

        head++;

		if (head >= size(body)) {
			head = 0;
		}
	}
}






//helper funciton determines if the key pressed is a valid direction
bool Worm::isValidChar(char inputChar){
	if (inputChar == 'w'||inputChar == 'a'||inputChar == 's'||inputChar == 'd'){
		return true;
	}
	return false;
}

