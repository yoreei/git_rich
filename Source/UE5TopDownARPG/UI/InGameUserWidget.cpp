// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameUserWidget.h"
#include "Components/Border.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetTree.h"

#include "../UE5TopDownARPGCharacter.h"
#include <UE5TopDownARPG/UE5TopDownARPGGameMode.h>
#include <UE5TopDownARPG/UE5TopDownARPG.h>


UInGameUserWidget::UInGameUserWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}

void UInGameUserWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
}

//bool UInGameUserWidget::SetReward(int32 NewReward)
//{
//    AUE5TopDownARPGGameMode* GameMode = Cast<AUE5TopDownARPGGameMode>(GetWorld()->GetAuthGameMode());
//    if (GameMode == nullptr)
//    {
//        ensure(false);
//        return false;
//    }
//
//    GameMode->SetReward(NewReward);
//    UpdateCurrentRewardBorder();
//    return true;
//}

bool UInGameUserWidget::ClearRewardBorders()
{
    if (WidgetTree == nullptr)
    {
        UE_LOG(LogUE5TopDownARPG, Error, TEXT("C++: WidgetTree is nullptr"));
        ensure(false);
        return false;
    }

    TArray<UWidget*> Widgets;
    WidgetTree->GetAllWidgets(Widgets);

    for (UWidget* Widget : Widgets)
    {
        if (Widget->GetName().Contains("Reward "))
        {
            UBorder* Border = Cast<UBorder>(Widget);
            if (Border == nullptr)
            {
                UE_LOG(LogUE5TopDownARPG, Error, TEXT("C++: coundlt cast border"));
                continue;
            }
            Border->SetBrushColor(InactiveRewardBrushColor);
        }
    }
    return true;
}

bool UInGameUserWidget::DrawRewardBorder()
{
    UBorder* Border = GetCurrentRewardBorder();
    if (Border == nullptr)
    {
        UE_LOG(LogUE5TopDownARPG, Error, TEXT("C++: no CurrentRewardBorder"));
        return false;
    }
    Border->SetBrushColor(ActiveRewardBrushColor);
    return true;
}

//bool UInGameUserWidget::GetCurrentRewardBorder()
//{
//    AUE5TopDownARPGGameMode* GameMode = Cast<AUE5TopDownARPGGameMode>(GetWorld()->GetAuthGameMode());
//    if (GameMode == nullptr)
//    {
//        return false;
//    }
//    FName Name = "Reward " + GameMode->CurrentReward;
//    UBorder* Border = WidgetTree->FindWidget<UBorder>(Name);
//    if (Border == nullptr)
//    {
//        UE_LOG(LogUE5TopDownARPG, Error, TEXT("C++: no such border"));
//        return false;
//    }
//
//    CurrentRewardBorder = Border;
//    return true;
//}

UBorder* UInGameUserWidget::GetCurrentRewardBorder()
{
    AUE5TopDownARPGGameMode* GameMode = Cast<AUE5TopDownARPGGameMode>(GetWorld()->GetAuthGameMode());
    if (GameMode == nullptr)
    {
        return nullptr;
    }
    FName Name = "Reward " + GameMode->CurrentReward;
    UBorder* Border = WidgetTree->FindWidget<UBorder>(Name);
    if (Border == nullptr)
    {
        UE_LOG(LogUE5TopDownARPG, Error, TEXT("C++: no such border"));
        return nullptr;
    }

    CurrentRewardBorder = Border;
    return Border;
}