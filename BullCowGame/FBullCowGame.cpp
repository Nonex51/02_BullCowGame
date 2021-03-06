#pragma once 

#include "FBullCowGame.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <map>

#define TMap std::map

using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); } // default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength(){ return MyHiddenWord.length(); } 
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }


int32 FBullCowGame::GetMaxTries() const {
	TMap < int32, int32 > WordLengthToMaxTries{ {3,5},{4,5},{5,5},{6,5},{7,6},{8,7},{9,8},{10,11},{11,12} };  //My Maxtries {Length world . Tries}
	return WordLengthToMaxTries[MyHiddenWord.length()];
}


void FBullCowGame::Reset()
{
	std::ifstream file("../save.txt", std::ios::in);  //open the file
	FString str;
	if (file)
	{
		std::getline(file, str);
		MyHiddenWord = str;
		MyCurrentTry = 1;
		bGameIsWon = false;
		file.close();
		return;
	}
	else //if open fail
	{
		std::cerr << "Open the File it's impossible !" << std::endl;
		std::cerr << "Make sure that Isogram.txt inside Bulls&Cows folder !" << std::endl;
	}	
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess)
{
	if (IsNumber(Guess)) 
	{
		return EGuessStatus::Number;
	}
	else if (!IsIsogram(Guess)) // if the guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess)) // if the guess isn't all lowercase
	{
		return EGuessStatus::Not_Lowercase; 
	}
	else if (Guess.length() != GetHiddenWordLength()) // if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

// receives a VALID guess, incriments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess

	// loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			// if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				if (MHWChar == GChar) { // if they're in the same place
					BullCowCount.Bulls++; // incriment bulls
				}
				else {
					BullCowCount.Cows++; // must be a cow
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen; // setup our map
	for (auto Letter : Word) 	// for all letters of the word
	{
		Letter = tolower(Letter); // handle mixed case
		if (LetterSeen[Letter]) {// if the letter is in the map
			return false; // we do NOT have an isogram
		}
		else {
			LetterSeen[Letter] = true;// add the letter to the map
		}
	}

	return true; // for example in cases where /0 is entered
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word) 
	{
		if (!islower(Letter))
		{
			return false;
		}
	}
	return true;
}

bool FBullCowGame::IsNumber(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!isdigit(Letter))
		{
			return false;
		}
		}
	return true;
}


Score FBullCowGame::SaveScore(FString Playername)
															//TODO save in a JSON file not  txt
														//take the value of Score variable and save in a file
{
	
	int num_ligne = 0;
	std::ifstream file("../score.txt", std::ios::in);  //open the file, if there is already some score get the all in the buffer (tab)
	if (file)
	{
		//first counts how many lines there are in the file for creat a table
		FString ligne;
		while (getline(file, ligne)){++num_ligne;}
		std::vector<FString> tab(num_ligne);
		//insert value in the table

		for (int i = 0; i < num_ligne; i++)
		{	
			file >> tab[i];
		}
		file.close();

		/* Remove the last empty line on the file
		while (getline(file, ligne))
		{
			int i;
			if (i == num_ligne)
			{
				FString ligne = "";
				getline(file, ligne, '|');
				getline(file, ligne, '|');
					if ((ligne != ""))
					{
						std::cout << "remove\n" << std::endl;
					}
					else
						std::cout << "File ok\n" << std::endl;
			}
			i++;
		}
		//TODO
		Getline on the last line on the file
		if this line is empty 
		also remove this line
		else do nothing
		*/
		
		
		//Register in the file
	std::ofstream file("../score.txt", std::ios::out | std::ios::app);  
		if (file)
		{
			int Score = MyCurrentTry -1;
			int Word = MyHiddenWord.length();
			for (int i = 0; i < num_ligne; i++)
			{
				file << tab[i];
			}
			//NOTE the format of the save data
			file << "|" << Playername << "|" << Score << "|" << Word << "|" << std::endl;
			file.close();
		}
		else
			std::cerr << "Impossible d'ouvrir le fichier !" << std::endl;
	}
	else //if open fail
	{
		std::cerr << "Open the File it's impossible !" << std::endl;
		std::cerr << "Make sure that Isogram.txt inside Bulls&Cows folder !" << std::endl;
	}
	return Score();
}
	
