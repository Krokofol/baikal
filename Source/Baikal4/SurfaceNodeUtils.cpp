// Fill out your copyright notice in the Description page of Project Settings.


#include "SurfaceNodeUtils.h"

using namespace std;

void USurfaceNodeUtils::getNodes(
	FString userDir,
	TArray<FVector>& coordinates,
	TArray<int32>& triangles,
	TArray<FLinearColor>& vertexColors
) {
	TArray<FString> lines = TArray<FString>();
	FFileHelper::LoadFileToStringArray(lines, *fileName(userDir));

	coordinates = TArray<FVector>();
	triangles = TArray<int32>();

	int32 lineCounter = 0;
	int32 columnCounter = 0;
	int32 nodesCounter = 0;
	for (FString line : lines)
	{
		columnCounter = countColumns(line, lineCounter, coordinates, vertexColors);
		lineCounter++;
	}
	for (FVector node : coordinates) 
	{
		nodesCounter++;
	}

	UE_LOG(LogTemp, Display, TEXT("node lines count is: %d"), lineCounter);
	UE_LOG(LogTemp, Display, TEXT("node columns count is: %d"), columnCounter);
	UE_LOG(LogTemp, Display, TEXT("nodes count is: % d"), nodesCounter);

	for (int i = 0; i < lineCounter - 1; i++) {
		for (int j = 0; j < columnCounter - 1; j++) {
			//first triangle
			triangles.Add(i * columnCounter + j);
			triangles.Add((i + 1) * columnCounter + j);
			triangles.Add(i * columnCounter + (j + 1));
			//second triangle
			triangles.Add(i * columnCounter + (j + 1));
			triangles.Add((i + 1) * columnCounter + j);
			triangles.Add((i + 1) * columnCounter + (j + 1));
		}
	}
	UE_LOG(LogTemp, Display, TEXT("nodes numbers in triangles count is: %d"), triangles.Num());

	return;
}

bool USurfaceNodeUtils::checkCoordinatesFile(FString userDir)
{
	TArray<FString> result = TArray<FString>();
	return FFileHelper::LoadFileToStringArray(result, *fileName(userDir));
}

void USurfaceNodeUtils::createDefaultCoordintatesFile(FString userDir)
{
	TArray<FString> defaultCoordinates = TArray<FString>();
	defaultCoordinates.Add(FString("6 14 18 20 26 35 44 50 54 56 61 70 70 69 66 64 64 59 49 45 37"));
	defaultCoordinates.Add(FString("-1 2 10 14 20 26 36 43 51 54 54 54 50 44 51 54 53 46 40 38 32"));
	defaultCoordinates.Add(FString("-8 -4 3 9 14 18 26 32 33 38 42 46 44 40 40 41 38 31 18 18 22"));
	defaultCoordinates.Add(FString("-17 -11 -5 2 5 8 17 23 26 28 27 28 26 24 28 27 24 18 8 8 15"));
	defaultCoordinates.Add(FString("-23 -18 -14 -10 -6 -2 1 11 14 16 16 17 18 16 10 1 4 1 2 4 17"));
	defaultCoordinates.Add(FString("-30 -25 -21 -15 -11 -8 -9 -10 -6 -2 4 6 6 4 1 -6 -7 -5 -2 8 26"));
	defaultCoordinates.Add(FString("-33 -32 -28 -16 -11 -10 -12 -14 -13 -12 -14 -14 -9 -6 -12 -12 -11 -6 11 34 56"));
	defaultCoordinates.Add(FString("-44 -44 -42 -28 -24 -20 -19 -17 -16 -16 -16 -18 -18 -20 -22 -16 -4 12 36 58 82"));
	defaultCoordinates.Add(FString("-52 -50 -46 -39 -35 -36 -33 -32 -31 -29 -26 -25 -24 -26 -24 -17 8 36 60 90 97"));
	defaultCoordinates.Add(FString("-62 -62 -58 -52 -48 -44 -38 -36 -36 -36 -34 -33 -26 -6 10 14 20 48 82 101 98"));

	FFileHelper::SaveStringArrayToFile(defaultCoordinates, *fileName(userDir));
	return;
}

FString USurfaceNodeUtils::fileName(FString userDir)
{
	return FString(userDir + ".Baikal/Example.txt");
}

int32 USurfaceNodeUtils::countColumns(FString line, int32 lineNumber, TArray<FVector>& coordinates, TArray<FLinearColor>& vertexColors)
{
	FString leftPart;
	FString lineCopy;
	if (line.StartsWith(" ")) {
		line.Split(FString(" "), &leftPart, &lineCopy);
	}
	else {
		lineCopy = FString(line);
	}

	int32 counter = 0;
	while (lineCopy.Contains(" "))
	{
		lineCopy.Split(FString(" "), &leftPart, &lineCopy);
		addVertex(lineNumber, -counter, FCString::Atoi(*lineCopy), coordinates, vertexColors);
		counter++;
	}
	addVertex(lineNumber, -counter, FCString::Atoi(*lineCopy), coordinates, vertexColors);
	return ++counter;
}

void USurfaceNodeUtils::addVertex(int32 x, int32 y, int32 z, TArray<FVector>& coordinates, TArray<FLinearColor>& vertexColors)
{
	coordinates.Add(FVector(x * 50, y * 50, z));
	vertexColors.Add(getColor(z - 430));
}

FLinearColor USurfaceNodeUtils::getColor(double z)
{
	// max for baical expected : 2700 - 430 (2270);
	// min for baical expected : -1198 - 430 (-1628);
	FLinearColor color;
	if (z > 0) {
		if (z > 700) {
			if (z > 1500) {
				color = FLinearColor(0.9, 0.9, 0.9);
			}
			else {
				color = FLinearColor(0.5, 0.5 - 0.35 * ((z - 700) / 800), 0.05);
			}
		}
		else {
			color = FLinearColor(0.15 + 0.45 * (z / 700), 0.6, 0.1);
		}
	}
	else {
		if (z > -800) {
			color = FLinearColor(0.3 * (1 - z / -800), 0.3 * (1 - z / -800), 0.25 * (1 - z / -800) + 0.75);
		}
		else {
			color = FLinearColor(0, 0, 0.25 + (1 - (z + 800) / -850) * 0.75);
		}
	}
	return color;
}

