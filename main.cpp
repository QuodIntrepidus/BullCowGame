/*This is the console executable, that makes use of the BullCow class
This acts as a view in a MVC pattern, and it is responsible for all user interaction.
For game logic see the FBullCowGame class
*/
#pragma once


#include <iostream>
#include <string>
#include "FBullCowGame.h"

using int32 = int;             //makes the syntax Unreal friendly
using FText = std::string;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
void PrintGameSummary();
bool AskToPlayAgain();

FBullCowGame BCGame; // instantiate a new game

//entry point of our application
int main()
{
	bool bPlayAgain = false;
	do 
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} 
	while (bPlayAgain);
	return 0;
	//exit game
}


void PrintIntro() {
	//introduction
	std::cout << "\n\nWelcome To Bulls and Cows Game, a fun word guessing game!\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n\n";
	std::cout << "Instructions: \n";
	std::cout << "Enter a " << BCGame.GetHiddenWordLength() << " - lettered word\n";
	std::cout << "Enter in lowercase\n";
	std::cout << "The word you enter should be an Isogram i.e. a word without repeating letters. Example: climb, short etc.\n";
	std::cout << "Bulls is the no. of correctly guessed letters in the correct place\n";
	std::cout << "Cows is the no. of correctly guessed letters in the wrong place\n";
	std::cout << "You have a total of " << BCGame.GetMaxTries() << " tries to guess the Isogram I'm thinking of!\n";
}


void PlayGame()  
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses while the game is NOT won
	// and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();  

		//Submit valid guess to the game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();
	return;
} 


//loop continually until a user gives a valid guess
FText GetValidGuess() 
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do
	{
		//asking for a word
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "\n";
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter an Isogram(word without repeating letters).\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all the letters in lowercase.\n";
			break;
		default: //assuming the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); //keep looping till we get no errors
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same word? (y/n)";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}
void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Wow you guessed my word! You WIN\n\n";
	}
	else
	{
		std::cout << "Better luck next time!\n\n";
	}
}