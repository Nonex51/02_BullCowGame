#pragma once 

#include <string>	
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <list>
#include <algorithm>
#include "Menu.h"
#include "FBullCowGame.h"
//#include <Windows.h>


int number = 0;

//TODO function Cin() to verif input of the player

void Menu::ClearCons()
{
	std::system("cls");
}

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
	std::cout << "               2. Choose a New Word" << std::endl;
	std::cout << "               3. Look the stats" << std::endl; 
	std::cout << "               4. Option" << std::endl; 
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
		case 0:
			
			break;
			case 1:
				ChooseNewWord();
				break;
			case 2:
				 
				DisplayListe();
				AddNewWord();
				break;
			case 3:std::cout << " " << std::endl;
				RemoveWord();
				break;
			}
	} while (menu != 0);
	return;
}

void Menu::DisplayListe()
{
	std::ifstream file(save, std::ios::in);  //open the file
	if (file)
	{
		std::string ligne;
		int num_ligne = 0;
		int id = 0;
		ClearCons();
		std::cout << " ==================== BULL & COW ====================\n" << std::endl;
		std::cout << " ---------------------- Liste -----------------------\n" << std::endl;
		while (getline(file, ligne))
		{
			++num_ligne;
			std::cout << "               " << num_ligne << ". " << ligne << std::endl;
		}
		std::cout << " \n" << std::endl;
		std::cout << " --------------------- End Liste --------------------\n" << std::endl;
	
	}
	else //if open fail
	{
		std::cerr << "Open the File it's impossible !" << std::endl;
		std::cerr << "Make sure that Isogram.txt inside Bulls&Cows folder !" << std::endl;
	}
	//system("PAUSE");
	return;
}


int Menu::AddNewWord()
{

std::string word;
std::string confirm;
	std::ofstream file(save, std::ios::out | std::ios::app); // open the file

	std::cout << " Enter your new word to add in the list\n " << std::endl;
	std::cin >> word;
	
	if (std::getline(std::cin, confirm))
	{
		file << word << std::endl;
		file.close();
		ClearCons();
		std::cout << " \" " << word << " \" "<< " It's add in the list\n\n" << std::endl;
	}
	else
		std::cerr << "Open the file it's impossible or write something!\n" << std::endl;
	return 0;
}

int Menu::ChooseNewWord()
{
	std::ifstream file(save, std::ios::in);  //open the file
	if (file)
	{
		std::string ligne;
		int num_ligne = 0;
		int id=0;
		ClearCons();
		std::cout << " ==================== BULL & COW ====================\n" << std::endl;
		std::cout << " ---------------------- Liste -----------------------\n" << std::endl;
		while (getline(file, ligne))  
		{
			++num_ligne;
			std::cout << "               " << num_ligne <<". " << ligne << std::endl;	
		}
		std::cout << " --------------------- End Liste --------------------\n" << std::endl;
		std::cout << " Press the number from the word of your choice.\n" << std::endl;
		std::cin >> id;
		file.clear(); // clear/unset end of file flag
		file.seekg(0, std::ios::beg);// up on the begin of the file
		int num_lignebackup = num_ligne + 1;

		// Initialisation table 	
		std::vector<FString> tab(num_ligne);
		std::vector<FString> tabbackup(num_lignebackup);

		for (int i = 0; i < num_ligne; i++)
		{
			file >> tab[i];
		}
		file.close();

		int wordselect = id - 1;
		for (int i = 0; i < wordselect; i++) {
			int j = i + 1;
			tabbackup[j] = tab[i];	
		}
		
		for (int i = id; i <num_ligne; i++){
			int j = i + 1;
			tabbackup[j] = tab[i];	
		}

		tabbackup.erase(tabbackup.begin() + id);// erase the empty container
		tabbackup[0] = tab[wordselect]; //put the word in the first place

		//NOTE to erase a single element, vec.erase(iterator), to erase multiple elements vec.erase(from, to). 
		//remove and remove_if to shuffle the ones you want to remove to the end, so that they can be erased in one go

			std::ofstream file(save, std::ios::out | std::ios::trunc); // open the file
			file.clear(); // clear/unset end of file flag
			
			for (int i = 0; i < num_ligne; i++)
			{
				FString word = tabbackup[i];
				file << word << std::endl;
			}
			file.close();
			
			//TODO verification with the access file with save.txt or isogram.txt	
			ClearCons();
			std::cout << "\n You have move " << tabbackup[0] << " in the first position.\n" << std::endl;
	}
	else //if open fail
	{
		std::cerr << "Open the File it's impossible !" << std::endl;
		std::cerr << "Make sure that Isogram.txt inside Bulls&Cows folder !" << std::endl;
	}
	//system("PAUSE");
	return 0;
}

