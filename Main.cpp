// ========================================================================================
// IBR - Professional Gaming Enhancement Suite
// Modern C++ ImGui-based Interface for Android
// Version: 4.2.1 (2025-04-27)
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
#include <pthread.h>
#include <jni.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <android/log.h>
#include <dlfcn.h>
#include <stdint.h>

#include "Includes/include.h"
#include "Includes/definition.h"

// Add necessary forward declarations
template<typename T>
static inline T ImLerp(T a, T b, float t) {
    return (T)(a + (b - a) * t);
}

// Function prototypes
void RenderAimButton(ImDrawList* draw);
void RenderBulletTrackButton(ImDrawList* draw);
void RenderLoginScreen();

// Change this:

// Declare missing variables
bool isLogin = false; // Global login state
ImU32 uniqueColor = IM_COL32(255, 0, 0, 255); // Default unique color

// ========================================================================================
// THEME CONFIGURATION & ANIMATION CONSTANTS
// ========================================================================================

namespace Theme {
    // Color palette
    namespace Colors {
        constexpr ImU32 Primary        = IM_COL32(25, 118, 210, 255);    // Blue
        constexpr ImU32 Secondary      = IM_COL32(76, 175, 80, 255);     // Green
        constexpr ImU32 Accent         = IM_COL32(255, 152, 0, 255);     // Orange
        constexpr ImU32 Danger         = IM_COL32(244, 67, 54, 255);     // Red
        constexpr ImU32 Warning        = IM_COL32(255, 193, 7, 255);     // Amber
        constexpr ImU32 Success        = IM_COL32(76, 175, 80, 255);     // Green
        constexpr ImU32 Info           = IM_COL32(3, 169, 244, 255);     // Light Blue
        constexpr ImU32 BackgroundDark = IM_COL32(18, 18, 18, 200);      // Dark background
        constexpr ImU32 BackgroundMid  = IM_COL32(30, 30, 30, 220);      // Mid background
        constexpr ImU32 TextPrimary    = IM_COL32(255, 255, 255, 255);   // White
        constexpr ImU32 TextSecondary  = IM_COL32(180, 180, 180, 255);   // Light gray
        
        // ESP Colors
        constexpr ImU32 VisibleEnemy   = IM_COL32(0, 255, 0, 255);       // Green
        constexpr ImU32 HiddenEnemy    = IM_COL32(255, 0, 0, 255);       // Red
        constexpr ImU32 Bot            = IM_COL32(255, 230, 90, 255);    // Yellow
        constexpr ImU32 TeamIndicator  = IM_COL32(0, 180, 255, 255);     // Cyan
    }

    // Animation values
    namespace Animation {
        constexpr float PulseSpeed = 2.0f;       // Speed for pulsing effects
        constexpr float RgbSpeed = 0.4f;         // Speed for RGB cycling
        constexpr float ButtonHoverSpeed = 0.2f; // Speed for hover effects
        constexpr float ToastDuration = 3.0f;    // Duration for toast notifications
    }
    
    // UI Element Dimensions
    namespace Dimensions {
        constexpr float ButtonHeight = 40.0f;
        constexpr float SliderHeight = 20.0f;
        constexpr float CheckboxSize = 18.0f;
        constexpr float BorderRadius = 10.0f;
        constexpr float WindowPadding = 10.0f;
    }
    
    // UI Fonts - will be initialized in SetupStyle
    namespace Fonts {
        ImFont* Title = nullptr;
        ImFont* Header = nullptr;
        ImFont* Normal = nullptr;
        ImFont* Small = nullptr;
    }
    
    // Apply the application theme to ImGui
    void SetupStyle(float density) {
        ImGuiStyle& style = ImGui::GetStyle();
        
        // Rounding and sizes
        style.WindowRounding = 12.0f;
        style.ChildRounding = 8.0f;
        style.FrameRounding = 6.0f;
        style.PopupRounding = 10.0f;
        style.ScrollbarRounding = 10.0f;
        style.GrabRounding = 6.0f;
        style.TabRounding = 8.0f;
        
        // Borders and spacing
        style.WindowBorderSize = 0.0f;
        style.ChildBorderSize = 1.0f;
        style.PopupBorderSize = 1.0f;
        style.FrameBorderSize = 0.0f;
        style.TabBorderSize = 0.0f;
        
        // Spacing 
        style.ItemSpacing = ImVec2(8, 8);
        style.ItemInnerSpacing = ImVec2(6, 6);
        style.WindowPadding = ImVec2(Dimensions::WindowPadding, Dimensions::WindowPadding);
        style.FramePadding = ImVec2(8, 4);
        
        // Alignment
        style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
        style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
        
        // Sizing
        style.ScrollbarSize = 16.0f * (density / 440.0f);
        style.GrabMinSize = 10.0f * (density / 440.0f);
        
        // Colors - Modern dark theme with accents
        ImVec4* colors = style.Colors;
        colors[ImGuiCol_WindowBg]               = ImVec4(0.10f, 0.10f, 0.12f, 0.94f);
        colors[ImGuiCol_Border]                 = ImVec4(0.08f, 0.08f, 0.09f, 0.00f);
        colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_FrameBg]                = ImVec4(0.15f, 0.15f, 0.16f, 1.00f);
        colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.19f, 0.19f, 0.21f, 1.00f);
        colors[ImGuiCol_FrameBgActive]          = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
        colors[ImGuiCol_TitleBg]                = ImVec4(0.09f, 0.09f, 0.11f, 1.00f);
        colors[ImGuiCol_TitleBgActive]          = ImVec4(0.12f, 0.12f, 0.14f, 1.00f);
        colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.09f, 0.09f, 0.11f, 0.75f);
        colors[ImGuiCol_MenuBarBg]              = ImVec4(0.15f, 0.15f, 0.16f, 1.00f);
        colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.15f, 0.15f, 0.16f, 0.80f);
        colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.30f, 0.30f, 0.33f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.40f, 0.40f, 0.44f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.66f, 0.66f, 0.73f, 1.00f);
        colors[ImGuiCol_CheckMark]              = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        colors[ImGuiCol_SliderGrab]             = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
        colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.46f, 0.71f, 1.00f, 1.00f);
        colors[ImGuiCol_Button]                 = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
        colors[ImGuiCol_ButtonHovered]          = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        colors[ImGuiCol_ButtonActive]           = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
        colors[ImGuiCol_Header]                 = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
        colors[ImGuiCol_HeaderHovered]          = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
        colors[ImGuiCol_HeaderActive]           = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        colors[ImGuiCol_Separator]              = ImVec4(0.20f, 0.20f, 0.22f, 1.00f);
        colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
        colors[ImGuiCol_SeparatorActive]        = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        colors[ImGuiCol_Tab]                    = ImVec4(0.20f, 0.20f, 0.22f, 0.90f);
        colors[ImGuiCol_TabHovered]             = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
        colors[ImGuiCol_TabActive]              = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        colors[ImGuiCol_TabUnfocused]           = ImVec4(0.15f, 0.15f, 0.16f, 1.00f);
        colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.20f, 0.20f, 0.22f, 1.00f);
        colors[ImGuiCol_PlotLines]              = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
        colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
        colors[ImGuiCol_PlotHistogram]          = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
        colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
        colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
        colors[ImGuiCol_DragDropTarget]         = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
        colors[ImGuiCol_NavHighlight]           = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
        colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
        colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.00f, 0.00f, 0.00f, 0.70f);
    }
}

// ========================================================================================
// HELPER UI COMPONENTS
// ========================================================================================

namespace UIComponents {
    // Flashing warning text
    void WarningText(const char* text, ImDrawList* draw, ImVec2 pos, float size = 20.0f) {
        float time = ImGui::GetTime();
        float alpha = (sinf(time * 5.0f) * 0.25f) + 0.75f;
        draw->AddText(nullptr, size, pos, IM_COL32(255, 70, 70, (int)(255 * alpha)), text);
    }
    
