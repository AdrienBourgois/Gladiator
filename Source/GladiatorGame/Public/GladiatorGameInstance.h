

#pragma once

#include "Engine/GameInstance.h"
#include "GladiatorGameInstance.generated.h"


UCLASS()
class GLADIATORGAME_API UGladiatorGameInstance : public UGameInstance
{
	GENERATED_BODY()

//	UGladiatorGameInstance(const FObjectInitializer& ObjectInitializer);
//	~UGladiatorGameInstance();
//
//public:
//
//	UFUNCTION(BlueprintCallable, Category = "Network|Test")
//		void StartOnlineGame();
//	UFUNCTION(BlueprintCallable, Category = "Network|Test")
//		void FindOnlineGames();
//	UFUNCTION(BlueprintCallable, Category = "Network|Test")
//		void JoinOnlineGame();
//	UFUNCTION(BlueprintCallable, Category = "Network|Test")
//		void DestroySessionAndLeaveGame();
//
//#pragma region HostGame
//
//	bool HostSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, bool bIsLAN, bool bIsPresence, int32 MaxNumPlayers);
//	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
//	void OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful);
//
//	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
//	FOnStartSessionCompleteDelegate OnStartSessionCompleteDelegate;
//	FDelegateHandle OnCreateSessionCompleteDelegateHandle;
//	FDelegateHandle OnStartSessionCompleteDelegateHandle;
//
//	TSharedPtr<class FOnlineSessionSettings> SessionSettings;
//	
//#pragma endregion 
//
//#pragma region FindSession
//
//	void FindSessions(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, bool bIsLAN, bool bIsPresence);
//	void OnFindSessionsComplete(bool bWasSuccessful);
//
//	FOnFindSessionsCompleteDelegate OnFindSessionsCompleteDelegate;
//	FDelegateHandle OnFindSessionsCompleteDelegateHandle;
//
//	TSharedPtr<class FOnlineSessionSearch> SessionSearch;
//
//#pragma endregion 
//
//#pragma region JoinSession
//
//	bool JoinSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, const FOnlineSessionSearchResult& SearchResult);
//	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
//
//	FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;
//	FDelegateHandle OnJoinSessionCompleteDelegateHandle;
//
//
//#pragma endregion 
//
//#pragma region DestroySession
//
//	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);
//
//	FOnDestroySessionCompleteDelegate OnDestroySessionCompleteDelegate;
//	FDelegateHandle OnDestroySessionCompleteDelegateHandle;
//
//
//#pragma endregion 

};