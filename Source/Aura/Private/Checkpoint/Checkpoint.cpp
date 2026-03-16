// IGR1S


#include "Checkpoint/Checkpoint.h"

#include "Components/SphereComponent.h"
#include "Game/AuraGameModeBase.h"
#include "Interaction/PlayerInterface.h"
#include "Kismet/GameplayStatics.h"


void ACheckpoint::LoadActor_Implementation()
{
	if (bReached)
	{
		HandleGlowEffects();
	}
}

// Sets default values
ACheckpoint::ACheckpoint(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	
	CheckpointMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("CheckpointMeshComp");
	CheckpointMeshComp->SetupAttachment(GetRootComponent());
	CheckpointMeshComp->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	CheckpointMeshComp->SetCollisionResponseToAllChannels(ECR_Block);
	
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetupAttachment(CheckpointMeshComp);
	SphereComp->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);
	

}

void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();
	SphereComp->OnComponentBeginOverlap.AddDynamic(this,&ACheckpoint::OnSphereOverlap);

}

void ACheckpoint::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->Implements<UPlayerInterface>())
	{
		bReached = true;
		
		AAuraGameModeBase* AuraGameMode = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(this));
		check(AuraGameMode);
		if (AuraGameMode)
		{
			AuraGameMode->SaveWorldState(GetWorld());
		}
		
		IPlayerInterface::Execute_SaveProgress(OtherActor, PlayerStartTag);
		
		HandleGlowEffects();
	}
	
	
}

void ACheckpoint::HandleGlowEffects()
{
	SphereComp->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	
	UMaterialInstanceDynamic* DynamicMaterialInstance = UMaterialInstanceDynamic::Create(CheckpointMeshComp->GetMaterial(0), this);
	
	CheckpointMeshComp->SetMaterial(0, DynamicMaterialInstance);
	CheckpointReached(DynamicMaterialInstance);
}