    // Animated pill button with icon
    bool PillButton(const char* label, const char* icon, ImVec2 size, 
                   ImU32 color = Theme::Colors::Primary, bool enabled = true) {
        ImGuiStyle& style = ImGui::GetStyle();
        float alpha = enabled ? 1.0f : 0.5f;
        ImVec4 buttonColor = ImGui::ColorConvertU32ToFloat4(color);
        buttonColor.w *= alpha;
        
        ImGui::PushStyleColor(ImGuiCol_Button, buttonColor);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(buttonColor.x + 0.1f, 
                                                            buttonColor.y + 0.1f, 
                                                            buttonColor.z + 0.1f, 
                                                            buttonColor.w));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(buttonColor.x - 0.1f, 
                                                           buttonColor.y - 0.1f, 
                                                           buttonColor.z - 0.1f, 
                                                           buttonColor.w));
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, size.y * 0.5f); // Pill shape
        
        bool result = ImGui::Button(label, size);
        
        ImGui::PopStyleVar();
        ImGui::PopStyleColor(3);
        return enabled && result;
    }
    
    // Custom toggle switch
    bool ToggleSwitch(const char* label, bool* value) {
        ImGuiStyle& style = ImGui::GetStyle();
        ImVec2 pos = ImGui::GetCursorScreenPos();
        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        
        float height = ImGui::GetFrameHeight();
        float width = height * 1.55f;
        float radius = height * 0.50f;
        
        ImGui::InvisibleButton(label, ImVec2(width, height));
        bool changed = false;
        if (ImGui::IsItemClicked()) {
            *value = !(*value);
            changed = true;
        }
        
        // Track background
        ImU32 bg_col = ImGui::GetColorU32(*value ? ImVec4(0.2f, 0.6f, 1.0f, 1.0f) : ImVec4(0.3f, 0.3f, 0.3f, 1.0f));
        draw_list->AddRectFilled(pos, ImVec2(pos.x + width, pos.y + height), bg_col, height * 0.5f);
        
        // Knob
        float t = *value ? 1.0f : 0.0f;
        float knob_x = ImLerp(pos.x + radius, pos.x + width - radius, t);
        ImU32 knob_col = ImGui::GetColorU32(*value ? ImVec4(1.0f, 1.0f, 1.0f, 1.0f) : ImVec4(0.8f, 0.8f, 0.8f, 1.0f));
        draw_list->AddCircleFilled(ImVec2(knob_x, pos.y + radius), radius - 1.5f, knob_col);
        
        // Label
        ImGui::SameLine();
        ImGui::Text("%s", label);
        
        return changed;
    }
    
	// Toggle switch for float values
    bool ToggleSwitchFloat(const char* label, float* value) {
        // Convert float to bool for the toggle display
        bool enabled = (*value > 0.0f);
        
        // Store previous state to detect changes
        bool prevState = enabled;
        
        // Reuse the existing toggle switch UI
        ImGuiStyle& style = ImGui::GetStyle();
        ImVec2 pos = ImGui::GetCursorScreenPos();
        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        
        float height = ImGui::GetFrameHeight();
        float width = height * 1.55f;
        float radius = height * 0.50f;
        
        ImGui::InvisibleButton(label, ImVec2(width, height));
        bool changed = false;
        
        if (ImGui::IsItemClicked()) {
            // Toggle the state
            enabled = !enabled;
            // Update the float value based on the new toggle state
            *value = enabled ? 1.0f : 0.0f;
            changed = true;
        }
        
        // Track background
        ImU32 bg_col = ImGui::GetColorU32(enabled ? ImVec4(0.2f, 0.6f, 1.0f, 1.0f) : ImVec4(0.3f, 0.3f, 0.3f, 1.0f));
        draw_list->AddRectFilled(pos, ImVec2(pos.x + width, pos.y + height), bg_col, height * 0.5f);
        
        // Knob
        float t = enabled ? 1.0f : 0.0f;
        float knob_x = ImLerp(pos.x + radius, pos.x + width - radius, t);
        ImU32 knob_col = ImGui::GetColorU32(enabled ? ImVec4(1.0f, 1.0f, 1.0f, 1.0f) : ImVec4(0.8f, 0.8f, 0.8f, 1.0f));
        draw_list->AddCircleFilled(ImVec2(knob_x, pos.y + radius), radius - 1.5f, knob_col);
        
        // Label
        ImGui::SameLine();
        ImGui::Text("%s", label);
        
        return changed;
    }
    
    // Card with heading and content
    void BeginCard(const char* title, ImU32 headerColor = Theme::Colors::Primary) {
        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, Theme::Dimensions::BorderRadius);
        ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 1.0f);
        ImGui::PushStyleColor(ImGuiCol_Border, ImGui::ColorConvertU32ToFloat4(headerColor));
        
        ImGui::BeginChild(title, ImVec2(0, ImGui::GetTextLineHeightWithSpacing() * 9), 
                         true, ImGuiWindowFlags_NoScrollbar);
        
        // Header
        ImGui::PushStyleColor(ImGuiCol_Text, ImGui::ColorConvertU32ToFloat4(Theme::Colors::TextPrimary));
        // Use default font since Theme::Fonts::Header might be null
        ImGui::Text("%s", title);
        ImGui::PopStyleColor();
        
        ImGui::Separator();
    }
    
    void EndCard() {
        ImGui::EndChild();
        ImGui::PopStyleColor();
        ImGui::PopStyleVar(2);
    }
    
    // Animated slider with value display
    bool EnhancedSlider(const char* label, float* v, float v_min, float v_max, const char* format = "%.1f") {
        ImGui::PushID(label);
        
        ImGui::Text("%s", label);
        ImGui::SameLine(ImGui::GetContentRegionAvail().x - 50); // Position for the value display
        ImGui::Text(format, *v);
        
        bool changed = ImGui::SliderFloat("##slider", v, v_min, v_max, "");
        
        ImGui::PopID();
        return changed;
    }
    
    // Section header with icon
    void SectionHeader(const char* label) {
        float thickness = 2.0f;
        ImVec2 p = ImGui::GetCursorScreenPos();
        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        float width = ImGui::CalcTextSize(label).x;
        
        ImGui::Spacing();
        
        // Draw line to the left of the text
        draw_list->AddLine(
            ImVec2(p.x, p.y + ImGui::GetTextLineHeight()/2),
            ImVec2(p.x + ImGui::GetContentRegionAvail().x * 0.2f - width/2 - 10, p.y + ImGui::GetTextLineHeight()/2),
            Theme::Colors::Primary, thickness
        );
        
        // Draw the text
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ImGui::GetContentRegionAvail().x * 0.2f - width/2);
        ImGui::PushStyleColor(ImGuiCol_Text, ImGui::ColorConvertU32ToFloat4(Theme::Colors::Primary));
        // Use default font as Theme::Fonts::Header may be null
        ImGui::Text("%s", label);
        ImGui::PopStyleColor();
        
        p.y = ImGui::GetCursorScreenPos().y - ImGui::GetTextLineHeight()/2;
        
        // Draw line to the right of the text
        draw_list->AddLine(
            ImVec2(p.x + ImGui::GetContentRegionAvail().x * 0.2f + width/2 + 10, p.y),
            ImVec2(p.x + ImGui::GetContentRegionAvail().x, p.y),
            Theme::Colors::Primary, thickness
        );
        
        ImGui::Spacing();
    }
}

// ========================================================================================
// ESP DRAWING UTILITIES
// ========================================================================================

namespace ESP {
    // Create a rainbow color that cycles over time
    ImU32 Rainbow(float time, float saturation = 1.0f, float value = 1.0f) {
        float hue = fmodf(time, 1.0f);
        ImVec4 color = ImColor::HSV(hue, saturation, value);
        return ImColor(color);
    }
    
    // Smoothly pulsate between two colors
    ImU32 PulseColor(ImU32 color1, ImU32 color2, float speed = 2.0f) {
        float t = (sinf(ImGui::GetTime() * speed) + 1.0f) * 0.5f;
        ImVec4 col1 = ImGui::ColorConvertU32ToFloat4(color1);
        ImVec4 col2 = ImGui::ColorConvertU32ToFloat4(color2);
        ImVec4 result;
        result.x = col1.x + (col2.x - col1.x) * t;
        result.y = col1.y + (col2.y - col1.y) * t;
        result.z = col1.z + (col2.z - col1.z) * t;
        result.w = col1.w + (col2.w - col1.w) * t;
        return ImGui::ColorConvertFloat4ToU32(result);
    }
    
