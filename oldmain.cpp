// ========================================================================================
// Advanced Gaming Enhancement Suite
// Modern ImGui-based Interface with AI-assisted targeting and enemy prediction
// ========================================================================================

#include <random>
#include <cstdint>
#include <chrono>
#include <array>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <memory>
#include <thread>
#include <mutex>
#include <deque>

#include "Includes/include.h"
#include "Includes/definition.h"

// ========================================================================================
// CONFIGURATION & CORE CONSTANTS
// ========================================================================================

namespace Config {
    // Game Settings
    namespace Game {
        float RenderDistance = 500.0f; // Maximum render distance for ESP
        int MaxPlayers = 100;
        bool AutoDetectVersion = true;
    }

    // ESP Settings
    namespace ESP {
        bool Enabled = true;
        bool Box = true;
        bool Skeleton = true;
        bool Name = true;
        bool Distance = true;
        bool Health = true;
        bool Line = true;
        float LineThickness = 1.0f;
        bool TeamID = true;
        bool WeaponName = true;
        bool NoBot = false;
        bool VisibleCheck = true;
        bool PredictionLine = true;  // Show movement prediction lines
        float PredictionTime = 2.0f;  // Seconds to predict forward
    }

    // Combat Settings
    namespace Combat {
        bool AimbotEnabled = true;
        float AimbotFOV = 350.0f;
        float AimbotSmoothing = 4.0f;
        int TargetPriority = 0; // 0 = Closest to crosshair, 1 = Lowest health, 2 = Closest distance
        bool PredictiveAiming = true;
        float BulletSpeed = 900.0f; // Average bullet speed for prediction
        bool AutoScope = false;
        bool AutoFire = false;
        bool NoRecoil = true;
        bool InstantHit = false;
        bool MagicBullet = true;
        bool HeadOnly = true;
        bool VisibilityCheck = true;
        bool IgnoreKnocked = true;
        bool IgnoreBots = false;
    }

    // Visual Settings
    namespace Visual {
        bool WideView = true;
        float FOV = 110.0f;
        bool ShowFPS = true;
        bool SmallCrosshair = true;
        bool ShowEnemyCount = true;
        bool PulseEffect = true;
        bool ShowHealthText = true;
        bool ShowWeaponInfo = true;
    }

    // AI Features
    namespace AI {
        bool Enabled = true;
        bool PredictMovement = true;
        bool AnalyzeThreatLevel = true;
        bool AutoSuggestActions = true;
        bool AlertMode = true;
        int AlertThreshold = 70; // 0-100 sensitivity
        bool AutoAdaptTargeting = true;
        bool TrackEnemyPatterns = true;
        int MemoryLength = 50; // How many positions to remember per player
        float ThreatDisplayTime = 5.0f; // How long to display threat alerts
    }

    // Memory Settings
    namespace Memory {
        bool AutoClean = true;
        bool AntiReport = true;
        bool SafeMode = true;
        bool InstantRefresh = true;
        bool MemoryPooling = true;
        int PoolSize = 64; // Memory pool size in MB
    }

    // Colors with runtime HSV adjustment
    namespace Colors {
        ImU32 VisibleEnemy = IM_COL32(0, 255, 0, 255);
        ImU32 InvisibleEnemy = IM_COL32(255, 0, 0, 255);
        ImU32 Bot = IM_COL32(255, 255, 0, 255);
        ImU32 TeamIndicator = IM_COL32(0, 255, 255, 255);
        ImU32 Warning = IM_COL32(255, 165, 0, 255);
        ImU32 Alert = IM_COL32(255, 0, 0, 255);
        ImU32 LowThreat = IM_COL32(0, 255, 0, 255);
        ImU32 MediumThreat = IM_COL32(255, 255, 0, 255);
        ImU32 HighThreat = IM_COL32(255, 0, 0, 255);
        
        // Dynamic color generators
        ImU32 Rainbow(float time) {
            float hue = fmodf(time, 1.0f);
            return ImColor::HSV(hue, 1.0f, 1.0f);
        }
        
        ImU32 PulseColor(ImU32 color, float intensity = 0.3f) {
            float time = ImGui::GetTime();
            float pulse = (sinf(time * 3.0f) * intensity) + (1.0f - intensity);
            ImVec4 col = ImGui::ColorConvertU32ToFloat4(color);
            col.w *= pulse;
            return ImGui::ColorConvertFloat4ToU32(col);
        }
    }
}

// ========================================================================================
// AI THREAT ANALYSIS AND PREDICTION SYSTEM
// ========================================================================================

class AISystem {
private:
    struct PlayerHistory {
        std::deque<FVector> positions;
        std::deque<float> timestamps;
        FVector velocity;
        FVector predictedPosition;
        int threatLevel = 0;  // 0-100
        bool isTargetingMe = false;
        float lastUpdateTime = 0;
        bool isVisible = false;
        float health = 100.0f;
        float distance = 1000.0f;
        std::string weaponName = "Unknown";
        int accuracy = 50;  // 0-100 estimated accuracy
        int activityLevel = 0;  // 0-100 how active they are
    };
    
    std::unordered_map<int, PlayerHistory> playerData;
    float lastAnalysisTime = 0;
    
    // Analysis constants
    const float ANALYSIS_INTERVAL = 0.2f;  // Run analysis every 200ms
    const float POSITION_EXPIRY = 30.0f;  // Expire position data after 30 seconds
    
public:
    struct ThreatAlert {
        int playerKey;
        std::string message;
        ImVec2 screenPos;
        float duration;
        float startTime;
        int threatLevel;  // 0-100
    };
    
    std::vector<ThreatAlert> activeAlerts;
    
    void TrackPlayer(ASTExtraPlayerCharacter* player, bool isVisible) {
        if (!player || !Config::AI::Enabled || !Config::AI::TrackEnemyPatterns)
            return;
        
        int playerKey = player->PlayerKey;
        float currentTime = ImGui::GetTime();
        
        // Initialize player data if needed
        if (playerData.find(playerKey) == playerData.end()) {
            playerData[playerKey] = PlayerHistory();
            playerData[playerKey].lastUpdateTime = currentTime;
        }
        
        auto& history = playerData[playerKey];
        
        // Add new position data
        FVector currentPos = player->GetActorLocation();
        history.positions.push_back(currentPos);
        history.timestamps.push_back(currentTime);
        
        // Keep history size limited
        while (history.positions.size() > Config::AI::MemoryLength) {
            history.positions.pop_front();
            history.timestamps.pop_front();
        }
        
        // Update other player data
        history.isVisible = isVisible;
        history.health = player->Health;
        
        if (g_LocalPlayer)
            history.distance = player->GetDistanceTo(g_LocalPlayer) / 100.0f;
        
        // Weapon information
        auto weaponManager = player->WeaponManagerComponent;
        if (weaponManager && weaponManager->CurrentWeaponReplicated) {
            auto weapon = reinterpret_cast<ASTExtraShootWeapon*>(weaponManager->CurrentWeaponReplicated);
            if (weapon) {
                history.weaponName = weapon->WeaponBase.WeaponId.ToString();
            }
        }
        
        history.lastUpdateTime = currentTime;
        
        // Calculate velocity (if we have enough history)
        if (history.positions.size() > 5 && history.timestamps.size() > 5) {
            int lastIdx = history.positions.size() - 1;
            int prevIdx = lastIdx - 5;  // Get position from 5 steps ago for smoother calculation
            
            float timeDiff = history.timestamps[lastIdx] - history.timestamps[prevIdx];
            if (timeDiff > 0.001f) {  // Avoid division by near-zero
                FVector posDiff = history.positions[lastIdx] - history.positions[prevIdx];
                history.velocity = posDiff * (1.0f / timeDiff);
            }
        }
    }
    
    FVector PredictPosition(ASTExtraPlayerCharacter* player, float predictionTime) {
        if (!player || !Config::AI::Enabled || !Config::AI::PredictMovement)
            return player->GetActorLocation();
        
        int playerKey = player->PlayerKey;
        if (playerData.find(playerKey) == playerData.end())
            return player->GetActorLocation();
        
        auto& history = playerData[playerKey];
        
        // Basic linear prediction using velocity
        FVector predictedPos = player->GetActorLocation() + history.velocity * predictionTime;
        
        // Store prediction
        history.predictedPosition = predictedPos;
        
        return predictedPos;
    }
    
