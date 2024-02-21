#include "cheat.h"
#include <filesystem>
#include <imgui/imgui_impl_dx11.h>
#include <imgui/imgui_internal.h>
#include <imgui/imgui_impl_win32.h>
#include <HookLib/HookLib.h>
#include "font.h"
#include "iconcpp.h"
#include "icons.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <tchar.h>
#include <fmt-8.0.1/include/fmt/core.h>
#include <fmt-8.0.1/include/fmt/printf.h>
#include <fmt-8.0.1/include/fmt/format.h>
#include <fmt-8.0.1/include/fmt/format-inl.h>
#include <fmt-8.0.1/src/format.cc>
#include "imgui_helper.h"


std::string getShortName(std::string name)
{
    if (name.find("cannon_ball") != std::string::npos)
        return "Cannon Ball";
    if (name.find("cannonball_chain_shot") != std::string::npos)
        return "Chainshot";
    if (name.find("cannonball_Grenade") != std::string::npos)
        return "Blunderbomb";
    if (name.find("cannonball_cur_fire") != std::string::npos)
        return "Firebomb";
    if (name.find("cannonball_cur") != std::string::npos)
        return "Cursed Cannon Ball";

    if (name.find("repair_wood") != std::string::npos)
        return "Wood";

    if (name.find("PomegranateFresh") != std::string::npos)
        return "Pomegranate";
    if (name.find("CoconutFresh") != std::string::npos)
        return "Coconut";
    if (name.find("BananaFresh") != std::string::npos)
        return "Banana";
    if (name.find("PineappleFresh") != std::string::npos)
        return "Pineapple";
    if (name.find("MangoFresh") != std::string::npos)
        return "Mango";

    if (name.find("GrubsFresh") != std::string::npos)
        return "Grubs";
    if (name.find("LeechesFresh") != std::string::npos)
        return "Leeches";
    if (name.find("EarthwormsFresh") != std::string::npos)
        return "Earthworms";

    if (name.find("fireworks_flare") != std::string::npos)
        return "Flare";
    if (name.find("fireworks_rocket") != std::string::npos)
        return "Fireworks S";
    if (name.find("fireworks_cake") != std::string::npos)
        return "Fireworks M";
    if (name.find("fireworks_living") != std::string::npos)
        return "Fireworks L";

    if (name.find("MapInABarrel") != std::string::npos)
        return "Scroll";

    if (name.find("hola") != std::string::npos)
        return "Hola";
    if (name.find("hola") != std::string::npos)
        return "Hola";
    if (name.find("hola") != std::string::npos)
        return "Hola";
    if (name.find("hola") != std::string::npos)
        return "Hola";
    if (name.find("hola") != std::string::npos)
        return "Hola";
    if (name.find("hola") != std::string::npos)
        return "Hola";
    return name;
}

int getMapNameCode(char* name)
{
    if (strstr(name, "wsp_resource_island_02_e") != NULL) // Barnacle Cay
    {
        return 1;
    }
    if (strstr(name, "wld_resource_island_01_b") != NULL) // Black Sand Atoll
    {
        return 2;
    }
    if (strstr(name, "wld_resource_island_02_b") != NULL) // Black Water Enclave
    {
        return 3;
    }
    if (strstr(name, "wld_resource_island_01_d") != NULL) // Blind Man's Lagoon
    {
        return 4;
    }
    if (strstr(name, "wsp_resource_island_01_f") != NULL) // Booty Isle
    {
        return 5;
    }
    if (strstr(name, "bsp_resource_island_01_a") != NULL) // Boulder Cay
    {
        return 6;
    }
    if (strstr(name, "dvr_resource_island_01_h") != NULL) // Brimstone Rock
    {
        return 7;
    }
    if (strstr(name, "wsp_resource_island_01_c") != NULL) // Castaway Isle
    {
        return 8;
    }
    if (strstr(name, "wsp_resource_island_01_a") != NULL) // Chicken Isle
    {
        return 9;
    }
    if (strstr(name, "dvr_resource_island_01_c") != NULL) // Cinder Islet
    {
        return 10;
    }
    if (strstr(name, "dvr_resource_island_01_b") != NULL) // Cursewater Shores
    {
        return 11;
    }
    if (strstr(name, "wsp_resource_island_01_e") != NULL) // Cutlass Cay
    {
        return 12;
    }
    if (strstr(name, "dvr_resource_island_01_g") != NULL) // Flame's End
    {
        return 13;
    }
    if (strstr(name, "wsp_resource_island_01_b") != NULL) // Fools Lagoon
    {
        return 14;
    }
    if (strstr(name, "dvr_resource_island_01_e") != NULL) // Glowstone Cay
    {
        return 15;
    }
    if (strstr(name, "wld_resource_island_02_c") != NULL) // Isle of Last Words
    {
        return 16;
    }
    if (strstr(name, "bsp_resource_island_02_f") != NULL) // Lagoon of Whispers
    {
        return 17;
    }
    if (strstr(name, "wld_resource_island_01_k") != NULL) // Liar's Backbone
    {
        return 18;
    }
    if (strstr(name, "bsp_resource_island_02_c") != NULL) // Lonely Isle
    {
        return 19;
    }
    if (strstr(name, "wsp_resource_island_02_a") != NULL) // Lookout Point
    {
        return 20;
    }
    if (strstr(name, "dvr_resource_island_01_i") != NULL) // Magma's Tide
    {
        return 21;
    }
    if (strstr(name, "wsp_resource_island_02_f") != NULL) // Mutineer Rock
    {
        return 22;
    }
    if (strstr(name, "wsp_resource_island_01_g") != NULL) // Old Salts Atoll
    {
        return 23;
    }
    if (strstr(name, "wsp_resource_island_01_d") != NULL) // Paradise Spring
    {
        return 24;
    }
    if (strstr(name, "bsp_resource_island_01_i") != NULL) // Picaroon Palms
    {
        return 25;
    }
    if (strstr(name, "wld_resource_island_01_c") != NULL) // Plunderer's Plight
    {
        return 26;
    }
    if (strstr(name, "bsp_resource_island_02_d") != NULL) // Rapier Cay
    {
        return 27;
    }
    if (strstr(name, "dvr_resource_island_01_f") != NULL) // Roaring Sands
    {
        return 28;
    }
    if (strstr(name, "bsp_resource_island_02_a") != NULL) // Rum Runner Isle
    {
        return 29;
    }
    if (strstr(name, "bsp_resource_island_01_b") != NULL) // Salty Sands
    {
        return 30;
    }
    if (strstr(name, "bsp_resource_island_02_b") != NULL) // Sandy Shallows
    {
        return 31;
    }
    if (strstr(name, "dvr_resource_island_01_a") != NULL) // Schored Pass
    {
        return 32;
    }
    if (strstr(name, "wld_resource_island_01_j") != NULL) // Scurvy Isley
    {
        return 33;
    }
    if (strstr(name, "bsp_resource_island_02_e") != NULL) // Sea Dog's Rest
    {
        return 34;
    }
    if (strstr(name, "wld_resource_island_01_h") != NULL) // Shark Tooth Key
    {
        return 35;
    }
    if (strstr(name, "wld_resource_island_02_e") != NULL) // Shiver Retreat
    {
        return 36;
    }
    if (strstr(name, "dvr_resource_island_01_d") != NULL) // The Forsaken Brink
    {
        return 37;
    }
    if (strstr(name, "wld_feature_tribute_peak") != NULL) // Tribute Peak
    {
        return 38;
    }
    if (strstr(name, "wld_resource_island_02_d") != NULL) // Tri-Rock Isle
    {
        return 39;
    }
    if (strstr(name, "bsp_resource_island_01_e") != NULL) // Twin Groves
    {
        return 40;
    }
    if (strstr(name, "dvr_feature_island_01_e") != NULL) // Ashen Reaches
    {
        return 41;
    }
    if (strstr(name, "bsp_feature_crescent_cove") != NULL) // Cannon Cove
    {
        return 42;
    }
    if (strstr(name, "bsp_feature_crescent_island") != NULL) // Crescent Isle
    {
        return 43;
    }
    if (strstr(name, "wsp_feature_crooks_hollow") != NULL) // Crook's Hollow
    {
        return 44;
    }
    if (strstr(name, "wsp_feature_devils_ridge") != NULL) // Devil's Ridge
    {
        return 45;
    }
    if (strstr(name, "wsp_feature_discovery_ridge") != NULL) // Discovery Ridge
    {
        return 46;
    }
    if (strstr(name, "dvr_feature_island_01_a") != NULL) // Fetcher's Rest
    {
        return 47;
    }
    if (strstr(name, "dvr_feature_island_01_b") != NULL) // Flintlock Peninsula
    {
        return 48;
    }
    if (strstr(name, "wld_feature_dragons_breath") != NULL) // Kraken's Fall
    {
        return 49;
    }
    if (strstr(name, "bsp_feature_lone_cove") != NULL) // Lone Cove
    {
        return 50;
    }
    if (strstr(name, "wld_feature_arches") != NULL) // Marauder's Arch
    {
        return 51;
    }
    if (strstr(name, "bsp_feature_mermaids_hideaway") != NULL) // Mermaid's Hideaway
    {
        return 52;
    }
    if (strstr(name, "wld_feature_old_faithful") != NULL) // Old Faithful Isle
    {
        return 53;
    }
    if (strstr(name, "wsp_feature_plunder_valley") != NULL) // Plunder Valley
    {
        return 54;
    }
    if (strstr(name, "dvr_feature_island_01_c") != NULL) // Ruby's Fall
    {
        return 55;
    }
    if (strstr(name, "bsp_feature_sailors_bounty") != NULL) // Sailor's Bounty
    {
        return 56;
    }
    if (strstr(name, "wsp_feature_sharkbait_cove") != NULL) // Shark Bait Cove
    {
        return 57;
    }
    if (strstr(name, "wld_feature_shipwreck_bay") != NULL) // Shipwreck Bay
    {
        return 58;
    }
    if (strstr(name, "bsp_feature_smugglers_bay") != NULL) // Smugglers' Bay
    {
        return 59;
    }
    if (strstr(name, "wsp_feature_snake_island") != NULL) // Snake Island
    {
        return 60;
    }
    if (strstr(name, "wld_feature_three_peaks") != NULL) // The Crooked Masts
    {
        return 61;
    }
    if (strstr(name, "dvr_feature_island_01_d") != NULL) // The Devil's Thirst
    {
        return 62;
    }
    if (strstr(name, "wld_feature_cavern_isle") != NULL) // The Sunken Grove
    {
        return 63;
    }
    if (strstr(name, "wsp_feature_thieves_haven") != NULL) // Thieves' Haven
    {
        return 64;
    }
    if (strstr(name, "bsp_feature_wanderers_archipelago") != NULL) // Wanderers Refuge
    {
        return 65;
    }
    return 0;
}

std::string getIslandNameByCode(int code)
{
    switch (code)
    {
    case 1: return "BarnaCle Cay";
    case 2: return "Black Sand Atoll";
    case 3: return "Black Water Enclave";
    case 4: return "Blind Man's Lagoon";
    case 5: return "Booty Isle";
    case 6: return "Boulder Cay";
    case 7: return "Brimstone Rock";
    case 8: return "Castaway Isle";
    case 9: return "Chicken Isle";
    case 10:return "Cinder Islet";
    case 11:return "Cursewater Shores";
    case 12:return "Cutlass Cay";
    case 13:return "Flame's End";
    case 14:return "Fools Lagoon";
    case 15:return "Glowstone Cay";
    case 16:return "Isle of Last Words";
    case 17:return "Lagoon of Whispers";
    case 18:return "Liar's Backbone";
    case 19:return "Lonely Isle";
    case 20:return "Lookout Point";
    case 21:return "Magma's Tide";
    case 22:return "Mutineer Rock";
    case 23:return "Old Salts Atoll";
    case 24:return "Paradise Spring";
    case 25:return "Picaroon Palms";
    case 26:return "Plunderer's Plight";
    case 27:return "Rapier Cay";
    case 28:return "Roaring Sands";
    case 29:return "Rum Runner Isle";
    case 30:return "Salty Sands";
    case 31:return "Sandy Shallows";
    case 32:return "Schored Pass";
    case 33:return "Scurvy Isley";
    case 34:return "Sea Dog's Rest";
    case 35:return "Shark Tooth Key";
    case 36:return "Shiver Retreat";
    case 37:return "The Forsaken Brink";
    case 38:return "Tribute Peak";
    case 39:return "Tri-Rock Isle";
    case 40:return "Twin Groves";
    case 41:return "Ashen Reaches";
    case 42:return "Cannon Cove";
    case 43:return "Crescent Isle";
    case 44:return "Crook's Hollow";
    case 45:return "Devil's Ridge";
    case 46:return "Discovery Ridge";
    case 47:return "Fetcher's Rest";
    case 48:return "Flintlock Peninsula";
    case 49:return "Kraken's Fall";
    case 50:return "Lone Cove";
    case 51:return "Marauder's Arch";
    case 52:return "Mermaid's Hideaway";
    case 53:return "Old Faithful Isle";
    case 54:return "Plunder Valley";
    case 55:return "Ruby's Fall";
    case 56:return "Sailor's Bounty";
    case 57:return "Shark Bait Cove";
    case 58:return "Shipwreck Bay";
    case 59:return "Smugglers' Bay";
    case 60:return "Snake Island";
    case 61:return "The Crooked Masts";
    case 62:return "The Devil's Thirst";
    case 63:return "The Sunken Grove";
    case 64:return "Thieves' Haven";
    case 65:return "Wanderers Refuge";
    default:return "No Island Data";
    }
}



uintptr_t milliseconds_now() {
    static LARGE_INTEGER s_frequency;
    static BOOL s_use_qpc = QueryPerformanceFrequency(&s_frequency);
    if (s_use_qpc) {
        LARGE_INTEGER now;
        QueryPerformanceCounter(&now);
        return (1000LL * now.QuadPart) / s_frequency.QuadPart;
    }
    else {
        return GetTickCount64();
    }
}

float CachedFramerates[1000];

float MaxArr(float arr[], int n)
{
    int i;
    float max = arr[0];
    for (i = 1; i < n; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}

float MinArr(float arr[], int n)
{
    int i;
    float min = arr[0];
    for (i = 1; i < n; i++)
    {
        if (arr[i] < min)
        {
            min = arr[i];
        }
    }
    return min;
}

int randomnumber = 0; // Number Holder

void fn()
{
    int min = -1000; // Back of the Target
    int max = +2000; // Front of the Target
    int randomNum = rand() % max + (min); // Random Number Gen
    randomnumber = randomNum; // Changes the value of randomnumber to the value of randomNum
    return; // disables the function because you should call it inside of a loop
}

FVector pickHoleToAim(AHullDamage* damage, const FVector& localLoc)
{
    FVector fLocation = { 0.f, 0.f, 9999.f };
    FVector location = FVector();
    float currentDist = 55000.f;
    const auto holes = damage->DamageZones;
    for (auto h = 0u; h < holes.Count; h++)
    {
        auto const hole = holes[h];
        if (hole->DamageLevel < 3)
        {
            location = FVector(reinterpret_cast<ACharacter*>(hole)->K2_GetActorLocation());
            float dist = localLoc.DistTo(location);
            if (dist <= currentDist)
            {
                currentDist = dist;
                fLocation = location;
            }
        }
    }
    return fLocation;
}


#define STEAM
//#define LOGFILE
//#define UWPDEBUG


namespace fs = std::filesystem;

void Cheat::Hacks::OnWeaponFiredHook(UINT64 arg1, UINT64 arg2)
{
    Logger::Log("arg1: %p, arg2: %p\n", arg1, arg2);
    auto& cameraCache = cache.localCamera->CameraCache.POV;
    auto prev = cameraCache.Rotation;
    cameraCache.Rotation = { -cameraCache.Rotation.Pitch, -cameraCache.Rotation.Yaw, 0.f };
    return OnWeaponFiredOriginal(arg1, arg2);

}

int32_t targetFunctionIndex = -1;

void Cheat::Hacks::ProcessEventHook(void* obj, UFunction* function, void* parms)
{
    //Logger::Log("ProcessEvent: %s with id %d\n", function->GetFullName().c_str(), function->Name.ComparisonIndex);

    if (targetFunctionIndex == -1)
        if (function->GetFullName().compare("Function AthenaEngine.BoxedRpcDispatcherComponent.Server_SendRpc") == 0)
            targetFunctionIndex = function->InternalIndex;
    
    if (function->InternalIndex == targetFunctionIndex)
    {
        auto result = (FSerialisedRpc*)parms;

        if (result->ContentsType->GetFullName().find("ScriptStruct Athena.TakeItemFromContainerRPC") != std::string::npos)
        {
            Logger::Log("asd\n");
           // return;
        }
        if (result->ContentsType->GetFullName().find("ScriptStruct Athena.ProjectileWeaponFireInaccuracySeedMismatchTelemetryEvent") != std::string::npos)
        {
            Logger::Log("asd\n");
            //return;
        }
    }

    ProcessEventOriginal(obj, function, parms);
}


void Cheat::Hacks::Init()
{
    //{
    //    UFunction* fn = UObject::FindObject<UFunction>("Function Athena.AthenaCharacterMovementComponent.SetMovementMode");
    //    if (fn) {
    //        Logger::Log("SetMovementMode: %p\n", fn->Func);
    //        /* if (SetHook(fn->Func, CanFireHook, reinterpret_cast<void**>(&CanFireOriginal)))
    //         {

    //         }*/
    //    }
    //}

    //UFunction* fn;

    //fn = UObject::FindObject<UFunction>("Function Athena.AthenaCharacterMovementComponent.SetMovementMode");    
    //Logger::Log("SetMovementMode: 0x%llX\n", fn->Func);

    //fn = UObject::FindObject<UFunction>("Function Athena.AthenaPlayerCharacter.OnWieldedItem");
    //Logger::Log("OnWieldedItem: 0x%llX\n", fn->Func);
    //
    /*fn = UObject::FindObject<UFunction>("Function Athena.ProjectileWeapon.OnWeaponFired");
    Logger::Log("OnWeaponFired: 0x%llX\n", fn->Func);
    SetHook((void*)0x7FF727EB7150, OnWeaponFiredHook, reinterpret_cast<void**>(&OnWeaponFiredOriginal));*/
    //
    //fn = UObject::FindObject<UFunction>("Function Engine.PlayerController.AddPitchInput");
    //Logger::Log("AddPitchInput: 0x%llX\n", fn->Func);


    /*UClass* klass = UObject::FindObject<UClass>("Class Athena.ProjectileWeapon");
    Logger::Log("Class Athena.ProjectileWeapon: 0x%llX\n", klass);
    void* vtable_raw = klass->Vtable;
    Logger::Log("Vtable: 0x%llX\n", vtable_raw);
    UINT64* vtable_uint64 = (UINT64*)vtable_raw;
    Logger::Log("ProcessEvent: 0x%llX\n", vtable_uint64[55]);
    SetHook((void*)0x7FF728508410, ProcessEventHook, reinterpret_cast<void**>(&ProcessEventOriginal));
    */

}

inline void Cheat::Hacks::Remove()
{
    //RemoveHook(CanFireOriginal);
   //RemoveHook(OnWeaponFiredOriginal);
   // RemoveHook(ProcessEventOriginal);
}

void Cheat::Renderer::Drawing::RenderText(const char* text, const FVector2D& pos, const ImVec4& color, const bool outlined = false, const bool centered = true)
{
    if (!text) return;
    auto ImScreen = *reinterpret_cast<const ImVec2*>(&pos);
    if (centered)
    {
        auto size = ImGui::CalcTextSize(text);
        ImScreen.x -= size.x * 0.5f;
        ImScreen.y -= size.y;
    }
    auto window = ImGui::GetCurrentWindow();

    // That "outline" doubles text drawn count so heaviest part of code becomes twice as slow while it's absolutely unnecessary

    if (cfg.visuals.bEnable && cfg.visuals.textoutlines)
    {
        window->DrawList->AddText(nullptr, 0.f, ImVec2(ImScreen.x - 1.f, ImScreen.y + 1.f), ImGui::GetColorU32(IM_COL32_BLACK), text);
    }
    //*/
    window->DrawList->AddText(nullptr, 0.f, ImScreen, ImGui::GetColorU32(color), text);
}

void Cheat::Renderer::renderPanel() {
    /*ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0, 0, 0, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 1.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0, 0, 0, 255));
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(40, 40, 40, 255));
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(255, 20, 147, 255));
    ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(70, 70, 70, 255));*/
    // ImGui::PushStyleColor(ImGuiCol_TabActive, ImVec4(255, 20, 147, 255));
    Cheat::Renderer::renderLogo();
    ImGui::Spacing();
    Cheat::Renderer::renderTabs();
    // ImGui::PopStyleColor();
    Cheat::Renderer::renderUser();
    //ImGui::PopStyleColor();
    //ImGui::PopStyleVar(6);
    //ImGui::PopStyleColor();
}

void Cheat::Renderer::Drawing::Render2DBox(const FVector2D& top, const FVector2D& bottom, const float height, const float width, const ImVec4& color)
{
    ImGui::GetCurrentWindow()->DrawList->AddRect({ top.X - width * 0.5f, top.Y }, { top.X + width * 0.5f, bottom.Y }, ImGui::GetColorU32(color), 0.f, 15, 1.5f);
}

bool Cheat::Renderer::Drawing::Render3DBox(AController* const controller, const FVector& origin, const FVector& extent, const FRotator& rotation, const ImVec4& color)
{
    FVector vertex[2][4];
    vertex[0][0] = { -extent.X, -extent.Y,  -extent.Z };
    vertex[0][1] = { extent.X, -extent.Y,  -extent.Z };
    vertex[0][2] = { extent.X, extent.Y,  -extent.Z };
    vertex[0][3] = { -extent.X, extent.Y, -extent.Z };

    vertex[1][0] = { -extent.X, -extent.Y, extent.Z };
    vertex[1][1] = { extent.X, -extent.Y, extent.Z };
    vertex[1][2] = { extent.X, extent.Y, extent.Z };
    vertex[1][3] = { -extent.X, extent.Y, extent.Z };

    FVector2D screen[2][4];
    FTransform const Transform(rotation);
    for (auto k = 0; k < 2; k++)
    {
        for (auto i = 0; i < 4; i++)
        {
            auto& vec = vertex[k][i];
            vec = Transform.TransformPosition(vec) + origin;
            if (!controller->ProjectWorldLocationToScreen(vec, screen[k][i])) return false;
        }

    }

    auto ImScreen = reinterpret_cast<ImVec2(&)[2][4]>(screen);

    auto window = ImGui::GetCurrentWindow();
    for (auto i = 0; i < 4; i++)
    {
        window->DrawList->AddLine(ImScreen[0][i], ImScreen[0][(i + 1) % 4], ImGui::GetColorU32(color));
        window->DrawList->AddLine(ImScreen[1][i], ImScreen[1][(i + 1) % 4], ImGui::GetColorU32(color));
        window->DrawList->AddLine(ImScreen[0][i], ImScreen[1][i], ImGui::GetColorU32(color));
    }

    return true;
}

bool Cheat::Renderer::Drawing::RenderSkeleton(AController* const controller, USkeletalMeshComponent* const mesh, const FMatrix& comp2world, const std::pair<const BYTE*, const BYTE>* skeleton, int size, const ImVec4& color)
{

    for (auto s = 0; s < size; s++)
    {
        auto& bone = skeleton[s];
        FVector2D previousBone;
        for (auto i = 0; i < skeleton[s].second; i++)
        {
            FVector loc;
            int res = mesh->GetBone(bone.first[i], comp2world, loc);
            if (res == 0)
                return false;

            FVector2D screen;
            if (!controller->ProjectWorldLocationToScreen(loc, screen)) return false;

            if (previousBone.Size() != 0) {
                auto ImScreen1 = *reinterpret_cast<ImVec2*>(&previousBone);
                auto ImScreen2 = *reinterpret_cast<ImVec2*>(&screen);
                ImGui::GetCurrentWindow()->DrawList->AddLine(ImScreen1, ImScreen2, ImGui::GetColorU32(color), 4.f);

                //std::string bone_num = std::to_string(bone.first[i]);
                //ImGui::GetCurrentWindow()->DrawList->AddText(ImScreen2, 0xAAAAAAAA, bone_num.c_str());

            }
            previousBone = screen;
        }
    }

    return true;
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI Cheat::Renderer::WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam) && bIsOpen) return true;
    if (bIsOpen)
    {
        ImGuiMouseCursor imgui_cursor = ImGui::GetMouseCursor();
        LPTSTR win32_cursor = IDC_ARROW;
        switch (imgui_cursor)
        {
        case ImGuiMouseCursor_Arrow:        win32_cursor = IDC_ARROW; break;
        case ImGuiMouseCursor_TextInput:    win32_cursor = IDC_IBEAM; break;
        case ImGuiMouseCursor_ResizeAll:    win32_cursor = IDC_SIZEALL; break;
        case ImGuiMouseCursor_ResizeEW:     win32_cursor = IDC_SIZEWE; break;
        case ImGuiMouseCursor_ResizeNS:     win32_cursor = IDC_SIZENS; break;
        case ImGuiMouseCursor_ResizeNESW:   win32_cursor = IDC_SIZENESW; break;
        case ImGuiMouseCursor_ResizeNWSE:   win32_cursor = IDC_SIZENWSE; break;
        case ImGuiMouseCursor_Hand:         win32_cursor = IDC_HAND; break;
        case ImGuiMouseCursor_NotAllowed:   win32_cursor = IDC_NO; break;
        }
        SetCursorOriginal(LoadCursorA(nullptr, win32_cursor));

    }
    if (!bIsOpen || uMsg == WM_KEYUP) return CallWindowProcA(WndProcOriginal, hwnd, uMsg, wParam, lParam);
    return DefWindowProcA(hwnd, uMsg, wParam, lParam);
}

HCURSOR WINAPI Cheat::Renderer::SetCursorHook(HCURSOR hCursor)
{
    if (bIsOpen) return 0;
    return SetCursorOriginal(hCursor);
}

BOOL WINAPI Cheat::Renderer::SetCursorPosHook(int X, int Y)
{
    if (bIsOpen) return FALSE;
    return SetCursorPosOriginal(X, Y);
}

void Cheat::Renderer::HookInput()
{
    RemoveInput();
    WndProcOriginal = reinterpret_cast<WNDPROC>(SetWindowLongPtrA(gameWindow, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WndProc)));
    Logger::Log("WndProcOriginal = %p\n", WndProcOriginal);
}

void Cheat::Renderer::RemoveInput()
{
    if (WndProcOriginal)
    {
        SetWindowLongPtrA(gameWindow, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WndProcOriginal));
        WndProcOriginal = nullptr;
    }
}




bool raytrace(UWorld* world, const struct FVector& start, const struct FVector& end, struct FHitResult* hit)
{
    if (world == nullptr || world->PersistentLevel == nullptr) //some checks
        return false;

    return UKismetMathLibrary::LineTraceSingle_NEW((UObject*)world, start, end, ETraceTypeQuery::TraceTypeQuery4, true, TArray<AActor*>() /*actors to ignore*/, EDrawDebugTrace::EDrawDebugTrace__None, true, hit); //TraceTypeQuery4 equals the visibility channel
}
    