    // Draw a stroke text
    void DrawStrokeText(ImDrawList* draw, float fontSize, ImVec2 pos, ImU32 color, const char* text) {
        // Draw outline
        draw->AddText(nullptr, fontSize, ImVec2(pos.x - 1, pos.y - 1), IM_COL32(0, 0, 0, 255), text);
        draw->AddText(nullptr, fontSize, ImVec2(pos.x + 1, pos.y - 1), IM_COL32(0, 0, 0, 255), text);
        draw->AddText(nullptr, fontSize, ImVec2(pos.x - 1, pos.y + 1), IM_COL32(0, 0, 0, 255), text);
        draw->AddText(nullptr, fontSize, ImVec2(pos.x + 1, pos.y + 1), IM_COL32(0, 0, 0, 255), text);
        
        // Draw text
        draw->AddText(nullptr, fontSize, pos, color, text);
    }
    
    // Draw a rectangle with animated corners
    void DrawAnimatedRectangle(ImDrawList* draw, ImVec2 topLeft, ImVec2 bottomRight, 
                           ImU32 color, float thickness = 1.0f) {
        float time = ImGui::GetTime();
        float length = std::min((bottomRight.x - topLeft.x), (bottomRight.y - topLeft.y)) * 0.25f;
        
        // Top-left corner
        draw->AddLine(
            ImVec2(topLeft.x, topLeft.y),
            ImVec2(topLeft.x + length, topLeft.y),
            color, thickness
        );
        draw->AddLine(
            ImVec2(topLeft.x, topLeft.y),
            ImVec2(topLeft.x, topLeft.y + length),
            color, thickness
        );
        
        // Top-right corner
        draw->AddLine(
            ImVec2(bottomRight.x - length, topLeft.y),
            ImVec2(bottomRight.x, topLeft.y),
            color, thickness
        );
        draw->AddLine(
            ImVec2(bottomRight.x, topLeft.y),
            ImVec2(bottomRight.x, topLeft.y + length),
            color, thickness
        );
        
        // Bottom-left corner
        draw->AddLine(
            ImVec2(topLeft.x, bottomRight.y - length),
            ImVec2(topLeft.x, bottomRight.y),
            color, thickness
        );
        draw->AddLine(
            ImVec2(topLeft.x, bottomRight.y),
            ImVec2(topLeft.x + length, bottomRight.y),
            color, thickness
        );
        
        // Bottom-right corner
        draw->AddLine(
            ImVec2(bottomRight.x - length, bottomRight.y),
            ImVec2(bottomRight.x, bottomRight.y),
            color, thickness
        );
        draw->AddLine(
            ImVec2(bottomRight.x, bottomRight.y - length),
            ImVec2(bottomRight.x, bottomRight.y),
            color, thickness
        );
    }
    
    // Draw a health bar with gradient color
    void DrawHealthBar(ImDrawList* draw, float health, float maxHealth, 
                   ImVec2 pos, float width, float height, float padding = 2.0f) {
        if (maxHealth <= 0.0f) maxHealth = 100.0f;
        health = std::clamp(health, 0.0f, maxHealth);
        float healthPercent = health / maxHealth;
        
        // Background
        ImVec2 bgStart(pos.x, pos.y);
        ImVec2 bgEnd(pos.x + width, pos.y + height);
        draw->AddRectFilled(bgStart, bgEnd, IM_COL32(40, 40, 40, 180), 4.0f);
        
        // Health
        ImVec2 hpStart(pos.x + padding, pos.y + padding);
        ImVec2 hpEnd(pos.x + padding + (width - padding*2) * healthPercent, pos.y + height - padding);
        
        // Color gradient: Red (low health) to Yellow to Green (full health)
        ImU32 healthColor;
        if (healthPercent < 0.5f) {
            // Interpolate from red to yellow
            float t = healthPercent / 0.5f;
            healthColor = IM_COL32(
                255,
                (int)(255 * t),
                0,
                255
            );
        } else {
            // Interpolate from yellow to green
            float t = (healthPercent - 0.5f) / 0.5f;
            healthColor = IM_COL32(
                (int)(255 * (1.0f - t)),
                255,
                0,
                255
            );
        }
        
        draw->AddRectFilled(hpStart, hpEnd, healthColor, 2.0f);
        
        // Draw percentage as text
        char buf[8];
        snprintf(buf, sizeof(buf), "%d%%", (int)(healthPercent * 100));
        float textWidth = ImGui::CalcTextSize(buf).x;
        draw->AddText(ImVec2(pos.x + (width - textWidth) * 0.5f, pos.y - 15), IM_COL32(255, 255, 255, 255), buf);
    }
    
    // Draw animated line from bottom center to target
    void DrawTargetingLine(ImDrawList* draw, ImVec2 start, ImVec2 end, ImU32 color, float thickness = 1.0f) {
        const float speed = 1.5f;
        const float time = ImGui::GetTime() * speed;
        const int segments = 15;
        
        float totalLength = std::hypot(end.x - start.x, end.y - start.y);
        float dashLength = totalLength / (float)segments;
        
        ImVec2 direction = ImVec2(end.x - start.x, end.y - start.y);
        float dirLength = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        
        if (dirLength < 0.001f) return; // Avoid division by zero
        
        direction.x /= dirLength;
        direction.y /= dirLength;
        
        for (int i = 0; i < segments; i++) {
            float t = fmodf(time + i * 0.1f, 1.0f);
            float startDist = i * dashLength;
            float endDist = startDist + dashLength * 0.6f; // 60% filled, 40% empty
            
            // Make some segments invisible to create dash effect
            if (i % 2 == 1) continue;
            
            ImVec2 segStart = ImVec2(
                start.x + direction.x * startDist,
                start.y + direction.y * startDist
            );
            
            ImVec2 segEnd = ImVec2(
                start.x + direction.x * endDist,
                start.y + direction.y * endDist
            );
            
            draw->AddLine(segStart, segEnd, color, thickness);
        }
    }
}

// ========================================================================================
// MENU SYSTEM
// ========================================================================================

// Define the menu tabs
enum class MenuTab {
    Main = 0,
    Visual = 1,
    Combat = 2,
    Settings = 3
};

// Menu system that manages the UI state
class MenuSystem {
private:
    MenuTab currentTab = MenuTab::Main;
    bool showDemoWindow = false;
    
    // Fade transition effect between tabs
    float tabTransition = 1.0f;
    MenuTab lastTab = MenuTab::Main;
    
    // Animation related variables
    float animTime = 0.0f;
    bool loaded = false;
    
    // Custom color preset selector
    int selectedColorPreset = 0;
    
    // Toast notifications
    struct ToastMessage {
        std::string message;
        float remaining;
        ImU32 color;
    };
    std::vector<ToastMessage> toasts;
    
public:
    // Initialize the menu
    void Initialize() {
        loaded = true;
    }
    
    // Add a toast notification
    void AddToast(const std::string& message, ImU32 color = Theme::Colors::Success, float duration = 3.0f) {
        ToastMessage toast;
        toast.message = message;
        toast.remaining = duration;
        toast.color = color;
        toasts.push_back(toast);
    }
    
