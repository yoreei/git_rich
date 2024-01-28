// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Containers/Set.h"

#include "UE5TopDownARPGGameMode.generated.h"


UENUM(BlueprintType)
enum class EGameState : uint8 {
    GameStart = 0,
    AskingQuestion,
    AnswerSuspense,
    AnswerReveal,
    AnsweredCorrectly,
    AnsweredWrong,
    Win,
    Lose,
    CustomCat1,
    CustomCat2,
};

/** Structure that defines a level up table entry */
USTRUCT(BlueprintType)
struct FQuestionData : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

public:

    FQuestionData()
        : QuestionId(0)
        , QuestionLevel(1)
        , QuestionText("Question Text")
        , Answer1("Answer 1 Text")
        , isAnswer1Correct(false)
        , Answer2("Answer 2 Text")
        , isAnswer2Correct(false)
        , Answer3("Answer 3 Text")
        , isAnswer3Correct(false)
        , Answer4("Answer 4 Text")
        , isAnswer4Correct(false)
    {}

    /** Unique Id */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
    int32 QuestionId;

    /** Expected Level range: [1 .. 3] */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
    int32 QuestionLevel;

    /** Player sees this */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
    FString QuestionText;

    /** Is this answer correct */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
    FString Answer1;

    /** Player sees this */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
    bool isAnswer1Correct;

    /** Player sees this */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
    FString Answer2;

    /** Player sees this */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
    bool isAnswer2Correct;

    /** Player sees this */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
    FString Answer3;

    /** Player sees this */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
    bool isAnswer3Correct;

    /** Player sees this */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
    FString Answer4;

    /** Player sees this */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
    bool isAnswer4Correct;
};

UCLASS(minimalapi)
class AUE5TopDownARPGGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AUE5TopDownARPGGameMode();

	void EndGame(bool IsWin);

    /*
    4 >= Answer >= 1
    */
    //UFUNCTION(BlueprintCallable, Category = "GitRich Functions")
    //void UIWidgetAnswer(int Answer);

    /*
    Get Random Question
    */
    UFUNCTION(BlueprintCallable, Category = "GitRich Functions")
    void GetRandQuestion(int QuestionLevel, FQuestionData& QuestionData);

    UFUNCTION(BlueprintCallable, Category = "GitRich Functions")
    void ResetShownQuestions();

    /*Set New Curren*/
    UFUNCTION(BlueprintCallable, Category = "GitRich Functions")
    bool SetReward(int32 NewReward);

    /*Returns: False if error*/
    UFUNCTION(BlueprintCallable, Category = "GitRich Functions")
    bool IncrementReward();

    /*
    CrowdCheer
    CrowdGasp
    Heartbeat_Fast
    Heartbeat_Medium
    Heartbeat_Slow
    MenuAndIntro_Loop
    MenuAndIntro_Start
    */
    UFUNCTION(BlueprintCallable, Category = "GitRich Functions")
    void PlaySound(const FString& AudioName) const;

    UFUNCTION(BlueprintCallable, Category = "GitRich Functions")
    void SetGameState(EGameState _GameState);

public:
    using QuestionKVPair = TTuple<const FName&, const FQuestionData&>;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = QuestionTable)
    UDataTable* QuestionDataTable;

    /* Keys of questions already answered */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GitRichVariables)
    TSet<FName> ShownIds{};

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GitRichVariables)
    int32 MaxReward = 10;

    UPROPERTY(BlueprintReadOnly, Category = GitRichVariables)
    int32 CurrentReward = 0;

    UPROPERTY()
    EGameState CurrentGameState;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GitRichVariables)
    TArray<FString> GameStartSounds;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GitRichVariables)
    TArray<FString> AskingQuestionSounds;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GitRichVariables)
    TArray<FString> AnswerSuspenseSounds;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GitRichVariables)
    TArray<FString> AnswerRevealSounds;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GitRichVariables)
    TArray<FString> AnsweredCorrectlySounds;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GitRichVariables)
    TArray<FString> AnsweredWrongSounds;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GitRichVariables)
    TArray<FString> WinSounds;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GitRichVariables)
    TArray<FString> LoseSounds;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GitRichVariables)
    TArray<FString> CustomCatSounds1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GitRichVariables)
    TArray<FString> CustomCatSounds2;

    TArray<TArray<FString>*> Sounds{
        &GameStartSounds,
        &AskingQuestionSounds,
        &AnswerSuspenseSounds,
        &AnswerRevealSounds,
        & AnsweredCorrectlySounds,
        & AnsweredWrongSounds,
        & WinSounds,
        & LoseSounds,
        & CustomCatSounds1,
        & CustomCatSounds2,
    };
};