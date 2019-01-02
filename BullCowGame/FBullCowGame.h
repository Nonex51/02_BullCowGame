/*The game logic (no view code or direct user interaction
The game is a simple guess the word game based on Mastermind*/

#pragma once
#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

struct Score		// Try to do this structure to manipulate better the data 
{
	FString Playername = "" ;
	//FString NamePlayer;
	//int score = 0 ;
	//int Word = 0 ;
};

enum class EGuessStatus		
{
	Number,
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame
{
public:
	FBullCowGame(); // constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength();
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString);
	void Reset();
	FBullCowCount SubmitValidGuess(FString);

	Score SaveScore(FString);
	

private:
	// see constructor for initialisation
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;	
	bool bGameIsWon;
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
	bool IsNumber(FString) const;
	//int best score
	
	
};