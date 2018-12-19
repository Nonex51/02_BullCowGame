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
	void Erase_Line();
	
	int AddNewWord();
	int RemoveWord();
	int ChooseNewWord();
	

private:
	FString file = "../save.txt";

}; 
