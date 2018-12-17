#pragma once 

#include <string>	
#include <iostream>
#include <fstream>
#include "Menu.h"
#include "FBullCowGame.h"

void Menu::Intro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << "²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²" << std::endl;
	std::cout << "²                                           ²" << std::endl;
	std::cout << "²             }   {        ___              ²" << std::endl;
	std::cout << "²  *\\         (o o)       (o o)             ²" << std::endl;
	std::cout << "²    \\_/-------\\ /         \\ /-------\\      ²" << std::endl;
	std::cout << "²       | BULL |O     &     O| COW  | \\_    ²" << std::endl;
	std::cout << "²       |----- |             |--,-,-|  *    ²" << std::endl;
	std::cout << "²       ^      ^             ^      ^       ²" << std::endl;
	std::cout << "=============================================" << std::endl;
	std::cout << std::endl;
	return;
}

void Menu::ShowMenu()
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
}

void Menu::NewWordMenu()
{
	int menu;
	do {
		std::cout << " ==================== BULL & COW ====================\n" << std::endl;
		std::cout << " ----------------------- MENU -----------------------\n" << std::endl;
		std::cout << "               1. Choose Word from List" << std::endl;
		std::cout << "               2. Add New Word" << std::endl;
		std::cout << "               3. Remove Word" << std::endl;
		std::cout << "               0. Back" << std::endl;
		std::cout << " \n\n" << std::endl;
		std::cout << "    Press the number of your choice and press Enter" << std::endl;
		std::cin >> menu;
		std::cout << std::endl;
		switch (menu)
			{
			case 1:
				ChooseNewWord();
				break;
			case 2:
				//AddNewWord();
				break;
			case 3:std::cout << " " << std::endl;
				break;
			}
	} while (menu != 0);
}

int Menu::AddNewWord()
{
	//TODO enter a new word and save in the list
	return 0;
}

void Menu::ClearCons()
{
	std::system("cls");
}

int Menu::ChooseNewWord() // TODO make a way to put content in the HIDDEN_WORD from FBullCowGame.cpp
{
	std::ifstream file("../Isograms.txt", std::ios::in);  //open the file
	if (file)
	{
		std::string ligne;
		int num_ligne = 0;
		ClearCons();
		std::cout << " ==================== BULL & COW ====================\n" << std::endl;
		std::cout << " ---------------------- Liste -----------------------\n" << std::endl;

		while (getline(file, ligne))  
		{
			++num_ligne;
			std::cout << "               " << num_ligne <<". " << ligne << std::endl;  
		}	
	}
	else //if open fail
	{
		std::cerr << "Open the File it's impossible !" << std::endl;
		std::cerr << "Make sure that Isogram.txt inside Bulls&Cows folder !" << std::endl;
	}
	return 0;
}

void Menu::ViewStats()
{
	{
		std::ifstream file("../save.txt", std::ios::in);  //open the file
		if (file)
		{
			std::string ligne;
			int num_ligne = 0;
			ClearCons();
			std::cout << " ==================== BULL & COW ====================\n" << std::endl;
			std::cout << " ---------------------- Score -----------------------\n" << std::endl;

			while (getline(file, ligne))
			{
				++num_ligne;
				std::cout << "               " << num_ligne << ". " << ligne << std::endl;
			}
		}
		else //if open fail
		{
			std::cerr << "Open the File it's impossible !" << std::endl;
			std::cerr << "Make sure that Isogram.txt inside Bulls&Cows folder !" << std::endl;
		}
		return;
	}

}