int Menu::RemoveWord()
{
	std::ifstream file(save, std::ios::in);  //open the file
	if (file)
	{
		std::string ligne;
		int num_ligne = 0;
		int Line_to_Erase = 0;
		ClearCons();
		std::cout << " ==================== BULL & COW ====================\n" << std::endl;
		std::cout << " ----------------------DELETES-----------------------\n" << std::endl;
		std::cout << " ---------------------- Liste -----------------------\n" << std::endl;
		while (getline(file, ligne))
		{
			++num_ligne;
			std::cout << "               " << num_ligne << ". " << ligne << std::endl;
		}
		std::cout << " --------------------- End Liste --------------------\n" << std::endl;
		std::cout << " Press the number from the word of your choice.\n" << std::endl;
		std::cin >> Line_to_Erase;
		
		if (Line_to_Erase != 0)
		{
			file.clear(); // clear/unset end of file flag
			file.seekg(0, std::ios::beg);// up on the begin of the file
			int num_lignebackup = Line_to_Erase - 1;

			// Initialisation table 	
			std::vector<FString> tab(num_ligne);

			for (int i = 0; i < num_ligne; i++)
			{
				file >> tab[i];
			}
			file.close();
			tab.erase(tab.begin() + num_lignebackup);
			int nbr_line = num_ligne - 1;
			std::ofstream file(save, std::ios::out | std::ios::trunc); // open the file
			file.clear(); // clear/unset end of file flag
			for (int i = 0; i < nbr_line -1; i++)
			{
				FString word = tab[i];
				file << word << std::endl;
			}
			file.close();
			std::cout << "You have remove the word "<< tab[num_lignebackup] << std::endl;
			}
		else {
			std::cout << " back \n" << std::endl;
		}
	}
	else //if open fail
	{
		std::cerr << "Open the File it's impossible !" << std::endl;
		std::cerr << "Make sure that Isogram.txt inside Bulls&Cows folder !" << std::endl;
	}
	system("PAUSE");
	return 0;
}

bool Menu::RemoveStats()
{
		std::cout << " Do you want remove the stats ? Y or N \n" << std::endl;
		std::string Response;
		std::cin >> Response;
		if ((Response == "y") || (Response == "Y")) {
			if (remove("../score.txt") != 0)
				perror("Error deleting file");
			else
				puts("File successfully deleted");
			std::ofstream outfile(score);
			outfile.close();
			std::cout << "You have remove the stat " << std::endl;
		}
		else {
			std::cout << "I have do nothing, don't worry\n" << std::endl;
		}
		
		return 0;
	
}

