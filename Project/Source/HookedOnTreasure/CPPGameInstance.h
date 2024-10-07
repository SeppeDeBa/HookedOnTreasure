// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CPPGameInstance.generated.h"
/**
 * 
 */
UCLASS()
class HOOKEDONTREASURE_API UCPPGameInstance : public UGameInstance
{
	GENERATED_BODY()
	//int m_Level0Medal = 0, m_Level1Medal = 0, m_Level2Medal = 0, m_Level3Medal = 0;
	UPROPERTY(EditAnywhere)	
	int m_LevelMedals[5]{4,0,0,0,0};
	
public:
	int GetAchievedMedalFromLevel(int levelInt) const
	{
		return m_LevelMedals[levelInt];		
#pragma region old
		//keeping old method as backup
		// switch (levelInt) //wanted to use an enum, but the MedalEnum has disappeared from my content browser, as has an older enum, switching to integers as backup
		// {
		// case 0:
		// 	return m_Level0Medal;
		// case 1:
		// 	return m_Level1Medal;
		// case 2:
		// 	return m_Level2Medal;
		// case 3:
		// 	return m_Level3Medal;

		//	default:
			//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::White, "Default hit on check medal in instance");
			//return 5;
		//}
#pragma endregion
	}
	
	bool MedalGotten(int medalAchieved, int levelInt)
	{
		if (medalAchieved > m_LevelMedals[levelInt])
		{
			if(GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::White, "Congratulations! You've upgraded your medal to: ");
			switch(medalAchieved)
			{
			case 1:
				if(GEngine)
					GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Black, "Bronze");
			break;
			case 2:
				if(GEngine)
					GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Cyan, "!Silver!");
				break;
			case 3:
				if(GEngine)
					GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, "!!Gold!!");
				break;
			default:
				break;
			}
			m_LevelMedals[levelInt] = medalAchieved;
			return true;
		}
		return false;
	}
};
