// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"


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
        if (Input == HiddenWord) {  // Input is whatever the user typed and then hit return
            PrintLine("Congratulation! Your guess is correct!\n");
            RestartGame();
        } else if (Input != HiddenWord) {
            --LifeCounts;
            if (LifeCounts <= 0) {
                LifeCounts = 0;
                PrintLine(TEXT("Game Over! The answer is '%s'. \n"), *HiddenWord);
                RestartGame();
            } else {
                PrintLine("Your guess is incorrect");
                PrintLine(TEXT("You have %i lifes left. Try again ..."), LifeCounts);
            }
        }
    } else {
        InitGame();
    }
}


void UBullCowCartridge::InitGame() {
    /*
    Helper function that initialize the bull cow game
    */
    HiddenWord = TEXT("cake");
    LifeCounts = 3;
    bGameOver = false;
    PrintLine(TEXT("Hi There, welcome to the Bull Cows!"));
    PrintLine(TEXT("Input the %i letter word,\nand press enter to continue ..."), HiddenWord.Len());
}


void UBullCowCartridge::RestartGame() {
    /*
    Helper function that prompts the user to restart the game
    */
    bGameOver = true;
    PrintLine(TEXT("Hit 'Enter' to restart the game..."));
}