#pragma once
#include <Windows.h>
#include <UE4/UE4.h>
#include <string>

#ifdef _MSC_VER
#pragma pack(push, 0x8)
#endif


struct FNameEntry
{
	uint32_t Index;
	uint32_t pad;
	FNameEntry* HashNext;
	char AnsiName[1024];

	const int GetIndex() const { return Index >> 1; }
	const char* GetAnsiName() const { return AnsiName; }
};

class TNameEntryArray
{
public:

	bool IsValidIndex(uint32_t index) const { return index < NumElements; }

	FNameEntry const* GetById(uint32_t index) const { return *GetItemPtr(index); }

	FNameEntry const* const* GetItemPtr(uint32_t Index) const {
		const auto ChunkIndex = Index / 16384;
		const auto WithinChunkIndex = Index % 16384;
		const auto Chunk = Chunks[ChunkIndex];
		return Chunk + WithinChunkIndex;
	}

	FNameEntry** Chunks[128];
	uint32_t NumElements = 0;
	uint32_t NumChunks = 0;
};

struct FName
{
	int ComparisonIndex = 0;
	int Number = 0;

	static inline TNameEntryArray* GNames = nullptr;

	static const char* GetNameByIdFast(int Id) {
		auto NameEntry = GNames->GetById(Id);
		if (!NameEntry) return nullptr;
		return NameEntry->GetAnsiName();
	}

	static std::string GetNameById(int Id) {
		auto NameEntry = GNames->GetById(Id);
		if (!NameEntry) return std::string();
		return NameEntry->GetAnsiName();
	}

	const char* GetNameFast() const {
		auto NameEntry = GNames->GetById(ComparisonIndex);
		if (!NameEntry) return nullptr;
		return NameEntry->GetAnsiName();
	}

	const std::string GetName() const {
		auto NameEntry = GNames->GetById(ComparisonIndex);
		if (!NameEntry) return std::string();
		return NameEntry->GetAnsiName();
	};

	inline bool operator==(const FName& other) const {
		return ComparisonIndex == other.ComparisonIndex;
	};

	FName() {}

	FName(const char* find) {
		for (auto i = 6000u; i < GNames->NumElements; i++)
		{
			auto name = GetNameByIdFast(i);
			if (!name) continue;
			if (strcmp(name, find) == 0) {
				ComparisonIndex = i;
				return;
			};
		}
	}
};

struct FUObjectItem
{
	class UObject* Object;
	int Flags;
	int ClusterIndex;
	int SerialNumber;
	int pad;
};

struct TUObjectArray
{
	FUObjectItem* Objects;
	int MaxElements;
	int NumElements;

	class UObject* GetByIndex(int index) { return Objects[index].Object; }
};

class UClass;
class UObject
{
public:
	UObject(UObject* addr) { *this = addr; }
	static inline TUObjectArray* GObjects = nullptr;
	void* Vtable; // 0x0
	int ObjectFlags; // 0x8
	int InternalIndex; // 0xC
	UClass* Class; // 0x10
	FName Name; // 0x18
	UObject* Outer; // 0x20

	std::string GetName() const;

	const char* GetNameFast() const;

	std::string GetFullName() const;

	template<typename T>
	static T* FindObject(const std::string& name)
	{
		for (int i = 0; i < GObjects->NumElements; ++i)
		{
			auto object = GObjects->GetByIndex(i);

			if (object == nullptr)
			{
				continue;
			}

			if (object->GetFullName() == name)
			{
				return static_cast<T*>(object);
			}
		}
		return nullptr;
	}

	static UClass* FindClass(const std::string& name)
	{
		return FindObject<UClass>(name);
	}

	template<typename T>
	static T* GetObjectCasted(uint32_t index)
	{
		return static_cast<T*>(GObjects->GetByIndex(index));
	}

	bool IsA(UClass* cmp) const;

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindObject<UClass>("Class CoreUObject.Object");
		return ptr;
	}
};

class UField : public UObject
{
public:
	using UObject::UObject;
	UField* Next;
};

class UProperty : public UField
{
public:
	int ArrayDim;
	int ElementSize;
	uint64_t PropertyFlags;
	char pad[0xC];
	int Offset_Internal;
	UProperty* PropertyLinkNext;
	UProperty* NextRef;
	UProperty* DestructorLinkNext;
	UProperty* PostConstructLinkNext;
};


class UStruct : public UField
{
public:
	using UField::UField;

	UStruct* SuperField;
	UField* Children;
	int PropertySize;
	int MinAlignment;
	TArray<uint8_t> Script;
	UProperty* PropertyLink;
	UProperty* RefLink;
	UProperty* DestructorLink;
	UProperty* PostConstructLink;
	TArray<UObject*> ScriptObjectReferences;
};
//nemtom
class UFunction : public UStruct
{
public:
	int FunctionFlags;
	uint16_t RepOffset;
	uint8_t NumParms;
	char pad;
	uint16_t ParmsSize;
	uint16_t ReturnValueOffset;
	uint16_t RPCId;
	uint16_t RPCResponseId;
	UProperty* FirstPropertyToInit;
	UFunction* EventGraphFunction; //0x00A0
	int EventGraphCallOffset;
	char pad_0x00AC[0x4]; //0x00AC
	void* Func; //0x00B0
};

// even talan? 55 new, 59 olddddddddddd
inline void ProcessEvent(void* obj, UFunction* function, void* parms)
{
	auto vtable = *reinterpret_cast<void***>(obj);
	reinterpret_cast<void(*)(void*, UFunction*, void*)>(vtable[55])(obj, function, parms);
}

template<typename Fn>
inline Fn GetVFunction(const void* instance, std::size_t index)
{
	auto vtable = *reinterpret_cast<const void***>(const_cast<void*>(instance));
	return reinterpret_cast<Fn>(vtable[index]);
}

class UClass : public UStruct
{
public:
	using UStruct::UStruct;
	unsigned char                                      UnknownData00[0x138];                                     // 0x0088(0x0138) MISSED OFFSET

	template<typename T>
	inline T* CreateDefaultObject()
	{
		return static_cast<T*>(CreateDefaultObject());
	}

	inline UObject* CreateDefaultObject()
	{
		return GetVFunction<UObject* (*)(UClass*)>(this, 88)(this);
	}

};

class FString : public TArray<wchar_t>
{
public:
	inline FString()
	{
	};

	FString(const wchar_t* other)
	{
		Max = Count = *other ? static_cast<int>(std::wcslen(other)) + 1 : 0;

		if (Count)
		{
			Data = const_cast<wchar_t*>(other);
		}
	};
	FString(const wchar_t* other, int count)
	{
		Data = const_cast<wchar_t*>(other);;
		Max = Count = count;
	};

	inline bool IsValid() const
	{
		return Data != nullptr;
	}

	inline const wchar_t* wide() const
	{
		return Data;
	}

	int multi(char* name, int size) const
	{
		return WideCharToMultiByte(CP_UTF8, 0, Data, Count, name, size, nullptr, nullptr) - 1;
	}

	inline const wchar_t* c_str() const
	{
		if (Data)
			return Data;
		return L"";
	}
};




enum class EPlayerActivityType : uint8_t
{
	None = 0,
	Bailing = 1,
	Cannon = 2,
	Cannon_END = 3,
	Capstan = 4,
	Capstan_END = 5,
	CarryingBooty = 6,
	CarryingBooty_END = 7,
	Dead = 8,
	Dead_END = 9,
	Digging = 10,
	Dousing = 11,
	EmptyingBucket = 12,
	Harpoon = 13,
	Harpoon_END = 14,
	LoseHealth = 15,
	Repairing = 16,
	Sails = 17,
	Sails_END = 18,
	UndoingRepair = 19,
	Wheel = 20,
	Wheel_END = 21,
};

struct FPirateDescription
{

};

struct AAthenaPlayerCharacter {

};

struct APlayerState // 11.06
{
	char pad[0x3c8];
	float                                              Score;                                                     // 0x3c8(0x0004) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float											   Ping;                                                      // 0x03CC(0x0001) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	FString							                   PlayerName;                                                // 0x03D0 (BlueprintVisible, BlueprintReadOnly, Net, ZeroConstructor, RepNotify, HasGetValueTypeHash)


	EPlayerActivityType GetPlayerActivity()
	{
		static auto fn = UObject::FindObject<UFunction>("Function Athena.AthenaPlayerState.GetPlayerActivity");
		EPlayerActivityType activity;
		ProcessEvent(this, fn, &activity);
		return activity;
	}


	FPirateDescription GetPirateDesc()
	{
		static auto fn = UObject::FindObject<UFunction>("Function Athena.AthenaPlayerState.GetPirateDesc");
		FPirateDescription desc;
		ProcessEvent(this, fn, &desc);
		return desc;
	}

};
// 11.06
struct FMinimalViewInfo {
	FVector Location;
	FRotator Rotation;
	char UnknownData_18[0x10];
	float FOV;  // 0x28(0x4)
};

struct UFOVHandlerFunctions_GetTargetFOV_Params
{
	class AAthenaPlayerCharacter* Character;
	float ReturnValue;
};

struct AGameCustomizationService_SetTime_Params
{
	int Hours;

	void SetTime(int Hours)
	{
		static auto fn = UObject::FindObject<UFunction>("Function Athena.GameCustomizationService.SetTime");
		AGameCustomizationService_SetTime_Params params;
		params.Hours = Hours;
		ProcessEvent(this, fn, &params);
	}
};

struct UFOVHandlerFunctions_SetTargetFOV_Params
{
	class AAthenaPlayerCharacter* Character;
	float TargetFOV;

	void SetTargetFOV(class AAthenaPlayerCharacter* Character, float TargetFOV)
	{
		static auto fn = UObject::FindObject<UFunction>("Function Athena.FOVHandlerFunctions.SetTargetFOV");
		UFOVHandlerFunctions_SetTargetFOV_Params params;
		params.Character = Character;
		params.TargetFOV = TargetFOV;
		ProcessEvent(this, fn, &params);
	}
};

FVector2D RotatePoint(FVector2D pointToRotate, FVector2D centerPoint, float angle, bool angleInRadians = false)
{
	if (!angleInRadians)
		angle = static_cast<float>(angle * (PI / 180.f));
	float cosTheta = static_cast<float>(cos(angle));
	float sinTheta = static_cast<float>(sin(angle));
	FVector2D returnVec = FVector2D(cosTheta * (pointToRotate.X - centerPoint.X) - sinTheta * (pointToRotate.Y - centerPoint.Y), sinTheta * (pointToRotate.X - centerPoint.X) + cosTheta * (pointToRotate.Y - centerPoint.Y)
	);
	returnVec += centerPoint;
	return returnVec;
}

struct FText
{
	char UnknownData[0x38];
};

// 11.06
struct FCameraCacheEntry {
	float TimeStamp;
	char pad[0x10]; //0xc old
	FMinimalViewInfo POV; // 0x10(0x5a0)
};
//11.06
struct FTViewTarget
{
	class AActor* Target;                                                    // 0x0000(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	unsigned char                                      UnknownData_KHBN[0x8];                                     // 0x0008(0x0008) MISSED OFFSET (FIX SPACE BETWEEN PREVIOUS PROPERTY)
	struct FMinimalViewInfo                            POV;                                                       // 0x0010(0x05A0) (Edit, BlueprintVisible)
	class APlayerState* PlayerState;                                               // 0x05B0(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash)
	unsigned char                                      UnknownData_QIMB[0x8];                                     // 0x05B8(0x0008) MISSED OFFSET (PADDING)

};

struct AController_K2_GetPawn_Params
{
	class APawn* ReturnValue;
};
//11.06
struct APlayerCameraManager {
	char pad[0x0440];
	FCameraCacheEntry CameraCache; // 0x0440
	FCameraCacheEntry LastFrameCameraCache;
	FTViewTarget ViewTarget;
	FTViewTarget PendingViewTarget;


	FVector GetCameraLocation() {
		static auto fn = UObject::FindObject<UFunction>("Function Engine.PlayerCameraManager.GetCameraLocation");
		FVector location;
		ProcessEvent(this, fn, &location);
		return location;
	};
	FRotator GetCameraRotation() {
		static auto fn = UObject::FindObject<UFunction>("Function Engine.PlayerCameraManager.GetCameraRotation");
		FRotator rotation;
		ProcessEvent(this, fn, &rotation);
		return rotation;
	}
};


struct FKey
{
	FName KeyName;
	unsigned char UnknownData00[0x18] = {};

	FKey() {};
	FKey(const char* InName) : KeyName(FName(InName)) {}
};

struct AController {

	char pad_0000[0x3e0];
	class ACharacter* Character; //0x03E0 11.22
	char pad_0480[0x70];
	APlayerCameraManager* PlayerCameraManager; // 0x0458(0x0008) //11.22
	char pad_04f8[0x1119]; //  10F9 volt
	bool IdleDisconnectEnabled;//0x1559 11.06  11.22 0x1579 ?

	void SetTime(int Hours)
	{
		static auto fn = UObject::FindObject<UFunction>("Function Athena.GameCustomizationService.SetTime");
		AGameCustomizationService_SetTime_Params params;
		params.Hours = Hours;
		ProcessEvent(this, fn, &params);
	}

	void SendToConsole(FString& cmd) {
		static auto fn = UObject::FindObject<UFunction>("Function Engine.PlayerController.SendToConsole");
		ProcessEvent(this, fn, &cmd);
	}

	bool WasInputKeyJustPressed(const FKey& Key) {
		static auto fn = UObject::FindObject<UFunction>("Function Engine.PlayerController.WasInputKeyJustPressed");
		struct
		{
			FKey Key;

			bool ReturnValue = false;
		} params;

		params.Key = Key;
		ProcessEvent(this, fn, &params);

		return params.ReturnValue;
	}

	APawn* K2_GetPawn() {
		static auto fn = UObject::FindObject<UFunction>("Function Engine.Controller.K2_GetPawn");
		AController_K2_GetPawn_Params params;
		class APawn* ReturnValue;
		ProcessEvent(this, fn, &params);
		return params.ReturnValue;
	}

	bool ProjectWorldLocationToScreen(const FVector& WorldLocation, FVector2D& ScreenLocation) {
		static auto fn = UObject::FindObject<UFunction>("Function Engine.PlayerController.ProjectWorldLocationToScreen");
		struct
		{
			FVector WorldLocation;
			FVector2D ScreenLocation;
			bool ReturnValue = false;
		} params;

		params.WorldLocation = WorldLocation;
		ProcessEvent(this, fn, &params);
		ScreenLocation = params.ScreenLocation;
		return params.ReturnValue;
	}

	FRotator GetControlRotation() {
		static auto fn = UObject::FindObject<UFunction>("Function Engine.Pawn.GetControlRotation");
		struct FRotator rotation;
		ProcessEvent(this, fn, &rotation);
		return rotation;
	}

	FRotator GetDesiredRotation() {
		static auto fn = UObject::FindObject<UFunction>("Function Engine.Pawn.GetDesiredRotation");
		struct FRotator rotation;
		ProcessEvent(this, fn, &rotation);
		return rotation;
	}

	void AddYawInput(float Val) {
		static auto fn = UObject::FindObject<UFunction>("Function Engine.PlayerController.AddYawInput");
		ProcessEvent(this, fn, &Val);
	}

	void AddPitchInput(float Val) {
		static auto fn = UObject::FindObject<UFunction>("Function Engine.PlayerController.AddPitchInput");
		ProcessEvent(this, fn, &Val);
	}

	void FOV(float NewFOV) {
		static auto fn = UObject::FindObject<UFunction>("Function Engine.PlayerController.FOV");
		ProcessEvent(this, fn, &NewFOV);
	}

	bool LineOfSightTo(ACharacter* Other, const FVector& ViewPoint, const bool bAlternateChecks) {
		static auto fn = UObject::FindObject<UFunction>("Function Engine.Controller.LineOfSightTo");
		struct {
			ACharacter* Other = nullptr;
			FVector ViewPoint;
			bool bAlternateChecks = false;
			bool ReturnValue = false;
		} params;
		params.Other = Other;
		params.ViewPoint = ViewPoint;
		params.bAlternateChecks = bAlternateChecks;
		ProcessEvent(this, fn, &params);
		return params.ReturnValue;
	}
};

struct UHealthComponent {
	float GetMaxHealth() {
		static auto fn = UObject::FindObject<UFunction>("Function Athena.HealthComponent.GetMaxHealth");
		float health = 0.f;
		ProcessEvent(this, fn, &health);
		return health;
	}
	float GetCurrentHealth() {
		static auto fn = UObject::FindObject<UFunction>("Function Athena.HealthComponent.GetCurrentHealth");
		float health = 0.f;
		ProcessEvent(this, fn, &health);
		return health;
	};
};


// 0x7AB old   0x7B3 0x7AD 758? 5D8?   class Engine.Character
// 11.06 0x440(0x8)??? 0x5D0 volt
struct USkeletalMeshComponent {
	char pad[0x5d8];
	TArray<FTransform> SpaceBasesArray[2];
	int CurrentEditableSpaceBases;
	int CurrentReadSpaceBases;

	FName GetBoneName(int BoneIndex)
	{
		static auto fn = UObject::FindObject<UFunction>("Function Engine.SkinnedMeshComponent.GetBoneName");
		struct
		{
			int BoneIndex = 0;
			FName ReturnValue;
		} params;
		params.BoneIndex = BoneIndex;
		ProcessEvent(this, fn, &params);
		return params.ReturnValue;
	}

