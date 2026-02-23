// IGR1S


#include "Actor/AuraFireBall.h"


void AAuraFireBall::BeginPlay()
{
	Super::BeginPlay();
	StartOutGoingTimeline();
}

void AAuraFireBall::OnsphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

