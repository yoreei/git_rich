// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"

#include "InGameUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE5TOPDOWNARPG_API UInGameUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UInGameUserWidget(const FObjectInitializer& ObjectInitializer);

	void NativeOnInitialized() override;

	///*Returns: False if error*/
	//UFUNCTION(BlueprintCallable, Category = "GitRich InGame Functions")
	//bool SetReward(int32 NewReward);

	UFUNCTION(BlueprintCallable, Category = "GitRich InGame UI Functions")
	bool ClearRewardBorders();
	
	UFUNCTION(BlueprintCallable, Category = "GitRich InGame UI Functions")
	bool DrawRewardBorder();

	UFUNCTION(BlueprintCallable, Category = "GitRich InGame UI Functions")
	UBorder* GetCurrentRewardBorder();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InGame UI")
	TObjectPtr<UBorder> CurrentRewardBorder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InGame UI")
	FLinearColor InactiveRewardBrushColor{ 1.f,1.f,1.f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InGame UI")
	FLinearColor ActiveRewardBrushColor{ 0.75f, 1.f, 0.f };
		
};