	FTransform K2_GetComponentToWorld() {
		static auto fn = UObject::FindObject<UFunction>("Function Engine.SceneComponent.K2_GetComponentToWorld");
		FTransform CompToWorld;
		ProcessEvent(this, fn, &CompToWorld);
		return CompToWorld;
	}

	bool GetBone(const uint32_t id, const FMatrix& componentToWorld, FVector& pos) {
		try {
			auto bones = SpaceBasesArray[CurrentReadSpaceBases];
			
			if (id >= bones.Count) return false;
			const auto& bone = bones[id];
			auto boneMatrix = bone.ToMatrixWithScale();
			auto world = boneMatrix * componentToWorld;
			pos = { world.M[3][0], world.M[3][1], world.M[3][2] };
			return true;
		}
		catch (...)
		{
			printf("error %d\n", __LINE__);
			return false;
		}
	}
};

struct UScriptViewportClient : UObject {
	char UnknownData_28[0x8]; // 0x28(0x08)
};

// Class Engine.GameViewportClient
// Size: 0x250 (Inherited: 0x30)
struct UGameViewportClient : UScriptViewportClient {
	char UnknownData_30[0x8]; // 0x30(0x08)
	struct UConsole* ViewportConsole; // 0x38(0x08)
	char DebugProperties[0x10]; // 0x40(0x10)
	char UnknownData_50[0x30]; // 0x50(0x30)
	struct UWorld* World; // 0x80(0x08)
	struct UGameInstance* GameInstance; // 0x88(0x08)
	char UnknownData_90[0x1c0]; // 0x90(0x1c0)

	void SSSwapControllers(); // Function Engine.GameViewportClient.SSSwapControllers // Exec|Native|Public // @ game+0x2fe5ca0
	void ShowTitleSafeArea(); // Function Engine.GameViewportClient.ShowTitleSafeArea // Exec|Native|Public // @ game+0x2fe5d50
	void SetConsoleTarget(int32_t PlayerIndex); // Function Engine.GameViewportClient.SetConsoleTarget // Exec|Native|Public // @ game+0x2fe5cc0
};

struct UAthenaGameViewportClient : UGameViewportClient {
	char UnknownData_250[0x10]; // 0x250(0x10)
};


struct AShipInternalWater {
	float GetNormalizedWaterAmount() {
		static auto fn = UObject::FindObject<UFunction>("Function Athena.ShipInternalWater.GetNormalizedWaterAmount");
		float params = 0.f;
		ProcessEvent(this, fn, &params);
		return params;
	}
};

struct ADamageZone {
	char pad[0x0654];
	int32_t DamageLevel; // 0x654(0x04)
};

//11.22
struct AHullDamage {
	char pad[0x0410];
	struct TArray<struct ADamageZone*> DamageZones; // 0x410(0x10)
	TArray<class ACharacter*> ActiveHullDamageZones; // 0x0420
};

struct UDrowningComponent {
	float GetOxygenLevel() {
		static auto fn = UObject::FindObject<UFunction>("Function Athena.DrowningComponent.GetOxygenLevel");
		float oxygen;
		ProcessEvent(this, fn, &oxygen);
		return oxygen;
	}
};
//11.22
struct AFauna {
	char pad1[0x818];
	FString* DisplayName; // 0x818(0x38)
};

enum class ESwimmingCreatureType : uint8_t
{
	SwimmingCreature = 0,
	Shark = 1,
	TinyShark = 2,
	Siren = 3,
	ESwimmingCreatureType_MAX = 4
};
// 11.22
struct ASharkPawn {
	char pad1[0x4c0];
	USkeletalMeshComponent* Mesh; // 0x4c0(0x8)
	char pad2[0x5C]; // 0x5C new 0x64 old?
	ESwimmingCreatureType SwimmingCreatureType; // 0x524
};
//11.22
struct FAIEncounterSpecification
{
	char pad[0x80];
	FString* LocalisableName; // 0x0080 
};

struct FStorageContainerNode {
	struct UClass* ItemDesc; // 0x00(0x08)
	int32_t NumItems; // 0x08(0x04)
	char UnknownData_C[0x4]; // 0x0c(0x04)
};

struct FStorageContainerBackingStore {
	char pad_0[0x20];
	struct TArray<struct FStorageContainerNode> ContainerNodes; // 0x20(0x10)
	bool AllowedItemsAreCached; // 0x30(0x01)
	char UnknownData_31[0x7]; // 0x31(0x07)
	char CachedAllowedItems[0x8]; // 0x38(0x08)
};


struct UStorageContainerComponent {
	char pad_00[0xc8];
	char UnknownData_C8[0x18]; // 0xc8(0x18)
	char ContainerDisplayName[0x38]; // 0xe0(0x38)
	char UnknownData_118[0x8]; // 0x118(0x08)
	char InstanceTransform[0x30]; // 0x120(0x30)
	struct FStorageContainerBackingStore ContainerNodes; // 0x150(0x40)
	struct TArray<struct AActor*> QuickGivers; // 0x190(0x10)
	struct TArray<struct AActor*> QuickTakers; // 0x1a0(0x10)
	char AddItemSFX[0x8]; // 0x1b0(0x08)
	char TakeItemSFX[0x8]; // 0x1b8(0x08)
	char OpenContainerSFX[0x8]; // 0x1c0(0x08)
	char BeginQuickGiveSFX[0x8]; // 0x1c8(0x08)
	char EndQuickGiveSFX[0x8]; // 0x1d0(0x08)
	char BeginQuickTakeSFX[0x8]; // 0x1d8(0x08)
	char EndQuickTakeSFX[0x8]; // 0x1e0(0x08)
	char StorageContainerSelector[0x8]; // 0x1e8(0x08)
	char UnknownData_1F0[0x30]; // 0x1f0(0x30)
	char SfxPool[0x8]; // 0x220(0x08)
	char UnknownData_228[0x40]; // 0x228(0x40)
	bool ShowCapacityInDescription; // 0x268(0x01)
	char UnknownData_269[0x9f]; // 0x269(0x9f)
	char Aggregator[0x8]; // 0x308(0x08)

	//void TakeItem(struct AActor* Player, int32_t NodeIndex); // Function Athena.StorageContainerComponent.TakeItem // Final|Native|Public|BlueprintCallable // @ game+0x38b5810
	//void OnRep_QuickTakers(struct TArray<struct AActor*> InOldTakers); // Function Athena.StorageContainerComponent.OnRep_QuickTakers // Final|Native|Private // @ game+0x38b5560
	//void OnRep_QuickGivers(struct TArray<struct AActor*> InOldGivers); // Function Athena.StorageContainerComponent.OnRep_QuickGivers // Final|Native|Private // @ game+0x38b5460
	//void OnRep_ContentsChanged(struct FStorageContainerBackingStore InOldItemCount); // Function Athena.StorageContainerComponent.OnRep_ContentsChanged // Final|Native|Private // @ game+0x38b52d0
	//void Multicast_DetachAllPlayersRPC(); // Function Athena.StorageContainerComponent.Multicast_DetachAllPlayersRPC // Final|Net|NetReliableNative|Event|NetMulticast|Private // @ game+0x38b52b0
	//struct FText GetContainerDisplayName(); // Function Athena.StorageContainerComponent.GetContainerDisplayName // Final|Native|Public|BlueprintCallable|BlueprintPure|Const // @ game+0x38b5220
	//void AddItem(struct AActor* Player, struct UClass* InItemDesc); // Function Athena.StorageContainerComponent.AddItem // Final|Native|Public|BlueprintCallable // @ game+0x38b5010
};

struct AStorageContainer {
	char pad_00[0x468];
	char UnknownData_468[0x8]; // 0x468(0x08)
	char Mesh[0x8]; // 0x470(0x08)
	char InteractionRegion[0x8]; // 0x478(0x08)
	char UnknownData_480[0x14]; // 0x480(0x14)
	char TrackedActorType; // 0x494(0x01)
	char UnknownData_495[0x33]; // 0x495(0x33)
	char random_Bytes[0x10];
	class UStorageContainerComponent* StorageContainer;
};

struct FVector_NetQuantize : public FVector
{

};

//11.06 ez is jo sztem 11.22
struct FHitResult
{
	unsigned char                                      bBlockingHit : 1;                                         // 0x0000(0x0001)
	unsigned char                                      bStartPenetrating : 1;                                    // 0x0000(0x0001)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0001(0x0003) MISSED OFFSET
	float                                              Time;                                                     // 0x0004(0x0004) (ZeroConstructor, IsPlainOldData)
	float                                              Distance;                                                 // 0x0008(0x0004) (ZeroConstructor, IsPlainOldData)
	char pad_5894[0x48];
	float                                              PenetrationDepth;                                         // 0x0054(0x0004) (ZeroConstructor, IsPlainOldData)
	int                                                Item;                                                     // 0x0058(0x0004) (ZeroConstructor, IsPlainOldData)
	char pad_3424[0x18];
	struct FName                                       BoneName;                                                 // 0x0074(0x0008) (ZeroConstructor, IsPlainOldData)
	int                                                FaceIndex;                                                // 0x007C(0x0004) (ZeroConstructor, IsPlainOldData)
};

struct FRepMovement {
	struct FVector LinearVelocity; // 0x00(0x0c)
	struct FVector AngularVelocity; // 0x0c(0x0c)
	struct FVector Location; // 0x18(0x0c)
	struct FRotator Rotation; // 0x24(0x0c)
	char bSimulatedPhysicSleep : 1; // 0x30(0x01)
	char bRepPhysics : 1; // 0x30(0x01)
	char UnknownData_30_2 : 6; // 0x30(0x01)
	char LocationQuantizationLevel; // 0x31(0x01)
	char VelocityQuantizationLevel; // 0x32(0x01)
	char RotationQuantizationLevel; // 0x33(0x01)
	char UnknownData_34[0x4]; // 0x34(0x04)
};

struct AShipReplicatedM {
	char pad_0[0x90];
	struct FRepMovement ReplicatedMovement; // 0x94(0x38)
};

struct AActor : UObject {
	char PrimaryActorTick[0x50]; // 0x28(0x50)
	float CustomTimeDilation; // 0x78(0x04)
	char bAllowRemovalFromServerWhenCollisionMerged : 1; // 0x7c(0x01)
	char bAllowRemovalFromServerWhenAutomaticallyInstanced : 1; // 0x7c(0x01)
	char bHidden : 1; // 0x7c(0x01)
	char bNetTemporary : 1; // 0x7c(0x01)
	char bNetStartup : 1; // 0x7c(0x01)
	char bOnlyRelevantToOwner : 1; // 0x7c(0x01)
	char bAlwaysRelevant : 1; // 0x7c(0x01)
	char bReplicateMovement : 1; // 0x7c(0x01)
	char bTearOff : 1; // 0x7d(0x01)
	char bExchangedRoles : 1; // 0x7d(0x01)
	char bPendingNetUpdate : 1; // 0x7d(0x01)
	char bNetLoadOnClient : 1; // 0x7d(0x01)
	char bNetUseOwnerRelevancy : 1; // 0x7d(0x01)
	char bBlockInput : 1; // 0x7d(0x01)
	char UnknownData_7D_6 : 1; // 0x7d(0x01)
	char bCanBeInCluster : 1; // 0x7d(0x01)
	char UnknownData_7E_0 : 2; // 0x7e(0x01)
	char bActorEnableCollision : 1; // 0x7e(0x01)
	char UnknownData_7E_3 : 1; // 0x7e(0x01)
	char bReplicateAttachment : 1; // 0x7e(0x01)
	char UnknownData_7E_5 : 1; // 0x7e(0x01)
	char bReplicates : 1; // 0x7e(0x01)
	char UnknownData_7F[0x1]; // 0x7f(0x01)
	char OnPreNetOwnershipChange[0x1]; // 0x80(0x01)
	char UnknownData_81[0x1]; // 0x81(0x01)
	char RemoteRole; // 0x82(0x01)
	char UnknownData_83[0x5]; // 0x83(0x05)
	struct AActor* Owner; // 0x88(0x08)
	char SpawnRestrictions; // 0x90(0x01)
	char UnknownData_91[0x3]; // 0x91(0x03)
	struct FRepMovement ReplicatedMovement; // 0x94(0x38)
	char UnknownData_CC[0x4]; // 0xcc(0x04)
	char AttachmentReplication[0x48]; // 0xd0(0x48)
	char Role; // 0x118(0x01)
	char UnknownData_119[0x1]; // 0x119(0x01)
	char AutoReceiveInput; // 0x11a(0x01)
	char UnknownData_11B[0x1]; // 0x11b(0x01)
	int32_t InputPriority; // 0x11c(0x04)
	struct UInputComponent* InputComponent; // 0x120(0x08)
	float NetCullDistanceSquared; // 0x128(0x04)
	char UnknownData_12C[0x4]; // 0x12c(0x04)
	int32_t NetTag; // 0x130(0x04)
	float NetUpdateTime; // 0x134(0x04)
	float NetUpdateFrequency; // 0x138(0x04)
	float NetPriority; // 0x13c(0x04)
	float LastNetUpdateTime; // 0x140(0x04)
	struct FName NetDriverName; // 0x144(0x08)
	char bAutoDestroyWhenFinished : 1; // 0x14c(0x01)
	char bCanBeDamaged : 1; // 0x14c(0x01)
	char bActorIsBeingDestroyed : 1; // 0x14c(0x01)
	char bCollideWhenPlacing : 1; // 0x14c(0x01)
	char bFindCameraComponentWhenViewTarget : 1; // 0x14c(0x01)
	char bRelevantForNetworkReplays : 1; // 0x14c(0x01)
	char UnknownData_14C_6 : 2; // 0x14c(0x01)
	char UnknownData_14D[0x3]; // 0x14d(0x03)
	char SpawnCollisionHandlingMethod; // 0x150(0x01)
	char UnknownData_151[0x7]; // 0x151(0x07)
	struct APawn* Instigator; // 0x158(0x08)
	struct TArray<struct AActor*> Children; // 0x160(0x10)
	struct USceneComponent* RootComponent; // 0x170(0x08)
	struct TArray<struct AMatineeActor*> ControllingMatineeActors; // 0x178(0x10)
	float InitialLifeSpan; // 0x188(0x04)
	char UnknownData_18C[0x4]; // 0x18c(0x04)
	char bAllowReceiveTickEventOnDedicatedServer : 1; // 0x190(0x01)
	char UnknownData_190_1 : 7; // 0x190(0x01)
	char UnknownData_191[0x7]; // 0x191(0x07)
	struct TArray<struct FName> Layers; // 0x198(0x10)
	char ParentComponentActor[0x8]; // 0x1a8(0x08)
	struct TArray<struct AActor*> ChildComponentActors; // 0x1b0(0x10)
	char UnknownData_1C0[0x8]; // 0x1c0(0x08)
	char bActorSeamlessTraveled : 1; // 0x1c8(0x01)
	char bIgnoresOriginShifting : 1; // 0x1c8(0x01)
	char bEnableAutoLODGeneration : 1; // 0x1c8(0x01)
	char InvertFeatureCheck : 1; // 0x1c8(0x01)
	char UnknownData_1C8_4 : 4; // 0x1c8(0x01)
	char UnknownData_1C9[0x3]; // 0x1c9(0x03)
	struct FName Feature; // 0x1cc(0x08)
	char UnknownData_1D4[0x4]; // 0x1d4(0x04)
	struct TArray<struct FName> Tags; // 0x1d8(0x10)
	uint64_t HiddenEditorViews; // 0x1e8(0x08)
	char UnknownData_1F0[0x4]; // 0x1f0(0x04)
	char UnknownData_1F4[0x3c]; // 0x1f4(0x3c)
	char OnEndPlay[0x1]; // 0x230(0x01)
	bool bDoOverlapNotifiesOnLoad; // 0x231(0x01)
	char UnknownData_232[0xf6]; // 0x232(0xf6)
	struct TArray<struct UActorComponent*> BlueprintCreatedComponents; // 0x328(0x10)
	struct TArray<struct UActorComponent*> InstanceComponents; // 0x338(0x10)
	char UnknownData_348[0x8]; // 0x348(0x08)
	struct TArray<struct AActor*> ChildActorInterfaceProviders; // 0x350(0x10)
	char UnknownData_360[0x68]; // 0x360(0x68)
	double DormancyLingeringInSeconds; // 0x3c8(0x08)

	struct FVector GetActorRightVector()
	{
		static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.GetActorRightVector");
		FVector ReturnValue;
		ProcessEvent(this, fn, &ReturnValue);
		return ReturnValue;
	}
};

struct ANamedPawn {
	char pad[0x3e8];
	struct APlayerState* PlayerState; // 0x3e8(0x08)
};
// Class Engine.Pawn
// Size: 0x448 (Inherited: 0x3d0)
struct APawn : AActor {
	char pad[0x20];
	struct APlayerState* PlayerState; // 0x3f0(0x08)
	char pad2[0x50];
};

struct FWorldMapIslandDataCaptureParams
{
	char pad1[0x0018];
	struct FVector                                     WorldSpaceCameraPosition;                                  // 0x0018(0x000C) (Edit, ZeroConstructor, Transient, EditConst, IsPlainOldData, NoDestructor)
	char pad2[0x8];
	float                                              CameraOrthoWidth;                                          // 0x002C(0x0004) (Edit, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)

};

struct UWorldMapIslandDataAsset {
	char pad[0x0030];
	struct FWorldMapIslandDataCaptureParams            CaptureParams;                                             // 0x0030(0x0040) (Edit, BlueprintVisible, BlueprintReadOnly)
	FVector WorldSpaceCameraPosition;
	// ADD THE OFFSET OF CAPTUREPARAMS TO THIS OFFSET
};

