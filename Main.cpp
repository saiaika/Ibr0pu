Iske andar addd kar do esp aimbot ka setup bhi dialog se call karna full jo tumne popup bnaya hai ise add kaaro 
#include "Helper/include.h"
#include "Helper/definition.h"
#include "Items.h"
json items_data;
std::map<int, bool> Items;

#if defined(__aarch64__)
#include <And64InlineHook/And64InlineHook.hpp>
#include "KittyMemory/MemoryPatch.h"
#else 
#include <Substrate/SubstrateHook.h>
#include <Substrate/CydiaSubstrate.h>
#endif

void fuck(void *offset, void* ptr, void **orig)
{
#if defined(__aarch64__)
    A64HookFunction(offset, ptr, orig);
#else
    MSHookFunction(offset, ptr, orig);
#endif
}
void GetLocalPlayer()
{
    if (auto GWorld = GetWorld())
    {
        if (auto NetDriver = GWorld->NetDriver)
        {
            if (auto ServerConnection = NetDriver->ServerConnection)
            {
                if (auto localController = (ASTExtraPlayerController *)ServerConnection->PlayerController)
                {
                    if (auto localPlayer = (ASTExtraPlayerCharacter *)localController->AcknowledgedPawn)
                    {
                        Cheat::localController = localController;
                        Cheat::localPlayer = localPlayer;
                    }
                }
            }
        }
    }
}