    // Update and render the toasts
    void RenderToasts(ImDrawList* draw, float deltaTime) {
        const float toastPadding = 10.0f;
        const float toastHeight = 40.0f;
        float yPosition = ImGui::GetIO().DisplaySize.y - 20.0f;
        
        for (auto it = toasts.begin(); it != toasts.end();) {
            it->remaining -= deltaTime;
            
            if (it->remaining <= 0.0f) {
                it = toasts.erase(it);
                continue;
            }
            
            // Fade in/out animation
            float alpha = 1.0f;
            if (it->remaining < 0.5f) {
                alpha = it->remaining / 0.5f;
            } else if (it->remaining > (Theme::Animation::ToastDuration - 0.5f)) {
                alpha = (Theme::Animation::ToastDuration - it->remaining) / 0.5f;
            }
            
            ImVec2 textSize = ImGui::CalcTextSize(it->message.c_str());
            float width = textSize.x + 2.0f * toastPadding;
            
            ImVec2 rectMin(
                (ImGui::GetIO().DisplaySize.x - width) * 0.5f,
                yPosition - toastHeight
            );
            ImVec2 rectMax(
                rectMin.x + width,
                yPosition
            );
            
            ImU32 bgColor = IM_COL32(40, 40, 40, (int)(200 * alpha));
            
            // Get RGB components from the color
            ImVec4 borderColorVec = ImGui::ColorConvertU32ToFloat4(it->color);
            ImU32 borderColor = IM_COL32(
                (int)(borderColorVec.x * 255 * alpha),
                (int)(borderColorVec.y * 255 * alpha),
                (int)(borderColorVec.z * 255 * alpha),
                (int)(borderColorVec.w * 255 * alpha)
            );
            
            ImU32 textColor = IM_COL32(255, 255, 255, (int)(255 * alpha));
            
            draw->AddRectFilled(rectMin, rectMax, bgColor, 8.0f);
            draw->AddRect(rectMin, rectMax, borderColor, 8.0f, 15, 2.0f);
            
            ImVec2 textPos(
                rectMin.x + (width - textSize.x) * 0.5f,
                rectMin.y + (toastHeight - textSize.y) * 0.5f
            );
            draw->AddText(textPos, textColor, it->message.c_str());
            
            yPosition -= (toastHeight + 10.0f);
            ++it;
        }
    }
    
    // Update animation state
    void Update(float deltaTime) {
        animTime += deltaTime;
        
        // Handle tab transition animation
        if (currentTab != lastTab) {
            tabTransition = 0.0f;
            lastTab = currentTab;
        }
        
        tabTransition = std::min(tabTransition + deltaTime * 4.0f, 1.0f);
    }
    