// Class Athena.IslandDataAssetEntry
// Size: 0x118 (Inherited: 0x28)
struct UIslandDataAssetEntry {
	char pad_00[0x28];
	struct FName IslandName; // 0x28(0x08)
	struct TArray<struct FTreasureMapData> TreasureMaps; // 0x30(0x10)
	struct UWorldMapIslandDataAsset* WorldMapData; // 0x40(0x08)
	struct UGeneratedLocationsDataAsset* UndergroundTreasureLocationsSource; // 0x48(0x08)
	struct TArray<struct FVector> UndergroundTreasureLocations; // 0x50(0x10)
	struct ULandmarkTreasureLocationsDataAsset* LandmarkTreasureLocationsSource; // 0x60(0x08)
	struct UGeneratedLocationsDataAsset* AISpawnLocationsSource; // 0x68(0x08)
	struct TArray<struct FVector> AISpawnLocations; // 0x70(0x10)
	struct TArray<struct UIslandItemDataAsset*> IslandItemLocationDataSources; // 0x80(0x10)
	struct TArray<struct UIslandSalvageSpawnerCollection*> IslandSalvageSpawnerCollections; // 0x90(0x10)
	struct TArray<struct FTypedIslandItemSpawnLocationData> SalvageItemsLocationData; // 0xa0(0x10)
	FString* LocalisedName; // 0xb0(0x38)
	struct UAISpawner* AISpawner; // 0xe8(0x08)
	struct UAISpawner* CannonsAISpawner; // 0xf0(0x08)
	struct UAISpawner* EmergentCaptainSpawner; // 0xf8(0x08)
	struct UIslandMaterialStatusZone* IslandMaterialStatusZone; // 0x100(0x08)
	char StatToFireWhenPlayerSetsFootOnIsland[0x4]; // 0x108(0x04)
	char StatToFireWhenShipVisitsAnIsland[0x4]; // 0x10c(0x04)
	bool ShouldBeHiddenOnWorldMap; // 0x110(0x01)
	bool UseAdvancedSearchForMermaidSpawn; // 0x111(0x01)
	char IslandActiveEventType; // 0x112(0x01)
	char UnknownData_113[0x5]; // 0x113(0x05)
};

struct UIslandDataAsset {
	char pad[0x0048];
	struct TArray<struct UIslandDataAssetEntry*> IslandDataEntries; // 0x48(0x10)
};

struct AIslandService {
	char pad[0x0458];
	UIslandDataAsset* IslandDataAsset; // 0x458
};

struct FXMarksTheSpotMapMark {
	struct FVector2D Position; // 0x00(0x08)
	float Rotation; // 0x08(0x04)
	bool IsUnderground; // 0x0c(0x01)
	char UnknownData_D[0x3]; // 0x0d(0x03)
};

struct AXMarksTheSpotMap
{
	char pad1[0x0808];
	//struct FString                                     MapTexturePath;                                            // 0x0818(0x0010) (Net, ZeroConstructor, RepNotify, HasGetValueTypeHash)
	//char pad2[0x80];
	//TArray<struct FXMarksTheSpotMapMark>               Marks;                                                     // 0x08A8(0x0010) (Net, ZeroConstructor, RepNotify)
	//char pad3[0x18];
	//float                                              Rotation;                                                  // 0x08D0(0x0004) (Net, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)


	struct FString MapTexturePath; // 0x808(0x10)
	char MapInventoryTexturePath[0x10]; // 0x818(0x10)
	char UnknownData_828[0x70]; // 0x828(0x70)
	struct TArray<struct FXMarksTheSpotMapMark> Marks; // 0x898(0x10)
	char UnknownData_8A8[0x18]; // 0x8a8(0x18)
	float Rotation; // 0x8c0(0x04)
};

//11.22
struct UWieldedItemComponent {
	char pad[0x02F0];
	ACharacter* CurrentlyWieldedItem; // 0x02F0
};
//11.06 
struct FWeaponProjectileParams
{
	float                                              Damage;                                                   // 0x0000(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              DamageMultiplierAtMaximumRange;                           // 0x0004(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              LifeTime;                                                 // 0x0008(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              TrailFadeOutTime;                                         // 0x000C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              Velocity;                                                 // 0x0010(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	char pad_78[0x94];
};
//11.07
struct FProjectileShotParams
{
	int                                                Seed;                                                     // 0x0000(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              ProjectileDistributionMaxAngle;                           // 0x0004(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	int                                                NumberOfProjectiles;                                      // 0x0008(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              ProjectileMaximumRange;                                   // 0x000C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float											   ProjectileHitScanMaximumRange; // 0x10(0x04)
	float                                              ProjectileDamage;                                         // 0x0014(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              ProjectileDamageMultiplierAtMaximumRange;                 // 0x0018(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
};
//11.06 szerintem jo 11.22 nemneztem 100% át
struct FProjectileWeaponParameters {
	int AmmoClipSize; // 0x00(0x04)
	int AmmoCostPerShot; // 0x04(0x04)
	float EquipDuration; // 0x08(0x04)
	float IntoAimingDuration; // 0x0c(0x04)
	float RecoilDuration; // 0x10(0x04)
	float ReloadDuration; // 0x14(0x04)
	struct FProjectileShotParams HipFireProjectileShotParams; // 0x18(0x1c)
	struct FProjectileShotParams AimDownSightsProjectileShotParams; // 0x34(0x1c)
	int Seed; // 0x50(0x04)
	float ProjectileDistributionMaxAngle; // 0x54(0x04)
	int NumberOfProjectiles; // 0x58(0x04)
	float ProjectileMaximumRange; // 0x5c(0x04)
	float ProjectileHitScanMaximumRange; // 0x60(0x04)
	float ProjectileDamage; // 0x64(0x04)
	float ProjectileDamageMultiplierAtMaximumRange; // 0x68(0x04)
	char UnknownData_6C[0x4]; // 0x6c(0x04)
	struct UClass* DamagerType; // 0x70(0x08)
	struct UClass* ProjectileId; // 0x78(0x08)
	struct FWeaponProjectileParams AmmoParams; // 0x80(0xa8)
	bool UsesScope; // 0x130(0x01)
	char UnknownData_119[0x3]; // 0x131(0x03)
	float ZoomedRecoilDurationIncrease; // 0x134(0x04)
	float SecondsUntilZoomStarts; // 0x138(0x04)
	float SecondsUntilPostStarts; // 0x13c(0x04)
	float WeaponFiredAINoiseRange; // 0x140(0x04)
	float MaximumRequestPositionDelta; // 0x144(0x04)
	float MaximumRequestAngleDelta; // 0x148(0x04)
	float TimeoutTolerance; // 0x14C(0x04)
	float AimingMoveSpeedScalar; // 0x150(0x04)
	char AimSensitivitySettingCategory; // 0x154(0x01)
	char UnknownData_13D[0x3]; // 0x155(0x03)
	float InAimFOV; // 0x158(0x04)
	float BlendSpeed; // 0x15c(0x04)
	struct UWwiseEvent* DryFireSfx; // 0x160(0x08)
	struct FName RumbleTag; // 0x178(0x08)
	bool KnockbackEnabled; // 0x180(0x01)
	char UnknownData_179[0x3]; // 0x181(0x03)
	bool StunEnabled; // 0x1D4(0x01)
	char UnknownData_1BD[0x3]; // 0x1d5(0x03)
	float StunDuration; // 0x1d8(0x04)
	struct FVector TargetingOffset; // 0x1dc(0x0c)
};
/*119 13D 179 1BD -> 131 155 181 1D5 ???
  11.06				*/
struct URepairableComponent {
	unsigned char                                      UnknownData_WIVW[0x18];                                    // 0x0118(0x0018) MISSED OFFSET (FIX SPACE BETWEEN PREVIOUS PROPERTY)
	float                                              InteractionPointDepthOffset;                               // 0x0170(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                              MaximumRepairAngleToRepairer;                              // 0x0174(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                              MaximumRepairDistance;                                     // 0x0178(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                              RepairTime;                                                // 0x017C(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class UClass* RepairType;                                                // 0x0180(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, UObjectWrapper, HasGetValueTypeHash)
	class USceneComponent* RepairMountParent;                                         // 0x0188(0x0008) (Edit, BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FTransform                                  RepairMountOffset;                                         // 0x0190(0x0030) (Edit, BlueprintVisible, IsPlainOldData, NoDestructor)
	struct FName                                       RepairMountSocket;                                         // 0x01C0(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	int                                                MaxDamageLevel;                                            // 0x01DC(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	unsigned char                                      UnknownData_CZX3[0x4];                                     // 0x01BC(0x0004) MISSED OFFSET (FIX SPACE BETWEEN PREVIOUS PROPERTY)
	class UClass* AIInteractionType;                                         // 0x01D0(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, UObjectWrapper, HasGetValueTypeHash)
	struct FVector                                     AIInteractionOffset;                                       // 0x01D0(0x000C) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor)
	unsigned char                                      UnknownData_SYYG[0x4];                                     // 0x01D4(0x0004) MISSED OFFSET (FIX SPACE BETWEEN PREVIOUS PROPERTY)
	unsigned char                                      UnknownData_EU9A[0x3];                                     // 0x01F1(0x0003) MISSED OFFSET (FIX SPACE BETWEEN PREVIOUS PROPERTY)
	int                                                DamageLevel;                                               // 0x020C(0x0004) (Net, ZeroConstructor, IsPlainOldData, RepNotify, NoDestructor, HasGetValueTypeHash)
	unsigned char                                      UnknownData_Z10X[0x87];                                    // 0x01F9(0x0087) MISSED OFFSET (PADDING)
};
//11.06
struct ABucket {
	char pad1[0x0788];
	class UInventoryItemComponent* InventoryItem;                                             // 0x0788(0x0008) (Edit, BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	TArray<struct FBucketContentsInfo>                 BucketContentsInfos;                                       // 0x0790(0x0010) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance)
	class UWwiseEvent* ScoopSfx;                                                  // 0x07A0(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FName                                       ThrowSocketName;                                           // 0x07A8(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FName                                       DrenchWielderSocketName;                                   // 0x07B0(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                              ScoopActionTime;                                           // 0x07B8(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                              ScoopCompleteTime;                                         // 0x07BC(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                              ThrowActionTime;                                           // 0x07C0(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                              ThrowCompleteTime;                                         // 0x07C4(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                              DrenchWielderActionTime;                                   // 0x07C8(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                              DrenchWielderCompleteTime;                                 // 0x07CC(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                              RequestToleranceTimeOnServer;                              // 0x07D0(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                              ProjectileSpeed;                                           // 0x07D4(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                              ProjectileAdditionalLiftAngle;                             // 0x07D8(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                              WaterFillFromShip;                                         // 0x07DC(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                              WaterFillFromSea;                                          // 0x07E0(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                              WaterTransferFillAmountModifier;                           // 0x07E4(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                              ScoopBufferDistance;                                       // 0x07E8(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	unsigned char                                      UnknownData_Z3K3[0x3];                                     // 0x07FD(0x0003) MISSED OFFSET (FIX SPACE BETWEEN PREVIOUS PROPERTY)
	class UClass* BucketScoopCooldownType;                                   // 0x07F0(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, UObjectWrapper, HasGetValueTypeHash)
	class UClass* BucketThrowCooldownType;                                   // 0x07F8(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, UObjectWrapper, HasGetValueTypeHash)
	class UClass* BucketDouseCooldownType;                                   // 0x0800(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, UObjectWrapper, HasGetValueTypeHash)
	float                                              ThrowLiquidAINoiseRange;                                   // 0x0808(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	unsigned char                                      UnknownData_1WAE[0x4];                                     // 0x081C(0x0004) MISSED OFFSET (FIX SPACE BETWEEN PREVIOUS PROPERTY)
	class UNamedNotificationInputComponent* NamedNotificationInputComponent;                           // 0x0820(0x0008) (Edit, ExportObject, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash)
	class ULiquidContainerComponent* LiquidContainer;                                           // 0x0810(0x0008) (Edit, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash)
	unsigned char                                      UnknownData_7SEW[0x1];                                     // 0x0870(0x0001) MISSED OFFSET (FIX SPACE BETWEEN PREVIOUS PROPERTY)
	unsigned char                                      UnknownData_NP3V[0x76];                                    // 0x0872(0x0076) MISSED OFFSET (FIX SPACE BETWEEN PREVIOUS PROPERTY)
	class UParticleSystemComponent* BucketContentsEffect;                                      // 0x08D0(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	unsigned char                                      UnknownData_ZK3R[0x8];                                    // 0x08F0(0x0010) MISSED OFFSET (PADDING)
};
//11.22
struct AProjectileWeapon {
	char pad[0x7C8];
	FProjectileWeaponParameters WeaponParameters; //0x7c8(0x1e8) 7d0xD

	bool CanFire()
	{
		static auto fn = UObject::FindObject<UFunction>("Function Athena.ProjectileWeapon.CanFire");
		bool canfire;
		ProcessEvent(this, fn, &canfire);
		return canfire;
	}


};


//11.22
struct ASlidingDoor {
	char pad_0x0[0x534]; 
	FVector InitialDoorMeshLocation; // 0x534(0xc)

	void OpenDoor() {
		static auto fn = UObject::FindObject<UFunction>("Function Athena.SkeletonFortDoor.OpenDoor");
		ProcessEvent(this, fn, nullptr);
	}
};

enum class ECookingSmokeFeedbackLevel : uint8_t {
	NotCooking = 0,
	Raw = 1,
	CookedWarning = 2,
	Cooked = 3,
	BurnedWarning = 4,
	Burned= 5,
	ECookingSmokeFeedbackLevel_MAX = 6,
};

enum class EDrawDebugTrace : uint8_t
{
	EDrawDebugTrace__None = 0,
	EDrawDebugTrace__ForOneFrame = 1,
	EDrawDebugTrace__ForDuration = 2,
	EDrawDebugTrace__Persistent = 3,
	EDrawDebugTrace__EDrawDebugTrace_MAX = 4
};

enum class ETraceTypeQuery : uint8_t
{
	TraceTypeQuery1 = 0,
	TraceTypeQuery2 = 1,
	TraceTypeQuery3 = 2,
	TraceTypeQuery4 = 3,
	TraceTypeQuery5 = 4,
	TraceTypeQuery6 = 5,
	TraceTypeQuery7 = 6,
	TraceTypeQuery8 = 7,
	TraceTypeQuery9 = 8,
	TraceTypeQuery10 = 9,
	TraceTypeQuery11 = 10,
	TraceTypeQuery12 = 11,
	TraceTypeQuery13 = 12,
	TraceTypeQuery14 = 13,
	TraceTypeQuery15 = 14,
	TraceTypeQuery16 = 15,
	TraceTypeQuery17 = 16,
	TraceTypeQuery18 = 17,
	TraceTypeQuery19 = 18,
	TraceTypeQuery20 = 19,
	TraceTypeQuery21 = 20,
	TraceTypeQuery22 = 21,
	TraceTypeQuery23 = 22,
	TraceTypeQuery24 = 23,
	TraceTypeQuery25 = 24,
	TraceTypeQuery26 = 25,
	TraceTypeQuery27 = 26,
	TraceTypeQuery28 = 27,
	TraceTypeQuery29 = 28,
	TraceTypeQuery30 = 29,
	TraceTypeQuery31 = 30,
	TraceTypeQuery32 = 31,
	TraceTypeQuery_MAX = 32,
	ETraceTypeQuery_MAX = 33
};

struct USceneComponent {
	FVector K2_GetComponentLocation() {
		FVector location;
		static auto fn = UObject::FindObject<UFunction>("Function Engine.SceneComponent.K2_GetComponentLocation");
		ProcessEvent(this, fn, &location);
		return location;
	}
};
//11.22
struct APuzzleVault {
	char pad[0x1030]; 
	ASlidingDoor* OuterDoor; // 0x1030(0x8)



};

struct FGuid
{
	int                                                A;                                                         // 0x0000(0x0004) (Edit, ZeroConstructor, SaveGame, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	int                                                B;                                                         // 0x0004(0x0004) (Edit, ZeroConstructor, SaveGame, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	int                                                C;                                                         // 0x0008(0x0004) (Edit, ZeroConstructor, SaveGame, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	int                                                D;                                                         // 0x000C(0x0004) (Edit, ZeroConstructor, SaveGame, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
};

struct FSessionTemplate
{
	struct FString                                     TemplateName;                                              // 0x0000(0x0010) (ZeroConstructor, Protected, HasGetValueTypeHash)
	unsigned char             SessionType;                                               // 0x0010(0x0001) (ZeroConstructor, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash)
	unsigned char                                      UnknownData_2Q1C[0x3];                                     // 0x0011(0x0003) MISSED OFFSET (FIX SPACE BETWEEN PREVIOUS PROPERTY)
	int                                                MaxPlayers;                                                // 0x0014(0x0004) (ZeroConstructor, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash)

};

