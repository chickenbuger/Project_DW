// Fill out your copyright notice in the Description page of Project Settings.


#include "DreamWorld/SaveGame/Sav_CharacterNames.h"

bool USav_CharacterNames::IsExistName(const FString In_Name)
{
	IsExist = false;
	// 1~3 index verify
	for (int i = 1; i <= 3; i++)
	{
		//인덱스에 대한 데이터가 존재하지 않는다면 nullptr 반환
		const FString* name = TotalPlayerNames.Find(i);
		if (nullptr != name)
		{
			//찾는 이름과 해당 index의 이름이 같다면 true 설정 및 반복 중단
			if (*name == In_Name)
			{
				IsExist = true;
				break;
			}
		}
	}
	return IsExist;
}

bool USav_CharacterNames::IsExistIndex(const int In_Index)
{
	IsExist = false;

	if (nullptr != TotalPlayerNames.Find(In_Index))
	{
		IsExist = true;
	}

	return IsExist;
}