    void AnalyzeThreats(ASTExtraPlayerCharacter* localPlayer, ASTExtraPlayerController* localController) {
        if (!localPlayer || !localController || !Config::AI::Enabled || !Config::AI::AnalyzeThreatLevel)
            return;
        
        float currentTime = ImGui::GetTime();
        if (currentTime - lastAnalysisTime < ANALYSIS_INTERVAL)
            return;
        
        lastAnalysisTime = currentTime;
        
        // Remove expired alerts
        activeAlerts.erase(
            std::remove_if(activeAlerts.begin(), activeAlerts.end(), 
                [currentTime](const ThreatAlert& alert) {
                    return (currentTime - alert.startTime) > alert.duration;
                }
            ),
            activeAlerts.end()
        );
        
        // Analyze each tracked player
        for (auto& pair : playerData) {
            int playerKey = pair.first;
            auto& history = pair.second;
            
            // Skip if data is too old
            if (currentTime - history.lastUpdateTime > POSITION_EXPIRY)
                continue;
            
            int oldThreatLevel = history.threatLevel;
            
            // Calculate threat level based on multiple factors
            int threatLevel = 0;
            
            // Distance factor (closer = more threat)
            int distanceThreat = std::min(100, int(100.0f * (250.0f / (history.distance + 50.0f))));
            threatLevel += distanceThreat * 0.4f; // 40% weight from distance
            
            // Weapon factor
            int weaponThreat = 0;
            if (history.weaponName.find("AWM") != std::string::npos ||
                history.weaponName.find("Kar98") != std::string::npos ||
                history.weaponName.find("M24") != std::string::npos) {
                weaponThreat = 90; // Sniper rifles are dangerous
            } else if (history.weaponName.find("M416") != std::string::npos ||
                       history.weaponName.find("AKM") != std::string::npos ||
                       history.weaponName.find("Groza") != std::string::npos) {
                weaponThreat = 75; // Assault rifles
            } else if (history.weaponName.find("UMP") != std::string::npos ||
                       history.weaponName.find("Vector") != std::string::npos) {
                weaponThreat = 60; // SMGs
            }
            threatLevel += weaponThreat * 0.2f; // 20% weight from weapon
            
            // Aiming at me factor (high priority)
            bool mightBeAimingAtMe = false;
            if (history.positions.size() > 3) {
                // Calculate a rough direction vector
                FVector playerDirection = history.positions.back() - history.positions[history.positions.size() - 3];
                UKismetMathLibrary::Normalize(playerDirection);
                
                // Calculate vector from enemy to me
                FVector toMeDirection = localPlayer->GetActorLocation() - history.positions.back();
                UKismetMathLibrary::Normalize(toMeDirection);
                
                // Check dot product for similarity
                float dotProduct = UKismetMathLibrary::Dot_VectorVector(playerDirection, toMeDirection);
                if (dotProduct > 0.8f) { // If they're pointing roughly at me
                    mightBeAimingAtMe = true;
                    threatLevel += 40; // Significant threat increase if aiming at me
                }
            }
            history.isTargetingMe = mightBeAimingAtMe;
            
            // Visibility factor
            if (history.isVisible) {
                threatLevel += 20; // Visible enemies are more of a threat
            }
            
            // Movement pattern factor - check if player is strafing/moving aggressively
            int movementThreatFactor = 0;
            if (history.positions.size() > 10) {
                float movementVariance = 0;
                for (size_t i = 1; i < history.positions.size(); i++) {
                    FVector posDiff = history.positions[i] - history.positions[i-1];
                    movementVariance += UKismetMathLibrary::VSize(posDiff);
                }
                movementVariance /= history.positions.size();
                
                if (movementVariance > 50.0f) { // High movement
                    movementThreatFactor = 15;
                } else if (movementVariance < 5.0f) { // Barely moving (camping/sniping)
                    movementThreatFactor = 25;
                }
            }
            threatLevel += movementThreatFactor;
            
            // Clamp final threat level
            history.threatLevel = std::min(100, std::max(0, threatLevel));
            
            // Create/update alerts for significant threats
            if (history.threatLevel > Config::AI::AlertThreshold) {
                if (history.threatLevel > oldThreatLevel + 20 || // Significant increase
                    (history.threatLevel > 80 && mightBeAimingAtMe)) { // Critical threat
                    
                    std::string message;
                    if (mightBeAimingAtMe && history.isVisible) {
                        message = "DANGER: Enemy targeting you!";
                    } else if (history.threatLevel > 90) {
                        message = "Critical threat nearby!";
                    } else if (history.threatLevel > 70) {
                        message = "High threat detected!";
                    } else {
                        message = "Potential threat!";
                    }
                    
                    // Add alert
                    ThreatAlert alert;
                    alert.playerKey = playerKey;
                    alert.message = message;
                    alert.startTime = currentTime;
                    alert.duration = Config::AI::ThreatDisplayTime;
                    alert.threatLevel = history.threatLevel;
                    
                    // Try to get screen position
                    FVector2D screenPos;
                    if (W2S(history.positions.back(), &screenPos)) {
                        alert.screenPos = ImVec2(screenPos.X, screenPos.Y);
                    } else {
                        alert.screenPos = ImVec2(ImGui::GetIO().DisplaySize.x/2, 100); // Default to top middle
                    }
                    
                    activeAlerts.push_back(alert);
                }
            }
        }
    }
    
    void RenderThreatAlerts(ImDrawList* draw) {
        if (!Config::AI::Enabled || !Config::AI::AlertMode)
            return;
            
        float currentTime = ImGui::GetTime();
        
        for (const auto& alert : activeAlerts) {
            float elapsed = currentTime - alert.startTime;
            float alpha = 1.0f;
            
            // Fade in/out animation
            if (elapsed < 0.5f) {
                alpha = elapsed / 0.5f;
            } else if (elapsed > (alert.duration - 0.5f)) {
                alpha = (alert.duration - elapsed) / 0.5f;
            }
            
            // Determine color based on threat level
            ImU32 alertColor;
            if (alert.threatLevel > 80) {
                alertColor = IM_COL32(255, 0, 0, static_cast<int>(255 * alpha));
            } else if (alert.threatLevel > 60) {
                alertColor = IM_COL32(255, 165, 0, static_cast<int>(255 * alpha));
            } else {
                alertColor = IM_COL32(255, 255, 0, static_cast<int>(255 * alpha));
            }
            
            // Pulse effect
            float pulse = 1.0f + sinf(currentTime * 8.0f) * 0.2f;
            
            // Draw alert box with message
            ImVec2 textSize = ImGui::CalcTextSize(alert.message.c_str());
            ImVec2 boxPos = ImVec2(alert.screenPos.x - textSize.x/2 - 10, alert.screenPos.y - textSize.y*2);
            ImVec2 boxSize = ImVec2(textSize.x + 20, textSize.y + 10);
            
            // Background
            draw->AddRectFilled(
                boxPos,
                ImVec2(boxPos.x + boxSize.x, boxPos.y + boxSize.y),
                IM_COL32(0, 0, 0, static_cast<int>(180 * alpha)),
                4.0f
            );
            
            // Border
            draw->AddRect(
                boxPos,
                ImVec2(boxPos.x + boxSize.x, boxPos.y + boxSize.y),
                alertColor,
                4.0f,
                0,
                2.0f * pulse
            );
            
            // Text
            draw->AddText(
                ImVec2(boxPos.x + 10, boxPos.y + 5),
                alertColor,
                alert.message.c_str()
            );
            
            // Directional indicator if off screen
            ImVec2 screenSize = ImGui::GetIO().DisplaySize;
            if (alert.screenPos.x < 0 || alert.screenPos.x > screenSize.x ||
                alert.screenPos.y < 0 || alert.screenPos.y > screenSize.y) {
                
                // Calculate direction to alert
                ImVec2 screenCenter(screenSize.x/2, screenSize.y/2);
                ImVec2 direction = ImVec2(alert.screenPos.x - screenCenter.x, alert.screenPos.y - screenCenter.y);
                float length = sqrtf(direction.x * direction.x + direction.y * direction.y);
                
                if (length > 0.001f) {
                    direction.x /= length;
                    direction.y /= length;
                    
                    // Calculate position on screen edge
                    float radius = std::min(screenSize.x, screenSize.y) * 0.4f;
                    ImVec2 indicatorPos = ImVec2(
                        screenCenter.x + direction.x * radius,
                        screenCenter.y + direction.y * radius
                    );
                    
                    // Draw arrow
                    const float arrowSize = 15.0f;
                    ImVec2 arrowTip = indicatorPos;
                    
                    float angle = atan2f(direction.y, direction.x);
                    ImVec2 arrow1(
                        arrowTip.x - arrowSize * cosf(angle + 0.5f),
                        arrowTip.y - arrowSize * sinf(angle + 0.5f)
                    );
                    ImVec2 arrow2(
                        arrowTip.x - arrowSize * cosf(angle - 0.5f),
                        arrowTip.y - arrowSize * sinf(angle - 0.5f)
                    );
                    
                    draw->AddTriangleFilled(arrowTip, arrow1, arrow2, alertColor);
                    draw->AddCircleFilled(arrowTip, 3.0f * pulse, alertColor);
                }
            }
        }
    }
    
    std::string GetBestActionSuggestion(ASTExtraPlayerCharacter* localPlayer, ASTExtraPlayerController* localController) {
        if (!localPlayer || !localController || !Config::AI::Enabled || !Config::AI::AutoSuggestActions)
            return "";
        
        // Count nearby threats by level
        int highThreats = 0, mediumThreats = 0, lowThreats = 0;
        int enemiesTargetingMe = 0;
        float nearestEnemyDistance = 1000.0f;
        
        for (const auto& pair : playerData) {
            const auto& history = pair.second;
            float currentTime = ImGui::GetTime();
            
            // Skip if data is too old
            if (currentTime - history.lastUpdateTime > POSITION_EXPIRY)
                continue;
                
            if (history.threatLevel > 75) highThreats++;
            else if (history.threatLevel > 40) mediumThreats++;
            else lowThreats++;
            
            if (history.isTargetingMe) enemiesTargetingMe++;
            
            if (history.distance < nearestEnemyDistance)
                nearestEnemyDistance = history.distance;
        }
        
        // Get player's health status
        float playerHealth = localPlayer->Health;
        float playerHealthPercent = (localPlayer->Health / localPlayer->HealthMax) * 100.0f;
        
        // Get player's position (for zone awareness)
        FVector playerPos = localPlayer->GetActorLocation();
        
        // Now make suggestions based on the situation
        if (enemiesTargetingMe > 1 && playerHealthPercent < 50) {
            return "⚠️ Multiple enemies targeting you - TAKE COVER!";
        } else if (highThreats > 2) {
            return "⚠️ Multiple high threats - consider repositioning";
        } else if (highThreats > 0 && playerHealthPercent < 30) {
            return "🩹 Low health! Heal before engaging";
        } else if (mediumThreats > 0 && nearestEnemyDistance < 50) {
            return "👁️ Close enemy - prepare for combat";
        } else if (nearestEnemyDistance < 200 && highThreats == 0 && mediumThreats == 0) {
            return "⚔️ Enemies nearby but unaware - good time to attack";
        } else if (highThreats + mediumThreats == 0 && lowThreats > 0) {
            return "🔍 Low threats only - safe to move or loot";
        }
        
        return "";
    }
    
    ImU32 GetThreatColor(int playerKey) {
        auto it = playerData.find(playerKey);
        if (it == playerData.end())
            return Config::Colors::LowThreat;
            
        int threatLevel = it->second.threatLevel;
        
        if (threatLevel > 75) return Config::Colors::HighThreat;
        if (threatLevel > 40) return Config::Colors::MediumThreat;
        return Config::Colors::LowThreat;
    }
};

// Global AI system instance
AISystem g_AISystem;

// ========================================================================================
// ENHANCED ESP DRAWING FUNCTIONS
// ========================================================================================

namespace ESP {
    // Draw a stroke text with 3D shadow effect
    void DrawStrokeText(ImDrawList* draw, float fontSize, ImVec2 pos, ImU32 color, const char* text, float strokeWidth = 1.0f) {
        // Shadow
        draw->AddText(nullptr, fontSize, ImVec2(pos.x + strokeWidth*1.5f, pos.y + strokeWidth*1.5f), IM_COL32(0, 0, 0, 100), text);
        
        // Outline (thicker outline)
        for (float x = -strokeWidth; x <= strokeWidth; x += strokeWidth) {
            for (float y = -strokeWidth; y <= strokeWidth; y += strokeWidth) {
                if (x == 0 && y == 0) continue; // Skip center position
                draw->AddText(nullptr, fontSize, ImVec2(pos.x + x, pos.y + y), IM_COL32(0, 0, 0, 255), text);
            }
        }
        
        // Main text
        draw->AddText(nullptr, fontSize, pos, color, text);
    }
    
