#include "Utils/GP4_UtilsFunctionLibrary.h"

bool UGP4_UtilsFunctionLibrary::ContainsBitwiseFlag(uint8 Source, uint8 Target)
{
	return (Source & Target) == Target;
}

uint8 UGP4_UtilsFunctionLibrary::SetBitwiseFlag(uint8 Source, uint8 Target)
{
	Source = 0;
	Source |= Target;
	return Source;
}

uint8 UGP4_UtilsFunctionLibrary::AddBitwiseFlag(uint8 Source, uint8 Target)
{
	return (Source | Target);
}

uint8 UGP4_UtilsFunctionLibrary::RemoveBitwiseFlag(uint8 Source, uint8 Target)
{
	if (UGP4_UtilsFunctionLibrary::ContainsBitwiseFlag(Source, Target))
	{
		return (Source ^ Target);
	}
	return Source;
}

FString UGP4_UtilsFunctionLibrary::GetGameStateAsString(const EGameState GameState)
{
	switch (GameState)
	{
	case EGameState::None: return "None";
	case EGameState::StartGame: return "StartGame";
	case EGameState::GameRunning: return "GameRunning";
	case EGameState::PauseGame: return "PauseGame";
	case EGameState::ResumeGame: return "ResumeGame";
	case EGameState::GameWon: return "GameWon";
	case EGameState::GameOver: return "GameOver";
	default: return "Invalid";
	}
}