// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE5TopDownARPGGameMode.h"
#include "UE5TopDownARPGPlayerController.h"
#include "UE5TopDownARPGCharacter.h"
#include "UE5TopDownARPG.h"

#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "CoreMinimal.h"
#include "Containers/Map.h"

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

void AUE5TopDownARPGGameMode::GetRandQuestion(int QuestionLevel, FQuestionData& QuestionData)
{
	if (QuestionLevel <= 0)
	{
		UE_LOG(LogUE5TopDownARPG, Warning, TEXT("C++: QuestionLevel must be >= 0"));
		return;
	}

	TArray<QuestionKVPair> AllLevelQuestions{};

	QuestionDataTable->ForeachRow<FQuestionData>(TEXT("ContextString"), [&](const FName& Key, const FQuestionData& Value)
		{
			if (Value.QuestionLevel == QuestionLevel && !ShownIds.Contains(Key))
			{
				QuestionKVPair Pair(Key, Value);
				AllLevelQuestions.Add(Pair);
			}
		});

	if (AllLevelQuestions.Num() <= 0)
	{
		UE_LOG(LogUE5TopDownARPG, Warning, TEXT("C++: Couldn't find any questions"));
		return;
	}
	int64 RandIdx = FMath::RandRange(0, 99999) % AllLevelQuestions.Num();
	QuestionKVPair Pair = AllLevelQuestions[RandIdx];
	FName Name = Pair.Get<0>();
	ShownIds.Add(Name);
	QuestionData = Pair.Get<1>(); // OUT

	UE_LOG(LogUE5TopDownARPG, Log, TEXT("C++: Found %d viable questions, returning one with Unique Name: %s"), AllLevelQuestions.Num(), *Name.ToString());
}

void AUE5TopDownARPGGameMode::ResetShownQuestions()
{
	ShownIds = TSet<FName>();
	UE_LOG(LogUE5TopDownARPG, Log, TEXT("C++: ShownIds.Num(): %d"), ShownIds.Num());
}

bool AUE5TopDownARPGGameMode::SetReward(int32 NewReward)
{
	if (NewReward > MaxReward)
	{
		UE_LOG(LogUE5TopDownARPG, Error, TEXT("C++: NewReward > MaxReward: (%d > %d)"), NewReward, MaxReward);
		return false;
	}
	CurrentReward = NewReward;
	return true;
}

bool AUE5TopDownARPGGameMode::IncrementReward()
{
	return SetReward(CurrentReward + 1);
}

void AUE5TopDownARPGGameMode::PlaySound(const FString& AudioName) const
{
	UWorld* World = GetWorld();
	FString SoundString = TEXT("/Script/Engine.SoundWave'/Game/AudioDesign/" + AudioName + "." + AudioName + "'");
	auto Obj = StaticLoadObject(USoundBase::StaticClass(), nullptr, *SoundString);
	USoundBase* Sound = Cast<USoundBase>(Obj);
	UGameplayStatics::PlaySound2D
	(
		World,
		Sound,
		1.f,
		1.f,
		0.f,
		nullptr,
		nullptr,
		true
	);
}

void AUE5TopDownARPGGameMode::SetGameState(EGameState NewGameState)
{
	CurrentGameState = NewGameState;
	TArray<FString>* StateSounds = Sounds[static_cast<uint8>(CurrentGameState)];
	if (StateSounds == nullptr)
	{
		UE_LOG(LogUE5TopDownARPG, Warning, TEXT("C++: Could not find sounds array for state: %d"), CurrentGameState);
		return;
	}

	for (FString& SoundStr : *StateSounds)
	{
		PlaySound(SoundStr);
	}
}