void clampAngles(FRotator &angles)
{
    if (angles.Pitch > 180)
        angles.Pitch -= 360;
    if (angles.Pitch < -180)
        angles.Pitch += 360;
    if (angles.Pitch < -75.f)
        angles.Pitch = -75.f;
    else if (angles.Pitch > 75.f)
        angles.Pitch = 75.f;
    while (angles.Yaw < -180.0f)
        angles.Yaw += 360.0f;
    while (angles.Yaw > 180.0f)
        angles.Yaw -= 360.0f;
}
ImColor outlinecolor = IM_COL32(5, 5, 5, 240);
void DrawESP(ImDrawList *draw)
{


static float rainbowHue = 0.0f; 
rainbowHue += 0.001f; 
if (rainbowHue > 1.0f)
    rainbowHue = 0.0f;
ImVec4 rainbowColor = ImColor::HSV(rainbowHue, 1.0f, 1.0f);
std::string Loda = "                                       Telegram : @owner824";
auto LodaTextSize = ImGui::CalcTextSize2(Loda.c_str(), 0, 20.0f);
float LodaPosX = 10.0f;  
float LodaPosY = glHeight - LodaTextSize.y - 10.0f;
ImU32 rainbowColorU32 = ImGui::ColorConvertFloat4ToU32(rainbowColor);
DrawTextWithBorder(draw, Loda, {LodaPosX, LodaPosY}, rainbowColorU32, outlinecolor, 20.0f);
static USTExtraGameInstance *Instance = nullptr;
if (!Instance) Instance = UObject::FindObject<USTExtraGameInstance>("STExtraGameInstance Transient.UAEGameEngine_1.STExtraGameInstance_1");
                      
    if (Instance != nullptr)
    {
        auto& UserSettings = Instance->UserDetailSetting;
              UserSettings.PUBGDeviceFPSDef = 120;
              UserSettings.PUBGDeviceFPSLow = 120;
              UserSettings.PUBGDeviceFPSMid = 120;
              UserSettings.PUBGDeviceFPSHigh = 120;
              UserSettings.PUBGDeviceFPSHDR = 120;
              UserSettings.PUBGDeviceFPSUltralHigh = 120;
              UserSettings.DeviceMaxQualityLevel = 3;
    }
	
	
	static ULocalPlayer *UlocalPlayer = nullptr;
    if (!UlocalPlayer)
    {
        UlocalPlayer = UObject::FindObject<ULocalPlayer>("LocalPlayer Transient.UAEGameEngine_1.LocalPlayer_1");
    }

    if (UlocalPlayer == nullptr)
        return;

if (Cheat::localController != nullptr){
MemoryPatch::createWithHex("libhdmpve.so",0x1560B8,"C0 03 5F D6").Modify();
MemoryPatch::createWithHex("libhdmpve.so",0x155DFC,"C0 03 5F D6").Modify();
}
    if (Cheat::localPlayer && Cheat::localController)
    {
    if (Cheat::Aimbot::Enable)
    {
    draw->AddCircle(ImVec2(glWidth / 2.0f, glHeight / 2.0f), Cheat::Aimbot::Radius * 0.5f, IM_COL32(255, 255, 255, 255), 100, 0.5f);
    }


     int totalEnemies = 0, totalBots = 0;
	 if (Cheat::localPlayer)
        {
            if (Cheat::localPlayer->PartHitComponent)
            {
                auto ConfigCollisionDistSqAngles = Cheat::localPlayer->PartHitComponent->ConfigCollisionDistSqAngles;
                for (int j = 0; j < ConfigCollisionDistSqAngles.Num(); j++)
                {
                    ConfigCollisionDistSqAngles[j].Angle = 180.0f;
                }
                Cheat::localPlayer->PartHitComponent->ConfigCollisionDistSqAngles = ConfigCollisionDistSqAngles;
            }
            
            

if (Cheat::Esp::Target){
auto Target = GetTargetForAimBot();
if (Target) {
auto target = Target->GetBonePos("Head", {});
auto footL = Target->GetBonePos("Root", {});
ImVec2 targetSC, footLPos;
if (W2S(target, (FVector2D*)&targetSC) && W2S(footL, (FVector2D*)&footLPos))
{
draw->AddLine({(float)glWidth / 2, 716}, {footLPos.x - 2, footLPos.y},IM_COL32(255, 0, 0, 255), 1.9f);
}}}
            
            if (Cheat::Aimbot::Enable){
uintptr_t Mesh = *(uintptr_t *)((uintptr_t) Cheat::localPlayer + 0x498);
if (Mesh != 0)
{
    uintptr_t Skeletal = *(uintptr_t *)(Mesh + 0x868);
    if (Skeletal != 0)
    {
        uintptr_t Asset = *(uintptr_t *)(Skeletal + 0x138);
        if (Asset != 0)
        {
            uintptr_t ArraySkeletal = *(uintptr_t *)(Asset + 0x38);
            if (ArraySkeletal != 0)
            {
                uintptr_t SkeletalBodySetup = *(uintptr_t *)(ArraySkeletal + sizeof(uintptr_t) * 14);

                if (SkeletalBodySetup != 0)
                {
                    uintptr_t BoxElems = *(uintptr_t *)(SkeletalBodySetup + 0x38);
                    if (BoxElems != 0)
                    {
                        *(float *)(BoxElems + 0x88) = -1000.0f;
                        *(float *)(BoxElems + 0x8c) = 200.0f;
                        *(float *)(BoxElems + 0x90) = 1000.0f;
}}}}}}}

			if (Cheat::Esp::WideView)
               Cheat::localPlayer->ThirdPersonCameraComponent->SetFieldOfView(Cheat::Esp::WideViewRange);
					
            if (Cheat::Aimbot::Enable)
            {
                ASTExtraPlayerCharacter *Target = GetTargetForAimBot();
                if (Target)
                {
                    if (Cheat::localPlayer->bIsWeaponFiring || Cheat::localPlayer->bIsGunADS)
                    {
                        FVector targetAimPos = Target->GetBonePos("Head", {});

                        if (auto WeaponManagerComponent = Cheat::localPlayer->WeaponManagerComponent)
                        {
                            auto PropSlot = WeaponManagerComponent->GetCurrentUsingPropSlot();

                            if ((int)PropSlot.GetValue() >= 1 && (int)PropSlot.GetValue() <= 3)
                            {
                                if (auto CurrentWeaponReplicated = (ASTExtraShootWeapon *)WeaponManagerComponent->CurrentWeaponReplicated)
                                {
                                    if (auto ShootWeaponComponent = CurrentWeaponReplicated->ShootWeaponComponent)
                                    {
                                        if (auto ShootWeaponEntityComponent = ShootWeaponComponent->ShootWeaponEntityComponent)
                                        {
                                            float BulletFireSpeed = CurrentWeaponReplicated->GetBulletFireSpeedFromEntity();

                                            if (auto CurrentVehicle = Target->CurrentVehicle)
                                            {
                                                FVector LinearVelocity = CurrentVehicle->ReplicatedMovement.LinearVelocity;
                                                float dist = Cheat::localPlayer->GetDistanceTo(Target);
                                                auto timeToTravel = dist / BulletFireSpeed;
                                                targetAimPos = targetAimPos + MultiplyVectorFloat(LinearVelocity, timeToTravel);
                                            }
                                            else
                                            {
                                                FVector Velocity = Target->GetVelocity();
                                                float dist = Cheat::localPlayer->GetDistanceTo(Target);
                                                auto timeToTravel = dist / BulletFireSpeed;
                                                targetAimPos = targetAimPos + MultiplyVectorFloat(Velocity, timeToTravel);
                                            }
                                            if (Cheat::Aimbot::Enable)
                                            {
                                                if (Cheat::localPlayer->bIsGunADS)
                                                {
                                                    float dist = Cheat::localPlayer->GetDistanceTo(Target) / 100.f;
                                                    targetAimPos.Z -= dist * Cheat::Aimbot::RecoilControl;
                                                }
                                            }
                                            FVector gunlocation = Cheat::localController->PlayerCameraManager->CameraCache.POV.Location;
                                            FRotator aimrotation = ToRotator(gunlocation, targetAimPos);
                                            FRotator gunrotaton = Cheat::localController->PlayerCameraManager->CameraCache.POV.Rotation;

                                            aimrotation.Pitch -= gunrotaton.Pitch;
                                            aimrotation.Yaw -= gunrotaton.Yaw;
                                            aimrotation.Roll = 0.0f;

                                            clampAngles(aimrotation);

                                            gunrotaton.Pitch += aimrotation.Pitch / 4.0f;
                                            gunrotaton.Yaw += aimrotation.Yaw / 4.0f;
                                            gunrotaton.Roll = 0.0f;
                                            

                                            Cheat::localController->SetControlRotation(gunrotaton, "");
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        auto Actors = GetActors();
        for (auto &Actor : Actors)
        {
                           if (isObjectInvalid(Actor))
                            continue;
                        if (Actor->IsA(ASTExtraPlayerCharacter::StaticClass())) {
                            ImU32 PlayerBone;
                            ImU32 PlayerLine;
                            ImU32 BotLine;
                            ImU32 BotBone;
                            ImU32 PlayerAlert;
                            ImU32 BotAlert;
                            auto Player = (ASTExtraPlayerCharacter *) Actor;
                            bool IsVisible = Cheat::localController->LineOfSightTo(Player, {0, 0, 0},
                                                                            true);

                            if (IsVisible) {
                                BotBone = IM_COL32(97, 255, 97, 255);
                                PlayerBone = IM_COL32(97, 255, 97, 255);
                                PlayerLine = IM_COL32(97, 255, 97, 255);
                                BotLine = IM_COL32(97, 255, 97, 255);
                            } else {
                                BotBone = IM_COL32(41, 180, 255, 255);
                                PlayerBone = IM_COL32(255, 79, 79, 255);
                                PlayerLine = IM_COL32(41, 180, 255, 255);
                                BotLine = IM_COL32(41, 180, 255, 255);
                            }
                            float Distance = Cheat::localPlayer->GetDistanceTo(Player) / 100.0f;
                            
                            if (Distance > 500.0f)                            
                                continue;
                                                        
                            if (Player->PlayerKey == Cheat::localController->PlayerKey)                            
                                continue;
                            

                            if (Player->TeamID == Cheat::localController->TeamID)                            
                                continue;              
                                              
                            if (Player->bDead)                                    
                                continue;
                            
                            if(Player->bHidden)
                               continue;

                            if (Player->bEnsure)
                                totalBots++;
                            else
                                totalEnemies++;

                                                                   
                            float magic_number = (Distance);
                            float mx = (glWidth / 4) / magic_number;

                            float healthLength = glWidth / 17;
                            if (healthLength < mx)
                                healthLength = mx;
                            auto HeadPos = Player->GetBonePos("Head", {});                            
                            ImVec2 headPosSC;


                            auto RootPos = Player->GetBonePos("Root", {});
                            ImVec2 RootPosSC;

                            if (W2S(HeadPos, (FVector2D *)&headPosSC) && W2S(RootPos, (FVector2D *)&RootPosSC))
                            {

                                    if (Cheat::Esp::Line) {
                                    draw->AddLine({(float) glWidth / 2, 0}, headPosSC,
                                                  BotBone, 0.5f);
                                }


                                if (Cheat::Esp::Skeleton) {
                                      static std::vector<std::string> right_arm{
        "neck_01", "clavicle_r", "upperarm_r", "lowerarm_r", "hand_r", "item_r"};

    static std::vector<std::string> left_arm{
        "neck_01", "clavicle_l", "upperarm_l", "lowerarm_l", "hand_l", "item_l"};

    static std::vector<std::string> spine{
        "Head", "neck_01", "spine_03", "spine_02", "spine_01", "pelvis"};

    static std::vector<std::string> lower_right{
        "pelvis", "thigh_r", "calf_r", "foot_r"};

    static std::vector<std::string> lower_left{
        "pelvis", "thigh_l", "calf_l", "foot_l"};
                                    static std::vector<std::vector<std::string>> skeleton{right_arm,
                                            left_arm,
                                            spine,
                                            lower_right,
                                            lower_left};

                                    for (auto &boneStructure: skeleton) {
                                        std::string lastBone;
                                        for (std::string &currentBone: boneStructure) {
                                            if (!lastBone.empty()) {
                                                ImVec2 boneFrom, boneTo;
                                                if (W2S(Player->GetBonePos(lastBone.c_str(), {}),
                                                        (FVector2D *) &boneFrom) &&
                                                        W2S(Player->GetBonePos(currentBone.c_str(), {}),
                                                            (FVector2D *) &boneTo)) {

                                                    if (Player->bEnsure) {
                                                        draw->AddLine(boneFrom, boneTo,
                                                                       BotBone, 1.0f);
                                                    } else {

                                                        draw->AddLine(boneFrom, boneTo,
                                                                      PlayerBone, 1.0f);
                                                    }
                                                }
                                            }
                                            lastBone = currentBone;
                                        }
                                    }
                                }
								if (Cheat::Esp::Box)
                        {
                            float boxHeight = abs(headPosSC.y - RootPosSC.y);
                            float boxWidth = boxHeight * 0.65f;

                            int iw = boxWidth / 4;
                            int ih = boxHeight / 4;
                            // top
                            bool isVisible1 = Cheat::localController->LineOfSightTo(Cheat::localController->PlayerCameraManager, Player->GetBonePos("hand_r", {}), true);
                            if (isVisible1)
                            {
                                draw->AddRect(ImVec2(headPosSC.x - (boxWidth / 2), headPosSC.y), ImVec2(headPosSC.x - (boxWidth / 2) + iw, headPosSC.y), IM_COL32(255, 0, 0, 255), 0.2f);
                                draw->AddRect(ImVec2(headPosSC.x - (boxWidth / 2) + boxWidth - iw, headPosSC.y), ImVec2(headPosSC.x - (boxWidth / 2) + boxWidth, headPosSC.y), IM_COL32(255, 0, 0, 255), 0.2f);
                            }
                            else
                            {
                                draw->AddRect(ImVec2(headPosSC.x - (boxWidth / 2), headPosSC.y), ImVec2(headPosSC.x - (boxWidth / 2) + iw, headPosSC.y), IM_COL32(255, 255, 255, 255), 0.2f);
                                draw->AddRect(ImVec2(headPosSC.x - (boxWidth / 2) + boxWidth - iw, headPosSC.y), ImVec2(headPosSC.x - (boxWidth / 2) + boxWidth, headPosSC.y), IM_COL32(255, 255, 255, 255), 0.2f);
                            }
                            bool isVisible12 = Cheat::localController->LineOfSightTo(Cheat::localController->PlayerCameraManager, Player->GetBonePos("hand_l", {}), true);
                            if (isVisible12)
                            {
                                draw->AddRect(ImVec2(headPosSC.x - (boxWidth / 2), headPosSC.y), ImVec2(headPosSC.x - (boxWidth / 2), headPosSC.y + ih), IM_COL32(255, 0, 0, 255), 0.2f);
                                draw->AddRect(ImVec2(headPosSC.x - (boxWidth / 2) + boxWidth - 1, headPosSC.y), ImVec2(headPosSC.x - (boxWidth / 2) + boxWidth - 1, headPosSC.y + ih), IM_COL32(255, 0, 0, 255), 0.2f);
                            }
                            else
                            {
                                draw->AddRect(ImVec2(headPosSC.x - (boxWidth / 2), headPosSC.y), ImVec2(headPosSC.x - (boxWidth / 2), headPosSC.y + ih), IM_COL32(255, 255, 255, 255), 0.2f);
                                draw->AddRect(ImVec2(headPosSC.x - (boxWidth / 2) + boxWidth - 1, headPosSC.y), ImVec2(headPosSC.x - (boxWidth / 2) + boxWidth - 1, headPosSC.y + ih), IM_COL32(255, 255, 255, 255), 0.2f);
                            }
                            bool isVisible123 = Cheat::localController->LineOfSightTo(Cheat::localController->PlayerCameraManager, Player->GetBonePos("foot_r", {}), true);

                            if (isVisible123)
                            {
                                draw->AddRect(ImVec2(headPosSC.x - (boxWidth / 2), headPosSC.y + boxHeight), ImVec2(headPosSC.x - (boxWidth / 2) + iw, headPosSC.y + boxHeight), IM_COL32(255, 0, 0, 255), 0.2f);
                                draw->AddRect(ImVec2(headPosSC.x - (boxWidth / 2) + boxWidth - iw, headPosSC.y + boxHeight), ImVec2(headPosSC.x - (boxWidth / 2) + boxWidth, headPosSC.y + boxHeight), IM_COL32(255, 0, 0, 255), 0.2f);
                            }
                            else
                            {
                                draw->AddRect(ImVec2(headPosSC.x - (boxWidth / 2), headPosSC.y + boxHeight), ImVec2(headPosSC.x - (boxWidth / 2) + iw, headPosSC.y + boxHeight), IM_COL32(255, 255, 255, 255), 0.2f);
                                draw->AddRect(ImVec2(headPosSC.x - (boxWidth / 2) + boxWidth - iw, headPosSC.y + boxHeight), ImVec2(headPosSC.x - (boxWidth / 2) + boxWidth, headPosSC.y + boxHeight), IM_COL32(255, 255, 255, 255), 0.2f);
                            }
                            bool isVisible1234 = Cheat::localController->LineOfSightTo(Cheat::localController->PlayerCameraManager, Player->GetBonePos("foot_l", {}), true);
                            if (isVisible1234)
                            {
                                draw->AddRect(ImVec2(headPosSC.x - (boxWidth / 2), headPosSC.y + boxHeight - ih), ImVec2(headPosSC.x - (boxWidth / 2), headPosSC.y + boxHeight), IM_COL32(255, 0, 0, 255), 0.2f);
                                draw->AddRect(ImVec2(headPosSC.x - (boxWidth / 2) + boxWidth - 1, headPosSC.y + boxHeight - ih), ImVec2(headPosSC.x - (boxWidth / 2) + boxWidth - 1, headPosSC.y + boxHeight), IM_COL32(255, 0, 0, 255), 0.2f);
                            }
                            else
                            {
                                draw->AddRect(ImVec2(headPosSC.x - (boxWidth / 2), headPosSC.y + boxHeight - ih), ImVec2(headPosSC.x - (boxWidth / 2), headPosSC.y + boxHeight), IM_COL32(255, 255, 255, 255), 0.2f);
                                draw->AddRect(ImVec2(headPosSC.x - (boxWidth / 2) + boxWidth - 1, headPosSC.y + boxHeight - ih), ImVec2(headPosSC.x - (boxWidth / 2) + boxWidth - 1, headPosSC.y + boxHeight), IM_COL32(255, 255, 255, 255), 0.2f);
                            }
                            }
                                if (Cheat::Esp::TeamID || Cheat::Esp::Name || Cheat::Esp::Distance) {
                                    ImGuiStyle &style = ImGui::GetStyle();
                                    ImVec4 savedTextColor = style.Colors[ImGuiCol_Text];
                                    style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

                                    std::string s;

									if (Cheat::Esp::Name) {
                                	if (Player->bEnsure) {
	          	s += " ";
	        	s += "Kidz";
            	}else{
	            s += Player->PlayerName.ToString();
	            }	  	
	            auto textSize = ImGui::CalcTextSize(s.c_str(), 0, ((float) density / 50.0f));
                draw->AddText(NULL,12,ImVec2(headPosSC.x - 4.4 - (textSize.x / 5) ,  headPosSC.y- 28.f),IM_COL32(0,0,0,255),s.c_str());
                draw->AddText(NULL,12,ImVec2(headPosSC.x - 2.4 - (textSize.x / 5) ,  headPosSC.y- 26.f),IM_COL32(0,0,0,255),s.c_str());
                draw->AddText(NULL,12,ImVec2(headPosSC.x - 2.4 - (textSize.x / 5) ,  headPosSC.y- 28.f),IM_COL32(0,0,0,255),s.c_str());
                draw->AddText(NULL,12,ImVec2(headPosSC.x - 4.4 - (textSize.x / 5) ,  headPosSC.y- 26.f),IM_COL32(0,0,0,255),s.c_str());
                draw->AddText(NULL,12,ImVec2(headPosSC.x - 3.4 - (textSize.x / 5) ,  headPosSC.y- 28.f),IM_COL32(0,0,0,255),s.c_str());
                draw->AddText(NULL,12,ImVec2(headPosSC.x - 3.4 - (textSize.x / 5) ,  headPosSC.y- 26.f),IM_COL32(0,0,0,255),s.c_str());
                draw->AddText(NULL,12,ImVec2(headPosSC.x - 4.4 - (textSize.x / 5) ,  headPosSC.y- 27.f),IM_COL32(0,0,0,255),s.c_str());
                draw->AddText(NULL,12,ImVec2(headPosSC.x - 2.4 - (textSize.x / 5) ,  headPosSC.y- 27.f),IM_COL32(0,0,0,255),s.c_str());
              	draw->AddText(NULL,12,ImVec2(headPosSC.x - 3.4 - (textSize.x / 5) ,  headPosSC.y- 27.f),IM_COL32(255, 255, 0, 255),s.c_str());
                }   
				                    if (Cheat::Esp::Distance) {
                                 float boxWidth = density / 1.6f;
                                boxWidth -= std::min(((boxWidth / 2) / 00.0f) * Distance,
                                                     boxWidth / 2);
                                float boxHeight = boxWidth * 0.13f;


                                std::string s;
								s += " ";
                                s += std::to_string((int) Distance);
                                s += "M";
                                   auto textSize = ImGui::CalcTextSize(s.c_str(), 0, ((float) density / 30.0f)); 						

                                    float strokeSize = 1.5f;
                                    for (float x = -strokeSize; x <= strokeSize; x += strokeSize) {
                                        for (float y = -strokeSize;
                                             y <= strokeSize; y += strokeSize) {
                                            draw->AddText(NULL, ((float) density / 36.0f),
                                                          {RootPosSC.x - (textSize.x / 2) + x,
                                                           RootPosSC.y + y}, IM_COL32(0, 0, 0, 155),
                                                          s.c_str());
                                        }
                                    }

                                    draw->AddText(NULL, ((float) density / 36.0f),
                                                  {RootPosSC.x - (textSize.x / 2), RootPosSC.y},
                                                  IM_COL32(7, 164, 242, 255), s.c_str());

                                    style.Colors[ImGuiCol_Text] = savedTextColor;
                                    }
                             if (Cheat::Esp::Health)
                           {
                            int CurHP = (int)std::max(0, std::min((int)Player->Health, (int)Player->HealthMax));
                        int MaxHP = (int)Player->HealthMax;
                        ImU32 color_red = ImColor(255, 25, 25);
                        ImU32 color_orange = ImColor(255, 180, 0);
                        ImU32 color_green = ImColor(50, 230, 50);
                        ImU32 current_color = color_green;
                        float health = Player->Health;

                        if (health <= 50.0f) {
                            current_color = color_orange;
                        }
                            
                        if (health <= 25.0f) {
                            current_color = color_red;
                        }

                            float boxHeight = abs(headPosSC.y - RootPosSC.y);
                            float boxWidth = 5.0f;
                            ImVec2 vStart = {headPosSC.x + 15.0f + (boxWidth / 2), headPosSC.y};
                            ImVec2 vEnd = {vStart.x + boxWidth, vStart.y + boxHeight};                        
                            ImVec2 vEndFilled = {vStart.x + (CurHP * boxWidth / MaxHP),
                                                 vStart.y + boxHeight};
                            ImVec2 vEndRect = {vStart.x + boxWidth, vStart.y + boxHeight};
                            draw->AddRectFilled(vStart, vEndFilled, current_color);
                            //draw->AddRect(vStart, vEndRect, IM_COL32(0, 0, 0, 155));
                            //draw->AddRect(vStart, vEndRect, IM_COL32(0, 0, 0, 155));
                        }
						}
						
						
						
	}                        
	}					   
	}                                                          
    if (totalEnemies + totalBots > 0)
    {
    ImGui::SetNextWindowPos(ImVec2((float)glWidth / 2, 60), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
    ImGui::SetNextWindowSizeConstraints(ImVec2(0, 0), ImVec2((float)glWidth, (float)glHeight));
    ImGui::Begin("Total Enemies", nullptr,
    ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings);
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "Total Enemies Around You %d", totalEnemies + totalBots);
    ImGui::End();
	}
    }
    }

EGLBoolean (*orig_eglSwapBuffers)(EGLDisplay dpy, EGLSurface surface);
EGLBoolean _eglSwapBuffers(EGLDisplay dpy, EGLSurface surface)
{
    eglQuerySurface(dpy, surface, EGL_WIDTH, &glWidth);
    eglQuerySurface(dpy, surface, EGL_HEIGHT, &glHeight);

    if (glWidth <= 0 || glHeight <= 0)
        return orig_eglSwapBuffers(dpy, surface);

    if (!g_App)
        return orig_eglSwapBuffers(dpy, surface);

    screenWidth = ANativeWindow_getWidth(g_App->window);
    screenHeight = ANativeWindow_getHeight(g_App->window);
    density = AConfiguration_getDensity(g_App->config);

    if (!initImGui)
    {
        ImGui::CreateContext();
        ImGuiStyle &style = ImGui::GetStyle();
        ImGui::StyleColorsDark();

        ImGui_ImplAndroid_Init();
        ImGui_ImplOpenGL3_Init(OBFUSCATE("#version 300 es"));
        ImGuiIO &io = ImGui::GetIO();

		io.Fonts->AddFontFromMemoryTTF((void *)Custom_data, Custom_size, 20.0f, NULL, 
		io.Fonts->GetGlyphRangesChineseFull());    
        initImGui = true;
    }

    ImGuiIO &io = ImGui::GetIO();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame(glWidth, glHeight);
    ImGui::NewFrame();

    GetLocalPlayer();
    DrawESP(ImGui::GetBackgroundDrawList());

    if (ImGui::Begin((OBFUSCATE("")), 0, ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar))
    {

		static bool isLogin = true;
        static std::string err;
        if (!isLogin) {
            ImGui::Text("Please Login !!");
            ImGui::PushItemWidth(-1);
            static char s[64];
            ImGui::InputText("##key", s, sizeof s);
            // Auto Paste
            auto key = getClipboardText();
            strncpy(s, key.c_str(), sizeof s);
            // Auto Login
            err = Login(s);
            if (err == "OK") {
            isLogin = bValid && g_Auth == g_Token;
            }
            ImGui::PopItemWidth();
            ImGui::PushItemWidth(-1);
            if (ImGui::Button("Paste Your Key", ImVec2(ImGui::GetContentRegionAvailWidth(), 0))) {
            auto key = getClipboardText();
            strncpy(s, key.c_str(), sizeof s);
            }
            ImGui::PopItemWidth();
            ImGui::PushItemWidth(-1);
            if (ImGui::Button("Login", ImVec2(ImGui::GetContentRegionAvailWidth(), 0))) {
            err = Login(s);
            if (err == "OK") {
            isLogin = bValid && g_Auth == g_Token;
            }
            }
            ImGui::PopItemWidth();
            if (!err.empty() && err != "OK") {
            ImGui::Text("Error : %s", err.c_str());
            }
            ImGui::PopItemWidth();
            }else {

		   Cheat::Esp::Name = true;
	       Cheat::Esp::Line = true;
		   Cheat::Esp::Box = true;
           Cheat::Esp::Skeleton = true;
		   Cheat::Esp::Distance = true;
           Cheat::Esp::Health = true;
		   Cheat::Esp::WideView = true;
		   Cheat::Esp::WideViewRange = 110.0f;
           Cheat::Aimbot::Enable = true;
           Cheat::Aimbot::VisCheck = true;
           Cheat::Aimbot::IgnoreKnock = true;
           Cheat::Aimbot::RecoilControl = 1.25f;
           Cheat::Aimbot::Radius = 350.0f;
           Cheat::Aimbot::Range = 500.0f;
           Cheat::Esp::Target = true;
           }
       	   }
    ImGui::End();
    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    return orig_eglSwapBuffers(dpy, surface);
           }
DWORD roosterBase = 0;
DWORD libUE4Base = 0;
DWORD libanogsBase = 0;
DWORD chut = 0;
DWORD libanortBase = 0;
DWORD libanogsAlloc = 0;
DWORD libUE4Alloc = 0;

unsigned int libanogsSize = 0x527520;
unsigned int libUE4Size = 0xAABDA10;

char *Offset;
DWORD NewBase = 0;

__int64 __fastcall (*osub_CBD78)(__int64 a1);
__int64 __fastcall sub_CBD78(__int64 a1)
{
 
     auto ret = reinterpret_cast<uintptr_t>(__builtin_return_address(0)); 
  if ( (ret - libanogsBase) == 0xcd568) {return 0LL;}

  return osub_CBD78(a1);
 
}






void *(*orig_ban_action)(void *arg);
void *(*orig_security_flag)(void *arg);
typedef bool (*CheckBanFlag_t)(void* this_ptr);
CheckBanFlag_t orig_ban_check = nullptr;
bool hooked_ban_check(void* this_ptr) {
    return false;
}




void *hooked_ban_action(void *arg) {
    return NULL;
}

void *hooked_security_flag(void *arg) {
    return (void *)1;
}

void patch_memory(void *addr) {
    uintptr_t base_addr = (uintptr_t)addr & ~(getpagesize() - 1);
    mprotect((void *)base_addr, getpagesize(), PROT_READ | PROT_WRITE | PROT_EXEC);
}

void hook_native_function(const char *lib, const char *symbol, void *hook_func, void **orig_func) {
    void *handle = dlopen(lib, RTLD_LAZY);
    if (!handle) {
        return;
    }

    void *target_func = dlsym(handle, symbol);
    if (!target_func) {
        return;
    }

    patch_memory(target_func);
    *orig_func = target_func;
    *(void **)target_func = hook_func;
}

size_t getLibrarySize(const char *libraryName)
{
    FILE *mapsFile = fopen("/proc/self/maps", "r");
    if (mapsFile == nullptr)
    {
        return 0;
    }

    char line[256];
    size_t size = 0;
    uintptr_t startAddr = 0, endAddr = 0;
    while (fgets(line, sizeof(line), mapsFile))
    {
        if (strstr(line, libraryName))
        {
            sscanf(line, "%lx-%lx", &startAddr, &endAddr);
            size = endAddr - startAddr;
            break;
        }
    }

    fclose(mapsFile);
    return size;
}
__int64 __fastcall JAAT_MODS(__int64 a1, __int64 a2, __int64 a3) {
    uintptr_t ret = reinterpret_cast<uintptr_t>(__builtin_return_address(0));
    if (ret == 0) {
        LOGI("Error: Invalid return address!");
        return -1;  // Return an error code instead of crashing
    }
    LOGI("Return Address: %p", (void*)ret);
    if (ret == 0x1394C0) {
        LOGI("Sleeping for 10 seconds...");
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }
    return a1;
}


void *hook_dlopen(const char *file, int mode) {
    auto ret = reinterpret_cast<uintptr_t>(__builtin_return_address(0));
     uintptr_t libanogsBase;  
    auto AnogsCaller = ret - libanogsBase;
    if (file && strstr(file, "libEGL.so")) { // Patched
        return nullptr; // Use nullptr instead of 0 for pointer return
    }
    if (file && strstr(file, "libm.so")) { // Unpatch
        return nullptr;
    }
    return dlopen(file, mode);
}

void* hook_memcpy(char* dest, const char* src, size_t size) {
    if (size == 0 || size > 0x100000 || !dest || !src) {
        return nullptr;
    }
    void* ret = __builtin_return_address(0);
    Dl_info info;    
    if (dladdr(ret, &info) && info.dli_sname) {
        if (strcmp(info.dli_sname, "suspicious_function") == 0) {
            return nullptr;
        }
    }
    return memcpy(dest, src, size);
} 


typedef __int64 (*UserInfoFunc)(int, int);
UserInfoFunc ouserinfo = nullptr; 
__int64 __fastcall userinfo(int a1, int a2)
{
    if (a1 == 3 || a1 == 4)
    {
        return 0LL;
    }
    if (ouserinfo) 
    {
        return ouserinfo(a1, a2);
    }
    return -1LL; 
}


__int64 __fastcall (*osub_1DD8B4)(__int64 a1, unsigned __int8 *a2, unsigned int a3);
__int64 __fastcall hsub_1DD8B4(__int64 a1, unsigned __int8 *a2, unsigned int a3)
{
    LOGI("CASE = 35 BLOCK, a1 = %lld, a2 = %p, a3 = %u", a1, a2, a3); 
    if (a2 && a3 > 0 && a3 <= 0x400)
    {        
        if (*a2 > 0x10u)
        {
            void *v7 = *(void **)(a1 + 26);
            if (v7)
            {
                *(_WORD *)(a1 + 24) = static_cast<_WORD>(a3);
                memcpy(v7, a2, a3); 
                return 0;
            }
            else
            {
                LOGE("Invalid destination pointer at a1 + 26");
                return -1;
            }
        }
        else
        {
            LOGW("Block detection failed: *a2 = %u", *a2);
            return -2;
        }
    }
    return osub_1DD8B4(a1, a2, a3);
}

_QWORD *__fastcall AnoSDKSetUserInfo(unsigned int a1, char *a2)
{
if(a1 == 3 || a1 == 4)
{  return 0;  }
 return AnoSDKSetUserInfo(a1,a2);
}

bool __fastcall (*osub_1EB7BC)(__int64 a1, __int64 a2, char a3);
bool __fastcall hsub_1EB7BC(__int64 a1, __int64 a2, char a3)
{
    LOGI(OBFUSCATE("Case 16 Calling : a1 -> %lld | a2 -> %s | a3 -> %d"), a1, (const char *)a2, a3);
    const char* str = (const char *)a2;
    if (strstr(str, "opcode_crash") || 
        strstr(str, "opcode_scan") || 
        strstr(str, "zygisk_module"))
    {
        LOGI(OBFUSCATE("Blocked Function | %s is Being Called From Address | %p"), str, (void*)a2);
        pthread_exit(nullptr);
        return false;
    }
    else
    {
        LOGI(OBFUSCATE("Allowed Function | %s is Being Called From Address | %p"), str, (void*)a2);
        return osub_1EB7BC(a1, a2, a3);
    }
}

void *anogs_thread(void *) {
    while (!isLibraryLoaded(OBFUSCATE("libanogs.so"))) {
        sleep(1);
    }
   libanogsBase = findLibrary(OBFUSCATE("libanogs.so"));
HOOK_LIB_NO_ORIG("libanogs.so","0x153F64",AnoSDKSetUserInfo);
HOOK_LIB_NO_ORIG("libanogs.so","0x4D2B28",hook_memcpy);// getofftimeday
HOOK_LIB_NO_ORIG("libanogs.so","0x4DB084",hook_memcpy);
HOOK_LIB_NO_ORIG("libanogs.so","0x138C20",hook_dlopen);// hook_dlopen
HOOK_LIB_NO_ORIG("libanogs.so","0x1ECA70",hook_memcpy);
HOOK_LIB_NO_ORIG("libanogs.so","0x36A758",hook_memcpy);//
HOOK_LIB_NO_ORIG("libanogs.so","0x167574",hook_memcpy);
HOOK_LIB_NO_ORIG("libanogs.so","0x1394C0",hook_memcpy);// crash
HOOK_LIB_NO_ORIG("libanogs.so","0x1FD694",hook_memcpy);//memory Tree 
HOOK_LIB_NO_ORIG("libanogs.so","0x3CE5B0",hook_memcpy);// all ban 
HOOK_LIB_NO_ORIG("libanogs.so","0x4A4CD8",hook_memcpy);// all ban 
HOOK_LIB_NO_ORIG("libanogs.so","0x4A2DD4",hook_memcpy);//day ban=
PATCH_LIB("libanogs.so","0x155FB0","D1 FF FF 17 FC 6F BA A9");
PATCH_LIB("libanogs.so","0x153A00","8A FF FF 17 F4 4F BE A9");
hook_native_function("libanogs.so", "_ZN12GameSecurity12CheckBanFlagEv", (void *)hooked_ban_check, (void **)&orig_ban_check);
hook_native_function("libanogs.so", "_ZN10PlayerData10TriggerBanEv", (void *)hooked_ban_action, (void **)&orig_ban_action);
hook_native_function("libUE4.so", "_ZN14SecurityModule15IsFlaggedPlayerEv", (void *)hooked_security_flag, (void **)&orig_security_flag);
DobbyHook((void *) DobbySymbolResolver(OBFUSCATE("/apex/com.android.runtime/lib64/bionic/libc.so"), OBFUSCATE("AnoSDKSetUserInfo")), (void *) userinfo, (void **) &ouserinfo);
HOOK_LIB_NO_ORIG("libUE4.so","0xBA26240",hook_memcpy);
HOOK_LIB_NO_ORIG("libUE4.so","0xBA26720",hook_memcpy);


    return NULL;
    }
    
    
    
void FixGameCrash()
{
    system("rm -rf /data/data/com.pubg.imobile/files");
    system("rm -rf /data/data/com.pubg.imobile/files/ano_tmp");
    system("touch /data/data/com.pubg.imobile/files/ano_tmp");
    system("chmod 000 /data/data/com.pubg.imobile/files/ano_tmp");
    system("rm -rf /data/data/com.pubg.imobile/files/obblib");
    system("touch /data/data/com.pubg.imobile/files/obblib");
    system("chmod 000 /data/data/com.pubg.imobile/files/obblib");
    system("rm -rf /data/data/com.pubg.imobile/files/xlog");
    system("touch /data/data/com.pubg.imobile/files/xlog");
    system("chmod 000 /data/data/com.pubg.imobile/files/xlog");
    system("rm -rf /data/data/com.pubg.imobile/app_bugly");
    system("touch /data/data/com.pubg.imobile/app_bugly");
    system("chmod 000 /data/data/com.pubg.imobile/app_bugly");
    system("rm -rf /data/data/com.pubg.imobile/app_crashrecord");
    system("touch /data/data/com.pubg.imobile/app_crashrecord");
    system("chmod 000 /data/data/com.pubg.imobile/app_crashrecord");
    system("rm -rf /data/data/com.pubg.imobile/app_crashSight");
    system("touch /data/data/com.pubg.imobile/app_crashSight");
    system("chmod 000 /data/data/com.pubg.imobile/app_crashSight");
}
    void *main_thread(void *)
         {
         FixGameCrash();
    Cheat::libUE4Base = Tools::GetBaseAddress("libUE4.so");
    while (!Cheat::libUE4Base)
         {
    Cheat::libUE4Base = Tools::GetBaseAddress("libUE4.so");
     sleep(1);
         }
     while (!g_App)
        {
     g_App = *(android_app **)(Cheat::libUE4Base + Cheat::GNativeAndroidApp_Offset);
     sleep(1);
         }

    FName::GNames = GetGNames();
    while (!FName::GNames)
        {
    FName::GNames = GetGNames();
     sleep(1);
        }
    UObject::GUObjectArray = (FUObjectArray *)(Cheat::libUE4Base + Cheat::GUObject_Offset);


   #define CHUT_LIB(lib, offset, ptr, orig) fuck((void *)KittyMemory::getAbsoluteAddress(lib, offset), (void *)ptr, (void **)&orig)
   CHUT_LIB("libUE4.so", 0xBA27480, _eglSwapBuffers, orig_eglSwapBuffers);

    items_data = json::parse(JSON_ITEMS);
    return nullptr;
        }

     __attribute__((constructor)) void _init()
        {
    pthread_create(&t, NULL, main_thread, NULL);
	pthread_create(&t, NULL, anogs_thread, NULL);
        }