/*bool GetProjectilePath(std::vector<FVector>& v, FVector& Vel, FVector& Pos, float Gravity, int count, UWorld* world)
{
    float interval = 0.033f;
    for (unsigned int i = 0; i < count; ++i)
    {
        v.push_back(Pos);
        FVector move;
        move.X = (Vel.X) * interval;
        move.Y = (Vel.Y) * interval;
        float newZ = Vel.Z - (Gravity * interval);
        move.Z = ((Vel.Z + newZ) * 0.5f) * interval;
        Vel.Z = newZ;
        FVector nextPos = Pos + move;

        bool res = true;
        {
            FHitResult hit_result;
            res = !raytrace(world, Pos, nextPos, &hit_result);
        }

        Pos = nextPos;
        if (!res) return true;
    }
    return false;
}*/

bool GetProjectilePath(std::vector<FVector>& v, FVector& Vel, FVector& Pos, float Gravity, int count, UWorld* world)
{
    float interval = 0.033f;

    for (unsigned int i = 0; i < count; ++i) //i<250
    {
        v.push_back(Pos);
        FVector move;
        move.X = (Vel.X) * interval;
        move.Y = (Vel.Y) * interval;
        float newZ = Vel.Z - (Gravity * interval);
        move.Z = ((Vel.Z + newZ) * 0.5f) * interval;
        Vel.Z = newZ;
        FVector nextPos = Pos + move;


        bool res = true;
        {
            FHitResult hit_result;
            res = !raytrace(world, Pos, nextPos, &hit_result);
        }


        Pos = nextPos;
        if (!res) return true; // we hit something
    }

    return false;
}


#include <complex>
// Shamelessly stolen from https://github.com/sidneycadot/quartic/blob/master/solve-quartic.cc
void SolveQuartic(const std::complex<float> coefficients[5], std::complex<float> roots[4]) {
    const std::complex<float> a = coefficients[4];
    const std::complex<float> b = coefficients[3] / a;
    const std::complex<float> c = coefficients[2] / a;
    const std::complex<float> d = coefficients[1] / a;
    const std::complex<float> e = coefficients[0] / a;

    const std::complex<float> Q1 = c * c - 3.f * b * d + 12.f * e;
    const std::complex<float> Q2 = 2.f * c * c * c - 9.f * b * c * d + 27.f * d * d + 27.f * b * b * e - 72.f * c * e;
    const std::complex<float> Q3 = 8.f * b * c - 16.f * d - 2.f * b * b * b;
    const std::complex<float> Q4 = 3.f * b * b - 8.f * c;

    const std::complex<float> Q5 = std::pow(Q2 / 2.f + std::sqrt(Q2 * Q2 / 4.f - Q1 * Q1 * Q1), 1.f / 3.f);
    const std::complex<float> Q6 = (Q1 / Q5 + Q5) / 3.f;
    const std::complex<float> Q7 = 2.f * std::sqrt(Q4 / 12.f + Q6);

    roots[0] = (-b - Q7 - std::sqrt(4.f * Q4 / 6.f - 4.f * Q6 - Q3 / Q7)) / 4.f;
    roots[1] = (-b - Q7 + std::sqrt(4.f * Q4 / 6.f - 4.f * Q6 - Q3 / Q7)) / 4.f;
    roots[2] = (-b + Q7 - std::sqrt(4.f * Q4 / 6.f - 4.f * Q6 + Q3 / Q7)) / 4.f;
    roots[3] = (-b + Q7 + std::sqrt(4.f * Q4 / 6.f - 4.f * Q6 + Q3 / Q7)) / 4.f;
}

#define _USE_MATH_DEFINES
#include <math.h>

FRotator ToFRotator(FVector vec)
{
    FRotator rot;
    float RADPI = (float)(180 / M_PI);
    rot.Yaw = (float)(atan2f(vec.Y, vec.X) * RADPI);
    rot.Pitch = (float)atan2f(vec.Z, sqrt((vec.X * vec.X) + (vec.Y * vec.Y))) * RADPI;
    rot.Roll = 0;

    return rot;
}

int AimAtStaticTarget(const FVector& oTargetPos, float fProjectileSpeed, float fProjectileGravityScalar, const FVector& oSourcePos, FRotator& oOutLow, FRotator& oOutHigh) {
    const float gravity = 981.f * fProjectileGravityScalar;
    const FVector diff(oTargetPos - oSourcePos);
    const FVector oDiffXY(diff.X, diff.Y, 0.0f);
    const float fGroundDist = oDiffXY.Size();

    const float s2 = fProjectileSpeed * fProjectileSpeed;
    const float s4 = s2 * s2;
    const float y = diff.Z;
    const float x = fGroundDist;
    const float gx = gravity * x;

    float root = s4 - (gravity * ((gx * x) + (2 * y * s2)));

    if (root < 0)
        return 0;

    root = std::sqrtf(root);

    const float fLowAngle = std::atan2f((s2 - root), gx);
    const float fHighAngle = std::atan2f((s2 + root), gx);

    int nSolutions = fLowAngle != fHighAngle ? 2 : 1;

    const FVector oGroundDir(oDiffXY.unit());

    oOutLow = ToFRotator(oGroundDir * std::cosf(fLowAngle) * fProjectileSpeed + FVector(0.f, 0.f, 1.f) * std::sinf(fLowAngle) * fProjectileSpeed);

    if (nSolutions == 2)
        oOutHigh = ToFRotator(oGroundDir * std::cosf(fHighAngle) * fProjectileSpeed + FVector(0.f, 0.f, 1.f) * std::sinf(fHighAngle) * fProjectileSpeed);

    return nSolutions;
}


#include <limits>
int AimAtMovingTarget(const FVector& oTargetPos, const FVector& oTargetVelocity, float fProjectileSpeed, float fProjectileGravityScalar, const FVector& oSourcePos, const FVector& oSourceVelocity, FRotator& oOutLow, FRotator& oOutHigh) {
    const FVector v(oTargetVelocity - oSourceVelocity);
    const FVector g(0.f, 0.f, -981.f * fProjectileGravityScalar);
    const FVector p(oTargetPos - oSourcePos);

    const float c4 = g | g * 0.25f;
    const float c3 = v | g;
    const float c2 = (p | g) + (v | v) - (fProjectileSpeed * fProjectileSpeed);
    const float c1 = 2.f * (p | v);
    const float c0 = p | p;

    std::complex<float> pOutRoots[4];
    const std::complex<float> pInCoeffs[5] = { c0, c1, c2, c3, c4 };

    SolveQuartic(pInCoeffs, pOutRoots);

    float fBestRoot = FLT_MAX;
    for (int i = 0; i < 4; i++) {
        if (pOutRoots[i].real() > 0.f && std::abs(pOutRoots[i].imag()) < 0.0001f && pOutRoots[i].real() < fBestRoot) {
            fBestRoot = pOutRoots[i].real();
        }
    }

    if (fBestRoot == FLT_MAX)
        return 0;

    const FVector oAimAt = oTargetPos + (v * fBestRoot);

    return AimAtStaticTarget(oAimAt, fProjectileSpeed, fProjectileGravityScalar, oSourcePos, oOutLow, oOutHigh);
}

FVector2D rotate_radar(FVector target_location, FVector source_location, FRotator source_rotation)
{
    const FVector diff_loc = target_location - source_location;

    float yaw = source_rotation.Yaw;
    yaw *= M_PI / 180.f;

    float x_rot = diff_loc.Y * std::cosf(yaw) - diff_loc.X * std::sinf(yaw);
    float y_rot = diff_loc.X * std::cosf(yaw) + diff_loc.Y * std::sinf(yaw);

    return { x_rot, y_rot };
}


HRESULT Cheat::Renderer::PresentHook(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags)
{
    if (!device)
    {
        ID3D11Texture2D* surface = nullptr;
        goto init;
    cleanup:
        Cheat::Remove();
        if (surface) surface->Release();
        return fnPresent(swapChain, syncInterval, flags);
    init:

        if (FAILED(swapChain->GetBuffer(0, __uuidof(surface), reinterpret_cast<PVOID*>(&surface)))) { goto cleanup; };
        Logger::Log("ID3D11Texture2D* surface = %p\n", surface);

        if (FAILED(swapChain->GetDevice(__uuidof(device), reinterpret_cast<PVOID*>(&device)))) goto cleanup;

        Logger::Log("ID3D11Device* device = %p\n", device);

        if (FAILED(device->CreateRenderTargetView(surface, nullptr, &renderTargetView))) goto cleanup;

        Logger::Log("ID3D11RenderTargetView* renderTargetView = %p\n", renderTargetView);

        surface->Release();
        surface = nullptr;

        device->GetImmediateContext(&context);

        Logger::Log("ID3D11DeviceContext* context = %p\n", context);

        ImGui::CreateContext();

        {
            ImGuiIO& io = ImGui::GetIO(); (void)io;
            io.Fonts->Clear();
            static const ImWchar icons_ranges[] = { 0xe000, 0xf8ff, 0 };
            //ImFont* font = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\calibril.ttf", 17);

            ImFontConfig font_cfg;
            font_cfg.FontDataOwnedByAtlas = false;
            font = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\calibril.ttf", 16, &font_cfg);

            ImFontConfig config;
            config.MergeMode = true;
            config.PixelSnapH = true;
            config.FontDataOwnedByAtlas = false;
            //ImFont* font = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\calibril.ttf", 17, &config);
            io.Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 19.0f, &config, icons_ranges);

            ImFontConfig esp_config;
            esp_config.FontDataOwnedByAtlas = false;
            esp_font = io.Fonts->AddFontFromMemoryCompressedTTF((void*)Smallest_compressed_data, Smallest_compressed_size, 14, &esp_config);
            //esp_font = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\smallest_pixel-7.ttf", 16, &esp_config);
            io.Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 19.0f, &config, icons_ranges);

            ImFontConfig title_config;
            title_config.FontDataOwnedByAtlas = false;
            title_font = io.Fonts->AddFontFromMemoryCompressedTTF((void*)Againts_compressed_data, Againts_compressed_size, 32, &esp_config);

            io.Fonts->Build();
        }
#ifdef STEAM
        DXGI_SWAP_CHAIN_DESC desc;
        swapChain->GetDesc(&desc);
        auto& window = desc.OutputWindow;
        gameWindow = window;
#else
        auto window = FindWindowA(NULL, "Sea of Thieves");
        gameWindow = window;