// ScriptStruct Sessions.CrewSessionTemplate
// 0x0020 (0x0038 - 0x0018)
struct FCrewSessionTemplate : public FSessionTemplate
{
	struct FString                                     MatchmakingHopper;                                         // 0x0018(0x0010) (ZeroConstructor, HasGetValueTypeHash)
	class UClass* ShipSize;                                                  // 0x0028(0x0008) (ZeroConstructor, IsPlainOldData, NoDestructor, UObjectWrapper, HasGetValueTypeHash)
	int                                                MaxMatchmakingPlayers;                                     // 0x0030(0x0004) (ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	unsigned char                                      UnknownData_JPXK[0x4];                                     // 0x0034(0x0004) MISSED OFFSET (PADDING)

};
//11.22
struct FCrew
{
	struct FGuid                                       CrewId;                                                   // 0x0000(0x0010) (ZeroConstructor, IsPlainOldData)
	struct FGuid                                       SessionId;                                                // 0x0010(0x0010) (ZeroConstructor, IsPlainOldData)
	TArray<class APlayerState*>                        Players;                                                  // 0x0020(0x0010) (ZeroConstructor)
	struct FCrewSessionTemplate                        CrewSessionTemplate;                                      // 0x0030(0x0038)
	struct FGuid                                       LiveryID;                                                 // 0x0068(0x0010) (ZeroConstructor, IsPlainOldData)
	unsigned char											   UnknownData_78[0x8];                                      // 0x0078(0x0008) MISSED OFFSET
	struct TArray<struct AActor*>                      AssociatedActors;                                         // 0x0080(0x0010) (ZeroConstructor)
	bool HasEverSetSail; // 0x90(0x01)
	char UnknownData_91[0x3]; // 0x91(0x03)
	int32_t ScrambleNameIndex; // 0x94(0x04)
	

};
//11.22
struct ACrewService {
	char pad[0x4A0]; 
	TArray<FCrew> Crews; // 0x04A0
	
};
//11.22
struct AShip
{
	char pad1[0x1082]; 
	bool                                               EmissaryFlagActive;                                        // 0x1082(0x0001) (Net, ZeroConstructor, IsPlainOldData, NoDestructor)

	FVector GetCurrentVelocity() {
		static auto fn = UObject::FindObject<UFunction>("Function Athena.Ship.GetCurrentVelocity");
		FVector params;
		ProcessEvent(this, fn, &params);
		return params;
	}
};

struct AShipService
{
	int GetNumShips()
	{
		static auto fn = UObject::FindObject<UFunction>("Function Athena.ShipService.GetNumShips");
		int num;
		ProcessEvent(this, fn, &num);
		return num;
	}
};
// 11.22 felcsúszott minden 1-el
struct AAthenaGameState {
	char pad[0x5b8];
	struct AWindService* WindService; // 0x5b0(0x8)
	struct APlayerManagerService* PlayerManagerService; // 0x5b8(0x8)
	struct AShipService* ShipService; // 0x5c0(0x8)
	struct AWatercraftService* WatercraftService; // 0x5c8(0x8)
	struct ATimeService* TimeService; // 0x5d0(0x8)
	struct UHealthCustomizationService* HealthService; // 0x5d8(0x8)
	struct UCustomWeatherService* CustomWeatherService; // 0x5e0(0x8)
	struct UCustomStatusesService* CustomStatusesService; // 0x5e8(0x8)
	struct AFFTWaterService* WaterService; // 0x5f0(0x8)
	struct AStormService* StormService; // 0x5f8(0x8)
	struct ACrewService* CrewService; // 0x600(0x8)							
	struct ACaptainedSessionService* CaptainedSessionService; // 0x608(0x08)
	struct AContestZoneService* ContestZoneService; // 0x610(0x8)
	struct AContestRowboatsService* ContestRowboatsService; // 0x618(0x08)
	struct AIslandService* IslandService; // 0x620(0x08)
	struct ANPCService* NPCService; // 0x628(0x08)
	struct ASkellyFortService* SkellyFortService; // 0x630(0x08)					
	struct ADeepSeaRegionService* DeepSeaRegionService; // 0x638(0x08)
	struct AAIDioramaService* AIDioramaService; // 0x640(0x08)
	struct AAshenLordEncounterService* AshenLordEncounterService; // 0x648(0x8)			
	struct AAggressiveGhostShipsEncounterService* AggressiveGhostShipsEncounterService; // 0x650(0x08)
	struct ATallTaleService* TallTaleService; // 0x658(0x08)
	struct AAIShipObstacleService* AIShipObstacleService; // 0x660(0x08)
	struct AAIShipService* AIShipService; // 0x668(0x08)							
	struct AAITargetService* AITargetService; // 0x670(0x08)
	struct UShipLiveryCatalogueService* ShipLiveryCatalogueService; // 0x678(0x08)
	struct AContestManagerService* ContestManagerService; // 0x680(0x08)
	struct ADrawDebugService* DrawDebugService; // 0x688(0x08)
	struct AWorldEventZoneService* WorldEventZoneService; // 0x690(0x08)
	struct UWorldResourceRegistry* WorldResourceRegistry; // 0x698(0x08)
	struct AKrakenService* KrakenService; // 0x6a0(0x08)
	struct UPlayerNameService* PlayerNameService; // 0x6a8(0x08)
	struct ATinySharkService* TinySharkService; // 0x6b0(0x08)
	struct AProjectileService* ProjectileService; // 0x6b8(0x08)
	struct ULaunchableProjectileService* LaunchableProjectileService; // 0x6c0(0x08)
	struct UServerNotificationsService* ServerNotificationsService; // 0x6c8(0x8)
	struct AAIManagerService* AIManagerService; // 0x6d0(0x8)
	struct AAIEncounterService* AIEncounterService; // 0x6d8(0x8)
	struct AAIEncounterGenerationService* AIEncounterGenerationService; // 0x6e0(0x8)
	struct UEncounterService* EncounterService; // 0x6e8(0x8)
	struct UGameEventSchedulerService* GameEventSchedulerService; // 0x6f0(0x8)
	struct UHideoutService* HideoutService; // 0x6f8(0x8)
	struct UAthenaStreamedLevelService* StreamedLevelService; // 0x700(0x8)
	struct ULocationProviderService* LocationProviderService; // 0x708(0x8)
	struct AHoleService* HoleService; // 0x710(0x8)
	struct APlayerBuriedItemService* PlayerBuriedItemService; // 0x718(0x8)
	struct ULoadoutService* LoadoutService; // 0x720(0x8)
	struct UOcclusionService* OcclusionService; // 0x728(0x8)
	struct UPetsService* PetsService; // 0x730(0x8)
	struct UAthenaAITeamsService* AthenaAITeamsService; // 0x738(0x8)
	struct AAllianceService* AllianceService; // 0x740(0x8)
	struct UMaterialAccessibilityService* MaterialAccessibilityService; // 0x748(0x8)
	//struct UNPCLoadedOnClientService* NPCLoadedOnClientService; // 0x750(0x08)			futyi
	struct AReapersMarkService* ReapersMarkService; // 0x758(0x8)
	struct AEmissaryLevelService* EmissaryLevelService; // 0x760(0x8)
	struct AFactionService* FactionService; // 0x768(0x08)				futyi
	struct ACampaignService* CampaignService; // 0x770(0x8)
	struct AStoryService* StoryService; // 0x778(0x8)
	struct AStorySpawnedActorsService* StorySpawnedActorsService; // 0x780(0x8)
	//struct AStoryClaimedResourcesService* StoryClaimedResourcesService; // 0x788(0x08)			futyi
	struct UGlobalVoyageDirectorService* GlobalVoyageDirector; // 0x790(0x8)
	struct AFlamesOfFateSettingsService* FlamesOfFateSettingsService; // 0x798(0x8)
	struct AServiceStatusNotificationsService* ServiceStatusNotificationsService; // 0x7a0(0x08)
	struct UMigrationService* MigrationService; // 0x7a8(0x8)
	//struct UShipStockService* ShipStockService; // 0x7b0(0x08)                        futyi
	struct AShroudBreakerService* ShroudBreakerService; // 0x7b8(0x8)
	struct UServerUpdateReportingService* ServerUpdateReportingService; // 0x7c0(0x8)
	struct AGenericMarkerService* GenericMarkerService; // 0x7c8(0x8)
	struct AMechanismsService* MechanismsService; // 0x7d0(0x8)
	struct UMerchantContractsService* MerchantContractsService; // 0x7d8(0x8)
	struct UShipFactory* ShipFactory; // 0x7e0(0x8)
	struct URewindPhysicsService* RewindPhysicsService; // 0x7e8(0x8)
	struct UNotificationMessagesDataAsset* NotificationMessagesDataAsset; // 0x7f0(0x8)
	struct AProjectileCooldownService* ProjectileCooldownService; // 0x7f8(0x8)
	struct UIslandReservationService* IslandReservationService; // 0x800(0x8)
	struct APortalService* PortalService; // 0x808(0x8)
	struct UMeshMemoryConstraintService* MeshMemoryConstraintService; // 0x810(0x8)
	struct ABootyStorageService* BootyStorageService; // 0x818(0x8)
	struct ASpireService* SpireService; // 0x828(0x8)
	struct AFireworkService* FireworkService; // 0x830(0x8)
	//struct AInvasionService* InvasionService; // 0x838(0x08)				futyi
	struct UAirGivingService* AirGivingService; // 0x840(0x8)
	struct UCutsceneService* CutsceneService; // 0x848(0x8)
	struct ACargoRunService* CargoRunService; // 0x850(0x8)
	struct ACommodityDemandService* CommodityDemandService; // 0x858(0x8)
	//struct ADebugTeleportationDestinationService* DebugTeleportationDestinationService; // 0x860(0x8)   futyi
	struct ASeasonProgressionUIService* SeasonProgressionUIService; // 0x868(0x8)
	struct UTransientActorService* TransientActorService; // 0x870(0x8)
	struct UTunnelsOfTheDamnedService* TunnelsOfTheDamnedService; // 0x878(0x8)
	struct UWorldSequenceService* WorldSequenceService; // 0x880(0x8)
	struct UItemLifetimeManagerService* ItemLifetimeManagerService; // 0x888(0x8)
	//struct AShipStorageJettisonService* ShipStorageJettisonService; // 0x890(0x08)				futyi
	struct ASeaFortsService* SeaFortsService; // 0x898(0x8)
	//struct ACustomServerLocalisationService* CustomServerLocalisationService; // 0x8a0(0x08)			futyi
	struct ABeckonService* BeckonService; // 0x8a8(0x8)
	struct UVolcanoService* VolcanoService; // 0x8b0(0x8)
	struct UShipAnnouncementService* ShipAnnouncementService; // 0x8b8(0x8)
	struct AShipsLogService* ShipsLogService; // 0x8c0(0x8)
};

struct UCharacterMovementComponent {
	FVector GetCurrentAcceleration() {
		static auto fn = UObject::FindObject<UFunction>("Function Engine.CharacterMovementComponent.GetCurrentAcceleration");
		FVector acceleration;
		ProcessEvent(this, fn, &acceleration);
		return acceleration;
	}
};

struct FFloatRange {
	float pad1;
	float min;
	float pad2;
	float max;
};
//11.22
struct ULoadableComponent
{
	char pad1[0x00D0];
	float                                              LoadTime;                                                  // 0x00D0(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                              UnloadTime;                                                // 0x00D4(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class UClass* DefaultObjectToLoad;                                       // 0x00E8(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, UObjectWrapper, HasGetValueTypeHash)
	unsigned char                                      UnknownData_GZLH[0x50];                                    // 0x00F0(0x0050) MISSED OFFSET (FIX SPACE BETWEEN PREVIOUS PROPERTY)
	struct FTransform                                  UnloadingPoint;                                            // 0x0140(0x0030) (Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData, NoDestructor, Protected)
	unsigned char                                      UnknownData_8A3T[0x18];                                    // 0x0170(0x0018) MISSED OFFSET (FIX SPACE BETWEEN PREVIOUS PROPERTY)
	bool                                               AlwaysLoaded;                                              // 0x0198(0x0001) (Net, ZeroConstructor, IsPlainOldData, NoDestructor)
	unsigned char                                      UnknownData_FGJ0[0x57];                                    // 0x0199(0x0057) MISSED OFFSET (PADDING)
};
//11.22 large-medium-small
struct UBootyStorageSettings
{
	char pad1[0x0038];
	float                                              StoreHoldTime;                                             // 0x0038(0x0004) (Edit, ZeroConstructor, Config, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                              RetrieveHoldTime;                                          // 0x003C(0x0004) (Edit, ZeroConstructor, Config, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                              PickupPointSpawnDepth;                                     // 0x0040(0x0004) (Edit, ZeroConstructor, Config, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                              PickupDismissDuration;                                     // 0x0044(0x0004) (Edit, ZeroConstructor, Config, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         LargePickupDismissDistanceCheck;                                // 0x0048(0x0004) (Edit, ZeroConstructor, Config, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float				MediumShipPickupDismissDistanceCheck;
	float				SmallShipPickupDismissDistanceCheck;
	unsigned char                                      MaxStoragePerLocation;                                     // 0x004C(0x0001) (Edit, ZeroConstructor, Config, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	unsigned char                                      UnknownData_V0LN[0x3];                                     // 0x004D(0x0003) MISSED OFFSET (FIX SPACE BETWEEN PREVIOUS PROPERTY)
	TArray<class UClass*>                              BlacklistedCategories;                                     // 0x0060(0x0010) (Edit, ZeroConstructor, Config, UObjectWrapper)
};
//11.22
struct ABootyStorageService
{
	char pad1[0x0450];
	class UBootyStorageSettings* BootyStorageSettings;                                      // 0x0450(0x0008) (ZeroConstructor, Transient, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class UBootyStorageSettingsAsset* BootyStorageSettingsAsset;                                 // 0x0458(0x0008) (ZeroConstructor, Transient, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	TArray<struct FCrewBootyStorage>                   Storage;                                                   // 0x0460(0x0010) (Net, ZeroConstructor, RepNotify)
	unsigned char                                      UnknownData_7TKK[0x8];                                     // 0x0758(0x0008) MISSED OFFSET (PADDING)
};
// 11.22 asszem jo
struct ACannon {
	char UnknownData_510[0x538]; // 0x510(0x28)
	struct USkeletalMeshMemoryConstraintComponent* BaseMeshComponent; // 0x538(0x08)
	struct UStaticMeshMemoryConstraintComponent* BarrelMeshComponent; // 0x540(0x08)
	struct UStaticMeshComponent* FuseMeshComponent; // 0x548(0x08)
	struct UReplicatedShipPartCustomizationComponent* CustomizationComponent; // 0x550(0x08)
	struct ULoadableComponent* LoadableComponent; // 0x558(0x08)
	struct ULoadingPointComponent* LoadingPointComponent; // 0x560(0x08)
	struct UChildActorComponent* CannonBarrelInteractionComponent; // 0x568(0x08)
	struct UFuseComponent* FuseComponent; // 0x570(0x08)
	struct FName CameraSocket; // 0x578(0x08)
	struct FName CameraInsideCannonSocket; // 0x580(0x08)
	struct FName LaunchSocket; // 0x588(0x08)
	struct FName TooltipSocket; // 0x590(0x08)
	struct FName AudioAimRTPCName; // 0x598(0x08)
	struct FName InsideCannonRTPCName; // 0x5a0(0x08)
	struct UClass* ProjectileClass; // 0x5a8(0x08)
	float TimePerFire; // 0x5b0(0x04)
	float ProjectileSpeed; // 0x5b4(0x04)
	float ProjectileGravityScale; // 0x5b8(0x04)
	struct FFloatRange PitchRange; // 0x5bc(0x10)
	struct FFloatRange YawRange; // 0x5cc(0x10)
	float PitchSpeed; // 0x5dc(0x04)
	float YawSpeed; // 0x5e0(0x04)
	char UnknownData_5E4[0x4]; // 0x5e4(0x04)
	struct UClass* CameraShake; // 0x5e8(0x08)
	float ShakeInnerRadius; // 0x5f0(0x04)
	float ShakeOuterRadius; // 0x5f4(0x04)
	float CannonFiredAINoiseRange; // 0x5f8(0x04)
	struct FName AINoiseTag; // 0x5fc(0x08)
	char UnknownData_604[0x4]; // 0x604(0x04)
	//struct FText CannonDisabledToolTipText; 
	char pad[0x38];// 0x608(0x38)
	//struct FText LoadingDisabledToolTipText; 
	char pad2[0x38];// 0x640(0x38)
	struct UClass* UseCannonInputId; // 0x678(0x08)
	struct UClass* StartLoadingCannonInputId; // 0x680(0x08)
	struct UClass* StopLoadingCannonInputId; // 0x688(0x08)
	float DefaultFOV; // 0x690(0x04)
	float AimFOV; // 0x694(0x04)
	float IntoAimBlendSpeed; // 0x698(0x04)
	float OutOfAimBlendSpeed; // 0x69c(0x04)
	struct UWwiseEvent* FireSfx; // 0x6a0(0x08)
	struct UWwiseEvent* DryFireSfx; // 0x6a8(0x08)
	struct UWwiseEvent* LoadingSfx_Play; // 0x6b0(0x08)
	struct UWwiseEvent* LoadingSfx_Stop; // 0x6b8(0x08)
	struct UWwiseEvent* UnloadingSfx_Play; // 0x6c0(0x08)
	struct UWwiseEvent* UnloadingSfx_Stop; // 0x6c8(0x08)
	struct UWwiseEvent* LoadedPlayerSfx; // 0x6d0(0x08)
	struct UWwiseEvent* UnloadedPlayerSfx; // 0x6d8(0x08)
	struct UWwiseEvent* FiredPlayerSfx; // 0x6e0(0x08)
	struct UWwiseObjectPoolWrapper* SfxPool; // 0x6e8(0x08)
	struct UWwiseEvent* StartPitchMovement; // 0x6f0(0x08)
	struct UWwiseEvent* StopPitchMovement; // 0x6f8(0x08)
	struct UWwiseEvent* StartYawMovement; // 0x700(0x08)
	struct UWwiseEvent* StopYawMovement; // 0x708(0x08)
	struct UWwiseEvent* StopMovementAtEnd; // 0x710(0x08)
	struct UWwiseObjectPoolWrapper* SfxMovementPool; // 0x718(0x08)
	struct UObject* FuseVfxFirstPerson; // 0x720(0x08)
	struct UObject* FuseVfxThirdPerson; // 0x728(0x08)
	struct UObject* MuzzleFlashVfxFirstPerson; // 0x730(0x08)
	struct UObject* MuzzleFlashVfxThirdPerson; // 0x738(0x08)
	struct FName FuseSocketName; // 0x740(0x08)
	struct FName BarrelSocketName; // 0x748(0x08)
	struct UClass* RadialCategoryFilter; // 0x750(0x08)
	struct UClass* DefaultLoadedItemDesc; // 0x758(0x08)
	float ClientRotationBlendTime; // 0x760(0x04)
	char UnknownData_764[0x4]; // 0x764(0x04)
	struct AItemInfo* LoadedItemInfo; // 0x768(0x08)
	char UnknownData_770[0x20]; // 0x770(0x20)
	struct UMemoryConstrainedMeshInitializer* BaseMMCMeshInitializer; // 0x790(0x08)
	struct UMemoryConstrainedMeshInitializer* BarrelMMCMeshInitializer; // 0x798(0x08)
	struct UCannonDescAsset* DescToSetWhenSafe; // 0x7a0(0x08)
	struct UCannonDescAsset* CurrentCannonDesc; // 0x7a8(0x08)
	float ServerPitch; // 0x7b0(0x04)
	float ServerYaw; // 0x7b4(0x04)
	struct UParticleSystemComponent* LoadedItemVFXComp; // 0x7b8(0x08)
	struct UStaticMesh* DefaultFuseMesh; // 0x7c0(0x08)
	char UnknownData_7C8[0x4f0]; // 0x7c8(0x4f0)
	char InteractionState; // 0xcb8(0x01)
	char UnknownData_CB9[0x7]; // 0xcb9(0x07)


