

#include "UGameBlueprintFunctionLibrary.h"
#include "SGameCharacter.h"
#include "SItem.h"
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

void UGameBlueprintFunctionLibrary::EnabledInput(bool bIsEnabled)
{
	TArray<AActor*> AllPlayers;
	
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
	for(const auto& name:RowNames)
	{
		if(ID == name)
		{
			if(const FSItemCategory* RowPtr = DataTablePtr->FindRow<FSItemCategory>(name,ContextString))
			{
				DISPLAY_SCREEN(TEXT("Success to load category!"));
				category=*RowPtr;
				bIsFound=true;
				return;
			}
		}
	}
	bIsFound=false;
}