    // Draw health bar with smoother gradients and effects
    void DrawHealthBar(ImDrawList* draw, float health, float maxHealth, ImVec2 pos, float width, float height, bool showText = false) {
        if (maxHealth <= 0.0f) maxHealth = 100.0f;
        health = std::clamp(health, 0.0f, maxHealth);
        float healthPercent = health / maxHealth;
        
        // Background with slight transparency
        draw->AddRectFilled(
            pos, 
            ImVec2(pos.x + width, pos.y + height), 
            IM_COL32(40, 40, 40, 180),
            height/4
        );
        
        // Health bar with gradient color
        ImU32 healthColor;
        if (healthPercent > 0.7f) {
            healthColor = IM_COL32(0, 255, 0, 255); // Green for high health
        } else if (healthPercent > 0.3f) {
            // Interpolate between yellow and green
            float t = (healthPercent - 0.3f) / 0.4f;
            int r = static_cast<int>(255 * (1 - t));
            int g = 255;
            healthColor = IM_COL32(r, g, 0, 255);
        } else {
            // Interpolate between red and yellow
            float t = healthPercent / 0.3f;
            int g = static_cast<int>(255 * t);
            healthColor = IM_COL32(255, g, 0, 255);
        }
        
        // Add pulsing effect for low health
        if (healthPercent < 0.25f && Config::Visual::PulseEffect) {
            float pulse = (sinf(ImGui::GetTime() * 8.0f) * 0.2f) + 0.8f;
            ImVec4 col = ImGui::ColorConvertU32ToFloat4(healthColor);
            col.w *= pulse;
            healthColor = ImGui::ColorConvertFloat4ToU32(col);
        }
        
        // Fill health bar
        if (healthPercent > 0) {
            draw->AddRectFilled(
                ImVec2(pos.x + 2, pos.y + 2),
                ImVec2(pos.x + 2 + (width - 4) * healthPercent, pos.y + height - 2),
                healthColor,
                (height-4)/4
            );
        }
        
        // Add health text if requested
        if (showText && Config::Visual::ShowHealthText) {
            char healthText[16];
            snprintf(healthText, sizeof(healthText), "%d%%", static_cast<int>(healthPercent * 100));
            
            float textHeight = height - 4;
            ImVec2 textSize = ImGui::CalcTextSize(healthText);
            float textX = pos.x + width/2 - textSize.x/2;
            float textY = pos.y + height/2 - textSize.y/2;
            
            draw->AddText(nullptr, textHeight, ImVec2(textX, textY), IM_COL32(255, 255, 255, 255), healthText);
        }
    }
    
    // Draw animated rectangle with advanced corner effect
    void DrawAnimatedRectangle(ImDrawList* draw, ImVec2 topLeft, ImVec2 bottomRight, ImU32 color, float thickness = 1.5f) {
        float time = ImGui::GetTime() * 2.0f; // Animation speed
        float cornerFraction = 0.25f; // Length of corners as fraction of smaller dimension
        
        float width = bottomRight.x - topLeft.x;
        float height = bottomRight.y - topLeft.y;
        float cornerSize = std::min(width, height) * cornerFraction;
        
        // Animation offset (goes from 0 to cornerSize)
        float offset = fmodf(time, 1.0f) * cornerSize;
        
        // Top-left corner
        draw->AddLine(
            ImVec2(topLeft.x, topLeft.y + offset),
            ImVec2(topLeft.x, topLeft.y),
            color, thickness
        );
        draw->AddLine(
            ImVec2(topLeft.x, topLeft.y),
            ImVec2(topLeft.x + offset, topLeft.y),
            color, thickness
        );
        
        // Top-right corner
        draw->AddLine(
            ImVec2(bottomRight.x - offset, topLeft.y),
            ImVec2(bottomRight.x, topLeft.y),
            color, thickness
        );
        draw->AddLine(
            ImVec2(bottomRight.x, topLeft.y),
            ImVec2(bottomRight.x, topLeft.y + offset),
            color, thickness
        );
        
        // Bottom-right corner
        draw->AddLine(
            ImVec2(bottomRight.x, bottomRight.y - offset),
            ImVec2(bottomRight.x, bottomRight.y),
            color, thickness
        );
        draw->AddLine(
            ImVec2(bottomRight.x, bottomRight.y),
            ImVec2(bottomRight.x - offset, bottomRight.y),
            color, thickness
        );
        
        // Bottom-left corner
        draw->AddLine(
            ImVec2(topLeft.x + offset, bottomRight.y),
            ImVec2(topLeft.x, bottomRight.y),
            color, thickness
        );
        draw->AddLine(
            ImVec2(topLeft.x, bottomRight.y),
            ImVec2(topLeft.x, bottomRight.y - offset),
            color, thickness
        );
    }
    
    // Draw skeleton with smooth transitions
    void DrawSkeleton(ImDrawList* draw, ASTExtraPlayerCharacter* player, ImU32 color, float thickness = 1.0f) {
        // Define bone connections to draw
        static std::vector<std::string> right_arm{
            "neck_01", "clavicle_r", "upperarm_r", "lowerarm_r", "hand_r"
        };
        
        static std::vector<std::string> left_arm{
            "neck_01", "clavicle_l", "upperarm_l", "lowerarm_l", "hand_l"
        };
        
        static std::vector<std::string> spine{
            "Head", "neck_01", "spine_03", "spine_02", "spine_01", "pelvis"
        };
        
        static std::vector<std::string> lower_right{
            "pelvis", "thigh_r", "calf_r", "foot_r"
        };
        
        static std::vector<std::string> lower_left{
            "pelvis", "thigh_l", "calf_l", "foot_l"
        };
        
        static std::vector<std::vector<std::string>> skeleton{
            right_arm, left_arm, spine, lower_right, lower_left
        };
        
        // Draw each bone connection
        for (auto& boneSet : skeleton) {
            std::string lastBone;
            for (std::string& bone : boneSet) {
                if (!lastBone.empty()) {
                    ImVec2 boneFrom, boneTo;
                    if (W2S(player->GetBonePos(lastBone.c_str(), {}), (FVector2D*)&boneFrom) &&
                        W2S(player->GetBonePos(bone.c_str(), {}), (FVector2D*)&boneTo)) {
                        
                        // Add slight pulsing effect to thickness
                        float pulseThickness = thickness;
                        if (Config::Visual::PulseEffect) {
                            float pulse = (sinf(ImGui::GetTime() * 3.0f) * 0.2f) + 0.8f;
                            pulseThickness *= pulse;
                        }
                        
                        draw->AddLine(boneFrom, boneTo, color, pulseThickness);
                    }
                }
                lastBone = bone;
            }
        }
    }
    
    // Draw target line with animated dashes
    void DrawTargetLine(ImDrawList* draw, ImVec2 start, ImVec2 end, ImU32 color, float thickness = 1.0f) {
        float time = ImGui::GetTime() * 2.0f; // Animation speed
        float totalLength = hypotf(end.x - start.x, end.y - start.y);
        int segments = std::max(5, static_cast<int>(totalLength / 30.0f)); // Adjust segments based on distance
        
        // Create direction vector
        float dirX = (end.x - start.x) / totalLength;
        float dirY = (end.y - start.y) / totalLength;
        
        // Calculate one segment length (dash + gap)
        float segmentLength = totalLength / segments;
        float dashLength = segmentLength * 0.6f; // 60% dash, 40% gap
        
        // Calculate animation offset
        float offset = fmodf(time * 50.0f, segmentLength);
        
        // Draw dashed line
        for (int i = 0; i < segments; i++) {
            float segStart = i * segmentLength - offset;
            float segEnd = segStart + dashLength;
            
            // Clamp to line length
            if (segStart < 0) segStart = 0;
            if (segEnd > totalLength) segEnd = totalLength;
            if (segStart >= totalLength || segEnd <= 0) continue;
            
            // Calculate points
            ImVec2 p1(start.x + dirX * segStart, start.y + dirY * segStart);
            ImVec2 p2(start.x + dirX * segEnd, start.y + dirY * segEnd);
            
            // Draw segment
            draw->AddLine(p1, p2, color, thickness);
        }
    }
    
    // Draw movement prediction line
    void DrawPredictionPath(ImDrawList* draw, ASTExtraPlayerCharacter* player, ImU32 color, float predictionTime = 2.0f) {
        if (!player || !Config::ESP::PredictionLine)
            return;
        
        // Get current position
        FVector currentPos = player->GetActorLocation();
        FVector velocity = player->GetVelocity();
        
        // Skip if not moving significantly
        if (UKismetMathLibrary::VSize(velocity) < 50.0f)
            return;
        
        // Use AI system to get a better prediction if available
        FVector predictedPos = g_AISystem.PredictPosition(player, predictionTime);
        
        // Draw prediction line
        ImVec2 startPos, endPos;
        if (W2S(currentPos, (FVector2D*)&startPos) && W2S(predictedPos, (FVector2D*)&endPos)) {
            // Get distance for scaling UI element
            float distance = 0.0f;
            if (g_LocalPlayer) {
                distance = player->GetDistanceTo(g_LocalPlayer) / 100.0f;
            }
            
            // Draw with fading effect
            const int steps = 10;
            for (int i = 0; i < steps; i++) {
                float t0 = static_cast<float>(i) / steps;
                float t1 = static_cast<float>(i + 1) / steps;
                
                ImVec2 p0 = ImVec2(
                    startPos.x + (endPos.x - startPos.x) * t0,
                    startPos.y + (endPos.y - startPos.y) * t0
                );
                
                ImVec2 p1 = ImVec2(
                    startPos.x + (endPos.x - startPos.x) * t1,
                    startPos.y + (endPos.y - startPos.y) * t1
                );
                
                // Fade opacity as we get further from current position
                ImVec4 colorVec = ImGui::ColorConvertU32ToFloat4(color);
                colorVec.w *= 1.0f - t0;
                ImU32 fadedColor = ImGui::ColorConvertFloat4ToU32(colorVec);
                
                draw->AddLine(p0, p1, fadedColor, 1.5f);
            }
            
            // Add arrow at the end
            float arrowSize = std::max(5.0f, 15.0f - (distance / 50.0f));
            float dx = endPos.x - startPos.x;
            float dy = endPos.y - startPos.y;
            float length = hypotf(dx, dy);
            
            if (length > 0.0001f) {
                dx /= length;
                dy /= length;
                
                ImVec2 normal(-dy, dx);
                
                ImVec2 arrowPoint1(
                    endPos.x - arrowSize * dx + arrowSize * 0.5f * normal.x,
                    endPos.y - arrowSize * dy + arrowSize * 0.5f * normal.y
                );
                
                ImVec2 arrowPoint2(
                    endPos.x - arrowSize * dx - arrowSize * 0.5f * normal.x,
                    endPos.y - arrowSize * dy - arrowSize * 0.5f * normal.y
                );
                
                draw->AddTriangleFilled(
                    endPos,
                    arrowPoint1,
                    arrowPoint2,
                    color
                );
            }
        }
    }
}

