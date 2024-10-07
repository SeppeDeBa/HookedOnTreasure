// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelChanger.h"
//#include "Blueprint/UserWidget.h"
#include "Misc/OutputDeviceNull.h"
#include "UObject/FastReferenceCollector.h"
//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::White, String)
// Sets default values
ALevelChanger::ALevelChanger()
{
 	//1. Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true; 

	
	//2. init main mesh
	m_Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = m_Mesh;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshAsset(TEXT("/Engine/BasicShapes/Cube"));
	if (!CubeMeshAsset.Succeeded())
	{
		UE_LOG(LogTemp, Error, TEXT("Game CPP instance does not exist"));
	}
	else
	{
		m_Mesh->SetStaticMesh(CubeMeshAsset.Object);
    }
	
	//3. init collision box
	m_BoxCollisionMesh = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Mesh"));
	m_BoxCollisionMesh->InitBoxExtent(FVector(m_CollisionBoxSize,m_CollisionBoxSize,m_CollisionBoxSize)); //https://docs.unrealengine.com/4.26/en-US/API/Runtime/Engine/Components/UBoxComponent/InitBoxExtent/
	m_BoxCollisionMesh->SetCollisionProfileName("Trigger");
	m_BoxCollisionMesh->SetupAttachment(m_Mesh);
	
	
	//did not work :<
	// ConstructorHelpers::FObjectFinder<UMaterialInterface> unclearedMatFinder(TEXT("/Game/Materials/Emissives/MI_Uncleared"));
	// ConstructorHelpers::FObjectFinder<UMaterial> unclearedMatFinder(TEXT("/Game/Materials/Emissives/MI_Bronze"));
	// ConstructorHelpers::FObjectFinder<UMaterial> unclearedMatFinder(TEXT("/Game/Materials/Emissives/MI_Silver"));
	// ConstructorHelpers::FObjectFinder<UMaterial> unclearedMatFinder(TEXT("/Game/Materials/Emissives/MI_Gold"));


	//4. assign materials, automatic did not work so manual
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> UnclearedMaterialFinder(TEXT("/Content/Materials/Emissives/MI_Uncleared"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> BronzeMaterialFinder(TEXT("/Content/Materials/Emissives/MI_Bronze"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> SilverMaterialFinder(TEXT("/Content/Materials/Emissives/MI_Silver"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> GoldMaterialFinder(TEXT("/Content/Materials/Emissives/MI_Gold"));
	m_Mat_Uncleared = UnclearedMaterialFinder.Object;
	m_Mat_Bronze = BronzeMaterialFinder.Object;
	m_Mat_Silver= SilverMaterialFinder.Object;
	m_Mat_Gold = GoldMaterialFinder.Object;



	
	// m_Mat_Uncleared = CreateDefaultSubobject<UMaterialInterface>("Mat_Uncleared");
	// m_Mat_Bronze = CreateDefaultSubobject<UMaterialInterface>("Mat_Bronze");
	// m_Mat_Silver= CreateDefaultSubobject<UMaterialInterface>("Mat_Silver");
	// m_Mat_Gold = CreateDefaultSubobject<UMaterialInterface>("Mat_Gold");
	
	
	//5.add the On Overlap
	m_BoxCollisionMesh->OnComponentBeginOverlap.AddDynamic(this, &ALevelChanger::OnOverlapBegin);
	
	//todo if choice is made for portfolio:
	//make own hud, use function in there to change the hud, so so close, but in the wrong direction...
	
	// TSubclassOf<UUserWidget> HUDWidgetClass;
	// if (HUDWidgetClass)
	// {
	// 	UUserWidget* HUDWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
	//
	// 	if (HUDWidget)
	// 	{
	// 		const FString command = FString::Printf(TEXT("SetMedalTimes %f %f %f"), m_BronzeTime, m_SilverTime, m_GoldTime);
	// 		FOutputDeviceNull ar;			
	// 		HUDWidget->CallFunctionByNameWithArguments(*command, ar, NULL, true);
	// 	}
	// }
}



// Called when the game starts or when spawned
void ALevelChanger::BeginPlay()
{
	Super::BeginPlay();
	;
	DrawDebugBox(GetWorld(), GetActorLocation(),FVector(m_CollisionBoxSize, m_CollisionBoxSize, m_CollisionBoxSize),
		FColor::White, true, -1, 0, 10);

	//set material of level achieved so far on startup.
	Mf_CheckAndSetMaterial();
}

// Called every frame
void ALevelChanger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelChanger::Mf_CheckAndSetMaterial()
{
	int medalGottenInt = Cast<UCPPGameInstance>(GetGameInstance())->GetAchievedMedalFromLevel(m_levelIntGoingTo);
	switch (medalGottenInt)
	{
	case 0:
		m_Mesh->SetMaterial(0,m_Mat_Uncleared);
		break;
	case 1:
		m_Mesh->SetMaterial(0,m_Mat_Bronze);
		break;
	case 2:
		m_Mesh->SetMaterial(0,m_Mat_Silver);
		break;
	case 3:
		m_Mesh->SetMaterial(0,m_Mat_Gold);
		break;
	default:
		m_Mesh->SetMaterial(0,m_Mat_Uncleared);
		break;
	}
}

int ALevelChanger::CheckMedalGotten() const
{
	const float timeSinceStart = GetGameTimeSinceCreation();
	if (timeSinceStart < m_GoldTime)
		return 3;
	if (timeSinceStart < m_SilverTime)
		return 2;
	if (timeSinceStart < m_BronzeTime)
		return 1;

	//no medal-worthy time was hit
	return 0;

}

void ALevelChanger::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	
	ACharacter* MyCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	if (OtherActor == MyCharacter && LevelToLoad != "")
	{
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("something overlapped!"));
		}
		UCPPGameInstance* MyGI = 	Cast<UCPPGameInstance>(GetGameInstance());
		if (MyGI == nullptr)
		{
			if (GEngine) {
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("MyGI is nullptr D:!"));
			}
		}
		MyGI->MedalGotten(CheckMedalGotten(), m_levelIntComingFrom);

		UGameplayStatics::OpenLevel(this, LevelToLoad,true);

		FLatentActionInfo LatentInfo; //defines who gets callback, knows of linkage, 
		UGameplayStatics::LoadStreamLevel(this, LevelToLoad, true, true, LatentInfo);
	}
}

