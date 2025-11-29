#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SortElement.h"
#include "SortVisualizer.generated.h"

UCLASS()
class BUBBLESORTPROJE_API ASortVisualizer : public AActor
{
	GENERATED_BODY()

public:
	ASortVisualizer();

	UFUNCTION(BlueprintCallable, Category = "Sorting")
	void InitializeArray(const TArray<int32>& InputNumbers);

	UFUNCTION(BlueprintCallable, Category = "Sorting")
	void StartBubbleSort();

	UFUNCTION(BlueprintCallable, Category = "Sorting")
	void ResetSystem();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Config")
	TSubclassOf<ASortElement> ElementClass;

	UPROPERTY(EditAnywhere, Category = "Config")
	float Spacing = 150.0f;

	UPROPERTY(EditAnywhere, Category = "Config")
	float SortSpeed = 0.5f;

private:
	TArray<ASortElement*> ElementActors;
	FTimerHandle SortTimerHandle;
	int32 i;
	int32 j;
	int32 ArraySize;

	void BubbleSortStep();
};