    // Render the top navigation bar
    void RenderNavBar() {
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 6));
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(6, 6));
        
        // Gradient background
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.12f, 0.12f, 0.14f, 0.8f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.18f, 0.18f, 0.20f, 0.8f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.24f, 0.24f, 0.28f, 0.8f));
        
        float width = ImGui::GetContentRegionAvail().x / 4.0f - 3.0f;
        
        RenderNavButton("Main", MenuTab::Main, width);
        ImGui::SameLine();
        RenderNavButton("Visual", MenuTab::Visual, width);
        ImGui::SameLine();
        RenderNavButton("Combat", MenuTab::Combat, width);
        ImGui::SameLine();
        RenderNavButton("Settings", MenuTab::Settings, width);
        
        ImGui::PopStyleColor(3);
        ImGui::PopStyleVar(2);
    }
    
    // Render a single navigation button
    void RenderNavButton(const char* label, MenuTab tab, float width) {
        bool isSelected = (currentTab == tab);
        
        if (isSelected) {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.26f, 0.59f, 0.98f, 0.7f));
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
        } else {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.15f, 0.15f, 0.17f, 0.6f));
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.8f, 0.8f, 0.8f, 0.8f));
        }
        
        if (ImGui::Button(label, ImVec2(width, 0))) {
            currentTab = tab;
        }
        
        ImGui::PopStyleColor(2);
    }
    
    // Render the main content based on the selected tab
    void RenderContent() {
        switch (currentTab) {
            case MenuTab::Main:
                RenderMainTab();
                break;
            case MenuTab::Visual:
                RenderVisualTab();
                break;
            case MenuTab::Combat:
                RenderCombatTab();
                break;
            case MenuTab::Settings:
                RenderSettingsTab();
                break;
        }
    }
    
    // Main tab content - Quick Actions
    void RenderMainTab() {
        UIComponents::SectionHeader("Quick Actions");
        
        // Quick ESP on/off button row
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 8));
        if (UIComponents::PillButton("START ESP", "🔍", ImVec2(ImGui::GetContentRegionAvail().x * 0.48f, 45), Theme::Colors::Secondary)) {
            // Enable all ESP features
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
            
            AddToast("ESP activated", Theme::Colors::Success);
        }
        ImGui::SameLine();
        if (UIComponents::PillButton("STOP ESP", "❌", ImVec2(ImGui::GetContentRegionAvail().x, 45), Theme::Colors::Danger)) {
            // Disable all ESP features
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
            
            AddToast("ESP deactivated", Theme::Colors::Warning);
        }
        ImGui::PopStyleVar();
        
        ImGui::Spacing();
        ImGui::Spacing();
        
        // Most used features with toggles
        UIComponents::SectionHeader("Quick Settings");
        
        ImGui::Columns(2, NULL, false);
        
        // Column 1
        UIComponents::ToggleSwitch("HeadShot V2", &Cheat::AimBot::HeadShoot);
        UIComponents::ToggleSwitch("No Recoil", &Cheat::Memory::NoRecoil);
        UIComponents::ToggleSwitch("Small Crosshair", &Cheat::Memory::SmallCrossHair);
        
        ImGui::NextColumn();
        
        // Column 2
        UIComponents::ToggleSwitch("Instant Hit", &Cheat::Memory::InstantHit);
        UIComponents::ToggleSwitch("IPad View", &Cheat::Memory::IPadView);
        UIComponents::ToggleSwitch("Anti-Report", &Cheat::Memory::AntiReport);
        
        ImGui::Columns(1);
        
        ImGui::Spacing();
        ImGui::Spacing();
        
        // FOV Slider
        UIComponents::EnhancedSlider("Field of View", &Cheat::Memory::WideViewRange, 0.0f, 150.0f, "%.0f°");
        
        ImGui::Spacing();
        ImGui::Spacing();
        
        // Bottom buttons row
        if (UIComponents::PillButton("Logout Account", "🔓", ImVec2(ImGui::GetContentRegionAvail().x, 45), Theme::Colors::Warning)) {
            system(OBFUSCATE("rm -rf /data/data/com.pubg.imobile/files"));
            AddToast("Logged out successfully", Theme::Colors::Info);
        }
    }
    
    // Visual tab content - ESP Settings
    void RenderVisualTab() {
        UIComponents::SectionHeader("ESP Options");
        
        ImGui::Columns(2, NULL, false);
        
        // Column 1
        UIComponents::ToggleSwitch("Player Box", &Cheat::Esp::Box);
        UIComponents::ToggleSwitch("Player Lines", &Cheat::Esp::Line);
        UIComponents::ToggleSwitch("Player Skeleton", &Cheat::Esp::Skeleton);
        UIComponents::ToggleSwitch("Player Health", &Cheat::Esp::Health);
        UIComponents::ToggleSwitch("Player Name", &Cheat::Esp::Name);
        
        ImGui::NextColumn();
        
        // Column 2
        UIComponents::ToggleSwitch("Player Distance", &Cheat::Esp::Distance);
        UIComponents::ToggleSwitch("Team ID", &Cheat::Esp::TeamID);
        UIComponents::ToggleSwitch("Enemy Alert", &Cheat::Esp::Alert);
        UIComponents::ToggleSwitch("Hide Bots", &Cheat::Esp::NoBot);
        UIComponents::ToggleSwitch("Enemies Alert", &Cheat::BulletTrack::EnimiesAlert);
        
        ImGui::Columns(1);
        
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();
        
        UIComponents::SectionHeader("Vehicle Options");
        
        ImGui::Columns(2, NULL, false);
        
        // Column 1
        UIComponents::ToggleSwitch("Vehicle Names", &Cheat::Esp::Vehicle::Name);
        UIComponents::ToggleSwitch("Vehicle Health", &Cheat::Esp::Vehicle::Health);
        
        ImGui::NextColumn();
        
        // Column 2
        UIComponents::ToggleSwitch("Vehicle Fuel", &Cheat::Esp::Vehicle::Fuel);
        UIComponents::ToggleSwitch("Target Line", &Cheat::Esp::TargetLine);
        
        ImGui::Columns(1);
        
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();
        
        UIComponents::SectionHeader("Game Info Display");
        UIComponents::ToggleSwitch("Show Match Info", &Cheat::Memory::GameInfo);
    }
    
    // Combat tab content
    void RenderCombatTab() {
        UIComponents::SectionHeader("Aim Assistance");
        
        if (UIComponents::ToggleSwitch("One-Click Combat Assist", &masterCheckbox2)) {
            Cheat::BulletTrack::Enable = masterCheckbox2;
            ByPussy = masterCheckbox2;
            Cheat::BulletTrack::Range = 400.0f;
            Cheat::BulletTrack::VisCheck = masterCheckbox2;
            Cheat::BulletTrack::IgnoreKnock = masterCheckbox2;
            AddToast(masterCheckbox2 ? "Combat assist activated" : "Combat assist deactivated",
                    masterCheckbox2 ? Theme::Colors::Success : Theme::Colors::Warning);
        }
        
        ImGui::Spacing();
        
        UIComponents::BeginCard("Aimbot Settings");
        
        ImGui::Columns(2, NULL, false);
        
        // Column 1
        UIComponents::ToggleSwitch("Show Aimbot Button", &AIMBUTTON);
        UIComponents::ToggleSwitch("Enable Aimbot", &Cheat::AimBot::Enable);
        UIComponents::ToggleSwitch("Visibility Check", &Cheat::AimBot::VisCheck);
        
        ImGui::NextColumn();
        
        // Column 2
        UIComponents::ToggleSwitch("Ignore Bots", &Cheat::AimBot::IgnoreBot);
        UIComponents::ToggleSwitchFloat("Recoil Compensation", &Cheat::AimBot::RecoilComparison);
        
        ImGui::Columns(1);
        
        ImGui::Text("Aim Target:");
        ImGui::SameLine();
        static const char *targets[] = {"HEAD", "BODY"};
        ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
        ImGui::Combo("##Target", (int *)&Cheat::AimBot::Target, targets, 2);
        
        ImGui::Text("Trigger Method:");
        ImGui::SameLine();
        static const char *triggers[] = {"None", "Shooting", "Scoping", "Both", "Any"};
        ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
        ImGui::Combo("##Trigger", (int *)&Cheat::AimBot::Trigger, triggers, 5);
        
        ImGui::Spacing();
        UIComponents::EnhancedSlider("FOV Radius", &Cheat::AimBot::Radius, 0.0f, 1000.0f, "%.0f");
        
        UIComponents::EndCard();
        
        ImGui::Spacing();
        
        UIComponents::BeginCard("Bullet Track Settings");
        
        ImGui::Columns(2, NULL, false);
        
        // Column 1
        UIComponents::ToggleSwitch("Show BT Button", &BTBUTTON);
        UIComponents::ToggleSwitch("Enable Bullet Track", &Cheat::BulletTrack::Enable);
        UIComponents::ToggleSwitch("Visibility Check", &Cheat::BulletTrack::VisCheck);
        
        ImGui::NextColumn();
        
        // Column 2
        UIComponents::ToggleSwitch("Ignore Knocked", &Cheat::BulletTrack::IgnoreKnock);
        UIComponents::ToggleSwitch("Ignore Bots", &Cheat::BulletTrack::IgnoreBot);
        UIComponents::ToggleSwitch("LAMBORGHINI Mode", &Cheat::BulletTrack::LAMBORGHINI);
        
        ImGui::Columns(1);
        
        ImGui::Spacing();
        UIComponents::EnhancedSlider("Bullet Track Radius", &Cheat::BulletTrack::Radius, 0.0f, 1000.0f, "%.0f");
        UIComponents::EnhancedSlider("Bullet Track Range", &Cheat::BulletTrack::Range, 0.0f, 400.0f, "%.0f");
        UIComponents::EnhancedSlider("Aim Position", &Cheat::BulletTrack::AimSet, -17.0f, 10.0f, "%.1f");
        
        UIComponents::EndCard();
    }
    
    // Settings tab content
    void RenderSettingsTab() {
        UIComponents::SectionHeader("Skins & Cosmetics");
        
        // X-SUIT Skin selection
        ImGui::Text("X-SUIT SKIN");
        const char* xsuuity[] = { "NO SKIN", "Blood Raven X-Suit", "Golden Pharaoh X-Suit", 
                                 "Avalanche X-suit", "Irresidence X-suit", "Poseidon X-suit", "Arcane Jester X-suit" };
        ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
        ImGui::Combo("##xs", &skinxsuit, xsuuity, IM_ARRAYSIZE(xsuuity));
        
        ImGui::Spacing();
        
        // M416 Skin selection
        ImGui::Text("M416 SKIN");
        const char* m416[] = { "NO SKIN", "Glacier - M416", "The Fool - M416", "Lizard Roar - M416",
                              "Wanderer - M416", "Call of the Wild - M416", "Imperial Splendor - M416" };
        ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
        ImGui::Combo("##m4", &skinm4, m416, IM_ARRAYSIZE(m416));
        
        ImGui::Spacing();
        
        // AKM Skin selection
        ImGui::Text("AKM SKIN");
        const char* AKM[] = { "NO SKIN", "Sculpture - AKM", "The Seven Seas - AKM", "Roaring Tiger - AKM",
                             "Glacier - AKM", "Desert Fossil - AKM", "Jack-o'-lantern - AKM", "Ghillie Dragon - AKM" };
        ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
        ImGui::Combo("##AKM", &skinakm, AKM, IM_ARRAYSIZE(AKM));
        
        ImGui::Spacing();
        
        // SCAR-L Skin selection
        ImGui::Text("SCAR-L SKIN");
        const char* SCAR[] = { "NO SKIN", "Water Blaster - SCAR-L", "Enchanted Pumpkin - SCAR-L",
                              "Enchanted Pumpkin - SCAR-L", "Operation Tomorrow - SCAR-L" };
        ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
        ImGui::Combo("##SCAR-L", &skinscar, SCAR, IM_ARRAYSIZE(SCAR));
        
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();
        
        UIComponents::SectionHeader("App Settings");
        
        ImGui::Columns(2, NULL, false);
        
        // Column 1
        UIComponents::ToggleSwitch("Anti-Report", &Cheat::Memory::AntiReport);
        UIComponents::ToggleSwitch("Memory Cleaner", &Cheat::Memory::MemoryCleaner);
        
        ImGui::NextColumn();
        
        // Column 2
        UIComponents::ToggleSwitch("Safe Mode", &Cheat::Memory::SafeMode);
        UIComponents::ToggleSwitch("Show FPS", &Cheat::Memory::ShowFPS);
        
        ImGui::Columns(1);
        
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();
        
        // Bottom buttons
        if (UIComponents::PillButton("Delete Reports", "🗑️", ImVec2(ImGui::GetContentRegionAvail().x * 0.48f, 45), Theme::Colors::Danger)) {
            system(OBFUSCATE("rm -rf /data/data/com.pubg.imobile/shared_prefs"));
            system(OBFUSCATE("rm -rf /data/data/com.pubg.imobile/databases"));
            system(OBFUSCATE("rm -rf /data/data/com.pubg.imobile/cache"));
            system(OBFUSCATE("rm -rf /data/data/com.pubg.imobile/app_crashKit"));
            system(OBFUSCATE("rm -rf /data/data/com.pubg.imobile/app_webview"));
            AddToast("All reports deleted", Theme::Colors::Success);
        }
        
        ImGui::SameLine();
        
        if (UIComponents::PillButton("Clear Game Cache", "🧹", ImVec2(ImGui::GetContentRegionAvail().x, 45), Theme::Colors::Warning)) {
            system(OBFUSCATE("rm -rf /storage/emulated/0/Android/data/com.pubg.imobile/cache*"));
            system(OBFUSCATE("rm -rf /storage/emulated/0/Android/data/com.pubg.imobile/files/cacheFile.txt"));
            system(OBFUSCATE("rm -rf /storage/emulated/0/Android/data/com.pubg.imobile/files/UE4Game/ShadowTrackerExtra/ShadowTrackerExtra/Saved/Logs*"));
            AddToast("Cache cleared", Theme::Colors::Success);
        }
    }
    
    // Animation for the snakes background
    void RenderSnakeBackground(ImDrawList* drawList, ImVec2 windowPos, ImVec2 windowSize) {
        float time = ImGui::GetTime();
        int totalSnakes = 12; // Reduced number for better performance
        float snakeSpeed = 0.5f;
        float waveAmplitude = 15.0f;
        float waveFreq = 3.0f;
        
        static std::vector<ImVec2> snakeCenters;
        static std::vector<ImVec2> snakeDirs;
        
        if (snakeCenters.size() != totalSnakes) {
            snakeCenters.clear();
            snakeDirs.clear();
            for (int i = 0; i < totalSnakes; ++i) {
                snakeCenters.push_back(ImVec2(
                    windowPos.x + rand() % (int)windowSize.x,
                    windowPos.y + rand() % (int)windowSize.y
                ));
                
                float angle = (rand() % 360) * (IM_PI / 180.0f);
                snakeDirs.push_back(ImVec2(cosf(angle), sinf(angle)));
            }
        }
        
        for (int s = 0; s < totalSnakes; ++s) {
            ImVec2& center = snakeCenters[s];
            ImVec2& dir = snakeDirs[s];
            
            // Update snake position
            center.x += dir.x * snakeSpeed;
            center.y += dir.y * snakeSpeed;
            
            // Bounce off walls
            if (center.x < windowPos.x || center.x > windowPos.x + windowSize.x) {
                dir.x *= -1;
                center.x = std::clamp(center.x, windowPos.x, windowPos.x + windowSize.x);
            }
            if (center.y < windowPos.y || center.y > windowPos.y + windowSize.y) {
                dir.y *= -1;
                center.y = std::clamp(center.y, windowPos.y, windowPos.y + windowSize.y);
            }
            
            float snakeTimeOffset = s * 0.7f;
            int segments = 30; // Reduced for performance
            
            std::vector<ImVec2> snakePath;
            for (int i = 0; i < segments; ++i) {
                float t = (float)i / segments;
                float baseX = center.x - dir.x * t * 60.0f; // Tail length
                float baseY = center.y - dir.y * t * 60.0f;
                
                float wave = sinf((time + snakeTimeOffset) * 2.0f + t * waveFreq * 3.0f) * waveAmplitude;
                ImVec2 normal(-dir.y, dir.x); // Perpendicular to direction
                
                ImVec2 pos = ImVec2(
                    baseX + normal.x * wave,
                    baseY + normal.y * wave
                );
                
                snakePath.push_back(pos);
            }
            
            // Draw snake
            for (int i = 1; i < segments; ++i) {
                float t = (float)i / segments;
                float fadeout = 1.0f - t; // Fade out toward tail
                
                // Generate color based on snake index
                ImU32 color;
                float hue = fmodf((s * 0.12f + time * 0.05f), 1.0f);
                
                // Bright, vibrant colors
                if (s % 3 == 0) {
                    // Fire snake (orange/red)
                    color = IM_COL32(
                        (int)(255 * fadeout),
                        (int)(100 * fadeout * t),
                        (int)(10 * fadeout * t * t),
                        (int)(140 * fadeout)
                    );
                } else if (s % 3 == 1) {
                    // Electric snake (cyan/blue)
                    color = IM_COL32(
                        (int)(40 * fadeout * t),
                        (int)(170 * fadeout),
                        (int)(255 * fadeout),
                        (int)(140 * fadeout)
                    );
                } else {
                    // Poison snake (green/yellow)
                    color = IM_COL32(
                        (int)(180 * fadeout * t),
                        (int)(255 * fadeout),
                        (int)(30 * fadeout * t),
                        (int)(140 * fadeout)
                    );
                }
                
                // Thicker near head, thinner at tail
                float thickness = (1.0f + 5.0f * (1.0f - t)) * (sinf(time * 4.0f + s) * 0.25f + 0.75f);
                drawList->AddLine(snakePath[i - 1], snakePath[i], color, thickness);
            }
        }
    }
};

