#pragma once
#include "FBullCowGame.h"

#include <string>

class Menu
{
public:
	
	//methode
	void Intro();
	void NewWordMenu();
	void ClearCons();
	void ViewStats();
	void ShowMenu();
	bool RemoveStats();
	void DisplayListe();
	int AddNewWord();
	int RemoveWord();
	int ChooseNewWord();
	void color();
	void TrackScore();
	//void TrackWord();
	//void ClearFlag(FString file);
	//void Pointeur();
	

private:
	FString save = "../save.txt";
	FString score = "../score.txt";
	

}; 
