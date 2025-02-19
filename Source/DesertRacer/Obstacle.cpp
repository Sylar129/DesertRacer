
#include "Obstacle.h"

#include "Components/CapsuleComponent.h"
#include "PaperSpriteComponent.h"
#include "Kismet/GameplayStatics.h"

#include "PlayerCharacter.h"
#include "MyGameMode.h"


AObstacle::AObstacle()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SetRootComponent(CapsuleComponent);

	ObstacleSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("ObstacleSprite"));
	ObstacleSprite->SetupAttachment(RootComponent);

}

void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AObstacle::OverlapBegin);

	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(GetWorld());
	MyGameMode = Cast<AMyGameMode>(GameMode);
}

void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AObstacle::OverlapBegin(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FrameSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
	if (Player) {
		Player->CanMove = false;
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::White, TEXT("Overlapped with Player!"));
		MyGameMode->ResetLevel(false);
	}
}