// Global menu system instance
MenuSystem gMenu;

// Login state tracking
struct LoginState {
    bool isLoggedIn = false;
    char keyInput[64] = {0};
    std::string errorMessage;
    
    void Reset() {
        isLoggedIn = false;
        memset(keyInput, 0, sizeof(keyInput));
        errorMessage.clear();
    }
};

// Global login state
LoginState gLoginState;

// ========================================================================================
// MAIN DRAWING FUNCTIONS
// ========================================================================================

// Helper function to extract color components
inline int GetR(ImU32 color) { return (color >> IM_COL32_R_SHIFT) & 0xFF; }
inline int GetG(ImU32 color) { return (color >> IM_COL32_G_SHIFT) & 0xFF; }
inline int GetB(ImU32 color) { return (color >> IM_COL32_B_SHIFT) & 0xFF; }

// Draw in-game ESP elements
void DrawESP(ImDrawList* draw) {
    // Display branding text
    float brandingSize = density / 19.0f;
    ESP::DrawStrokeText(draw, brandingSize, ImVec2(density / 19.0f, 50), Theme::Colors::Primary, "IBR Pro");
    
    // Display purchase information (with shadow effect for better visibility)
    float purchaseSize = density / 10.0f;
    ESP::DrawStrokeText(draw, purchaseSize, ImVec2(density / 10.0f, 650), Theme::Colors::TextPrimary, "Premium Gaming Enhancement Suite");
    ESP::DrawStrokeText(draw, purchaseSize, ImVec2(density / 10.0f, 670), Theme::Colors::TextPrimary, "By saiaika - 2025-04-27");
    
    // Display telegram channel info with outline
    std::string credit = OBFUSCATE("[0] Telegram Channel -> IBR Premium Upgrade");
    auto textSize = ImGui::CalcTextSize(credit.c_str());
    float creditSize = density / 14.0f;
    
    // Draw text with outline effect for better visibility
    ESP::DrawStrokeText(
        draw, 
        creditSize, 
        ImVec2((glWidth / 2) - (textSize.x / 2), 30), 
        IM_COL32(0, 255, 0, 255),
        credit.c_str()
    );
    
    // Game object processing begins here
    auto Actors = GetActors();
    int totalEnemies = 0, totalBots = 0;
    
    // Locate local player and controller
    ASTExtraPlayerCharacter* localPlayer = 0;
    ASTExtraPlayerController* localController = 0;
    
    for (int i = 0; i < Actors.size(); i++) {
        auto Actor = Actors[i];
        if (isObjectInvalid(Actor))
            continue;
        
        if (Actor->IsA(ASTExtraPlayerController::StaticClass())) {
            localController = (ASTExtraPlayerController*)Actor;
            break;
        }
    }
    
    if (localController) {
        // Find the local player character
        for (int i = 0; i < Actors.size(); i++) {
            auto Actor = Actors[i];
            if (isObjectInvalid(Actor))
                continue;
            
            if (Actor->IsA(ASTExtraPlayerCharacter::StaticClass())) {
                if (((ASTExtraPlayerCharacter*)Actor)->PlayerKey == localController->PlayerKey) {
                    localPlayer = (ASTExtraPlayerCharacter*)Actor;
                    break;
                }
            }
        }
        
        // Process player features if local player found
        if (localPlayer) {
            // Process collision angles for improved hit detection
            if (localPlayer->PartHitComponent) {
                auto ConfigCollisionDistSqAngles = localPlayer->PartHitComponent->ConfigCollisionDistSqAngles;
                for (int j = 0; j < ConfigCollisionDistSqAngles.Num(); j++) {
                    ConfigCollisionDistSqAngles[j].Angle = 180.0f; // Maximum angle
                }
                localPlayer->PartHitComponent->ConfigCollisionDistSqAngles = ConfigCollisionDistSqAngles;
            }
            
            // Apply iPad view if enabled
            if (Cheat::Memory::IPadView) {
                localPlayer->ThirdPersonCameraComponent->SetFieldOfView(Cheat::Memory::WideViewRange);
            }
            
            // Draw aim mode indicator
            if (Cheat::BulletTrack::Target == Cheat::EAimTarget::Head) {
                ESP::DrawStrokeText(
                    draw,
                    density / 22.0f,
                    ImVec2(glWidth / 2 - 107.0f, 540.0f),
                    Theme::Colors::Success,
                    "Aim->Mode : Head"
                );
            } else {
                ESP::DrawStrokeText(
                    draw,
                    density / 22.0f,
                    ImVec2(glWidth / 2 - 107.0f, 540.0f),
                    Theme::Colors::Info,
                    "Aim->Mode : Body"
                );
            }
        }
        
        // Update global pointers for use in other systems
        g_LocalController = localController;
        g_LocalPlayer = localPlayer;
        
        // Process enemies and display ESP
        // This would be expanded with the full ESP implementation
    }
}

