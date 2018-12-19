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

int number = 0;

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
				AddNewWord();
				break;
			case 3:std::cout << " " << std::endl;
				RemoveWord();
				break;
			}
	} while (menu != 0);
}

int Menu::AddNewWord()
{

std::string word;
std::string confirm;
	std::ofstream file("../save.txt", std::ios::out | std::ios::app); // open the file

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
	std::ifstream file("../save.txt", std::ios::in);  //open the file
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

		

			std::ofstream file("../save.txt", std::ios::out | std::ios::trunc); // open the file
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
	std::ifstream file("../save.txt", std::ios::in);  //open the file
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
		std::ofstream file("../save.txt", std::ios::out | std::ios::trunc); // open the file
		file.clear(); // clear/unset end of file flag
		for (int i = 0; i < nbr_line -1; i++)
		{
			FString word = tab[i];
			file << word << std::endl;
		}

		file.close();


		/*
		
			for (int i = 0; i < num_ligne; i++)
			{
				

				if (Line_to_Erase == i)
				{
					std::cout << " do nothing" << std::endl;
				}
				else {
					file >> tab[i];
				}
			}
			tab.erase(tab.begin() + id);
		
		file.close();


		

*/








	}
	else //if open fail
	{
		std::cerr << "Open the File it's impossible !" << std::endl;
		std::cerr << "Make sure that Isogram.txt inside Bulls&Cows folder !" << std::endl;
	}

	system("PAUSE");
	return 0;
}

/*void Erase_Line(char* file, int Line_to_Erase)
{
	std::string Buffer = ""; //Variable contenant le texte à réécrire dans le fichier
	std::ifstream ReadFile(file);
	if (ReadFile) //Si le fichier est trouvé
	{
		std::string line;
		int Line = 0;
		while (std::getline(ReadFile, line)) //on parcours le fichier et on initialise line à la ligne actuelle
		{
			Line++;
			if (Line != Line_to_Erase) //Si la ligne atteinte est différente de la ligne à supprimer...
				Buffer += line + "\n"; //On ajoute le contenu de la ligne dans le contenu à réécrire
		}
	}
	ReadFile.close(); //On ferme le fichier en lecture

	std::ofstream WriteFile(File); //On ouvre ce même fichier en écriture
	WriteFile << Buffer; //On écris le texte dedans
	WriteFile.close(); //et on ferme le fichier
}*/





void Menu::ViewStats()
{
	{
		std::ifstream file("../stat.txt", std::ios::in);  //open the file
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


//NOTE if you lunch the game, you can cheat if you look the word before


