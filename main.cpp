   // agar classes namespace me hain
#include <random>     // Random ke liye
#include <cstdint>    // uintptr_t ke liye

   
#include "Includes/include.h"
#include "Includes/definition.h"
void DrawESP(ImDrawList *draw) {
	draw->AddText({((float) density / 19.0f), 50}, IM_COL32(255, 0, 0, 200),
"NxT VIP");

draw->AddText({((float) density / 10.0f), 650}, IM_COL32(000,000,000, 255),
                          "For Buy Key -> @NEXXA_CHEAT");
	draw->AddText({((float) density / 10.0f), 650}, IM_COL32(255,255,255, 255),
                          "For Buy Key -> @NEXXA_CHEAT");
    draw->AddText({((float) density / 10.0f), 670}, IM_COL32(000,000,000, 255),
                          "Channel -> @NEXXA_CHEATZ");
	draw->AddText({((float) density / 10.0f), 670}, IM_COL32(255,255,255, 255),
                          "Channel -> @NEXXA_CHEATZ");
	std::string credit = OBFUSCATE("[0] Telegram Channel -> NEXXA ALL SRC+BYPASS");
    auto textSize = ImGui::CalcTextSize2(credit.c_str(), 0, ((float)density / 14.0f));
    ImU32 outlineColor = IM_COL32(255, 0, 0, 3);
    ImU32 textColor = IM_COL32(0, 255, 0, 255);
    draw->AddText(NULL, ((float)density / 14.0f), {((float)glWidth / 2) - (textSize.x / 2) - 2, 28}, outlineColor, credit.c_str());
    draw->AddText(NULL, ((float)density / 14.0f), {((float)glWidth / 2) - (textSize.x / 2) + 2, 28}, outlineColor, credit.c_str());
    draw->AddText(NULL, ((float)density / 14.0f), {((float)glWidth / 2) - (textSize.x / 2), 30 - 2}, outlineColor, credit.c_str());
    draw->AddText(NULL, ((float)density / 14.0f), {((float)glWidth / 2) - (textSize.x / 2), 30 + 2}, outlineColor, credit.c_str());
    draw->AddText(NULL, ((float)density / 14.0f), {((float)glWidth / 2) - (textSize.x / 2), 30}, textColor, credit.c_str());	
	
	
	
        auto Actors = GetActors();
		
        int totalEnemies = 0, totalBots = 0;

        ASTExtraPlayerCharacter *localPlayer = 0;
        ASTExtraPlayerController *localController = 0;
		
		
        for (int i = 0; i < Actors.size(); i++) {
            auto Actor = Actors[i];
            if (isObjectInvalid(Actor))
                continue;

            if (Actor->IsA(ASTExtraPlayerController::StaticClass())) {
                localController = (ASTExtraPlayerController *) Actor;
                break;
            }
        }
		
		

        if (localController) {
            for (int i = 0; i < Actors.size(); i++) {
                auto Actor = Actors[i];
                if (isObjectInvalid(Actor))
                    continue;

                if (Actor->IsA(ASTExtraPlayerCharacter::StaticClass())) {
                    if (((ASTExtraPlayerCharacter *) Actor)->PlayerKey ==
                        localController->PlayerKey) {
                        localPlayer = (ASTExtraPlayerCharacter *) Actor;
                        break;
                    }
                }
            }

		// Src ~ NIKHIL_VIP_OWNER
            if (localPlayer) {
                if (localPlayer->PartHitComponent) {
                    auto ConfigCollisionDistSqAngles = localPlayer->PartHitComponent->ConfigCollisionDistSqAngles;
                    for (int j = 0; j < ConfigCollisionDistSqAngles.Num(); j++) {
                        ConfigCollisionDistSqAngles[j].Angle = 90.0f;
                    }
                    localPlayer->PartHitComponent->ConfigCollisionDistSqAngles = ConfigCollisionDistSqAngles;
                }

                if (localPlayer) {
                    if (localPlayer->PartHitComponent) {
                        auto ConfigCollisionDistSqAngles = localPlayer->PartHitComponent->ConfigCollisionDistSqAngles;
                        for (int j = 0; j < ConfigCollisionDistSqAngles.Num(); j++) {
                            ConfigCollisionDistSqAngles[j].Angle = 180.0f;
                        }
                        localPlayer->PartHitComponent->ConfigCollisionDistSqAngles = ConfigCollisionDistSqAngles;
                    }
					if (Cheat::Memory::IPadView)
                    localPlayer->ThirdPersonCameraComponent->SetFieldOfView(Cheat::Memory::WideViewRange);
                    static bool bShooting = false;
                    if (BulletTrack) {
                        auto WeaponManagerComponent = localPlayer->WeaponManagerComponent;
                        if (WeaponManagerComponent) {
                            auto propSlot = WeaponManagerComponent->GetCurrentUsingPropSlot();
                            if ((int) propSlot.GetValue() >= 1 && (int) propSlot.GetValue() <= 3) {
                                auto CurrentWeaponReplicated = (ASTExtraShootWeapon *) WeaponManagerComponent->CurrentWeaponReplicated;
                                if (CurrentWeaponReplicated) {
                                    auto ShootWeaponComponent = CurrentWeaponReplicated->ShootWeaponComponent;
                                    if (ShootWeaponComponent) {
                                        int shoot_event_idx = 169;
                                        auto VTable = (void **) ShootWeaponComponent->VTable;
                                        auto f_mprotect = [](uintptr_t addr, size_t len,
                                                             int32_t prot) -> int32_t {
                                            static_assert(PAGE_SIZE == 4096);
                                            constexpr
                                            size_t page_size = static_cast<size_t>(PAGE_SIZE);
                                            void *start = reinterpret_cast<void *>(addr &
                                                                                   -page_size);
                                            uintptr_t end =
                                                    (addr + len + page_size - 20) & -page_size;
                                            return mprotect(start, end -
                                                                   reinterpret_cast<uintptr_t>(start),
                                                            prot);
                                        };
                                        if (VTable && (VTable[shoot_event_idx] != shoot_event)) {
                                            orig_shoot_event = decltype(orig_shoot_event)(
                                                    VTable[shoot_event_idx]);

                                            f_mprotect((uintptr_t)(&VTable[shoot_event_idx]),
                                                       sizeof(uintptr_t), PROT_READ | PROT_WRITE);
                                            VTable[shoot_event_idx] = (void *) shoot_event;
                                        }
                                    }
                                }
                            }
                        }
                    }
					if (Cheat::Esp::TargetLine) {
      if (Cheat::BulletTrack::Enable) {
         ASTExtraPlayerCharacter *Target = GetTargetByPussy();        
         long PlayerAimLineColor = IM_COL32(255, 255, 255, 255); // White color             
         if (Target) {
         FVector RootPos = Target->GetBonePos("Root", {});
         ImVec2 RootPosSC;
         if (W2S(RootPos, (FVector2D *)&RootPosSC)) {
         draw->AddLine(RootPosSC, {(float) glWidth / 2, (float) glHeight},
         PlayerAimLineColor, 1.0f); // Adjusted line width
         }
        }
    }  

if (Cheat::BulletTrack::Target == Cheat::EAimTarget::Head) {
draw->AddText(nullptr, ((float) density / 22.0f),ImVec2(glWidth / 2 - 107.1f, 540.1),IM_COL32(0,0,0,255),"     Aim->Mode : Head");
draw->AddText(nullptr, ((float) density / 22.0f),ImVec2(glWidth / 2 - 106.9f, 540.9),IM_COL32(0,0,0,255),"     Aim->Mode : Head");
draw->AddText(nullptr, ((float) density / 22.0f),ImVec2(glWidth / 2 - 107.1f, 540.9f),IM_COL32(0,0,0,255),"     Aim->Mode : Head");
draw->AddText(nullptr, ((float) density / 22.0f),ImVec2(glWidth / 2 - 106.9f, 540.1f),IM_COL32(0,0,0,255),"     Aim->Mode : Head");
draw->AddText(nullptr, ((float) density / 22.0f),ImVec2(glWidth / 2 - 107.1f, 540.f),IM_COL32(0,0,0,255),"     Aim->Mode : Head");
draw->AddText(nullptr, ((float) density / 22.0f),ImVec2(glWidth / 2 - 106.9f, 540.f),IM_COL32(0,0,0,255),"     Aim->Mode : Head");
draw->AddText(nullptr, ((float) density / 22.0f),ImVec2(glWidth / 2 - 107.f, 540.9f),IM_COL32(0,0,0,255),"     Aim->Mode : Head");
draw->AddText(nullptr, ((float) density / 22.0f),ImVec2(glWidth / 2 - 107.f, 540.1f),IM_COL32(0,0,0,255),"     Aim->Mode : Head");
draw->AddText(nullptr, ((float) density / 22.0f),ImVec2(glWidth / 2 - 107.f, 540),IM_COL32(255,255,255,255),"     Aim->Mode : Head");         
}else{
draw->AddText(nullptr, ((float) density / 22.0f),ImVec2(glWidth / 2 - 107.1f, 540.1),IM_COL32(0,0,0,255),"Aim->Mode : Body");
draw->AddText(nullptr, ((float) density / 22.0f),ImVec2(glWidth / 2 - 106.9f, 540.9),IM_COL32(0,0,0,255),"Aim->Mode : Body");
draw->AddText(nullptr, ((float) density / 22.0f),ImVec2(glWidth / 2 - 107.1f, 540.9f),IM_COL32(0,0,0,255),"Aim->Mode : Body");
draw->AddText(nullptr, ((float) density / 22.0f),ImVec2(glWidth / 2 - 106.9f, 540.1f),IM_COL32(0,0,0,255),"Aim->Mode : Body");
draw->AddText(nullptr, ((float) density / 22.0f),ImVec2(glWidth / 2 - 107.1f,540.f  ),IM_COL32(0,0,0,255),"Aim->Mode : Body");
draw->AddText(nullptr, ((float) density / 22.0f),ImVec2(glWidth / 2 - 106.9f, 540.f),IM_COL32(0,0,0,255),"Aim->Mode : Body");
draw->AddText(nullptr, ((float) density / 22.0f),ImVec2(glWidth / 2 - 107.f, 540.9f),IM_COL32(0,0,0,255),"Aim->Mode : Body");
draw->AddText(nullptr, ((float) density / 22.0f),ImVec2(glWidth / 2 - 107.f, 540.1f),IM_COL32(0,0,0,255),"Aim->Mode : Body");
draw->AddText(nullptr, ((float) density / 22.0f),ImVec2(glWidth / 2 - 107.f, 540),IM_COL32(255,255,255,255),"Aim->Mode : Body");         
}

		// Src ~ NIKHIL_VIP_OWNER
		
		 if (Cheat::AimBot::Enable) {
			  draw->AddCircle(ImVec2(glWidth / 2, glHeight / 2), Cheat::AimBot::Radius, IM_COL32(0,0,0,255), 0, 0.9f);
               
                    ASTExtraPlayerCharacter *Target = GetTargetForAimBot();
                    if (Target) {
                        bool triggerOk = false;
                        if (Cheat::AimBot::Trigger != Cheat::EAimTrigger::None) {
                            if (Cheat::AimBot::Trigger == Cheat::EAimTrigger::Shooting) {
                                triggerOk = localPlayer->bIsWeaponFiring;
                            } else if (Cheat::AimBot::Trigger == Cheat::EAimTrigger::Scoping) {
                                triggerOk = localPlayer->bIsGunADS;
                            } else if (Cheat::AimBot::Trigger == Cheat::EAimTrigger::Both) {
                                triggerOk = localPlayer->bIsWeaponFiring && localPlayer->bIsGunADS;
                            } else if (Cheat::AimBot::Trigger == Cheat::EAimTrigger::Any) {
                                triggerOk = localPlayer->bIsWeaponFiring || localPlayer->bIsGunADS;
                            }
                        } else triggerOk = true;
                        if (triggerOk) {
                            FVector targetAimPos = Target->GetBonePos("Head", {});
                            if (Cheat::AimBot::Target == Cheat::EAimTarget::Chest) {
                                targetAimPos.Z -= 25.0f;
                            }

                                  auto WeaponManagerComponent = localPlayer->WeaponManagerComponent;
                            if (WeaponManagerComponent) {
                                auto propSlot = WeaponManagerComponent->GetCurrentUsingPropSlot();
                                if ((int) propSlot.GetValue() >= 1 &&
                                    (int) propSlot.GetValue() <= 3) {
                                    auto CurrentWeaponReplicated = (ASTExtraShootWeapon *) WeaponManagerComponent->CurrentWeaponReplicated;
                                    if (CurrentWeaponReplicated) {
                                        auto ShootWeaponComponent = CurrentWeaponReplicated->ShootWeaponComponent;
                                        if (ShootWeaponComponent) {
                                            UShootWeaponEntity *ShootWeaponEntityComponent = ShootWeaponComponent->ShootWeaponEntityComponent;
                                            if (ShootWeaponEntityComponent) {
                                                ASTExtraVehicleBase *CurrentVehicle = Target->CurrentVehicle;
                                                if (CurrentVehicle) {
                                                    FVector LinearVelocity = CurrentVehicle->ReplicatedMovement.LinearVelocity;

                                                    float dist = localPlayer->GetDistanceTo(Target);
                                                    auto timeToTravel = dist /
                                                                        ShootWeaponEntityComponent->BulletFireSpeed;

                                                    targetAimPos = UKismetMathLibrary::Add_VectorVector(
                                                            targetAimPos,
                                                            UKismetMathLibrary::Multiply_VectorFloat(
                                                                    LinearVelocity, timeToTravel));
                                                } else {
                                                    FVector Velocity = Target->GetVelocity();

                                                    float dist = localPlayer->GetDistanceTo(Target);
                                                    auto timeToTravel = dist /
                                                                        ShootWeaponEntityComponent->BulletFireSpeed;

                                                    targetAimPos = UKismetMathLibrary::Add_VectorVector(
                                                            targetAimPos,
                                                            UKismetMathLibrary::Multiply_VectorFloat(
                                                                    Velocity, timeToTravel));
                                                }
                                                localController->SetControlRotation(ToRotator(
                                                        localController->PlayerCameraManager->CameraCache.POV.Location,
                                                        targetAimPos), "200");
               
                                             if (Cheat::AimBot::RecoilComparison) {
                                                                                                   if (g_LocalPlayer->bIsGunADS) {
                                                        if (g_LocalPlayer->bIsWeaponFiring) {
                                                            float dist = g_LocalPlayer->GetDistanceTo(Target) / 100.f;                                                                                 
                                                            targetAimPos.Z -= dist * Cheat::AimBot::Recc;
                                                        }  
                                                    }
                                                }
                                                localController->SetControlRotation(ToRotator(localController->PlayerCameraManager->CameraCache.POV.Location, targetAimPos), "");
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                  }			 
// --------- yahan tak, extra closing braces hata di --------
                
             
                FVector ViewPosY{0, 0, 0};
                        if (localPlayer) {
                        ViewPosY = localPlayer->GetBonePos("Head", {});
                        ViewPosY.Z += 360.f;
                         
}
}
}




                if (localController != 0)
                {
                
                if (Cheat::Memory::SmallCrossHair || Cheat::Memory::FastShoot ||
                        Cheat::Memory::NoRecoil) {
                        auto WeaponManagerComponent = localPlayer->WeaponManagerComponent;
                        if (WeaponManagerComponent) {
                            auto propSlot = WeaponManagerComponent->GetCurrentUsingPropSlot();
                            if ((int) propSlot.GetValue() >= 1 && (int) propSlot.GetValue() <= 3) {
                                auto CurrentWeaponReplicated = (ASTExtraShootWeapon *) WeaponManagerComponent->CurrentWeaponReplicated;
                                if (CurrentWeaponReplicated) {
                                    auto ShootWeaponComponent = CurrentWeaponReplicated->ShootWeaponComponent;
                                    if (ShootWeaponComponent) {
                                        UShootWeaponEntity *ShootWeaponEntityComponent = ShootWeaponComponent->ShootWeaponEntityComponent;
                                        if (ShootWeaponEntityComponent) {

                                            if (Cheat::Memory::SmallCrossHair) {
                                                ShootWeaponEntityComponent->GameDeviationFactor = 0.0f;                                                
                                            }
                               
                                            if (Cheat::Memory::NoRecoil) {
                                              ShootWeaponEntityComponent->RecoilKickADS = 0.0f;             // No Shake 1
                                              ShootWeaponEntityComponent->AnimationKick = 0.0f;             // No Shake 
                                              ShootWeaponEntityComponent->ShotGunCenterPerc = 0.0f;         // No Spread 1
                                              ShootWeaponEntityComponent->ShotGunVerticalSpread = 0.0f;     // No Spread 2
                                              ShootWeaponEntityComponent->ShotGunHorizontalSpread = 0.0f;   // No Spread 3
                                              ShootWeaponEntityComponent->AccessoriesVRecoilFactor = 0.0f;  // More Accuracy 1
                                              ShootWeaponEntityComponent->AccessoriesHRecoilFactor = 0.0f;  // More Accuracy 2
                                              ShootWeaponEntityComponent->AccessoriesRecoveryFactor = 0.0f; // More Accuracy 3


                                             }
                                           
                                           }
                                        }
                                    }
                                }
                            }
                        }                                                      
		// Src ~ NIKHIL_VIP_OWNER                      
             for (auto &i : Actors) {
                auto Actor = i;
                if (isObjectInvalid(Actor))
                    continue;

                if (Actor->IsA(ASTExtraPlayerCharacter::StaticClass())) {
                    auto Player = (ASTExtraPlayerCharacter *) Actor;
					
                    float Distance = localPlayer->GetDistanceTo(Player) / 500.0f;
                    if (Distance > 500.0f)
                        continue;
				
                    if (Player->PlayerKey == localController->PlayerKey)
                        continue;

                    if (Player->TeamID == localController->TeamID)
                        continue;

                    if (Player->bDead)
                        continue;

                    if (!Player->Mesh)
                        continue;

                    if (Player->bEnsure)
                        totalBots++;
                    else totalEnemies++;

                    if (Cheat::Esp::NoBot)
                        if (Player->bEnsure)
                            continue;

                    float magic_number = (Distance);
                    float mx = (glWidth / 4) / magic_number;

                    float healthLength = glWidth / 19;
                    if (healthLength < mx)
                        healthLength = mx;

                    auto HeadPos = Player->GetBonePos("Head", {});
                    ImVec2 HeadPosSC;

                    auto RootPos = Player->GetBonePos("Root", {});
                    ImVec2 RootPosSC;
                    auto upper_r = Player->GetBonePos("upperarm_r", {});
                    ImVec2 upper_rPoSC;
                    auto lowerarm_r = Player->GetBonePos("lowerarm_r", {});
                    ImVec2 lowerarm_rPoSC;
                    auto hand_r = Player->GetBonePos("hand_r", {});
                    ImVec2 hand_rPoSC;
                    auto upper_l = Player->GetBonePos("upperarm_l", {});
                    ImVec2 upper_lPoSC;
                    auto lowerarm_l = Player->GetBonePos("lowerarm_l", {});
                    ImVec2 lowerarm_lSC;
                    auto hand_l = Player->GetBonePos("hand_l", {});
                    ImVec2 hand_lPoSC;
                    auto thigh_l = Player->GetBonePos("thigh_l", {});
                    ImVec2 thigh_lPoSC;
                    auto calf_l = Player->GetBonePos("calf_l", {});
                    ImVec2 calf_lPoSC;
                    auto foot_l = Player->GetBonePos("foot_l", {});
                    ImVec2 foot_lPoSC;
                    auto thigh_r = Player->GetBonePos("thigh_r", {});
                    ImVec2 thigh_rPoSC;
                    auto calf_r = Player->GetBonePos("calf_r", {});
                    ImVec2 calf_rPoSC;
                    auto foot_r = Player->GetBonePos("foot_r", {});
                    ImVec2 foot_rPoSC;
                    auto neck_01 = Player->GetBonePos("neck_01", {});
                    ImVec2 neck_01PoSC;
                    auto Pelvis = Player->GetBonePos("pelvis", {});
                    ImVec2 PelvisPoSC;

                    bool IsVisible = localController->LineOfSightTo(Player, {0, 0, 0}, true);

					long PlayerBoxClrCf = IM_COL32(0, 255, 0, 255);
                        long PlayerBoxClrCf2 = IM_COL32(0, 255, 0, 25);
                        
                        if (!localController->LineOfSightTo(Player, {0, 0, 0}, true)) {
                            PlayerBoxClrCf = IM_COL32(255, 255, 255, 255);
                            PlayerBoxClrCf2 = IM_COL32(255, 255, 255, 25);
                        }
					
                    int SCOLOR, SCOLOR2;

                    if (IsVisible)
                    {
                        SCOLOR = IM_COL32(0, 255, 0, 255);
                        SCOLOR2 = IM_COL32(0, 255, 0, 255);
                    }else{
                        SCOLOR = IM_COL32(255, 255, 255, 255);
                        SCOLOR2 = IM_COL32(255, 255, 255, 255);
                    }

                    if (W2S(HeadPos, (FVector2D *) &HeadPosSC) &&
                        W2S(upper_r, (FVector2D *) &upper_rPoSC) &&
                        W2S(upper_l, (FVector2D *) &upper_lPoSC) &&
                        W2S(lowerarm_r, (FVector2D *) &lowerarm_rPoSC ) &&
                        W2S(hand_r, (FVector2D *) &hand_rPoSC ) &&
                        W2S(lowerarm_l, (FVector2D *) &lowerarm_lSC ) &&
                        W2S(hand_l, (FVector2D *) &hand_lPoSC ) &&
                        W2S(thigh_l, (FVector2D *) &thigh_lPoSC ) &&
                        W2S(calf_l, (FVector2D *) &calf_lPoSC ) &&
                        W2S(foot_l, (FVector2D *) &foot_lPoSC ) &&
                        W2S(thigh_r, (FVector2D *) &thigh_rPoSC ) &&
                        W2S(calf_r, (FVector2D *) &calf_rPoSC ) &&
                        W2S(foot_r, (FVector2D *) &foot_rPoSC ) &&
                        W2S(neck_01, (FVector2D *) &neck_01PoSC ) &&
                        W2S(Pelvis, (FVector2D *) &PelvisPoSC ) &&
                        W2S(RootPos, (FVector2D *) &RootPosSC)){

// =============================================================
//  ESP Rope/Line – 3‑rang animation + visible/cover logic
//  Replace karo sirf itni block se; baaki tumhaara code same
// =============================================================
if (Cheat::Esp::Line)
{
    ImVec2 lineStart = { (float)glWidth / 2.0f, 0.0f };
    ImVec2 lineEnd   = { HeadPosSC.x, HeadPosSC.y - 55.0f };

    const float offsetAmount = 3.0f;
    const float dashLength   = 10.0f;
    const float gapLength    = 5.0f;

    static float dashOffset1 = 0.0f;
    static float dashOffset2 = 7.5f;
    float delta = ImGui::GetIO().DeltaTime;
    dashOffset1 = fmodf(dashOffset1 + delta * 120.0f, dashLength + gapLength);
    dashOffset2 = fmodf(dashOffset2 + delta * 120.0f, dashLength + gapLength);

    bool isBot = false;
    {
        std::string nameStr = Player->PlayerName.ToString();
        std::transform(nameStr.begin(), nameStr.end(), nameStr.begin(), ::tolower);
        if (nameStr.find("bot") != std::string::npos ||
            nameStr.find("ai_") != std::string::npos ||
            nameStr.find("aibot") != std::string::npos)
            isBot = true;
    }

    bool isCovered = false;

    const ImU32 pureGreen = IM_COL32(60, 255, 60, 255);
    static ImU32 cycleCols[3] = {
        IM_COL32(255, 60, 60, 255),
        IM_COL32(60, 60, 255, 255),
        IM_COL32(255, 215, 0, 255)
    };

    float time = ImGui::GetTime();
    const float ropeWave     = 1.5f;
    const float vertWaveAmp  = 4.0f;
    const float vertWaveFreq = 6.0f;

    for (int strand = 0; strand < 2; ++strand)
    {
        float currentOffset = (strand == 0) ? dashOffset1 : dashOffset2;
        float offsetY       = (strand == 0) ? -offsetAmount : offsetAmount;

        ImVec2 start = { lineStart.x, lineStart.y + offsetY };
        ImVec2 end   = { lineEnd.x,   lineEnd.y   + offsetY };

        float dx = end.x - start.x;
        float dy = end.y - start.y;
        float len = sqrtf(dx * dx + dy * dy);
        if (len < 1.0f || !std::isfinite(len)) continue;

        ImVec2 normal(-dy / len, dx / len);

        float curPos = currentOffset;
        while (curPos < len)
        {
            float segEnd = fminf(curPos + dashLength, len);

            float t0 = curPos / len;
            float t1 = segEnd / len;

            ImVec2 p0(start.x + t0 * dx, start.y + t0 * dy);
            ImVec2 p1(start.x + t1 * dx, start.y + t1 * dy);

            float phase0 = fmodf(time * 5.0f + t0 * 20.0f, 6.2831f); // Wrap to [0, 2pi]
            float phase1 = fmodf(time * 5.0f + t1 * 20.0f, 6.2831f);
            float vert0  = sinf(time * vertWaveFreq + t0 * 15.0f) * vertWaveAmp;
            float vert1  = sinf(time * vertWaveFreq + t1 * 15.0f) * vertWaveAmp;

            ImVec2 p0a = { p0.x + normal.x * ropeWave * sinf(phase0), p0.y + normal.y * ropeWave * sinf(phase0) + vert0 };
            ImVec2 p1a = { p1.x + normal.x * ropeWave * sinf(phase1), p1.y + normal.y * ropeWave * sinf(phase1) + vert1 };

            ImVec2 p0b = { p0.x - normal.x * ropeWave * sinf(phase0), p0.y - normal.y * ropeWave * sinf(phase0) + vert0 };
            ImVec2 p1b = { p1.x - normal.x * ropeWave * sinf(phase1), p1.y - normal.y * ropeWave * sinf(phase1) + vert1 };

            ImU32 ropeCol;
            if (isBot)
            {
                ropeCol = IM_COL32(190, 140, 70, 255);
            }
            else if (!isCovered)
            {
                ropeCol = pureGreen;
            }
            else
            {
                int segIdx = int(curPos / (dashLength + gapLength)) % 3;
                ropeCol = cycleCols[segIdx];
            }

            draw->AddLine(p0a, p1a, ropeCol, 1.8f);
            draw->AddLine(p0b, p1b, ropeCol, 1.8f);

            curPos += dashLength + gapLength;
        }
    }
}
                         if (Cheat::Esp::Box) {
    float boxHeight = abs(HeadPosSC.y - RootPosSC.y);
    float boxWidth = boxHeight * 0.65f;

    ImVec2 vStart = {HeadPosSC.x - (boxWidth / 2), HeadPosSC.y};
    ImVec2 vEnd = {vStart.x + boxWidth, vStart.y + boxHeight};

    ImVec2 topLeft = vStart;
    ImVec2 topRight = {vEnd.x, vStart.y};
    ImVec2 bottomRight = vEnd;
    ImVec2 bottomLeft = {vStart.x, vEnd.y};

    bool isEnemyVisible = /* yaha pe tu apna visibility check lagaye jaise */ IsVisible;

    if (isEnemyVisible) {
        // Enemy saamne ho toh green box
        ImU32 greenColor = IM_COL32(0, 255, 0, 255);
        draw->AddRect(topLeft, bottomRight, greenColor, 1.5f, 240, 1.7f);
    } else {
        // 3 color ghoomte hue box
        ImU32 colors[3] = {
            IM_COL32(255, 0, 0, 255),   // Red
            IM_COL32(0, 255, 0, 255),   // Green
            IM_COL32(0, 0, 255, 255)    // Blue
        };

        float time = ImGui::GetTime();
        int shift = static_cast<int>(time * 2.0f) % 3;

        draw->AddLine(topLeft, topRight, colors[(0 + shift) % 3], 1.7f);       // Top
        draw->AddLine(topRight, bottomRight, colors[(1 + shift) % 3], 1.7f);   // Right
        draw->AddLine(bottomRight, bottomLeft, colors[(2 + shift) % 3], 1.7f); // Bottom
        draw->AddLine(bottomLeft, topLeft, colors[(3 + shift) % 3], 1.7f);     // Left
    }
}
									
                        if (Cheat::Esp::Skeleton) {
    // Visibility check (replace 'IsVisible' with your actual logic)
    bool isEnemyVisible = /* tu yaha pe apna visibility check use kare */ IsVisible;

    ImU32 skeletonColor = isEnemyVisible 
                          ? IM_COL32(0, 255, 0, 255)   // Green when visible
                          : IM_COL32(255, 0, 0, 255);  // Red when behind cover

    float time = ImGui::GetTime();
    float pulse = sin(time * 2.0f) * 0.5f + 1.5f;  // Smooth thickness animation

    // Draw static colored skeleton
    draw->AddLine({upper_rPoSC.x, upper_rPoSC.y}, neck_01PoSC, skeletonColor, pulse);
    draw->AddLine({upper_lPoSC.x, upper_lPoSC.y}, neck_01PoSC, skeletonColor, pulse);

    draw->AddLine({upper_rPoSC.x, upper_rPoSC.y}, lowerarm_rPoSC, skeletonColor, pulse);
    draw->AddLine({lowerarm_rPoSC.x, lowerarm_rPoSC.y}, hand_rPoSC, skeletonColor, pulse);

    draw->AddLine({upper_lPoSC.x, upper_lPoSC.y}, lowerarm_lSC, skeletonColor, pulse);
    draw->AddLine({lowerarm_lSC.x, lowerarm_lSC.y}, hand_lPoSC, skeletonColor, pulse);

    draw->AddLine({thigh_rPoSC.x, thigh_rPoSC.y}, thigh_lPoSC, skeletonColor, pulse);

    draw->AddLine({thigh_lPoSC.x, thigh_lPoSC.y}, calf_lPoSC, skeletonColor, pulse);
    draw->AddLine({calf_lPoSC.x, calf_lPoSC.y}, foot_lPoSC, skeletonColor, pulse);

    draw->AddLine({thigh_rPoSC.x, thigh_rPoSC.y}, calf_rPoSC, skeletonColor, pulse);
    draw->AddLine({calf_rPoSC.x, calf_rPoSC.y}, foot_rPoSC, skeletonColor, pulse);

    draw->AddLine({neck_01PoSC.x, neck_01PoSC.y}, PelvisPoSC, skeletonColor, pulse);
    draw->AddLine({neck_01PoSC.x, neck_01PoSC.y}, HeadPosSC, skeletonColor, pulse);
}

/*
							*/
							
if (Cheat::Esp::Health) {
    int CurHP = std::max(0, std::min((int)Player->Health, (int)Player->HealthMax));
    int MaxHP = std::max(1, (int)Player->HealthMax);

    float HPPercent = (float)CurHP / (float)MaxHP;
    float time = ImGui::GetTime();

    float boxWidth  = density / 5.0f;
    boxWidth -= std::min(((boxWidth / 2) / 500.0f) * Distance, boxWidth / 2);
    float boxHeight = boxWidth * 0.15f;

    ImVec2 vStart = {HeadPosSC.x - (boxWidth / 2), HeadPosSC.y - (boxHeight * 2.0f)};
    ImVec2 vEnd   = {vStart.x + (CurHP * boxWidth / MaxHP), vStart.y + boxHeight};

    // --------- FULL‑GREEN HEALTH BAR (flag & chakra removed) ----------
    ImU32 greenCol = IM_COL32(  0, 255,   0, 255);   // pure green
    ImU32 backCol  = IM_COL32( 25,  25,  25, 180);   // dark background

    // background bar (empty HP)
    draw->AddRectFilled(vStart,
                        ImVec2(vStart.x + boxWidth, vStart.y + boxHeight),
                        backCol);

    // filled health
    draw->AddRectFilled(vStart,
                        vEnd,
                        greenCol);

    // border
    draw->AddRect(vStart,
                  ImVec2(vStart.x + boxWidth, vStart.y + boxHeight),
                  IM_COL32(255, 255, 255, 200),
                  3.0f);

    // HP percent text above
    char hpText[8];
    snprintf(hpText, sizeof(hpText), "%d%%", (int)(HPPercent * 100));
    ImVec2 hpSize = ImGui::CalcTextSize(hpText);
    ImVec2 hpPos  = {vStart.x + (boxWidth / 2) - (hpSize.x / 2), vStart.y - hpSize.y - 2};
    draw->AddText(hpPos, IM_COL32(255, 255, 255, 230), hpText);
}


                                
						if (Cheat::Esp::TeamID || Cheat::Esp::Name ||
                                    Cheat::Esp::Distance) {
								float boxWidth = density / 2.25f;
                                boxWidth -= std::min(((boxWidth / 2) / 00.0f) * Distance,
                                                     boxWidth / 2);
                                float boxHeight = boxWidth * 0.19f;
                                    std::string s;

                                    if (Cheat::Esp::TeamID) {
                                        s += "(" + std::to_string(Player->TeamID) + ") ";
                                    }
if (Cheat::Esp::Name && draw)
{
    // -------- naam aur rang tayyar karo --------
    std::string rawName = Player->PlayerName.ToString();      // FString  → std::string

    bool isBot = false;

    // Universal bot-detection
    if (Player->bIsAI)                                     isBot = true;
    else if (rawName.rfind("Player", 0) == 0)              isBot = true;
    else if (rawName.find("AI") != std::string::npos)      isBot = true;
    else if (Player->TeamID >= 100)                        isBot = true;

    std::string displayName = isBot ? "Bot" : rawName;      // <-- yahi change
    ImU32 nameColor         = isBot ? IM_COL32(255, 230, 90, 255)    // light yellow
                                    : IM_COL32(  0, 255,  0, 255);   // green

    // -------- naam draw karo --------
    ImVec2 nameSize = ImGui::CalcTextSize(displayName.c_str());
    ImVec2 namePos  = { RootPosSC.x - nameSize.x * 0.5f,
                        RootPosSC.y + 15.0f };

    draw->AddText(nullptr, 15.0f, namePos, nameColor, displayName.c_str());

    // -------- distance (agar ON hai) --------
    if (Cheat::Esp::Distance)
    {
        std::string distStr = std::to_string(static_cast<int>(Distance)) + "M";
        ImVec2 distSize = ImGui::CalcTextSize(distStr.c_str());
        ImVec2 distPos  = { RootPosSC.x - distSize.x * 0.5f,
                            namePos.y + nameSize.y + 2.0f };

        draw->AddText(nullptr, 15.0f, distPos, nameColor, distStr.c_str());
    }
}


            if (Cheat::Memory::GameInfo) {     
                                if (Actor->IsA(ASTExtraGameStateBase::StaticClass())) {
                                auto InGame = (ASTExtraGameStateBase *) Actor;
                                std::string s;
                                s += "\nMatch ID : ";
                                s += std::to_string((int) InGame->GameID);
                                s += "\nMode: ";
                                s += std::to_string((int) InGame->PlayerNumPerTeam);
                                s += "\nPlayers: ";
                                s += std::to_string((int) InGame->PlayerNum);
                                s += "\nMatch Time : ";
                                s += std::to_string((int) InGame->ElapsedTime);
                                s += "s | ";
                                s += std::to_string((int) InGame->ElapsedTime / 60);
                                s += "m";


								draw->AddText({((float) density / 15.0f), 500}, IM_COL32(255, 255, 255, 255),s.c_str());

                            	}
                      			}                      
									
									
		



if (Cheat::Esp::Alert) {
    bool dummy = false;
    FVector PlayerPos = Player->CurrentVehicle ? Player->CurrentVehicle->RootComponent->RelativeLocation
                                               : Player->RootComponent->RelativeLocation;

    FVector LocalPos = localPlayer->CurrentVehicle ? localPlayer->CurrentVehicle->RootComponent->RelativeLocation
                                                   : localPlayer->RootComponent->RelativeLocation;

    FVector RadarPos = WorldToRadar(
        localController->PlayerCameraManager->CameraCache.POV.Rotation.Yaw,
        PlayerPos, LocalPos, NULL, NULL,
        Vector3(glWidth, glHeight, 0), dummy
    );

    Vector3 forward = Vector3((glWidth / 2.f) - RadarPos.X, (glHeight / 2.f) - RadarPos.Y, 0.f);
    FVector angleVec;
    VectorAnglesRadar(forward, angleVec);
    float angleYaw = angleVec.Y + 180.f;
    float angleRad = DEG2RAD(angleYaw);

    float newX = (glWidth / 2.f) + ((30.0f / 2) * 8.0f) * cosf(angleRad);
    float newY = (glHeight / 2.f) + ((30.0f / 2) * 8.0f) * sinf(angleRad);

    // Triangle points for alert direction
    std::array<Vector3, 3> arrow = {
        Vector3(newX - ((90 / 4.f + 3.5f) / 2.f), newY - ((30 / 4.f + 3.5f) / 2.f), 0.f),
        Vector3(newX + ((90 / 4.f + 3.5f) / 4.f), newY, 0.f),
        Vector3(newX - ((30 / 4.f + 3.5f) / 2.f), newY + ((20 / 4.f + 3.5f) / 2.f), 0.f)
    };

    RotateTriangle(arrow, angleYaw); // Rotate based on enemy direction

    // Use pointer as unique ID for consistent color
    std::uintptr_t uniqueID = reinterpret_cast<std::uintptr_t>(Player);
    std::mt19937 rng(static_cast<unsigned int>(uniqueID));
    std::uniform_int_distribution<int> dist(0, 255);
    int r = dist(rng);
    int g = dist(rng);
    int b = dist(rng);
    ImU32 imColor = IM_COL32(r, g, b, 255);

    // Draw alert circle
    draw->AddCircle(ImVec2(newX, newY), 7.0f, imColor, 64, 7.0f);
}
		
		
		
		
		
		
		
							if(Cheat::BulletTrack::Enable){
					        draw->AddCircle(ImVec2(glWidth / 2, glHeight / 2), Cheat::BulletTrack::Radius, IM_COL32(0, 4, 255 ,255), 0, 0.9f);
						    }
                           if (Cheat::Esp::Vehicle::Name || Cheat::Esp::Vehicle::Fuel || Cheat::Esp::Vehicle::Health) {
    if (i->IsA(ASTExtraVehicleBase::StaticClass())) {
        auto Vehicle = (ASTExtraVehicleBase*) i;
        if (!Vehicle->Mesh || !Vehicle->VehicleCommon) return;

        int CurHP = std::clamp((int)Vehicle->VehicleCommon->HP, 0, (int)Vehicle->VehicleCommon->HPMax);
        int MaxHP = (int)Vehicle->VehicleCommon->HPMax;
        float Distance = Vehicle->GetDistanceTo(localPlayer) / 100.f;

        long hpColor = IM_COL32(
            std::min(((510 * (MaxHP - CurHP)) / MaxHP), 255),
            std::min(((510 * CurHP) / MaxHP), 255),
            0, 155
        );

        FVector2D screenPos;
        if (W2S(Vehicle->K2_GetActorLocation(), &screenPos)) {
            float widthScale = std::min(0.10f * Distance, 50.f);
            float barWidth = 70.f - widthScale;
            float barHeight = barWidth * 0.15f;

            float fontSize = (float)density / 30.0f;
            float textX = screenPos.X - (barWidth / 2);

            // Vehicle Name + Distance
  if (Cheat::Esp::Vehicle::Name) {
    const char* vNameC = GetVehicleName(Vehicle);           // raw C‑string
    std::string label  = std::string(vNameC) + " " + std::to_string((int)Distance);

    draw->AddText(NULL, fontSize,
                  ImVec2(textX, screenPos.Y),
                  IM_COL32(255, 255, 255, 255),
                  label.c_str());
}

            // Fuel Percentage
            if (Cheat::Esp::Vehicle::Fuel && Vehicle->VehicleCommon->FuelMax > 0) {
                int fuelPercent = (int)(100 * Vehicle->VehicleCommon->Fuel / Vehicle->VehicleCommon->FuelMax);
                std::string fuelText = "FUEL: " + std::to_string(fuelPercent);
                draw->AddText(NULL, fontSize, ImVec2(textX, screenPos.Y + 15.f), IM_COL32(255, 255, 0, 255), fuelText.c_str());
            }

            // Health Bar
            if (Cheat::Esp::Vehicle::Health && MaxHP > 0) {
                ImVec2 barStart = {textX, screenPos.Y - (barHeight * 1.5f)};
                ImVec2 barFilled = {barStart.x + (CurHP * barWidth / MaxHP), barStart.y + barHeight};
                ImVec2 barBorder = {barStart.x + barWidth, barStart.y + barHeight};

                draw->AddRectFilled(barStart, barFilled, hpColor, 3.2f);
                draw->AddRect(barStart, barBorder, IM_COL32(0, 0, 0, 255), 3.2f);
            }
        }
    }
}
			
			

			//LAMBORGHINI AVENTADOR (GREEN)
if (Cheat::BulletTrack::LAMBORGHINI) {
kFox::SetSearchRange(RegionType::ANONYMOUS);    
kFox::MemorySearch("1961001", Type::TYPE_DWORD);    
kFox::MemoryWrite("1961020", 0, Type::TYPE_DWORD);
kFox::ClearResult();
}
			
			
			
			
			
			
if (AIMBUTTON){
ImGui::SetNextWindowPos(ImVec2(900, 100), ImGuiCond_FirstUseEver);
ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);
static int clicked = 0;
ImGui::PushStyleColor(ImGuiCol_Button, {0,0,0,0});
ImGui::PushStyleColor(ImGuiCol_ButtonHovered, {0,0,0,0});
ImGui::PushStyleColor(ImGuiCol_ButtonActive, {0,0,0,0}); 
ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);
if (ImGui::Begin("##BUTTONFORAIM", &AIMBUTTON, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoSavedSettings)){
const ImVec2 pos = ImGui::GetWindowPos();
ImDrawList* draw = ImGui::GetWindowDrawList();
if (Cheat::AimBot::Enable) {
draw->AddRectFilled(ImVec2(pos.x + 100, pos.y + 100),ImVec2(pos.x + 200, pos.y + 200), ImColor(0,0,0,200), 100.0f);
draw->AddLine(ImVec2(pos.x + 150, pos.y + 120),ImVec2(pos.x + 150, pos.y + 140), ImColor(255, 3, 3),7.0f);
draw->AddLine(ImVec2(pos.x + 150, pos.y + 160),ImVec2(pos.x + 150, pos.y + 180), ImColor(255, 3, 3),7.0f);
draw->AddLine(ImVec2(pos.x + 120, pos.y + 150),ImVec2(pos.x + 140, pos.y + 150), ImColor(255, 3, 3),7.0f);
draw->AddLine(ImVec2(pos.x + 160, pos.y + 150),ImVec2(pos.x + 180, pos.y + 150), ImColor(255, 3, 3),7.0f);
ImGui::SetCursorPos(ImVec2(100,100));
if (ImGui::Button("##AIMON", ImVec2(100, 100))) {
Cheat::AimBot::Enable = !Cheat::AimBot::Enable;
}
} else {
draw->AddRectFilled(ImVec2(pos.x + 100, pos.y + 100), ImVec2(pos.x + 200, pos.y + 200), ImColor(0,0,0,200), 100.0f);
draw->AddLine(ImVec2(pos.x + 150, pos.y + 110),ImVec2(pos.x + 150, pos.y + 140), ImColor(0,255,0,255),7.0f);
draw->AddLine(ImVec2(pos.x + 150, pos.y + 160),ImVec2(pos.x + 150, pos.y + 190), ImColor(0,255,0,255),7.0f);
draw->AddLine(ImVec2(pos.x + 110, pos.y + 150),ImVec2(pos.x + 140, pos.y + 150), ImColor(0,255,0,255),7.0f);
draw->AddLine(ImVec2(pos.x + 160, pos.y + 150),ImVec2(pos.x + 190, pos.y + 150), ImColor(0,255,0,255),7.0f);
ImGui::SetCursorPos(ImVec2(100,100));
if (ImGui::Button("##AIMOFF", ImVec2(100, 100))) {
Cheat::AimBot::Enable = !Cheat::AimBot::Enable;
}}ImGui::PopStyleColor(3);
}}

			
			
			
			
			
			if (BTBUTTON){
				

ImGui::SetNextWindowPos(ImVec2(900, 100), ImGuiCond_FirstUseEver);
ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);
static int clicked = 0;
ImGui::PushStyleColor(ImGuiCol_Button, {0,0,0,0});
ImGui::PushStyleColor(ImGuiCol_ButtonHovered, {0,0,0,0});
ImGui::PushStyleColor(ImGuiCol_ButtonActive, {0,0,0,0});
ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);
if (ImGui::Begin("##BUTTONFORBT", &BTBUTTON, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoSavedSettings)){
const ImVec2 pos = ImGui::GetWindowPos();
ImDrawList* draw = ImGui::GetWindowDrawList();
if (Cheat::BulletTrack::Enable) {
draw->AddRectFilled(ImVec2(pos.x + 100, pos.y + 100), ImVec2(pos.x + 200, pos.y + 200), ImColor(0,0,0,200), 100.0f);
draw->AddLine(ImVec2(pos.x + 150, pos.y + 120),ImVec2(pos.x + 150, pos.y + 140), ImColor(0, 4, 255),7.0f);
draw->AddLine(ImVec2(pos.x + 150, pos.y + 160),ImVec2(pos.x + 150, pos.y + 180), ImColor(0, 4, 255),7.0f);
draw->AddLine(ImVec2(pos.x + 120, pos.y + 150),ImVec2(pos.x + 140, pos.y + 150), ImColor(0, 4, 255),7.0f);
draw->AddLine(ImVec2(pos.x + 160, pos.y + 150),ImVec2(pos.x + 180, pos.y + 150), ImColor(0, 4, 255),7.0f);
ImGui::SetCursorPos(ImVec2(100,100));
if (ImGui::Button("##BTON", ImVec2(100, 100))) {
Cheat::BulletTrack::Enable = !Cheat::BulletTrack::Enable;
}
} else {
draw->AddRectFilled(ImVec2(pos.x + 100, pos.y + 100), ImVec2(pos.x + 200, pos.y + 200), ImColor(0,0,0,200), 100.0f);
draw->AddLine(ImVec2(pos.x + 150, pos.y + 110),ImVec2(pos.x + 150, pos.y + 140), ImColor(0,255,0,255),7.0f);
draw->AddLine(ImVec2(pos.x + 150, pos.y + 160),ImVec2(pos.x + 150, pos.y + 190), ImColor(0,255,0,255),7.0f);
draw->AddLine(ImVec2(pos.x + 110, pos.y + 150),ImVec2(pos.x + 140, pos.y + 150), ImColor(0,255,0,255),7.0f);
draw->AddLine(ImVec2(pos.x + 160, pos.y + 150),ImVec2(pos.x + 190, pos.y + 150), ImColor(0,255,0,255),7.0f);
ImGui::SetCursorPos(ImVec2(100,100));
if (ImGui::Button("##BTOFF", ImVec2(100, 100))) {
Cheat::BulletTrack::Enable = !Cheat::BulletTrack::Enable;

}}ImGui::PopStyleColor(3);
}}          


if (Cheat::BulletTrack::EnimiesAlert) {
draw->AddText(NULL, ((float) density / 10.0f), {((float)glWidth / 2) - (glWidth / 8), 100}, ImColor(isRed, isBlue, isGreen), "Warning! Enimes Alert");
draw->AddText(NULL, ((float) density / 10.0f), {((float)glWidth / 2) - (glWidth / 8), 100}, ImColor(isRed, isBlue, isGreen), "Warning! Enimes Alert");
draw->AddText(NULL, ((float) density / 10.0f), {((float)glWidth / 2) - (glWidth / 8), 100}, ImColor(isRed, isBlue, isGreen), "Warning! Enimes Alert");
draw->AddText(NULL, ((float) density / 10.0f), {((float)glWidth / 2) - (glWidth / 8), 100}, ImColor(isRed, isBlue, isGreen), "Warning! Enimes Alert");
            }               
		    }
			}
		    
			
			
			
			
			
			
				   g_LocalController = localController;
           g_LocalPlayer = localPlayer;
    
	
	 
        std::string s;
        if (totalEnemies + totalBots > 0) {
            std::string s;
            if (totalEnemies + totalBots < 10)
                s += "     ";
            else s += "    ";
            s += std::to_string((int) totalEnemies + totalBots);
            draw->AddRectFilled(ImVec2(glWidth / 2 - 68, 61.5), ImVec2(glWidth / 2 + 68, 85.5), IM_COL32(255, 0, 0, 15));
            draw->AddRectFilled(ImVec2(glWidth / 2 - 60, 61.5), ImVec2(glWidth / 2 + 60, 85.5), IM_COL32(255, 0, 0, 15));
            draw->AddRectFilled(ImVec2(glWidth / 2 - 56, 61.5), ImVec2(glWidth / 2 + 56, 85.5), IM_COL32(255, 0, 0, 15));
            draw->AddRectFilled(ImVec2(glWidth / 2 - 52, 61.5), ImVec2(glWidth / 2 + 52, 85.5), IM_COL32(255, 0, 0, 15));
            draw->AddRectFilled(ImVec2(glWidth / 2 - 48, 61.5), ImVec2(glWidth / 2 + 48, 85.5), IM_COL32(255, 0, 0, 15));
            draw->AddRectFilled(ImVec2(glWidth / 2 - 44, 61.5), ImVec2(glWidth / 2 + 44, 85.5), IM_COL32(255, 0, 0, 15));
            draw->AddRectFilled(ImVec2(glWidth / 2 - 40, 61.5), ImVec2(glWidth / 2 + 40, 85.5), IM_COL32(255, 0, 0, 15));
            draw->AddRectFilled(ImVec2(glWidth / 2 - 36, 61.5), ImVec2(glWidth / 2 + 36, 85.5), IM_COL32(255, 0, 0, 15));
            draw->AddText(nullptr, ((float) density / 21.0f), ImVec2(glWidth / 2 - 32.f, 61), IM_COL32(255, 255, 255, 255), s.c_str());
        } else{
            std::string s;
            s += "CLEAR";
            draw->AddRectFilled(ImVec2(glWidth / 2 - 68, 61.5), ImVec2(glWidth / 2 + 68, 85.5), IM_COL32(87, 143, 255, 15));
            draw->AddRectFilled(ImVec2(glWidth / 2 - 60, 61.5), ImVec2(glWidth / 2 + 60, 85.5), IM_COL32(87, 143, 255, 15));
            draw->AddRectFilled(ImVec2(glWidth / 2 - 56, 61.5), ImVec2(glWidth / 2 + 56, 85.5), IM_COL32(87, 143, 255, 15));
            draw->AddRectFilled(ImVec2(glWidth / 2 - 52, 61.5), ImVec2(glWidth / 2 + 52, 85.5), IM_COL32(87, 143, 255, 15));
            draw->AddRectFilled(ImVec2(glWidth / 2 - 48, 61.5), ImVec2(glWidth / 2 + 48, 85.5), IM_COL32(87, 143, 255, 15));
            draw->AddRectFilled(ImVec2(glWidth / 2 - 44, 61.5), ImVec2(glWidth / 2 + 44, 85.5), IM_COL32(87, 143, 255, 15));
            draw->AddRectFilled(ImVec2(glWidth / 2 - 40, 61.5), ImVec2(glWidth / 2 + 40, 85.5), IM_COL32(87, 143, 255, 15));
            draw->AddRectFilled(ImVec2(glWidth / 2 - 36, 61.5), ImVec2(glWidth / 2 + 36, 85.5), IM_COL32(87, 143, 255, 15));
            draw->AddText(nullptr, ((float) density / 21.0f), ImVec2(glWidth / 2 - 32.f, 61), IM_COL32(255, 255, 255, 255), s.c_str());
            }
			}
			}
			}
			}
			}
			}
			
			

			
		
	   	    
		

			
		// Src ~ NIKHIL_VIP_OWNER
		// Src ~ NIKHIL_VIP_OWNER
EGLBoolean (*orig_eglSwapBuffers)(EGLDisplay dpy, EGLSurface surface);

EGLBoolean _eglSwapBuffers(EGLDisplay dpy, EGLSurface surface) {
    eglQuerySurface(dpy, surface, EGL_WIDTH, &glWidth);
    eglQuerySurface(dpy, surface, EGL_HEIGHT, &glHeight);

    if (glWidth <= 0 || glHeight <= 0)
        return orig_eglSwapBuffers(dpy, surface);

    if (!g_App)
        return orig_eglSwapBuffers(dpy, surface);

    screenWidth = ANativeWindow_getWidth(g_App->window);
    screenHeight = ANativeWindow_getHeight(g_App->window);
    density = AConfiguration_getDensity(g_App->config);

    if (!initImGui) {
        ImGui::CreateContext();
// ================= OVERLAY STYLE (FULLY TRANSPARENT) =================
ImGuiStyle& style = ImGui::GetStyle();
ImGui::StyleColorsDark();

// -------- rounding / spacing -----------
style.WindowRounding    = 10.f;
style.FrameRounding     = 9.f;
style.ChildRounding     = 8.f;
style.ScrollbarRounding = 8.f;
style.ScrollbarSize     = 20.f;
style.GrabMinSize       = 11.f;
style.FrameBorderSize   = 4.f;
style.WindowBorderSize  = 4.f;

style.ItemSpacing       = ImVec2(6,4);
style.ItemInnerSpacing  = ImVec2(12,3);
style.WindowTitleAlign  = ImVec2(0.5f,0.5f);
style.ButtonTextAlign   = ImVec2(0.5f,0.5f);
style.FramePadding      = ImVec2(4,4);
style.WindowPadding     = ImVec2(10,10);

// -------- COLORS --------
ImVec4 transparent = ImVec4(0,0,0,0);                // ImVec4 aise define karo
style.Colors[ImGuiCol_WindowBg]        = transparent;
style.Colors[ImGuiCol_ChildBg]         = transparent;
style.Colors[ImGuiCol_PopupBg]         = transparent;
style.Colors[ImGuiCol_FrameBg]         = transparent;
style.Colors[ImGuiCol_FrameBgHovered]  = transparent;
style.Colors[ImGuiCol_FrameBgActive]   = transparent;
style.Colors[ImGuiCol_TitleBg]         = transparent;
style.Colors[ImGuiCol_TitleBgActive]   = transparent;
style.Colors[ImGuiCol_TitleBgCollapsed]= transparent;

// text pure green
style.Colors[ImGuiCol_Text] = ImVec4(0,1,0,1);       // 0‑1 range (0,255,0,255 -> 0,1,0,1)

// ---------- RGB BORDER ANIMATION ----------
static float hue = 0.f;
hue += 0.002f;
if (hue > 1.f) hue = 0.f;

// HSV‑>RGB, returns ImVec4
ImVec4 rgb = ImColor::HSV(hue, 1.f, 1.f);

style.Colors[ImGuiCol_Border]       = rgb;
style.Colors[ImGuiCol_BorderShadow] = rgb;

// ---------------------------------------------------------------------
// Ab window, child, popup sab total transparent; sirf border + widgets dikhेंगे.



        ImGui_ImplAndroid_Init();
        ImGui_ImplOpenGL3_Init("#version 300 es");
        ImGuiIO &io = ImGui::GetIO();

		io.Fonts->AddFontFromMemoryCompressedTTF(Roboto_compressed_data, Roboto_compressed_size, 19.f, nullptr, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
        ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(Roboto_compressed_data, Roboto_compressed_size, 19.f, nullptr, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
		/*
		io.Fonts->AddFontFromMemoryTTF((void *)Custom_data, Custom_size, 20.0f, NULL, 
		io.Fonts->GetGlyphRangesChineseFull());    
		*/
        ImFontConfig cfg; 
        cfg.SizePixels = ((float) density / 20.0f);
        io.Fonts->AddFontDefault(&cfg);
        initImGui = true;
        }
		// Src ~ @TheFlith
    ImGuiIO &io = ImGui::GetIO();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame(glWidth, glHeight);
    ImGui::NewFrame();

    DrawESP(ImGui::GetBackgroundDrawList());     
    ImGui::SetNextWindowSize(ImVec2((float) glWidth * 0.45f, (float) glHeight * 0.80f), ImGuiCond_Once);
	char buf[128];
  sprintf(buf, (OBFUSCATE("NEXXA NEW SRC 64 BIT </> %0.1f FPS ###AnimatedTitle")),(io.Framerate), ImGui::GetFrameCount());

    if (ImGui::Begin(buf), NULL,   ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoSavedSettings){
	static bool NIKHILPAPA1 = "f";
     static bool NIKHILPAPA2 = "a";
     static bool NIKHILPAPA3 = "l";
     static bool NIKHILPAPA4 = "s";
     static bool NIKHILPAPA5 = "e";
     static bool isLogin, logginIn = NIKHILPAPA1+NIKHILPAPA2+NIKHILPAPA3+NIKHILPAPA4+NIKHILPAPA5;   {
// Global RGB hue
static float rgbHue = 0.0f;

// RGB update every frame
rgbHue += 0.001f;
if (rgbHue > 1.0f) rgbHue = 0.0f;

ImVec4 rgbColor = ImColor::HSV(rgbHue, 1.0f, 1.0f); // HSV to RGB
ImGuiStyle& style = ImGui::GetStyle();

// Apply style first (your existing code, can be loaded once)
ImGui::StyleColorsDark();
// ... [your full style setup here as before]

// Apply animated RGB to border and border shadow
style.Colors[ImGuiCol_Border] = rgbColor;
style.Colors[ImGuiCol_BorderShadow] = rgbColor;
	
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
				
// Snake animation + fire trail
// Snake animation + fire trail
const auto& drawList = ImGui::GetWindowDrawList();
ImVec2 winPos = ImGui::GetWindowPos();
ImVec2 winSize = ImGui::GetWindowSize();

float time = ImGui::GetTime();
int segments = 250;
int totalSnakes = 20;

float snakeSpeed = 1.0f;
float waveAmplitude = 10.0f;
float waveFreq = 4.0f;

static std::vector<ImVec2> snakeCenters;
static std::vector<ImVec2> snakeDirs;
if (snakeCenters.size() != totalSnakes) {
    snakeCenters.clear();
    snakeDirs.clear();
    for (int i = 0; i < totalSnakes; ++i) {
        float x = winPos.x + rand() % (int)winSize.x;
        float y = winPos.y + rand() % (int)winSize.y;
        snakeCenters.push_back(ImVec2(x, y));

        float angle = (rand() % 360) * (IM_PI / 180.0f);
        snakeDirs.push_back(ImVec2(cosf(angle), sinf(angle)));
    }
}

for (int s = 0; s < totalSnakes; ++s)
{
    ImVec2& center = snakeCenters[s];
    ImVec2& dir = snakeDirs[s];

    center.x += dir.x * snakeSpeed;
    center.y += dir.y * snakeSpeed;

    if (center.x < winPos.x || center.x > winPos.x + winSize.x) dir.x *= -1;
    if (center.y < winPos.y || center.y > winPos.y + winSize.y) dir.y *= -1;

    float snakeTimeOffset = s * 0.7f;

    ImU8 rBase = 200;
    ImU8 gBase = 120;
    ImU8 bBase = 50;

    std::vector<ImVec2> snakePath;
    for (int i = 0; i < segments; ++i) {
        float t = (float)i / segments;
        float baseX = center.x - dir.x * t * 12;
        float baseY = center.y - dir.y * t * 12;

        float wave = sinf((time + snakeTimeOffset) + t * waveFreq) * waveAmplitude;
        ImVec2 normal(-dir.y, dir.x);
        ImVec2 pos = ImVec2(
            baseX + normal.x * wave,
            baseY + normal.y * wave
        );
        snakePath.push_back(pos);
    }

    for (int i = 1; i < segments; ++i) {
        float t = (float)i / segments;
        float glow = sinf(time * 10.0f - t * 20.0f) * 0.5f + 0.5f;

        ImU32 color = IM_COL32(
            rBase + glow * 55,
            gBase + glow * 40,
            bBase,
            (int)(130 + 100 * (1.0f - t))
        );

        float thickness = 5.0f * (1.0f - t) + 1.2f;
        drawList->AddLine(snakePath[i - 1], snakePath[i], color, thickness);
    }

    // Snake head
    ImVec2 head = snakePath[0];
    drawList->AddCircleFilled(head, 10.0f, IM_COL32(255, 140, 0, 255));
    drawList->AddCircleFilled(ImVec2(head.x - 2.5f, head.y - 2.5f), 2.0f, IM_COL32(0, 0, 0, 255));
    drawList->AddCircleFilled(ImVec2(head.x + 2.5f, head.y - 2.5f), 2.0f, IM_COL32(0, 0, 0, 255));

    // Flickering fire tongue
    if (((int)((time + s) * 6)) % 2 == 0) {
        drawList->AddLine(head, ImVec2(head.x, head.y + 14), IM_COL32(255, 80, 0, 255), 1.5f);
        drawList->AddLine(ImVec2(head.x, head.y + 14), ImVec2(head.x - 3, head.y + 18), IM_COL32(255, 50, 0, 255), 1.2f);
        drawList->AddLine(ImVec2(head.x, head.y + 14), ImVec2(head.x + 3, head.y + 18), IM_COL32(255, 50, 0, 255), 1.2f);
    }
}



// =================================================================
				
				
		// Src ~ NIKHIL_VIP_OWNER
               if(ImGui::Button("MAIN MENU", ImVec2(152, 40))) {
               Settings::Tab = 1;
               }
               ImGui::SameLine();
    
               if(ImGui::Button("EXTRA MENU", ImVec2(152, 40))) {
               Settings::Tab = 2;
               }
               ImGui::SameLine();
      
               if(ImGui::Button("BULLET MENU", ImVec2(147, 40))) {
               Settings::Tab = 3;
               }
   
               ImGui::Spacing();
               ImGui::Separator();
		// Src ~ NIKHIL_VIP_OWNER
                if (Settings::Tab == 1) {
                if (ImGui::Button("START ESP",ImVec2(315, 40))) {
                Cheat::Esp::TargetLine = true;
                Cheat::Esp::Line = true;
                Cheat::Esp::Skeleton = true;
                Cheat::Esp::Health = true;
                Cheat::Esp::Distance = true;
                Cheat::Esp::Name = true;
                Cheat::Esp::TeamID = true;
                Cheat::Esp::Alert = true;
				Cheat::Memory::GameInfo = true;
				Cheat::BulletTrack::EnimiesAlert = true;
                }
		// Src ~ NIKHIL_VIP_OWNER
                if (ImGui::Button("STOP ESP",ImVec2(315, 40))) {
                Cheat::Esp::TargetLine = false;
                Cheat::Esp::Line = false;
                Cheat::Esp::Skeleton = false;
                Cheat::Esp::Health = false;
                Cheat::Esp::Distance = false;
                Cheat::Esp::Name = false;
                Cheat::Esp::TeamID = false;
				
                Cheat::Esp::Alert = false;
				Cheat::Memory::GameInfo = false;
				Cheat::BulletTrack::EnimiesAlert = false;
                }
		// Src ~ NIKHIL_VIP_OWNER
                ImGui::Spacing();
                ImGui::Separator();
   
                ImGui::PushItemWidth(150);  // You can adjust the width as needed
                ImGui::SliderFloat("150", &Cheat::Memory::WideViewRange, (0.0f), (150.0f),"%.0f");
                ImGui::PopItemWidth();
                ImGui::Spacing();
                ImGui::Columns(2);
				/*if (ImGui::Checkbox(" Lobby Bypass", &Cheat::Memory::SnaxLobby)) {
                pthread_create(&t, 0, run_thread, (void *) (177));
                }*/
               // ImGui::NextColumn();
     //           ImGui::Checkbox(" Auto Flash", &Cheat::Memory::SnaxParachute);
                ImGui::NextColumn();
                ImGui::Checkbox(" HeadShoot V2", &Cheat::AimBot::HeadShoot);
               // ImGui::NextColumn();
			//	if (ImGui::Checkbox(" XHit Effect", &Cheat::Memory::XHitEffect)) {
              //  pthread_create(&t, 0, run_thread, (void *) (107));
              //  }
                ImGui::NextColumn();
                ImGui::Checkbox(" Sdk->Cross", &Cheat::Memory::SmallCrossHair);
                ImGui::NextColumn();
                ImGui::Checkbox(" Instant Hit", &Cheat::Memory::InstantHit);
                ImGui::NextColumn();
				ImGui::Checkbox(" Sdk->IPad View", &Cheat::Memory::IPadView);
                ImGui::NextColumn();
				ImGui::Checkbox(" Sdk->No Recoil", &Cheat::Memory::NoRecoil);
				ImGui::NextColumn();
			//	ImGui::Checkbox(" Sdk->No Recoil", &Cheat::Memory::NoRecoil);
            //    if (ImGui::Checkbox(" Sdk->No Grass", &Cheat::Memory::NoTree)) {
             //   pthread_create(&t, 0, run_thread, (void *) (106));
			//	if (ImGui::Checkbox(" XHit Effect", &Cheat::Memory::XHitEffect)) {
             //   pthread_create(&t, 0, run_thread, (void *) (107));
	
           
				     
                ImGui::Columns(1);
                ImGui::Spacing();
                ImGui::Separator();/*
                if (ImGui::Button("Delete Reports",ImVec2(225, 40))) {
                system(OBFUSCATE("rm -rf /data/data/com.pubg.imobile/shared_prefs"));
                system(OBFUSCATE("rm -rf /data/data/com.pubg.imobile/databases"));
                system(OBFUSCATE("rm -rf /data/data/com.pubg.imobile/cache"));
                system(OBFUSCATE("rm -rf /data/data/com.pubg.imobile/app_crashKit"));
                system(OBFUSCATE("rm -rf /data/data/com.pubg.imobile/app_webview"));
                system(OBFUSCATE("rm -rf /storage/emulated/0/Android/data/com.pubg.imobile/cache*"));
                system(OBFUSCATE("rm -rf /storage/emulated/0/Android/data/com.pubg.imobile/files/cacheFile.txt"));
                system(OBFUSCATE("rm -rf /storage/emulated/0/Android/data/com.pubg.imobile/files/login-identifier.txt"));
                system(OBFUSCATE("rm -rf /storage/emulated/0/Android/data/com.pubg.imobile/files/UE4Game/ShadowTrackerExtra/ShadowTrackerExtra/Saved/Avatar*"));
                system(OBFUSCATE("rm -rf /storage/emulated/0/Android/data/com.pubg.imobile/files/UE4Game/ShadowTrackerExtra/ShadowTrackerExtra/Saved/Collision_Detection"));
 
                system(OBFUSCATE("rm -rf /storage/emulated/0/Android/data/com.pubg.imobile/files/UE4Game/ShadowTrackerExtra/ShadowTrackerExtra/Saved/Demos/UserReplay*"));
                system(OBFUSCATE("rm -rf /storage/emulated/0/Android/data/com.pubg.imobile/files/UE4Game/ShadowTrackerExtra/ShadowTrackerExtra/Saved/ImageDownload*"));
                system(OBFUSCATE("rm -rf /storage/emulated/0/Android/data/com.pubg.imobile/files/UE4Game/ShadowTrackerExtra/ShadowTrackerExtra/Saved/ImageDownloadMgr"));
                system(OBFUSCATE("rm -rf /storage/emulated/0/Android/data/com.pubg.imobile/files/UE4Game/ShadowTrackerExtra/ShadowTrackerExtra/Saved/Logs*"));
                system(OBFUSCATE("rm -rf /storage/emulated/0/Android/data/com.pubg.imobile/files/UE4Game/ShadowTrackerExtra/ShadowTrackerExtra/Saved/MMKV*"));
                system(OBFUSCATE("rm -rf /storage/emulated/0/Android/data/com.pubg.imobile/files/UE4Game/ShadowTrackerExtra/ShadowTrackerExtra/Saved/RoleInfo*"));
                system(OBFUSCATE("rm -rf /storage/emulated/0/Android/data/com.pubg.imobile/files/UE4Game/ShadowTrackerExtra/ShadowTrackerExtra/Saved/GameErrorNoRecords"));
                system(OBFUSCATE("rm -rf /storage/emulated/0/Android/data/com.pubg.imobile/files/UE4Game/ShadowTrackerExtra/ShadowTrackerExtra/Saved/StatEventReportedFlag"));
                }
                ImGui::SameLine();*/
                if (ImGui::Button("Logout Account",ImVec2(315, 40))) {
                system(OBFUSCATE("rm -rf /data/data/com.pubg.imobile/files"));
                }
                } 
		// Src ~ NIKHIL_VIP_OWNER
                if (Settings::Tab == 2) {
    				ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Text("X-SUIT SKIN ");
                                    const char* xsuuity[] = { "NO SKIN", "Blood Raven X-Suit", "Golden Pharaoh X-Suit", "Avalanche X-suit", "Irresidence X-suit", "Poseidon X-suit", "Arcane Jester X-suit", "Silvanus X-Suit", "Memorise X-Suit"};
                                    ImGui::Combo("##xs", &skinxsuit, xsuuity, IM_ARRAYSIZE(xsuuity));
                                    
           ImGui::Text("M416 SKIN  ");
                                    const char* m416[] = { "NO SKIN", " Glacier - M416", "The Fool - M416","Lizard Roar - M416"," Wanderer - M416","Call of the Wild - M416", "Imperial Splendor - M416", "Silver Guru - M416", "TechnoCore - M416","Tidal Embrace - M416","Shinobi Kami - M416"};
                                    ImGui::Combo("##m4", &skinm4, m416, IM_ARRAYSIZE(m416));
                                    ImGui::TableNextColumn();
                                    ImGui::Spacing();
					
            ImGui::Text("AKM SKIN ");
            const char* AKM[] = { "NO SKIN", "Sculpture - AKM", "The Seven Seas - AKM","Roaring Tiger - AKM","Glacier - AKM","Desert Fossil - AKM","Jack-o'-lantern - AKM","Ghillie Dragon - AKM"};
            ImGui::Combo("##AKM", &skinakm, AKM, IM_ARRAYSIZE(AKM));
            ImGui::TableNextColumn();
			ImGui::Spacing();
            ImGui::Text("SCAR-L SKIN ");
            const char* SCAR[] = { "NO SKIN", "Water Blaster - SCAR-L", "Enchanted Pumpkin - SCAR-L","Enchanted Pumpkin - SCAR-L","Operation Tomorrow - SCAR-L "};
            ImGui::Combo("##SCAR-L", &skinscar, SCAR, IM_ARRAYSIZE(SCAR));
			ImGui::TableNextColumn();
				
                }
			    }
				
			if (Settings::Tab == 3) {	
				
 
			
			
			                if (ImGui::Checkbox(" Aim->One Click All Features On", &masterCheckbox2)) {
                Cheat::BulletTrack::Enable = masterCheckbox2;
                ByPussy = masterCheckbox2;
                Cheat::BulletTrack::Enable = masterCheckbox2;
                Cheat::BulletTrack::Range = 400.0f;
                Cheat::BulletTrack::VisCheck = masterCheckbox2;
                Cheat::BulletTrack::IgnoreKnock = masterCheckbox2;

                }
				
				ImGui::Checkbox("AIMBOT BUTTON", &AIMBUTTON);
				ImGui::Checkbox(" Aim->Enable AIMBOT", &Cheat::AimBot::Enable);
		  ImGui::Spacing();
					ImGui::Text("TRIGGER: ");
                    ImGui::SameLine();
                    static const char *targets[] = {"HEAD", "BODY"};
					ImGui::Spacing();
                    ImGui::Combo("##Target", (int *) &Cheat::AimBot::Target, targets, 2, -1);
					ImGui::Spacing();
					ImGui::Text("Target: ");
			        ImGui::Spacing();
			        static const char *triggers[] = {"None", "Shooting", "Scoping", "Both (Shooting & Scoping)", "Any (Shooting / Scoping"};
					ImGui::Spacing();
                    ImGui::Combo("##Trigger", (int *) &Cheat::AimBot::Trigger, triggers, 5, -1);
				    ImGui::Spacing();
			    	ImGui::Spacing();
					ImGui::DragFloat("Cross", &Cheat::AimBot::Cross, 6.2f, 0.0f, 1500.0f, "%.0f");
 
			//	ImGui::Checkbox(" MAGIC->BULLET", &Cheat::Esp::MagicBullet);
				ImGui::Checkbox(" Enemy->Visibility Check", &Cheat::AimBot::VisCheck);
                ImGui::Checkbox(" Enemy->Ignore Kidz", &Cheat::AimBot::IgnoreBot);
                
				ImGui::Checkbox(" Aim->Enable BT", &Cheat::BulletTrack::Enable);
				ImGui::Checkbox("BULLET TRACK BUTTON ", &BTBUTTON);
			    ImGui::SliderFloat(" Set->Aim Radius BT", &Cheat::BulletTrack::Radius, (0.0f), (1000.0f),"%.0f");                  
                ImGui::SliderFloat(" Set->Aim Range BT", &Cheat::BulletTrack::Range, (0.0f), (400.0f),"%.0f");
                ImGui::SliderFloat(" Set->Aim Position", &Cheat::BulletTrack::AimSet, (-17.0f), (10.0f),"%.0f");
                ImGui::Checkbox(" Enemy->Visibility Check", &Cheat::BulletTrack::VisCheck);
                ImGui::Checkbox(" Enemy->Ignore Knocked", &Cheat::BulletTrack::IgnoreKnock);
                ImGui::Checkbox(" Enemy->Ignore Kidz", &Cheat::BulletTrack::IgnoreBot);
				ImGui::Checkbox(" LAMBORGHINI " , &Cheat::BulletTrack::LAMBORGHINI);
				ImGui::Checkbox(" Esp->Vehicle Name", &Cheat::Esp::Vehicle::Name);
                ImGui::Checkbox(" Esp->Vehicle Health", &Cheat::Esp::Vehicle::Health);
                ImGui::Checkbox(" Esp->Vehicle Fuel", &Cheat::Esp::Vehicle::Fuel);
			ImGui::TableNextColumn();
			
			
}
				            }
							
							
ImGui::Render();
ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
return orig_eglSwapBuffers(dpy, surface);
							
				}
			   ImGui::EndChild();   
                }
				
				
				
		// Src ~ NIKHIL_VIP_OWNER
 






#define SLEEP_TIME 1000LL / 120LL
void *ipad_thread(void *) {
        while (true) {
        auto t1 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        if (Cheat::Memory::WideView) {
        auto objs = UObject::GetGlobalObjects();
        for (int i = 0; i < objs.Num(); i++) {
        auto Object = objs.GetByIndex(i);
        if (isObjectInvalid(Object))
                continue;
          if (Object->IsA(ULocalPlayer::StaticClass())) {
          auto playerChar = (ULocalPlayer *) Object;      
          playerChar->AspectRatioAxisConstraint = EAspectRatioAxisConstraint::AspectRatio_MaintainYFOV;
     }     
     }
     }
         auto td = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - t1;
         std::this_thread::sleep_for(std::chrono::milliseconds(std::max(std::min(0LL, SLEEP_TIME - td),SLEEP_TIME)));
     }  
     }
	 
	 
void *main_thread(void *) {
anogs = Tools::GetBaseAddress("libanogs.so");
        while (!anogs) {
            anogs = Tools::GetBaseAddress("libanogs.so");
            sleep(1);

		}
	 

    Cheat::libUE4Base = Tools::GetBaseAddress("libUE4.so");
    while (!Cheat::libUE4Base) {
        Cheat::libUE4Base = Tools::GetBaseAddress("libUE4.so");
        sleep(1);
		
; //100rw-p228ffe
    }
    while (!g_App) {
        g_App = *(android_app * *)(Cheat::libUE4Base + Cheat::GNativeAndroidApp_Offset);
        sleep(1);
    }
    
    FName::GNames = GetGNames();
    while (!FName::GNames) {
        FName::GNames = GetGNames();
        sleep(1);
    }
    UObject::GUObjectArray = (FUObjectArray * )(Cheat::libUE4Base + Cheat::GUObject_Offset);

    orig_onInputEvent = decltype(orig_onInputEvent)(g_App->onInputEvent);
    g_App->onInputEvent = onInputEvent;
    initOffset();

    Tools::Hook((void *) DobbySymbolResolver(OBFUSCATE("/system/lib/libEGL.so"), OBFUSCATE("eglSwapBuffers")), (void *) _eglSwapBuffers, (void **) &orig_eglSwapBuffers);
    Tools::Hook((void *) (Cheat::libUE4Base + Cheat::ProcessEvent_Offset), (void *) hkProcessEvent, (void **) &oProcessEvent);

    return nullptr;
}

__attribute__((constructor)) void _init() {

    pthread_create(&t, NULL, main_thread, NULL);
	pthread_create(&t, NULL, ipad_thread, NULL);
/*  pthread_create(&t, NULL, anogs_thread, NULL);
    pthread_create(&t, NULL, ue4_thread, NULL);*/
}
		// Src ~ NIKHIL_VIP_OWNER

