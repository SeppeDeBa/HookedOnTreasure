// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Logging/LogMacros.h"
#include "Components/SceneComponent.h"
#include "CPPGameInstance.h"
#include "GameFramework/Character.h" //has to be added to know that MyChar can be casted to AActor
#include "LevelChanger.generated.h"

UCLASS()
class HOOKEDONTREASURE_API ALevelChanger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelChanger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	UPROPERTY(EditAnywhere, Category = "LC_LevelData")//ADDING ZZ TO EASILY SEARCH FOR IT IN BROWSER
	FName LevelToLoad;

	
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	// UPROPERTY(EditAnywhere, Category = "LC_Level Data")
	// int m_isInHub;
	UPROPERTY(EditAnywhere, Category = "LC_Level Data")
	int m_levelIntComingFrom;
	UPROPERTY(EditAnywhere, Category = "LC_Level Data")
	int m_levelIntGoingTo;

	//medal times
	UPROPERTY(EditAnywhere, Category = "LC_Medal Times")
	float m_BronzeTime;
	UPROPERTY(EditAnywhere, Category = "LC_Medal Times")
	float m_SilverTime;
	UPROPERTY(EditAnywhere, Category = "LC_Medal Times")
	float m_GoldTime;
	
	//main mesh
	UPROPERTY(VisibleAnywhere, Category = "LC_Mesh")
	UStaticMeshComponent* m_Mesh;

	//coll box
	UPROPERTY(EditAnywhere, Category = "LC_Box Collision")
	int m_CollisionBoxSize = 55;
	UPROPERTY(EditAnywhere, Category = "LC_Box Collision")
	UBoxComponent* m_BoxCollisionMesh = nullptr;
	
	
	//possible materials --> UMaterialInterface gives both material and instance
	UPROPERTY(EditAnywhere, Category = "LC_Materials")
	UMaterialInterface* m_Mat_Uncleared;
	UPROPERTY(EditAnywhere, Category = "LC_Materials")
	UMaterialInterface* m_Mat_Bronze;
	UPROPERTY(EditAnywhere, Category = "LC_Materials")
	UMaterialInterface* m_Mat_Silver;
	UPROPERTY(EditAnywhere, Category = "LC_Materials")
	UMaterialInterface* m_Mat_Gold;
	
	
	//helper functions
	void Mf_CheckAndSetMaterial(); //set material on startup
	int CheckMedalGotten() const; //check medal gotten on close 
	
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult); //gotten from ue documentation: https://docs.unrealengine.com/5.0/en-US/loading-and-unloading-levels-using-cplusplus-in-unreal-engine/

	
};
