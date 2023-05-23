

#include "UGameBlueprintFunctionLibrary.h"
#include "SGameCharacter.h"
#include "SItem.h"
#include "Action/SActionData.h"
#include "SGameMacros.h"
#include "Kismet/GameplayStatics.h"

// player
ASGameCharacter* UGameBlueprintFunctionLibrary::GetPlayer(const UObject* WorldContextObject)
{
	if(ASGameCharacter* player=Cast<ASGameCharacter>(UGameplayStatics::GetPlayerCharacter(WorldContextObject,0)))
	{
		return player;
	}
	//DISPLAY_SCREEN("Fail to cast to player!");
	return  nullptr;
}

void UGameBlueprintFunctionLibrary::ControlPlayerInput(const UObject* WorldContextObject,bool bIsEnabled)
{
	
	ACharacter* Player =  UGameplayStatics::GetPlayerCharacter(WorldContextObject,0);
	if(!Player)
	{
		return;
	}
	if(bIsEnabled)
	{
		Player->EnableInput(UGameplayStatics::GetPlayerController(WorldContextObject,0));
	}
	else
	{
		Player->DisableInput(UGameplayStatics::GetPlayerController(WorldContextObject,0));
	}
	
}

//item
void UGameBlueprintFunctionLibrary::FindItemInDataTable(FSItem item, bool& bIsFound,FSItemProperty& category)
{
	const UDataTable* DataTablePtr=LoadObject<UDataTable>
	(nullptr,UTF8_TO_TCHAR("DataTable'/Game/Data/ItemCategoryDataTable.ItemCategoryDataTable'"));
	FString ContextString;
	const FName ID=item.ID;
	TArray<FName> RowNames=DataTablePtr->GetRowNames();
	for(const auto& RowName:RowNames)
	{
		if(ID == RowName)
		{
			if(const FSItemProperty* RowPtr = DataTablePtr->FindRow<FSItemProperty>(RowName,ContextString))
			{
				//DISPLAY_SCREEN(TEXT("Success to load item category!"));
				category=*RowPtr;
				bIsFound=true;
				return;
			}
		}
	}
	bIsFound=false;
}

void UGameBlueprintFunctionLibrary::FindActionInDataTable(FName Name, bool& bIsFound, FSActionProperty& Property)
{
	const UDataTable* DataTablePtr=LoadObject<UDataTable>
(nullptr,UTF8_TO_TCHAR("DataTable'/Game/Data/ActionPropertyDataTable.ActionPropertyDataTable'"));
	FString ContextString;
	const FName ActionName=Name;
	TArray<FName> RowNames=DataTablePtr->GetRowNames();
	for(const auto& RowName:RowNames)
	{
		if(ActionName == RowName)
		{
			if(const FSActionProperty* RowPtr = DataTablePtr->FindRow<FSActionProperty>(RowName,ContextString))
			{
				//DISPLAY_SCREEN(TEXT("Success to load Action category!"));
				Property= *RowPtr;
				bIsFound=true;
				return;
			}
		}
	}
	bIsFound=false;
}
