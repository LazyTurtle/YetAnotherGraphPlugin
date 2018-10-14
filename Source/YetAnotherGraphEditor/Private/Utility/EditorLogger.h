// Copyright (c) 2018 Jhonny Hueller
#pragma once

#include "CoreMinimal.h"
DECLARE_LOG_CATEGORY_EXTERN(LogYetAnotherGraphEditor, Verbose, All);
#define EDLLog(Message,...) UE_LOG(LogYetAnotherGraphEditor, Log, TEXT(Message), ##__VA_ARGS__)
#define EDDLog(Message,...) UE_LOG(LogYetAnotherGraphEditor, Display, TEXT(Message), ##__VA_ARGS__)
#define EDWLog(Message,...) UE_LOG(LogYetAnotherGraphEditor, Warning, TEXT(Message), ##__VA_ARGS__)
#define EDELog(Message,...) UE_LOG(LogYetAnotherGraphEditor, Error, TEXT(Message), ##__VA_ARGS__)