	bool IsReadyToFire() {
		static auto fn = UObject::FindObject<UFunction>("Function Athena.Cannon.IsReadyToFire");
		bool is_ready = true;
		ProcessEvent(this, fn, &is_ready);
		return is_ready;
	}

	void Fire() {
		static auto fn = UObject::FindObject<UFunction>("Function Athena.Cannon.Fire");
		ProcessEvent(this, fn, nullptr);
	}

	bool IsReadyToReload() {
		static auto fn = UObject::FindObject<UFunction>("Function Athena.Cannon.IsReadyToReload");
		bool is_ready = true;
		ProcessEvent(this, fn, &is_ready);
		return is_ready;
	}

	void Reload() {
		static auto fn = UObject::FindObject<UFunction>("Function Athena.Cannon.Reload");
		ProcessEvent(this, fn, nullptr);
	}

	void ForceAimCannon(float Pitch, float Yaw)
	{
		static auto fn = UObject::FindObject<UFunction>("Function Athena.Cannon.ForceAimCannon");
		struct {
			float Pitch;
			float Yaw;
		} params;
		params.Pitch = Pitch;
		params.Yaw = Yaw;
		ProcessEvent(this, fn, &params);
	}

	void Server_Fire(float Pitch, float Yaw)
	{
		static auto fn = UObject::FindObject<UFunction>("Function Athena.Cannon.Server_Fire");
		struct {
			float Pitch;
			float Yaw;
		} params;
		params.Pitch = Pitch;
		params.Yaw = Yaw;
		ProcessEvent(this, fn, &params);
	}

};

/*struct UStaticMeshMemoryConstraintComponent
{
	char UnknownData_620[0x640]; // 0x620(0x20)
	struct UMeshMemoryConstraintHandler* Handler; // 0x640(0x08)
	struct TArray<struct FStringAssetReference> FallbackOverrideMaterials; // 0x648(0x10)
	struct UClass* MeshFallbackCategory; // 0x658(0x08)
	//struct FStringAssetReference MeshReference; 
	char pad[0x10];// 0x660(0x10)
	int64_t CachedMeshResourceSize; // 0x670(0x08)
	bool MemoryAccountedFor; // 0x678(0x01)
	bool NeedMeshLoadOnServer; // 0x679(0x01)
	char UnknownData_67A[0x6]; // 0x67a(0x06)
	struct UClass* BudgetToCountMemoryAgainstIfNoFallback; // 0x680(0x08)
	//struct FFeatureFlag OptionalFeatureToggleForMMC; 
	char pad2[0x0c];// 0x688(0x0c)
	char UnknownData_694[0xc]; // 0x694(0x0c)

	bool GetIsMeshFinishedChange()
	{
		static auto fn = UObject::FindObject<UFunction>("Function Athena.StaticMeshMemoryConstraintComponent.GetIsMeshFinishedChange");
		bool is_finished = true;
		ProcessEvent(this, fn, &is_finished);
		return is_finished;
	}// Function Athena.StaticMeshMemoryConstraintComponent.GetIsMeshFinishedChange // Final|Native|Public|BlueprintCallable|BlueprintPure|Const // @ game+0x3321080
};*/

/*struct USkeletalMeshSocket {
	char pad[0x28];
	struct FName SocketName; // 0x28(0x08)
	struct FName BoneName; // 0x30(0x08)
	struct FVector RelativeLocation; // 0x38(0x0c)
	struct FRotator RelativeRotation; // 0x44(0x0c)
	struct FVector RelativeScale; // 0x50(0x0c)
	bool bForceAlwaysAnimated; // 0x5c(0x01)
	char UnknownData_5D[0x3]; // 0x5d(0x03)

	void InitializeSocketFromLocation(struct USkeletalMeshComponent* SkelComp, struct FVector WorldLocation, struct FVector WorldNormal)
	{

	}// Function Engine.SkeletalMeshSocket.InitializeSocketFromLocation // Final|RequiredAPI|Native|Public|HasDefaults|BlueprintCallable // @ game+0x30a9f20
	struct FVector GetSocketLocation(struct USkeletalMeshComponent* SkelComp)
	{
		static auto fn = UObject::FindObject<UFunction>("Function Engine.SkeletalMeshSocket.GetSocketLocation");
		FVector socket_location;
		ProcessEvent(this, fn, &socket_location);
		return socket_location;
	}// Function Engine.SkeletalMeshSocket.GetSocketLocation // Final|RequiredAPI|Native|Public|HasDefaults|BlueprintCallable|BlueprintPure|Const // @ game+0x30a9e30
};*/

// 11.06 11.22 idk
struct UItemDesc {
	char pad[0x0028];
	FString* Title; // 0x0028(0x38)
};

struct UItemDescEx : UObject {
	struct FText Title; // 0x28(0x38)
	struct FText Description; // 0x60(0x38)
	//char pad_60[0x68];
	char pad_98[0x30];
	char pad_c0[0x58];
};

//11.22
struct AItemInfo {
	char pad[0x0440];
	UItemDesc* Desc; // 0x0440(0x8)
};
// 11.22
struct UInteractableComponent
{
	char pad1[0x0100];
	float                                              InteractionRadius;                                         // 0x0100(0x0004) (Edit, ZeroConstructor, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash)
};
// gewgo tudja TwT 
struct AHarpoonLauncher {
	char pad1[0xB11];
	FRotator rotation; // 0xB04
	// ROTATION OFFSET FOUND USING RECLASS.NET: https://www.unknowncheats.me/forum/sea-of-thieves/470590-reclass-net-plugin.html

	void Server_RequestAim(float InPitch, float InYaw)
	{
		static auto fn = UObject::FindObject<UFunction>("Function Athena.HarpoonLauncher.Server_RequestAim");
		struct {
			float InPitch;
			float InYaw;
		} params;
		params.InPitch = InPitch;
		params.InYaw = InYaw;
		ProcessEvent(this, fn, &params);
	}
};

struct UInventoryManipulatorComponent {
	bool ConsumeItem(ACharacter* item) {
		static auto fn = UObject::FindObject<UFunction>("Function Athena.InventoryManipulatorComponent.ConsumeItem");

		struct
		{
			ACharacter* item;
			bool ReturnValue;
		} params;

		params.item = item;
		params.ReturnValue = false;

		ProcessEvent(this, fn, &params);

		return params.ReturnValue;
	}
};
//11.22 idk
class UActorComponent
{
	unsigned char                                      UnknownData_GRZN[0x8];                                     // 0x0028(0x0008) MISSED OFFSET (FIX SPACE BETWEEN PREVIOUS PROPERTY)
	TArray<struct FName>                               ComponentTags;                                             // 0x0080(0x0010) (Edit, BlueprintVisible, ZeroConstructor)
	TArray<struct FSimpleMemberReference>              UCSModifiedProperties;                                     // 0x0090(0x0010) (ZeroConstructor)
	unsigned char                                      UnknownData_1HIB[0x10];                                    // 0x00A0(0x0010) MISSED OFFSET (FIX SPACE BETWEEN PREVIOUS PROPERTY)
	TArray<class UAssetUserData*>                      AssetUserData;                                             // 0x00B0(0x0010) (ExportObject, ZeroConstructor, ContainsInstancedReference, Protected)
	unsigned char                                      UnknownData_2I5J : 3;                                      // 0x00C0(0x0001) BIT_FIELD (PADDING)
	unsigned char                                      bReplicates : 1;                                           // 0x00C0(0x0001) BIT_FIELD (Edit, BlueprintVisible, BlueprintReadOnly, Net, DisableEditOnInstance, NoDestructor)
	unsigned char                                      bNetAddressable : 1;                                       // 0x00C0(0x0001) BIT_FIELD (NoDestructor, Protected)
	unsigned char                                      UnknownData_G3LM : 3;                                      // 0x00C0(0x0001) BIT_FIELD (PADDING)
	unsigned char                                      UnknownData_UWFN : 6;                                      // 0x00C1(0x0001) BIT_FIELD (PADDING)
	unsigned char                                      bCreatedByConstructionScript : 1;                          // 0x00C1(0x0001) BIT_FIELD (Deprecated, NoDestructor)
	unsigned char                                      bInstanceComponent : 1;                                    // 0x00C1(0x0001) BIT_FIELD (Deprecated, NoDestructor)
	unsigned char                                      bAutoActivate : 1;                                         // 0x00C2(0x0001) BIT_FIELD (Edit, BlueprintVisible, BlueprintReadOnly, NoDestructor)
	unsigned char                                      bIsActive : 1;                                             // 0x00C2(0x0001) BIT_FIELD (Net, Transient, RepNotify, NoDestructor)
	unsigned char                                      bEditableWhenInherited : 1;                                // 0x00C2(0x0001) BIT_FIELD (Edit, DisableEditOnInstance, NoDestructor)
	unsigned char                                      UnknownData_4IP7 : 5;                                      // 0x00C2(0x0001) BIT_FIELD (PADDING)
	unsigned char                                      UnknownData_66RP : 3;                                      // 0x00C3(0x0001) BIT_FIELD (PADDING)
	unsigned char                                      bNeedsLoadForClient : 1;                                   // 0x00C3(0x0001) BIT_FIELD (Edit, NoDestructor)
	unsigned char                                      bNeedsLoadForServer : 1;                                   // 0x00C3(0x0001) BIT_FIELD (Edit, NoDestructor)
	unsigned char                                      UnknownData_0ZMF[0x2];                                     // 0x00C6(0x0002) MISSED OFFSET (PADDING)
};
//11.22
struct UDrunkennessComponentPublicData
{
	char pad1[0x0028];
	TArray<struct FDrunkennessSetupData>               DrunkennessSetupData;                                      // 0x0028(0x0010) (Edit, ZeroConstructor)
	float                                              VomitingThresholdWhenGettingDrunker;                       // 0x0038(0x0004) (Edit, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                              VomitingThresholdWhenSobering;                             // 0x003C(0x0004) (Edit, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                              MinTimeBetweenVomitSpews;                                  // 0x0040(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                              MaxTimeBetweenVomitSpews;                                  // 0x0044(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                              MinVomitSpewDuration;                                      // 0x0048(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                              MaxVomitSpewDuration;                                      // 0x004C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                              WaterSplashSoberingAmount;                                 // 0x0050(0x0004) (Edit, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                              WaterSplashSoberingRate;                                   // 0x0054(0x0004) (Edit, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class UCurveFloat* DrunkennessRemappingCurveForScreenVfx;                     // 0x0058(0x0008) (Edit, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class UCurveFloat* DrunkennessRemappingCurveForStaggering;                    // 0x0060(0x0008) (Edit, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                              CameraRollAmp;                                             // 0x0068(0x0004) (Edit, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                              CameraRollAccel;                                           // 0x006C(0x0004) (Edit, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class UWwiseObjectPoolWrapper* DrunkennessComponentPool;                                  // 0x0070(0x0008) (Edit, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class UWwiseEvent* StartDrunkennessSfx;                                       // 0x0078(0x0008) (Edit, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class UWwiseEvent* StopDrunkennessSfx;                                        // 0x0080(0x0008) (Edit, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class UWwiseEvent* StartDrunkennessSfxRemotePlayer;                           // 0x0088(0x0008) (Edit, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class UWwiseEvent* StopDrunkennessSfxRemotePlayer;                            // 0x0090(0x0008) (Edit, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FName                                       PlayerDrunkennessAmountRtpc;                               // 0x0098(0x0008) (Edit, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FName                                       RemotePlayerDrunkennessAmountRtpc;                         // 0x00A0(0x0008) (Edit, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                              MinDrunkennessToToggleLocomotionAnimType;                  // 0x00A8(0x0004) (Edit, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	unsigned char                                      UnknownData_JG4X[0x4];                                     // 0x00AC(0x0004) MISSED OFFSET (PADDING)
};
//11.22
struct UDrunkennessComponent
{
	char pad1[0x00D0];
	class UDrunkennessComponentPublicData* PublicData;                                                // 0x00D0(0x0008) (Edit, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	unsigned char                                      UnknownData_N5FF[0x140];                                   // 0x00D8(0x0140) MISSED OFFSET (FIX SPACE BETWEEN PREVIOUS PROPERTY)
	float                                              TargetDrunkenness;                                    // 0x0218(0x0008) (Net, ZeroConstructor, IsPlainOldData, RepNotify, NoDestructor, HasGetValueTypeHash)
	float                                              CurrentDrunkenness;                                   // 0x0220(0x0008) (Net, ZeroConstructor, IsPlainOldData, RepNotify, NoDestructor, HasGetValueTypeHash)
	float                                              RemainingAmountToSoberUpDueToWaterSplash;                  // 0x0228(0x0004) (Net, ZeroConstructor, IsPlainOldData, RepNotify, NoDestructor, HasGetValueTypeHash)
	unsigned char                                      UnknownData_SJF3[0xC];                                     // 0x022C(0x000C) MISSED OFFSET (FIX SPACE BETWEEN PREVIOUS PROPERTY)
	struct FName                                       VomitVFXType;                                              // 0x0250(0x0008) (Edit, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
};
//11.22
class ACharacter : public UObject {
public:
	
	char pad1[0x3C0];	//0x28 from inherit
	APlayerState* PlayerState;  // 0x3e8(0x8)													same
	char pad2[0x10];
	AController* Controller;// 0x400(0x8)														same           
	char pad3[0x38];
	USkeletalMeshComponent* Mesh; // 0x440(0x8)													same
	UCharacterMovementComponent* CharacterMovement;// 0x448(0x8)								same
	char pad4[0x3E0];
	UWieldedItemComponent* WieldedItemComponent; // 0x0830										same
	char pad43[0x8];
	UInventoryManipulatorComponent* InventoryManipulatorComponent; // 0x0840					same
	char pad5[0x10];
	UHealthComponent* HealthComponent; // 0x0858(0x0008)										same
	char pad6[0x4D8];
	UDrunkennessComponent* DrunkennessComponent; //  D38										same
	char pad7[0x8];
	UDrowningComponent* DrowningComponent;//   D48												same

	void ReceiveTick(float DeltaSeconds)
	{
		static auto fn = UObject::FindObject<UFunction>("Function Engine.ActorComponent.ReceiveTick");
		ProcessEvent(this, fn, &DeltaSeconds);
	}

	void GetActorBounds(bool bOnlyCollidingComponents, FVector& Origin, FVector& BoxExtent) {
		static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.GetActorBounds");
		struct
		{
			bool bOnlyCollidingComponents = false;
			FVector Origin;
			FVector BoxExtent;
		} params;

		params.bOnlyCollidingComponents = bOnlyCollidingComponents;

		ProcessEvent(this, fn, &params);

		Origin = params.Origin;
		BoxExtent = params.BoxExtent;
	}

	bool K2_SetActorLocation(FVector& NewLocation, bool bSweep, FHitResult& SweepHitResult, bool bTeleport)
	{
		static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.K2_SetActorLocation");
		struct
		{
			FVector NewLocation;
			bool bSweep = false;
			FHitResult SweepHitResult;
			bool bTeleport = false;
		} params;

		params.NewLocation = NewLocation;
		params.bSweep = bSweep;
		params.bTeleport = bTeleport;

		ProcessEvent(this, fn, &params);

		SweepHitResult = params.SweepHitResult;
	}