// Define the render functions
void RenderAimButton(ImDrawList* draw) {
    ImVec2 pos = ImVec2(900, 100);
    float buttonSize = 100.0f;
    
    // Create a fancy rounded button
    if (Cheat::AimBot::Enable) {
        // Active state
        draw->AddRectFilled(
            ImVec2(pos.x + 100, pos.y + 100),
            ImVec2(pos.x + 200, pos.y + 200),
            IM_COL32(0, 0, 0, 200),
            buttonSize
        );
        
        // Red crosshair
        ImU32 activeColor = IM_COL32(255, 3, 3, 255);
        draw->AddLine(ImVec2(pos.x + 150, pos.y + 120), ImVec2(pos.x + 150, pos.y + 140), activeColor, 7.0f);
        draw->AddLine(ImVec2(pos.x + 150, pos.y + 160), ImVec2(pos.x + 150, pos.y + 180), activeColor, 7.0f);
        draw->AddLine(ImVec2(pos.x + 120, pos.y + 150), ImVec2(pos.x + 140, pos.y + 150), activeColor, 7.0f);
        draw->AddLine(ImVec2(pos.x + 160, pos.y + 150), ImVec2(pos.x + 180, pos.y + 150), activeColor, 7.0f);
    } else {
        // Inactive state
        draw->AddRectFilled(
            ImVec2(pos.x + 100, pos.y + 100),
            ImVec2(pos.x + 200, pos.y + 200),
            IM_COL32(0, 0, 0, 200),
            buttonSize
        );
        
        // Green crosshair
        ImU32 inactiveColor = IM_COL32(0, 255, 0, 255);
        draw->AddLine(ImVec2(pos.x + 150, pos.y + 110), ImVec2(pos.x + 150, pos.y + 140), inactiveColor, 7.0f);
        draw->AddLine(ImVec2(pos.x + 150, pos.y + 160), ImVec2(pos.x + 150, pos.y + 190), inactiveColor, 7.0f);
        draw->AddLine(ImVec2(pos.x + 110, pos.y + 150), ImVec2(pos.x + 140, pos.y + 150), inactiveColor, 7.0f);
        draw->AddLine(ImVec2(pos.x + 160, pos.y + 150), ImVec2(pos.x + 190, pos.y + 150), inactiveColor, 7.0f);
    }
}

void RenderBulletTrackButton(ImDrawList* draw) {
    ImVec2 pos = ImVec2(900, 100);
    float buttonSize = 100.0f;
    
    if (Cheat::BulletTrack::Enable) {
        // Active state
        draw->AddRectFilled(
            ImVec2(pos.x + 100, pos.y + 100),
            ImVec2(pos.x + 200, pos.y + 200),
            IM_COL32(0, 0, 0, 200),
            buttonSize
        );
        
        // Blue crosshair
        ImU32 activeColor = IM_COL32(0, 4, 255, 255);
        draw->AddLine(ImVec2(pos.x + 150, pos.y + 120), ImVec2(pos.x + 150, pos.y + 140), activeColor, 7.0f);
        draw->AddLine(ImVec2(pos.x + 150, pos.y + 160), ImVec2(pos.x + 150, pos.y + 180), activeColor, 7.0f);
        draw->AddLine(ImVec2(pos.x + 120, pos.y + 150), ImVec2(pos.x + 140, pos.y + 150), activeColor, 7.0f);
        draw->AddLine(ImVec2(pos.x + 160, pos.y + 150), ImVec2(pos.x + 180, pos.y + 150), activeColor, 7.0f);
    } else {
        // Inactive state
        draw->AddRectFilled(
            ImVec2(pos.x + 100, pos.y + 100),
            ImVec2(pos.x + 200, pos.y + 200),
            IM_COL32(0, 0, 0, 200),
            buttonSize
        );
        
        // Green crosshair
        ImU32 inactiveColor = IM_COL32(0, 255, 0, 255);
        draw->AddLine(ImVec2(pos.x + 150, pos.y + 110), ImVec2(pos.x + 150, pos.y + 140), inactiveColor, 7.0f);
        draw->AddLine(ImVec2(pos.x + 150, pos.y + 160), ImVec2(pos.x + 150, pos.y + 190), inactiveColor, 7.0f);
        draw->AddLine(ImVec2(pos.x + 110, pos.y + 150), ImVec2(pos.x + 140, pos.y + 150), inactiveColor, 7.0f);
        draw->AddLine(ImVec2(pos.x + 160, pos.y + 150), ImVec2(pos.x + 190, pos.y + 150), inactiveColor, 7.0f);
    }
}

// ========================================================================================
// MAIN WINDOW RENDERING
// ========================================================================================

// Entry point for the mod menu rendering
EGLBoolean (*orig_eglSwapBuffers)(EGLDisplay dpy, EGLSurface surface);

EGLBoolean _eglSwapBuffers(EGLDisplay dpy, EGLSurface surface) {
    // Get the surface dimensions
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
        
        // Set up the modern theme
        Theme::SetupStyle(density);
        
        // Initialize the platform backends
        ImGui_ImplAndroid_Init();
        ImGui_ImplOpenGL3_Init("#version 300 es");
        
        // Configure fonts
        ImGuiIO &io = ImGui::GetIO();
        
        // Add Roboto font
        io.Fonts->AddFontFromMemoryCompressedTTF(
            Roboto_compressed_data, 
            Roboto_compressed_size,
            19.0f,
            nullptr,
            io.Fonts->GetGlyphRangesCyrillic()
        );
        
        // Add a default font with scaling
        ImFontConfig cfg;
        cfg.SizePixels = ((float)density / 20.0f);
        io.Fonts->AddFontDefault(&cfg);
        
        // Initialize the menu system
        gMenu.Initialize();
        
        // Mark initialization complete
        initImGui = true;
    }
    
    // Begin ImGui frame
    ImGuiIO &io = ImGui::GetIO();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame(glWidth, glHeight);
    ImGui::NewFrame();
    
    // Draw ESP elements in background
    DrawESP(ImGui::GetBackgroundDrawList());
    
    // Calculate delta time
    float deltaTime = io.DeltaTime;
    
    // Update animations
    gMenu.Update(deltaTime);
    
    // Render toast notifications
    gMenu.RenderToasts(ImGui::GetBackgroundDrawList(), deltaTime);
    
    // Set up the main window size
    ImGui::SetNextWindowSize(ImVec2((float)glWidth * 0.45f, (float)glHeight * 0.80f), ImGuiCond_Once);
    
    // Create window title with FPS counter
    char buf[128];
    sprintf(buf, (OBFUSCATE("IBR Premium v4.2.1 • %.1f FPS ###MainWindow")), io.Framerate);
    
    // Begin main window
    if (ImGui::Begin(buf, nullptr, ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoSavedSettings)) {
        // Check login state
        if (!isLogin) {
            // Login screen
            RenderLoginScreen();
        } else {
            // Main menu
            
            // Draw animated background
            gMenu.RenderSnakeBackground(
                ImGui::GetWindowDrawList(),
                ImGui::GetWindowPos(),
                ImGui::GetWindowSize()
            );
            
            // Navigation bar
            gMenu.RenderNavBar();
            
            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Spacing();
            
            // Content based on selected tab
            gMenu.RenderContent();
        }
    }
    ImGui::End();
    
    // Render ImGui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    
    // Forward to original function
    return orig_eglSwapBuffers(dpy, surface);
}