// ========================================================================================
// MAIN ESP & AIMBOT FUNCTIONS
// ========================================================================================

// Storage for closest aimbot target
struct {
    ASTExtraPlayerCharacter* target = nullptr;
    float lastUpdateTime = 0.0f;
    float fov = 0.0f;
    bool isVisible = false;
    float distance = 1000.0f;
    ImVec2 screenPos = {0, 0};
} g_AimbotData;

// Get the best target for aimbot based on configured priority
ASTExtraPlayerCharacter* GetBestTarget(ASTExtraPlayerCharacter* localPlayer, ASTExtraPlayerController* localController) {
    if (!localPlayer || !localController || !Config::Combat::AimbotEnabled)
        return nullptr;
    
    // Update at most 60 times per second for performance
    float currentTime = ImGui::GetTime();
    if (currentTime - g_AimbotData.lastUpdateTime < 1.0f/60.0f && g_AimbotData.target)
        return g_AimbotData.target;
    
    g_AimbotData.lastUpdateTime = currentTime;
    
    float closestFov = Config::Combat::AimbotFOV;
    float lowestHealth = FLT_MAX;
    float closestDistance = FLT_MAX;
    ASTExtraPlayerCharacter* bestTarget = nullptr;
    
    ImVec2 screenCenter = ImVec2(glWidth / 2.0f, glHeight / 2.0f);
    
    // Collect and filter targets first
    std::vector<ASTExtraPlayerCharacter*> validTargets;
    auto Actors = GetActors();
    
    for (auto& Actor : Actors) {
        if (isObjectInvalid(Actor))
            continue;
        
        if (!Actor->IsA(ASTExtraPlayerCharacter::StaticClass()))
            continue;
        
        auto player = static_cast<ASTExtraPlayerCharacter*>(Actor);
        
        // Skip invalid targets
        if (player == localPlayer || 
            player->PlayerKey == localController->PlayerKey ||
            player->TeamID == localController->TeamID ||
            player->bDead)
            continue;
        
        // Skip bots if configured
        if (Config::Combat::IgnoreBots && player->bEnsure)
            continue;
        
        // Skip knocked players if configured
        if (Config::Combat::IgnoreKnocked && player->bDBNO)
            continue;
        
        // Check visibility if configured
        bool isVisible = true;
        if (Config::Combat::VisibilityCheck) {
            isVisible = localController->LineOfSightTo(player, {0, 0, 0}, true);
            if (!isVisible)
                continue;
        }
        
        // Get distance
        float distance = localPlayer->GetDistanceTo(player) / 100.0f;
        
        // Calculate FOV to target
        ImVec2 screenPos;
        FVector targetPos = player->GetBonePos(Config::Combat::HeadOnly ? "Head" : "spine_01", {});
        
        if (W2S(targetPos, (FVector2D*)&screenPos)) {
            float dx = screenPos.x - screenCenter.x;
            float dy = screenPos.y - screenCenter.y;
            float fov = sqrtf(dx*dx + dy*dy);
            
            if (fov <= Config::Combat::AimbotFOV) {
                // Valid target, add to list
                validTargets.push_back(player);
                
                // Track closestFov for priority 0
                if (fov < closestFov) {
                    closestFov = fov;
                    g_AimbotData.fov = fov;
                    g_AimbotData.screenPos = screenPos;
                }
                
                // Track lowestHealth for priority 1
                if (player->Health < lowestHealth) {
                    lowestHealth = player->Health;
                }
                
                // Track closestDistance for priority 2
                if (distance < closestDistance) {
                    closestDistance = distance;
                    g_AimbotData.distance = distance;
                }
            }
        }
    }
    
    // Find best target based on priority
    if (!validTargets.empty()) {
        switch (Config::Combat::TargetPriority) {
            case 0: // Closest to crosshair
                for (auto target : validTargets) {
                    ImVec2 screenPos;
                    FVector targetPos = target->GetBonePos(Config::Combat::HeadOnly ? "Head" : "spine_01", {});
                    
                    if (W2S(targetPos, (FVector2D*)&screenPos)) {
                        float dx = screenPos.x - screenCenter.x;
                        float dy = screenPos.y - screenCenter.y;
                        float fov = sqrtf(dx*dx + dy*dy);
                        
                        if (fov <= closestFov) {
                            closestFov = fov;
                            bestTarget = target;
                            g_AimbotData.isVisible = localController->LineOfSightTo(target, {0, 0, 0}, true);
                        }
                    }
                }
                break;
                
            case 1: // Lowest health
                for (auto target : validTargets) {
                    if (target->Health <= lowestHealth) {
                        lowestHealth = target->Health;
                        bestTarget = target;
                        g_AimbotData.isVisible = localController->LineOfSightTo(target, {0, 0, 0}, true);
                    }
                }
                break;
                
            case 2: // Closest distance
                for (auto target : validTargets) {
                    float distance = localPlayer->GetDistanceTo(target) / 100.0f;
                    if (distance <= closestDistance) {
                        closestDistance = distance;
                        bestTarget = target;
                        g_AimbotData.isVisible = localController->LineOfSightTo(target, {0, 0, 0}, true);
                    }
                }
                break;
        }
    }
    
    g_AimbotData.target = bestTarget;
    return bestTarget;
}

// Process aimbot logic
void ProcessAimbot(ASTExtraPlayerCharacter* localPlayer, ASTExtraPlayerController* localController) {
    if (!localPlayer || !localController || !Config::Combat::AimbotEnabled)
        return;
    
    // Auto actions - scope in when needed
    if (Config::Combat::AutoScope && localPlayer->WeaponManagerComponent) {
        auto target = GetBestTarget(localPlayer, localController);
        if (target) {
            float distance = localPlayer->GetDistanceTo(target) / 100.0f;
            if (distance > 50.0f) {
                // Simulate scope button press
                localPlayer->bIsGunADS = true;
            }
        }
    }
    
    // Get target and bail if none found
    auto target = GetBestTarget(localPlayer, localController);
    if (!target)
        return;
    
    // Check trigger conditions
    bool shouldFire = false;
    
    if (Config::Combat::AutoFire) {
        // Only auto-fire if we have a good target in range
        float distance = localPlayer->GetDistanceTo(target) / 100.0f;
        bool canSeeTarget = localController->LineOfSightTo(target, {0, 0, 0}, true);
        
        shouldFire = canSeeTarget && distance < 200.0f;
        
        if (shouldFire) {
            localPlayer->bIsWeaponFiring = true;
        }
    }
    
    // Only aim when firing or when option is enabled
    if (!localPlayer->bIsWeaponFiring && !Config::Combat::AutoFire)
        return;
        
    // Get weapon manager
    auto weaponManager = localPlayer->WeaponManagerComponent;
    if (!weaponManager)
        return;
        
    // Get weapon info
    auto currentWeapon = reinterpret_cast<ASTExtraShootWeapon*>(weaponManager->CurrentWeaponReplicated);
    if (!currentWeapon || !currentWeapon->ShootWeaponComponent)
        return;
        
    auto weaponComp = currentWeapon->ShootWeaponComponent;
    auto weaponEntity = weaponComp->ShootWeaponEntityComponent;
    if (!weaponEntity)
        return;
    
    // Apply recoil removal if configured
    if (Config::Combat::NoRecoil) {
        weaponEntity->RecoilKickADS = 0.0f;
        weaponEntity->AnimationKick = 0.0f;
        weaponEntity->ShotGunCenterPerc = 0.0f;
        weaponEntity->ShotGunVerticalSpread = 0.0f;
        weaponEntity->ShotGunHorizontalSpread = 0.0f;
        weaponEntity->AccessoriesVRecoilFactor = 0.0f;
        weaponEntity->AccessoriesHRecoilFactor = 0.0f;
        weaponEntity->AccessoriesRecoveryFactor = 0.0f;
        weaponEntity->GameDeviationFactor = 0.0f;
    }
    
    // Calculate target position (head or body)
    FVector targetPos = target->GetBonePos(Config::Combat::HeadOnly ? "Head" : "spine_01", {});
    
    // Apply prediction if enabled
    if (Config::Combat::PredictiveAiming) {
        // Get bullet speed from weapon or use default
        float bulletSpeed = Config::Combat::BulletSpeed;
        if (weaponEntity->BulletFireSpeed > 0)
            bulletSpeed = weaponEntity->BulletFireSpeed;
            
        // Calculate time to target
        float distance = localPlayer->GetDistanceTo(target);
        float timeToTarget = distance / bulletSpeed;
        
        // Get target velocity
        FVector velocity = target->GetVelocity();
        
        // Handle vehicle case
        if (target->CurrentVehicle) {
            velocity = target->CurrentVehicle->ReplicatedMovement.LinearVelocity;
        }
        
        // Apply prediction
        targetPos += velocity * timeToTarget;
    }
    
    // Set up aim rotation
    FVector camLocation = localController->PlayerCameraManager->CameraCache.POV.Location;
    FRotator targetRot = ToRotator(camLocation, targetPos);
    
    // Smooth aiming if configured
    if (Config::Combat::AimbotSmoothing > 0.0f) {
        FRotator currentRot = localController->PlayerCameraManager->CameraCache.POV.Rotation;
        
        // Calculate delta and apply smoothing
        FRotator delta = targetRot - currentRot;
        
        // Normalize delta to -180 to 180 range
        if (delta.Pitch > 180.0f) delta.Pitch -= 360.0f;
        if (delta.Pitch < -180.0f) delta.Pitch += 360.0f;
        if (delta.Yaw > 180.0f) delta.Yaw -= 360.0f;
        if (delta.Yaw < -180.0f) delta.Yaw += 360.0f;
        
        // Apply smoothing factor
        delta.Pitch /= Config::Combat::AimbotSmoothing;
        delta.Yaw /= Config::Combat::AimbotSmoothing;
        
        // Calculate new rotation
        FRotator newRot = currentRot + delta;
        targetRot = newRot;
    }
    
    // Apply the rotation
    localController->SetControlRotation(targetRot, "");
}