	bool BlueprintUpdateCamera(FVector& NewCameraLocation, FRotator& NewCameraRotation, float& NewCameraFOV)
	{
		static auto fn = UObject::FindObject<UFunction>("Function Engine.PlayerCameraManager.BlueprintUpdateCamera");
		struct
		{
			FVector NewCameraLocation;
			FRotator NewCameraRotation;
			float NewCameraFOV;
		} params;

		params.NewCameraLocation = NewCameraLocation;
		params.NewCameraRotation = NewCameraRotation;
		params.NewCameraFOV = NewCameraFOV;

		ProcessEvent(this, fn, &params);

		NewCameraLocation = params.NewCameraLocation;
		NewCameraRotation = params.NewCameraRotation;
		NewCameraFOV = params.NewCameraFOV;
	}

	ACharacter* GetCurrentShip() {
		static auto fn = UObject::FindObject<UFunction>("Function Athena.AthenaCharacter.GetCurrentShip");
		ACharacter* ReturnValue;
		ProcessEvent(this, fn, &ReturnValue);
		return ReturnValue;
	}

	ACharacter* GetAttachParentActor() {
		static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.GetAttachParentActor");
		ACharacter* ReturnValue;
		ProcessEvent(this, fn, &ReturnValue);
		return ReturnValue;
	};

	ACharacter* GetParentActor() {
		static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.GetParentActor");
		ACharacter* ReturnValue;
		ProcessEvent(this, fn, &ReturnValue);
		return ReturnValue;
	};

	ACharacter* GetWieldedItem() {
		if (!WieldedItemComponent) return nullptr;
		return WieldedItemComponent->CurrentlyWieldedItem;
	}

	FVector GetVelocity() {
		static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.GetVelocity");
		FVector velocity;
		ProcessEvent(this, fn, &velocity);
		return velocity;
	}

	FVector GetForwardVelocity() {
		static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.GetActorForwardVector");
		FVector ForwardVelocity;
		ProcessEvent(this, fn, &ForwardVelocity);
		return ForwardVelocity;
	}

	AItemInfo* GetItemInfo() {
		static auto fn = UObject::FindObject<UFunction>("Function Athena.ItemProxy.GetItemInfo");
		AItemInfo* info = nullptr;
		ProcessEvent(this, fn, &info);
		return info;
	}

	void CureAllAilings() {
		static auto fn = UObject::FindObject<UFunction>("Function Athena.AthenaCharacter.CureAllAilings");
		ProcessEvent(this, fn, nullptr);
	}

	void Kill(uint8_t DeathType) {
		static auto fn = UObject::FindObject<UFunction>("Function Athena.AthenaCharacter.Kill");
		ProcessEvent(this, fn, &DeathType);
	}

	bool IsDead() {
		static auto fn = UObject::FindObject<UFunction>("Function Athena.AthenaCharacter.IsDead");
		bool isDead = true;
		ProcessEvent(this, fn, &isDead);
		return isDead;
	}

	bool IsInWater() {
		static auto fn = UObject::FindObject<UFunction>("Function Athena.AthenaCharacter.IsInWater");
		bool isInWater = false;
		ProcessEvent(this, fn, &isInWater);
		return isInWater;
	}

	bool IsLoading() {
		static auto fn = UObject::FindObject<UFunction>("Function AthenaLoadingScreen.AthenaLoadingScreenBlueprintFunctionLibrary.IsLoadingScreenVisible");
		bool isLoading = true;
		ProcessEvent(this, fn, &isLoading);
		return isLoading;
	}

	bool IsShipSinking()
	{
		static auto fn = UObject::FindObject<UFunction>("Function Athena.HullDamage.IsShipSinking");
		bool IsShipSinking = true;
		ProcessEvent(this, fn, &IsShipSinking);
		return IsShipSinking;
	}

	bool IsSinking()
	{
		static auto fn = UObject::FindObject<UFunction>("Function Athena.SinkingComponent.IsSinking");
		bool IsSinking = true;
		ProcessEvent(this, fn, &IsSinking);
		return IsSinking;
	}

	bool PlayerIsTeleporting()
	{
		static auto fn = UObject::FindObject<UFunction>("Function Athena.StreamingTelemetryBaseEvent.PlayerIsTeleporting");
		bool PlayerIsTeleporting = true;
		ProcessEvent(this, fn, &PlayerIsTeleporting);
		return PlayerIsTeleporting;
	}

	FRotator K2_GetActorRotation() {
		static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.K2_GetActorRotation");
		FRotator params;
		ProcessEvent(this, fn, &params);
		return params;
	}

	FVector K2_GetActorLocation() {
		static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.K2_GetActorLocation");
		FVector params;
		ProcessEvent(this, fn, &params);
		return params;
	}

	FVector GetActorForwardVector() {
		static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.GetActorForwardVector");
		FVector params;
		ProcessEvent(this, fn, &params);
		return params;
	}

	FVector GetActorUpVector() {
		static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.GetActorUpVector");
		FVector params;
		ProcessEvent(this, fn, &params);
		return params;
	}

	inline bool isSkeleton() {
		static auto obj = UObject::FindClass("Class Athena.AthenaAICharacter");
		return IsA(obj);
	}

	inline bool isPlayer() {
		static auto obj = UObject::FindClass("Class Athena.AthenaPlayerCharacter");
		return IsA(obj);
	}

	inline bool isPuzzleVault() {
		static auto obj = UObject::FindClass("Class Athena.PuzzleVault");
		return IsA(obj);
	}

	inline bool isShip() {
		static auto obj = UObject::FindClass("Class Athena.Ship");
		return IsA(obj);
	}

	inline bool isSloop() {
		static auto obj = UObject::FindClass("Class Athena.SmallShip");
		return IsA(obj);
	}

	inline bool isCannonProjectile() {
		static auto obj = UObject::FindClass("Class Athena.CannonProjectile");
		return IsA(obj);
	}

	inline bool isMapTable() {
		static auto obj = UObject::FindClass("Class Athena.MapTable");
		return IsA(obj);
	}

	inline bool isCookingPot() {
		static auto obj = UObject::FindClass("Class Cooking.CookingPot");
		return IsA(obj);
	}

	inline bool isHarpoon() {
		static auto obj = UObject::FindClass("Class Athena.HarpoonLauncher");
		return IsA(obj);
	}

	inline bool isFishingRod() {
		static auto obj = UObject::FindClass("Class Athena.FishingRod");
		return IsA(obj);
	}

	inline bool isMap() {
		static auto obj = UObject::FindClass("Class Athena.TreasureMap");
		return IsA(obj);
	}

	inline bool isXMarkMap() {
		static auto obj = UObject::FindClass("Class Athena.XMarksTheSpotMap");
		return IsA(obj);
	}

	inline bool isCannon() {
		static auto obj = UObject::FindClass("Class Athena.Cannon");
		return IsA(obj);
	}

	inline bool isFarShip() {
		static auto obj = UObject::FindClass("Class Athena.ShipNetProxy");
		return IsA(obj);
	}

	inline bool isItem() {
		static auto obj = UObject::FindClass("Class Athena.ItemProxy");
		return IsA(obj);
	}

	inline bool isAmmoChest() {
		static auto obj = UObject::FindClass("Class Athena.AmmoChest");
		return IsA(obj);
	}






	inline bool isNewHole()
	{
		static auto obj = UObject::FindClass("BlueprintGeneratedClass BP_BaseInternalDamageZone.BP_BaseInternalDamageZone_C");
		return IsA(obj);
	}

	inline bool isKeg() {
		static auto obj = UObject::FindClass("");
		return IsA(obj);
	}

	inline bool isShipwreck() {
		static auto obj = UObject::FindClass("Class Athena.Shipwreck");
		return IsA(obj);

	}

	inline bool isShark() {
		static auto obj = UObject::FindClass("Class Athena.SharkPawn");
		return IsA(obj);
	}

	inline bool isMegalodon() {
		static auto obj = UObject::FindClass("Class Athena.TinyShark");
		return IsA(obj);
	}

	inline bool isMermaid() {
		static auto obj = UObject::FindClass("Class Athena.Mermaid");
		return IsA(obj);
	}

	inline bool isRowboat() {
		static auto obj = UObject::FindClass("Class Watercrafts.Rowboat");
		return IsA(obj);
	}

	inline bool isAnimal() {
		static auto obj = UObject::FindClass("Class AthenaAI.Fauna");
		return IsA(obj);
	}

	inline bool isEvent() {
		static auto obj = UObject::FindClass("Class Athena.GameplayEventSignal");
		return IsA(obj);
	}


	inline bool isStorm() {
		static auto obj = UObject::FindClass("Class Athena.Storm");
		return IsA(obj);
	}




	inline bool isSail() {
		static auto obj = UObject::FindClass("Class Athena.Sail");
		return IsA(obj);
	}

	inline bool isMast() {
		static auto obj = UObject::FindClass("Class Athena.Mast");
		return IsA(obj);
	}

	bool isWeapon() {
		static auto obj = UObject::FindClass("Class Athena.ProjectileWeapon");
		return IsA(obj);
	}

	bool isBucket() {
		static auto obj = UObject::FindClass("Class Athena.Bucket");
		return IsA(obj);
	}

	bool isSword() {
		static auto obj = UObject::FindClass("Class Athena.MeleeWeapon");
		return IsA(obj);
	}

	inline bool isBarrel() {
		static auto obj = UObject::FindClass("Class Athena.StorageContainer");
		return IsA(obj);
	}

	inline bool isStorageComponent() {
		static auto obj = UObject::FindClass("Class Athena.StorageContainerComponent");
		return IsA(obj);
	}

	bool isBuriedTreasure() {
		static auto obj = UObject::FindClass("Class Athena.BuriedTreasureLocation");
		return IsA(obj);
	}

	inline bool isSeagulls() {
		static auto obj = UObject::FindClass("Class Athena.Seagulls");
		return IsA(obj);
	}

	inline bool isEmissaryFlag() {
		static auto obj = UObject::FindClass("Class Athena.EmissaryFlag");
		return IsA(obj);
	}

	AHullDamage* GetHullDamage() {
		static auto fn = UObject::FindObject<UFunction>("Function Athena.Ship.GetHullDamage");
		AHullDamage* params = nullptr;
		ProcessEvent(this, fn, &params);
		return params;
	}	

	AShipInternalWater* GetInternalWater() {
		static auto fn = UObject::FindObject<UFunction>("Function Athena.Ship.GetInternalWater");
		AShipInternalWater* params = nullptr;
		ProcessEvent(this, fn, &params);
		return params;
	}

	float GetMinWheelAngle() {
		static auto fn = UObject::FindObject<UFunction>("Function Athena.Wheel.GetMinWheelAngle");
		float angle = 0.f;
		ProcessEvent(this, fn, &angle);
		return angle;
	}
	
	float GetMaxWheelAngle() {
		static auto fn = UObject::FindObject<UFunction>("Function Athena.Wheel.GetMaxWheelAngle");
		float angle = 0.f;
		ProcessEvent(this, fn, &angle);
		return angle;
	}

	void ForceSetWheelAngle(float Angle) {
		static auto fn = UObject::FindObject<UFunction>("Function Athena.Wheel.ForceSetWheelAngle");
		ProcessEvent(this, fn, &Angle);
	}

	bool CanJump() {
		static auto fn = UObject::FindObject<UFunction>("Function Engine.Character.CanJump");
		bool can_jump = false;
		ProcessEvent(this, fn, &can_jump);
		return can_jump;
	}

	void Jump() {
		static auto fn = UObject::FindObject<UFunction>("Function Engine.Character.Jump");
		ProcessEvent(this, fn, nullptr);
	}

	bool IsMastDown() {
		static auto fn = UObject::FindObject<UFunction>("Function Athena.Mast.IsMastFullyDamaged");
		bool ismastdown = false;
		ProcessEvent(this, fn, &ismastdown);
		return ismastdown;
	}

	void OpenFerryDoor() {
		static auto fn = UObject::FindObject<UFunction>("Function Athena.GhostShipDoor.OpenForPlayer");
		ProcessEvent(this, fn, nullptr);
	}

	float GetTargetFOV(class AAthenaPlayerCharacter* Character) {
		static auto fn = UObject::FindObject<UFunction>("Function Athena.FOVHandlerFunctions.GetTargetFOV");
		UFOVHandlerFunctions_GetTargetFOV_Params params;
		params.Character = Character;
		ProcessEvent(this, fn, &params);
		return params.ReturnValue;
	}

	void SetTime(int Hours)
	{
		static auto fn = UObject::FindObject<UFunction>("Function Athena.GameCustomizationService.SetTime");
		AGameCustomizationService_SetTime_Params params;
		params.Hours = Hours;
		ProcessEvent(this, fn, &params);
	}

	void SetTargetFOV(class AAthenaPlayerCharacter* Character, float TargetFOV) {
		static auto fn = UObject::FindObject<UFunction>("Function Athena.FOVHandlerFunctions.SetTargetFOV");
		UFOVHandlerFunctions_SetTargetFOV_Params params;
		params.Character = Character;
		params.TargetFOV = TargetFOV;
		ProcessEvent(this, fn, &params);
	}
};

class UKismetTextLibrary
{
private:
	static inline UClass* defaultObj;
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindObject<UClass>("Class Engine.KismetTextLibrary");
		return ptr;
	}


	static struct FText TextTrimTrailing(const struct FText& InText);
	static struct FText TextTrimPrecedingAndTrailing(const struct FText& InText);
	static struct FText TextTrimPreceding(const struct FText& InText);
	static bool TextIsTransient(const struct FText& InText);
	static bool TextIsEmpty(const struct FText& InText);
	static bool TextIsCultureInvariant(const struct FText& InText);
	static bool NotEqual_TextText(const struct FText& A, const struct FText& B);
	static bool NotEqual_IgnoreCase_TextText(const struct FText& A, const struct FText& B);
	static struct FText GetEmptyText();
	static struct FText Format(const struct FText& InPattern, TArray<struct FFormatTextArgument> InArgs);
	static bool FindTextInLocalizationTable(const class FString& Namespace, const class FString& Key, struct FText* OutText);
	static bool EqualEqual_TextText(const struct FText& A, const struct FText& B);
	static bool EqualEqual_IgnoreCase_TextText(const struct FText& A, const struct FText& B);
	//static class FString Conv_TextToString(const struct FText& InText);
	static struct FText Conv_StringToText(const class FString& InString);
	static class FString Conv_TextToString(const struct FText& InText)
	{
		static auto fn = UObject::FindObject<UFunction>("Function Engine.KismetTextLibrary.Conv_TextToString");

		struct
		{
			struct FText                   InText;
			class FString                  ReturnValue;
		} params;

		params.InText = InText;

		ProcessEvent(defaultObj, fn, &params);
		return params.ReturnValue;
	}

	static struct FText Conv_NameToText(const struct FName& InName)
	{
		static auto fn = UObject::FindObject<UFunction>("Function Engine.KismetTextLibrary.Conv_NameToText");

		struct
		{
			struct FName                   InName;
			struct FText                   ReturnValue;
		} params;

		params.InName = InName;

		ProcessEvent(defaultObj, fn, &params);
		return params.ReturnValue;
	}
	//static struct FText Conv_NameToText(const struct FName& InName);
	static struct FText Conv_IntToText(int Value, bool bUseGrouping, int MinimumIntegralDigits, int MaximumIntegralDigits);
	static struct FText Conv_FloatToText(float Value, char RoundingMode, bool bUseGrouping, int MinimumIntegralDigits, int MaximumIntegralDigits, int MinimumFractionalDigits, int MaximumFractionalDigits);
	static struct FText Conv_ByteToText(unsigned char Value);
	static struct FText Conv_BoolToText(bool InBool);
	static struct FText AsTimespan_Timespan(const struct FTimespan& InTimespan);
	static struct FText AsTime_DateTime(const struct FDateTime& In);
	static struct FText AsPercent_Float(float Value, char RoundingMode, bool bUseGrouping, int MinimumIntegralDigits, int MaximumIntegralDigits, int MinimumFractionalDigits, int MaximumFractionalDigits);
	static struct FText AsDateTime_DateTime(const struct FDateTime& In);
	static struct FText AsDate_DateTime(const struct FDateTime& InDateTime);
	static struct FText AsCurrency_Integer(int Value, char RoundingMode, bool bUseGrouping, int MinimumIntegralDigits, int MaximumIntegralDigits, int MinimumFractionalDigits, int MaximumFractionalDigits, const class FString& CurrencyCode);
	static struct FText AsCurrency_Float(float Value, char RoundingMode, bool bUseGrouping, int MinimumIntegralDigits, int MaximumIntegralDigits, int MinimumFractionalDigits, int MaximumFractionalDigits, const class FString& CurrencyCode);
};

class UKismetMathLibrary {
private:
	static inline UClass* defaultObj;
public:
	static bool Init() {
		return defaultObj = UObject::FindObject<UClass>("Class Engine.KismetMathLibrary");
	}
	static FRotator NormalizedDeltaRotator(const struct FRotator& A, const struct FRotator& B) {
		static auto fn = UObject::FindObject<UFunction>("Function Engine.KismetMathLibrary.NormalizedDeltaRotator");

		struct
		{
			struct FRotator                A;
			struct FRotator                B;
			struct FRotator                ReturnValue;
		} params;

		params.A = A;
		params.B = B;

		ProcessEvent(defaultObj, fn, &params);

		return params.ReturnValue;

	};
	static FRotator FindLookAtRotation(const FVector& Start, const FVector& Target) {
		static auto fn = UObject::FindObject<UFunction>("Function Engine.KismetMathLibrary.FindLookAtRotation");

		struct {
			FVector Start;
			FVector Target;
			FRotator ReturnValue;
		} params;
		params.Start = Start;
		params.Target = Target;

		ProcessEvent(defaultObj, fn, &params);
		return params.ReturnValue;
	}

