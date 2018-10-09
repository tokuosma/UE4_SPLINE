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

void ULoggingBlueprintFunctionLibrary::CreateViewportScreenShotFilename(AActor *target, FString  filename, int sizeX, int sizeY )
{
    std::string fpath = "C:\\sample.png";
    FString filePath(fpath.c_str());
    FString ScreenshotPath = FPaths::ProjectSavedDir() + TEXT("Screenshots/") + filename + ".png";
    UGameViewportClient* ViewportClient = target->GetWorld()->GetGameViewport();
    uint32 resolutionX = sizeX;
    uint32 resolutionY = sizeY;
    GetHighResScreenshotConfig().SetResolution(resolutionX, resolutionY); //Sets the res multiplier
    GIsHighResScreenshot = true;
    ViewportClient->OnScreenshotCaptured().Clear();
    ViewportClient->OnScreenshotCaptured().AddLambda(
        [ScreenshotPath](int32 SizeX, int32 SizeY, const TArray<FColor>& Bitmap)
    {
        // Make sure that all alpha values are opaque.
        TArray<FColor>& RefBitmap = const_cast<TArray<FColor>&>(Bitmap);
        for (auto& Color : RefBitmap)
            Color.A = 255;

        TArray<uint8> CompressedBitmap;
        FImageUtils::CompressImageArray(SizeX, SizeY, RefBitmap, CompressedBitmap);
        if (FFileHelper::SaveArrayToFile(CompressedBitmap, *ScreenshotPath) == true) {
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("screenshot saved!"));
        }
        else {
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("screenshot failed!"));
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, ScreenshotPath);
        }
    });
    //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Saving a high res screenshot at location " + fpath));
    //FScreenshotRequest::RequestScreenshot(filename, false, true);
    ViewportClient->Viewport->TakeHighResScreenShot();
    
}