// Login screen function
void RenderLoginScreen() {
    static std::string err;
    
    // Center content
    float windowWidth = ImGui::GetWindowWidth();
    float contentWidth = std::min(400.0f, windowWidth * 0.7f);
    ImGui::SetCursorPosX((windowWidth - contentWidth) * 0.5f);
    
    // Logo/banner area
    ImGui::BeginChild("##LogoArea", ImVec2(contentWidth, 120), true, ImGuiWindowFlags_NoScrollbar);
    {
        // Center logo text
        const char* logoText = "IBR Premium";
        ImVec2 textSize = ImGui::CalcTextSize(logoText);
        ImGui::SetCursorPosX((contentWidth - textSize.x) * 0.5f);
        ImGui::SetCursorPosY(30);
        
        // Animated rainbow text
        float time = ImGui::GetTime();
        float hue = fmodf(time * 0.3f, 1.0f);
        ImVec4 colorVec = ImColor::HSV(hue, 1.0f, 1.0f);
        ImGui::PushStyleColor(ImGuiCol_Text, colorVec);
        ImGui::Text("%s", logoText);
        ImGui::PopStyleColor();
        
        // Subtitle
        const char* subtitleText = "Premium Gaming Enhancement";
        textSize = ImGui::CalcTextSize(subtitleText);
        ImGui::SetCursorPosX((contentWidth - textSize.x) * 0.5f);
        ImGui::SetCursorPosY(75);
        ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.8f, 1.0f), "%s", subtitleText);
    }
    ImGui::EndChild();
    
    ImGui::SetCursorPosX((windowWidth - contentWidth) * 0.5f);
    ImGui::Spacing();
    
    // Login form
    ImGui::BeginChild("##LoginForm", ImVec2(contentWidth, 220), true);
    {
        ImGui::Spacing();
        ImGui::Text("Please Login");
        ImGui::Spacing();
        
        ImGui::PushItemWidth(-1);
        
        // Key input field with improved styling
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 6.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 8));
        
        static char keyInput[64] = {0};
        ImGui::InputText("##key", keyInput, sizeof(keyInput), ImGuiInputTextFlags_Password);
        ImGui::PopStyleVar(2);
        
        ImGui::Spacing();
        ImGui::Spacing();
        
        // Auto-paste functionality
        auto key = getClipboardText();
        if (!key.empty()) {
            strncpy(keyInput, key.c_str(), sizeof(keyInput));
        }
        
        // Login button
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.6f, 1.0f, 0.8f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.7f, 1.0f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.15f, 0.5f, 0.9f, 1.0f));
        
        if (ImGui::Button("LOGIN", ImVec2(-1, 45))) {
            // Process login
            err = Login(keyInput);
            if (err == "OK") {
                isLogin = bValid && g_Auth == g_Token;
            }
        }
        ImGui::PopStyleColor(3);
        
        ImGui::Spacing();
        
        // Paste key button
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.3f, 0.3f, 0.3f, 0.8f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.4f, 0.4f, 0.4f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.25f, 0.25f, 0.25f, 1.0f));
        
        if (ImGui::Button("PASTE LICENSE KEY", ImVec2(-1, 35))) {
            auto key = getClipboardText();
            strncpy(keyInput, key.c_str(), sizeof(keyInput));
        }
        ImGui::PopStyleColor(3);
        
        ImGui::Spacing();
        
        // Error message
        if (!err.empty() && err != "OK") {
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.3f, 0.3f, 1.0f));
            ImGui::TextWrapped("Error: %s", err.c_str());
            ImGui::PopStyleColor();
        }
        
        ImGui::PopItemWidth();
    }
    ImGui::EndChild();
    
    ImGui::SetCursorPosX((windowWidth - contentWidth) * 0.5f);
    ImGui::Spacing();
    
    // Footer with contact information
    ImGui::BeginChild("##FooterArea", ImVec2(contentWidth, 70), true, ImGuiWindowFlags_NoScrollbar);
    {
        ImGui::Spacing();
        
        const char* contactText = "Created by saiaika";
        ImVec2 textSize = ImGui::CalcTextSize(contactText);
        ImGui::SetCursorPosX((contentWidth - textSize.x) * 0.5f);
        ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1.0f), "%s", contactText);
        
        ImGui::Spacing();
        
        char dateText[64];
        snprintf(dateText, sizeof(dateText), "Version 4.2.1 (2025-04-27)");
        textSize = ImGui::CalcTextSize(dateText);
        ImGui::SetCursorPosX((contentWidth - textSize.x) * 0.5f);
        ImGui::TextColored(ImVec4(0.4f, 0.6f, 0.9f, 1.0f), "%s", dateText);
    }
    ImGui::EndChild();
}

// ========================================================================================
// BACKGROUND THREADS
// ========================================================================================

// Thread for handling iPad view setting
void *ipad_thread(void *) {
    while (true) {
        auto t1 = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();
        
        if (Cheat::Memory::WideView) {
            auto objs = UObject::GetGlobalObjects();
            for (int i = 0; i < objs.Num(); i++) {
                auto Object = objs.GetByIndex(i);
                if (isObjectInvalid(Object))
                    continue;
                
                if (Object->IsA(ULocalPlayer::StaticClass())) {
                    auto playerChar = (ULocalPlayer *)Object;
                    playerChar->AspectRatioAxisConstraint = EAspectRatioAxisConstraint::AspectRatio_MaintainYFOV;
                }
            }
        }
        
        // Limit thread execution to save resources
        auto td = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count() - t1;
        std::this_thread::sleep_for(std::chrono::milliseconds(
            std::max(std::min(0LL, SLEEP_TIME - td), SLEEP_TIME)));
    }
}

// Main initialization thread
void *main_thread(void *) {
    // Load the anogs.so library
    anogs = Tools::GetBaseAddress("libanogs.so");
    while (!anogs) {
        anogs = Tools::GetBaseAddress("libanogs.so");
        sleep(1);
    }

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
    
    // Initialize name table
    FName::GNames = GetGNames();
    while (!FName::GNames) {
        FName::GNames = GetGNames();
        sleep(1);
    }
    
    // Initialize object array
    UObject::GUObjectArray = (FUObjectArray*)(Cheat::libUE4Base + Cheat::GUObject_Offset);
    
    // Hook input events
    orig_onInputEvent = decltype(orig_onInputEvent)(g_App->onInputEvent);
    g_App->onInputEvent = onInputEvent;
    
    // Initialize system offsets
    initOffset();
    
    // Set up EGL and ProcessEvent hooks
    Tools::Hook(
        (void*)DobbySymbolResolver(OBFUSCATE("/system/lib/libEGL.so"), OBFUSCATE("eglSwapBuffers")),
        (void*)_eglSwapBuffers,
        (void**)&orig_eglSwapBuffers
    );
    
    Tools::Hook(
        (void*)(Cheat::libUE4Base + Cheat::ProcessEvent_Offset),
        (void*)hkProcessEvent,
        (void**)&oProcessEvent
    );
    
    return nullptr;
}

// Entry point - constructor is called when library is loaded
__attribute__((constructor)) void _init() {
    // IBR Banner - Logo display on initialization
    LOGI(OBFUSCATE("╔═══════════════════════════════════════════╗"));
    LOGI(OBFUSCATE("║       IBR PREMIUM GAME BYPASS v4.2.1      ║"));
    LOGI(OBFUSCATE("║             BY SAIAIKA 2025               ║"));
    LOGI(OBFUSCATE("╚═══════════════════════════════════════════╝"));

    // Create main thread
    pthread_t t;
    pthread_create(&t, NULL, main_thread, NULL);
    
    // Create iPad view thread
    pthread_t ipad_t;
    pthread_create(&ipad_t, NULL, ipad_thread, NULL);
}