	static FVector Conv_RotatorToVector(const struct FRotator& InRot) {
		static auto fn = UObject::FindObject<UFunction>("Function Engine.KismetMathLibrary.Conv_RotatorToVector");

		struct
		{
			struct FRotator                InRot;
			struct FVector                 ReturnValue;
		} params;
		params.InRot = InRot;

		ProcessEvent(defaultObj, fn, &params);		
		return params.ReturnValue;
	}

	static bool LineTraceSingle_NEW(class UObject* WorldContextObject, const struct FVector& Start, const struct FVector& End, ETraceTypeQuery TraceChannel, bool bTraceComplex, TArray<class AActor*> ActorsToIgnore, EDrawDebugTrace DrawDebugType, bool bIgnoreSelf, struct FHitResult* OutHit)
	{
		static auto fn = UObject::FindObject<UFunction>("Function Engine.KismetSystemLibrary.LineTraceSingle_NEW");

		struct
		{
			class UObject* WorldContextObject;
			struct FVector                 Start;
			struct FVector                 End;
			ETraceTypeQuery				   TraceChannel;
			bool                           bTraceComplex;
			TArray<class AActor*>          ActorsToIgnore;
			EDrawDebugTrace				   DrawDebugType;
			struct FHitResult              OutHit;
			bool                           bIgnoreSelf;
			bool                           ReturnValue;
		} params;

		params.WorldContextObject = WorldContextObject;
		params.Start = Start;
		params.End = End;
		params.TraceChannel = TraceChannel;
		params.bTraceComplex = bTraceComplex;
		params.ActorsToIgnore = ActorsToIgnore;
		params.DrawDebugType = DrawDebugType;
		params.bIgnoreSelf = bIgnoreSelf;

		ProcessEvent(defaultObj, fn, &params);

		if (OutHit != nullptr)
			*OutHit = params.OutHit;

		return params.ReturnValue;
	}

	static void DrawDebugBox(UObject* WorldContextObject, const FVector& Center, const FVector& Extent, const FLinearColor& LineColor, const FRotator& Rotation, float Duration) {
		static auto fn = UObject::FindObject<UFunction>("Function Engine.KismetSystemLibrary.DrawDebugBox");
		struct
		{
			UObject* WorldContextObject = nullptr;
			FVector Center;
			FVector Extent;
			FLinearColor LineColor;
			FRotator Rotation;
			float Duration = INFINITY;
		} params;

		params.WorldContextObject = WorldContextObject;
		params.Center = Center;
		params.Extent = Extent;
		params.LineColor = LineColor;
		params.Rotation = Rotation;
		params.Duration = Duration;
		ProcessEvent(defaultObj, fn, &params);
	}
	static void DrawDebugArrow(UObject* WorldContextObject, const FVector& LineStart, const FVector& LineEnd, float ArrowSize, const FLinearColor& LineColor, float Duration) {
		static auto fn = UObject::FindObject<UFunction>("Function Engine.KismetSystemLibrary.DrawDebugBox");
		struct
		{
			class UObject* WorldContextObject = nullptr;
			struct FVector LineStart;
			struct FVector LineEnd;
			float ArrowSize = 1.f;
			struct FLinearColor LineColor;
			float Duration = 1.f;
		} params;

		params.WorldContextObject = WorldContextObject;
		params.LineStart = LineStart;
		params.LineEnd = LineEnd;
		params.ArrowSize = ArrowSize;
		params.LineColor = LineColor;
		params.Duration = Duration;

		ProcessEvent(defaultObj, fn, &params);
	}
};

struct UCrewFunctions {
private:
	static inline UClass* defaultObj;
public:
	static bool Init() {
		return defaultObj = UObject::FindObject<UClass>("Class Athena.CrewFunctions");
	}
	static bool AreCharactersInSameCrew(ACharacter* Player1, ACharacter* Player2) {
		static auto fn = UObject::FindObject<UFunction>("Function Athena.CrewFunctions.AreCharactersInSameCrew");
		struct
		{
			ACharacter* Player1;
			ACharacter* Player2;
			bool ReturnValue;
		} params;
		params.Player1 = Player1;
		params.Player2 = Player2;
		ProcessEvent(defaultObj, fn, &params);
		return params.ReturnValue;
	}
};
//11.22 
struct UPlayer {
	char UnknownData00[0x30];
	AController* PlayerController;
};
//11.22
struct UGameInstance {
	char UnknownData00[0x38];
	TArray<UPlayer*> LocalPlayers; // 0x38

	struct UOnlineSession* OnlineSession; // 0x50(0x08)  idk hogy kell e ez id
	

};
//11.22 udk            Class Engine.Level                       struct ULevel : UObject {
struct ULevel {
	char UnknownData00[0xA0];
	TArray<ACharacter*> AActors;
};
//11.22 idk
struct UWorld {
	static inline UWorld** GWorld = nullptr;
	char pad1[0x30];
	/*ULevel* PersistentLevel; // 0x0030(0x8)
	char pad2[0x20];
	AAthenaGameState* GameState; //0x0058(0x8)
	char pad3[0xF0];
	TArray<ULevel*> Levels; //0x0150(0x10)
	char pad4[0x50];
	ULevel* CurrentLevel; //0x01B0(0x8)
	char pad5[0x8];
	UGameInstance* GameInstance; //0x01C0(0x8)*/
	ULevel* PersistentLevel; // 0x30(0x08)
	struct UNetDriver* NetDriver; // 0x38(0x08)
	struct ULineBatchComponent* LineBatcher; // 0x40(0x08)
	struct ULineBatchComponent* PersistentLineBatcher; // 0x48(0x08)
	struct ULineBatchComponent* ForegroundLineBatcher; // 0x50(0x08)
	AAthenaGameState* GameState; // 0x58(0x08)
	struct AGameNetworkManager* NetworkManager; // 0x60(0x08)
	struct UPhysicsCollisionHandler* PhysicsCollisionHandler; // 0x68(0x08)
	struct TArray<struct UObject*> ExtraReferencedObjects; // 0x70(0x10)
	struct TArray<struct UObject*> PerModuleDataObjects; // 0x80(0x10)
	struct TArray<struct ULevelStreaming*> StreamingLevels; // 0x90(0x10)
	struct FString StreamingLevelsPrefix; // 0xa0(0x10)
	struct ULevel* CurrentLevelPendingVisibility; // 0xb0(0x08)
	struct AParticleEventManager* MyParticleEventManager; // 0xb8(0x08)
	struct APhysicsVolume* DefaultPhysicsVolume; // 0xc0(0x08)
	struct TArray<struct ULevelStreaming*> DirtyStreamingLevels; // 0xc8(0x10)
	char UnknownData_D8[0x1c]; // 0xd8(0x1c)
	struct FName Feature; // 0xf4(0x08)
	char UnknownData_FC[0x4]; // 0xfc(0x04)
	struct TArray<struct FName> FeatureReferences; // 0x100(0x10)
	bool ParticleLOD_bUseGameThread; // 0x110(0x01)
	bool ParticleLOD_bUseMultipleViewportCase; // 0x111(0x01)
	char UnknownData_112[0x2]; // 0x112(0x02)
	struct FVector ParticleLOD_PlayerViewpointLocation; // 0x114(0x0c)
	struct FString TestMetadata; // 0x120(0x10)
	struct UNavigationSystem* NavigationSystem; // 0x130(0x08)
	struct AGameMode* AuthorityGameMode; // 0x138(0x08)
	struct UAISystemBase* AISystem; // 0x140(0x08)
	struct UAvoidanceManager* AvoidanceManager; // 0x148(0x08)
	TArray<struct ULevel*> Levels; // 0x150(0x10)
	char UnknownData_160[0x50]; // 0x160(0x50)
	struct ULevel* CurrentLevel; // 0x1b0(0x08)
	char UnknownData_1B8[0x8]; // 0x1b8(0x08)
	UGameInstance* OwningGameInstance; // 0x1c0(0x08)
	struct TArray<struct UMaterialParameterCollectionInstance*> ParameterCollectionInstances; // 0x1c8(0x10)
	char UnknownData_1D8[0x520]; // 0x1d8(0x520)
	struct UWorldComposition* WorldComposition; // 0x6f8(0x08)
	char UnknownData_700[0x3d]; // 0x700(0x3d)
	char UnknownData_73D_0 : 7; // 0x73d(0x01)
	char bAreConstraintsDirty : 1; // 0x73d(0x01)
	char UnknownData_73E[0x8a]; // 0x73e(0x8a)
};

enum class EMeleeWeaponMovementSpeed : uint8_t
{
	EMeleeWeaponMovementSpeed__Default = 0,
	EMeleeWeaponMovementSpeed__SlightlySlowed = 1,
	EMeleeWeaponMovementSpeed__Slowed = 2,
	EMeleeWeaponMovementSpeed__EMeleeWeaponMovementSpeed_MAX = 3
};

//11.22
struct UMeleeAttackDataAsset
{
	char pad[0x0238];
	float                                              ClampYawRange;                                             // 0x0238(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                              ClampYawRate;                                              // 0x023C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
};

//11.22
struct UMeleeWeaponDataAsset
{
	char pad[0x0048];
	class UMeleeAttackDataAsset* HeavyAttack; //0x0048
	char pad2[0x0028];
	EMeleeWeaponMovementSpeed BlockingMovementSpeed; //0x0078
};
//11.22
struct AMeleeWeapon
{
	char pad[0x07A8];
	struct UMeleeWeaponDataAsset* DataAsset; //0x7A8 
};
struct FWorldMapShipLocation {
	struct FGuid CrewId; // 0x00(0x10)
	struct UClass* ShipSize; // 0x10(0x08)
	struct FVector2D Location; // 0x18(0x08)
	float Rotation; // 0x20(0x04)
	char ReplicatedRotation; // 0x24(0x01)
	char Flags; // 0x25(0x01)
	char UnknownData_26[0x2]; // 0x26(0x02)
	struct UTexture* CrewLiveryOverlayIcon; // 0x28(0x08)
	char ReapersMarkLevel; // 0x30(0x01)
	char EmissaryLevel; // 0x31(0x01)
	bool OwnerIsInFaction; // 0x32(0x01)
	bool OwnerIsMaxFaction; // 0x33(0x01)
	struct FName OwnerFactionName; // 0x34(0x08)
	bool OwnerIsInvadingShip; // 0x3c(0x01)
	char UnknownData_3D[0x3]; // 0x3d(0x03)
};
//11.22
struct AMapTable
{
	char pad[0x04E8];
	TArray<struct FVector2D> MapPins; // 0x04E8
	TArray<struct FWorldMapShipLocation> TrackedShips; // 0x4f8(0x10)
};
//11.22
struct AInteractableBase {
	char UnknownData_3C8[0x3d8]; // 0x3c8(0x10)
	bool RequiresFacingFront; // 0x3d8(0x01)
	bool RequiresNotBeingAirborne; // 0x3d9(0x01)
	bool RequiresNotSwimming; // 0x3da(0x01)
	bool InteractionsCanBeDisabled; // 0x3db(0x01)
	bool CanSetInteractionState; // 0x3dc(0x01)
	char UnknownData_3DD[0x3]; // 0x3dd(0x03)
	struct TArray<struct UInteractionPrerequisiteBase*> InteractionPrerequisites; // 0x3e0(0x10)
	struct UActionRulesComponent* ActionRulesComponent; // 0x3f0(0x08)
	char InteractableIdentifier; // 0x3f8(0x01)
	char UnknownData_3F9[0x1]; // 0x3f9(0x01)
	char CurrentInteractionState; // 0x3fa(0x01)
	char UnknownData_3FB[0x5]; // 0x3fb(0x05)
};
//11.22
struct FCookingClientRepresentation {
	bool Cooking; // 0x00(0x01)
	bool HasItem; // 0x01(0x01)
	char UnknownData_2[0x06]; // 0x02(0x06)
	struct AItemInfo* CurrentlyCookingItem; // 0x08(0x08)
	//struct FString CurrentCookingItemDisplayName; // 0x10(0x38)
	char pad[0x38];
	struct UClass* CurrentCookingItemCategory; // 0x48(0x08)
	char SmokeFeedbackLevel; // 0x50(0x01)
	char UnknownData_51[0x3]; // 0x51(0x03)
	float VisibleCookedExtent; // 0x54(0x04)
	float CurrentItemPlacementAngle; // 0x58(0x04)
	struct FName CurrentCookableTypeName; // 0x5c(0x08)
	char UnknownData_64[0x4]; // 0x64(0x04)
};
//11.22
struct UCookerComponent {
	char UnknownData_C8[0xd0]; // 0xc8(0x08)
	struct TArray<struct FStatus> StatusToApplyToContents; // 0xd0(0x10)
	struct TArray<struct FCookerSmokeFeedbackEntry> VFXFeedback; // 0xe0(0x10)
	struct UStaticMeshMemoryConstraintComponent* CookableStaticMeshComponent; // 0xf0(0x08)
	struct USkeletalMeshMemoryConstraintComponent* CookableSkeletalMeshComponent; // 0xf8(0x08)
	struct FName CookedMaterialParameterName; // 0x100(0x08)
	struct FName BurnDownDirectionParameterName; // 0x108(0x08)
	float PlacementVarianceAngleBound; // 0x110(0x04)
	bool OnByDefault; // 0x114(0x01)
	char UnknownData_115[0x03]; // 0x115(0x03)
	struct UCookingComponentAudioParams* AudioParams; // 0x118(0x08)
	char VfxLocation; // 0x120(0x01)
	char UnknownData_121[0x7]; // 0x121(0x07)
	struct AItemInfo* CurrentlyCookingItem; // 0x128(0x08)
	struct FCookingClientRepresentation CookingState; // 0x130(0x68)
	struct UParticleSystemComponent* SmokeParticleComponent; // 0x198(0x08)
	struct UMaterialInstanceDynamic* VisibleCookableMaterial; // 0x1a0(0x08)
	bool TurnedOn; // 0x1a8(0x01)
	bool OnIsland; // 0x1a9(0x01)
	char UnknownData_1AA[0x9e]; // 0x1aa(0x9e)

	void OnRep_CookingState(struct FCookingClientRepresentation OldRepresentation); // Function Cooking.CookerComponent.OnRep_CookingState // Final|Native|Private|HasOutParms // @ game+0x3915310
};

struct FPlayerStat {
	uint32_t StatId; // 0x00(0x04)
};
//11.22
struct UCookableComponent {
	char UnknownData_C8[0xe8]; // 0xc8(0x20)
	struct UClass* NextCookState; // 0xe8(0x08)
	float TimeToNextCookState; // 0xf0(0x04)
	char UnknownData_F4[0x4]; // 0xf4(0x04)
	struct TArray<struct FCookableComponentSmokeFeedbackTimingEntry> SmokeFeedbackLevels; // 0xf8(0x10)
	struct UCurveFloat* VisibleCookedExtentOverTime; // 0x108(0x08)
	float DefaultVisibleCookedExtent; // 0x110(0x04)
	struct FName CookableTypeName; // 0x114(0x08)
	struct FPlayerStat CookedStat; // 0x11c(0x04)
	struct FPlayerStat ShipCookedStat; // 0x120(0x04)
	char CookingState; // 0x124(0x01)
	char InitialCookingState; // 0x125(0x01)
	char RemovedCookingState; // 0x126(0x01)
	bool IgnoreCookedFromRawStats; // 0x127(0x01)
};

struct ACookingPot {
	char UnknownData_400[0x408]; // 0x400(0x08)
	struct UStaticMeshComponent* MeshComponent; // 0x408(0x08)
	struct UActionRulesInteractableComponent* InteractableComponent; // 0x410(0x08)
	struct UCookerComponent* CookerComponent; // 0x418(0x08)
	float HoldToInteractTime; // 0x420(0x04)
	char UnknownData_424[0x4]; // 0x424(0x04)
	//struct FString NotWieldingCookableItemTooltip; // 0x428(0x38)
	//struct FString WieldingCookableItemTooltip; // 0x460(0x38)
	//struct FString TakeItemTooltip; // 0x498(0x38)
	//struct FString CannotTakeItemTooltip; // 0x4d0(0x38)
	//struct FString MixInItemTooltip; // 0x508(0x38)*/
	char pad[0x118];
	char UnknownData_540[0xa0]; // 0x540(0xa0)
};

struct FFishingMiniGameData {
	struct UFishingMiniGameSetupDataAsset* SetupDataAsset; // 0x00(0x08)
	struct UFishingMiniGameFishDataAsset* FishDataAsset; // 0x08(0x08)
};

struct FFishingMiniGame {
	struct FFishingMiniGameData Data; // 0x00(0x10)
	char UnknownData_10[0x40]; // 0x10(0x40)
};

struct FFishingMiniGamePlayerInput {
	char InputDirection; // 0x00(0x01)
	char BattlingDirection; // 0x01(0x01)
	bool IsReeling; // 0x02(0x01)
};

enum class EFishingFishState : uint8_t {
	NotSet = 0,
	RisingFromTheDepths = 1,
	AttachedToFloat_MovingToFloat = 2,
	AttachedToFloat_Battling = 3,
	AttachedToFloat_Tired = 4,
	AttachedToFloat_Caught = 5,
	AttachedToFloat_Caught_Instant = 6,
	Escaping = 7,
	EFishingFishState_MAX = 8,
};

