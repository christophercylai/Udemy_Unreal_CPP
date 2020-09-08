// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"


void UBullCowCartridge::BeginPlay()
{
    /*
    When the game starts
    */
    Super::BeginPlay();
    InitGame();
}


void UBullCowCartridge::OnInput(const FString& Input)
{
    /*
    When the player hits enter
    */
    ClearScreen();
    if (! bGameOver) {
        ProcessGame(Input);
    } else {
        InitGame();
    }
}


void UBullCowCartridge::InitGame() {
    /*
    Helper function that initialize the bull cow game
    */
    HiddenWord = ListOfWords[rand() % ListOfWords.Num()];
    bGameOver = false;
    LifeCounts = 3;
    PrintLine(TEXT("Hi There, welcome to the Bull Cows!"));
    PrintLine(TEXT("Input the %i letter word,\nand press enter to continue ..."), HiddenWord.Len());
}


bool UBullCowCartridge::IsIsogram(const FString Guess) const {
    /*
    Helper function: Prevents the player to enter a word that has duplicated letters
    */
    // Looping through 'Guess' in reverse order and compare each character against
    // others characters that have lesser position values
    for (int32 full_len = Guess.Len()-1; full_len >= 1; --full_len) {  // full_len >= 1: not checking the last char
        for (int32 part_len = full_len-1; part_len >= 0; --part_len) {
            if (Guess[full_len] == Guess[part_len]) {
                PrintLine(TEXT("'%s' has duplicate letters '%c'."), *Guess, Guess[part_len]);
                PrintLine(TEXT("The word cannot have duplicate letters."));
                return false;
            }
        }
    }
    return true;
}


void UBullCowCartridge::ProcessGame(const FString Guess) {
    if (Guess == HiddenWord) {  // Input is whatever the user typed and then hit return
        PrintLine(TEXT("Congratulation! Your guess is correct!\n"));
        RestartGame();
        return;
    }
    // Prevents the player to enter a word that is longer then 'HiddenWord'
    if (Guess.Len() != HiddenWord.Len()) {  // Input is whatever the user typed and then hit return
        PrintLine(TEXT("'%s' has %i letters.\nThe number of letters should be %i."), *Guess, Guess.Len(), HiddenWord.Len());
        goto EXIT;
    }
    if (! IsIsogram(Guess)) {
        goto EXIT;
    }
    --LifeCounts;
    PrintLine(TEXT("Your guess '%s' is incorrect."), *Guess);
    if (LifeCounts <= 0) {
        LifeCounts = 0;
        PrintLine(TEXT("Game Over! The answer is '%s'. \n"), *HiddenWord);
        RestartGame();
        return;
    }
    EXIT:
    PrintLine(TEXT("You have %i lifes left. Try again ..."), LifeCounts);
}


void UBullCowCartridge::RestartGame() {
    /*
    Helper function that prompts the user to restart the game
    */
    bGameOver = true;
    PrintLine(TEXT("Hit 'Enter' to restart the game ..."));
}