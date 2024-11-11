#pragma once
#include "CoreMinimal.h"
#include "Systems/GP4_GameMode.h"
#include "GP4_UtilsFunctionLibrary.generated.h"

UCLASS()
class UGP4_UtilsFunctionLibrary : public UObject
{
	GENERATED_BODY()
public:

	static FString GetGameStateAsString(const EGameState GameState);

	/*
	 *Note from Peter: For blueprint things consider making a separate class
	 *and derive from blueprint function library instead. Dunno if it's better than UObject
	 *since haven't used them much, but might worth taking a look into them.
	 */
	UFUNCTION(BlueprintCallable, Category = "Bitwise")
	static bool ContainsBitwiseFlag(uint8 Source, uint8 Target);
	UFUNCTION(BlueprintCallable, Category = "Bitwise")
	static uint8 SetBitwiseFlag(uint8 Source, uint8 Target);
	UFUNCTION(BlueprintCallable, Category = "Bitwise")
	static uint8 AddBitwiseFlag(uint8 Source, uint8 Target);
	UFUNCTION(BlueprintCallable, Category = "Bitwise")
	static uint8 RemoveBitwiseFlag(uint8 Source, uint8 Target);
};

	
