#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SortElement.generated.h"

UCLASS()
class BUBBLESORTPROJE_API ASortElement : public AActor
{
	GENERATED_BODY()

public:
	ASortElement();

	virtual void Tick(float DeltaTime) override; // Her karede hareket için gerekli

	void SetValue(int32 InValue);
	int32 GetValue() const { return Value; }

	// Yeni Hedef Belirleme Fonksiyonu
	void MoveToPosition(FVector NewTargetLocation);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UTextRenderComponent* TextComponent;

	int32 Value;

	// Hedef Konum ve Hareket Durumu
	FVector TargetLocation;
	bool bIsMoving;
};