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
	FString FullPath = LogPath + FileName + TEXT(".txt");
	/// Make "Project/Saved/Log/" in case it doesn't exists
	IFileManager::Get().MakeDirectory(*LogPath);
	/// AppendLog to FileName.log file
	std::string testDir = std::string(TCHAR_TO_UTF8(*FullPath));
	std::string test = std::string(TCHAR_TO_UTF8(*LogToAppend));
	std::ofstream myfile;
	myfile.open(testDir);
	myfile << test.c_str();
	myfile.close();

	return FFileHelper::SaveStringToFile(LogToAppend + TEXT("\r\n"), *FullPath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append);
}

bool ULoggingBlueprintFunctionLibrary::FileIO__SaveStringTextToFile(FString SaveDirectory, FString JoyfulFileName, FString SaveText, bool AllowOverWriting)
{
	if (!FPlatformFileManager::Get().GetPlatformFile().CreateDirectoryTree(*SaveDirectory))
	{
		//Could not make the specified directory
		return false;
		//~~~~~~~~~~~~~~~~~~~~~~
	}

	//get complete file path
	//SaveDirectory += "\\";
	SaveDirectory += JoyfulFileName + "txt";

	//No over-writing?
	if (!AllowOverWriting)
	{
		//Check if file exists already
		if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*SaveDirectory))
		{
			//no overwriting
			return false;
		}
	}

	return FFileHelper::SaveStringToFile(SaveText, *SaveDirectory, FFileHelper::EEncodingOptions::ForceUTF8);
}
