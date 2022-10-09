// Fill out your copyright notice in the Description page of Project Settings.


#include "CPPGameInstance.h"
#include "Http.h"
#include <SocketSubsystem.h>
#include "Dom/JsonObject.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"
#include "Json.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include <IPAddress.h>


const static FName SESSION_NAME = TEXT("UnrealPong Session");
const static FName SERVER_NAME_SETTINGS_KEY = TEXT("UnrealPong Server");

void UCPPGameInstance::Init()
{
	Super::Init();	

	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
}

FString UCPPGameInstance::GetPlayerIP()
{
	bool canBind = false;
	TSharedRef<FInternetAddr> localIp = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->GetLocalHostAddr(*GLog, canBind);
	return (localIp->IsValid() ? localIp->ToString(false) : "");
}

void UCPPGameInstance::Host(const FString& LobbyName)
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
	RequestObj->SetStringField("Lobby_Name", LobbyName);
	RequestObj->SetStringField("IP_Address", GetPlayerIP());

	FString RequestBody;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestObj, Writer);

	Request->OnProcessRequestComplete().BindUObject(this, &UCPPGameInstance::PutLobbyInfo);
	Request->SetURL("https://kavtekassignment-default-rtdb.firebaseio.com/Host/Lobbys.json");
	Request->SetVerb("PUT");
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString(RequestBody);
	Request->ProcessRequest();
}

void UCPPGameInstance::PushLeaderBoard(const FString& winnerName, const FString& loserName, const FString& resultRedScore, const FString& resultBlueScore) {
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
	RequestObj->SetStringField("Winner", winnerName);
	RequestObj->SetStringField("Loser", loserName);
	RequestObj->SetStringField("Blue_Score", resultRedScore);
	RequestObj->SetStringField("Red_Score", resultBlueScore);

	FString RequestBody;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestObj, Writer);

	Request->OnProcessRequestComplete().BindUObject(this, &UCPPGameInstance::PutLobbyInfo);
	Request->SetURL("https://kavtekassignment-default-rtdb.firebaseio.com/Host/LeaderBoard.json");
	Request->SetVerb("PUT");
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString(RequestBody);
	Request->ProcessRequest();

}

void UCPPGameInstance::RefreshServerList()
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UCPPGameInstance::GetLobbyInfo);
	Request->SetURL("https://kavtekassignment-default-rtdb.firebaseio.com/Host/Lobbys.json");
	Request->SetVerb("GET");
	Request->SetHeader("User-Agent", "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", "application/json");
	Request->ProcessRequest();
}
void UCPPGameInstance::RefreshLeaderboard()
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UCPPGameInstance::GetLeaderboardInfo);
	Request->SetURL("https://kavtekassignment-default-rtdb.firebaseio.com/Host/LeaderBoard.json");
	Request->SetVerb("GET");
	Request->SetHeader("User-Agent", "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", "application/json");
	Request->ProcessRequest();
}
void UCPPGameInstance::DeleteLobbyInfo() {
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();

	FString RequestBody;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestObj, Writer);

	Request->OnProcessRequestComplete().BindUObject(this, &UCPPGameInstance::PutLobbyInfo);
	Request->SetURL("https://kavtekassignment-default-rtdb.firebaseio.com/Host/Lobbys.json");
	Request->SetVerb("DELETE");
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString(RequestBody);
	Request->ProcessRequest();
}

void UCPPGameInstance::PutLobbyInfo(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully) {}

void UCPPGameInstance::GetLobbyInfo(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(Response->GetContentAsString());
	FJsonSerializer::Deserialize(JsonReader, JsonObject);

	getIPAdress = JsonObject->GetStringField("IP_Address");
	getLobbyName = JsonObject->GetStringField("Lobby_Name");
	SaveLobbyName = JsonObject->GetStringField("Lobby_Name");
}
void UCPPGameInstance::GetLeaderboardInfo(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(Response->GetContentAsString());
	FJsonSerializer::Deserialize(JsonReader, JsonObject);
	SaveLobbyName = JsonObject->GetStringField("Lobby_Name");
	getWinnerName = JsonObject->GetStringField("Winner");
	getLoserName = JsonObject->GetStringField("Loser");
	getResultRedScore = JsonObject->GetStringField("Red_Score");
	getResultBlueScore = JsonObject->GetStringField("Blue_Score");
}

