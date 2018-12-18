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
				//SelectWord();
				break;
			case 2:
				AddNewWord();
				break;
			case 3:std::cout << " " << std::endl;
				break;
			}
	} while (menu != 0);
}

int Menu::AddNewWord()
{

std::string word;
std::string confirm;
	std::ofstream file("../save.txt", std::ios::out | std::ios::app); // open the file

	std::cout << " Enter your new word to add in the list " << std::endl;
	std::cin >> word;
	
	if (std::getline(std::cin, confirm))
	{
		file << word << std::endl;
		file.close();
		std::cout << " \" " << word << " \" "<< " It's add in the list\n\n" << std::endl;
	}
	else
		std::cerr << "Open the file it's impossible or write something!" << std::endl;
	return 0;
}



int number = 0;
;
int Menu::ChooseNewWord() // TODO make a way to put content in the HIDDEN_WORD from FBullCowGame.cpp
{
	std::ifstream file("../Isograms.txt", std::ios::in);  //open the file
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
		file.seekg(0, std::ios::beg);
		int num_lignebackup = num_ligne + 1;

		// Initialisation table 	
		std::vector<FString> tab(num_ligne);
		std::vector<FString> tabbackup(num_lignebackup);

		for (int i = 0; i < num_ligne; i++)
		{
			file >> tab[i];
			std::cout << tab[i] << std::endl;
		}
		std::cout << "\nfin tab \n"  << std::endl;
		file.close();

		int wordselect = id - 1;
		for (int i = 0; i < wordselect; i++) {
			int j = i + 1;
			tabbackup[j] = tab[i];
			std::cout << "." << tabbackup[j] << std::endl;
		}
		std::cout << "\nfin first half\n" << std::endl;

		for (int i = id; i <num_ligne; i++){
			int j = i + 1;
			tabbackup[j] = tab[i];
			std::cout << "." << tabbackup[j] << std::endl;
		}
		std::cout << "\nfin second half\n" << std::endl;
		tabbackup[0] = tab[wordselect];

		
		std::cout <<"\n you are select "<< tab[wordselect] << " in "<< id << " position.\n" << std::endl;
		

			for (int i = 0; i < num_ligne; i++)
			{
				std::cout <<"." << tabbackup[i] << std::endl;
			}
		//TODO register the tabbackup table in the file isogram but erase all before
		
	/*		FILE * pFile;
			char buffer[] = { 'x' , 'y' , 'z' };
			pFile = fopen(".. / tables.txt", "wb");
			fwrite(buffer, sizeof(char), sizeof(buffer), pFile);
			fclose(pFile);
			return 0;
	*/		
	/*
			FILE *file;
				int i;

				file = fopen(".. / tables.txt", "wb");
				if (!file) {
					return EXIT_FAILURE;
				}

				fwrite(tab, sizeof FString, sizeof *tab, file);
				fclose(file);

				memset(&tab, 0, sizeof FString);
				file = fopen("tableau.txt", "rb");

				if (!file) {
					return EXIT_FAILURE;
				}

				fread(tab, sizeof FString, sizeof *tab, file);
				fclose(file);

				for (i = 0; i < 10; i++) {
					printf("%d\n", tab[i]);
				}

				return EXIT_SUCCESS;
			}

	*/
				

		system("PAUSE");
		
		//return EXIT_SUCCESS;
	}
	else //if open fail
	{
		std::cerr << "Open the File it's impossible !" << std::endl;
		std::cerr << "Make sure that Isogram.txt inside Bulls&Cows folder !" << std::endl;
	}
	//SelectWord();
	system("PAUSE");
	return 0;
}












void Menu::SelectWord()
{
	int menu;
	int word;
	do 
	{
		//TODO create a table with the content of my list isogram with the number in ID 
		/*
		std::ifstream file("../Isograms.txt");
		std:: a <int> b (
			std::istream_iterator<int>(file),
			std::istream_iterator<int>{});
		*/
		
		//TODO table of 10 word
		//TODO insert world in the cases of the table
		 

		std::cout << "Select the number to put the word in the list" << std::endl;
		std::cout << "There are " << number << " words in the list" << std::endl;
		std::cin >> menu;
		std::cout << std::endl;
		switch (menu)
		{
		case 1:
			std::cout << "you select 1" << std::endl;
			//TODO take case one of the table (index 0)
			//TODO insert the value on the first place in the list
			std::cin >> word;
			break;
		case 2:
			std::cout << "you select 2" << std::endl;
			//TODO take case 2
			break;
		case 3:
			std::cout << "you select 3" << std::endl;
			break;
		case 4:
			std::cout << "you select 4" << std::endl;
			break;
		case 5:
			std::cout << "you select 5" << std::endl;
			break;
		case 6:
			std::cout << "you select 6" << std::endl;
			break;
		}
	} while (menu != 0);
	//NOTE how to generate case if there is more word automaticly ? 
	//NOTE Generat a struture that take in parameter the number of the word in the list, 
	//from the table, that struture is a boucle with a case that insert the word in the "hidden" variable 

}





void Menu::ClearCons()
{
	std::system("cls");
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





