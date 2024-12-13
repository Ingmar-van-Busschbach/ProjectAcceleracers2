/**
* Copyright (C) 2017-2024 | eelDev AB
*
* EOSCore Documentation: https://eeldev.com
*/

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
#include <FindSessionsCallbackProxy.h>
#include "OnlineSubsystemModuleEOSCore.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogEOSCoreSubsystem, Log, All);

class FOnlineSubsystemEOSCoreModule : public IModuleInterface
{
public:
	FOnlineSubsystemEOSCoreModule()
		: m_EOSFactory(NULL)
		  , m_EOSHandle(nullptr)
	{
	}

	virtual ~FOnlineSubsystemEOSCoreModule()
	{
	}

public:
	// IModuleInterface
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	virtual bool SupportsDynamicReloading() override { return false; }
	virtual bool SupportsAutomaticShutdown() override { return false; }
private:
	class FOnlineFactoryEOSCore* m_EOSFactory;
	void* m_EOSHandle;
};

DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnSessionInviteCallback, bool, bSuccess, APlayerController*, playerController, FBlueprintSessionResult, session);

UCLASS()
class UEOSSubsystemLibrary : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "EOSCore|OSS")
	static void ListenForSessionInvites(APlayerController* playerController, const FOnSessionInviteCallback& callback);

	UFUNCTION(BlueprintCallable, Category = "EOSCore|OSS", meta = (WorldContext = "worldContextObject"))
	static void StopListeningForSessionInvites(APlayerController* playerController);
};