// Main ESP drawing function
void DrawESP(ImDrawList* draw) {
    if (!Config::ESP::Enabled)
        return;
        
    // Find local player and controller
    ASTExtraPlayerCharacter* localPlayer = nullptr;
    ASTExtraPlayerController* localController = nullptr;
    
    auto Actors = GetActors();
    for (auto& Actor : Actors) {
        if (isObjectInvalid(Actor))
            continue;
            
        if (Actor->IsA(ASTExtraPlayerController::StaticClass())) {
            localController = static_cast<ASTExtraPlayerController*>(Actor);
            break;
        }
    }
    
    if (localController) {
        for (auto& Actor : Actors) {
            if (isObjectInvalid(Actor))
                continue;
                
            if (Actor->IsA(ASTExtraPlayerCharacter::StaticClass())) {
                auto player = static_cast<ASTExtraPlayerCharacter*>(Actor);
                if (player->PlayerKey == localController->PlayerKey) {
                    localPlayer = player;
                    break;
                }
            }
        }
    }
    
    // Bail if we couldn't find player
    if (!localPlayer || !localController)
        return;
    
    // Keep track of enemy counts
    int totalEnemies = 0;
    int totalBots = 0;
    
    // Process all actors for ESP rendering
    for (auto& Actor : Actors) {
        if (isObjectInvalid(Actor))
            continue;
            
        // Draw player ESP
        if (Actor->IsA(ASTExtraPlayerCharacter::StaticClass())) {
            auto player = static_cast<ASTExtraPlayerCharacter*>(Actor);
            
            // Skip self, teammates, dead players
            if (player == localPlayer || 
                player->PlayerKey == localController->PlayerKey ||
                player->TeamID == localController->TeamID ||
                player->bDead)
                continue;
                
            // Track enemy counts
            if (player->bEnsure) {
                totalBots++;
            } else {
                totalEnemies++;
            }
            
            // Skip bots if configured
            if (Config::ESP::NoBot && player->bEnsure)
                continue;
                
            // Calculate distance and apply distance filtering
            float distance = localPlayer->GetDistanceTo(player) / 100.0f;
            if (distance > Config::Game::RenderDistance)
                continue;
                
            // Check visibility
            bool isVisible = localController->LineOfSightTo(player, {0, 0, 0}, true);
            
            // Track this player with AI system
            g_AISystem.TrackPlayer(player, isVisible);
            
            // Get colors based on visibility and bot status
            ImU32 espColor;
            ImU32 textColor;
            
            if (player->bEnsure) {
                espColor = isVisible ? Config::Colors::Bot : Config::Colors::PulseColor(Config::Colors::Bot);
                textColor = Config::Colors::Bot;
            } else {
                espColor = isVisible ? Config::Colors::VisibleEnemy : Config::Colors::InvisibleEnemy;
                textColor = espColor;
                
                // Use AI-based threat color if enabled
                if (Config::AI::Enabled && Config::AI::AnalyzeThreatLevel) {
                    ImU32 threatColor = g_AISystem.GetThreatColor(player->PlayerKey);
                    if (!isVisible) {
                        threatColor = Config::Colors::PulseColor(threatColor);
                    }
                    espColor = threatColor;
                    textColor = threatColor;
                }
            }
            
            // Get bone positions for ESP drawing
            FVector headPos = player->GetBonePos("Head", {});
            FVector rootPos = player->GetBonePos("Root", {});
            
            ImVec2 headPosSC, rootPosSC;
            if (W2S(headPos, (FVector2D*)&headPosSC) && W2S(rootPos, (FVector2D*)&rootPosSC)) {
                // Calculate dynamic box size based on distance
                float boxHeight = abs(headPosSC.y - rootPosSC.y);
                float boxWidth = boxHeight * 0.65f;
                
                // Draw box if enabled
                if (Config::ESP::Box) {
                    ImVec2 topLeft = ImVec2(headPosSC.x - boxWidth / 2, headPosSC.y);
                    ImVec2 bottomRight = ImVec2(topLeft.x + boxWidth, topLeft.y + boxHeight);
                    
                    // Draw box with enhanced visual style
                    ESP::DrawAnimatedRectangle(draw, topLeft, bottomRight, espColor);
                }
                
                // Draw skeleton if enabled
                if (Config::ESP::Skeleton) {
                    ESP::DrawSkeleton(draw, player, espColor);
                }
                
                // Draw player line if enabled
                if (Config::ESP::Line) {
                    ImVec2 lineStart = ImVec2(glWidth / 2, 0);
                    ImVec2 lineEnd = ImVec2(headPosSC.x, headPosSC.y - 10.0f);
                    
                    ESP::DrawTargetLine(draw, lineStart, lineEnd, espColor, Config::ESP::LineThickness);
                }
                
                // Draw health bar if enabled
                if (Config::ESP::Health) {
                    float healthBarWidth = boxWidth + 5.0f;
                    float healthBarHeight = boxHeight * 0.04f;
                    float healthBarX = headPosSC.x - (healthBarWidth / 2);
                    float healthBarY = headPosSC.y - healthBarHeight * 2.5f;
                    
                    ESP::DrawHealthBar(
                        draw,
                        player->Health,
                        player->HealthMax,
                        ImVec2(healthBarX, healthBarY),
                        healthBarWidth,
                        healthBarHeight,
                        true
                    );
                }
                
                // Draw name and other info if enabled
                float textY = rootPosSC.y + 5.0f;
                float fontSize = 14.0f * (1.0f - std::min(distance / 400.0f, 0.5f)); // Scale down with distance
                
                std::string infoText;
                
                if (Config::ESP::Name) {
                    std::string name = player->PlayerName.ToString();
                    if (player->bEnsure) {
                        name = "Bot";
                    }
                    
                    if (Config::ESP::TeamID) {
                        infoText += "[" + std::to_string(player->TeamID) + "] ";
                    }
                    
                    infoText += name;
                }
                
                if (Config::ESP::Distance) {
                    if (!infoText.empty()) infoText += " | ";
                    infoText += std::to_string((int)distance) + "m";
                }
                
                // Draw weapon info if enabled
                std::string weaponText;
                if (Config::ESP::WeaponName && Config::Visual::ShowWeaponInfo) {
                    auto weaponManager = player->WeaponManagerComponent;
                    if (weaponManager && weaponManager->CurrentWeaponReplicated) {
                        auto weapon = reinterpret_cast<ASTExtraShootWeapon*>(weaponManager->CurrentWeaponReplicated);
                        if (weapon) {
                            weaponText = weapon->WeaponBase.WeaponId.ToString();
                        }
                    }
                }
                
                // Display player info with proper alignment and outline
                if (!infoText.empty()) {
                    ImVec2 textSize = ImGui::CalcTextSize(infoText.c_str());
                    float textX = headPosSC.x - (textSize.x / 2);
                    
                    ESP::DrawStrokeText(draw, fontSize, ImVec2(textX, textY), textColor, infoText.c_str());
                    textY += textSize.y + 2.0f;
                }
                
                // Display weapon info below the player info
                if (!weaponText.empty()) {
                    ImVec2 weaponTextSize = ImGui::CalcTextSize(weaponText.c_str());
                    float weaponTextX = headPosSC.x - (weaponTextSize.x / 2);
                    
                    ESP::DrawStrokeText(
                        draw,
                        fontSize * 0.85f,
                        ImVec2(weaponTextX, textY),
                        IM_COL32(200, 200, 255, 255),
                        weaponText.c_str()
                    );
                }
                
                // Draw movement prediction line from AI system
                if (Config::AI::Enabled && Config::AI::PredictMovement) {
                    ESP::DrawPredictionPath(draw, player, espColor, Config::ESP::PredictionTime);
                }
            }
        }
        
        // Draw vehicle ESP if needed
        else if (Actor->IsA(ASTExtraVehicleBase::StaticClass())) {
            auto vehicle = static_cast<ASTExtraVehicleBase*>(Actor);
            if (!vehicle->Mesh || !vehicle->VehicleCommon)
                continue;
            
            float distance = vehicle->GetDistanceTo(localPlayer) / 100.0f;
            if (distance > Config::Game::RenderDistance)
                continue;
            
            FVector2D screenPos;
            if (W2S(vehicle->K2_GetActorLocation(), &screenPos)) {
                // Draw vehicle name
                const char* vehicleName = GetVehicleName(vehicle);
                std::string infoText = std::string(vehicleName) + " [" + std::to_string((int)distance) + "m]";
                
                ESP::DrawStrokeText(
                    draw,
                    15.0f,
                    ImVec2(screenPos.X, screenPos.Y),
                    IM_COL32(120, 230, 255, 255),
                    infoText.c_str()
                );
                
                // Draw health and fuel bars if needed
                if (vehicle->VehicleCommon->HPMax > 0) {
                    float healthBarWidth = 60.0f;
                    float healthBarHeight = 6.0f;
                    float healthBarX = screenPos.X - (healthBarWidth / 2);
                    float healthBarY = screenPos.Y - 25.0f;
                    
                    ESP::DrawHealthBar(
                        draw,
                        vehicle->VehicleCommon->HP,
                        vehicle->VehicleCommon->HPMax,
                        ImVec2(healthBarX, healthBarY),
                        healthBarWidth,
                        healthBarHeight
                    );
                    
                    if (vehicle->VehicleCommon->FuelMax > 0) {
                        float fuelBarY = screenPos.Y - 15.0f;
                        
                        ESP::DrawHealthBar(
                            draw,
                            vehicle->VehicleCommon->Fuel,
                            vehicle->VehicleCommon->FuelMax,
                            ImVec2(healthBarX, fuelBarY),
                            healthBarWidth,
                            healthBarHeight
                        );
                    }
                }
            }
        }
    }
    
    // Run AI threat analysis
    g_AISystem.AnalyzeThreats(localPlayer, localController);
    
    // Draw threat alerts
    g_AISystem.RenderThreatAlerts(draw);
    
    // Draw action suggestions from AI
    if (Config::AI::Enabled && Config::AI::AutoSuggestActions) {
        std::string suggestion = g_AISystem.GetBestActionSuggestion(localPlayer, localController);
        if (!suggestion.empty()) {
            ImVec2 suggestionSize = ImGui::CalcTextSize(suggestion.c_str());
            float suggX = (glWidth - suggestionSize.x) * 0.5f;
            float suggY = glHeight * 0.15f;
            
            // Draw with pulsing effect
            float pulse = (sinf(ImGui::GetTime() * 2.0f) * 0.2f) + 0.8f;
            ImU32 suggestionColor = IM_COL32(255, 220, 0, static_cast<int>(255 * pulse));
            
            // Background for better readability
            ImVec2 padding(15, 8);
            draw->AddRectFilled(
                ImVec2(suggX - padding.x, suggY - padding.y),
                ImVec2(suggX + suggestionSize.x + padding.x, suggY + suggestionSize.y + padding.y),
                IM_COL32(0, 0, 0, 180),
                8.0f
            );
            
            // Border
            draw->AddRect(
                ImVec2(suggX - padding.x, suggY - padding.y),
                ImVec2(suggX + suggestionSize.x + padding.x, suggY + suggestionSize.y + padding.y),
                suggestionColor,
                8.0f,
                0,
                2.0f
            );
            
            // Text
            ESP::DrawStrokeText(draw, 18.0f, ImVec2(suggX, suggY), suggestionColor, suggestion.c_str());
        }
    }
    
    // Draw enemy counter
    if (Config::Visual::ShowEnemyCount && (totalEnemies + totalBots > 0)) {
        std::string counterText;
        if (totalBots > 0 && totalEnemies > 0) {
            counterText = "Players: " + std::to_string(totalEnemies) + " | Bots: " + std::to_string(totalBots);
        } else if (totalEnemies > 0) {
            counterText = "Players: " + std::to_string(totalEnemies);
        } else {
            counterText = "Bots: " + std::to_string(totalBots);
        }
        
        ImVec2 textSize = ImGui::CalcTextSize(counterText.c_str());
        float centerX = glWidth / 2.0f - textSize.x / 2.0f;
        
        // Color based on enemy count
        ImU32 countColor;
        if (totalEnemies > 2) {
            countColor = IM_COL32(255, 0, 0, 255); // Red for many enemies
        } else if (totalEnemies > 0) {
            countColor = IM_COL32(255, 165, 0, 255); // Orange for some enemies
        } else {
            countColor = IM_COL32(0, 255, 0, 255); // Green for bots only
        }
        
        // Draw with pulsating effect
        if (Config::Visual::PulseEffect) {
            float pulse = (sinf(ImGui::GetTime() * 4.0f) * 0.2f) + 0.8f;
            ImVec4 col = ImGui::ColorConvertU32ToFloat4(countColor);
            col.w *= pulse;
            countColor = ImGui::ColorConvertFloat4ToU32(col);
        }
        
        // Draw background
        draw->AddRectFilled(
            ImVec2(centerX - 10, 50 - 5),
            ImVec2(centerX + textSize.x + 10, 50 + textSize.y + 5),
            IM_COL32(0, 0, 0, 160),
            5.0f
        );
        
        ESP::DrawStrokeText(draw, 18.0f, ImVec2(centerX, 50), countColor, counterText.c_str());
    }
    
    // Draw FOV circle for aimbot
    if (Config::Combat::AimbotEnabled) {
        float pulse = (sinf(ImGui::GetTime() * 3.0f) * 0.2f) + 0.8f;
        ImU32 fovColor = IM_COL32(255, 255, 255, static_cast<int>(120 * pulse));
        
        draw->AddCircle(
            ImVec2(glWidth / 2, glHeight / 2),
            Config::Combat::AimbotFOV,
            fovColor,
            64,
            1.5f
        );
        
        // If we have a target, highlight it
        if (g_AimbotData.target && g_AimbotData.fov <= Config::Combat::AimbotFOV) {
            ImU32 targetColor = g_AimbotData.isVisible 
                ? IM_COL32(0, 255, 0, 255) 
                : IM_COL32(255, 0, 0, 255);
                
            // Draw indicator at target position
            FVector targetHeadPos = g_AimbotData.target->GetBonePos(Config::Combat::HeadOnly ? "Head" : "spine_01", {});
            ImVec2 targetScreen;
            if (W2S(targetHeadPos, (FVector2D*)&targetScreen)) {
                // Draw a pulsing diamond around the target
                const float size = 12.0f * pulse;
                
                draw->AddQuad(
                    ImVec2(targetScreen.x, targetScreen.y - size),
                    ImVec2(targetScreen.x + size, targetScreen.y),
                    ImVec2(targetScreen.x, targetScreen.y + size),
                    ImVec2(targetScreen.x - size, targetScreen.y),
                    targetColor,
                    2.0f
                );
            }
        }
    }
    
    // Process aimbot
    ProcessAimbot(localPlayer, localController);
}

