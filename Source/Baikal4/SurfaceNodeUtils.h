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
		static void getNodes(
			FString userDir,
			int32 horizontalScale,
			TArray<FVector>& coordinates,
			int32& nodesCountX,
			int32& nodesCountY
		);

		UFUNCTION(BlueprintCallable, Category = "Surface")
		static void generateTriangles(
			int32 nodesCountX,
			int32 nodesCountY,
			TArray<int32>& triangles
		);

		UFUNCTION(BlueprintCallable, Category = "Surface")
		static bool checkCoordinatesFile(FString userDir);

		UFUNCTION(BlueprintCallable, Category = "Surface")
		static void createDefaultCoordintatesFile(FString userDir);

		UFUNCTION(BlueprintCallable, Category = "Surface")
		static TArray<FVector> takeEach(
			int32 x1, int32 y1, int32 x2, int32 y2,
			TArray<FVector> nodes,
			int32 skip,
			int32 nodesCountX,
			int32 nodesCountY
		);

		UFUNCTION(BlueprintCallable, Category = "Surface")
		static TArray<FLinearColor> colorVertexes(TArray<FVector> nodes);

		static FString fileName(FString userDir);

		static int32 countColumns(FString line);

		static void getVertexes(TArray<FString> lines, int32 countX, int32 countY, int32 horizontalScale, TArray<FVector>& coordinates);

		static void addLineVertexes(int32 x, FString line, int32 countX, int32 countY, int32 horizontalScale, TArray<FVector>& vertexes);

		static void addVertex(
			int32 x, int32 y, int32 z, 
			int32 horizontalScale, 
			TArray<FVector>& coordinates
		);

		static FLinearColor getColor(double z);
};
