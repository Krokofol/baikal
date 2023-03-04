// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SurfaceNodeUtils.generated.h"

/**
 * 
 */
UCLASS()
class BAIKAL4_API USurfaceNodeUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()


		UFUNCTION(BlueprintCallable, Category = "Surface")
		static void getNodes(FString userDir, TArray<FVector>& coordinates, TArray<int32>& triangles);

		UFUNCTION(BlueprintCallable, Category = "Surface")
		static bool checkCoordinatesFile(FString userDir);

		UFUNCTION(BlueprintCallable, Category = "Surface")
		static void createDefaultCoordintatesFile(FString userDir);

		static FString fileName(FString userDir);

		static int32 countColumns(FString column, int32 lineNumber, TArray<FVector>& coordinates);
};
