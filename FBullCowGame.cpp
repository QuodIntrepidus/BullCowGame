#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); } // default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,5}, {4,7}, {5,7}, {6,10}, {7,10} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "blame";
	
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}
// recieves a valid guess and increments turn and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); //assuming the same length as guess
	
	//loop through all the letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)					//MHWChar = My Hidden Word Character
	{
		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++)					//GChar = Guess word character
		{
			// if they match
			if (Guess[GChar] == MyHiddenWord[MHWChar]) 
			{ 
				if (MHWChar == GChar) //if they're in the same place
				{ 
					BullCowCount.Bulls++; //increment bulls 
				}
				else 
				{
					BullCowCount.Cows++; //must be a cow
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess)  const
{
	if (!IsIsogram(Guess)) //if the guess isn't an isogram 
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess)) //if the guess isn't all lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) //if the guess length is wrong
	{
		return EGuessStatus::Wrong_length;
	}
	else //otherwise
	{
		return EGuessStatus::OK;
	}

}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isogram
	if (Word.length() <= 1)
	{
		return true;
	}

	TMap<char, bool> LetterSeen; // set our map
	for (auto Letter : Word)   // for all letters of the word
	{
		Letter = tolower(Letter);                              // changes all letters to lowercase // handle mixed case
		if (LetterSeen[Letter]) { return false; }              // if the letter is in the map  // we do NOT have an isogram
		else { LetterSeen[Letter] = true; }		               // otherwise // add the letter to the map as seen
	}
	return true; // for example in cases where /0 is entered
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))                                 // if not a lowercase letter
		{
			return false;                                     // return false
		}
	}
	return true;
}
