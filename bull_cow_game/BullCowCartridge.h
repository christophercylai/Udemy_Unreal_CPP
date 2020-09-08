// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;
	void InitGame();
	void RestartGame();
	// TODO: make 'Guess' a smart pointer
	void ProcessGame(const FString Guess);
	bool IsIsogram(const FString Guess) const;
	void GetValidWords();

	// Your declarations go below!
	private:
    FString HiddenWord = TEXT("");
	int32 LifeCounts = 0;
	bool bGameOver = false;
	TArray<FString> ValidWords = {};
};
