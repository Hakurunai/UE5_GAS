// Copyright Hakurunai

#pragma once

//CUSTOM TODO : Print without __VA_ARGS__ to be able to only render text on screen
#define PRINT(Time, Color, String, ...) if (GEngine)\
{GEngine->AddOnScreenDebugMessage(-1, Time, Color, FString::Printf(TEXT(String), __VA_ARGS__));}

#define DPRINT(String, ...) if (GEngine)\
{GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT(String), __VA_ARGS__));}