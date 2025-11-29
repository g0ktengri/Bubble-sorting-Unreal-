#include "SortElement.h"
#include "Components/TextRenderComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h" // Bu kütüphane zorunlu

ASortElement::ASortElement()
{
	PrimaryActorTick.bCanEverTick = true;

	// 1. Mesh Bileþeni
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

	// 2. KÜPÜ ZORLA YÜKLE (Hardcode)
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshAsset(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (CubeMeshAsset.Succeeded())
	{
		MeshComponent->SetStaticMesh(CubeMeshAsset.Object);
	}

	// 3. MATERYALÝ ZORLA YÜKLE (Sarý renk verir)
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial"));
	if (MaterialAsset.Succeeded())
	{
		MeshComponent->SetMaterial(0, MaterialAsset.Object);
	}

	// 4. Yazý Bileþeni
	TextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextComponent"));
	TextComponent->SetupAttachment(RootComponent);
	TextComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 60.0f));
	TextComponent->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	TextComponent->SetWorldSize(40.0f);
	TextComponent->SetTextRenderColor(FColor::Black);
	TextComponent->SetText(FText::FromString("0"));

	bIsMoving = false;
}

void ASortElement::BeginPlay()
{
	Super::BeginPlay();
	TargetLocation = GetActorLocation();
}

void ASortElement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsMoving)
	{
		FVector CurrentLoc = GetActorLocation();
		FVector NewLoc = FMath::VInterpTo(CurrentLoc, TargetLocation, DeltaTime, 5.0f);
		SetActorLocation(NewLoc);

		if (FVector::Dist(NewLoc, TargetLocation) < 1.0f)
		{
			SetActorLocation(TargetLocation);
			bIsMoving = false;
		}
	}
}

void ASortElement::SetValue(int32 InValue)
{
	Value = InValue;
	TextComponent->SetText(FText::AsNumber(Value));

	// Boyutlandýrma (Çok küçük kalmasýn diye en az 0.2 yapýyoruz)
	float HeightScale = (float)Value / 10.0f;
	if (HeightScale < 0.2f) HeightScale = 0.2f;

	SetActorScale3D(FVector(1.0f, 1.0f, HeightScale));
}

void ASortElement::MoveToPosition(FVector NewTargetLocation)
{
	TargetLocation = NewTargetLocation;
	bIsMoving = true;
}