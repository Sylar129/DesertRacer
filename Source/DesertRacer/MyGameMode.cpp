
#include "MyGameMode.h"

#include "Kismet/GameplayStatics.h"

void AMyGameMode::ResetLevel(bool IsWin)
{
    float ResetTime = IsWin ? WinResetTime : LoseResetTime;

    GetWorldTimerManager().SetTimer(ResetGameTimer, this, &AMyGameMode::OnResetGameTimerTimeout,1.0f, false, ResetTime);
}

void AMyGameMode::OnResetGameTimerTimeout()
{
    UGameplayStatics::OpenLevel(GetWorld(), FName("MainLevel"));
}
