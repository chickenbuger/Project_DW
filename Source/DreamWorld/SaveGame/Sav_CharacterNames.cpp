// Fill out your copyright notice in the Description page of Project Settings.


#include "DreamWorld/SaveGame/Sav_CharacterNames.h"

bool USav_CharacterNames::IsExistName(const FString In_Name)
{
	IsExist = false;
	// 1~3 index verify
	for (int i = 1; i <= 3; i++)
	{
		//�ε����� ���� �����Ͱ� �������� �ʴ´ٸ� nullptr ��ȯ
		const FString* name = TotalPlayerNames.Find(i);
		if (nullptr != name)
		{
			//ã�� �̸��� �ش� index�� �̸��� ���ٸ� true ���� �� �ݺ� �ߴ�
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
