// Fill out your copyright notice in the Description page of Project Settings.

#include "LoggingBlueprintFunctionLibrary.h"


bool ULoggingBlueprintFunctionLibrary::AppendLogToFile(const FString & LogToAppend, const FString & FileName)
{
	/// Validation
	if (LogToAppend.IsEmpty() || FileName.IsEmpty())
	{
		///#Warning
		UE_LOG(LogTemp, Warning, TEXT("CSWWarning - GenericFunctionLibrary.ApprendLogToFile() - LogToAppend or FileName is empty"));
		return false;
	}
	/// Get "Project/Saved/Log/" path
	FString LogPath = FPaths::ProjectSavedDir() + TEXT("Logs/");
	FString FullPath = LogPath + FileName + TEXT(".csv");
	/// Make "Project/Saved/Log/" in case it doesn't exists
	IFileManager::Get().MakeDirectory(*LogPath);
	/// AppendLog to FileName.log file
	return FFileHelper::SaveStringToFile(LogToAppend + TEXT("\r\n"), *FullPath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append);
}

FString ULoggingBlueprintFunctionLibrary::GetDateTimeString(FDateTime DateTime)
{
    FString dateString = DateTime.ToIso8601();
    if (dateString.IsEmpty()) {
        return "EMPTY";
    }
    else return dateString;
}
