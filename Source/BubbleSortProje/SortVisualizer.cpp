#include "SortVisualizer.h"

ASortVisualizer::ASortVisualizer()
{
	PrimaryActorTick.bCanEverTick = false;
	Spacing = 150.0f;
	SortSpeed = 0.5f;
}

void ASortVisualizer::InitializeArray(const TArray<int32>& InputNumbers)
{
	// Temizlik
	for (ASortElement* Actor : ElementActors)
	{
		if (Actor) Actor->Destroy();
	}
	ElementActors.Empty();

	if (!ElementClass) return;

	// Oluþturma
	for (int32 Index = 0; Index < InputNumbers.Num(); Index++)
	{
		FVector SpawnLoc = GetActorLocation() + FVector(0.0f, Index * Spacing, 0.0f);

		// Spawn parametreleri (Çakýþma olsa bile zorla oluþtur)
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		ASortElement* NewElement = GetWorld()->SpawnActor<ASortElement>(ElementClass, SpawnLoc, FRotator::ZeroRotator, SpawnParams);

		if (NewElement)
		{
			NewElement->SetValue(InputNumbers[Index]);
			ElementActors.Add(NewElement);
		}
	}
	ArraySize = ElementActors.Num();
}

void ASortVisualizer::StartBubbleSort()
{
	if (ArraySize < 2) return;

	i = 0;
	j = 0;

	// Timer varsa temizle, sonra yeniden baþlat
	GetWorld()->GetTimerManager().ClearTimer(SortTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(SortTimerHandle, this, &ASortVisualizer::BubbleSortStep, SortSpeed, true);
}

void ASortVisualizer::BubbleSortStep()
{
	if (i < ArraySize - 1)
	{
		if (j < ArraySize - i - 1)
		{
			ASortElement* A = ElementActors[j];
			ASortElement* B = ElementActors[j + 1];

			if (A->GetValue() > B->GetValue())
			{
				// Swap
				ElementActors.Swap(j, j + 1);

				// Yeni pozisyonlara git
				FVector BaseLoc = GetActorLocation();
				FVector TargetForA = BaseLoc + FVector(0.0f, (j + 1) * Spacing, 0.0f);
				FVector TargetForB = BaseLoc + FVector(0.0f, j * Spacing, 0.0f);

				A->MoveToPosition(TargetForA);
				B->MoveToPosition(TargetForB);
			}
			j++;
		}
		else
		{
			j = 0;
			i++;
		}
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(SortTimerHandle);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("SIRALAMA BITTI"));
	}


}

void ASortVisualizer::ResetSystem()
{
	// 1. Varsa çalýþan Timer'ý durdur (Sýralama yarým kaldýysa)
	GetWorld()->GetTimerManager().ClearTimer(SortTimerHandle);

	// 2. Sahnedeki tüm küpleri yok et
	for (ASortElement* Actor : ElementActors)
	{
		if (Actor) Actor->Destroy();
	}
	ElementActors.Empty();

	// Deðiþkenleri sýfýrla
	ArraySize = 0;
	i = 0;
	j = 0;
}