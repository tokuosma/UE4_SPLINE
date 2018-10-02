// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreMisc.h"
#include "Runtime/Core/Public/Misc/Paths.h"
#include "Runtime/Core/Public/Misc/FileHelper.h"
#include "Runtime/Core/Public/HAL/FileManager.h"
#include "Runtime/Core/Public/HAL/PlatformFilemanager.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LoggingBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class SPLINE_API ULoggingBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	/*
	* Append a string into a file.
	* Uses default path "Project/Saved/Logs/"
	* Uses default extension ".log"
	* @param LogToAppend - Message to be appended into the .log file.
	* @param FileName - Name of the .log file.
	*/
	UFUNCTION(BlueprintCallable, Category = "Logging")
	static bool AppendLogToFile(const FString& LogToAppend, const FString& FileName);

    UFUNCTION(BlueprintCallable, Category = "Time")
    static FString GetDateTimeString(FDateTime DateTime);
	
};