// ========================================================================================
// UI COMPONENTS & SETTINGS INTERFACE
// ========================================================================================

namespace UI {
    // Main menu state
    bool showMenu = false;
    int currentTab = 0;
    const char* tabs[] = {"ESP", "Combat", "Visual", "AI", "Settings"};
    
    // For smooth animations
    float menuOpenProgress = 0.0f;
    
    // Custom toggle switch that looks modern
    bool ToggleSwitch(const char* label, bool* value) {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems)
            return false;
            
        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);
        
        const float height = ImGui::GetFrameHeight();
        const float width = height * 1.7f;
        const float radius = height * 0.5f;
        const ImVec2 pos = window->DC.CursorPos;
        
        const ImRect total_bb(pos, ImVec2(pos.x + width + style.ItemInnerSpacing.x + ImGui::CalcTextSize(label).x, pos.y + height));
        
        ImGui::ItemSize(total_bb, style.FramePadding.y);
        if (!ImGui::ItemAdd(total_bb, id))
            return false;
            
        bool hovered, held;
        bool pressed = ImGui::ButtonBehavior(ImRect(pos, ImVec2(pos.x + width, pos.y + height)), id, &hovered, &held);
        if (pressed) {
            *value = !(*value);
            ImGui::MarkItemEdited(id);
        }
        
        // Colors
        const ImU32 bg_color = ImGui::GetColorU32(*value ? ImVec4(0.2f, 0.6f, 1.0f, 1.0f) : ImVec4(0.3f, 0.3f, 0.3f, 1.0f));
        const ImU32 circle_color = ImGui::GetColorU32(*value ? ImVec4(1.0f, 1.0f, 1.0f, 1.0f) : ImVec4(0.8f, 0.8f, 0.8f, 1.0f));
        
        // Background track
        window->DrawList->AddRectFilled(pos, ImVec2(pos.x + width, pos.y + height), bg_color, height * 0.5f);
        
        // Circle knob - with animation
        static std::unordered_map<ImGuiID, float> animations;
        auto it = animations.find(id);
        if (it == animations.end())
            animations[id] = *value ? 1.0f : 0.0f;
        
        float& t = animations[id];
        if (*value && t < 1.0f) {
            t += ImGui::GetIO().DeltaTime * 4.0f;
            if (t > 1.0f) t = 1.0f;
        } else if (!*value && t > 0.0f) {
            t -= ImGui::GetIO().DeltaTime * 4.0f;
            if (t < 0.0f) t = 0.0f;
        }
        
        const float circle_x = pos.x + radius + t * (width - 2.0f * radius);
        window->DrawList->AddCircleFilled(ImVec2(circle_x, pos.y + radius), radius - 1.5f, circle_color);
        
        // Label
        ImGui::SameLine();
        ImGui::Text("%s", label);
        
        return pressed;
    }
    
    // A prettier slider with value display
    bool Slider(const char* label, float* v, float v_min, float v_max, const char* format = "%.1f") {
        ImGui::PushID(label);
        
        ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.15f, 0.15f, 0.15f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(0.18f, 0.18f, 0.18f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(0.3f, 0.6f, 1.0f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(0.4f, 0.7f, 1.0f, 1.0f));
        
        ImGui::Text("%s", label);
        ImGui::SameLine(ImGui::GetContentRegionAvail().x - 50); // Position for the value display
        ImGui::Text(format, *v);
        
        bool changed = ImGui::SliderFloat("##slider", v, v_min, v_max, "");
        
        ImGui::PopStyleColor(5);
        ImGui::PopID();
        return changed;
    }
    
    // A button with customizable colors and hover effects
    bool ColorButton(const char* label, ImVec4 color, ImVec2 size = ImVec2(0, 0)) {
        ImGui::PushStyleColor(ImGuiCol_Button, color);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(color.x + 0.1f, color.y + 0.1f, color.z + 0.1f, color.w));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(color.x - 0.1f, color.y - 0.1f, color.z - 0.1f, color.w));
        bool result = ImGui::Button(label, size);
        ImGui::PopStyleColor(3);
        return result;
    }
    
    // Section header with fancy line
    void SectionHeader(const char* label) {
        ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
        
        const float thickness = 2.0f;
        const ImU32 color = ImGui::GetColorU32(ImGuiCol_ButtonHovered);
        
        ImVec2 p = ImGui::GetCursorScreenPos();
        float width = ImGui::CalcTextSize(label).x;
        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        
        float availWidth = ImGui::GetContentRegionAvail().x;
        float lineWidth = (availWidth - width - 20.0f) / 2.0f;
        
        ImGui::Spacing();
        
        // Draw left line
        if (lineWidth > 0) {
            draw_list->AddLine(
                ImVec2(p.x, p.y + ImGui::GetTextLineHeight() / 2),
                ImVec2(p.x + lineWidth, p.y + ImGui::GetTextLineHeight() / 2),
                color, thickness
            );
        }
        
        // Draw text
        ImGui::SameLine(lineWidth + 10);
        ImGui::TextColored(ImVec4(0.8f, 0.8f, 1.0f, 1.0f), "%s", label);
        
        // Draw right line
        ImGui::SameLine();
        p.x = ImGui::GetCursorScreenPos().x;
        if (lineWidth > 0) {
            draw_list->AddLine(
                ImVec2(p.x, p.y + ImGui::GetTextLineHeight() / 2),
                ImVec2(p.x + lineWidth, p.y + ImGui::GetTextLineHeight() / 2),
                color, thickness
            );
        }
        
        ImGui::PopFont();
        ImGui::Spacing();
    }
    
    // Draw a tab button
    bool TabButton(const char* label, bool selected) {
        ImVec2 size = ImVec2(ImGui::GetContentRegionAvail().x / 5 - 4, 0);
        
        if (selected) {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.4f, 0.8f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.5f, 0.9f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.4f, 0.8f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
        } else {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.15f, 0.15f, 0.15f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.25f, 0.25f, 0.25f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.7f, 0.7f, 0.7f, 1.0f));
        }
        
        bool clicked = ImGui::Button(label, size);
        ImGui::PopStyleColor(4);
        
        return clicked;
    }
    
    // Draw ESP settings tab
    void DrawESPTab() {
        SectionHeader("ESP Visualization");
        
        ImGui::Columns(2, nullptr, false);
        
        ToggleSwitch("ESP Enabled", &Config::ESP::Enabled);
        ToggleSwitch("Box ESP", &Config::ESP::Box);
        ToggleSwitch("Skeleton", &Config::ESP::Skeleton);
        ToggleSwitch("Health Bar", &Config::ESP::Health);
        ToggleSwitch("Name Display", &Config::ESP::Name);
        
        ImGui::NextColumn();
        
        ToggleSwitch("Distance", &Config::ESP::Distance);
        ToggleSwitch("Team ID", &Config::ESP::TeamID);
        ToggleSwitch("Weapon Info", &Config::ESP::WeaponName);
        ToggleSwitch("Hide Bots", &Config::ESP::NoBot);
        ToggleSwitch("Line to Enemy", &Config::ESP::Line);
        
        ImGui::Columns(1);
        
        ImGui::Spacing();
        
        Slider("Line Thickness", &Config::ESP::LineThickness, 0.5f, 3.0f, "%.1f");
        Slider("Render Distance", &Config::Game::RenderDistance, 100.0f, 1000.0f, "%.0f m");
        Slider("Prediction Time", &Config::ESP::PredictionTime, 0.5f, 5.0f, "%.1f s");
        
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();
        
        SectionHeader("Movement Prediction");
        
        ToggleSwitch("Show Movement Paths", &Config::ESP::PredictionLine);
        
        ImGui::Spacing();
    }
    
    // Draw Combat settings tab
    void DrawCombatTab() {
        SectionHeader("Aimbot Settings");
        
        ImGui::Columns(2, nullptr, false);
        
        ToggleSwitch("Enable Aimbot", &Config::Combat::AimbotEnabled);
        ToggleSwitch("Headshot Only", &Config::Combat::HeadOnly);
        ToggleSwitch("Visibility Check", &Config::Combat::VisibilityCheck);
        ToggleSwitch("Ignore Knocked", &Config::Combat::IgnoreKnocked);
        ToggleSwitch("Ignore Bots", &Config::Combat::IgnoreBots);
        
        ImGui::NextColumn();
        
        ToggleSwitch("Predictive Aiming", &Config::Combat::PredictiveAiming);
        ToggleSwitch("Auto-Scope", &Config::Combat::AutoScope);
        ToggleSwitch("Auto-Fire", &Config::Combat::AutoFire);
        ToggleSwitch("No Recoil", &Config::Combat::NoRecoil);
        ToggleSwitch("Instant Hit", &Config::Combat::InstantHit);
        
        ImGui::Columns(1);
        
        ImGui::Spacing();
        
        Slider("FOV Radius", &Config::Combat::AimbotFOV, 50.0f, 1000.0f, "%.0f");
        Slider("Smoothing", &Config::Combat::AimbotSmoothing, 1.0f, 20.0f, "%.1f");
        Slider("Bullet Speed", &Config::Combat::BulletSpeed, 500.0f, 2000.0f, "%.0f");
        
        ImGui::Spacing();
        
        ImGui::Text("Target Priority:");
        const char* priorities[] = {
            "Closest to Crosshair", 
            "Lowest Health", 
            "Closest Distance"
        };
        ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
        ImGui::Combo("##target_priority", &Config::Combat::TargetPriority, priorities, IM_ARRAYSIZE(priorities));
        
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();
        
        SectionHeader("Magic Bullet");
        
        ToggleSwitch("Enable Magic Bullet", &Config::Combat::MagicBullet);
        if (Config::Combat::MagicBullet) {
            ImGui::TextColored(ImVec4(1.0f, 0.6f, 0.0f, 1.0f), "Warning: Use with caution, may cause detection");
        }
        
        ImGui::Spacing();
    }
    
    // Draw Visual settings tab
    void DrawVisualTab() {
        SectionHeader("View Settings");
        
        ImGui::Columns(2, nullptr, false);
        
        ToggleSwitch("Wide View", &Config::Visual::WideView);
        ToggleSwitch("Show FPS", &Config::Visual::ShowFPS);
        ToggleSwitch("Small Crosshair", &Config::Visual::SmallCrosshair);
        ToggleSwitch("Show Enemy Count", &Config::Visual::ShowEnemyCount);
        
        ImGui::NextColumn();
        
        ToggleSwitch("Pulse Effects", &Config::Visual::PulseEffect);
        ToggleSwitch("Show Health Text", &Config::Visual::ShowHealthText);
        ToggleSwitch("Show Weapon Info", &Config::Visual::ShowWeaponInfo);
        
        ImGui::Columns(1);
        
        ImGui::Spacing();
        
        Slider("Field of View", &Config::Visual::FOV, 60.0f, 150.0f, "%.0f");
        
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();
        
        SectionHeader("Color Settings");
        
        // Color picking demo
        ImGui::Text("Color Theme:");
        static int colorTheme = 0;
        const char* themes[] = {
            "Default", "High Contrast", "Stealth", "Colorful"
        };
        ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
        if (ImGui::Combo("##color_theme", &colorTheme, themes, IM_ARRAYSIZE(themes))) {
            switch (colorTheme) {
                case 0: // Default
                    Config::Colors::VisibleEnemy = IM_COL32(0, 255, 0, 255);
                    Config::Colors::InvisibleEnemy = IM_COL32(255, 0, 0, 255);
                    Config::Colors::Bot = IM_COL32(255, 255, 0, 255);
                    break;
                case 1: // High Contrast
                    Config::Colors::VisibleEnemy = IM_COL32(0, 255, 255, 255);
                    Config::Colors::InvisibleEnemy = IM_COL32(255, 0, 255, 255);
                    Config::Colors::Bot = IM_COL32(255, 255, 255, 255);
                    break;
                case 2: // Stealth
                    Config::Colors::VisibleEnemy = IM_COL32(150, 150, 255, 180);
                    Config::Colors::InvisibleEnemy = IM_COL32(255, 150, 150, 180);
                    Config::Colors::Bot = IM_COL32(150, 255, 150, 180);
                    break;
                case 3: // Colorful
                    Config::Colors::VisibleEnemy = IM_COL32(0, 255, 128, 255);
                    Config::Colors::InvisibleEnemy = IM_COL32(255, 0, 128, 255);
                    Config::Colors::Bot = IM_COL32(255, 128, 0, 255);
                    break;
            }
        }
        
        ImGui::Spacing();
    }
    
    // Draw AI settings tab
    void DrawAITab() {
        SectionHeader("AI Features");
        
        ImGui::Columns(2, nullptr, false);
        
        ToggleSwitch("Enable AI System", &Config::AI::Enabled);
        ToggleSwitch("Movement Prediction", &Config::AI::PredictMovement);
        ToggleSwitch("Threat Analysis", &Config::AI::AnalyzeThreatLevel);
        ToggleSwitch("Action Suggestions", &Config::AI::AutoSuggestActions);
        
        ImGui::NextColumn();
        
        ToggleSwitch("Alert Mode", &Config::AI::AlertMode);
        ToggleSwitch("Adaptive Targeting", &Config::AI::AutoAdaptTargeting);
        ToggleSwitch("Track Enemy Patterns", &Config::AI::TrackEnemyPatterns);
        
        ImGui::Columns(1);
        
        ImGui::Spacing();
        
        Slider("Alert Threshold", (float*)&Config::AI::AlertThreshold, 0.0f, 100.0f, "%d%%");
        Slider("Memory Length", (float*)&Config::AI::MemoryLength, 10.0f, 200.0f, "%.0f frames");
        Slider("Alert Duration", &Config::AI::ThreatDisplayTime, 1.0f, 10.0f, "%.1f s");
        
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();
        
        SectionHeader("AI Information");
        
        ImGui::TextWrapped(
            "The AI system tracks and analyzes enemy movement patterns, weapon usage, "
            "and behavior to provide tactical advantages. It helps detect threats "
            "and predict enemy actions before they occur."
        );
        
        ImGui::Spacing();
        
        if (!Config::AI::Enabled) {
            ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.0f, 1.0f), 
                "Enable AI for advanced threat detection and predictive targeting."
            );
        }
        
        ImGui::Spacing();
    }
    
    // Draw Settings tab
    void DrawSettingsTab() {
        SectionHeader("Memory Settings");
        
        ImGui::Columns(2, nullptr, false);
        
        ToggleSwitch("Auto Memory Cleaning", &Config::Memory::AutoClean);
        ToggleSwitch("Anti-Report", &Config::Memory::AntiReport);
        
        ImGui::NextColumn();
        
        ToggleSwitch("Safe Mode", &Config::Memory::SafeMode);
        ToggleSwitch("Memory Pooling", &Config::Memory::MemoryPooling);
        
        ImGui::Columns(1);
        
        ImGui::Spacing();
        
        Slider("Memory Pool Size", (float*)&Config::Memory::PoolSize, 16.0f, 256.0f, "%d MB");
        
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();
        
        SectionHeader("Game Options");
        
        ToggleSwitch("Auto-Detect Version", &Config::Game::AutoDetectVersion);
        Slider("Max Players", (float*)&Config::Game::MaxPlayers, 20.0f, 100.0f, "%d players");
        
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();
        
        // Safety buttons
        if (UI::ColorButton("Clear Game Cache", ImVec4(0.9f, 0.5f, 0.1f, 1.0f), ImVec2(ImGui::GetContentRegionAvail().x * 0.48f, 0))) {
            system("rm -rf /storage/emulated/0/Android/data/com.pubg.imobile/cache*");
            system("rm -rf /storage/emulated/0/Android/data/com.pubg.imobile/files/UE4Game/ShadowTrackerExtra/ShadowTrackerExtra/Saved/Logs*");
        }
        
        ImGui::SameLine();
        
        if (UI::ColorButton("Remove Reports", ImVec4(0.9f, 0.2f, 0.2f, 1.0f), ImVec2(-1, 0))) {
            system("rm -rf /data/data/com.pubg.imobile/shared_prefs");
            system("rm -rf /data/data/com.pubg.imobile/databases");
            system("rm -rf /data/data/com.pubg.imobile/cache");
            system("rm -rf /data/data/com.pubg.imobile/app_crashKit");
        }
        
        ImGui::Spacing();
    }
    
    // Draw the main settings window
    void DrawSettingsWindow() {
        // Handle menu animation
        float targetProgress = showMenu ? 1.0f : 0.0f;
        menuOpenProgress += (targetProgress - menuOpenProgress) * ImGui::GetIO().DeltaTime * 10.0f;
        menuOpenProgress = std::min(1.0f, std::max(0.0f, menuOpenProgress));
        
        if (menuOpenProgress <= 0.01f && !showMenu)
            return;
            
        // Apply animation with slide-in effect
        ImVec2 windowSize = ImVec2(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.7f);
        float xPos = (ImGui::GetIO().DisplaySize.x - windowSize.x) * 0.5f;
        float yPos = ImGui::GetIO().DisplaySize.y - windowSize.y * menuOpenProgress;
        
        ImGui::SetNextWindowPos(ImVec2(xPos, yPos));
        ImGui::SetNextWindowSize(windowSize);
        
        // Window styling
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 10.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(15, 15));
        
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.06f, 0.06f, 0.08f, 0.97f));
        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.08f, 0.08f, 0.1f, 0.9f));
        
        static char windowTitle[64];
        snprintf(windowTitle, sizeof(windowTitle), "Enhanced ESP & Aimbot v2.0 • %.1f FPS###MainWindow", ImGui::GetIO().Framerate);
        
        // Main window
        if (ImGui::Begin(windowTitle, nullptr, 
            ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar)) {
            
            // Top tabs bar
            for (int i = 0; i < IM_ARRAYSIZE(tabs); i++) {
                if (i > 0) ImGui::SameLine();
                if (TabButton(tabs[i], currentTab == i)) {
                    currentTab = i;
                }
            }
            
            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Spacing();
            
            // Tab content
            switch (currentTab) {
                case 0: DrawESPTab(); break;
                case 1: DrawCombatTab(); break;
                case 2: DrawVisualTab(); break;
                case 3: DrawAITab(); break;
                case 4: DrawSettingsTab(); break;
            }
        }
        ImGui::End();
        
        ImGui::PopStyleColor(2);
        ImGui::PopStyleVar(3);
    }
}

