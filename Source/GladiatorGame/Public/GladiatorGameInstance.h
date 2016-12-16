

#pragma once

#include "Engine/GameInstance.h"
#include "UnrealNetwork.h"
#include "Online.h"
#include "GladiatorGameInstance.generated.h"


UCLASS()
class GLADIATORGAME_API UGladiatorGameInstance : public UGameInstance
{
	GENERATED_BODY()

	UGladiatorGameInstance(const FObjectInitializer& ObjectInitializer);
	~UGladiatorGameInstance();

public:

	UFUNCTION(BlueprintCallable, Category = "Network")
		void StartOnlineGame(bool IsLan);
	UFUNCTION(BlueprintCallable, Category = "Network")
		void FindOnlineGames(bool IsLan, FString Adress);
	UFUNCTION(BlueprintCallable, Category = "Network")
		void JoinOnlineGame();
	/*UFUNCTION(BlueprintCallable, Category = "Network")
		void DestroySessionAndLeaveGame();*/

#pragma region HostGame

	bool HostSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, bool bIsLAN, bool bIsPresence, int32 MaxNumPlayers);
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful);

	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
	FOnStartSessionCompleteDelegate OnStartSessionCompleteDelegate;
	FDelegateHandle OnCreateSessionCompleteDelegateHandle;
	FDelegateHandle OnStartSessionCompleteDelegateHandle;

	TSharedPtr<class FOnlineSessionSettings> SessionSettings;
	
#pragma endregion 

#pragma region FindSession

	void FindSessions(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, bool bIsLAN, bool bIsPresence);
	void OnFindSessionsComplete(bool bWasSuccessful);

	FOnFindSessionsCompleteDelegate OnFindSessionsCompleteDelegate;
	FDelegateHandle OnFindSessionsCompleteDelegateHandle;

	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

#pragma endregion 

#pragma region JoinSession

	bool JoinSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, const FOnlineSessionSearchResult& SearchResult);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;
	FDelegateHandle OnJoinSessionCompleteDelegateHandle;
	FString AdressIP = "127.0.0.1";

#pragma endregion 

#pragma region DestroySession

	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);

	FOnDestroySessionCompleteDelegate OnDestroySessionCompleteDelegate;
	FDelegateHandle OnDestroySessionCompleteDelegateHandle;


#pragma endregion 

};