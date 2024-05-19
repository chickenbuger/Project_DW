// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DreamWorld/DreamWorldGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeDreamWorldGameMode() {}
// Cross Module References
	DREAMWORLD_API UClass* Z_Construct_UClass_ADreamWorldGameMode();
	DREAMWORLD_API UClass* Z_Construct_UClass_ADreamWorldGameMode_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_DreamWorld();
// End Cross Module References
	void ADreamWorldGameMode::StaticRegisterNativesADreamWorldGameMode()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ADreamWorldGameMode);
	UClass* Z_Construct_UClass_ADreamWorldGameMode_NoRegister()
	{
		return ADreamWorldGameMode::StaticClass();
	}
	struct Z_Construct_UClass_ADreamWorldGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ADreamWorldGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_DreamWorld,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ADreamWorldGameMode_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADreamWorldGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "DreamWorldGameMode.h" },
		{ "ModuleRelativePath", "DreamWorldGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ADreamWorldGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ADreamWorldGameMode>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ADreamWorldGameMode_Statics::ClassParams = {
		&ADreamWorldGameMode::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x008802ACu,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ADreamWorldGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_ADreamWorldGameMode_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_ADreamWorldGameMode()
	{
		if (!Z_Registration_Info_UClass_ADreamWorldGameMode.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ADreamWorldGameMode.OuterSingleton, Z_Construct_UClass_ADreamWorldGameMode_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ADreamWorldGameMode.OuterSingleton;
	}
	template<> DREAMWORLD_API UClass* StaticClass<ADreamWorldGameMode>()
	{
		return ADreamWorldGameMode::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ADreamWorldGameMode);
	ADreamWorldGameMode::~ADreamWorldGameMode() {}
	struct Z_CompiledInDeferFile_FID_PROJECT_DW_DreamWorld_Source_DreamWorld_DreamWorldGameMode_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_PROJECT_DW_DreamWorld_Source_DreamWorld_DreamWorldGameMode_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ADreamWorldGameMode, ADreamWorldGameMode::StaticClass, TEXT("ADreamWorldGameMode"), &Z_Registration_Info_UClass_ADreamWorldGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ADreamWorldGameMode), 2337155303U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_PROJECT_DW_DreamWorld_Source_DreamWorld_DreamWorldGameMode_h_1434837776(TEXT("/Script/DreamWorld"),
		Z_CompiledInDeferFile_FID_PROJECT_DW_DreamWorld_Source_DreamWorld_DreamWorldGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_PROJECT_DW_DreamWorld_Source_DreamWorld_DreamWorldGameMode_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
