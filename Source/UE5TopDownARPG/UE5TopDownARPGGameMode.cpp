// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE5TopDownARPGGameMode.h"
#include "UE5TopDownARPGPlayerController.h"
#include "UE5TopDownARPGCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "UE5TopDownARPG.h"

AUE5TopDownARPGGameMode::AUE5TopDownARPGGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AUE5TopDownARPGPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
	
	// Get Questions
	ConstructorHelpers::FObjectFinder<UDataTable> DataTableObject(TEXT("/Game/TopDown/Questions.Questions"));
	if (DataTableObject.Succeeded())
	{
		QuestionDataTable = DataTableObject.Object;
		FQuestionData* Row = QuestionDataTable->FindRow<FQuestionData>("NewRow", "what's this?");
		ensure(Row);
		if (Row)
		{

		}
		else
		{
			UE_LOG(LogUE5TopDownARPG, Log, TEXT("UUIWidget could not load Row"));
		}

	}
	else
	{
		UE_LOG(LogUE5TopDownARPG, Log, TEXT("UUIWidget could not load Questions data table"));
	}

}

void AUE5TopDownARPGGameMode::EndGame(bool IsWin)
{
	if (IsWin)
	{
		UE_LOG(LogUE5TopDownARPG, Log, TEXT("Win"));
	}
	else
	{
		UE_LOG(LogUE5TopDownARPG, Log, TEXT("Lose"));
	}
}


void AUE5TopDownARPGGameMode::UIWidgetAnswer(int Answer)
{
	UE_LOG(LogUE5TopDownARPG, Log, TEXT("You have answered: %d"), Answer); 
	FQuestionData* Row = QuestionDataTable->FindRow<FQuestionData>("1", "what's this?");
	ensure(Row);
}

void AUE5TopDownARPGGameMode::GetRandQuestion(int QuestionLevel, FQuestionData& QuestionData)
{
	TArray<FQuestionData*> AllLevelQuestions{};

	QuestionDataTable->ForeachRow<FQuestionData>(TEXT("ContextString"), [&](const FName& Key, const FQuestionData& Value)
		{
			if (Value.QuestionLevel == QuestionLevel)
			{
				AllLevelQuestions.Add(const_cast<FQuestionData*>(&Value));
			}
		});

	if (AllLevelQuestions.Num() <= 0)
	{
		UE_LOG(LogUE5TopDownARPG, Log, TEXT("Couldn't find any questions"));
		return;
	}
	int64 RandIdx = AllLevelQuestions.Num() % (FMath::RandRange(0, 99999));
	UE_LOG(LogUE5TopDownARPG, Log, TEXT("%d of %d"), RandIdx, AllLevelQuestions.Num());
	QuestionData = *AllLevelQuestions[RandIdx];
	//ensure(Row);
}