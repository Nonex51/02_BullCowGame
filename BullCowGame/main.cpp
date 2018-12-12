/* This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/
#pragma once

#include <iostream>
#include <string>	
#include "FBullCowGame.h"
#include "time.h"
#include <fstream>


//to make syntax unreal friendly
using FText = std::string;
using int32 = int;


//function propotype as outside a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();
void DisplayMenu();
void ClearCons();
int ChooseNewWord();
int PutNewWord();



FBullCowGame BCGame; // instantiate a new game, which we re-use acrosss plays

// the entry point for our application
int main()
{
	DisplayMenu();
	return 0; // exit the application
}

void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²" << std::endl;
	std::cout << "²                                           ²" << std::endl;
	std::cout << "²             }   {        ___              ²" << std::endl;
	std::cout << "²  *\\         (o o)       (o o)             ²" << std::endl;
	std::cout << "²    \\_/-------\\ /         \\ /-------\\      ²" << std::endl;
	std::cout << "²       | BULL |O     &     O| COW  | \\_    ²" << std::endl;
	std::cout << "²       |----- |             |--,-,-|  *    ²" << std::endl;
	std::cout << "²       ^      ^             ^      ^       ²" << std::endl;
	std::cout << "=============================================" << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
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
		if (std::getline(std::cin, Response)){ ClearCons(); }
		else { DisplayMenu(); }
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "WELL DONE - YOU WIN!\n";
	}
	else
	{
		std::cout << "Better luck next time! \n";
	}
}

void ClearCons()
{
	std::system("cls");	
}


int ChooseNewWord() // TODO make a way to put content in the HIDDEN_WORD from FBullCowGame.cpp
{
	std::ifstream fichier("../Isograms.txt",std::ios::in);  //open the file
	if (fichier)  
	{
		std::string content;
		fichier >> content;  
		std::cout << content << "\n" ;
		//HIDDEN_WORD = content;
	}
	else //if open fail
	{	
		std::cerr << "Open the File it's impossible !" << std::endl;
		std::cerr << "Make sure that Isogram.txt inside Bulls&Cows folder !" << std::endl;
	}	
	return 0;
}

int PutNewWord()
{
	//TODO enter a new word and save in the list
	return 0;
}

void DisplayMenu() // TODO the new menu
{
	int menu;
	bool bPlayAgain = false;
	do
	{
		std::cout << " ==================== BULL & COW ====================\n" << std::endl;
		std::cout << " ----------------------- MENU -----------------------\n" << std::endl;
		std::cout << "1. Start Bull&Cow" << std::endl;
		std::cout << "2. Choose a New Word" << std::endl; //TODO under menu to choose between create, look, select in the Isogram.txt list
		std::cout << "3. Look the stats" << std::endl; //TODO a function to make some stats about the game or about the player
		std::cout << "4. Option" << std::endl; // TODO option menu to choose color and difficulty of the IA
		std::cout << " \n\n" << std::endl;
		std::cout << " Press the number of your choice and press Enter" << std::endl;
		std::cin >> menu;
		std::cout << std::endl;

		switch (menu)
		{
		case 0: break;

		case 1:	do {
			ClearCons();
			PrintIntro();
			PlayGame();
			bPlayAgain = AskToPlayAgain();
		} while (bPlayAgain);
			break;

		case 2:ChooseNewWord();
			break;

		case 3:std::cout << "Fonctionnality non implement" << std::endl;
			break;

		case 4:std::cout << "Fonctionnality non implement" << std::endl;
			break;




		}

	} while (menu != 0);
}