// ========================================================================================
// MAIN RENDERING & ENTRY POINTS
// ========================================================================================

// Mouse and touch input handling
int32_t onInputEvent(struct android_app* app, AInputEvent* event) {
    if (orig_onInputEvent && ImGui_ImplAndroid_HandleInputEvent(event)) {
        return 1;
    }
    
    // Handle menu toggle with 3-finger tap
    if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {
        int32_t action = AMotionEvent_getAction(event) & AMOTION_EVENT_ACTION_MASK;
        int32_t pointerCount = AMotionEvent_getPointerCount(event);
        
        if (action == AMOTION_EVENT_ACTION_DOWN && pointerCount >= 3) {
            UI::showMenu = !UI::showMenu;
            return 1;
        }
    }
    
    return orig_onInputEvent(app, event);
}

// Hook for ProcessEvent
void hkProcessEvent(UObject* object, UFunction* function, void* parms) {
    // Forward to original function
    oProcessEvent(object, function, parms);
}

// Main drawing function - called for each frame via EGL swap buffer hook
EGLBoolean _eglSwapBuffers(EGLDisplay dpy, EGLSurface surface) {
    eglQuerySurface(dpy, surface, EGL_WIDTH, &glWidth);
    eglQuerySurface(dpy, surface, EGL_HEIGHT, &glHeight);
    
    if (glWidth <= 0 || glHeight <= 0 || !g_App)
        return orig_eglSwapBuffers(dpy, surface);
    
    // Get device information
    screenWidth = ANativeWindow_getWidth(g_App->window);
    screenHeight = ANativeWindow_getHeight(g_App->window);
    density = AConfiguration_getDensity(g_App->config);
    
    // Initialize ImGui on first run
    if (!initImGui) {
        ImGui::CreateContext();
        
        // Configure ImGui style
        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowRounding = 10.0f;
        style.ChildRounding = 8.0f;
        style.FrameRounding = 6.0f;
        style.PopupRounding = 6.0f;
        style.ScrollbarRounding = 6.0f;
        style.GrabRounding = 6.0f;
        style.TabRounding = 6.0f;
        
        style.WindowBorderSize = 0.0f;
        style.FrameBorderSize = 0.0f;
        
        style.ItemSpacing = ImVec2(8, 8);
        style.ItemInnerSpacing = ImVec2(6, 6);
        style.FramePadding = ImVec2(8, 4);
        style.WindowPadding = ImVec2(15, 15);
        
        style.ScrollbarSize = 12.0f;
        
        ImVec4* colors = style.Colors;
        colors[ImGuiCol_WindowBg]               = ImVec4(0.08f, 0.08f, 0.10f, 0.95f);
        colors[ImGuiCol_Border]                 = ImVec4(0.10f, 0.10f, 0.12f, 0.50f);
        colors[ImGuiCol_FrameBg]                = ImVec4(0.13f, 0.13f, 0.15f, 1.00f);
        colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.15f, 0.15f, 0.17f, 1.00f);
        colors[ImGuiCol_FrameBgActive]          = ImVec4(0.17f, 0.17f, 0.19f, 1.00f);
        colors[ImGuiCol_TitleBg]                = ImVec4(0.09f, 0.09f, 0.11f, 1.00f);
        colors[ImGuiCol_TitleBgActive]          = ImVec4(0.11f, 0.11f, 0.13f, 1.00f);
        colors[ImGuiCol_Button]                 = ImVec4(0.20f, 0.41f, 0.68f, 0.50f);
        colors[ImGuiCol_ButtonHovered]          = ImVec4(0.24f, 0.45f, 0.72f, 1.00f);
        colors[ImGuiCol_ButtonActive]           = ImVec4(0.26f, 0.49f, 0.78f, 1.00f);
        colors[ImGuiCol_Header]                 = ImVec4(0.20f, 0.41f, 0.68f, 0.45f);
        colors[ImGuiCol_HeaderHovered]          = ImVec4(0.24f, 0.45f, 0.72f, 0.80f);
        colors[ImGuiCol_HeaderActive]           = ImVec4(0.26f, 0.49f, 0.78f, 1.00f);
        colors[ImGuiCol_Tab]                    = ImVec4(0.15f, 0.30f, 0.57f, 0.80f);
        colors[ImGuiCol_TabHovered]             = ImVec4(0.24f, 0.45f, 0.72f, 0.80f);
        colors[ImGuiCol_TabActive]              = ImVec4(0.26f, 0.49f, 0.78f, 1.00f);
        
        // Initialize ImGui backends
        ImGui_ImplAndroid_Init();
        ImGui_ImplOpenGL3_Init("#version 300 es");
        
        // Load fonts
        ImGuiIO& io = ImGui::GetIO();
        
        // Main font with proper scaling based on density
        ImFontConfig config;
        config.SizePixels = (density / 10.0f);
        io.Fonts->AddFontDefault(&config);
        
        // Second font for headers - slightly larger
        ImFontConfig headerConfig;
        headerConfig.SizePixels = (density / 8.0f);
        io.Fonts->AddFontDefault(&headerConfig);
        
        initImGui = true;
    }
    
    // Start new ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame(glWidth, glHeight);
    ImGui::NewFrame();
    
    // Draw ESP
    DrawESP(ImGui::GetBackgroundDrawList());
    
    // Draw settings window if menu is open
    UI::DrawSettingsWindow();
    
    // Render ImGui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    
    // Forward to original function
    return orig_eglSwapBuffers(dpy, surface);
}

