

#include "GladiatorGame.h"
#include "GladiatorGameInstance.h"

//UGladiatorGameInstance::UGladiatorGameInstance(const FObjectInitializer& ObjectInitializer)
//	: Super(ObjectInitializer)
//{
//	UE_LOG(LogTemp, Warning, TEXT("UGladiatorGameInstance"));
//
//	OnCreateSessionCompleteDelegate = FOnCreateSessionCompleteDelegate::CreateUObject(this, &UGladiatorGameInstance::OnCreateSessionComplete);
//	OnStartSessionCompleteDelegate = FOnStartSessionCompleteDelegate::CreateUObject(this, &UGladiatorGameInstance::OnStartOnlineGameComplete);
//	OnFindSessionsCompleteDelegate = FOnFindSessionsCompleteDelegate::CreateUObject(this, &UGladiatorGameInstance::OnFindSessionsComplete);
//	OnJoinSessionCompleteDelegate = FOnJoinSessionCompleteDelegate::CreateUObject(this, &UGladiatorGameInstance::OnJoinSessionComplete);
//	OnDestroySessionCompleteDelegate = FOnDestroySessionCompleteDelegate::CreateUObject(this, &UGladiatorGameInstance::OnDestroySessionComplete);
//}
//UGladiatorGameInstance::~UGladiatorGameInstance()
//{
//	DestroySessionAndLeaveGame();
//}
//
//#pragma region BPFunc
//void UGladiatorGameInstance::StartOnlineGame()
//{
//	UE_LOG(LogTemp, Warning, TEXT("BPFunc StartOnlineGame"));
//
//	ULocalPlayer* const Player = GetFirstGamePlayer();
//	HostSession(Player->GetPreferredUniqueNetId(), GameSessionName, true, true, 4);
//}
//
//void UGladiatorGameInstance::FindOnlineGames()
//{
//	UE_LOG(LogTemp, Warning, TEXT("BPFunc FindOnlineGames"));
//
//	ULocalPlayer* const Player = GetFirstGamePlayer();
//
//	FindSessions(Player->GetPreferredUniqueNetId(), GameSessionName, true, true);
//}
//
//void UGladiatorGameInstance::JoinOnlineGame()
//{
//	UE_LOG(LogTemp, Warning, TEXT("BPFunc JoinOnlineGame"));
//	ULocalPlayer* const Player = GetFirstGamePlayer();
//
//	// Just a SearchResult where we can save the one we want to use, for the case we find more than one!
//	FOnlineSessionSearchResult SearchResult;
//
//	// If the Array is not empty, we can go through it
//	if (SessionSearch->SearchResults.Num() > 0)
//	{
//		for (int32 i = 0; i < SessionSearch->SearchResults.Num(); i++)
//		{
//			// To avoid something crazy, we filter sessions from ourself
//			if (SessionSearch->SearchResults[i].Session.OwningUserId != Player->GetPreferredUniqueNetId())
//			{
//				SearchResult = SessionSearch->SearchResults[i];
//
//				// Once we found sounce a Session that is not ours, just join it. Instead of using a for loop, you could
//				// use a widget where you click on and have a reference for the GameSession it represents which you can use
//				// here
//				JoinSession(Player->GetPreferredUniqueNetId(), GameSessionName, SearchResult);
//				break;
//			}
//		}
//	}
//}
//
//void UGladiatorGameInstance::DestroySessionAndLeaveGame()
//{
//	UE_LOG(LogTemp, Warning, TEXT("BPFunc DestroySessionAndLeaveGame"));
//
//	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
//	if (OnlineSub)
//	{
//		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
//
//		if (Sessions.IsValid())
//		{
//			Sessions->AddOnDestroySessionCompleteDelegate_Handle(OnDestroySessionCompleteDelegate);
//
//			Sessions->DestroySession(GameSessionName);
//		}
//	}
//}
//#pragma endregion 
//
////Function to host a game
//#pragma region HostGame
//bool UGladiatorGameInstance::HostSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, bool bIsLAN, bool bIsPresence, int32 MaxNumPlayers)
//{
//	UE_LOG(LogTemp, Warning, TEXT("HostFunc HostSession"));
//	IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get();
//	if (OnlineSub)
//	{
//		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
//		if (Sessions.IsValid() && UserId.IsValid())
//		{
//			SessionSettings = MakeShareable(new FOnlineSessionSettings());
//			SessionSettings->bIsLANMatch = bIsLAN;
//			SessionSettings->bUsesPresence = bIsPresence;
//			SessionSettings->NumPublicConnections = MaxNumPlayers;
//			SessionSettings->NumPrivateConnections = 0;
//			SessionSettings->bAllowInvites = true;
//			SessionSettings->bAllowJoinInProgress = true;
//			SessionSettings->bShouldAdvertise = true;
//			SessionSettings->bAllowJoinViaPresence = true;
//			SessionSettings->bAllowJoinViaPresenceFriendsOnly = false;
//			SessionSettings->Set(SETTING_MAPNAME, FString("ArenaNetworkTest"), EOnlineDataAdvertisementType::ViaOnlineService);
//
//			OnCreateSessionCompleteDelegateHandle = Sessions->AddOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegate);
//
//			return Sessions->CreateSession(*UserId, SessionName, *SessionSettings);
//		}
//	}
//	else
//		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("No OnlineSubsytem found!"));
//	return false;
//}
//
//void UGladiatorGameInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
//{
//	UE_LOG(LogTemp, Warning, TEXT("HostFunc OnCreateSessionComplete"));
//
//	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
//	if (OnlineSub)
//	{
//		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
//		if (Sessions.IsValid())
//		{
//			Sessions->ClearOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegateHandle);
//			if (bWasSuccessful)
//			{
//				OnStartSessionCompleteDelegateHandle = Sessions->AddOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegate);
//				Sessions->StartSession(SessionName);
//			}
//		}
//
//	}
//}
//
//void UGladiatorGameInstance::OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful)
//{
//	UE_LOG(LogTemp, Warning, TEXT("HostFunc OnStartOnlineGameComplete"));
//
//	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
//	if (OnlineSub)
//	{
//		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
//		if (Sessions.IsValid())
//			Sessions->ClearOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegateHandle);
//	}
//
//	if (bWasSuccessful)
//		UGameplayStatics::OpenLevel(GetWorld(), "ArenaNetworkTest", true, "listen");
//}
//#pragma endregion 
//
////Find an online session
//#pragma region FindSession
//void UGladiatorGameInstance::FindSessions(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, bool bIsLAN, bool bIsPresence)
//{
//	UE_LOG(LogTemp, Warning, TEXT("FindSession FindSessions"));
//
//	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
//	if (OnlineSub)
//	{
//		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
//
//		if (Sessions.IsValid() && UserId.IsValid())
//		{
//			UE_LOG(LogTemp, Warning, TEXT("FindSession FindSessions  Sessions.IsValid() && UserId.IsValid()"));
//
//			SessionSearch = MakeShareable(new FOnlineSessionSearch());
//
//			SessionSearch->bIsLanQuery = bIsLAN;
//			SessionSearch->MaxSearchResults = 20;
//			SessionSearch->PingBucketSize = 50;
//
//			if (bIsPresence)
//			{
//				UE_LOG(LogTemp, Warning, TEXT("FindSession FindSessions  bIsPresence = true"));
//				SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, bIsPresence, EOnlineComparisonOp::Equals);
//			}
//
//			TSharedRef<FOnlineSessionSearch> SearchSettingsRef = SessionSearch.ToSharedRef();
//
//			OnFindSessionsCompleteDelegateHandle = Sessions->AddOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegate);
//
//			Sessions->FindSessions(*UserId, SearchSettingsRef);
//		}
//	}
//	else
//	{
//		UE_LOG(LogTemp, Warning, TEXT("FindSession FindSessions  else"));
//		OnFindSessionsComplete(false);
//	}
//}
//
//void UGladiatorGameInstance::OnFindSessionsComplete(bool bWasSuccessful)
//{
//	UE_LOG(LogTemp, Warning, TEXT("FindSession OnFindSessionsComplete"));
//
//	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("OFindSessionsComplete bSuccess: %d"), bWasSuccessful));
//
//	IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get();
//	if (OnlineSub)
//	{
//		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
//		if (Sessions.IsValid())
//		{
//			Sessions->ClearOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegateHandle);
//
//			//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Num Search Results: %d"), SessionSearch->SearchResults.Num()));
//			UE_LOG(LogTemp, Warning, TEXT("Num Search Results: %d"), SessionSearch->SearchResults.Num());
//
//			if (SessionSearch->SearchResults.Num() > 0)
//			{
//				for (int32 SearchIdx = 0; SearchIdx < SessionSearch->SearchResults.Num(); SearchIdx++)
//				{
//					//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Session Number: %d | Sessionname: %s "), SearchIdx + 1, *(SessionSearch->SearchResults[SearchIdx].Session.OwningUserName)));
//					UE_LOG(LogTemp, Warning, TEXT("Session Number: %d | Sessionname: %s "), SearchIdx + 1, *(SessionSearch->SearchResults[SearchIdx].Session.OwningUserName));
//				}
//			}
//		}
//	}
//}
//#pragma endregion 
//
////Joins a session via a search result
//#pragma region JoinSession
//bool UGladiatorGameInstance::JoinSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, const FOnlineSessionSearchResult& SearchResult)
//{
//	bool bSuccessful = false;
//	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
//
//	if (OnlineSub)
//	{
//		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
//
//		if (Sessions.IsValid() && UserId.IsValid())
//		{
//			OnJoinSessionCompleteDelegateHandle = Sessions->AddOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegate);
//			bSuccessful = Sessions->JoinSession(*UserId, SessionName, SearchResult);
//		}
//	}
//
//	return bSuccessful;
//}
//
//void UGladiatorGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
//{
//	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("OnJoinSessionComplete %s, %d"), *SessionName.ToString(), static_cast<int32>(Result)));
//	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
//	if (OnlineSub)
//	{
//		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
//
//		if (Sessions.IsValid())
//		{
//			Sessions->ClearOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegateHandle);
//			APlayerController * const PlayerController = GetFirstLocalPlayerController();
//			FString TravelURL;
//
//			if (PlayerController && Sessions->GetResolvedConnectString(SessionName, TravelURL))
//				PlayerController->ClientTravel(TravelURL, ETravelType::TRAVEL_Absolute);
//		}
//	}
//}
//#pragma endregion 
//
//#pragma region DestroySession
//
//void UGladiatorGameInstance::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
//{
//	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("OnDestroySessionComplete %s, %d"), *SessionName.ToString(), bWasSuccessful));
//
//	// Get the OnlineSubsystem we want to work with
//	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
//	if (OnlineSub)
//	{
//		// Get the SessionInterface from the OnlineSubsystem
//		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
//
//		if (Sessions.IsValid())
//		{
//			// Clear the Delegate
//			Sessions->ClearOnDestroySessionCompleteDelegate_Handle(OnDestroySessionCompleteDelegateHandle);
//
//			// If it was successful, we just load another level (could be a MainMenu!)
//			if (bWasSuccessful)
//			{
//				UGameplayStatics::OpenLevel(GetWorld(), "NetworkTest", true);
//			}
//		}
//	}
//}
//#pragma endregion 