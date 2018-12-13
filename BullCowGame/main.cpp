/* This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/
#pragma once

#include <iostream>
#include <string>	
#include "FBullCowGame.h"
#include "Menu.h"
#include "time.h"
#include <fstream>


//to make syntax unreal friendly
using FText = std::string;
using int32 = int;


//function propotype as outside a class

void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();
void DisplayMenu();
void GameIntro();



FBullCowGame BCGame; // instantiate a new game, which we re-use acrosss plays
Menu MenuInst;//instantiate a new menu

// the entry point for our application
int main()
{
	DisplayMenu();
	return 0; // exit the application
}



void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	// loop for the number of turns asking for guesses
	while ( ! BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) { // ! = NOT
		FText Guess = GetValidGuess();

		// submit valid guess to the game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		// print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";	
	}

	PrintGameSummary();
	return;
}

FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();

		// get a guess from the player
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		 Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Number:
			std::cout << "Please don't enter number ONLY letters.\n\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters \n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letter \n\n";
			break;
		}
	
	} while (Status != EGuessStatus::OK);//keep until we get no errors
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same word (y/n)? ";
	FText Response = "";		
		if (std::getline(std::cin, Response)){ MenuInst.ClearCons(); }
		else { DisplayMenu(); }
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "WELL DONE - YOU WIN!\n";
		BCGame.SaveScore();
	}
	else
	{
		std::cout << "Better luck next time! \n";
	}
}

void GameIntro()
{
	std::cout << "Can you guess the " <<BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
}


void DisplayMenu() 
{
	int varmenu;
	bool bPlayAgain = false;
	do
	{
		std::cout << " ==================== BULL & COW ====================\n" << std::endl;
		std::cout << " ----------------------- MENU -----------------------\n" << std::endl;
		std::cout << "               1. Start Bull&Cow" << std::endl;
		std::cout << "               2. Choose a New Word" << std::endl; //TODO under menu to choose between create, look, select in the Isogram.txt list
		std::cout << "               3. Look the stats" << std::endl; //TODO a function to make some stats about the game or about the player
		std::cout << "               4. Option" << std::endl; // TODO option menu to choose color
		std::cout << "               5. Quit" << std::endl;
		std::cout << " \n\n" << std::endl;
		std::cout << "    Press the number of your choice and press Enter" << std::endl;
		std::cin >> varmenu;
		std::cout << std::endl;

		switch (varmenu)
		{
		case 0: 
			MenuInst.ClearCons();
			std::cout << "   \n\n \n\n  Press the number of your choice and press Enter" << std::endl;
			_sleep(2000);
			MenuInst.ClearCons();
			DisplayMenu();
			break;

		case 1:	do {				//NOTE when you valide you choice in the menu the game think that you have put one try, why ?
			MenuInst.ClearCons();
			MenuInst.Intro();
			GameIntro();
			PlayGame();
			bPlayAgain = AskToPlayAgain();
		} while (bPlayAgain);
			break;

		case 2:
			MenuInst.ClearCons();
			MenuInst.NewWordMenu();
			break;

		case 3:
			MenuInst.ClearCons();
			MenuInst.ViewStats();
			break;

		case 4:std::cout << "Fonctionnality non implement" << std::endl;
			break;

		case 5:
			return;
			break;

		}

	} while (varmenu != 0);
}

/*


4. Create functionality to track score of the player. (least number of guesses)
5. In the new Main menu, show their last played score and best score out of all the games they've played so far.
6. Create Functionality to save the player's scores in disk.
7. Update the best score in the main menu to read from disk when the game starts and make sure it's shown in the Main Menu
8. Create Functionality to clear game scores on disk.
*/







