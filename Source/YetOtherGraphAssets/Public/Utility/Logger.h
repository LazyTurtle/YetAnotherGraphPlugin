#pragma once

#include "CoreMinimal.h"
DECLARE_LOG_CATEGORY_EXTERN(LogYetOtherGraphAssets, Verbose, All);
#define LLog(Message,...) UE_LOG(LogYetOtherGraphAssets, Log, TEXT(Message), ##__VA_ARGS__)
#define DLog(Message,...) UE_LOG(LogYetOtherGraphAssets, Display, TEXT(Message), ##__VA_ARGS__)
#define WLog(Message,...) UE_LOG(LogYetOtherGraphAssets, Warning, TEXT(Message), ##__VA_ARGS__)
#define ELog(Message,...) UE_LOG(LogYetOtherGraphAssets, Error, TEXT(Message), ##__VA_ARGS__)


