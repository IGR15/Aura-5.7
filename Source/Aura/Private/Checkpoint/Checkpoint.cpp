// IGR1S


#include "Checkpoint/Checkpoint.h"

#include "Components/SphereComponent.h"


// Sets default values
ACheckpoint::ACheckpoint(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	
	SphereComp->SetupAttachment(GetRootComponent());
	SphereComp->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);
	
	CheckpointMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("CheckpointMeshComp");
	CheckpointMeshComp->SetupAttachment(GetRootComponent());
	CheckpointMeshComp->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	CheckpointMeshComp->SetCollisionResponseToAllChannels(ECR_Block);
}

void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();
	SphereComp->OnComponentBeginOverlap.AddDynamic(this,&ACheckpoint::OnSphereOverlap);

}

void ACheckpoint::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag(FName("Player")))
	{
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
