// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <iostream>
#include <fstream>
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

	/** Saves text to filename of your choosing, make sure include whichever file extension you want in the filename, ex: SelfNotes.txt . Make sure to include the entire file path in the save directory, ex: C:\MyGameDir\BPSavedTextFiles */
	UFUNCTION(BlueprintCallable, Category = "Victory BP Library|File IO")
	static bool FileIO__SaveStringTextToFile(FString SaveDirectory, FString JoyfulFileName, FString SaveText, bool AllowOverWriting = false);

	
};


