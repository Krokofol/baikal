// Fill out your copyright notice in the Description page of Project Settings.


#include "SurfaceNodeUtils.h"
#include <iostream>
#include <fstream>

using namespace std;

void USurfaceNodeUtils::getNodes(
	FString userDir,
	int32 horizontalScale,
	TArray<FVector>& coordinates,
	int32& nodesCountX,
	int32& nodesCountY
) {
	TArray<FString> lines = TArray<FString>();
	FFileHelper::LoadFileToStringArray(lines, *fileName(userDir));

	nodesCountX = lines.Num();
	nodesCountY = countColumns(lines[0]);
	int32 nodesCounter = 0;

	getVertexes(lines, nodesCountX, nodesCountY, horizontalScale, coordinates);

	UE_LOG(LogTemp, Display, TEXT("node lines count is: %d"), nodesCountX);
	UE_LOG(LogTemp, Display, TEXT("node columns count is: %d"), nodesCountY);
	UE_LOG(LogTemp, Display, TEXT("nodes count is: % d"), coordinates.Num());

	return;
}

void USurfaceNodeUtils::generateTriangles(
	int32 nodesCountX,
	int32 nodesCountY,
	TArray<int32>& triangles
) {
	triangles = TArray<int32>();
	ofstream myfile;
	myfile.open("C:/Autodesk/example.txt");

	for (int x = 0; x < nodesCountX - 1; x++) {
		for (int y = 0; y < nodesCountY - 1; y++) {
			//first triangle (1)
			triangles.Add(x * nodesCountY + y);
			triangles.Add((x + 1) * nodesCountY + y);
			triangles.Add(x * nodesCountY + (y + 1));
			myfile << x * nodesCountY + y << ";" << (x + 1)* nodesCountY + y << ";" << x * nodesCountY + (y + 1) << "\n";
			//second triangle (2, backside)
			triangles.Add(x * nodesCountY + (y + 1));
			triangles.Add((x + 1) * nodesCountY + y);
			triangles.Add((x + 1) * nodesCountY + (y + 1));
			myfile << x * nodesCountY + (y + 1) << ";" << (x + 1) * nodesCountY + y << ";" << (x + 1) * nodesCountY + (y + 1) << "\n";
		}
	}
	myfile.close();
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

TArray<FVector> USurfaceNodeUtils::takeEach(
	int32 x1, int32 y1, int32 x2, int32 y2, 
	TArray<FVector> nodes, 
	int32 skip,
	int32 nodesCountX,
	int32 nodesCountY
) {
	TArray<FVector> actualNodes = TArray<FVector>();
	int32 minX = min(x1, x2);
	int32 maxX = max(x1, x2);
	int32 minY = min(y1, y2);
	int32 maxY = max(y1, y2);
	
	for (int i = minX; i <= maxX; i++) {
		for (int j = minY; j <= maxY; j++) {
			if ((i - minX) % skip == 0 && (j - minY) % skip == 0) {
				actualNodes.Add(nodes[nodesCountY * i + j]);
			}
		}
	}

	return actualNodes;
}

TArray<FLinearColor> USurfaceNodeUtils::colorVertexes(TArray<FVector> nodes)
{
	TArray<FLinearColor> colors = TArray<FLinearColor>();
	for (FVector node : nodes)
	{
		colors.Add(getColor(node.Z - 430));
	}
	return colors;
}

FString USurfaceNodeUtils::fileName(FString userDir)
{
	return FString(userDir + ".Baikal/Example.txt");
}

int32 USurfaceNodeUtils::countColumns(FString line) {
	int32 result = 0;
	for (TCHAR symbol: line.GetCharArray())
		if (symbol == TCHAR(' '))
			result++;
	return ++result;
}

void USurfaceNodeUtils::getVertexes(TArray<FString> lines, int32 countX, int32 countY, int32 horizontalScale, TArray<FVector>& coordinates)
{
	coordinates = TArray<FVector>();
	for (int32 x = 0; x < lines.Num(); x++) {
		addLineVertexes(x, lines[x], countX, countY, horizontalScale, coordinates);
	}
}

void USurfaceNodeUtils::addLineVertexes(int32 x, FString line, int32 countX, int32 countY, int32 horizontalScale, TArray<FVector>& vertexes)
{
	TArray<FString> digits;
	line.ParseIntoArray(digits, *FString(" "));
	for (int32 y = 0; y < digits.Num(); y++) {
		int32 z = FCString::Atoi(*digits[y]);
		addVertex(x - countX / 2, - y + countY / 2, z, horizontalScale, vertexes);
	}
}

void USurfaceNodeUtils::addVertex(int32 x, int32 y, int32 z, int32 horizontalScale, TArray<FVector>& coordinates)
{
	coordinates.Add(FVector(x * horizontalScale, y * horizontalScale, z));
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