struct AFishingFish : ACharacter {
	char UnknownData_5E0[0x5f0]; // 0x5e0(0x10)
	struct UFishDataAsset* FishDataAsset; // 0x5f0(0x08)
	struct UFishingMiniGameFishDataAsset* FishingMiniGameFishDataAsset; // 0x5f8(0x08)
	struct UParticleSystemComponent* BattlingVFX; // 0x600(0x08)
	struct UParticleSystemComponent* BeingTiredVFX; // 0x608(0x08)
	struct UWaterInteractionComponent* WaterInteractionComponent; // 0x610(0x08)
	struct UClass* CaughtFishItemDesc; // 0x618(0x08)
	char UnknownData_620[0x290]; // 0x620(0x290)
	struct UDitherComponent* DitherComponent; // 0x8b0(0x08)
	struct FVector MouthAttachLocation; // 0x8b8(0x0c)
	float AutoKillTime; // 0x8c4(0x04)
	char UnknownData_8C8[0x8]; // 0x8c8(0x08)
	int32_t RandomAnimationLoopVal; // 0x8d0(0x04)
	char UnknownData_8D4[0x3c]; // 0x8d4(0x3c)

	void Multicast_SetVisible(); // Function Athena.FishingFish.Multicast_SetVisible // Net|NetReliableNative|Event|NetMulticast|Public // @ game+0x3d908c0
};

struct FAthenaAnimationFishingParams {
	char FishingState; // 0x00(0x01)
	bool InFishing; // 0x01(0x01)
	char UnknownData_2[0x2]; // 0x02(0x02)
	struct FVector2D RodBend; // 0x04(0x08)
	float ReelSpeed; // 0x0c(0x04)
	bool CastFailed; // 0x10(0x01)
	bool IsFishHookedAndVisible; // 0x11(0x01)
	char UnknownData_12[0x2]; // 0x12(0x02)
	struct FVector2D PlayerInputForce; // 0x14(0x08)
	float TensionShake; // 0x1c(0x04)
	float LineSnapShake; // 0x20(0x04)
	bool IKIsActive; // 0x24(0x01)
	char UnknownData_25[0x3]; // 0x25(0x03)
	float IKBlendInSpeed; // 0x28(0x04)
	float IKBlendIOutSpeed; // 0x2c(0x04)
	bool IsComedyItem; // 0x30(0x01)
	char FishingJIPState; // 0x31(0x01)
	char UnknownData_32[0x2]; // 0x32(0x02)
};

struct FEventSetFishingTensionShake {
	float TensionShake; // 0x00(0x04)
};

struct FFishingRodReplicatedFishState {
	struct AFishingFish* FishingFish; // 0x00(0x08)
	char FishingFishState; // 0x08(0x01)
	bool FishHasEscaped; // 0x09(0x01)
	char UnknownData_A[0x6]; // 0x0a(0x06)
};

struct FFishingFishSelector {
	struct UAvailableFishForSpawning* AvailableFish; // 0x00(0x08)
	char UnknownData_8[0xa8]; // 0x08(0xa8)
	struct TArray<struct UFishSpawnParamsDataAsset*> SelectedFishCache; // 0xb0(0x10)
	struct UObject* Root; // 0xc0(0x08)
	struct UFishSpawnParamsDataAsset* GatheredConditions; // 0xc8(0x08)
	struct UVoyageLocationOnlyNamedIslandListDataAsset* GatheredIsland; // 0xd0(0x08)
};

struct AFishingRod {
	char UnknownData_780[0x7a0]; // 0x780(0x20)
	struct UClass* AuxiliaryRadialCategoryFilter; // 0x7a0(0x08)
	struct TArray<struct UClass*> AuxiliaryRadialAllowedItems; // 0x7a8(0x10)
	struct UInventoryItemComponent* InventoryItem; // 0x7b8(0x08)
	struct FFishingFishSelector FishSelector; // 0x7c0(0xd8)
	struct UFishingRodSetupDataAsset* FishingRodSetupDataAsset; // 0x898(0x08)
	struct UFishingSetupDataAsset* FishingSetupDataAssetInToSea; // 0x8a0(0x08)
	struct UFishingSetupDataAsset* FishingSetupDataAssetInToPond; // 0x8a8(0x08)
	struct UFishingMiniGameSetupDataAsset* FishingMiniGameSetupDataAssetInToSea; // 0x8b0(0x08)
	struct UFishingMiniGameSetupDataAsset* FishingMiniGameSetupDataAssetInToPond; // 0x8b8(0x08)
	struct UFishingFreeLookConstrainsDataAsset* FishingFreeLookConstrainsDataAsset; // 0x8c0(0x08)
	struct UMaterialManipulationComponent* MaterialManipulationComponent; // 0x8c8(0x08)
	struct UFishingLineRenderComponent* Rope; // 0x8d0(0x08)
	struct FVector InteractionPointOffset; // 0x8d8(0x0c)
	char UnknownData_8E4[0x4]; // 0x8e4(0x04)
	struct UClass* StatTriggerForCatchingAFish; // 0x8e8(0x08)
	char ServerState; // 0x8f0(0x01)
	bool IsReeling; // 0x8f1(0x01)
	char UnknownData_8F2[0x6]; // 0x8f2(0x06)
	struct FFishingRodReplicatedFishState ReplicatedFishState; // 0x8f8(0x10)
	struct AActor* FishInteractionProxy; // 0x908(0x08)
	struct FFishingMiniGamePlayerInput FishingMiniGamePlayerInput; // 0x910(0x03)
	bool PlayerIsBattlingFish; // 0x913(0x01)
	char UnknownData_914[0x4]; // 0x914(0x04)
	struct AItemProxy* BaitOnFloat; // 0x918(0x08)
	struct FVector FishingFloatRelativeCentreLocation; // 0x920(0x0c)
	struct FVector FishingFloatOffset; // 0x92c(0x0c)
	bool CastIsInToAPond; // 0x938(0x01)
	char UnknownData_939[0x7]; // 0x939(0x07)
	struct UClass* CaughtFishClass; // 0x940(0x08)
	char BaitOnRodType; // 0x948(0x01)
	char BattlingState; // 0x949(0x01)
	char UnknownData_94A[0x6]; // 0x94a(0x06)
	struct AItemProxy* ComedyItemOnFloat; // 0x950(0x08)
	struct UClass* CaughtComedyItemDesc; // 0x958(0x08)
	float TimeReelingWhenBattlingBeforeSnapping; // 0x960(0x04)
	float FishingMiniGamePercentageInToEscaping; // 0x964(0x04)
	float MinimumDistanceFromPlayer; // 0x968(0x04)
	char UnknownData_96C[0x4]; // 0x96c(0x04)
	struct AActor* FishingFloatActor; // 0x970(0x08)
	struct AItemProxy* LocalOnlyBaitOnFloat; // 0x978(0x08)
	struct FFishingMiniGame FishingMiniGame; // 0x980(0x50)
	struct AFishingFish* NonReplicatedLocalFishingFishOnRod; // 0x9d0(0x08)
	struct AItemProxy* LocalOnlyComedyItemOnFloat; // 0x9d8(0x08)
	bool IsInFishingActionState; // 0x9e0(0x01)
	char UnknownData_9E1[0x1af]; // 0x9e1(0x1af)

	//void Server_ToggleReeling(bool Reeling);// Function Athena.FishingRod.Server_ToggleReeling // Final|Net|NetReliableNative|Event|Private|NetServer|NetValidate // @ game+0x3d90fb0
	void Server_ToggleReeling(bool Reeling)
	{
		static auto fn = UObject::FindObject<UFunction>("Function Athena.FishingRod.Server_ToggleReeling");
		struct {
			bool Reeling = false;
		} params;
		params.Reeling = Reeling;
		ProcessEvent(this, fn, &params);
	}
	void Server_SetAreFishingAnimationsLoaded(bool InAreAnimsLoaded); // Function Athena.FishingRod.Server_SetAreFishingAnimationsLoaded // Final|Net|NetReliableNative|Event|Private|NetServer|NetValidate // @ game+0x3d90ef0
	void Server_PlayerHasDetectedABlockedLine(); // Function Athena.FishingRod.Server_PlayerHasDetectedABlockedLine // Final|Net|NetReliableNative|Event|Private|NetServer|NetValidate // @ game+0x3d90ea0
	void Server_PlayerHasDetectedABlockedFish(); // Function Athena.FishingRod.Server_PlayerHasDetectedABlockedFish // Final|Net|NetReliableNative|Event|Private|NetServer|NetValidate // @ game+0x3d90e50
	//void Server_EndPreCasting(float Duration); // Function Athena.FishingRod.Server_EndPreCasting // Final|Net|NetReliableNative|Event|Private|NetServer|NetValidate // @ game+0x3d90da0
	void Server_EndPreCasting(float Duration)
	{
		static auto fn = UObject::FindObject<UFunction>("Function Athena.FishingRod.Server_EndPreCasting");
		struct {
			float Duration;
		} params;
		params.Duration = Duration;
		ProcessEvent(this, fn, &params);
	}
	void Server_BeginPreCasting() // Function Athena.FishingRod.Server_BeginPreCasting // Final|Net|NetReliableNative|Event|Private|NetServer|NetValidate // @ game+0x3d90d50
	{
		static auto fn = UObject::FindObject<UFunction>("Function Athena.FishingRod.Server_BeginPreCasting");
		ProcessEvent(this, fn, nullptr);
	}
		//void Server_BattlingStateChanged(char InputDirection, char BattlingDirection); // Function Athena.FishingRod.Server_BattlingStateChanged // Final|Net|NetReliableNative|Event|Private|NetServer|NetValidate // @ game+0x3d90c60
	void Server_BattlingStateChanged(char InputDirection, char BattlingDirection)
	{
		static auto fn = UObject::FindObject<UFunction>("Function Athena.FishingRod.Server_BattlingStateChanged");
		struct {
			char InputDirection;
			char BattlingDirection;
		} params;
		params.InputDirection = InputDirection;
		params.BattlingDirection = BattlingDirection;
		ProcessEvent(this, fn, &params);
	}
	void Server_AddBaitToFloat(struct AItemInfo* SelectedItem); // Function Athena.FishingRod.Server_AddBaitToFloat // Final|Net|NetReliableNative|Event|Private|NetServer|NetValidate // @ game+0x3d90ba0
	void OnRep_ServerState(); // Function Athena.FishingRod.OnRep_ServerState // Final|Native|Private // @ game+0x3d90aa0
	void OnRep_ReplicatedFishState(struct FFishingRodReplicatedFishState PreviousReplicatedFishState); // Function Athena.FishingRod.OnRep_ReplicatedFishState // Final|Native|Private|HasOutParms // @ game+0x3d90a00
	void OnRep_PlayerIsBattlingFish(); // Function Athena.FishingRod.OnRep_PlayerIsBattlingFish // Final|Native|Private // @ game+0x3d909e0
	void OnRep_FishInteractionProxy(); // Function Athena.FishingRod.OnRep_FishInteractionProxy // Final|Native|Private // @ game+0x3d909a0
	void OnRep_FishingMiniGamePlayerInput(); // Function Athena.FishingRod.OnRep_FishingMiniGamePlayerInput // Final|Native|Private // @ game+0x3d909c0
	void OnRep_ComedyItemOnFloat(); // Function Athena.FishingRod.OnRep_ComedyItemOnFloat // Final|Native|Private // @ game+0x3d90980
	void OnRep_CaughtFishClass(); // Function Athena.FishingRod.OnRep_CaughtFishClass // Final|Native|Private // @ game+0x3d90960
	void OnRep_BattlingState(); // Function Athena.FishingRod.OnRep_BattlingState // Final|Native|Private // @ game+0x3d90940
	void OnRep_BaitOnRodType(); // Function Athena.FishingRod.OnRep_BaitOnRodType // Final|Native|Private // @ game+0x3d90920
	void OnRep_BaitOnFloat(); // Function Athena.FishingRod.OnRep_BaitOnFloat // Final|Native|Private // @ game+0x3d90900
	void OnComedyItemDestroyed(); // Function Athena.FishingRod.OnComedyItemDestroyed // Final|Native|Private // @ game+0x3d908e0
	void Multicast_RetractLine(char FishingRodRetractLineVisuals); // Function Athena.FishingRod.Multicast_RetractLine // Final|Net|NetReliableNative|Event|NetMulticast|Private // @ game+0x3d90840
	void Multicast_RemoveFishInstant();// Function Athena.FishingRod.Multicast_RemoveFishInstant // Final|Net|NetReliableNative|Event|NetMulticast|Private // @ game+0x3d90820
	void Multicast_RemoveFishFromLine() // Function Athena.FishingRod.Multicast_RemoveFishFromLine // Final|Net|Native|Event|NetMulticast|Private // @ game+0x3d90800
	{
		static auto fn = UObject::FindObject<UFunction>("Function Athena.FishingRod.Multicast_RemoveFishFromLine");
		ProcessEvent(this, fn, nullptr);
	}
	void Multicast_FishEscaped(); // Function Athena.FishingRod.Multicast_FishEscaped // Final|Net|NetReliableNative|Event|NetMulticast|Private // @ game+0x3d907e0
	void Multicast_BringInACatch(bool IsComedyItem);// Function Athena.FishingRod.Multicast_BringInACatch // Final|Net|NetReliableNative|Event|NetMulticast|Private // @ game+0x3d90750
};

enum class EFishingRodServerState : uint8_t {
	NotBeingUsed,
	PreparingToCast,
	VerifyingCastLocation,
	Casting,
	DelayBeforeSpawningFish,
	RequestFishSpawnWhenPossible,
	WaitingForAsyncLoadToFinish,
	WaitingForFishToBite,
	FishMovingInToBite,
	FishOnRodAndWaitingForPlayerInput,
	FishMovingToMinimumDistanceFromPlayer,
	FishingMiniGameUnderway,
	FishCaught,
	ReelingInAComedyItem,
	ComedyItemCaught,
	EFishingRodServerState_MAX,
};

struct UScriptStruct : UStruct {
	char UnknownData_88[0x98]; // 0x88(0x10)
};

struct FSerialisedRpc
{
	unsigned char                                      UnknownData00[0x18];                                      // 0x0000(0x0018) MISSED OFFSET
	class UScriptStruct* ContentsType;                                             // 0x0018(0x0008) (ZeroConstructor, IsPlainOldData)
};

struct UBoxedRpcDispatcherComponent{
	char UnknownData_C8[0xD0]; // 0xc8(0x08)

	void Server_SendRpc(struct FSerialisedRpc Event); // Function AthenaEngine.BoxedRpcDispatcherComponent.Server_SendRpc // Net|NetReliableNative|Event|Protected|NetServer|NetValidate // @ game+0x3176dc0
	void NetMulticastExcludeServer_SendRpc(struct FSerialisedRpc Event); // Function AthenaEngine.BoxedRpcDispatcherComponent.NetMulticastExcludeServer_SendRpc // Net|NetReliableNative|Event|NetMulticast|Protected // @ game+0x3176c90
	void Client_SendRpc(struct FSerialisedRpc Event); // Function AthenaEngine.BoxedRpcDispatcherComponent.Client_SendRpc // Net|NetReliableNative|Event|Protected|NetClient // @ game+0x31769a0
};

struct FBoxedRpc {
	char UnknownData_0[0x8]; // 0x00(0x08)
	struct UScriptStruct* Type; // 0x08(0x08)
};

struct FThrowGrenadeRpc : FBoxedRpc {
	char pad[0x10];
	struct FVector RelativeLocalThrowLocation; // 0x10(0x0c)
	struct FRotator LocalLaunchAngle; // 0x1c(0x0c)
	float LocalLaunchSpeed; // 0x28(0x04)
	struct FVector LocalWielderVelocity; // 0x2c(0x0c)
};

struct ALightingController {
	char pad[0x7a8];
	struct UExponentialHeightFogComponent* Fog; // 0x7a8(0x08)
	struct UExponentialHeightFogComponent* UnderwaterFog; // 0x7b0(0x08)
	struct UPostProcessComponent* GlobalPostProcess; // 0x7b8(0x08)
	struct UDirectionalLightComponent* RainLight; // 0x7c0(0x08)
	struct UStaticMeshComponent* Moon; // 0x7c8(0x08)
	struct USkyLightComponent* SkyLight; // 0x7d0(0x08)
	float DebugTimeOfDay; // 0x7d8(0x04)
	float DebugRain; // 0x7dc(0x04)
	float DebugMurk; // 0x7e0(0x04)
	int32_t DebugDay; // 0x7e4(0x04)
	char IsDebugFixedTimeOfDay : 1; // 0x7e8(0x01)
	char ShowDebugSunHeightInfo : 1; // 0x7e8(0x01)
	char ShowDebugLightingZoneInfo : 1; // 0x7e8(0x01)
	char ShowDebugUnderwater : 1; // 0x7e8(0x01)
	char UnknownData_7E8_4 : 4; // 0x7e8(0x01)
	char UnknownData_7E9[0x27]; // 0x7e9(0x27)
	char pad2[0x480];
	//struct FLightingControllerLightingVars LightingVars; // 0x810(0x460)
	//struct FLightingControllerMaterialInstances MaterialInstances; // 0xc70(0x20)
	struct TArray<struct AActor*> ReflectionProbes; // 0xc90(0x10)
	char UnknownData_CA0[0x20]; // 0xca0(0x20)
	struct TArray<struct FWaterModifierZoneParametersAndLocation> MurkZones; // 0xcc0(0x10)
	char UnknownData_CD0[0xa8]; // 0xcd0(0xa8)
	struct UCurveFloat* EndOfWorldLightingZoneWeightCurve; // 0xd78(0x08)
	char UnknownData_D80[0xf0]; // 0xd80(0xf0)
};

struct FStringAssetReference {
	struct FString AssetLongPathname; // 0x00(0x10)
};

#ifdef _MSC_VER
#pragma pack(pop)
#endif