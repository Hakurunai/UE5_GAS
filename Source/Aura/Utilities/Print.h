// Copyright Hakurunai

#pragma once

#define PRINT(Time, Color, String, ...) if (GEngine)\
{GEngine->AddOnScreenDebugMessage(-1, Time, Color, FString::Printf(TEXT(String), __VA_ARGS__));}

#define PRINT_TEXT(Time, Color, String) if (GEngine)\
{GEngine->AddOnScreenDebugMessage(-1, Time, Color, TEXT(String));}

#define DEBUGPRINT(String, ...) if (GEngine)\
{GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT(String), __VA_ARGS__));}