// Apply memory cleaning - remove reporting logs and files
void FixGameCrash() {
    if (Config::Memory::AntiReport) {
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
}

// Main initialization thread
void *main_thread(void *) {
    FixGameCrash();
    
    // Load the UE4 library
    Cheat::libUE4Base = Tools::GetBaseAddress("libUE4.so");
    while (!Cheat::libUE4Base) {
        Cheat::libUE4Base = Tools::GetBaseAddress("libUE4.so");
        sleep(1);
    }
    
    // Wait for Android app
    while (!g_App) {
        g_App = *(android_app**)(Cheat::libUE4Base + Cheat::GNativeAndroidApp_Offset);
        sleep(1);
    }
    
    // Initialize Unreal Engine core systems
    FName::GNames = GetGNames();
    while (!FName::GNames) {
        FName::GNames = GetGNames();
        sleep(1);
    }
    
    UObject::GUObjectArray = (FUObjectArray*)(Cheat::libUE4Base + Cheat::GUObject_Offset);
    
    // Install hooks
    orig_onInputEvent = decltype(orig_onInputEvent)(g_App->onInputEvent);
    g_App->onInputEvent = onInputEvent;
    
    initOffset();
    
    // Hook EGL swap buffers
    Tools::Hook(
        (void*)DobbySymbolResolver("/system/lib/libEGL.so", "eglSwapBuffers"),
        (void*)_eglSwapBuffers,
        (void**)&orig_eglSwapBuffers
    );
    
    // Hook ProcessEvent
    Tools::Hook(
        (void*)(Cheat::libUE4Base + Cheat::ProcessEvent_Offset),
        (void*)hkProcessEvent,
        (void**)&oProcessEvent
    );
    
    return nullptr;
}

// Wide view thread for FOV adjustments
void *wideview_thread(void*) {
    while (true) {
        // Skip execution until UE4 is loaded
        if (!Cheat::libUE4Base) {
            sleep(1);
            continue;
        }
        
        if (Config::Visual::WideView) {
            auto objs = UObject::GetGlobalObjects();
            for (int i = 0; i < objs.Num(); i++) {
                auto Object = objs.GetByIndex(i);
                if (isObjectInvalid(Object))
                    continue;
                
                if (Object->IsA(ULocalPlayer::StaticClass())) {
                    auto playerChar = (ULocalPlayer*)Object;
                    playerChar->AspectRatioAxisConstraint = EAspectRatioAxisConstraint::AspectRatio_MaintainYFOV;
                    
                    // Apply FOV
                    if (g_LocalPlayer && g_LocalPlayer->ThirdPersonCameraComponent) {
                        g_LocalPlayer->ThirdPersonCameraComponent->SetFieldOfView(Config::Visual::FOV);
                    }
                }
            }
        }
        
        // Sleep for a short time to reduce CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

// Anti-cheat bypass thread - various hooks for anti-report
void *bypass_thread(void*) {
    while (!Cheat::libUE4Base) {
        sleep(1);
    }
    
    // Load libanogs.so handles
    void* libanogsHandle = dlopen("libanogs.so", RTLD_LAZY);
    if (libanogsHandle) {
        // Various anti-cheat bypasses
        void* checkBanFlagFunc = dlsym(libanogsHandle, "_ZN12GameSecurity12CheckBanFlagEv");
        if (checkBanFlagFunc) {
            Tools::Hook(checkBanFlagFunc, (void*)([]() -> bool { return false; }), nullptr);
        }
        
        void* triggerBanFunc = dlsym(libanogsHandle, "_ZN10PlayerData10TriggerBanEv");
        if (triggerBanFunc) {
            Tools::Hook(triggerBanFunc, (void*)([]() -> void* { return nullptr; }), nullptr);
        }
    }
    
    // UE4 security module bypass
    void* securityModuleFunc = dlsym(RTLD_DEFAULT, "_ZN14SecurityModule15IsFlaggedPlayerEv");
    if (securityModuleFunc) {
        Tools::Hook(securityModuleFunc, (void*)([]() -> void* { return (void*)1; }), nullptr);
    }
    
    return nullptr;
}

// Entry point - called when the library is loaded
__attribute__((constructor)) void _init() {
    // Create threads
    pthread_create(&t, NULL, main_thread, NULL);
    pthread_create(&t2, NULL, wideview_thread, NULL);
    pthread_create(&t3, NULL, bypass_thread, NULL);
}
