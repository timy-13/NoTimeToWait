// Fill out your copyright notice in the Description page of Project Settings.


#include "NTTWGameplayTags.h"

namespace NTTWGameplayTags
{
	UE_DEFINE_GAMEPLAY_TAG(TAG_Food, "Food");

	UE_DEFINE_GAMEPLAY_TAG(TAG_Food_Bread, "Food.Bread");

	UE_DEFINE_GAMEPLAY_TAG(TAG_Food_Watermelon, "Food.Watermelon");

	UE_DEFINE_GAMEPLAY_TAG(TAG_Interaction_Grabbed, "Interaction.Grabbed");

	UE_DEFINE_GAMEPLAY_TAG(TAG_Interaction_NotGrabbed, "Interaction.NotGrabbed");

	UE_DEFINE_GAMEPLAY_TAG(TAG_Table_Customer_Served, "Table.Customer.Served");

	UE_DEFINE_GAMEPLAY_TAG(TAG_Table_Customer_NotServed, "Table.Customer.NotServed");

	UE_DEFINE_GAMEPLAY_TAG(TAG_Table_Customer_WaitingForMenu, "Table.Customer.WaitingForMenu");

	UE_DEFINE_GAMEPLAY_TAG(TAG_Table_Customer_WaitingForFood, "Table.Customer.WaitingForFood");

	UE_DEFINE_GAMEPLAY_TAG(TAG_Table_Empty, "Table.Empty");

	UE_DEFINE_GAMEPLAY_TAG(TAG_Table_Dirty, "Table.Dirty");

	UE_DEFINE_GAMEPLAY_TAG(TAG_Customer_Normal, "Customer.Normal");
}