#endif
        Logger::Log("gameWindow = %p\n", window);

        if (!ImGui_ImplWin32_Init(window)) goto cleanup;
        if (!ImGui_ImplDX11_Init(device, context)) goto cleanup;
        if (!ImGui_ImplDX11_CreateDeviceObjects()) goto cleanup;
        Logger::Log("ImGui initialized successfully!\n");

        HookInput();
    }


    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();


    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0));
    ImGui::PushFont(esp_font);

    ImGui::Begin("#1", nullptr, ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoTitleBar);
    auto& io = ImGui::GetIO();
    ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
    ImGui::SetWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y), ImGuiCond_Always);

    auto drawList = ImGui::GetCurrentWindow()->DrawList;
   
    try
    {
        do
        {      
            memset(&cache, 0, sizeof(Cache));
            auto const world = *UWorld::GWorld;

            if (!world) break;
            auto const game = world->OwningGameInstance;
            if (!game) break;
            auto const gameState = world->GameState;
            if (!gameState) break;
            cache.gameState = gameState;
            if (!game->LocalPlayers.Data) break;

            auto const localPlayer = game->LocalPlayers[0];
            if (!localPlayer) break;
            auto const localController = localPlayer->PlayerController;

            if (!localController) break;
            cache.localController = localController;
            auto const camera = localController->PlayerCameraManager;

            if (!camera) break;
            cache.localCamera = camera;
            const auto cameraLoc = camera->GetCameraLocation();
            const auto cameraRot = camera->GetCameraRotation();

            int XMarksMapCount = 1;

            auto const localCharacter = localController->Character;
            if (!localCharacter) break;

            auto const localPlayerCharacter = (AAthenaPlayerCharacter*)localController->K2_GetPawn();
            if (!localPlayerCharacter) break;

            auto const AACharacter = (AAthenaPlayerCharacter*)localCharacter;
            if (!localPlayerCharacter) break;

            const auto levels = world->Levels;
            if (!levels.Data) break;

            const auto localLoc = localCharacter->K2_GetActorLocation();

            bool isWieldedWeapon = false;
            auto item = localCharacter->GetWieldedItem();

            auto const localSword = *reinterpret_cast<AMeleeWeapon**>(&item);       

            if (item)
                isWieldedWeapon = item->isWeapon();


            auto const localWeapon = *reinterpret_cast<AProjectileWeapon**>(&item);

            if (cfg.misc.bEnable && cfg.misc.render.bEnable)
            {
                if (&cfg.misc.render.fpsboost)
                {
                    // NEEDS TO BE CODED
                }
            }

            ACharacter* attachObject = localCharacter->GetAttachParentActor();

            bool isHarpoon = false;

            if (attachObject)
            {
                if (cfg.aim.harpoon.bEnable && attachObject->isHarpoon())
                {
                    isHarpoon = true;
                }
            }

            bool isCannon = false;

            if (attachObject)
            {
                if (cfg.aim.cannon.bEnable && attachObject->isCannon())
                {
                    isCannon = true;
                }
            }

            cache.good = true;

            static struct {
                ACharacter* target = nullptr;
                FVector location;
                FRotator delta;
                float best = FLT_MAX;
                float smoothness = 1.f;
            } aimBest;

            aimBest.target = nullptr;
            aimBest.best = FLT_MAX;

            

            if (isCannon)
            {
                auto cannon = reinterpret_cast<ACannon*>(attachObject);

                if (cannon->LoadedItemInfo)
                {
                    std::wstring loaded_name = cannon->LoadedItemInfo->Desc->Title->wide();
                    if (L"Chainshot" == loaded_name)
                        cfg.aim.cannon.b_chain_shots = true;
                    else
                        cfg.aim.cannon.b_chain_shots = false;
                }

                float gravity_scale = cannon->ProjectileGravityScale;
                if (cfg.aim.cannon.b_chain_shots)
                    gravity_scale = 1.f;

                float gravity = 981.f * gravity_scale;
                float launchspeed = cannon->ProjectileSpeed;

                FRotator angle = { cannon->ServerPitch, cannon->ServerYaw, 0.f };

                FRotator comp_angle = attachObject->K2_GetActorRotation();
                angle.Pitch += comp_angle.Pitch;
                angle.Yaw += comp_angle.Yaw;
                angle.Roll += comp_angle.Roll;

                FVector vForward = UKismetMathLibrary::Conv_RotatorToVector(angle);
                FVector pos = attachObject->K2_GetActorLocation();
                pos.Z += 100;   //1m
                pos = pos + (vForward * 150);   //1,50m

                FVector vel = vForward * launchspeed;
                if (localCharacter->GetCurrentShip())
                    vel = vel + localCharacter->GetCurrentShip()->GetVelocity();

                std::vector<FVector> path;
                int count = 250; //250

                bool hit = GetProjectilePath(path, vel, pos, gravity, count, world);

                FVector2D screen_pos_prev;
                for (int i = 0; i < path.size(); i++)
                {
                    FVector2D screen_pos;
                    bool is_on_screen = localController->ProjectWorldLocationToScreen(path[i], screen_pos);
                    if (is_on_screen) {
                        if (hit && i == path.size() - 1)
                        {
                            drawList->AddCircle({ screen_pos.X, screen_pos.Y }, 7, ImGui::ColorConvertFloat4ToU32(cfg.visuals.players.enemyColorInv), 9, 1);
                        }
                        else if (i >= 1)
                            drawList->AddLine({ screen_pos_prev.X, screen_pos_prev.Y }, { screen_pos.X, screen_pos.Y }, ImGui::ColorConvertFloat4ToU32(cfg.visuals.players.enemyColorVis), 1);

                        screen_pos_prev = screen_pos;
                    }
                }
            }
            
            typedef struct _cannonball_location {
                FVector location;
                int draw_times;
                int drawn;
            } cannonball_location;
            static std::vector<cannonball_location> cannonball_tracers;

            if (!cannonball_tracers.empty())
                for (int i = cannonball_tracers.size() - 1; i >= 0; i--)
                    if (cannonball_tracers.at(i).drawn >= cannonball_tracers.at(i).draw_times)
                        cannonball_tracers.erase(cannonball_tracers.begin() + i);


            FVector2D radar_pos = { 1750.f, 175.f };
            //radar frame

            if (cfg.visuals.bEnable && !localCharacter->IsLoading())
            {
               

                if (cfg.visuals.client.b_cannon_tracers)
                {
                    for (int i = 0; i < cannonball_tracers.size(); i++)
                    {
                        FVector location = cannonball_tracers[i].location;
                        const int dist = localLoc.DistTo(location) * 0.01f;
                        FVector2D screen;
                        if (localController->ProjectWorldLocationToScreen(location, screen) && dist <= 515)
                            drawList->AddCircle({ screen.X - 1, screen.Y - 1 }, 2, ImGui::GetColorU32(cfg.visuals.client.cannon_tracers_color), 6, 1);

                        cannonball_tracers[i].drawn++;
                    }
                }

                if (cfg.visuals.radar.bEnable)
                {
                    //fill
                    drawList->AddCircleFilled({ radar_pos.X, radar_pos.Y }, (cfg.visuals.radar.i_size / 2.f), 0x44000000, 60);

                    //frame
                    drawList->AddCircle({ radar_pos.X, radar_pos.Y }, (cfg.visuals.radar.i_size / 2.f) + 1.f, 0xFF000000, 60, 1.f);

                    //horizontal
                    drawList->AddLine({ radar_pos.X - (cfg.visuals.radar.i_size / 2.f), radar_pos.Y }, { radar_pos.X + (cfg.visuals.radar.i_size / 2.f), radar_pos.Y }, 0xFF000000, 1);

                    //center outline
                    drawList->AddCircleFilled({ radar_pos.X, radar_pos.Y }, 6, 0xFF000000, 15);

                    //dir outline
                    drawList->AddLine({ radar_pos.X, radar_pos.Y }, { radar_pos.X, radar_pos.Y - 26 }, 0xFF000000, 3);

                    //center
                    drawList->AddCircleFilled({ radar_pos.X, radar_pos.Y }, 5, 0xFF00FF00, 15);

                    //dir
                    drawList->AddLine({ radar_pos.X, radar_pos.Y }, { radar_pos.X, radar_pos.Y - 25 }, 0xFF00FF00, 1);
                }

                if (cfg.visuals.client.bCompass)
                {
                    const char* directions[] = { "N", "NE", "E", "SE", "S", "SW", "W", "NW" };
                    int yaw = ((int)cameraRot.Yaw + 450) % 360;
                    int index = int(yaw + 22.5f) % 360 * 0.0222222f;

                    FVector2D pos = { io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.02f };
                    auto col = ImVec4(1.f, 1.f, 1.f, 1.f);
                    Drawing::RenderText(const_cast<char*>(directions[index]), pos, col);
                    char buf[0x30];
                    int len = sprintf(buf, "%d", yaw);
                    pos.Y += 15.f;
                    Drawing::RenderText(buf, pos, col);
                }

                if (cfg.visuals.client.bOxygen && localCharacter->IsInWater())
                {
                    auto drownComp = localCharacter->DrowningComponent;
                    if (!drownComp) break;
                    auto level = drownComp->GetOxygenLevel();
                    auto posX = io.DisplaySize.x * 0.5f;
                    auto posY = io.DisplaySize.y * 0.85f;
                    auto barWidth2 = io.DisplaySize.x * 0.05f;
                    auto barHeight2 = io.DisplaySize.y * 0.0030f;
                    drawList->AddRectFilled({ posX - barWidth2, posY - barHeight2 }, { posX + barWidth2, posY + barHeight2 }, ImGui::GetColorU32(IM_COL32(0, 0, 0, 255)));
                    drawList->AddRectFilled({ posX - barWidth2, posY - barHeight2 }, { posX - barWidth2 + barWidth2 * level * 2.f, posY + barHeight2 }, ImGui::GetColorU32(IM_COL32(0, 200, 255, 255)));
                }

                if (cfg.visuals.client.bCrosshair)
                {
                    drawList->AddLine({ io.DisplaySize.x * 0.5f - cfg.visuals.client.fCrosshair, io.DisplaySize.y * 0.5f }, { io.DisplaySize.x * 0.5f + cfg.visuals.client.fCrosshair, io.DisplaySize.y * 0.5f }, ImGui::GetColorU32(cfg.visuals.client.crosshairColor));
                    drawList->AddLine({ io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f - cfg.visuals.client.fCrosshair }, { io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f + cfg.visuals.client.fCrosshair }, ImGui::GetColorU32(cfg.visuals.client.crosshairColor));
                }

                if (cfg.visuals.islands.bEnable)
                {
                    if (cfg.visuals.islands.bName)
                    {
                        const auto entries = AthenaGameViewportClient->World->GameState->IslandService->IslandDataAsset->IslandDataEntries;
                        for (auto i = 0u; i < entries.Count; i++)
                        {
                           
                            auto const island = entries[i];
                            auto const WorldMapData = island->WorldMapData;
                            if (!WorldMapData) continue;
                            const FVector islandLoc = WorldMapData->CaptureParams.WorldSpaceCameraPosition;
                            const float dist =localLoc.DistTo(islandLoc) * 0.01f;
                            if ((islandLoc.DistTo(FVector(0.f, 0.f, 0.f)) * 0.01) < 50.f) continue; // Conflictive Islands merging at 0.0.0 World Pos
                            if (dist > cfg.visuals.islands.intMaxDist) continue;
                            FVector2D screen;
                            if (localController->ProjectWorldLocationToScreen(islandLoc, screen))
                            {
                                char buf[0x64];
                                auto len = island->LocalisedName->multi(buf, 0x50);
                                sprintf_s(buf + len, sizeof(buf) - len, " [%.0fm]", dist);
                                Drawing::RenderText(buf, screen, cfg.visuals.islands.textCol);
                            }
                        }
                    }
                }
                
            }

            if (cfg.fishing.bEnable)
            {
                if (item)
                {
                    if (item->isFishingRod())
                    {
                        auto const localRod = *reinterpret_cast<AFishingRod**>(&item);
                        auto serverstate = localRod->ServerState;
                        //auto tensionshake = localRod->FishingTensionShake.TensionShake;
                        INPUT input{ 0 };
                        input.type = INPUT_MOUSE;

                        if (serverstate == 0)
                        {
                            /*static std::uintptr_t desiredTime = 0;
                            if (milliseconds_now() >= desiredTime)
                            {
                                input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
                                SendInput(1, &input, sizeof(INPUT));
                                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                                input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
                                SendInput(1, &input, sizeof(INPUT));
                                Logger::Log("Data sent\n");
                                desiredTime = milliseconds_now() + 2500;
                            }*/
                        }

                        if (localRod->ReplicatedFishState.FishingFishState == 4)
                        {
                            //Logger::Log("4\n");
                            //mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                            static std::uintptr_t desiredTime = 0;
                            if (milliseconds_now() >= desiredTime)
                            {
                                localRod->Server_ToggleReeling(true);
                                //Logger::Log("Data sent\n");
                                desiredTime = milliseconds_now() + 1000;
                            }
                            //localRod->Server_ToggleReeling(true);
                        }


                        else if (localRod->ReplicatedFishState.FishingFishState == 3)
                        {
                            //Logger::Log("Tension shake %.0f", tensionshake);
                            //Logger::Log("3\n");
                            //mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                            static std::uintptr_t desiredTime = 0;
                            if (milliseconds_now() >= desiredTime)
                            {
                                localRod->Server_ToggleReeling(false);
                                //Logger::Log("Data sent\n");
                                //Logger::Log("Tension shake %.0f\n", tensionshake);
                                desiredTime = milliseconds_now() + 1000;
                            }
                            //localRod->Server_ToggleReeling(false);
                            if (localRod->FishingFloatOffset.Y > -300.f && localRod->FishingFloatOffset.Y < 300.f) // Direction = Up
                            {
                                //Logger::Log("Up\n");
                                keybd_event(0x44, 42, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
                                keybd_event(0x41, 42, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
                                keybd_event(0x53, 42, KEYEVENTF_EXTENDEDKEY | 0, 0);
                            }
                            else if (localRod->FishingFloatOffset.Y < -300.f) // Direction = Left
                            {
                                //Logger::Log("Left\n");
                                keybd_event(0x53, 42, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
                                keybd_event(0x41, 42, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
                                keybd_event(0x44, 42, KEYEVENTF_EXTENDEDKEY | 0, 0);
                            }
                            else if (localRod->FishingFloatOffset.Y > 300.f) // Direction = Right
                            {
                                //Logger::Log("Right\n");
                                keybd_event(0x53, 42, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
                                keybd_event(0x44, 42, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
                                keybd_event(0x41, 42, KEYEVENTF_EXTENDEDKEY | 0, 0);
                            }
                        }

                        else if (serverstate == 12 && !localRod->PlayerIsBattlingFish)
                        {
                            //Logger::Log("5\n");
                            input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
                            SendInput(1, &input, sizeof(INPUT));
                            keybd_event(0x53, 42, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
                            keybd_event(0x44, 42, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
                            keybd_event(0x41, 42, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
                            /*std::this_thread::sleep_for(std::chrono::milliseconds(5000));
                            //void Multicast_RemoveFishFromLine();
                            keybd_event(0x46, 42, KEYEVENTF_EXTENDEDKEY, 0);
                            keybd_event(0x46, 42, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
                            cfg.fishing.bEnable = false;*/
                            // Press all the keys up, disable the feature
                        }
                    }
                }
            } 
            
            if (cfg.misc.bEnable && !localCharacter->IsLoading())
            {
                if (cfg.misc.client.bEnable)
                {
                    if (cfg.misc.client.bShipInfo)
                    {
                        auto ship = localCharacter->GetCurrentShip();
                        if (ship)
                        {
                            FVector velocity = ship->GetVelocity() / 100.f;
                            char buf[0xFF];

                            FVector2D pos{ 1.f, 45.f };
                            ImVec4 col{ 1.f,1.f,1.f,1.f };

                            auto speed = velocity.Size();
                            sprintf(buf, "Speed: %.0fm/s", speed);
                            pos.Y += 5.f;
                            Drawing::RenderText(buf, pos, col, true, false);

                            int holes = ship->GetHullDamage()->ActiveHullDamageZones.Count;
                            sprintf(buf, "Holes: %d", holes);
                            pos.Y += 20.f;
                            Drawing::RenderText(buf, pos, col, true, false);

                            int amount = 0;
                            auto water = ship->GetInternalWater();
                            if (water) amount = water->GetNormalizedWaterAmount() * 100.f;
                            sprintf(buf, "Water: %d%%", amount);
                            pos.Y += 20.f;
                            Drawing::RenderText(buf, pos, col, true, false);

                            pos.Y += 22.f;
                            float internal_water_percent = ship->GetInternalWater()->GetNormalizedWaterAmount();
                            drawList->AddLine({ pos.X - 1, pos.Y }, { pos.X + 100 + 1, pos.Y }, 0xFF000000, 6);
                            drawList->AddLine({ pos.X, pos.Y }, { pos.X + 100, pos.Y }, 0xFF00FF00, 4);
                            drawList->AddLine({ pos.X, pos.Y }, { pos.X + (100.f * internal_water_percent), pos.Y }, 0xFF0000FF, 4);
                        }
                    }

                    static std::uintptr_t desiredTime = 0;
                    if (milliseconds_now() >= desiredTime)
                    {
                        int return_value = (int)localCharacter->GetTargetFOV(AACharacter);;
                        //Logger::Log("return_value = %d\n", return_value); // Print return_value
                        //localController->SetTime(cfg.misc.client.time);
                        localController->FOV(cfg.misc.client.fov);
                        if (return_value == 17.f) //spyglass
                        {
                            localController->FOV(cfg.misc.client.fov * 0.2f);
                        }
                        desiredTime = milliseconds_now() + 100;
                    }
                }

                if (cfg.misc.sword.bEnable && item && item->isSword())
                {
                    if (cfg.misc.sword.noblockreduce)
                    {
                        localSword->DataAsset->BlockingMovementSpeed = EMeleeWeaponMovementSpeed::EMeleeWeaponMovementSpeed__EMeleeWeaponMovementSpeed_MAX;
                    }
                    else
                    {
                        localSword->DataAsset->BlockingMovementSpeed = EMeleeWeaponMovementSpeed::EMeleeWeaponMovementSpeed__Slowed;
                    }

                    if (cfg.misc.sword.noclamp)
                    {
                        localSword->DataAsset->HeavyAttack->ClampYawRange = -1.f;
                    }
                    else
                    {
                        localSword->DataAsset->HeavyAttack->ClampYawRange = 90.f;
                    }
                }

                if (cfg.misc.macro.bEnable)
                {
                    if (cfg.misc.macro.bLootsprint)
                    {
                        static std::uintptr_t desiredTime = 0;
                        if (milliseconds_now() >= desiredTime)
                        {
                            if (GetAsyncKeyState(0x56) & 0x8000)
                            {
                                keybd_event(0x58, 42, KEYEVENTF_EXTENDEDKEY | 0, 0);
                                keybd_event(VK_LSHIFT, 42, KEYEVENTF_EXTENDEDKEY | 0, 0);
                                keybd_event(VK_LSHIFT, 42, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
                                keybd_event(0x46, 42, KEYEVENTF_EXTENDEDKEY | 0, 0);
                                keybd_event(0x46, 42, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
                                keybd_event(0x58, 42, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
                                // if f=pickup bind then keybd_event(0x45 = keybd_event(0x46
                                // if e=pickup binf then 0x46 to 0x45
                            }
                            desiredTime = milliseconds_now() + 75;
                        }
                    }

                    if (cfg.misc.macro.b_bunnyhop)
                    {
                        static std::uintptr_t desiredTime = 0;
                        if (milliseconds_now() >= desiredTime)
                        {
                            if (ImGui::IsKeyPressed(VK_SPACE))
                            {
                                if (localCharacter->CanJump())
                                {
                                    localCharacter->Jump();
                                }
                            }
                            desiredTime = milliseconds_now() + 10;
                        }
                    }

                    if (localController->IdleDisconnectEnabled && cfg.misc.macro.bIdleKick)
                    {
                        localController->IdleDisconnectEnabled = false;

                    }
                }

                if (cfg.misc.game.bEnable)
                {
                    if (cfg.misc.game.bShowPlayers)
                    {
                        ImGui::PopStyleColor();
                        ImGui::PopStyleVar(2);
                        ImGui::SetNextWindowSize(ImVec2(335.f, 700.f), ImGuiCond_Once);
                        ImGui::SetNextWindowPos(ImVec2(10.f, 180.f), ImGuiCond_Once);
                        ImGui::Begin("PlayersList", 0, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_AlwaysAutoResize | ImGuiColumnsFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);
                        auto shipsService = gameState->ShipService;
                        if (shipsService)
                        {
                            ImGui::BeginChild("Info", { 0.f, 18.f });
                            ImGui::Text("Server Player List | Total Ships (Including AI): %d", shipsService->GetNumShips());
                            ImGui::EndChild();
                        }

                        auto crewService = gameState->CrewService;
                        auto crews = crewService->Crews;
                        if (crews.Data)
                        {
                            ImGui::Columns(2, "CrewPlayers", ImGuiColumnsFlags_NoResize);
                            ImGui::Separator();
                            ImGui::Text("Name"); ImGui::NextColumn();
                            ImGui::SetColumnOffset(1, 185.0f);
                            ImGui::Text("Activity"); ImGui::NextColumn();
                            ImGui::Separator();
                            for (uint32_t i = 0; i < crews.Count; i++)
                            {
                                auto& crew = crews[i];
                                auto players = crew.Players;
                                if (players.Data)
                                {
                                    for (uint32_t k = 0; k < players.Count; k++)
                                    {
                                        auto& player = players[k];
                                        char buf[0x64];
                                        player->PlayerName.multi(buf, 0x50);
                                        ImGui::Text(buf);
                                        ImGui::NextColumn();
                                        const char* actions[] = { "None", "Bailing", "Cannon", "Cannon_END", "Anchor", "Anchor_END", "Carrying Item", "Carrying Item_END", "Dead", "Dead_END", "Digging", "Extinguishing Fire", "Emptying Bucket", "Harpoon", "Harpoon_END", "Losing Health", "Repairing", "Sails", "Sails_END", "Undoing Repair", "Wheel", "Wheel_END" };
                                        auto activity = (uint8_t)player->GetPlayerActivity();
                                        if (activity < 21) { ImGui::Text(actions[activity]); }

                                        ImGui::NextColumn();
                                    }
                                    ImGui::Separator();
                                }

                            }
                            ImGui::Columns();
                        }
                        ImGui::End();
                        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
                        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
                        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0));
                    }
                }
                
                if (cfg.misc.allweapons.bEnable && localWeapon && isWieldedWeapon)
                {
                    if (cfg.misc.allweapons.fasterreloading)
                    {
                        /*
                        localWeapon->WeaponParameters.EquipDuration = -1.f;
                        localWeapon->WeaponParameters.RecoilDuration = 0.07f;
                        localWeapon->WeaponParameters.SecondsUntilZoomStarts = -1.f; // EYE OF REACH SCOPE FIX
                        localWeapon->WeaponParameters.SecondsUntilPostStarts = -1.f;
                        localWeapon->WeaponParameters.ZoomedRecoilDurationIncrease = -10.f;
                        localWeapon->WeaponParameters.IntoAimingDuration = -1.f;
                        localWeapon->WeaponParameters.TimeoutTolerance = -10.f;
                        //localWeapon->WeaponParameters.ProjectileDistributionMaxAngle = -180.f;*/
                        
                    }

                    if (cfg.misc.allweapons.fasteraimingspeed)
                    {
                        //localWeapon->WeaponParameters.AimingMoveSpeedScalar = 200.f;
                    }
                }
                
                if (cfg.misc.others.bEnable)
                {
                    if (cfg.misc.others.fasterharpoon && attachObject->isHarpoon())
                    {
                        
                    }
                }
                
            }

            for (auto l = 0u; l < levels.Count; l++)
            {
                auto const level = levels[l];
                if (!level) continue;
                const auto actors = level->AActors;
                if (!actors.Data) continue;

                for (auto a = 0u; a < actors.Count; a++)
                {
                    auto const actor = actors[a];
                    if (!actor) continue;


                    

                    {
                        //if (actor->isShip())
                        //{
                        //    const FVector forward = actor->GetActorForwardVector();
                        //    const FVector up = actor->GetActorUpVector();

                        //    const FVector loc = actor->K2_GetActorLocation();

                        //    FVector loc_back_line = loc - (up * 100.f) - (forward * 600.f);
                        //    FVector loc_front_line = loc - (up * 100.f) + (forward * 1000.f);

                        //    FVector2D screen_back_line;
                        //    FVector2D screen_front_line;
                        //    if (localController->ProjectWorldLocationToScreen(loc_back_line, screen_back_line) && localController->ProjectWorldLocationToScreen(loc_front_line, screen_front_line))
                        //    {
                        //        drawList->AddLine(*reinterpret_cast<ImVec2*>(&screen_back_line), *reinterpret_cast<ImVec2*>(&screen_front_line), 0xFF00FF00, 3.f);
                        //    }
                        //}
                        //if (actor->isShip())
                        //{
                        //    const FVector forward = actor->GetActorForwardVector();
                        //    const FVector up = actor->GetActorUpVector();
                        //    const FVector loc = actor->K2_GetActorLocation();

                        //    FVector loc_mast = loc;

                        //    //only for sloops
                        //    loc_mast += forward * 80.f;
                        //    loc_mast += up * 1690.f;

                        //    FVector2D screen_mast;
                        //    if (localController->ProjectWorldLocationToScreen(loc_mast, screen_mast))
                        //        drawList->AddCircle(*reinterpret_cast<ImVec2*>(&screen_mast), 10, 0xFF00FFFF, 20, 1);
                        //}
                    }

                    if (cfg.visuals.bEnable && !localCharacter->IsLoading())
                    {
                        if (cfg.visuals.megalodon.bEnable)
                        {
                            if (actor->isMegalodon())
                            {
                                const FVector location = actor->K2_GetActorLocation();
                                const int dist = localLoc.DistTo(location) * 0.01f;
                                if (dist > cfg.visuals.megalodon.drawdistance) continue;
                                FVector2D screen;
                                if (cfg.visuals.megalodon.bName)
                                {
                                    if (localController->ProjectWorldLocationToScreen(location, screen))
                                    {
                                        char buf[0x16];
                                        sprintf(buf, "Megalodon");
                                        Drawing::RenderText(buf, screen, cfg.visuals.megalodon.textCol);
                                        /*
                                        char buf[0x64];
                                        if (type.find("Hungering") != std::string::npos)
                                            sprintf(buf, "The Hungering One [%dm]", dist);
                                        else if (type.find("Crested") != std::string::npos)
                                            sprintf(buf, "The Crested Queen [%dm]", dist);
                                        else if (type.find("Shadowmaw") != std::string::npos)
                                            sprintf(buf, "The Shadowmaw [%dm]", dist);
                                        else if (type.find("Terror") != std::string::npos)
                                            sprintf(buf, "The Ancient Terror [%dm]", dist);
                                        else if (type.find("Shrouded") != std::string::npos)
                                            sprintf(buf, "The Shrouded Ghost [%dm]", dist);
                                        Drawing::RenderText(buf, screen, cfg.visuals.ships.textCol);
                                        */
                                    }
                                }
                            }
                        }

                        if (cfg.visuals.ships.bEnable)
                        {
                            FVector location = actor->K2_GetActorLocation();
                            location.Z = 3000;
                            const int dist = localLoc.DistTo(location) * 0.01f;

                            if (cfg.visuals.ships.bName && actor->isShip() && dist < 1726)
                            {
                                int amount = 0;
                                FVector2D screen;
                                FVector velocity = actor->GetVelocity() / 100.f;
                                auto speed = velocity.Size();

                                if (localController->ProjectWorldLocationToScreen(location, screen))
                                {
                                    auto water = actor->GetInternalWater();
                                    if (water) amount = water->GetNormalizedWaterAmount() * 100.f;
                                    auto type = actor->GetName();
                                    char buf[0x64];
                                    if (type.find("BP_Small") != std::string::npos)
                                        sprintf(buf, "Sloop\n(%d%% Water)\n[%dm] [%.0fm/s]", amount, dist, speed);
                                    else if (type.find("BP_Medium") != std::string::npos)
                                        sprintf(buf, "Brig (%d%% Water) [%dm] [%.0fm/s]", amount, dist, speed);
                                    else if (type.find("BP_Large") != std::string::npos)
                                        sprintf(buf, "Galleon (%d%% Water) [%dm] [%.0fm/s]", amount, dist, speed);
                                    else if (type.find("AISmall") != std::string::npos)
                                        sprintf(buf, "Skeleton Sloop (%d%% Water) [%dm] [%.0fm/s]", amount, dist, speed);
                                    else if (type.find("AILarge") != std::string::npos)
                                        sprintf(buf, "Skeleton Galleon (%d%% Water) [%dm] [%.0fm/s]", amount, dist, speed);
                                    Drawing::RenderText(buf, screen, cfg.visuals.ships.textCol);
                                }
                            }

                            if (cfg.visuals.ships.bName && actor->isFarShip() && dist > 1725)
                            {
                                int amount = 0;
                                FVector2D screen;
                                FVector velocity = actor->GetVelocity() / 100.f;
                                auto speed = velocity.Size();

                                if (localController->ProjectWorldLocationToScreen(location, screen))
                                {
                                    auto type = actor->GetName();
                                    char buf[0x64];
                                    if (type.find("BP_Small") != std::string::npos)
                                        sprintf(buf, "Sloop [%dm]", dist);
                                    else if (type.find("BP_Medium") != std::string::npos)
                                        sprintf(buf, "Brig [%dm]", dist);
                                    else if (type.find("BP_Large") != std::string::npos)
                                        sprintf(buf, "Galleon [%dm]", dist);
                                    else if (type.find("BP_AISmall") != std::string::npos)
                                        sprintf(buf, "Skeleton Sloop [%dm]", dist);
                                    else if (type.find("BP_AILarge") != std::string::npos)
                                        sprintf(buf, "Skeleton Galleon [%dm]", dist);
                                    Drawing::RenderText(buf, screen, cfg.visuals.ships.textCol);
                                }
                            }

                            if (actor->isShip())
                            {
                                const FVector location = actor->K2_GetActorLocation();
                                const int dist = localLoc.DistTo(location) * 0.01f;
                                FVector2D screen;

                                if (cfg.visuals.ships.bDamage && dist <= 225)
                                {
                                    auto const damage = actor->GetHullDamage();
                                    if (!damage) continue;
                                    const auto holes = damage->ActiveHullDamageZones;
                                    for (auto h = 0u; h < holes.Count; h++)
                                    {
                                        auto const hole = holes[h];

                                        const FVector location = hole->K2_GetActorLocation();
                                        if (localController->ProjectWorldLocationToScreen(location, screen))
                                        {
                                            auto color = cfg.visuals.ships.damageColor;
                                            drawList->AddLine({ screen.X - 6.f, screen.Y + 6.f }, { screen.X + 6.f, screen.Y - 6.f }, ImGui::GetColorU32(color));
                                            drawList->AddLine({ screen.X - 6.f, screen.Y - 6.f }, { screen.X + 6.f, screen.Y + 6.f }, ImGui::GetColorU32(color));
                                        };
                                    }
                                }
                            }
                        }

                        if (cfg.visuals.mermaids.bEnable)
                        {
                            if (actor->isMermaid())
                            {
                                FVector2D screen;
                                const FVector location = actor->K2_GetActorLocation();
                                const int dist = localLoc.DistTo(location) * 0.01f;
                                if (dist > cfg.visuals.mermaids.drawdistance) continue;
                                if (cfg.visuals.mermaids.bName && dist)
                                {
                                    if (localController->ProjectWorldLocationToScreen(location, screen)) 
                                    {
                                        char buf[0x16];
                                        sprintf(buf, "Mermaid [%dm]", dist);
                                        Drawing::RenderText(buf, screen, cfg.visuals.mermaids.textCol);
                                    }
                                }
                            }
                        }

                        if (cfg.visuals.rowboats.bEnable)
                        {
                            if (cfg.visuals.rowboats.bName)
                            {
                                if (actor->isRowboat())
                                {
                                    const FVector location = actor->K2_GetActorLocation();
                                    const int dist = localLoc.DistTo(location) * 0.01f;
                                    if (dist > cfg.visuals.rowboats.drawdistance) continue;
                                    FVector2D screen;

                                    if (localController->ProjectWorldLocationToScreen(location, screen))
                                    {
                                        auto type = actor->GetName();
                                        char buf[0x64];
                                        if (type.find("Cannon") != std::string::npos)
                                            sprintf(buf, "Cannon Rowboat [%dm]", dist);
                                        else if (type.find("Harpoon") != std::string::npos)
                                            sprintf(buf, "Harpoon Rowboat [%dm]", dist);
                                        else if (type.find("Rowboat") != std::string::npos)
                                            sprintf(buf, "Rowboat [%dm]", dist);
                                        Drawing::RenderText(buf, screen, cfg.visuals.rowboats.textCol);
                                    }
                                }
                            }

                        }

                        if (cfg.visuals.world.bEnable)
                        {
                            if (actor->isEvent())
                            {
                                const FVector location = actor->K2_GetActorLocation();
                                FVector2D screen;

                                if (localController->ProjectWorldLocationToScreen(location, screen))
                                {
                                    auto type = actor->GetName();
                                    const int dist = localLoc.DistTo(location) * 0.01f;
                                    if (dist > cfg.visuals.world.drawdistance) continue;
                                    char buf[0x64];
                                    if (type.find("ShipCloud") != std::string::npos)
                                        sprintf(buf, "Fleet [%dm]", dist);
                                    else if (type.find("AshenLord") != std::string::npos)
                                        sprintf(buf, "Ashen Lord [%dm]", dist);
                                    else if (type.find("Flameheart") != std::string::npos)
                                        sprintf(buf, "Flame Heart [%dm]", dist);
                                    else if (type.find("LegendSkellyFort") != std::string::npos)
                                        sprintf(buf, "Fort of Fortune [%dm]", dist);
                                    else if (type.find("SkellyFortOfTheDamned") != std::string::npos)
                                        sprintf(buf, "FOTD [%dm]", dist);
                                    else if (type.find("BP_SkellyFort") != std::string::npos)
                                        sprintf(buf, "Skull Fort [%dm]", dist);
                                    Drawing::RenderText(buf, screen, cfg.visuals.world.textCol);
                                }
                            }
                        }
                        
                    /*if (cfg.misc.xmarks.bEnable && actor->isXMarkMap())
                    {
                        if (XMarksMapCount == 1 && item && item->isXMarkMap())
                            Drawing::RenderText("Recognized Maps:", { io.DisplaySize.x * 0.85f, io.DisplaySize.y * 0.85f }, { 1.f, 1.f, 0.f, 1.f });
                        auto map = reinterpret_cast<AXMarksTheSpotMap*>(actor);
                        FString mapName = map->MapTexturePath;
                        auto mapMarks = map->Marks;

                        char cMapName[0x64];
                        const int len = mapName.multi(cMapName, sizeof(cMapName));
                        int mapCode = getMapNameCode(cMapName);

                        

                        //const auto islandDataEntries = gameState->IslandService->IslandDataAsset->IslandDataEntries;
                        //const auto islandDataEntries = gameState->IslandService->IslandDataAsset->IslandDataEntries;
                        const auto islandDataEntries = AthenaGameViewportClient->World->GameState->IslandService->IslandDataAsset->IslandDataEntries;

                        try
                        {
                            float scaleFactor = 1.041669;

                            for (auto i = 0u; i < islandDataEntries.Count; i++)
                            {
                                auto island = islandDataEntries[i];
                                const char* sIslandName = island->IslandName.GetNameFast();
                                char ccIsland[0x64];
                                ZeroMemory(ccIsland, sizeof(ccIsland));
                                sprintf_s(ccIsland, sizeof(ccIsland), sIslandName);

                                int code = getMapNameCode(ccIsland);

                                if (mapCode == code)
                                {
                                    std::string buf = getIslandNameByCode(mapCode);
                                    if (item && item->isXMarkMap())
                                        Drawing::RenderText(buf.c_str(), { io.DisplaySize.x * 0.85f, io.DisplaySize.y * 0.85f + 10 + 20 * XMarksMapCount }, { 0.f, 1.f, 0.f, 1.f });
                                    XMarksMapCount++;

                                    auto const WorldMapData = island->WorldMapData;
                                    if (!WorldMapData) continue;

                                    const FVector islandLoc = WorldMapData->CaptureParams.WorldSpaceCameraPosition;
                                    auto islandOrtho = WorldMapData->CaptureParams.CameraOrthoWidth;


                                    for (auto i = 0u; i < mapMarks.Count; i++)
                                    {
                                        auto mark = mapMarks[i];

                                        FVector2D v = FVector2D(mark.Position);
                                        FVector2D vectorRotated = RotatePoint(v, FVector2D(0.5f, 0.5f), 180 + map->Rotation, false);
                                        FVector2D vectorAlligned = FVector2D(vectorRotated.X - 0.5f, vectorRotated.Y - 0.5f);

                                        float islandScale = islandOrtho / scaleFactor;
                                        FVector2D offsetPos = vectorAlligned * islandScale;


                                        FVector digSpot = FVector(islandLoc.X - offsetPos.X, islandLoc.Y - offsetPos.Y, 0.f);

                                        FHitResult hit_result;
                                        auto start = FVector(digSpot.X, digSpot.Y, 5000.f);

                                        bool res = raytrace(world, start, digSpot, &hit_result);
                                        digSpot.Z = hit_result.ImpactPoint.Z;

                                        FVector2D screen;
                                        if (localController->ProjectWorldLocationToScreen(digSpot, screen))
                                        {
                                            char buf3[0x64];
                                            const int dist = localLoc.DistTo(digSpot) * 0.01f;
                                            //if (dist > cfg->esp.islands.marksRenderDistance) continue;
                                            sprintf_s(buf3, sizeof(buf3), "X [%dm]", dist);
                                            Drawing::RenderText(buf3, screen, cfg.visuals.islands.textCol);
                                        }

                                    }
                                }

                            }
                        }
                        catch (...) {
                        }
                    }*/

                        if (cfg.visuals.items.bEnable)
                        {
                            if (cfg.visuals.items.bName)
                            {
                                auto location = actor->K2_GetActorLocation();
                                FVector2D screen;
                                if (actor->isItem())
                                {
                                    const int dist = localLoc.DistTo(location) * 0.01f;
                                    if (dist > cfg.visuals.items.itemdrawdistance) continue;
                                    if (actor->GetAttachParentActor() == localCharacter->GetCurrentShip() && !GetAsyncKeyState(0x52) && localCharacter->GetCurrentShip() != NULL) continue;
                                    if (localController->ProjectWorldLocationToScreen(location, screen))
                                    {
                                        auto const desc = actor->GetItemInfo()->Desc;
                                        if (!desc) continue;
                                        char buf[0x64];
                                        const int len = desc->Title->multi(buf, 0x50);
                                        snprintf(buf + len, sizeof(buf) - len, " [%dm]", dist);
                                        Drawing::RenderText(buf, screen, cfg.visuals.items.textCol);
                                    }
                                }
                            }

                            if (cfg.visuals.items.barrelitems)
                            {
                                const FVector location = actor->K2_GetActorLocation();
                                FVector2D screen;
                                if (actor->isBarrel())
                                {
                                    const int dist = localLoc.DistTo(location) * 0.01f;
                                    if (dist > cfg.visuals.items.barreldrawdistance) continue;
                                    if (actor->GetAttachParentActor() == localCharacter->GetCurrentShip() && !GetAsyncKeyState(0x52) && localCharacter->GetCurrentShip() != NULL) continue;
                                    if (localController->ProjectWorldLocationToScreen(location, screen))
                                    {
                                        char buf[0x64];
                                        sprintf(buf, "B");
                                        Drawing::RenderText(buf, screen, cfg.visuals.items.barreltextCol);


                                        AStorageContainer* barrel = (AStorageContainer*)actor;
                                       


                                        if (barrel->StorageContainer)
                                        {
                                            auto cNodes = barrel->StorageContainer->ContainerNodes.ContainerNodes;
                                            for (unsigned int k = 0; k < cNodes.Count; k++)
                                            {
                                                FStorageContainerNode node = cNodes[k];

                                                if (node.ItemDesc)
                                                {
                                                    UItemDescEx* itemDesc = node.ItemDesc->CreateDefaultObject<UItemDescEx>();

                                                    if (itemDesc)
                                                    {
                                                        char buf2[0x50];
                                                        ZeroMemory(buf2, sizeof(buf2));


                                                        //FString itemName = itemDesc->Description.TextData->Text;
                                                        std::string itemName2 = getShortName(itemDesc->GetName());


                                                        int len = snprintf(buf2, sizeof(buf2), itemName2.c_str());
                                                        snprintf(buf2 + len, sizeof(buf2) - len, " [%d]", node.NumItems);


                                                        screen.Y += 20;

                                                        if (cfg.misc.others.barrelstoggle)
                                                        {
                                                            if (GetAsyncKeyState(0x52)) // R Key 
                                                                Drawing::RenderText(buf2, screen, cfg.visuals.items.barreltextCol);
                                                        }
                                                        else
                                                        {
                                                            Drawing::RenderText(buf2, screen, cfg.visuals.items.barreltextCol);
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }

                            if (cfg.visuals.items.ammochests)
                            {
                                const FVector location = actor->K2_GetActorLocation();
                                FVector2D screen;
                                if (actor->isAmmoChest())
                                {
                                    const int dist = localLoc.DistTo(location) * 0.01f;
                                    if (dist > cfg.visuals.items.ammochestsdrawdistance) continue;
                                    if (localController->ProjectWorldLocationToScreen(location, screen))
                                    {
                                        char buf[0x64];
                                        sprintf(buf, "Ammo Chest [%dm]", dist);
                                        Drawing::RenderText(buf, screen, cfg.visuals.items.ammotextCol);
                                    }
                                }
                            }
                        }

                        if (cfg.visuals.radar.bEnable && localCharacter->GetCurrentShip())
                        {
                            do
                            {
                                if (!actor->isShip())
                                    break;

                                auto local_ship = localCharacter->GetCurrentShip();
                                if (!local_ship)
                                    break;

                                if (local_ship == actor)
                                    break;

                                const FVector target_location = actor->K2_GetActorLocation();
                                const FVector target_front_location = target_location + (actor->GetActorForwardVector() * (20.f * (float)cfg.visuals.radar.i_scale));

                                const FVector local_location = local_ship->K2_GetActorLocation();
                                const FRotator rotation = local_ship->K2_GetActorRotation();

                                FVector2D radar_point_1 = rotate_radar(target_location, local_location, rotation);
                                if (cfg.visuals.radar.i_scale != 0)
                                    radar_point_1 *= (1.f / cfg.visuals.radar.i_scale);

                                FVector2D radar_point_2 = rotate_radar(target_front_location, local_location, rotation);
                                if (cfg.visuals.radar.i_scale != 0)
                                    radar_point_2 *= (1.f / cfg.visuals.radar.i_scale);

                                float distance_to_center = std::sqrtf(radar_point_1.X * radar_point_1.X + radar_point_1.Y * radar_point_1.Y);
                                if (distance_to_center < ((float)cfg.visuals.radar.i_size / 2.f))
                                {
                                    //point 1
                                    drawList->AddCircleFilled({ radar_pos.X + radar_point_1.X, radar_pos.Y - radar_point_1.Y }, 5, 0xFF000000, 15);
                                    drawList->AddCircleFilled({ radar_pos.X + radar_point_1.X, radar_pos.Y - radar_point_1.Y }, 4, 0xFF0000FF, 15);

                                    //point 2
                                    drawList->AddLine({ radar_pos.X + radar_point_1.X, radar_pos.Y - radar_point_1.Y }, { radar_pos.X + radar_point_2.X, radar_pos.Y - radar_point_2.Y }, 0xFF0000FF, 1.f);
                                }

                            } while (false);
                        }

                        if (cfg.visuals.client.bEnable)
                        {
                            if (cfg.visuals.client.b_cannon_tracers)
                            {
                                if (actor->isCannonProjectile())
                                {
                                    cannonball_location add_location = {};
                                    add_location.location = actor->K2_GetActorLocation();
                                    add_location.draw_times = cfg.visuals.client.cannon_tracers_length;
                                    add_location.drawn = 0;
                                    cannonball_tracers.push_back(add_location);
                                }
                            }
                        }

                        if (cfg.visuals.flag.bEnable)
                        {
                            if (cfg.visuals.flag.bName)
                            {
                                const FVector location = actor->K2_GetActorLocation();
                                FVector2D screen;
                                if (actor->isEmissaryFlag())
                                {
                                    const int dist = localLoc.DistTo(location) * 0.01f;
                                    if (dist > cfg.visuals.flag.drawdistance) continue;
                                    if (localController->ProjectWorldLocationToScreen(location, screen))
                                    {
                                        char buf[0x64];
                                        sprintf(buf, "Emissary Flag [%dm]", dist);
                                        Drawing::RenderText(buf, screen, cfg.visuals.flag.textCol);
                                    }
                                }
                            }
                        }

                        if (cfg.visuals.storm.bEnable)
                        {
                            
                            const FVector location = actor->K2_GetActorLocation();
                            
                            FVector2D screen;
                        
                            



                            if (cfg.visuals.storm.bName)
                            {
                                
                                auto type = actor->GetName();
                                if (type.find("Storm") != std::string::npos)
                                {
                                    const int dist = localLoc.DistTo(location) * 0.01f;

                                    if (dist > cfg.visuals.storm.drawdistance) continue;
                                    if (location != NULL)
                                    {
                                        if (localController->ProjectWorldLocationToScreen(location, screen))
                                        {




                                            char buf[0x64];
                                            sprintf(buf, "Storm [%dm]", dist);




                                            Drawing::RenderText(buf, screen, cfg.visuals.storm.textCol);



                                        }
                                    }
                                }
                            }
                        }



                       


                  
                        
                        if (cfg.visuals.seagulls.bEnable)
                        {
                            if (cfg.visuals.seagulls.bName) 
                            {
                                const FVector location = actor->K2_GetActorLocation();
                                FVector2D screen;
                                auto type = actor->GetName();
                                if (type.find("Seagull") != std::string::npos)
                                {
                                    const int dist = localLoc.DistTo(location) * 0.01f;
                                    if (dist > cfg.visuals.seagulls.drawdistance) continue;
                                    if (localController->ProjectWorldLocationToScreen(location, screen))
                                    {
                                        char buf[0x64];
                                        sprintf(buf, "Seagulls [%dm]", dist);
                                        Drawing::RenderText(buf, screen, cfg.visuals.seagulls.textCol);
                                    }
                                }
                                if (type.find("GhostShipRewardMarker") != std::string::npos)
                                {
                                    const int dist = localLoc.DistTo(location) * 0.01f;
                                    if (dist > cfg.visuals.seagulls.drawdistance) continue;
                                    if (localController->ProjectWorldLocationToScreen(location, screen))
                                    {
                                        char buf[0x64];
                                        sprintf(buf, "OOS Reward [%dm]", dist);
                                        Drawing::RenderText(buf, screen, cfg.visuals.seagulls.textCol);
                                    }

                                }
                                // EMISSARY FLAG TEST :D
                               /* if (type.find("EmissaryFlotsam") != std::string::npos)
                                {
                                    if (actor->isItem())
                                    {
                                        const int dist = localLoc.DistTo(location) * 0.01f;
                                        if (dist > cfg.visuals.seagulls.drawdistance) continue;
                                        if (localController->ProjectWorldLocationToScreen(location, screen))
                                        {
                                            auto const desc = actor->GetItemInfo()->Desc;
                                            if (!desc) continue;
                                            char buf[0x64];
                                            const int len = desc->Title->multi(buf, 0x50);
                                            snprintf(buf + len, sizeof(buf) - len, " [%dm]", dist);
                                            Drawing::RenderText(buf, screen, cfg.visuals.seagulls.textCol);
                                        }
                                    }
                                }*/
                            }

                        }
                        if (cfg.visuals.client.bDebug)
                        {
                            const FVector location = actor->K2_GetActorLocation();
                            const float dist = localLoc.DistTo(location) * 0.01f;
                            if (dist < cfg.visuals.client.fDebug)
                            {
                                auto const actorClass = actor->Class;
                                if (!actorClass) continue;
                                auto super = actorClass->SuperField;
                                if (!super) continue;
                                FVector2D screen;
                                if (localController->ProjectWorldLocationToScreen(location, screen))
                                {
                                    auto type = actor->GetName();
                                    auto superName = super->GetNameFast();
                                    auto className = actorClass->GetNameFast();
                                    if (superName && className  /*&&!(type.find("EmissaryFlotsam_Reapers") != std::string::npos)*/)
                                    {
                                        char buf[0x128];
                                        sprintf(buf, " %s %s [%dm] (%p)", className, superName, (int)dist, actor);
                                        Drawing::RenderText(buf, screen, ImVec4(1.f, 1.f, 1.f, 1.f));
                                    }
                                }
                            }
                        }

                        if (cfg.visuals.skeletons.bEnable && actor->isSkeleton() && !actor->IsDead())
                        {
                            const FVector location = actor->K2_GetActorLocation();
                            const int dist = localLoc.DistTo(location) * 0.01f;
                            if (dist > cfg.visuals.skeletons.drawdistance) continue;

                            // todo: make a function to draw both skeletons and players as they are similar
                            FVector origin, extent;
                            actor->GetActorBounds(true, origin, extent);

                            FVector2D headPos;
                            if (!localController->ProjectWorldLocationToScreen({ location.X, location.Y, location.Z + extent.Z }, headPos)) continue;
                            FVector2D footPos;
                            if (!localController->ProjectWorldLocationToScreen({ location.X, location.Y, location.Z - extent.Z }, footPos)) continue;

                            const float height = abs(footPos.Y - headPos.Y);
                            const float width = height * 0.4f;

                            const bool bVisible = localController->LineOfSightTo(actor, cameraLoc, false);
                            const ImVec4 col = bVisible ? cfg.visuals.skeletons.colorVis : cfg.visuals.skeletons.colorInv;

                            switch (cfg.visuals.skeletons.boxType)
                            {
                            case Config::EBox::E2DBoxes:
                            {
                                Drawing::Render2DBox(headPos, footPos, height, width, col);
                                break;
                            }
                            case Config::EBox::E3DBoxes:
                            {
                                FRotator rotation = actor->K2_GetActorRotation();
                                if (!Drawing::Render3DBox(localController, origin, extent, rotation, col)) continue;
                                break;
                            }
                            /*
                            case Config::EBox::EDebugBoxes:
                            {
                                UKismetMathLibrary::DrawDebugBox(actor, origin, extent, *reinterpret_cast<const FLinearColor*>(&col), actor->K2_GetActorRotation(), 0.0f);
                                break;
                            }
                            */
                            }

                            if (cfg.visuals.skeletons.bName)
                            {
                                char buf[0x20];
                                sprintf(buf, "Skeleton [%dm]", dist);
                                Drawing::RenderText(buf, headPos, cfg.visuals.skeletons.textCol);
                            }

                            if (cfg.visuals.skeletons.barType != Config::EBar::ENone)
                            {
                                auto const healthComp = actor->HealthComponent;
                                if (!healthComp) continue;
                                const float hp = healthComp->GetCurrentHealth() / healthComp->GetMaxHealth();
                                const float width2 = width * 0.5f;
                                const float adjust = height * 0.025f;

                                switch (cfg.visuals.skeletons.barType)
                                {
                                case Config::EBar::ELeft:
                                {
                                    const float len = height * hp;
                                    drawList->AddRectFilled({ headPos.X - width2 - adjust * 2.f, headPos.Y }, { headPos.X - width2 - adjust, footPos.Y - len }, ImGui::GetColorU32(IM_COL32(255, 0, 0, 255)));
                                    drawList->AddRectFilled({ headPos.X - width2 - adjust * 2.f, footPos.Y - len }, { headPos.X - width2 - adjust, footPos.Y }, ImGui::GetColorU32(IM_COL32(0, 255, 0, 255)));
                                    break;
                                }
                                case Config::EBar::ERight:
                                {
                                    const float len = height * hp;
                                    drawList->AddRectFilled({ headPos.X + width2 + adjust, headPos.Y }, { headPos.X + width2 + adjust * 2.f, footPos.Y - len }, ImGui::GetColorU32(IM_COL32(255, 0, 0, 255)));
                                    drawList->AddRectFilled({ headPos.X + width2 + adjust, footPos.Y - len }, { headPos.X + width2 + adjust * 2.f, footPos.Y }, ImGui::GetColorU32(IM_COL32(0, 255, 0, 255)));
                                    break;
                                }
                                case Config::EBar::EBottom:
                                {
                                    const float len = width * hp;
                                    drawList->AddRectFilled({ headPos.X - width2, footPos.Y + adjust }, { headPos.X - width2 + len, footPos.Y + adjust * 2.f }, ImGui::GetColorU32(IM_COL32(0, 255, 0, 255)));
                                    drawList->AddRectFilled({ headPos.X - width2 + len, footPos.Y + adjust }, { headPos.X + width2, footPos.Y + adjust * 2.f }, ImGui::GetColorU32(IM_COL32(255, 0, 0, 255)));
                                    break;
                                }
                                case Config::EBar::ETop:
                                {
                                    const float len = width * hp;
                                    drawList->AddRectFilled({ headPos.X - width2, headPos.Y - adjust * 2.f }, { headPos.X - width2 + len, headPos.Y - adjust }, ImGui::GetColorU32(IM_COL32(0, 255, 0, 255)));
                                    drawList->AddRectFilled({ headPos.X - width2 + len, headPos.Y - adjust * 2.f }, { headPos.X + width2, headPos.Y - adjust }, ImGui::GetColorU32(IM_COL32(255, 0, 0, 255)));
                                    break;
                                }
                                }
                            }
                        }

                        if (cfg.visuals.shipwrecks.bEnable && actor->isShipwreck())
                        {
                            auto location = actor->K2_GetActorLocation();
                            FVector2D screen;
                            if (localController->ProjectWorldLocationToScreen(location, screen))
                            {
                                const int dist = localLoc.DistTo(location) * 0.01f;
                                if (dist > cfg.visuals.shipwrecks.drawdistance) continue;
                                char buf[0x64];
                                sprintf(buf, "Shipwreck [%dm]", dist);
                                Drawing::RenderText(buf, screen, cfg.visuals.shipwrecks.textCol);
                            }
                        }

                        if (cfg.visuals.players.bEnable && actor->isPlayer() && actor != localCharacter && !actor->IsDead())
                        {
                            const FVector location = actor->K2_GetActorLocation();
                            const int dist = localLoc.DistTo(location) * 0.01f;
                            if (dist > cfg.visuals.skeletons.drawdistance) continue;

                            const bool teammate = UCrewFunctions::AreCharactersInSameCrew(actor, localCharacter);
                            if (teammate && !cfg.visuals.players.bDrawTeam) continue;

                            FVector origin, extent;
                            actor->GetActorBounds(true, origin, extent);

                            FVector2D headPos;
                            if (!localController->ProjectWorldLocationToScreen({ location.X, location.Y, location.Z + extent.Z }, headPos)) continue;
                            FVector2D footPos;
                            if (!localController->ProjectWorldLocationToScreen({ location.X, location.Y, location.Z - extent.Z }, footPos)) continue;

                            const float height = abs(footPos.Y - headPos.Y);
                            const float width = height * 0.4f;

                            const bool bVisible = localController->LineOfSightTo(actor, cameraLoc, false);

                            ImVec4 col;
                            if (teammate) col = bVisible ? cfg.visuals.players.teamColorVis : cfg.visuals.players.teamColorInv;
                            else  col = bVisible ? cfg.visuals.players.enemyColorVis : cfg.visuals.players.enemyColorInv;

                            switch (cfg.visuals.players.boxType)
                            {
                            case Config::EBox::E2DBoxes:
                            {
                                Drawing::Render2DBox(headPos, footPos, height, width, col);
                                break;
                            }
                            case Config::EBox::E3DBoxes:
                            {
                                FRotator rotation = actor->K2_GetActorRotation();
                                FVector ext = { 35.f, 35.f, extent.Z };
                                if (!Drawing::Render3DBox(localController, location, ext, rotation, col)) continue;
                                break;
                            }

                            /*
                            case Config::EBox::EDebugBoxes:
                            {
                                FVector ext = { 35.f, 35.f, extent.Z };
                                UKismetMathLibrary::DrawDebugBox(actor, location, ext, *reinterpret_cast<FLinearColor*>(&col), actor->K2_GetActorRotation(), 0.0f);
                                break;
                            }
                            */
                            }
                            
                             if (cfg.visuals.players.bSkeleton)
                            {
                                auto const mesh = actor->Mesh;
                                if (!actor->Mesh) continue;

                                const BYTE bodyHead[] = { 4, 5, 6, 51, 7, 6, 80, 7, 8, 9 };
                                const BYTE neckHandR[] = { 80, 81, 82, 83, 84 };
                                const BYTE neckHandL[] = { 51, 52, 53, 54, 55 };
                                const BYTE bodyFootR[] = { 4, 111, 112, 113, 114 };
                                const BYTE bodyFootL[] = { 4, 106, 107, 108, 109 };

                                const std::pair<const BYTE*, const BYTE> skeleton[] = { {bodyHead, 10}, {neckHandR, 5}, {neckHandL, 5}, {bodyFootR, 5}, {bodyFootL, 5} };

                                const FMatrix comp2world = mesh->K2_GetComponentToWorld().ToMatrixWithScale();
                               if (!Drawing::RenderSkeleton(localController, mesh, comp2world, skeleton, 5, col)) continue;
                           }
                           
                            if (cfg.visuals.players.bName)
                            {
                                auto const playerState = actor->PlayerState;
                                if (!playerState)
                                {
                                    continue;
                                }
                                const auto playerName = playerState->PlayerName;
                                if (!playerName.Data)
                                {
                                    continue;
                                }
                                char buf[0x30];
                                const int len = playerName.multi(buf, 0x20);
                                snprintf(buf + len, sizeof(buf) - len, " [%dm]", dist);
                                const float adjust = height * 0.05f;
                                FVector2D pos = { headPos.X, headPos.Y - adjust };
                                Drawing::RenderText(buf, pos, cfg.visuals.players.textCol);
                            }

                            // if (cfg.visuals.players.bWeaponanmes) todo:fix this
                            //{
                            //    const auto playerWeaponName = actor->WieldedItemComponent->CurrentlyWieldedItem->Name;
                           // }

                            if (cfg.visuals.players.barType != Config::EBar::ENone)
                            {
                                auto const healthComp = actor->HealthComponent;
                                if (!healthComp)
                                    continue;

                                const float hp = healthComp->GetCurrentHealth() / healthComp->GetMaxHealth();
                                const float width2 = width * 0.5f;
                                const float adjust = height * 0.025f;
                                switch (cfg.visuals.players.barType)
                                {
                                case Config::EBar::ELeft:
                                {
                                    const float len = height * hp;
                                    drawList->AddRectFilled({ headPos.X - width2 - adjust * 2.f, headPos.Y }, { headPos.X - width2 - adjust, footPos.Y - len }, ImGui::GetColorU32(IM_COL32(255, 0, 0, 255)));
                                    drawList->AddRectFilled({ headPos.X - width2 - adjust * 2.f, footPos.Y - len }, { headPos.X - width2 - adjust, footPos.Y }, ImGui::GetColorU32(IM_COL32(0, 255, 0, 255)));
                                    break;
                                }
                                case Config::EBar::ERight:
                                {
                                    const float len = height * hp;
                                    drawList->AddRectFilled({ headPos.X + width2 + adjust, headPos.Y }, { headPos.X + width2 + adjust * 2.f, footPos.Y - len }, ImGui::GetColorU32(IM_COL32(255, 0, 0, 255)));
                                    drawList->AddRectFilled({ headPos.X + width2 + adjust, footPos.Y - len }, { headPos.X + width2 + adjust * 2.f, footPos.Y }, ImGui::GetColorU32(IM_COL32(0, 255, 0, 255)));
                                    break;
                                }
                                case Config::EBar::EBottom:
                                {
                                    const float len = width * hp;
                                    drawList->AddRectFilled({ headPos.X - width2, footPos.Y + adjust }, { headPos.X - width2 + len, footPos.Y + adjust * 2.f }, ImGui::GetColorU32(IM_COL32(0, 255, 0, 255)));
                                    drawList->AddRectFilled({ headPos.X - width2 + len, footPos.Y + adjust }, { headPos.X + width2, footPos.Y + adjust * 2.f }, ImGui::GetColorU32(IM_COL32(255, 0, 0, 255)));
                                    break;
                                }
                                case Config::EBar::ETop:
                                {
                                    const float len = width * hp;
                                    drawList->AddRectFilled({ headPos.X - width2, headPos.Y - adjust * 2.f }, { headPos.X - width2 + len, headPos.Y - adjust }, ImGui::GetColorU32(IM_COL32(0, 255, 0, 255)));
                                    drawList->AddRectFilled({ headPos.X - width2 + len, headPos.Y - adjust * 2.f }, { headPos.X + width2, headPos.Y - adjust }, ImGui::GetColorU32(IM_COL32(255, 0, 0, 255)));
                                    break;
                                }
                                }

                            }
                        }

                        if (cfg.visuals.animals.bEnable && actor->isAnimal())
                        {
                            FVector origin, extent;
                            actor->GetActorBounds(true, origin, extent);

                            FVector2D headPos;
                            if (!localController->ProjectWorldLocationToScreen({ origin.X, origin.Y, origin.Z + extent.Z }, headPos)) continue;
                            FVector2D footPos;
                            if (!localController->ProjectWorldLocationToScreen({ origin.X, origin.Y, origin.Z - extent.Z }, footPos)) continue;

                            float height = abs(footPos.Y - headPos.Y);
                            float width = height * 0.6f;

                            if (cfg.visuals.animals.bName)
                            {

                                auto displayName = reinterpret_cast<AFauna*>(actor)->DisplayName;
                                if (displayName) {
                                    const int dist = localLoc.DistTo(origin) * 0.01f;
                                    if (dist > cfg.visuals.animals.drawdistance) continue;
                                    char buf[0x32];
                                    const int len = displayName->multi(buf, 0x50); 
                                    snprintf(buf + len, sizeof(buf) - len, " [%dm]", dist);
                                    const float adjust = height * 0.05f;
                                    FVector2D pos = { headPos.X, headPos.Y - adjust };
                                    Drawing::RenderText(buf, pos, cfg.visuals.animals.textCol);
                                }
                            }
                        }

                       






                        if (cfg.visuals.sharks.bEnable && actor->isShark())
                        {
                            FVector origin, extent;
                            actor->GetActorBounds(true, origin, extent);

                            FVector2D headPos;
                            if (!localController->ProjectWorldLocationToScreen({ origin.X, origin.Y, origin.Z + extent.Z }, headPos)) continue;
                            FVector2D footPos;
                            if (!localController->ProjectWorldLocationToScreen({ origin.X, origin.Y, origin.Z - extent.Z }, footPos)) continue;

                            const float height = abs(footPos.Y - headPos.Y);
                            const float width = height * 0.6f;

                            if (cfg.visuals.sharks.bName)
                            {
                                char buf[0x20];
                                const int dist = localLoc.DistTo(origin) * 0.01f;
                                if (dist > cfg.visuals.sharks.drawdistance) continue;
                                sprintf(buf, "Shark [%dm]", dist);
                                const float adjust = height * 0.05f;
                                FVector2D pos = { headPos.X, headPos.Y - adjust };
                                Drawing::RenderText(buf, pos, cfg.visuals.sharks.textCol);
                            }
                        }

                      

                        if (cfg.visuals.puzzles.bEnable && actor->isPuzzleVault())
                        {
                            auto vault = reinterpret_cast<APuzzleVault*>(actor);
                            if (cfg.visuals.puzzles.bDoor)
                            {
                                const FVector location = reinterpret_cast<ACharacter*>(vault->OuterDoor)->K2_GetActorLocation();
                                FVector2D screen;
                                if (location != NULL)
                                {
                                    if (localController->ProjectWorldLocationToScreen(location, screen))
                                    {
                                        char buf[0x64];
                                        const int dist = localLoc.DistTo(location) * 0.01f;
                                        if (dist > cfg.visuals.puzzles.drawdistance) continue;
                                        sprintf(buf, "Vault Door [%dm]", dist);
                                        Drawing::RenderText(buf, screen, cfg.visuals.puzzles.textCol);
                                    }
                                }
                            }
                        }




                }

                    if (cfg.misc.client.b_map_pins)
                    {
                        if (actor->isMapTable())
                        {
                            if (localCharacter->GetCurrentShip() == actor->GetParentActor())
                            {
                                auto maptable = reinterpret_cast<AMapTable*>(actor);
                                auto map_pins = maptable->MapPins;
                                for (int i = 0; i < map_pins.Count; i++)
                                {
                                    FVector2D current_map_pin = map_pins[i];

                                    current_map_pin *= 100.f;
                                    FVector current_map_pin_world;
                                    current_map_pin_world.X = current_map_pin.X;
                                    current_map_pin_world.Y = current_map_pin.Y;
                                    current_map_pin_world.Z = 0.f;

                                    FVector2D screen;
                                    if (localController->ProjectWorldLocationToScreen(current_map_pin_world, screen))
                                    {
                                        const int dist = localLoc.DistTo(current_map_pin_world) * 0.01f;
                                        char buf[0x64];
                                        snprintf(buf, sizeof(buf), "Map Pin [%dm]", dist);
                                        Drawing::RenderText(buf, { screen.X, screen.Y - 8 }, { 1.f,1.f,1.f,1.f }, true, true);
                                    }
                                }
                            }

                        }
                    }
                    if (cfg.misc.others.b_ship_pins)
                    {
                        if (actor->isMapTable())
                        {
                            if (localCharacter->GetCurrentShip() == actor->GetParentActor())
                            {
                                auto maptable = reinterpret_cast<AMapTable*>(actor);
                                auto tracked_ships = maptable->TrackedShips;
                                for (auto s = 0u; s < tracked_ships.Count; s++)
                                {
                                        FWorldMapShipLocation current_ship = tracked_ships[s];
                                        //FVector2D current_map_pin = map_pins[i];

                                        //current_ship.Location *= 100.f;
                                        FVector current_ship_pin_world;
                                        current_ship_pin_world.X = current_ship.Location.X;
                                        current_ship_pin_world.Y = current_ship.Location.Y;
                                        current_ship_pin_world.Z = 0.f;
                                        const int dist = localLoc.DistTo(current_ship_pin_world) * 0.01f;
                                        FVector2D screen;
                                        if (dist < 3500.f) continue;
                                        if (localController->ProjectWorldLocationToScreen(current_ship_pin_world, screen))
                                        {
                                            char buf[0x64];
                                            snprintf(buf, sizeof(buf), "Ship [%dm]", dist);
                                           /* else if (dist < 3500.f && asd != 0)
                                                snprintf(buf, sizeof(buf), "[Reaper: %d]", asd);
                                            else if (dist > 3500.f && asd == 0)
                                                snprintf(buf, sizeof(buf), "Ship [%dm]", dist);*/
                                                
                                            Drawing::RenderText(buf, { screen.X, screen.Y - 8 }, cfg.visuals.ships.textCol, true, true);
                                        }
                                }
                            }

                        }
                    }

                    if (cfg.misc.client.b_cooking_timer)
                    {
                        auto ship = localCharacter->GetCurrentShip();
                        if (ship) 
                        {
                            if (actor->isCookingPot())

                            {
                                FVector location = actor->K2_GetActorLocation();
                                location.Z = 30;
                                const int dist = localLoc.DistTo(location) * 0.01f;
                                if (dist < 30) {
                                    auto pot = reinterpret_cast<ACookingPot*>(actor);
                                    const auto cooking_state = pot->CookerComponent->CookingState;

                                    ImVec4 col{ 1.f,1.f,1.f,1.f };
                                    ImVec4 col_warning{ 1.f, 0.f, 0.f, 1.f };
                                    FVector2D pos{ 1.f, 112.f };
                                    FVector2D pos_warning{ 1.f, 132.f };

                                    bool warning = false;

                                    const char* text_state;
                                    if (cooking_state.Cooking)
                                    {
                                        if (cooking_state.VisibleCookedExtent < 1)
                                            text_state = "Raw";
                                        else if (cooking_state.VisibleCookedExtent == 1)
                                            text_state = "Almost Cooked";
                                        else if (cooking_state.VisibleCookedExtent > 1)
                                        {
                                            text_state = "Cooked";
                                            warning = true;
                                        }
                                        else if (cooking_state.VisibleCookedExtent > 2)
                                            text_state = "Burned";
                                    }
                                    else {
                                        text_state = "Not Cooking";
                                    }
                                  /*  auto pot = reinterpret_cast<ACookingPot*>(actor);
                                    auto component = pot->CookerComponent;
                                    int smoke_level = int(component->CookingState.SmokeFeedbackLevel);
                                    int cooked_extent = int(component->CookingState.VisibleCookedExtent * 100 / 2);

                                    ImVec4 col_warning{ 1.f, 0.f, 0.f, 1.f };
                                    FVector2D pos{ 1.f, 112.f };
                                    ImVec4 col{ 1.f,1.f,1.f,1.f };
                                    char buf[0x64];

                                    if (smoke_level == 0) {
                                        sprintf(buf, "Cooking Pot Empty [%dm] %d", dist, smoke_level);
                                    }
                                    else {
                                        if (cooked_extent == 0) sprintf(buf, "Raw [%dm]", dist);
                                        if (cooked_extent > 0) sprintf(buf, "Undercooked");
                                        if (cooked_extent > 50) sprintf(buf, "Cooked");
                                        //if (cooked_extent > 50 && cooked_extent < 101) sprintf(buf, "Cooked");// Drawing::RenderText(buf, pos, col_warning, true, false);
                                        if (cooked_extent > 100) sprintf(buf, "Burned");
                                    }*/
                                    //const char* c = text_state.c_str();
                                    Drawing::RenderText(text_state, pos, col, true, false);
                                    if (warning)
                                    {
                                        const char* warning_text;
                                        warning_text = "Ready!";
                                        Drawing::RenderText(warning_text, pos_warning, col_warning, true, false);
                                        //Drawing::RenderText(buf, pos_time, col_warning, true, false);
                                    }
                                }
                            }
                           //if (actor->isItem())
                            //{
                              /*  auto type = actor->GetName();
                                FVector2D pos_time{ 1.f, 152.f };
                                ImVec4 col_time{ 1.f, 0.f, 0.f, 1.f };
                                if (type.find("BP_fod") != std::string::npos)
                                {
                                    auto comp = reinterpret_cast<UCookableComponent*>(actor);
                                    const auto time = comp->TimeToNextCookState;
                                    char buf[0x64];
                                    sprintf(buf, "%f", time);
                                    Drawing::RenderText(buf, pos_time, col_time, true, false);
                                }
                           //}*/
                        }
                    }
                    
                    if (ImGui::IsKeyPressed(VK_F10))
                    {
                        if (cfg.misc.others.tpitems && actor->isItem())
                        {
                            const FVector location = actor->K2_GetActorLocation();
                            const int dist = localLoc.DistTo(location) * 0.01f;
                            location.Z + 5;
                            if (dist > cfg.misc.others.itemdistance) continue;
                            {

                                FVector NewLocation = localCharacter->K2_GetActorLocation();
                                FHitResult hit_result;
                                actor->K2_SetActorLocation(NewLocation, false, hit_result, true);
                            }
                        }
                    }

                    if (ImGui::IsKeyPressed(VK_F11))
                    {
                        if (cfg.misc.others.freecam)
                        {
                            FVector NewCameraLocation = localCharacter->K2_GetActorLocation();
                            NewCameraLocation.Z + 5;
                            FRotator NewCameraRotation = localCharacter->K2_GetActorRotation();
                            float NewCameraFOV = 0.f;
                            localCharacter->BlueprintUpdateCamera(NewCameraLocation, NewCameraRotation, NewCameraFOV);
                        }
                    }

                    /*if (cfg.fishing.bEnable)
                    {
                        if (item->isFishingRod())
                        {
                            auto const localRod = *reinterpret_cast<AFishingRod**>(&item);
                            auto serverstate = localRod->ServerState;


                            if (localRod->ReplicatedFishState.FishingFishState == 4)
                            {
                                Logger::Log("4");
                               // mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
                                //localRod->Server_ToggleReeling(true);
                            }


                            else if (localRod->ReplicatedFishState.FishingFishState == 3)
                            {
                                
                                Logger::Log("3");
                               // mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
                                //localRod->Server_ToggleReeling(false);
                            }

                            else if (localRod->ReplicatedFishState.FishingFishState == 5 && !localRod->PlayerIsBattlingFish)
                            {
                                Logger::Log("5");
                              //  mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
                                // Press all the keys up, disable the feature
                            }
                        }
                    }*/

                    if (cfg.aim.bEnable)
                    {
                        if (isCannon)
                        {
                            if (cfg.aim.cannon.b_chain_shots && actor->isShip())
                            {
                                do
                                {
                                    if (actor == localCharacter->GetCurrentShip())          //target is own ship
                                    {
                                        break;
                                    }
                                    
                                    /*
                                    if (actor->IsMastDown())          //target mast is down
                                    {
                                        break;
                                    }
                                    */

                                    FVector location = actor->K2_GetActorLocation();

                                    if (cfg.aim.cannon.bVisibleOnly && !localController->LineOfSightTo(actor, cameraLoc, false))
                                    {
                                        break;
                                    }

                                    if (location.DistTo(cameraLoc) > 55000)                 //cannons have max range of around 500m
                                    {
                                        break;
                                    }

                                    int amount = 0;
                                    auto water = actor->GetInternalWater();
                                    amount = water->GetNormalizedWaterAmount() * 100.f;
                                    if (amount == 100)
                                        break;

                                    auto cannon = reinterpret_cast<ACannon*>(attachObject);

                                    float gravity_scale = cannon->ProjectileGravityScale;

                                    const FVector forward = actor->GetActorForwardVector();
                                    const FVector up = actor->GetActorUpVector();
                                    const FVector loc = actor->K2_GetActorLocation();

                                    FVector loc_mast = loc;

                                    loc_mast += forward * 80.f;
                                    loc_mast += up * 1300.f;

                                    location = loc_mast;

                                    gravity_scale = 1.f;

                                    FRotator low, high;
                                    int i_solutions = AimAtMovingTarget(location, actor->GetVelocity(), cannon->ProjectileSpeed, gravity_scale, cameraLoc, attachObject->GetVelocity(), low, high);
                                    if (i_solutions < 1)                                    //no valid angle found
                                        break;

                                    low.Clamp();
                                    low -= attachObject->K2_GetActorRotation();
                                    low.Clamp();

                                    float absPitch = abs(low.Pitch);
                                    float absYaw = abs(low.Yaw);
                                    if (absPitch > cfg.aim.cannon.fPitch || absYaw > cfg.aim.cannon.fYaw) { break; }
                                    float sum = absYaw + absPitch;  //ok   
                                    if (sum < aimBest.best)
                                    {
                                        aimBest.target = actor;
                                        aimBest.location = location;
                                        aimBest.delta = low;
                                        aimBest.best = sum;
                                    }
                                } while (false);
                            }

                            if (cfg.aim.cannon.playeraimbot && cfg.aim.cannon.b_chain_shots == false && actor->isPlayer() && actor != localCharacter && !actor->IsDead())
                            {
                                do
                                {
                                    /*
                                    if (actor == localCharacter->GetCurrentShip())          //target is own ship
                                    {
                                        break;
                                    }
                                    */

                                    if (!cfg.aim.players.bTeam) if (UCrewFunctions::AreCharactersInSameCrew(actor, localCharacter)) break;

                                    FVector location = actor->K2_GetActorLocation();

                                    if (location.DistTo(cameraLoc) > 55000)                 //cannons have max range of around 500m
                                    {
                                        break;
                                    }

                                    auto cannon = reinterpret_cast<ACannon*>(attachObject);

                                    float gravity_scale = cannon->ProjectileGravityScale;

                                    FRotator low, high;
                                    int i_solutions = AimAtMovingTarget(location, actor->GetVelocity(), cannon->ProjectileSpeed, gravity_scale, cameraLoc, attachObject->GetForwardVelocity(), low, high);
                                    if (i_solutions < 1)                                    //no valid angle found
                                        break;

                                    low.Clamp();
                                    low -= attachObject->K2_GetActorRotation();
                                    low.Clamp();

                                    float absPitch = abs(low.Pitch);
                                    float absYaw = abs(low.Yaw);
                                    if (absPitch > cfg.aim.cannon.fPitch || absYaw > cfg.aim.cannon.fYaw) { break; }
                                    float sum = absYaw + absPitch;  //ok   
                                    if (sum < aimBest.best)
                                    {
                                        aimBest.target = actor;
                                        aimBest.location = location;
                                        aimBest.delta = low;
                                        aimBest.best = sum;
                                    }
                                } while (false);
                            }

                            if (cfg.aim.cannon.skeletonaimbot && cfg.aim.cannon.b_chain_shots == false && actor->isSkeleton() && actor != localCharacter && !actor->IsDead() && !localController->LineOfSightTo(actor, cameraLoc, false))
                            {
                                do
                                {
                                    /*
                                    if (actor == localCharacter->GetCurrentShip())          //target is own ship
                                    {w
                                        break;
                                    }
                                    */

                                    FVector location = actor->K2_GetActorLocation();

                                    if (location.DistTo(cameraLoc) > 55000)                 //cannons have max range of around 500m
                                    {
                                        break;
                                    }

                                    auto cannon = reinterpret_cast<ACannon*>(attachObject);

                                    float gravity_scale = cannon->ProjectileGravityScale;

                                    FRotator low, high;
                                    int i_solutions = AimAtMovingTarget(location, actor->GetVelocity(), cannon->ProjectileSpeed, gravity_scale, cameraLoc, attachObject->GetForwardVelocity(), low, high);
                                    if (i_solutions < 1)                                    //no valid angle found
                                        break;

                                    low.Clamp();
                                    low -= attachObject->K2_GetActorRotation();
                                    low.Clamp();

                                    float absPitch = abs(low.Pitch);
                                    float absYaw = abs(low.Yaw);
                                    if (absPitch > cfg.aim.cannon.fPitch || absYaw > cfg.aim.cannon.fYaw) { break; }
                                    float sum = absYaw + absPitch;  //ok   
                                    if (sum < aimBest.best)
                                    {
                                        aimBest.target = actor;
                                        aimBest.location = location;
                                        aimBest.delta = low;
                                        aimBest.best = sum;
                                    }
                                } while (false);
                            }


                            if (cfg.aim.cannon.b_chain_shots == false && actor->isShip())
                            {
                                do
                                {
                                    if (actor == localCharacter->GetCurrentShip())          //target is own ship
                                    {
                                        break;
                                    }

                                    FVector location = actor->K2_GetActorLocation();

                                    if (cfg.aim.cannon.bVisibleOnly && !localController->LineOfSightTo(actor, cameraLoc, false))
                                    {
                                        break;
                                    }

                                    if (location.DistTo(cameraLoc) > 55000)                 //cannons have max range of around 500m
                                    {
                                        break;
                                    }

                                    auto cannon = reinterpret_cast<ACannon*>(attachObject);
                                    
                                    int amount = 0;
                                    auto water = actor->GetInternalWater();
                                    amount = water->GetNormalizedWaterAmount() * 100.f;
                                    if (amount == 100)
                                        break;
                                    
                                    float gravity_scale = cannon->ProjectileGravityScale;
                                    if (cfg.aim.cannon.deckshots)
                                    {
                                        const FVector forward = actor->GetActorForwardVector();
                                        const FVector up = actor->GetActorUpVector();
                                        const FVector loc = actor->K2_GetActorLocation();
                                        FVector loc_mast = loc;
                                        loc_mast += forward * 52.f;
                                        loc_mast += up * 275.f;
                                        location = loc_mast;
                                        gravity_scale = 1.30f;
                                    }
                                    else if (cfg.aim.cannon.lowAim)
                                    {
                                        auto const damage = actor->GetHullDamage();
                                        if (damage)
                                        {
                                            FVector loc = pickHoleToAim(damage, localLoc);
                                            if (loc.Sum() != 9999.f)
                                                location = loc;
                                        }
                                    }
                                    else if (cfg.aim.cannon.randomshots)
                                    {
                                            static std::uintptr_t desiredTime = 0; // Delaying it like this because I'm running the whole cheat inside of a loop (using sleep will cause everything to pause)
                                            if (milliseconds_now() >= desiredTime)
                                            {
                                                fn();
                                                desiredTime = milliseconds_now() + 2000; // Delay
                                            }

                                            const FVector forward = actor->GetActorForwardVector(); // Target Forward Vector
                                            const FVector target = actor->K2_GetActorLocation(); // Target Location

                                            FVector loc_target = target;

                                            loc_target += forward * randomnumber;

                                            location = loc_target;

                                    }

                                    FRotator low, high;
                                    int i_solutions = AimAtMovingTarget(location, actor->GetVelocity(), cannon->ProjectileSpeed, gravity_scale, cameraLoc, attachObject->GetVelocity(), low, high);
                                    if (i_solutions < 1)                                    //no valid angle found
                                        break;

                                    low.Clamp();
                                    low -= attachObject->K2_GetActorRotation();
                                    low.Clamp();

                                    float absPitch = abs(low.Pitch);
                                    float absYaw = abs(low.Yaw);
                                    if (absPitch > cfg.aim.cannon.fPitch || absYaw > cfg.aim.cannon.fYaw) { break; }
                                    float sum = absYaw + absPitch;  //ok   
                                    if (sum < aimBest.best)
                                    {
                                        aimBest.target = actor;
                                        aimBest.location = location;
                                        aimBest.delta = low;
                                        aimBest.best = sum;
                                    }
                                } while (false);
                            }
                        }
                        else if (isHarpoon)    //todo:fix FRotator offset
                        {
                            if (actor->isItem())
                            {
                                do
                                {
                                    FVector location = actor->K2_GetActorLocation();
                        
                                   float dist = cameraLoc.DistTo(location);
                                    if (dist > 7770.f || dist < 260.f) { break; }
                                    if (cfg.aim.harpoon.bVisibleOnly) if (!localController->LineOfSightTo(actor, cameraLoc, false)) { break; }
                                    auto harpoon = reinterpret_cast<AHarpoonLauncher*>(attachObject);
                                    auto center = UKismetMathLibrary::NormalizedDeltaRotator(cameraRot, harpoon->rotation);
                                    FRotator delta = UKismetMathLibrary::NormalizedDeltaRotator(UKismetMathLibrary::FindLookAtRotation(cameraLoc, location), center);
                                   if (delta.Pitch < -35.f || delta.Pitch > 67.f || abs(delta.Yaw) > 50.f) { break; }
                                    FRotator diff = delta - harpoon->rotation;
                                    float absPitch = abs(diff.Pitch);
                                    float absYaw = abs(diff.Yaw);
                                    if (absPitch > cfg.aim.harpoon.fPitch || absYaw > cfg.aim.harpoon.fYaw) { break; }
                                    float sum = absYaw + absPitch;
                                    if (sum < aimBest.best)
                                    {
                                        aimBest.target = actor;
                                        aimBest.location = location;
                                        aimBest.delta = delta;
                                        aimBest.best = sum;
                                    }
                        
                                } while (false);
                            }
                        }

                        else if (!attachObject && isWieldedWeapon)
                        {
                            if (cfg.aim.players.bEnable && actor->isPlayer() && actor != localCharacter && !actor->IsDead())
                            {
                                do
                                {
                                    FVector playerLoc = actor->K2_GetActorLocation();
                                    if (!actor->IsInWater() && localWeapon->WeaponParameters.NumberOfProjectiles == 1)
                                    {
                                        playerLoc.Z += cfg.aim.players.fAimHeight;
                                    }

                                    float dist = localLoc.DistTo(playerLoc);
                                    if (dist > localWeapon->WeaponParameters.ProjectileMaximumRange) { break; }

                                    if (cfg.aim.players.bVisibleOnly) if (!localController->LineOfSightTo(actor, cameraLoc, false)) { break; }
                                    if (!cfg.aim.players.bTeam) if (UCrewFunctions::AreCharactersInSameCrew(actor, localCharacter)) break;

                                    FRotator rotationDelta = UKismetMathLibrary::NormalizedDeltaRotator(UKismetMathLibrary::FindLookAtRotation(cameraLoc, playerLoc), cameraRot);

                                    float absYaw = abs(rotationDelta.Yaw);
                                    float absPitch = abs(rotationDelta.Pitch);
                                    if (absYaw > cfg.aim.players.fYaw || absPitch > cfg.aim.players.fPitch) { break; }
                                    float sum = absYaw + absPitch;

                                    if (sum < aimBest.best)
                                    {
                                        aimBest.target = actor;
                                        aimBest.location = playerLoc;
                                        aimBest.delta = rotationDelta;
                                        aimBest.best = sum;
                                        aimBest.smoothness = cfg.aim.players.fSmoothness;
                                    }

                                } while (false);
                            }

                            else if (cfg.aim.kegs.bEnable && actor->isKeg())
                            {
                                do
                                {
                                    const FVector playerLoc = actor->K2_GetActorLocation();
                                    const float dist = localLoc.DistTo(playerLoc);

                                    if (dist > localWeapon->WeaponParameters.ProjectileMaximumRange) break;
                                    if (cfg.aim.skeletons.bVisibleOnly) if (!localController->LineOfSightTo(actor, cameraLoc, false)) break;

                                    const FRotator rotationDelta = UKismetMathLibrary::NormalizedDeltaRotator(UKismetMathLibrary::FindLookAtRotation(cameraLoc, playerLoc), cameraRot);

                                    const float absYaw = abs(rotationDelta.Yaw);
                                    const float absPitch = abs(rotationDelta.Pitch);
                                    if (absYaw > cfg.aim.skeletons.fYaw || absPitch > cfg.aim.skeletons.fPitch) break;
                                    const float sum = absYaw + absPitch;

                                    if (sum < aimBest.best)
                                    {
                                        aimBest.target = actor;
                                        aimBest.location = playerLoc;
                                        aimBest.delta = rotationDelta;
                                        aimBest.best = sum;
                                        aimBest.smoothness = cfg.aim.skeletons.fSmoothness;
                                    }

                                } while (false);
                            }

                            else if (cfg.aim.skeletons.bEnable && actor->isSkeleton() && !actor->IsDead())
                            {
                                do
                                {
                                    FVector playerLoc = actor->K2_GetActorLocation();
                                    if (localWeapon->WeaponParameters.NumberOfProjectiles == 1)
                                    playerLoc.Z += cfg.aim.skeletons.fAimHeight;

                                    const float dist = localLoc.DistTo(playerLoc);

                                    if (dist > localWeapon->WeaponParameters.ProjectileMaximumRange) break;
                                    if (cfg.aim.skeletons.bVisibleOnly) if (!localController->LineOfSightTo(actor, cameraLoc, false)) break;

                                    const FRotator rotationDelta = UKismetMathLibrary::NormalizedDeltaRotator(UKismetMathLibrary::FindLookAtRotation(cameraLoc, playerLoc), cameraRot);

                                    const float absYaw = abs(rotationDelta.Yaw);
                                    const float absPitch = abs(rotationDelta.Pitch);
                                    if (absYaw > cfg.aim.skeletons.fYaw || absPitch > cfg.aim.skeletons.fPitch) break;
                                    const float sum = absYaw + absPitch;

                                    if (sum < aimBest.best)
                                    {
                                        aimBest.target = actor;
                                        aimBest.location = playerLoc;
                                        aimBest.delta = rotationDelta;
                                        aimBest.best = sum;
                                        aimBest.smoothness = cfg.aim.skeletons.fSmoothness;
                                    }

                                } while (false);
                            }
                        }
                    }
                }
            }

            if (aimBest.target != nullptr)
            {
                FVector2D screen;
                if (localController->ProjectWorldLocationToScreen(aimBest.location, screen))
                {
                    auto col = ImGui::GetColorU32(IM_COL32(0, 200, 0, 255));
                    drawList->AddLine({ io.DisplaySize.x * 0.5f , io.DisplaySize.y * 0.5f }, { screen.X, screen.Y }, col);
                    drawList->AddCircle({ screen.X, screen.Y }, 3.f, col);
                }
                if (localController->ProjectWorldLocationToScreen(aimBest.location, screen))
                {
                }

                if (ImGui::IsMouseDown(1))
                {
                    if (isCannon)
                    {
                        auto cannon = reinterpret_cast<ACannon*>(attachObject);
                        if (cannon)
                        {
                            if (((aimBest.delta.Pitch > cannon->PitchRange.max) || (aimBest.delta.Pitch < cannon->PitchRange.min)) || ((aimBest.delta.Yaw > cannon->YawRange.max) || (aimBest.delta.Yaw < cannon->YawRange.min)))
                            {
                                std::string str_text_message = "TARGET IS OUT OF RANGE!";
                                drawList->AddText({ io.DisplaySize.x * 0.5f , io.DisplaySize.y * 0.5f + 30.f }, 0xFFFFFFFF, str_text_message.c_str());
                            }
                            else
                            {
                                cannon->ForceAimCannon(aimBest.delta.Pitch, aimBest.delta.Yaw);

                                if (cfg.aim.cannon.b_instant_shoot && cannon->IsReadyToFire())
                                {
                                    cannon->Fire();
                                }
                            }
                        }
                    }
                    else if (isHarpoon)
                    {
                        reinterpret_cast<AHarpoonLauncher*>(attachObject)->rotation = aimBest.delta;
                    }
                    else
                    {
                        /*
                        * LV - Local velocity
                        * TV - Target velocity
                        * RV - Target relative velocity
                        * BS - Bullet speed
                        * RL - Relative local location
                        */
                        FVector LV = localCharacter->GetVelocity();
                        if (auto const localShip = localCharacter->GetCurrentShip()) LV += localShip->GetVelocity();
                        FVector TV = aimBest.target->GetVelocity();
                        if (auto const targetShip = aimBest.target->GetCurrentShip()) TV += targetShip->GetVelocity();
                        const FVector RV = TV - LV;
                        const float BS = localWeapon->WeaponParameters.AmmoParams.Velocity;
                        const FVector RL = localLoc - aimBest.location;
                        const float a = RV.Size() - BS * BS;
                        const float b = (RL * RV * 2.f).Sum();
                        const float c = RL.SizeSquared();
                        const float D = b*b - 4 * a * c;
                        if (D > 0)
                        {
                            const float DRoot = sqrtf(D);
                            const float x1 = (-b + DRoot) / (2 * a);
                            const float x2 = (-b - DRoot) / (2 * a);
                            if (x1 >= 0 && x1 >= x2) aimBest.location += RV * x1;
                            else if (x2 >= 0) aimBest.location += RV * x2;

                            aimBest.delta = UKismetMathLibrary::NormalizedDeltaRotator(UKismetMathLibrary::FindLookAtRotation(cameraLoc, aimBest.location), cameraRot);
                            auto smoothness = 1.f / aimBest.smoothness;
                            localController->AddYawInput(aimBest.delta.Yaw * smoothness);
                            localController->AddPitchInput(aimBest.delta.Pitch * -smoothness);
                        }

                    }
                }
            }

        } while (false);
    }
    catch (...) 
    {
        // todo: somehow get the address where the error occurred
        Logger::Log("Exception\n");
    }

    ImGui::End();
    ImGui::PopStyleColor();
    ImGui::PopStyleVar(2);
    ImGui::PopFont();


    
    
#ifdef STEAM
    if (ImGui::IsKeyPressed(VK_INSERT)) bIsOpen = !bIsOpen;
#else
    // if you would like to have full input in UWP version: reverse game and find array of key states (see: https://github.com/MICROSOFT-XBOX-ATG/MICROSOFT_UWP_UNREAL/blob/release_uwp/Engine/Source/Runtime/ApplicationCore/Private/UWP/UWPInputInterface.cpp#L9). 
    static const FKey insert("Insert");
    if (cache.localController && cache.localController->WasInputKeyJustPressed(insert)) { bIsOpen = !bIsOpen; } // todo: change this shit
#endif

    if (bIsOpen) {
        ImGui::SetNextWindowSize(ImVec2(1375, 825), ImGuiCond_Once);
        ImGui::PushFont(title_font);
        ImGui::Begin("Placeholder", 0, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
        ImGui::PopFont();


        ImGuiStyle* style = &ImGui::GetStyle();

        style->WindowPadding = ImVec2(8, 8);
        style->WindowRounding = 0.0f;
        style->FramePadding = ImVec2(4, 3);
        style->FrameRounding = 2.0f;
        style->ItemSpacing = ImVec2(6, 4);
        style->ItemInnerSpacing = ImVec2(4, 4);
        style->IndentSpacing = 20.0f;
        style->ScrollbarSize = 14.0f;
        style->ScrollbarRounding = 0.0f;
        style->GrabMinSize = 5.0f;
        style->GrabRounding = 0.0f;
        style->WindowBorderSize = 1;
        style->WindowTitleAlign = ImVec2(0.5f, 0.5f);
        style->FramePadding = ImVec2(4, 3);
        style->TabRounding = 0.0f;

        style->Colors[ImGuiCol_TitleBg] = ImColor(50, 50, 50, 255);
        style->Colors[ImGuiCol_TitleBgActive] = ImColor(50, 50, 50, 255);
        //style->Colors[ImGuiCol_Text] = ImColor(255, 20, 147, 255);

        style->Colors[ImGuiCol_Button] = ImColor(255, 20, 147, 225);
        style->Colors[ImGuiCol_ButtonActive] = ImColor(255, 20, 147, 225);
        style->Colors[ImGuiCol_ButtonHovered] = ImColor(41, 40, 41, 255);

        style->Colors[ImGuiCol_Separator] = ImColor(70, 70, 70, 255);
        style->Colors[ImGuiCol_SeparatorActive] = ImColor(76, 76, 76, 255);
        style->Colors[ImGuiCol_SeparatorHovered] = ImColor(76, 76, 76, 255);

        style->Colors[ImGuiCol_Tab] = ImColor(40, 40, 40, 255);
        style->Colors[ImGuiCol_TabHovered] = ImColor(255, 20, 147, 225);
        style->Colors[ImGuiCol_TabActive] = ImColor(70, 70, 70, 255);

        style->Colors[ImGuiCol_SliderGrab] = ImColor(255, 20, 147, 225);
        style->Colors[ImGuiCol_SliderGrabActive] = ImColor(255, 50, 147, 225);


        style->Colors[ImGuiCol_MenuBarBg] = ImColor(76, 76, 76, 255);

        style->Colors[ImGuiCol_FrameBg] = ImColor(37, 36, 37, 255);
        style->Colors[ImGuiCol_FrameBgActive] = ImColor(37, 36, 37, 255);
        style->Colors[ImGuiCol_FrameBgHovered] = ImColor(37, 36, 37, 255);

        style->Colors[ImGuiCol_Header] = ImColor(0, 0, 0, 0);
        style->Colors[ImGuiCol_HeaderActive] = ImColor(0, 0, 0, 0);
        style->Colors[ImGuiCol_HeaderHovered] = ImColor(46, 46, 46, 255);

        style->Colors[ImGuiCol_CheckMark] = ImColor(255, 20, 147, 225);

        style->Colors[ImGuiCol_WindowBg] = ImColor(40, 40, 40, 255);
        ImGui::PushFont(font);
        //ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(255, 255, 255, 255));


        ImGui::Columns(2);
        ImGui::SetColumnOffset(1, 173);

        renderPanel();

        {// Right side
            ImGui::NextColumn();
            ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 0.0f);
            switch (selectedTab) {
            case 0: {
                renderSubTab0();
                break;
            }
            case 1: {
                renderSubTab1();
                break;
            }
            case 2: {
                renderSubTab2();
                break;
            }
            case 3: {
                renderSubTab3();
                //Config::i().renderImGui();// for config, save current(new), load, delete, duplicate, overwrite
                break;
            }
            }
            ImGui::PopStyleVar();
        }
        /*if (ImGui::BeginTabBar("Bars")) {
            if (ImGui::BeginTabItem(ICON_FA_EYE " Visuals")) 
            {
                ImGui::Text("Global Visuals");
                if (ImGui::BeginChild("Global", ImVec2(0.f, 0.f), false, 0))
                {
                    ImGui::Checkbox("Enable", &cfg.visuals.bEnable);
                    ImGui::Checkbox("Text Outlines", &cfg.visuals.textoutlines);
                    ImGui::Columns(3, "CLM1", false);
                    const char* boxes[] = { "None", "2DBox", "3DBox" };

                        ImGui::Text("Players");
                        if (ImGui::BeginChild("PlayersSettings", ImVec2(0.f, 200.f), true, 0 | ImGuiWindowFlags_NoScrollWithMouse))
                        {
                            const char* bars[] = { "None", "2DRectLeft", "2DRectRight", "2DRectBottom", "2DRectTop" };
                            ImGui::Checkbox("Enable", &cfg.visuals.players.bEnable);
                            ImGui::Checkbox("Draw Teammates", &cfg.visuals.players.bDrawTeam);
                            ImGui::Checkbox("Draw Name", &cfg.visuals.players.bName);
                            //ImGui::Checkbox("Draw Weapon Name WIP ", &cfg.visuals.players.bWeaponanmes);
                            ImGui::Checkbox("Draw Skeleton WIP ", &cfg.visuals.players.bSkeleton);
                            ImGui::Combo("Box Type", reinterpret_cast<int*>(&cfg.visuals.players.boxType), boxes, IM_ARRAYSIZE(boxes));
                            ImGui::Combo("Health Bar Type", reinterpret_cast<int*>(&cfg.visuals.players.barType), bars, IM_ARRAYSIZE(bars));
                            ImGui::ColorEdit4("Visible Enemy Color", &cfg.visuals.players.enemyColorVis.x, 0);
                            ImGui::ColorEdit4("Invisible Enemy Color", &cfg.visuals.players.enemyColorInv.x, 0);
                            ImGui::ColorEdit4("Visible Team Color", &cfg.visuals.players.teamColorVis.x, 0);
                            ImGui::ColorEdit4("Invisible Team Color", &cfg.visuals.players.teamColorInv.x, 0);
                            ImGui::ColorEdit4("Text Color", &cfg.visuals.players.textCol.x, 0);
                            ImGui::SliderFloat("Draw Distance", &cfg.visuals.players.drawdistance, 0.f, 5000.f, "%.0f");
                        }
                        ImGui::EndChild();

                        ImGui::NextColumn();

                        ImGui::Text("Skeletons");
                        if (ImGui::BeginChild("SkeletonsSettings", ImVec2(0.f, 200.f), true, 0 | ImGuiWindowFlags_NoScrollWithMouse))
                        {
                            ImGui::Checkbox("Enable", &cfg.visuals.skeletons.bEnable);
                            ImGui::Checkbox("Draw Name", &cfg.visuals.skeletons.bName);
                            ImGui::Combo("Box Type", reinterpret_cast<int*>(&cfg.visuals.skeletons.boxType), boxes, IM_ARRAYSIZE(boxes));
                            ImGui::ColorEdit4("Visible Color", &cfg.visuals.skeletons.colorVis.x, 0);
                            ImGui::ColorEdit4("Invisible Color", &cfg.visuals.skeletons.colorInv.x, 0);
                            ImGui::ColorEdit4("Text Color", &cfg.visuals.skeletons.textCol.x, 0);
                            ImGui::SliderFloat("Draw Distance", &cfg.visuals.skeletons.drawdistance, 0.f, 5000.f, "%.0f");

                        }
                        ImGui::EndChild();

                        ImGui::NextColumn();

                        ImGui::Text("Ships");
                        if (ImGui::BeginChild("ShipsSettings", ImVec2(0.f, 200.f), true, 0 | ImGuiWindowFlags_NoScrollWithMouse)) {

                            ImGui::Checkbox("Enable", &cfg.visuals.ships.bEnable);
                            ImGui::Checkbox("Draw Name", &cfg.visuals.ships.bName);
                            ImGui::Checkbox("Show Holes", &cfg.visuals.ships.bDamage);
                            ImGui::ColorEdit4("Damage Color", &cfg.visuals.ships.damageColor.x, 0);
                            ImGui::ColorEdit4("Text Color", &cfg.visuals.ships.textCol.x, 0);
                        }
                        ImGui::EndChild();

                        ImGui::NextColumn();

                        ImGui::Text("Islands");
                        if (ImGui::BeginChild("IslandsSettings", ImVec2(0.f, 200.f), true, 0 | ImGuiWindowFlags_NoScrollWithMouse))
                        {
                            ImGui::Checkbox("Enable", &cfg.visuals.islands.bEnable);
                            ImGui::Checkbox("Draw Names", &cfg.visuals.islands.bName);
                            ImGui::SliderInt("Max Distance", &cfg.visuals.islands.intMaxDist, 100, 2750, "%d", ImGuiSliderFlags_AlwaysClamp);
                            ImGui::ColorEdit4("Text Color", &cfg.visuals.islands.textCol.x, 0);
                        }
                        ImGui::EndChild();

                        ImGui::NextColumn();

                        ImGui::Text("Items");
                        if (ImGui::BeginChild("ItemsSettings", ImVec2(0.f, 200.f), true, 0 | ImGuiWindowFlags_NoScrollWithMouse))
                        {
                            ImGui::Checkbox("Enable", &cfg.visuals.items.bEnable);
                            ImGui::Checkbox("Draw Name", &cfg.visuals.items.bName);
                            ImGui::Checkbox("Barrels", &cfg.visuals.items.barrelitems);
                            ImGui::Checkbox("Ammo Chests", &cfg.visuals.items.ammochests);
                            ImGui::ColorEdit4("Text Color", &cfg.visuals.items.textCol.x, 0);
                            ImGui::ColorEdit4("Barrel Text Color", &cfg.visuals.items.barreltextCol.x, 0);
                            ImGui::ColorEdit4("Ammo Chest Text Color", &cfg.visuals.items.ammotextCol.x, 0);
                            ImGui::SliderFloat("Item Draw Distance", &cfg.visuals.items.itemdrawdistance, 0.f, 5000.f, "%.0f");
                            ImGui::SliderFloat("Barrel Draw Distance", &cfg.visuals.items.barreldrawdistance, 0.f, 5000.f, "%.0f");
                            ImGui::SliderFloat("Ammochest Draw Distance", &cfg.visuals.items.ammochestsdrawdistance, 0.f, 5000.f, "%.0f");
                        }
                        ImGui::EndChild();

                        ImGui::NextColumn();

                        ImGui::Text("Animals");
                        if (ImGui::BeginChild("AnimalsSettings", ImVec2(0.f, 200.f), true, 0 | ImGuiWindowFlags_NoScrollWithMouse))
                        {
                            ImGui::Checkbox("Enable", &cfg.visuals.animals.bEnable);
                            ImGui::Checkbox("Draw Name", &cfg.visuals.animals.bName);
                            ImGui::ColorEdit4("Text Color", &cfg.visuals.animals.textCol.x, 0);
                            ImGui::SliderFloat("Draw Distance", &cfg.visuals.animals.drawdistance, 0.f, 5000.f, "%.0f");
                        }
                        ImGui::EndChild();

                        ImGui::NextColumn();

                        ImGui::Text("Megalodon");
                        if (ImGui::BeginChild("MegalodonSettings", ImVec2(0.f, 200.f), true, 0 | ImGuiWindowFlags_NoScrollWithMouse))
                        {
                            ImGui::Checkbox("Enable", &cfg.visuals.megalodon.bEnable);
                            ImGui::Checkbox("Draw Name", &cfg.visuals.megalodon.bName);
                            ImGui::ColorEdit4("Text Color", &cfg.visuals.megalodon.textCol.x, 0);
                            ImGui::SliderFloat("Draw Distance", &cfg.visuals.megalodon.drawdistance, 0.f, 5000.f, "%.0f");
                        }
                        ImGui::EndChild();

                        ImGui::NextColumn();

                        ImGui::Text("Sharks");
                        if (ImGui::BeginChild("SharksSettings", ImVec2(0.f, 200.f), true, 0 | ImGuiWindowFlags_NoScrollWithMouse))
                        {
                            ImGui::Checkbox("Enable", &cfg.visuals.sharks.bEnable);
                            ImGui::Checkbox("Draw Name", &cfg.visuals.sharks.bName);
                            ImGui::ColorEdit4("Text Color", &cfg.visuals.sharks.textCol.x, 0);
                            ImGui::SliderFloat("Draw Distance", &cfg.visuals.sharks.drawdistance, 0.f, 5000.f, "%.0f");
                        }
                        ImGui::EndChild();

                        ImGui::NextColumn();

                        ImGui::Text("Mermaids");
                        if (ImGui::BeginChild("MermaidsSettings", ImVec2(0.f, 200.f), true, 0 | ImGuiWindowFlags_NoScrollWithMouse))
                        {
                            ImGui::Checkbox("Enable", &cfg.visuals.mermaids.bEnable);
                            ImGui::Checkbox("Draw Name", &cfg.visuals.mermaids.bName);
                            ImGui::ColorEdit4("Text Color", &cfg.visuals.mermaids.textCol.x, 0);
                            ImGui::SliderFloat("Draw Distance", &cfg.visuals.mermaids.drawdistance, 0.f, 5000.f, "%.0f");
                        }
                        ImGui::EndChild();

                        ImGui::NextColumn();

                        ImGui::Text("Rowboats");
                        if (ImGui::BeginChild("RowboatsSettings", ImVec2(0.f, 200.f), true, 0 | ImGuiWindowFlags_NoScrollWithMouse))
                        {
                            ImGui::Checkbox("Enable", &cfg.visuals.rowboats.bEnable);
                            ImGui::Checkbox("Draw Name", &cfg.visuals.rowboats.bName);
                            ImGui::ColorEdit4("Text Color", &cfg.visuals.rowboats.textCol.x, 0);
                            ImGui::SliderFloat("Draw Distance", &cfg.visuals.rowboats.drawdistance, 0.f, 5000.f, "%.0f");
                        }
                        ImGui::EndChild();

                        ImGui::NextColumn();

                        ImGui::Text("Puzzles");
                        if (ImGui::BeginChild("PuzzlesSettings", ImVec2(0.f, 200.f), true, 0 | ImGuiWindowFlags_NoScrollWithMouse))
                        {

                            ImGui::Checkbox("Enable", &cfg.visuals.puzzles.bEnable);
                            ImGui::Checkbox("Draw Doors", &cfg.visuals.puzzles.bDoor);
                            ImGui::ColorEdit4("Text Color", &cfg.visuals.puzzles.textCol.x, 0);
                            ImGui::SliderFloat("Draw Distance", &cfg.visuals.puzzles.drawdistance, 0.f, 5000.f, "%.0f");

                        }
                        ImGui::EndChild();

                        ImGui::NextColumn();

                        ImGui::Text("Shipwrecks");
                        if (ImGui::BeginChild("ShipwrecksSettings", ImVec2(0.f, 200.f), true, 0 | ImGuiWindowFlags_NoScrollWithMouse))
                        {
                            ImGui::Checkbox("Enable", &cfg.visuals.shipwrecks.bEnable);
                            ImGui::Checkbox("Draw Name", &cfg.visuals.shipwrecks.bName);
                            ImGui::ColorEdit4("Text Color", &cfg.visuals.shipwrecks.textCol.x, 0);
                            ImGui::SliderFloat("Draw Distance", &cfg.visuals.shipwrecks.drawdistance, 0.f, 5000.f, "%.0f");
                        }
                        ImGui::EndChild();

                        ImGui::NextColumn();

                        ImGui::Text("Client");
                        if (ImGui::BeginChild("ClientSettings", ImVec2(0.f, 200.f), true, 0 | ImGuiWindowFlags_NoScrollWithMouse))
                        {
                            ImGui::Checkbox("Enable", &cfg.visuals.client.bEnable);
                            ImGui::Checkbox("Crosshair", &cfg.visuals.client.bCrosshair);
                            if (cfg.visuals.client.bCrosshair)
                            {
                                ImGui::SameLine();
                                ImGui::SetNextItemWidth(75.f);
                                ImGui::SliderFloat("Radius##1", &cfg.visuals.client.fCrosshair, 1.f, 100.f);
                            }
                            ImGui::ColorEdit4("Crosshair Color", &cfg.visuals.client.crosshairColor.x, ImGuiColorEditFlags_DisplayRGB);

                            ImGui::Checkbox("Oxygen Level", &cfg.visuals.client.bOxygen);
                            ImGui::Checkbox("Compass", &cfg.visuals.client.bCompass);

                            ImGui::Checkbox("Debug", &cfg.visuals.client.bDebug);
                            if (cfg.visuals.client.bDebug)
                            {
                                ImGui::SameLine();
                                ImGui::SetNextItemWidth(150.f);
                                ImGui::SliderFloat("Radius##2", &cfg.visuals.client.fDebug, 1.f, 1000.f);
                            }

                            ImGui::Checkbox("Cannon Tracers", &cfg.visuals.client.b_cannon_tracers);
                            ImGui::SliderInt("Tracer Length", &cfg.visuals.client.cannon_tracers_length, 1, 400, "%d");
                            ImGui::ColorEdit4("Tracer Color", &cfg.visuals.client.cannon_tracers_color.x, ImGuiColorEditFlags_DisplayRGB);
                        }
                        ImGui::EndChild();

                        ImGui::NextColumn();

                        ImGui::Text("Ship Radar");
                        if (ImGui::BeginChild("RadarSettings", ImVec2(0.f, 200.f), true, 0 | ImGuiWindowFlags_NoScrollWithMouse))
                        {
                            ImGui::Checkbox("Enable", &cfg.visuals.radar.bEnable);
                            ImGui::SliderInt("Radar Size", &cfg.visuals.radar.i_size, 100, 250);
                            ImGui::SliderInt("Radar Scale", &cfg.visuals.radar.i_scale, 10, 500);
                        }
                        ImGui::EndChild();

                        ImGui::NextColumn();
                        ImGui::Text("World Events");
                        if (ImGui::BeginChild("WorldSettings", ImVec2(0.f, 200.f), true, 0 | ImGuiWindowFlags_NoScrollWithMouse))
                        {
                            ImGui::Checkbox("Enable", &cfg.visuals.world.bEnable);
                            ImGui::ColorEdit4("Text Color", &cfg.visuals.world.textCol.x, 0);
                            ImGui::SliderFloat("Draw Distance", &cfg.visuals.world.drawdistance, 0.f, 20000.f, "%.0f");
                        }
                        ImGui::EndChild();

                        ImGui::NextColumn();
                        ImGui::Text("Seagulls");
                        if (ImGui::BeginChild("SeagullsSettings", ImVec2(0.f, 200.f), true, 0 | ImGuiWindowFlags_NoScrollWithMouse))
                        {
                            ImGui::Checkbox("Enable", &cfg.visuals.seagulls.bEnable);
                            ImGui::Checkbox("Draw Name", &cfg.visuals.seagulls.bName);
                            ImGui::ColorEdit4("Text Color", &cfg.visuals.seagulls.textCol.x, 0);
                            ImGui::SliderFloat("Draw Distance", &cfg.visuals.seagulls.drawdistance, 0.f, 20000.f, "%.0f");
                        }
                        ImGui::EndChild();


                        ImGui::NextColumn();
                        ImGui::Text("Storm");
                        if (ImGui::BeginChild("StormSettings", ImVec2(0.f, 200.f), true, 0 | ImGuiWindowFlags_NoScrollWithMouse))
                        {
                            ImGui::Checkbox("Enable", &cfg.visuals.storm.bEnable);
                            ImGui::Checkbox("Draw Name", &cfg.visuals.storm.bName);
                            ImGui::ColorEdit4("Text Color", &cfg.visuals.storm.textCol.x, 0);
                            ImGui::SliderFloat("Draw Distance", &cfg.visuals.storm.drawdistance, 0.f, 15000.f, "%.0f");
                        }
                        ImGui::EndChild();
                }
                ImGui::EndChild();

                ImGui::Columns(3, "CLM1", false);
                const char* boxes[] = { "None", "2DBox", "3DBox" };
                
                ImGui::Text("Players");
                if (ImGui::BeginChild("PlayersSettings", ImVec2(0.f, 200.f), true, 0 | ImGuiWindowFlags_NoScrollWithMouse))
                {
                    const char* bars[] = { "None", "2DRectLeft", "2DRectRight", "2DRectBottom", "2DRectTop" };
                    ImGui::Checkbox("Enable", &cfg.visuals.players.bEnable);
                    ImGui::Checkbox("Draw Teammates", &cfg.visuals.players.bDrawTeam);
                    ImGui::Checkbox("Draw Name", &cfg.visuals.players.bName);
                    //ImGui::Checkbox("Draw Weapon Name WIP ", &cfg.visuals.players.bWeaponanmes);
                    ImGui::Checkbox("Draw Skeleton WIP ", &cfg.visuals.players.bSkeleton);
                    ImGui::Combo("Box Type", reinterpret_cast<int*>(&cfg.visuals.players.boxType), boxes, IM_ARRAYSIZE(boxes));
                    ImGui::Combo("Health Bar Type", reinterpret_cast<int*>(&cfg.visuals.players.barType), bars, IM_ARRAYSIZE(bars));
                    ImGui::ColorEdit4("Visible Enemy Color", &cfg.visuals.players.enemyColorVis.x, 0);
                    ImGui::ColorEdit4("Invisible Enemy Color", &cfg.visuals.players.enemyColorInv.x, 0);
                    ImGui::ColorEdit4("Visible Team Color", &cfg.visuals.players.teamColorVis.x, 0);
                    ImGui::ColorEdit4("Invisible Team Color", &cfg.visuals.players.teamColorInv.x, 0);
                    ImGui::ColorEdit4("Text Color", &cfg.visuals.players.textCol.x, 0);
                    ImGui::SliderFloat("Draw Distance", &cfg.visuals.players.drawdistance, 0.f, 5000.f, "%.0f");
                }
                ImGui::EndChild();

                ImGui::NextColumn();

                ImGui::Text("Skeletons");
                if (ImGui::BeginChild("SkeletonsSettings", ImVec2(0.f, 200.f), true, 0 | ImGuiWindowFlags_NoScrollWithMouse))
                {
                    ImGui::Checkbox("Enable", &cfg.visuals.skeletons.bEnable);
                    ImGui::Checkbox("Draw Name", &cfg.visuals.skeletons.bName);
                    ImGui::Combo("Box Type", reinterpret_cast<int*>(&cfg.visuals.skeletons.boxType), boxes, IM_ARRAYSIZE(boxes));
                    ImGui::ColorEdit4("Visible Color", &cfg.visuals.skeletons.colorVis.x, 0);
                    ImGui::ColorEdit4("Invisible Color", &cfg.visuals.skeletons.colorInv.x, 0);
                    ImGui::ColorEdit4("Text Color", &cfg.visuals.skeletons.textCol.x, 0);
                    ImGui::SliderFloat("Draw Distance", &cfg.visuals.skeletons.drawdistance, 0.f, 5000.f, "%.0f");

                }
                ImGui::EndChild();

                ImGui::NextColumn();

                ImGui::Text("Ships");
                if (ImGui::BeginChild("ShipsSettings", ImVec2(0.f, 200.f), true, 0 | ImGuiWindowFlags_NoScrollWithMouse)) {

                    ImGui::Checkbox("Enable", &cfg.visuals.ships.bEnable);
                    ImGui::Checkbox("Draw Name", &cfg.visuals.ships.bName);
                    ImGui::Checkbox("Show Holes", &cfg.visuals.ships.bDamage);
                    ImGui::ColorEdit4("Damage Color", &cfg.visuals.ships.damageColor.x, 0);
                    ImGui::ColorEdit4("Text Color", &cfg.visuals.ships.textCol.x, 0);
                }
                ImGui::EndChild();

                ImGui::NextColumn();

                ImGui::Text("Islands");
                if (ImGui::BeginChild("IslandsSettings", ImVec2(0.f, 200.f), true, 0 | ImGuiWindowFlags_NoScrollWithMouse)) 
                {
                    ImGui::Checkbox("Enable", &cfg.visuals.islands.bEnable);
                    ImGui::Checkbox("Draw Names", &cfg.visuals.islands.bName);
                    ImGui::SliderInt("Max Distance", &cfg.visuals.islands.intMaxDist, 100, 2750, "%d", ImGuiSliderFlags_AlwaysClamp);
                    ImGui::ColorEdit4("Text Color", &cfg.visuals.islands.textCol.x, 0);
                }
                ImGui::EndChild();

                ImGui::NextColumn();

                ImGui::Text("Items");
                if (ImGui::BeginChild("ItemsSettings", ImVec2(0.f, 200.f), true, 0 | ImGuiWindowFlags_NoScrollWithMouse))
                {
                    ImGui::Checkbox("Enable", &cfg.visuals.items.bEnable);
                    ImGui::Checkbox("Draw Name", &cfg.visuals.items.bName);
                    ImGui::Checkbox("Barrels", &cfg.visuals.items.barrelitems);
                    ImGui::Checkbox("Ammo Chests", &cfg.visuals.items.ammochests);
                    ImGui::ColorEdit4("Text Color", &cfg.visuals.items.textCol.x, 0);
                    ImGui::ColorEdit4("Barrel Text Color", &cfg.visuals.items.barreltextCol.x, 0);
                    ImGui::ColorEdit4("Ammo Chest Text Color", &cfg.visuals.items.ammotextCol.x, 0);
                    ImGui::SliderFloat("Item Draw Distance", &cfg.visuals.items.itemdrawdistance, 0.f, 5000.f, "%.0f");
                    ImGui::SliderFloat("Barrel Draw Distance", &cfg.visuals.items.barreldrawdistance, 0.f, 5000.f, "%.0f");
                    ImGui::SliderFloat("Ammochest Draw Distance", &cfg.visuals.items.ammochestsdrawdistance, 0.f, 5000.f, "%.0f");
                }
                ImGui::EndChild();

                ImGui::NextColumn();

                ImGui::Text("Animals");
                if (ImGui::BeginChild("AnimalsSettings", ImVec2(0.f, 200.f), true, 0 | ImGuiWindowFlags_NoScrollWithMouse))
                {
                    ImGui::Checkbox("Enable", &cfg.visuals.animals.bEnable);
                    ImGui::Checkbox("Draw Name", &cfg.visuals.animals.bName);
                    ImGui::ColorEdit4("Text Color", &cfg.visuals.animals.textCol.x, 0);
                    ImGui::SliderFloat("Draw Distance", &cfg.visuals.animals.drawdistance, 0.f, 5000.f, "%.0f");
                }
                ImGui::EndChild();

                ImGui::NextColumn();

                ImGui::Text("Megalodon");
                if (ImGui::BeginChild("MegalodonSettings", ImVec2(0.f, 200.f), true, 0 | ImGuiWindowFlags_NoScrollWithMouse))
                {
                    ImGui::Checkbox("Enable", &cfg.visuals.megalodon.bEnable);
                    ImGui::Checkbox("Draw Name", &cfg.visuals.megalodon.bName);
                    ImGui::ColorEdit4("Text Color", &cfg.visuals.megalodon.textCol.x, 0);
                    ImGui::SliderFloat("Draw Distance", &cfg.visuals.megalodon.drawdistance, 0.f, 5000.f, "%.0f");
                }
                ImGui::EndChild();

                ImGui::NextColumn();

                ImGui::Text("Sharks");
                if (ImGui::BeginChild("SharksSettings", ImVec2(0.f, 200.f), true, 0 | ImGuiWindowFlags_NoScrollWithMouse))
                {
                    ImGui::Checkbox("Enable", &cfg.visuals.sharks.bEnable);
                    ImGui::Checkbox("Draw Name", &cfg.visuals.sharks.bName);
                    ImGui::ColorEdit4("Text Color", &cfg.visuals.sharks.textCol.x, 0);
                    ImGui::SliderFloat("Draw Distance", &cfg.visuals.sharks.drawdistance, 0.f, 5000.f, "%.0f");
                }
                ImGui::EndChild();

                ImGui::NextColumn();

                ImGui::Text("Mermaids");
                if (ImGui::BeginChild("MermaidsSettings", ImVec2(0.f, 200.f), true, 0 | ImGuiWindowFlags_NoScrollWithMouse))
                {
                    ImGui::Checkbox("Enable", &cfg.visuals.mermaids.bEnable);
                    ImGui::Checkbox("Draw Name", &cfg.visuals.mermaids.bName);
                    ImGui::ColorEdit4("Text Color", &cfg.visuals.mermaids.textCol.x, 0);
                    ImGui::SliderFloat("Draw Distance", &cfg.visuals.mermaids.drawdistance, 0.f, 5000.f, "%.0f");
                }
                ImGui::EndChild();

                ImGui::NextColumn();

                ImGui::Text("Rowboats");
                if (ImGui::BeginChild("RowboatsSettings", ImVec2(0.f, 200.f), true, 0 | ImGuiWindowFlags_NoScrollWithMouse))
                {
                    ImGui::Checkbox("Enable", &cfg.visuals.rowboats.bEnable);
                    ImGui::Checkbox("Draw Name", &cfg.visuals.rowboats.bName);
                    ImGui::ColorEdit4("Text Color", &cfg.visuals.rowboats.textCol.x, 0);
                    ImGui::SliderFloat("Draw Distance", &cfg.visuals.rowboats.drawdistance, 0.f, 5000.f, "%.0f");
                }
                ImGui::EndChild();

                ImGui::NextColumn();

                ImGui::Text("Puzzles");
                if (ImGui::BeginChild("PuzzlesSettings", ImVec2(0.f, 200.f), true, 0 | ImGuiWindowFlags_NoScrollWithMouse))
                {

                    ImGui::Checkbox("Enable", &cfg.visuals.puzzles.bEnable);
                    ImGui::Checkbox("Draw Doors", &cfg.visuals.puzzles.bDoor);
                    ImGui::ColorEdit4("Text Color", &cfg.visuals.puzzles.textCol.x, 0);
                    ImGui::SliderFloat("Draw Distance", &cfg.visuals.puzzles.drawdistance, 0.f, 5000.f, "%.0f");

                }
                ImGui::EndChild();

                ImGui::NextColumn();

                ImGui::Text("Shipwrecks");
                if (ImGui::BeginChild("ShipwrecksSettings", ImVec2(0.f, 200.f), true, 0 | ImGuiWindowFlags_NoScrollWithMouse))
                {
                    ImGui::Checkbox("Enable", &cfg.visuals.shipwrecks.bEnable);
                    ImGui::Checkbox("Draw Name", &cfg.visuals.shipwrecks.bName);
                    ImGui::ColorEdit4("Text Color", &cfg.visuals.shipwrecks.textCol.x, 0);
                    ImGui::SliderFloat("Draw Distance", &cfg.visuals.shipwrecks.drawdistance, 0.f, 5000.f, "%.0f");
                }
                ImGui::EndChild();

                ImGui::NextColumn();

                ImGui::Text("Client");
                if (ImGui::BeginChild("ClientSettings", ImVec2(0.f, 200.f), true, 0 | ImGuiWindowFlags_NoScrollWithMouse))
                {
                    ImGui::Checkbox("Enable", &cfg.visuals.client.bEnable);
                    ImGui::Checkbox("Crosshair", &cfg.visuals.client.bCrosshair);
                    if (cfg.visuals.client.bCrosshair)
                    {
                        ImGui::SameLine();
                        ImGui::SetNextItemWidth(75.f);
                        ImGui::SliderFloat("Radius##1", &cfg.visuals.client.fCrosshair, 1.f, 100.f);
                    }
                    ImGui::ColorEdit4("Crosshair Color", &cfg.visuals.client.crosshairColor.x, ImGuiColorEditFlags_DisplayRGB);

                    ImGui::Checkbox("Oxygen Level", &cfg.visuals.client.bOxygen);
                    ImGui::Checkbox("Compass", &cfg.visuals.client.bCompass);

                    ImGui::Checkbox("Debug", &cfg.visuals.client.bDebug);
                    if (cfg.visuals.client.bDebug)
                    {
                        ImGui::SameLine();
                        ImGui::SetNextItemWidth(150.f);
                        ImGui::SliderFloat("Radius##2", &cfg.visuals.client.fDebug, 1.f, 1000.f);
                    }

                    ImGui::Checkbox("Cannon Tracers", &cfg.visuals.client.b_cannon_tracers);
                    ImGui::SliderInt("Tracer Length", &cfg.visuals.client.cannon_tracers_length, 1, 400, "%d");
                    ImGui::ColorEdit4("Tracer Color", &cfg.visuals.client.cannon_tracers_color.x, ImGuiColorEditFlags_DisplayRGB);
                }
                ImGui::EndChild();

                ImGui::NextColumn();

                ImGui::Text("Ship Radar");
                if (ImGui::BeginChild("RadarSettings", ImVec2(0.f, 200.f), true, 0 | ImGuiWindowFlags_NoScrollWithMouse))
                    {
                        ImGui::Checkbox("Enable", &cfg.visuals.radar.bEnable);
                        ImGui::SliderInt("Radar Size", &cfg.visuals.radar.i_size, 100, 250);
                        ImGui::SliderInt("Radar Scale", &cfg.visuals.radar.i_scale, 10, 500);
                    }
                ImGui::EndChild();

                ImGui::NextColumn();
                ImGui::Text("World Events");
                if (ImGui::BeginChild("WorldSettings", ImVec2(0.f, 200.f), true, 0 | ImGuiWindowFlags_NoScrollWithMouse))
                {
                    ImGui::Checkbox("Enable", &cfg.visuals.world.bEnable);
                    ImGui::ColorEdit4("Text Color", &cfg.visuals.world.textCol.x, 0);
                    ImGui::SliderFloat("Draw Distance", &cfg.visuals.world.drawdistance, 0.f, 20000.f, "%.0f");
                }
                ImGui::EndChild();

                ImGui::NextColumn();
                ImGui::Text("Seagulls");
                if (ImGui::BeginChild("SeagullsSettings", ImVec2(0.f, 200.f), true, 0 | ImGuiWindowFlags_NoScrollWithMouse))
                {
                    ImGui::Checkbox("Enable", &cfg.visuals.seagulls.bEnable);
                    ImGui::Checkbox("Draw Name", &cfg.visuals.seagulls.bName);
                    ImGui::ColorEdit4("Text Color", &cfg.visuals.seagulls.textCol.x, 0);
                    ImGui::SliderFloat("Draw Distance", &cfg.visuals.seagulls.drawdistance, 0.f, 20000.f, "%.0f");
                }
                ImGui::EndChild();

                
                ImGui::NextColumn();
                ImGui::Text("Storm");
                if (ImGui::BeginChild("StormSettings", ImVec2(0.f, 200.f), true, 0 | ImGuiWindowFlags_NoScrollWithMouse))
                {
                    ImGui::Checkbox("Enable", &cfg.visuals.storm.bEnable);
                    ImGui::Checkbox("Draw Name", &cfg.visuals.storm.bName);
                    ImGui::ColorEdit4("Text Color", &cfg.visuals.storm.textCol.x, 0);
                    ImGui::SliderFloat("Draw Distance", &cfg.visuals.storm.drawdistance, 0.f, 15000.f, "%.0f");
                }
                ImGui::EndChild();
                

               
      

                ImGui::NextColumn();
                ImGui::Text("Flag");
                if (ImGui::BeginChild("FlagSettings", ImVec2(0.f, 200.f), true, 0 | ImGuiWindowFlags_NoScrollWithMouse))
                {
                    ImGui::Checkbox("Enable", &cfg.visuals.flag.bEnable);
                    ImGui::Checkbox("Draw Name", &cfg.visuals.flag.bName);
                    ImGui::ColorEdit4("Text Color", &cfg.visuals.flag.textCol.x, 0);
                    ImGui::SliderFloat("Draw Distance", &cfg.visuals.flag.drawdistance, 0.f, 1725.f, "%.0f");
                }
                ImGui::EndChild();

                ImGui::Columns();
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem(ICON_FA_CROSSHAIRS " Aim")) {

                ImGui::Text("Global Aim");
                if (ImGui::BeginChild("Global", ImVec2(0.f, 29.f), false, 0 | ImGuiWindowFlags_NoScrollWithMouse))
                {
                    ImGui::Checkbox("Enable", &cfg.aim.bEnable);
                }
                ImGui::EndChild();

                
                ImGui::Columns(3, "CLM1", false);
                ImGui::Text("Players");
                if (ImGui::BeginChild("PlayersSettings", ImVec2(0.f, 200.f), true, 0 | ImGuiWindowFlags_NoScrollWithMouse))
                {
                    ImGui::Checkbox("Enable", &cfg.aim.players.bEnable);
                    ImGui::Checkbox("Visible Only", &cfg.aim.players.bVisibleOnly);
                    ImGui::Checkbox("Aim At Teammates", &cfg.aim.players.bTeam);
                    ImGui::SliderFloat("Yaw", &cfg.aim.players.fYaw, 1.f, 200.f, "%.0f", ImGuiSliderFlags_AlwaysClamp);
                    ImGui::SliderFloat("Pitch", &cfg.aim.players.fPitch, 1.f, 200.f, "%.0f", ImGuiSliderFlags_AlwaysClamp);
                    ImGui::SliderFloat("Smoothness", &cfg.aim.players.fSmoothness, 1.f, 100.f, "%.0f", ImGuiSliderFlags_AlwaysClamp);
                    ImGui::SliderFloat("Aim Height", &cfg.aim.players.fAimHeight, 0.f, 100.f, "%.0f", ImGuiSliderFlags_AlwaysClamp);
                }
                ImGui::EndChild();

                ImGui::NextColumn();

                

                ImGui::Text("Skeletons");
                if (ImGui::BeginChild("SkeletonsSettings", ImVec2(0.f, 200.f), true, 0 | ImGuiWindowFlags_NoScrollWithMouse))
                {
                    ImGui::Checkbox("Enable", &cfg.aim.skeletons.bEnable);
                    ImGui::Checkbox("Visible Only", &cfg.aim.skeletons.bVisibleOnly);
                    ImGui::SliderFloat("Yaw", &cfg.aim.skeletons.fYaw, 1.f, 200.f, "%.0f", ImGuiSliderFlags_AlwaysClamp);
                    ImGui::SliderFloat("Pitch", &cfg.aim.skeletons.fPitch, 1.f, 200.f, "%.0f", ImGuiSliderFlags_AlwaysClamp);
                    ImGui::SliderFloat("Smoothness", &cfg.aim.skeletons.fSmoothness, 1.f, 100.f, "%.0f", ImGuiSliderFlags_AlwaysClamp);
                    ImGui::SliderFloat("Aim Height", &cfg.aim.skeletons.fAimHeight, 0.f, 100.f, "%.0f", ImGuiSliderFlags_AlwaysClamp);
                }
                ImGui::EndChild();

                ImGui::NextColumn();

                ImGui::Text("Harpoon (WIP) ");
                if (ImGui::BeginChild("HarpoonSettings", ImVec2(0.f, 200.f), true, 0 | ImGuiWindowFlags_NoScrollWithMouse))
                {
                    ImGui::Checkbox("Enable", &cfg.aim.harpoon.bEnable);
                    ImGui::Checkbox("Visible Only", &cfg.aim.harpoon.bVisibleOnly);
                    ImGui::SliderFloat("Yaw", &cfg.aim.harpoon.fYaw, 1.f, 100.f, "%.0f", ImGuiSliderFlags_AlwaysClamp);
                    ImGui::SliderFloat("Pitch", &cfg.aim.harpoon.fPitch, 1.f, 100.f, "%.0f", ImGuiSliderFlags_AlwaysClamp);
                }
                ImGui::EndChild();

                ImGui::NextColumn();
               
                ImGui::Text("Cannon (WIP)");
                if (ImGui::BeginChild("CannonSettings", ImVec2(0.f, 200.f), true, 0 | ImGuiWindowFlags_NoScrollWithMouse))
                {
                    ImGui::Checkbox("Enable", &cfg.aim.cannon.bEnable);
                    ImGui::Checkbox("Chain Aimbot (Auto Detects)", &cfg.aim.cannon.b_chain_shots);
                    ImGui::Checkbox("Visible Only", &cfg.aim.cannon.bVisibleOnly);
                    ImGui::Checkbox("Insta", &cfg.aim.cannon.b_instant_shoot);
                    ImGui::Checkbox("Aim At Players", &cfg.aim.cannon.playeraimbot);
                    ImGui::Checkbox("Aim At Skeletons", &cfg.aim.cannon.skeletonaimbot);
                    ImGui::Checkbox("Random Holes", &cfg.aim.cannon.randomshots);
                    ImGui::Checkbox("Deckshots", &cfg.aim.cannon.deckshots);
                    ImGui::SliderFloat("Yaw", &cfg.aim.cannon.fYaw, 1.f, 100.f, "%.0f", ImGuiSliderFlags_AlwaysClamp);
                    ImGui::SliderFloat("Pitch", &cfg.aim.cannon.fPitch, 1.f, 100.f, "%.0f", ImGuiSliderFlags_AlwaysClamp);
                }
                ImGui::EndChild();
                
                ImGui::Columns();

                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem(ICON_FA_SLIDERS_H " Misc")) {

                ImGui::Text("Global Misc");
                if (ImGui::BeginChild("Global", ImVec2(0.f, 29.f), false, 0 | ImGuiWindowFlags_NoScrollWithMouse))
                {
                    ImGui::Checkbox("Enable", &cfg.misc.bEnable);
                }
                ImGui::EndChild();

                ImGui::Columns(3, "CLM1", false);
                ImGui::Text("Client");
                if (ImGui::BeginChild("ClientSettings", ImVec2(0.f, 200.f), true, 0 | ImGuiWindowFlags_NoScrollWithMouse))
                {
                    ImGui::Checkbox("Enable", &cfg.misc.client.bEnable);
                    ImGui::Checkbox("Ship Info", &cfg.misc.client.bShipInfo);
                    ImGui::Checkbox("Map Pins", &cfg.misc.client.b_map_pins);
                    ImGui::Checkbox("Cooking Timer", &cfg.misc.client.b_cooking_timer);
                    ImGui::SliderFloat("FOV", &cfg.misc.client.fov, 90.f, 180.f, "%.0f");
                    //ImGui::SliderInt("Time", &cfg.misc.client.time, 0, 24, "%.0f");

                    ImGui::Separator();
                    if (ImGui::Button("Save Settings"))
                    {
                        do {
                            wchar_t buf[MAX_PATH];
                            GetModuleFileNameW(hinstDLL, buf, MAX_PATH);
                            fs::path path = fs::path(buf).remove_filename() / ".settings";
                            auto file = CreateFileW(path.wstring().c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
                            if (file == INVALID_HANDLE_VALUE) break;
                            DWORD written;
                            if (WriteFile(file, &cfg, sizeof(cfg), &written, 0)) ImGui::OpenPopup("##SettingsSaved");
                            CloseHandle(file);
                        } while (false);
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("Load Settings")) 
                    {
                        do {
                            wchar_t buf[MAX_PATH];
                            GetModuleFileNameW(hinstDLL, buf, MAX_PATH);
                            fs::path path = fs::path(buf).remove_filename() / ".settings";
                            auto file = CreateFileW(path.wstring().c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
                            if (file == INVALID_HANDLE_VALUE) break;
                            DWORD readed;
                            if (ReadFile(file, &cfg, sizeof(cfg), &readed, 0))  ImGui::OpenPopup("##SettingsLoaded");
                            CloseHandle(file);
                        } while (false);
                    }

                    ImVec2 center(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f);
                    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
                    if (ImGui::BeginPopupModal("##SettingsSaved", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar))
                    {
                        ImGui::Text("\nSettings Saved!\n\n");
                        ImGui::Separator();
                        if (ImGui::Button("OK", { 170.f , 0.f })) { ImGui::CloseCurrentPopup(); }
                        ImGui::EndPopup();
                    }
                    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
                    if (ImGui::BeginPopupModal("##SettingsLoaded", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar))
                    {
                        ImGui::Text("\nSettings Loaded!\n\n");
                        ImGui::Separator();
                        if (ImGui::Button("OK", { 170.f , 0.f })) { ImGui::CloseCurrentPopup(); }
                        ImGui::EndPopup();
                    }
                }
                ImGui::EndChild();

                ImGui::NextColumn();

                ImGui::Text("Macros");
                if (ImGui::BeginChild("MacrosSettings", ImVec2(0.f, 200.f), true, 0 | ImGuiWindowFlags_NoScrollWithMouse))
                {
                    ImGui::Checkbox("Enable", &cfg.misc.macro.bEnable);
                    ImGui::Checkbox("Bunny Hop", &cfg.misc.macro.b_bunnyhop);
                    ImGui::Checkbox("Loot Sprint", &cfg.misc.macro.bLootsprint);
                    ImGui::Checkbox("Take Loot from Barrel", &cfg.misc.macro.takelootfrombarreltocrate);
                    ImGui::Checkbox("Disable Idle Kick", &cfg.misc.macro.bIdleKick);
                }
                ImGui::EndChild();

                ImGui::NextColumn();

                ImGui::Text("Game");
                if (ImGui::BeginChild("GameSettings", ImVec2(0.f, 200.f), true, 0 | ImGuiWindowFlags_NoScrollWithMouse))
                {
                    ImGui::Checkbox("Enable", &cfg.misc.game.bEnable);
                    ImGui::Checkbox("Show Players List", &cfg.misc.game.bShowPlayers);
                }
                ImGui::EndChild();

                ImGui::NextColumn();

                ImGui::Text("Weapons");
                if (ImGui::BeginChild("Weapon Settings", ImVec2(0.f, 200.f), true, 0 | ImGuiWindowFlags_NoScrollWithMouse))
                {
                    ImGui::Checkbox("Enable", &cfg.misc.allweapons.bEnable);
                    ImGui::Checkbox("No Spread", &cfg.misc.allweapons.fasterreloading);
                    ImGui::Checkbox("Faster Aiming", &cfg.misc.allweapons.fasteraimingspeed);
                }
                ImGui::EndChild();

                ImGui::NextColumn();

                ImGui::EndTabItem();
            }
            //ImGui::EndTabBar();
            if (ImGui::BeginTabItem(ICON_FA_FISH " Fishing")) {

                ImGui::Text("Fishing");
                if (ImGui::BeginChild("Fishing bot", ImVec2(0.f, 200.f), true, 0 | ImGuiWindowFlags_NoScrollWithMouse))
                {
                    ImGui::Checkbox("Enable", &cfg.fishing.bEnable);
                }
                ImGui::EndChild();

                ImGui::Columns(3, "CLM1", false);
                ImGui::Text("Fishing");
                if (ImGui::BeginChild("FishingSettings", ImVec2(0.f, 200.f), true, 0 | ImGuiWindowFlags_NoScrollWithMouse))
                {
                }
                    ImGui::EndChild();

                    ImGui::NextColumn();

                    ImGui::EndTabItem();
            }
            ImGui::EndTabBar();*/
        //};
        ImGui::End();
    }
    context->OMSetRenderTargets(1, &renderTargetView, nullptr);
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    return PresentOriginal(swapChain, syncInterval, flags);
}

HRESULT Cheat::Renderer::ResizeHook(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags)
{

    if (renderTargetView)
    {
        ImGui_ImplDX11_Shutdown();
        ImGui::DestroyContext();
        renderTargetView->Release();
        renderTargetView = nullptr;
    }
    if (context)
    {
        context->Release();
        context = nullptr;
    }
    if (device)
    {
        device->Release();
        device = nullptr;
    }
    
    return ResizeOriginal(swapChain, bufferCount, width, height, newFormat, swapChainFlags);
}


inline bool Cheat::Renderer::Init()
{
    HMODULE dxgi = GetModuleHandleA("dxgi.dll");
    Logger::Log("dxgi: %p\n", dxgi);
    //static BYTE PresentSig[] = { 0x55, 0x57, 0x41, 0x56, 0x48, 0x8d, 0x6c, 0x24, 0x90, 0x48, 0x81, 0xec, 0x70, 0x01 };
    static BYTE PresentSig[] = { 0xe9, 0x00, 0x00, 0x00, 0x00, 0x48, 0x89, 0x74, 0x24, 0x00, 0x55 };
    //static BYTE PresentHead[] = { 0x48, 0x89, 0x5c, 0x24, 0x10 };
    //BYTE* fnPresent = Tools::PacthFn(dxgi, PresentSig, sizeof(PresentSig), PresentHead, sizeof(PresentHead));
    fnPresent = reinterpret_cast<decltype(fnPresent)>(Tools::FindFn(dxgi, PresentSig, sizeof(PresentSig)));
    Logger::Log("IDXGISwapChain::Present: %p\n", fnPresent);
    if (!fnPresent) return false;
    
    //static BYTE ResizeSig[] = { 0x48, 0x81, 0xec, 0xc0, 0x00, 0x00, 0x00, 0x48, 0xc7, 0x45, 0x1f }; 
    static BYTE ResizeSig[] = { 0xe9, 0x00, 0x00, 0x00, 0x00, 0x54, 0x41, 0x55, 0x41, 0x56, 0x41, 0x57, 0x48, 0x8d, 0x68, 0x00, 0x48, 0x81, 0xec, 0x00, 0x00, 0x00, 0x00, 0x48, 0xc7, 0x45, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0x89, 0x58, 0x00, 0x48, 0x89, 0x70, 0x00, 0x48, 0x89, 0x78, 0x00, 0x45, 0x8b, 0xf9, 0x45, 0x8b, 0xe0, 0x44, 0x8b, 0xea, 0x48, 0x8b, 0xf9, 0x8b, 0x45, 0x00, 0x89, 0x44, 0x24, 0x00, 0x8b, 0x75, 0x00, 0x89, 0x74, 0x24, 0x00, 0x44, 0x89, 0x4c, 0x24, 0x00, 0x45, 0x8b, 0xc8, 0x44, 0x8b, 0xc2, 0x48, 0x8b, 0xd1, 0x48, 0x8d, 0x4d, 0x00, 0xe8, 0x00, 0x00, 0x00, 0x00, 0x48, 0x8b, 0xc7, 0x48, 0x8d, 0x4f, 0x00, 0x48, 0xf7, 0xd8, 0x48, 0x1b, 0xdb, 0x48, 0x23, 0xd9, 0x48, 0x8b, 0x4b, 0x00, 0x48, 0x8b, 0x01, 0x48, 0x8b, 0x40, 0x00, 0xff, 0x15, 0x00, 0x00, 0x00, 0x00, 0x48, 0x89, 0x5d, 0x00, 0x8b, 0x87, 0x00, 0x00, 0x00, 0x00, 0x89, 0x45, 0x00, 0x45, 0x33, 0xf6 };
    //static BYTE ResizeHead[] = { 0x48, 0x8b, 0xc4, 0x55, 0x41, 0x54 };
    //BYTE* fnResize = Tools::PacthFn(dxgi, ResizeSig, sizeof(ResizeSig), ResizeHead, sizeof(ResizeHead));
    fnResize = reinterpret_cast<decltype(fnResize)>(Tools::FindFn(dxgi, ResizeSig, sizeof(ResizeSig)));
    Logger::Log("IDXGISwapChain::ResizeBuffers: %p\n", fnResize);
    if (!fnResize) return false;
    

    if (!SetHook(fnPresent, PresentHook, reinterpret_cast<void**>(&PresentOriginal)))
    {
        return false;
    };

    Logger::Log("PresentHook: %p\n", PresentHook);
    Logger::Log("PresentOriginal: %p\n", PresentOriginal);

    if (!SetHook(fnResize, ResizeHook, reinterpret_cast<void**>(&ResizeOriginal)))
    {
        return false;
    };

    Logger::Log("ResizeHook: %p\n", ResizeHook);
    Logger::Log("ResizeOriginal: %p\n", ResizeOriginal);

    if (!SetHook(SetCursorPos, SetCursorPosHook, reinterpret_cast<void**>(&SetCursorPosOriginal)))
    {
        Logger::Log("Can't hook SetCursorPos\n");
        return false;
    };

    if (!SetHook(SetCursor, SetCursorHook, reinterpret_cast<void**>(&SetCursorOriginal)))
    {
        Logger::Log("Can't hook SetCursor\n");
        return false;
    };

    return true;
}

void Cheat::Renderer::renderSubTab0() {
    std::vector<std::string> arr = { "Regular Aimbot", "Cannon Aimbot", "Other" };
    //ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 0.0f);
    ImGuiHelper::drawTabHorizontally("subtab-0", ImVec2(ImGuiHelper::getWidth(), 50), arr, selectedSubTab0);
    //ImGui::PopStyleVar();
    ImGui::Spacing();

    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0, 0, 0, 0));
    ImGui::BeginChild("modules-wrapper", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), false);
    ImGui::PopStyleColor();

    switch (selectedSubTab0) {
    case 0: {
        ImGui::Columns(2, nullptr, false);
        ImGui::SetColumnOffset(1, 500);

        ImGui::Checkbox("Global Aim Switch", &cfg.aim.bEnable);

        ImGui::Text("Players");
        ImGui::BeginChild("Player Settings", ImVec2(ImGuiHelper::getWidth(), ImGuiHelper::getHeight()), true);
        //ImGui::Checkbox("Enable", &cfg.aim.bEnable);
        ImGui::Checkbox("Enable", &cfg.aim.players.bEnable);
        ImGui::Checkbox("Visible Only", &cfg.aim.players.bVisibleOnly);
        ImGui::Checkbox("Aim At Teammates", &cfg.aim.players.bTeam);
        ImGui::SliderFloat("Yaw", &cfg.aim.players.fYaw, 1.f, 200.f, "%.0f", ImGuiSliderFlags_AlwaysClamp);
        ImGui::SliderFloat("Pitch", &cfg.aim.players.fPitch, 1.f, 200.f, "%.0f", ImGuiSliderFlags_AlwaysClamp);
        ImGui::SliderFloat("Smoothness", &cfg.aim.players.fSmoothness, 1.f, 100.f, "%.0f", ImGuiSliderFlags_AlwaysClamp);
        ImGui::SliderFloat("Aim Height", &cfg.aim.players.fAimHeight, 0.f, 100.f, "%.0f", ImGuiSliderFlags_AlwaysClamp);

        ImGui::EndChild();
        ImGui::NextColumn();
        //ImGui::SetColumnOffset(1, 300);
        //ImGui::Spacing();
        ImGui::Text("Skeletons");
        ImGui::BeginChild("Skeleton Settings", ImVec2(ImGuiHelper::getWidth(), ImGuiHelper::getHeight()), true);
        ImGui::Checkbox("Enable", &cfg.aim.skeletons.bEnable);
        ImGui::Checkbox("Visible Only", &cfg.aim.skeletons.bVisibleOnly);
        ImGui::SliderFloat("Yaw", &cfg.aim.skeletons.fYaw, 1.f, 200.f, "%.0f", ImGuiSliderFlags_AlwaysClamp);
        ImGui::SliderFloat("Pitch", &cfg.aim.skeletons.fPitch, 1.f, 200.f, "%.0f", ImGuiSliderFlags_AlwaysClamp);
        ImGui::SliderFloat("Smoothness", &cfg.aim.skeletons.fSmoothness, 1.f, 100.f, "%.0f", ImGuiSliderFlags_AlwaysClamp);
        ImGui::SliderFloat("Aim Height", &cfg.aim.skeletons.fAimHeight, 0.f, 100.f, "%.0f", ImGuiSliderFlags_AlwaysClamp);
        //RCS::i().renderImGui();
        ImGui::EndChild();

        

        //ImGui::BeginChild("aimassist3", ImVec2(ImGuiHelper::getWidth(), ImGuiHelper::getHeight()), true);
        //ImGui::EndChild();

        break;
    }
    case 1: {
        //ImGui::Columns(2, nullptr, false);
        ImGui::Text("Cannon");
        ImGui::BeginChild("Cannon settings", ImVec2(ImGuiHelper::getWidth(), ImGuiHelper::getHeight()), true);
        ImGui::Checkbox("Enable", &cfg.aim.cannon.bEnable);
        ImGui::Checkbox("Chain Aimbot (Auto Detects)", &cfg.aim.cannon.b_chain_shots);
        ImGui::Checkbox("Visible Only", &cfg.aim.cannon.bVisibleOnly);
        ImGui::Checkbox("Insta", &cfg.aim.cannon.b_instant_shoot);
        ImGui::Checkbox("Aim At Players", &cfg.aim.cannon.playeraimbot);
        ImGui::Checkbox("Aim At Skeletons", &cfg.aim.cannon.skeletonaimbot);
        ImGui::Checkbox("Random Holes", &cfg.aim.cannon.randomshots);
        ImGui::Checkbox("Hole Logic", &cfg.aim.cannon.lowAim);
        ImGui::Checkbox("Deckshots", &cfg.aim.cannon.deckshots);
        ImGui::SliderFloat("Yaw", &cfg.aim.cannon.fYaw, 1.f, 100.f, "%.0f", ImGuiSliderFlags_AlwaysClamp);
        ImGui::SliderFloat("Pitch", &cfg.aim.cannon.fPitch, 1.f, 100.f, "%.0f", ImGuiSliderFlags_AlwaysClamp);
        ImGui::EndChild();
        break;
    }
    case 2: {
        ImGui::Text("Harpoon");
        ImGui::BeginChild("Harpoon settings", ImVec2(ImGuiHelper::getWidth(), ImGuiHelper::getHeight()), true);
        ImGui::Checkbox("Enable", &cfg.aim.harpoon.bEnable);
        ImGui::Checkbox("Visible Only", &cfg.aim.harpoon.bVisibleOnly);
        ImGui::SliderFloat("Yaw", &cfg.aim.harpoon.fYaw, 1.f, 100.f, "%.0f", ImGuiSliderFlags_AlwaysClamp);
        ImGui::SliderFloat("Pitch", &cfg.aim.harpoon.fPitch, 1.f, 100.f, "%.0f", ImGuiSliderFlags_AlwaysClamp);
        ImGui::EndChild();
        break;
    }
    }

    ImGui::EndChild();
}

void Cheat::Renderer::renderSubTab1() {
    ImGuiHelper::drawTabHorizontally("subtab-1", ImVec2(ImGuiHelper::getWidth(), 50), { "ESP", "World", "Other" }, selectedSubTab1);
    ImGui::Spacing();

    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0, 0, 0, 0));
    ImGui::BeginChild("modules-wrapper", ImVec2(ImGuiHelper::getWidth(), ImGuiHelper::getHeight()), false);
    ImGui::PopStyleColor();

    switch (selectedSubTab1) {
    case 0: {
        ImGui::Columns(2, nullptr, false);
        ImGui::SetColumnOffset(1, 500);

        ImGui::Checkbox("Global Visuals Switch", &cfg.visuals.bEnable);

        const char* bars[] = { "None", "2DRectLeft", "2DRectRight", "2DRectBottom", "2DRectTop" };
        const char* boxes[] = { "None", "2DBox", "3DBox" };
        
        //

        ImGui::Text("Players");
        ImGui::BeginChild("Player ESP", ImVec2(ImGuiHelper::getWidth(), ImGuiHelper::getHeight()), true);
        ImGui::Checkbox("Enable", &cfg.visuals.players.bEnable);
        ImGui::Checkbox("Draw Teammates", &cfg.visuals.players.bDrawTeam);
        ImGui::Checkbox("Draw Name", &cfg.visuals.players.bName);
        //ImGui::Checkbox("Draw Weapon Name WIP ", &cfg.visuals.players.bWeaponanmes);
        ImGui::Checkbox("Draw Skeleton WIP ", &cfg.visuals.players.bSkeleton);
        ImGui::Combo("Box Type", reinterpret_cast<int*>(&cfg.visuals.players.boxType), boxes, IM_ARRAYSIZE(boxes));
        ImGui::Combo("Health Bar Type", reinterpret_cast<int*>(&cfg.visuals.players.barType), bars, IM_ARRAYSIZE(bars));
        ImGui::ColorEdit4("Visible Enemy", &cfg.visuals.players.enemyColorVis.x, 0); ImGui::SameLine();
        ImGui::ColorEdit4("Invisible Enemy", &cfg.visuals.players.enemyColorInv.x, 0);
        ImGui::ColorEdit4("Visible Team", &cfg.visuals.players.teamColorVis.x, 0); ImGui::SameLine();
        ImGui::ColorEdit4("Invisible Team", &cfg.visuals.players.teamColorInv.x, 0);
        ImGui::ColorEdit4("Text", &cfg.visuals.players.textCol.x, 0);
        ImGui::SliderFloat("Draw Distance", &cfg.visuals.players.drawdistance, 0.f, 5000.f, "%.0f");

        ImGui::EndChild();

        ImGui::NextColumn();

        ImGui::Text("Skeletons");
        ImGui::BeginChild("Skeleton ESP", ImVec2(ImGuiHelper::getWidth(), 300), true);
        ImGui::Checkbox("Enable", &cfg.visuals.skeletons.bEnable);
        ImGui::Checkbox("Draw Name", &cfg.visuals.skeletons.bName);
        ImGui::Combo("Box Type", reinterpret_cast<int*>(&cfg.visuals.skeletons.boxType), boxes, IM_ARRAYSIZE(boxes));
        ImGui::ColorEdit4("Visible", &cfg.visuals.skeletons.colorVis.x, 0); ImGui::SameLine();
        ImGui::ColorEdit4("Invisible", &cfg.visuals.skeletons.colorInv.x, 0);
        ImGui::ColorEdit4("Text", &cfg.visuals.skeletons.textCol.x, 0);
        ImGui::SliderFloat("Draw Distance", &cfg.visuals.skeletons.drawdistance, 0.f, 5000.f, "%.0f");

        ImGui::EndChild();

        ImGui::Spacing();

        ImGui::Text("Ships");
        ImGui::BeginChild("Ship ESP", ImVec2(ImGuiHelper::getWidth(), ImGuiHelper::getHeight()), true);
        ImGui::Checkbox("Enable", &cfg.visuals.ships.bEnable);
        ImGui::Checkbox("Draw Name", &cfg.visuals.ships.bName);
        ImGui::Checkbox("Show Holes", &cfg.visuals.ships.bDamage);
        ImGui::ColorEdit4("Damage", &cfg.visuals.ships.damageColor.x, 0); ImGui::SameLine();
        ImGui::ColorEdit4("Text", &cfg.visuals.ships.textCol.x, 0);

        ImGui::EndChild();

        



        //ImGui::BeginChild("aimassist3", ImVec2(ImGuiHelper::getWidth(), ImGuiHelper::getHeight()), true);
        //ImGui::EndChild();

        break;
    }
    case 1: {
        ImGui::Columns(3, nullptr, false);
        ImGui::SetColumnOffset(1, 525);
        ImGui::SetColumnOffset(2, 850);
        ImGui::Text("Islands");
        ImGui::BeginChild("Islands", ImVec2(ImGuiHelper::getWidth(), 138), true);
        ImGui::Checkbox("Enable", &cfg.visuals.islands.bEnable);
        ImGui::Checkbox("Draw Names", &cfg.visuals.islands.bName);
        ImGui::SliderInt("Max Distance", &cfg.visuals.islands.intMaxDist, 100, 2750, "%d", ImGuiSliderFlags_AlwaysClamp);
        ImGui::Spacing();
        ImGui::ColorEdit4("Text", &cfg.visuals.islands.textCol.x, 0);

        ImGui::EndChild();

        ImGui::Spacing();

        ImGui::Text("Items");
        ImGui::BeginChild("Items", ImVec2(ImGuiHelper::getWidth(), 255), true);
        ImGui::Checkbox("Enable", &cfg.visuals.items.bEnable);
        ImGui::Checkbox("Draw Name", &cfg.visuals.items.bName);
        ImGui::Checkbox("Barrels", &cfg.visuals.items.barrelitems);
        ImGui::Checkbox("Ammo Chests", &cfg.visuals.items.ammochests);
        ImGui::Checkbox("Barrelpeek", &cfg.misc.others.barrelstoggle);
        ImGui::ColorEdit4("Text ", &cfg.visuals.items.textCol.x, 0); ImGui::SameLine();
        ImGui::ColorEdit4("Barrel Text ", &cfg.visuals.items.barreltextCol.x, 0); ImGui::SameLine();
        ImGui::ColorEdit4("Ammo Chest ", &cfg.visuals.items.ammotextCol.x, 0);
        ImGui::SliderFloat("Item Draw Distance", &cfg.visuals.items.itemdrawdistance, 0.f, 5000.f, "%.0f");
        ImGui::SliderFloat("Barrel Draw Distance", &cfg.visuals.items.barreldrawdistance, 0.f, 5000.f, "%.0f");
        ImGui::SliderFloat("AmmoBox Draw Distance", &cfg.visuals.items.ammochestsdrawdistance, 0.f, 5000.f, "%.0f");

        ImGui::EndChild();

        ImGui::Spacing();

        ImGui::Text("Animals");
        ImGui::BeginChild("Animals", ImVec2(ImGuiHelper::getWidth(), 138), true);
        ImGui::Checkbox("Enable", &cfg.visuals.animals.bEnable);
        ImGui::Checkbox("Draw Name", &cfg.visuals.animals.bName);
        ImGui::ColorEdit4("Text", &cfg.visuals.animals.textCol.x, 0);
        ImGui::SliderFloat("Draw Distance", &cfg.visuals.animals.drawdistance, 0.f, 5000.f, "%.0f");

        ImGui::EndChild();

        ImGui::Spacing();


        ImGui::Text("World Events");
        ImGui::BeginChild("World Events", ImVec2(ImGuiHelper::getWidth(), ImGuiHelper::getHeight()), true);
        ImGui::Checkbox("Enable", &cfg.visuals.world.bEnable);
        ImGui::ColorEdit4("Text", &cfg.visuals.world.textCol.x, 0);
        ImGui::SliderFloat("Draw Distance", &cfg.visuals.world.drawdistance, 0.f, 20000.f, "%.0f");

        ImGui::EndChild();

        ImGui::NextColumn();

        ImGui::Text("Sharks");
        ImGui::BeginChild("Sharks", ImVec2(ImGuiHelper::getWidth(), 125), true);
        ImGui::Checkbox("Enable", &cfg.visuals.sharks.bEnable);
        ImGui::Checkbox("Draw Name", &cfg.visuals.sharks.bName);
        ImGui::ColorEdit4("Text", &cfg.visuals.sharks.textCol.x, 0);
        ImGui::SliderFloat("Draw Distance", &cfg.visuals.sharks.drawdistance, 0.f, 5000.f, "%.0f");

        ImGui::EndChild();

        ImGui::Spacing();

        ImGui::Text("Mermaids");
        ImGui::BeginChild("Mermaids", ImVec2(ImGuiHelper::getWidth(), 125), true);
        ImGui::Checkbox("Enable", &cfg.visuals.mermaids.bEnable);
        ImGui::Checkbox("Draw Name", &cfg.visuals.mermaids.bName);
        ImGui::ColorEdit4("Text", &cfg.visuals.mermaids.textCol.x, 0);
        ImGui::SliderFloat("Draw Distance", &cfg.visuals.mermaids.drawdistance, 0.f, 5000.f, "%.0f");

        ImGui::EndChild();

        ImGui::Spacing();

        ImGui::Text("Rowboats");
        ImGui::BeginChild("Rowboats", ImVec2(ImGuiHelper::getWidth(), 125), true);
        ImGui::Checkbox("Enable", &cfg.visuals.rowboats.bEnable);
        ImGui::Checkbox("Draw Name", &cfg.visuals.rowboats.bName);
        ImGui::ColorEdit4("Text", &cfg.visuals.rowboats.textCol.x, 0);
        ImGui::SliderFloat("Draw Distance", &cfg.visuals.rowboats.drawdistance, 0.f, 5000.f, "%.0f");

        ImGui::EndChild();

        ImGui::Spacing();

        ImGui::Text("Puzzles");
        ImGui::BeginChild("Puzzles", ImVec2(ImGuiHelper::getWidth(), 125), true);
        ImGui::Checkbox("Enable", &cfg.visuals.puzzles.bEnable);
        ImGui::Checkbox("Draw Doors", &cfg.visuals.puzzles.bDoor);
        ImGui::ColorEdit4("Text", &cfg.visuals.puzzles.textCol.x, 0);
        ImGui::SliderFloat("Draw Distance", &cfg.visuals.puzzles.drawdistance, 0.f, 5000.f, "%.0f");

        ImGui::EndChild();

        ImGui::NextColumn();

        ImGui::Text("Shipwrecks");
        ImGui::BeginChild("Shipwrecks", ImVec2(ImGuiHelper::getWidth(), 125), true);
        ImGui::Checkbox("Enable", &cfg.visuals.shipwrecks.bEnable);
        ImGui::Checkbox("Draw Name", &cfg.visuals.shipwrecks.bName);
        ImGui::ColorEdit4("Text", &cfg.visuals.shipwrecks.textCol.x, 0);
        ImGui::SliderFloat("Draw Distance", &cfg.visuals.shipwrecks.drawdistance, 0.f, 5000.f, "%.0f");

        ImGui::EndChild();

        ImGui::Spacing();

        ImGui::Text("Megalodon");
        ImGui::BeginChild("Megalodon", ImVec2(ImGuiHelper::getWidth(), 138), true);
        ImGui::Checkbox("Enable", &cfg.visuals.megalodon.bEnable);
        ImGui::Checkbox("Draw Name", &cfg.visuals.megalodon.bName);
        ImGui::ColorEdit4("Text", &cfg.visuals.megalodon.textCol.x, 0);
        ImGui::SliderFloat("Draw Distance", &cfg.visuals.megalodon.drawdistance, 0.f, 5000.f, "%.0f");

        ImGui::EndChild();

        ImGui::Spacing();

        ImGui::Text("Seagulls");
        ImGui::BeginChild("Seagulls", ImVec2(ImGuiHelper::getWidth(), 125), true);
        ImGui::Checkbox("Enable", &cfg.visuals.seagulls.bEnable);
        ImGui::Checkbox("Draw Name", &cfg.visuals.seagulls.bName);
        ImGui::ColorEdit4("Text", &cfg.visuals.seagulls.textCol.x, 0);
        ImGui::SliderFloat("Draw Distance", &cfg.visuals.seagulls.drawdistance, 0.f, 20000.f, "%.0f");

        ImGui::EndChild();

        ImGui::Spacing();

        ImGui::Text("Storm");
        ImGui::BeginChild("Storm", ImVec2(ImGuiHelper::getWidth(), 125), true);
        ImGui::Checkbox("Enable", &cfg.visuals.storm.bEnable);
        ImGui::Checkbox("Draw Name", &cfg.visuals.storm.bName);
        ImGui::ColorEdit4("Text", &cfg.visuals.storm.textCol.x, 0);
        ImGui::SliderFloat("Draw Distance", &cfg.visuals.storm.drawdistance, 0.f, 15000.f, "%.0f");

        ImGui::EndChild();


        break;
    }
    case 2: {

        ImGui::Text("Client");
        ImGui::BeginChild("Client", ImVec2(ImGuiHelper::getWidth(), ImGuiHelper::getHeight()), true);
        ImGui::Checkbox("Crosshair", &cfg.visuals.client.bCrosshair); ImGui::SameLine();
        if (cfg.visuals.client.bCrosshair)
        {
            ImGui::SetNextItemWidth(75.f);
            ImGui::SliderFloat("Radius##1", &cfg.visuals.client.fCrosshair, 1.f, 100.f);
            ImGui::SameLine();
        }
        ImGui::ColorEdit4("Crosshair Color", &cfg.visuals.client.crosshairColor.x, ImGuiColorEditFlags_DisplayRGB);

        ImGui::Checkbox("Oxygen Level", &cfg.visuals.client.bOxygen);
        ImGui::Checkbox("Compass", &cfg.visuals.client.bCompass);

        ImGui::Checkbox("Debug", &cfg.visuals.client.bDebug);
        if (cfg.visuals.client.bDebug)
        {
            ImGui::SameLine();
            ImGui::SetNextItemWidth(150.f);
            ImGui::SliderFloat("Radius##2", &cfg.visuals.client.fDebug, 1.f, 1000.f);
        }

        ImGui::Checkbox("Cannon Tracers", &cfg.visuals.client.b_cannon_tracers);
        ImGui::SliderInt("Tracer Length", &cfg.visuals.client.cannon_tracers_length, 1, 400, "%d");
        ImGui::Spacing();
        ImGui::ColorEdit4("Tracer", &cfg.visuals.client.cannon_tracers_color.x, ImGuiColorEditFlags_DisplayRGB);
        ImGui::EndChild();

        break;
    }
    }

    ImGui::EndChild();
}

void Cheat::Renderer::renderSubTab2() {
    ImGuiHelper::drawTabHorizontally("subtab-2", ImVec2(ImGuiHelper::getWidth(), 50), { "General", "Weapons", "Other" }, selectedSubTab2);
    ImGui::Spacing();

    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0, 0, 0, 0));
    ImGui::BeginChild("modules-wrapper", ImVec2(ImGuiHelper::getWidth(), ImGuiHelper::getHeight()), false);
    ImGui::PopStyleColor();

    switch (selectedSubTab2) {
    case 0: {
        ImGui::Columns(2, nullptr, false);
        ImGui::SetColumnOffset(1, 500);

        ImGui::Checkbox("Global Misc Switch", &cfg.misc.bEnable);

        ImGui::Text("Client");
        ImGui::BeginChild("Client settings misc", ImVec2(ImGuiHelper::getWidth(), ImGuiHelper::getHeight()), true);
        ImGui::Checkbox("Enable", &cfg.misc.client.bEnable);
        ImGui::Checkbox("Ship Info", &cfg.misc.client.bShipInfo);
        ImGui::Checkbox("Map Pins", &cfg.misc.client.b_map_pins);
        ImGui::Checkbox("Cooking Timer", &cfg.misc.client.b_cooking_timer);
        ImGui::SliderFloat("FOV", &cfg.misc.client.fov, 90.f, 180.f, "%.0f");
        //ImGui::SliderInt("Time", &cfg.misc.client.time, 0, 24, "%.0f");

        ImGui::EndChild();

        ImGui::NextColumn();

        ImGui::Text("Macros");
        ImGui::BeginChild("Macro settings", ImVec2(ImGuiHelper::getWidth(), ImGuiHelper::getHeight()), true);
        ImGui::Checkbox("Enable", &cfg.misc.macro.bEnable);
        ImGui::Checkbox("Bunny Hop", &cfg.misc.macro.b_bunnyhop);
        ImGui::Checkbox("Loot Sprint", &cfg.misc.macro.bLootsprint);
        ImGui::Checkbox("Take Loot from Barrel", &cfg.misc.macro.takelootfrombarreltocrate);
        ImGui::Checkbox("Disable Idle Kick", &cfg.misc.macro.bIdleKick);

        ImGui::EndChild();
        break;
    }
    case 1: {

        ImGui::Text("Under construction");
        break;
    }
    case 2: {
        ImGui::Text("Players List");
        ImGui::BeginChild("Players List", ImVec2(ImGuiHelper::getWidth(), 400), true);
        ImGui::Checkbox("Enable", &cfg.misc.game.bEnable);
        ImGui::Checkbox("Show Players List", &cfg.misc.game.bShowPlayers);
        ImGui::EndChild();

        ImGui::Text("XMarks");
        ImGui::BeginChild("XMarks", ImVec2(ImGuiHelper::getWidth(), ImGuiHelper::getHeight()), true);
        ImGui::Checkbox("Enable", &cfg.misc.xmarks.bEnable);
        break;
    }
    }
}

void Cheat::Renderer::renderSubTab3() {
    ImGuiHelper::drawTabHorizontally("subtab-3", ImVec2(ImGuiHelper::getWidth(), 50), { "Fishing", "SOON", "SOON"}, selectedSubTab3);
    ImGui::Spacing();

    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0, 0, 0, 0));
    ImGui::BeginChild("modules-wrapper", ImVec2(ImGuiHelper::getWidth(), ImGuiHelper::getHeight()), false);
    ImGui::PopStyleColor();

    switch (selectedSubTab3) {
    case 0: {
       // ImGui::Columns(2, nullptr, false);
      //  ImGui::SetColumnOffset(1, 500);

        //ImGui::Checkbox("Global Misc Switch", &cfg.misc.bEnable);

        ImGui::Text("Fishing Bot");
        ImGui::BeginChild("Fishing Bot", ImVec2(ImGuiHelper::getWidth(), ImGuiHelper::getHeight()), true);
        ImGui::Checkbox("Enable", &cfg.fishing.bEnable);
        ImGui::EndChild();
        break;
    }
    case 1: {
        break;
    }
    case 2: {
        break;
    }
    }
}

void Cheat::Renderer::renderLogo()
{ 
    ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0.f);
    ImGui::BeginGroup(); { // group it so we can redirect to Website when its pressed
        ImGui::BeginChild("Logo", ImVec2(158, 50), true, ImGuiWindowFlags_NoScrollbar);

        //sf::Sprite sprite(*logoTx);
        //ImGui::Image(sprite);

        ImGui::PushFont(title_font);
        ImGui::SameLine();

        ImGui::SetCursorPos(ImVec2(30, 11)); // dont know how to center it sorry :>
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(255, 20, 147, 255));
        ImGui::Text("crazy name");
        ImGui::PopStyleColor();
        ImGui::PopFont();

        ImGui::EndChild();

        /* if (ImGui::IsItemClicked(1)) { // redirect to a website/discord on right click
             ::ShellExecuteA(NULL, obf("open").c_str(), obf("https://www.youtube.com/watch?v=dQw4w9WgXcQ").c_str(), NULL, NULL, SW_SHOWDEFAULT);
         }*/

        ImGui::EndGroup();
    }
    ImGui::PopStyleVar();
}

void Cheat::Renderer::renderUser() {

    ImGuiStyle* style = &ImGui::GetStyle();
    int height = 80;
    ImGui::Dummy(ImVec2(0.0f, ImGui::GetContentRegionAvail().y - height - style->ItemSpacing.y));
    ImGui::PushFont(font);
    ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0.f);
    ImGui::BeginChild("User", ImVec2(158, height), true, ImGuiWindowFlags_NoScrollbar);
    ImGui::SetCursorPosX(30);
    if (ImGui::Button("Save Settings"))
    {
        do {
            wchar_t buf[MAX_PATH];
            GetModuleFileNameW(hinstDLL, buf, MAX_PATH);
            fs::path path = fs::path(buf).remove_filename() / ".settings";
            auto file = CreateFileW(path.wstring().c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
            if (file == INVALID_HANDLE_VALUE) break;
            DWORD written;
            if (WriteFile(file, &cfg, sizeof(cfg), &written, 0)) ImGui::OpenPopup("##SettingsSaved");
            CloseHandle(file);
        } while (false);
    }
    ImGui::SetCursorPosX(30);
    if (ImGui::Button("Load Settings"))
    {
        do {
            wchar_t buf[MAX_PATH];
            GetModuleFileNameW(hinstDLL, buf, MAX_PATH);
            fs::path path = fs::path(buf).remove_filename() / ".settings";
            auto file = CreateFileW(path.wstring().c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
            if (file == INVALID_HANDLE_VALUE) break;
            DWORD readed;
            if (ReadFile(file, &cfg, sizeof(cfg), &readed, 0))  ImGui::OpenPopup("##SettingsLoaded");
            CloseHandle(file);
        } while (false);
    }
    //ImGui::TextUnformatted("User:");
    //ImGui::TextUnformatted("xyz");
    ImGui::PopStyleVar();
    ImGui::PopFont();

    ImGui::EndChild();
}
void Cheat::Renderer::renderTabs() {
    ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0.f);
    ImGui::BeginChild("tabs", ImVec2(158, 220), true);

    /*ImGuiTextFilter2 filter;
    filter.Draw2(ICON_FA_SEARCH" search"), 140);*/
    ImGui::Spacing();

    ImVec4 col(0, 0, 0, 0);
    ImVec4 col2(255, 20, 147, 225);
    ImVec4 coltext(255, 255, 255, 255);
    ImGuiStyle* style = &ImGui::GetStyle();

    style->Colors[ImGuiCol_Button] = ImColor(255, 20, 147, 225);
    style->Colors[ImGuiCol_ButtonActive] = ImColor(255, 20, 147, 225);
    style->Colors[ImGuiCol_ButtonHovered] = ImColor(41, 40, 41, 255);

    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5); // round buttons
    std::string tabNames[] = { (ICON_FA_CROSSHAIRS " aimbot"), ICON_FA_EYE " visuals", ICON_FA_COG " misc", ICON_FA_BOOK " automation" };
    for (int i = 0; i < sizeof(tabNames) / sizeof(tabNames[0]); i++) {
        std::string it = tabNames[i];
        //ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0, 0.5));
        //ImGui::PushStyleColor(ImGuiCol_Button, selectedTab == i ? col2 : col);
       //ImGui::PushStyleColor(ImGuiCol_Text, selectedTab == i ? col2 : coltext);
        //ImGui::PushStyleColor(ImGuiCol_ButtonActive, col2);
        if (ImGui::Button(it.c_str(), ImVec2(140, 40))) selectedTab = i;
       // ImGui::PopStyleVar();
        //ImGui::PopStyleColor(2);
    }
    ImGui::PopStyleVar(2);

    ImGui::EndChild();
}

inline bool Cheat::Renderer::Remove()
{
    Renderer::RemoveInput(); 
    if (!RemoveHook(PresentOriginal) || !RemoveHook(ResizeOriginal) || !RemoveHook(SetCursorPosOriginal) || !RemoveHook(SetCursorOriginal))
    {
        return false;
    }
    if (renderTargetView)
    {
        ImGui_ImplDX11_Shutdown();
        ImGui::DestroyContext();
        renderTargetView->Release();
        renderTargetView = nullptr;
    }
    if (context)
    {
        context->Release();
        context = nullptr;
    }
    if (device)
    {
        device->Release();
        device = nullptr;
    }
    return true;
}

inline bool Cheat::Tools::CompareByteArray(BYTE* data, BYTE* sig, SIZE_T size)
{
    for (SIZE_T i = 0; i < size; i++) {
        if (data[i] != sig[i]) {
            if (sig[i] == 0x00) continue;
            return false;
        }
    }
    return true;
}
//aa
inline BYTE* Cheat::Tools::FindSignature(BYTE* start, BYTE* end, BYTE* sig, SIZE_T size)
{
    for (BYTE* it = start; it < end - size; it++) {
        if (CompareByteArray(it, sig, size)) {
            return it;
        };
    }
    return 0;
}

void* Cheat::Tools::FindPointer(BYTE* sig, SIZE_T size, int addition = 0)
{
    auto base = static_cast<BYTE*>(gBaseMod.lpBaseOfDll);
    auto address = FindSignature(base, base + gBaseMod.SizeOfImage - 1, sig, size);
    if (!address) return nullptr;
    auto k = 0;
    for (; sig[k]; k++);
    auto offset = *reinterpret_cast<UINT32*>(address + k);
    return address + k + 4 + offset + addition;
}

inline BYTE* Cheat::Tools::FindFn(HMODULE mod, BYTE* sig, SIZE_T sigSize)
{
    if (!mod || !sig || !sigSize) return 0;
    MODULEINFO modInfo;
    if (!K32GetModuleInformation(GetCurrentProcess(), mod, &modInfo, sizeof(MODULEINFO))) return 0;
    auto base = static_cast<BYTE*>(modInfo.lpBaseOfDll);
    auto fn = Tools::FindSignature(base, base + modInfo.SizeOfImage - 1, sig, sigSize);
    if (!fn) return 0;
    for (; *fn != 0xCC && *fn != 0xC3; fn--);
    fn++;
    return fn;
}

inline bool Cheat::Tools::PatchMem(void* address, void* bytes, SIZE_T size)
{
    DWORD oldProtection;
    if (VirtualProtect(address, size, PAGE_EXECUTE_READWRITE, &oldProtection))
    {
        memcpy(address, bytes, size);
        return VirtualProtect(address, size, oldProtection, &oldProtection);
    };
    return false;
}

/*inline bool Cheat::Tools::HookVT(void** vtable, UINT64 index, void* FuncH, void** FuncO)
{
    if (!vtable || !FuncH || !vtable[index]) return false;
    if (FuncO) { *FuncO = vtable[index]; }
    PatchMem(&vtable[index], &FuncH, 8);
    return FuncH == vtable[index];
}*/

inline BYTE* Cheat::Tools::PacthFn(HMODULE mod, BYTE* sig, SIZE_T sigSize, BYTE* bytes, SIZE_T bytesSize)
{
    if (!mod || !sig || !sigSize || !bytes || !bytesSize) return 0;
    auto fn = FindFn(mod, sig, sigSize);
    if (!fn) return 0;
    return Tools::PatchMem(fn, bytes, bytesSize) ? fn : 0;
}

inline bool Cheat::Tools::FindNameArray()
{
    static BYTE sig[] = { 0x48, 0x89, 0x3D, 0x00, 0x00, 0x00, 0x00, 0x41, 0x8B, 0x75, 0x00 };
    auto address = reinterpret_cast<decltype(FName::GNames)*>(FindPointer(sig, sizeof(sig)));
    if (!address) return 0;
    Logger::Log("%p\n", address);
    FName::GNames = *address;
    return FName::GNames;
}

inline bool Cheat::Tools::FindObjectsArray()
{
    static BYTE sig[] = { 0x48, 0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x81, 0x4C, 0xD1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0x8D, 0x4D, 0xD8 };
    UObject::GObjects = reinterpret_cast<decltype(UObject::GObjects)>(FindPointer(sig, sizeof(sig)));
    return UObject::GObjects;
}

inline bool Cheat::Tools::FindWorld()
{
    static BYTE sig[] = { 0x48, 0x8B, 0x05, 0x00, 0x00, 0x00, 0x00, 0x48, 0x8B, 0x88, 0x00, 0x00, 0x00, 0x00, 0x48, 0x85, 0xC9, 0x74, 0x06, 0x48, 0x8B, 0x49, 0x70 };
    UWorld::GWorld = reinterpret_cast<decltype(UWorld::GWorld)>(FindPointer(sig, sizeof(sig)));
    return UWorld::GWorld;
}

inline bool Cheat::Tools::InitSDK()
{
    AthenaGameViewportClient = UObject::FindObject<UAthenaGameViewportClient>("AthenaGameViewportClient Transient.AthenaGameEngine_1.AthenaGameViewportClient_1");
    if (!UCrewFunctions::Init()) return false;
    if (!UKismetMathLibrary::Init()) return false;
    return true;
}

inline bool Cheat::Logger::Init()
{
    fs::path log;
#ifdef STEAM
    wchar_t buf[MAX_PATH];
    if (!GetModuleFileNameW(hinstDLL, buf, MAX_PATH)) return false;
    log = fs::path(buf).remove_filename() / "log.txt";
#else
#ifdef UWPDEBUG
    log = "C:\\Users\\Maxi\\AppData\\Local\\Packages\\Microsoft.SeaofThieves_8wekyb3d8bbwe\\TempState\\log.txt";
#else
    return true;
#endif
#endif
    file = CreateFileW(log.wstring().c_str(), GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    return file != INVALID_HANDLE_VALUE;
}

inline bool Cheat::Logger::Remove()
{
    if (!file) return true;
    return CloseHandle(file);
}

void Cheat::Logger::Log(const char* format, ...)
{
#if defined STEAM || defined UWPDEBUG
    SYSTEMTIME rawtime;
    GetSystemTime(&rawtime);
    char buf[MAX_PATH];
    auto size = GetTimeFormatA(LOCALE_CUSTOM_DEFAULT, 0, &rawtime, "[HH':'mm':'ss] ", buf, MAX_PATH) - 1;
    size += snprintf(buf + size, sizeof(buf) - size, "[TID: 0x%X] ", GetCurrentThreadId());
    va_list argptr;
    va_start(argptr, format);
    size += vsnprintf(buf + size, sizeof(buf) - size, format, argptr);
#if defined LOGFILE
    WriteFile(file, buf, size, NULL, NULL);
#endif
    printf("%s", buf);
    va_end(argptr);
#endif
}

bool Cheat::Init(HINSTANCE _hinstDLL)
{
    hinstDLL = _hinstDLL;

    AllocConsole();						//attaches console	
    freopen("CONOUT$", "w", stdout);	//sets cout to be used with our newly created console

    if (!Logger::Init())
    {
        return false;
    };
    if (!K32GetModuleInformation(GetCurrentProcess(), GetModuleHandleA(nullptr), &gBaseMod, sizeof(MODULEINFO))) 
    {
        return false;
    };
    Logger::Log("Base address: %p\n", gBaseMod.lpBaseOfDll);
    if (!Tools::FindNameArray()) 
    {
        Logger::Log("Can't find NameArray!\n");
        return false;
    }
    Logger::Log("NameArray: %p\n", FName::GNames);
    if (!Tools::FindObjectsArray()) 
    {
        Logger::Log("Can't find ObjectsArray!\n");
        return false;
    } 
    Logger::Log("ObjectsArray: %p\n", UObject::GObjects);
    if (!Tools::FindWorld())
    {
        Logger::Log("Can't find World!\n");
        return false;
    }
    Logger::Log("World: %p\n", UWorld::GWorld);
    if (!Tools::InitSDK())
    {
        Logger::Log("Can't find important objects!\n");
        return false;
    };
    
    if (!Renderer::Init())
    {
        Logger::Log("Can't initialize renderer\n");
        return false;
    }
    Hacks::Init();

#ifdef STEAM
    auto t = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(ClearingThread), nullptr, 0, nullptr);
    if (t) CloseHandle(t);
#endif

    return true;
}

void Cheat::ClearingThread()
{
    while (true) {
        if (GetAsyncKeyState(VK_END) & 1) {
            FreeLibraryAndExitThread(hinstDLL, 0);
        }
        Sleep(20);
    }
}

void Cheat::Tests()
{
    /*
    auto world = *UWorld::GWorld;
    auto localController = world->GameInstance->LocalPlayers[0]->PlayerController;
    Logger::Log("%p\n", localController);
    */
}


bool Cheat::Remove()
{

    Logger::Log("Removing cheat...\n");
    
    if (!Renderer::Remove() || !Logger::Remove())
    {
        return false;
    };

    Hacks::Remove();

    //Hacks::Remove();

    // some other stuff...

    FreeConsole();

    return true;
}