void Menu::ViewStats()
{
	{
		std::ifstream file(score, std::ios::in);  //open the file
		if (file)
		{
			FString ligne;
			int num_ligne = 0;
			ClearCons();
			std::cout << " ==================== BULL & COW ====================\n" << std::endl;
			std::cout << " ---------------------Last Score --------------------\n" << std::endl;
			
			while (getline(file, ligne, '|'))
			{// make a structure to get NamePlayer, Score , Word and after make a list with this information 
				++num_ligne;
				getline(file, ligne, '|');
				std::cout << num_ligne << " . " << ligne;
				getline(file, ligne, '|');
				std::cout <<  " as win with " << ligne;
				getline(file, ligne, '|');
				std::cout <<  " try with " << ligne;
				std::cout << " letters" << std::endl;
				
			}
			//file.clear(); // clear/unset end of file flag
				//file.seekg(0, std::ios::beg);// up on the begin of the file
		}
		else //if open fail
		{
			std::cerr << "Open the File it's impossible !" << std::endl;
			std::cerr << "Make sure that Isogram.txt inside Bulls&Cows folder !" << std::endl;
		}
		return;
	}

}

void Menu::color()
{
	int menu;
	FString back;
	FString letter;
	do {
		std::cout << " ==================== BULL & COW ====================\n" << std::endl;
		std::cout << " ---------------- Choose the color ------------------\n" << std::endl;
		std::cout << "               1. Blue" << std::endl;
		std::cout << "               2. Green" << std::endl;
		std::cout << "               3. Gray" << std::endl;
		std::cout << "               4. Red" << std::endl;
		std::cout << "               5. Violet" << std::endl;
		std::cout << "               6. Yellow" << std::endl;
		std::cout << "               7. Green" << std::endl;
		std::cout << "               8. Blue" << std::endl;
		std::cout << "               9. Salmon" << std::endl;	//Make your MixColor
		std::cout << "               0. Exit" << std::endl;
		std::cout << " \n\n" << std::endl;
		std::cout << "    Press the number of your choice and press Enter" << std::endl;
		std::cin >> menu;
		std::cout << std::endl;
		switch (menu)
		{
		case 0:

			break;
		case 1:
			system("Color 1A");
			break;
		case 2:
			system("Color 2B");
			break;
		case 3:
			system("Color 3C");
			break;
		case 4:
			system("Color 4D");
			break;
		case 5:
			system("Color 5E");
			break;
		case 6:
			system("Color 6F");
			break;
		case 7:
			system("Color A1");
			break;
		case 8:
			system("Color B2");
			break;
		case 9:
			/*
			std::cout << "Choose background color" << std::endl;
			std::cin >> back;
			std::cout << "Choose letter color" << std::endl;
			std::cin >> letter;
			system("Color *back* *letter*");
			*/
			system("Color C3");
			//system("Color D4");
			//system("Color E5");
			//system("Color F6");
			break;
		}
	} while (menu != 0);
	return;
}


//TODO function go to search the best score in the score file 
void Menu::TrackScore()
	{
		{
			
			std::ifstream file(score, std::ios::in);  //open the file
			if (file)
			{
				FString ligne = "";
				getline(file, ligne, '|');
				getline(file, ligne, '|');
				file.clear();
				file.seekg(0, std::ios::beg);
					if ((ligne != ""))
					{
						FString ligne;
						getline(file, ligne, '|');
						std::cout << " Best: ";
						getline(file, ligne, '|');
						std::cout << ligne << " guessed in ";
						getline(file, ligne, '|');
						std::cout << " tries a " << ligne;
						getline(file, ligne, '|');
						std::cout << " letter word \n";
						std::cout << "=============================================\n" << std::endl;
					}

					else //if open fail
					{
						std::cout << "You're going to write down your score " << std::endl;
						std::cout << "=============================================\n" << std::endl;
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





	
	//TODO Read the file, search the same word,
	//	Get the best score 
	//	Get the name of the guess
	//	Screen the score in game 


/*
int a = 0;
void Menu::Pointeur()
{	
	std::cout << "Contenu of my Variable: "<< a << std::endl;
	std::cout << "Adress of my Variable: " << &a << std::endl;
	std::cout << "\n" << std::endl;
	std::cout << "Choose the new valeur " << std::endl;
	std::cin >> a;
		return;
}
*/





