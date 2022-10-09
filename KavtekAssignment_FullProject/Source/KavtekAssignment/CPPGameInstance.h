// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Http.h"
#include "MenuInterface.h"
#include "PongData.h"
#include "CPPGameInstance.generated.h"

/**
 *
 */
//DECLARE_LOG_CATEGORY_EXTERN(LogMainMenu, Log, All);

UCLASS(Blueprintable)
class KAVTEKASSIGNMENT_API UCPPGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

public:
	virtual void Init() override;

	virtual FString GetPlayerIP();

	UFUNCTION(BlueprintCallable)
	virtual void Host(const FString& LobbyName);

	UFUNCTION(BlueprintCallable)
	virtual void PushLeaderBoard(const FString& winnerName, const FString& loserName, const FString& resultRedScore, const FString& resultBlueScore);

	UFUNCTION(BlueprintCallable)
	virtual void RefreshServerList();

	UFUNCTION(BlueprintCallable)
	virtual void RefreshLeaderboard();

	UFUNCTION(BlueprintCallable)
	virtual void DeleteLobbyInfo();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString SaveLobbyName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ID_Address;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString getIPAdress;	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString getLobbyName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString getWinnerName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString getLoserName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString getResultRedScore;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString getResultBlueScore;

private:
	void PutLobbyInfo(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);

	void GetLobbyInfo(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);

	void GetLeaderboardInfo(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);
};
