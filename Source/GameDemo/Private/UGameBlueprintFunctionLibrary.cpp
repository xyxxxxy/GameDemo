

#include "UGameBlueprintFunctionLibrary.h"
#include "SGameCharacter.h"
#include "SItem.h"
#include "Action/SActionData.h"
#include "SGameMacros.h"
#include "Kismet/GameplayStatics.h"

// player
ASGameCharacter* UGameBlueprintFunctionLibrary::GetPlayer()
{
	if(ASGameCharacter* player=Cast<ASGameCharacter>(UGameplayStatics::GetPlayerPawn(nullptr,0)))
	{
		return player;
	}
	DISPLAY_SCREEN("Fail to cast to player!");
	return  nullptr;
}

void UGameBlueprintFunctionLibrary::ControlPlayerInput(bool bIsEnabled)
{
	ASGameCharacter* player=GetPlayer();
	if(!player)
	{
		return;
	}
	if(bIsEnabled)
	{
		player->EnableInput(UGameplayStatics::GetPlayerController(nullptr,0));
	}
	else
	{
		player->DisableInput(UGameplayStatics::GetPlayerController(nullptr,0));
	}
	
}

//item
void UGameBlueprintFunctionLibrary::FindItemInDataTable(FSItem item, bool& bIsFound,FSItemCategory& category)
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
			if(const FSItemCategory* RowPtr = DataTablePtr->FindRow<FSItemCategory>(RowName,ContextString))
			{
				DISPLAY_SCREEN(TEXT("Success to load item category!"));
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
				DISPLAY_SCREEN(TEXT("Success to load Action category!"));
				Property= *RowPtr;
				bIsFound=true;
				return;
			}
		}
	}
	bIsFound=false;
}
