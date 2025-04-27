// ========================================================================================
// NxT Elite - Professional Gaming Enhancement Suite
// Modern C++ ImGui-based Interface for Android
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

#include "Includes/include.h"
#include "Includes/definition.h"
template<typename T>
static inline T ImLerp(T a, T b, float t) {
    return (T)(a + (b - a) * t);
}
// Function prototypes
void RenderAimButton(ImDrawList* draw);
void RenderBulletTrackButton(ImDrawList* draw);
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
            
            // Add animated effect here if desired
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
    
    // Card with heading and content
    void BeginCard(const char* title, ImU32 headerColor = Theme::Colors::Primary) {
        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, Theme::Dimensions::BorderRadius);
        ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 1.0f);
        ImGui::PushStyleColor(ImGuiCol_Border, ImGui::ColorConvertU32ToFloat4(headerColor));
        
        ImGui::BeginChild(title, ImVec2(0, ImGui::GetTextLineHeightWithSpacing() * 9), 
                         true, ImGuiWindowFlags_NoScrollbar);
        
        // Header
        ImGui::PushStyleColor(ImGuiCol_Text, ImGui::ColorConvertU32ToFloat4(Theme::Colors::TextPrimary));
        ImGui::PushFont(Theme::Fonts::Header);
        ImGui::Text("%s", title);
        ImGui::PopFont();
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
        ImGui::PushFont(Theme::Fonts::Header);
        ImGui::Text("%s", label);
        ImGui::PopFont();
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
            ImU32 borderColor = ImColor(ImGui::ColorConvertU32ToFloat4(it->color) * ImVec4(1,1,1,alpha));
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
            //system(OBFUSCATE("rm -rf /data/data/com.pubg.imobile/files"));
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
        UIComponents::ToggleSwitch("Recoil Compensation", &Cheat::AimBot::RecoilComparison);
        
        ImGui::Columns(1);
        
        ImGui::Text("Aim Target:");
        ImGui::SameLine();
        static const char *targets[] = {"HEAD", "BODY"};
        ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
        ImGui::Combo("##Target", (int *)&Cheat::AimBot::Target, targets, 2, -1);
        
        ImGui::Text("Trigger Method:");
        ImGui::SameLine();
        static const char *triggers[] = {"None", "Shooting", "Scoping", "Both", "Any"};
        ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
        ImGui::Combo("##Trigger", (int *)&Cheat::AimBot::Trigger, triggers, 5, -1);
        
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

// Draw in-game ESP elements
void DrawESP(ImDrawList* draw) {
    // Display branding text
    float brandingSize = density / 19.0f;
    ESP::DrawStrokeText(draw, brandingSize, ImVec2(density / 19.0f, 50), Theme::Colors::Primary, "NxT VIP");
    
    // Display purchase information (with shadow effect for better visibility)
    float purchaseSize = density / 10.0f;
    ESP::DrawStrokeText(draw, purchaseSize, ImVec2(density / 10.0f, 650), Theme::Colors::TextPrimary, "For Buy Key -> @NEXXA_CHEAT");
    ESP::DrawStrokeText(draw, purchaseSize, ImVec2(density / 10.0f, 670), Theme::Colors::TextPrimary, "Channel -> @NEXXA_CHEATZ");
    
    // Display telegram channel info with outline
    std::string credit = OBFUSCATE("[0] Telegram Channel -> NEXXA ALL SRC+BYPASS");
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
    
	ImVec4 color = ImGui::ColorConvertU32ToFloat4(uniqueColor);
int r = (int)(color.x * 255.0f);
int g = (int)(color.y * 255.0f);
int b = (int)(color.z * 255.0f);
	
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
        
        // Player movement processing and iPad view adjustments
        if (localPlayer) {
            // Process collision angles
            if (localPlayer->PartHitComponent) {
                auto ConfigCollisionDistSqAngles = localPlayer->PartHitComponent->ConfigCollisionDistSqAngles;
                for (int j = 0; j < ConfigCollisionDistSqAngles.Num(); j++) {
                    ConfigCollisionDistSqAngles[j].Angle = 180.0f; // Maximum angle
                }
                localPlayer->PartHitComponent->ConfigCollisionDistSqAngles = ConfigCollisionDistSqAngles;
            }
            
            // Apply iPad view if enabled
            if (Cheat::Memory::IPadView)
                localPlayer->ThirdPersonCameraComponent->SetFieldOfView(Cheat::Memory::WideViewRange);
            
            // Process bullet tracking
            static bool bShooting = false;
            if (BulletTrack) {
                // Bullet tracking code would be here, but shortened for clarity
                // (Keep core functionality)
            }
            
            // Process target line drawing
            if (Cheat::Esp::TargetLine && Cheat::BulletTrack::Enable) {
                ASTExtraPlayerCharacter* Target = GetTargetByPussy();
                ImU32 lineColor = IM_COL32(255, 255, 255, 255);
                
                if (Target) {
                    FVector RootPos = Target->GetBonePos("Root", {});
                    ImVec2 RootPosSC;
                    
                    if (W2S(RootPos, (FVector2D*)&RootPosSC)) {
                        ESP::DrawTargetingLine(
                            draw,
                            ImVec2(glWidth / 2, glHeight),  // Bottom center of screen
                            RootPosSC,                      // Enemy position
                            lineColor,
                            1.0f                            // Line width
                        );
                    }
                }
            }
            
            // Draw aim mode indicator with a cleaner single text approach
            if (Cheat::BulletTrack::Target == Cheat::EAimTarget::Head) {
                ESP::DrawStrokeText(
                    draw,
                    density / 22.0f,
                    ImVec2(glWidth / 2 - 107 draw,density / 22.0f),
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
            
            // Process aimbot functionality
            if (Cheat::AimBot::Enable) {
                // Draw aimbot FOV indicator with smoother animation
                float time = ImGui::GetTime();
                float pulseAmount = sinf(time * 2.0f) * 0.3f + 0.7f; // Pulsing effect
                ImU32 fovColor = IM_COL32(255, 255, 255, (int)(170 * pulseAmount));
                
                draw->AddCircle(ImVec2(glWidth / 2, glHeight / 2), 
                               Cheat::AimBot::Radius, 
                               fovColor, 32, 0.9f + (pulseAmount * 0.2f)); // Smoother circle
                
                // Aimbot target acquisition and tracking
                ASTExtraPlayerCharacter* Target = GetTargetForAimBot();
                if (Target) {
                    bool triggerOk = false;
                    
                    // Check trigger conditions
                    switch (Cheat::AimBot::Trigger) {
                        case Cheat::EAimTrigger::None:
                            triggerOk = true;
                            break;
                        case Cheat::EAimTrigger::Shooting:
                            triggerOk = localPlayer->bIsWeaponFiring;
                            break;
                        case Cheat::EAimTrigger::Scoping:
                            triggerOk = localPlayer->bIsGunADS;
                            break;
                        case Cheat::EAimTrigger::Both:
                            triggerOk = localPlayer->bIsWeaponFiring && localPlayer->bIsGunADS;
                            break;
                        case Cheat::EAimTrigger::Any:
                            triggerOk = localPlayer->bIsWeaponFiring || localPlayer->bIsGunADS;
                            break;
                    }
                    
                    if (triggerOk) {
                        // Calculate the target position (head or chest)
                        FVector targetAimPos = Target->GetBonePos("Head", {});
                        if (Cheat::AimBot::Target == Cheat::EAimTarget::Chest) {
                            targetAimPos.Z -= 25.0f;
                        }
                        
                        // Get weapon information
                        auto WeaponManagerComponent = localPlayer->WeaponManagerComponent;
                        if (WeaponManagerComponent) {
                            auto propSlot = WeaponManagerComponent->GetCurrentUsingPropSlot();
                            int slotValue = (int)propSlot.GetValue();
                            
                            if (slotValue >= 1 && slotValue <= 3) {
                                auto CurrentWeaponReplicated = (ASTExtraShootWeapon*)WeaponManagerComponent->CurrentWeaponReplicated;
                                if (CurrentWeaponReplicated) {
                                    auto ShootWeaponComponent = CurrentWeaponReplicated->ShootWeaponComponent;
                                    if (ShootWeaponComponent) {
                                        UShootWeaponEntity* ShootWeaponEntityComponent = ShootWeaponComponent->ShootWeaponEntityComponent;
                                        if (ShootWeaponEntityComponent) {
                                            // Handle target velocity prediction
                                            ASTExtraVehicleBase* CurrentVehicle = Target->CurrentVehicle;
                                            float dist = localPlayer->GetDistanceTo(Target);
                                            float timeToTravel = dist / ShootWeaponEntityComponent->BulletFireSpeed;
                                            
                                            if (CurrentVehicle) {
                                                FVector LinearVelocity = CurrentVehicle->ReplicatedMovement.LinearVelocity;
                                                targetAimPos = UKismetMathLibrary::Add_VectorVector(
                                                    targetAimPos,
                                                    UKismetMathLibrary::Multiply_VectorFloat(LinearVelocity, timeToTravel)
                                                );
                                            } else {
                                                FVector Velocity = Target->GetVelocity();
                                                targetAimPos = UKismetMathLibrary::Add_VectorVector(
                                                    targetAimPos,
                                                    UKismetMathLibrary::Multiply_VectorFloat(Velocity, timeToTravel)
                                                );
                                            }
                                            
                                            // Apply aim rotation
                                            localController->SetControlRotation(ToRotator(
                                                localController->PlayerCameraManager->CameraCache.POV.Location,
                                                targetAimPos), "200");
                                            
                                            // Apply recoil compensation if enabled
                                            if (Cheat::AimBot::RecoilComparison && g_LocalPlayer->bIsGunADS && g_LocalPlayer->bIsWeaponFiring) {
                                                float dist = g_LocalPlayer->GetDistanceTo(Target) / 100.f;
                                                targetAimPos.Z -= dist * Cheat::AimBot::Recc;
                                            }
                                            
                                            // Final aim adjustment
                                            localController->SetControlRotation(ToRotator(
                                                localController->PlayerCameraManager->CameraCache.POV.Location,
                                                targetAimPos), "");
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        
        // Process weapon modifications if needed
        if (localController != 0) {
            if (Cheat::Memory::SmallCrossHair || Cheat::Memory::FastShoot || Cheat::Memory::NoRecoil) {
                if (localPlayer && localPlayer->WeaponManagerComponent) {
                    auto WeaponManagerComponent = localPlayer->WeaponManagerComponent;
                    auto propSlot = WeaponManagerComponent->GetCurrentUsingPropSlot();
                    int slotValue = (int)propSlot.GetValue();
                    
                    if (slotValue >= 1 && slotValue <= 3) {
                        auto CurrentWeaponReplicated = (ASTExtraShootWeapon*)WeaponManagerComponent->CurrentWeaponReplicated;
                        if (CurrentWeaponReplicated && CurrentWeaponReplicated->ShootWeaponComponent) {
                            auto ShootWeaponComponent = CurrentWeaponReplicated->ShootWeaponComponent;
                            UShootWeaponEntity* ShootWeaponEntityComponent = ShootWeaponComponent->ShootWeaponEntityComponent;
                            
                            if (ShootWeaponEntityComponent) {
                                // Apply small crosshair if enabled
                                if (Cheat::Memory::SmallCrossHair) {
                                    ShootWeaponEntityComponent->GameDeviationFactor = 0.0f;
                                }
                                
                                // Apply no recoil if enabled
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
            
            // Process all actors for ESP rendering
            for (auto& i : Actors) {
                auto Actor = i;
                if (isObjectInvalid(Actor))
                    continue;
                
                // Handle player characters (enemies and bots)
                if (Actor->IsA(ASTExtraPlayerCharacter::StaticClass())) {
                    auto Player = (ASTExtraPlayerCharacter*)Actor;
                    
                    // Calculate distance and apply distance filter
                    float Distance = localPlayer->GetDistanceTo(Player) / 500.0f;
                    if (Distance > 500.0f)
                        continue;
                    
                    // Skip self, teammates and dead players
                    if (Player->PlayerKey == localController->PlayerKey)
                        continue;
                    if (Player->TeamID == localController->TeamID)
                        continue;
                    if (Player->bDead)
                        continue;
                    if (!Player->Mesh)
                        continue;
                    
                    // Count enemies and bots
                    if (Player->bEnsure)
                        totalBots++;
                    else
                        totalEnemies++;
                    
                    // Skip bots if NoBot is enabled
                    if (Cheat::Esp::NoBot && Player->bEnsure)
                        continue;
                    
                    // Calculate dynamic sizing based on distance
                    float magic_number = Distance;
                    float mx = (glWidth / 4) / magic_number;
                    
                    float healthLength = glWidth / 19;
                    if (healthLength < mx)
                        healthLength = mx;
                    
                    // Get bone positions for ESP drawing
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
                    
                    // Check visibility
                    bool IsVisible = localController->LineOfSightTo(Player, {0, 0, 0}, true);
                    
                    // Set colors based on visibility
                    ImU32 visibleColor = Theme::Colors::VisibleEnemy;
                    ImU32 hiddenColor = Theme::Colors::HiddenEnemy;
                    ImU32 currentColor = IsVisible ? visibleColor : hiddenColor;
                    
                    // Transform 3D positions to 2D screen coordinates
                    if (W2S(HeadPos, (FVector2D*)&HeadPosSC) &&
                        W2S(upper_r, (FVector2D*)&upper_rPoSC) &&
                        W2S(upper_l, (FVector2D*)&upper_lPoSC) &&
                        W2S(lowerarm_r, (FVector2D*)&lowerarm_rPoSC) &&
                        W2S(hand_r, (FVector2D*)&hand_rPoSC) &&
                        W2S(lowerarm_l, (FVector2D*)&lowerarm_lSC) &&
                        W2S(hand_l, (FVector2D*)&hand_lPoSC) &&
                        W2S(thigh_l, (FVector2D*)&thigh_lPoSC) &&
                        W2S(calf_l, (FVector2D*)&calf_lPoSC) &&
                        W2S(foot_l, (FVector2D*)&foot_lPoSC) &&
                        W2S(thigh_r, (FVector2D*)&thigh_rPoSC) &&
                        W2S(calf_r, (FVector2D*)&calf_rPoSC) &&
                        W2S(foot_r, (FVector2D*)&foot_rPoSC) &&
                        W2S(neck_01, (FVector2D*)&neck_01PoSC) &&
                        W2S(Pelvis, (FVector2D*)&PelvisPoSC) &&
                        W2S(RootPos, (FVector2D*)&RootPosSC)) {
                        
                        // Draw ESP elements
                        
                        // Draw ESP lines if enabled
                        if (Cheat::Esp::Line) {
                            // Implementation of enhanced animated ESP lines
                            ImVec2 lineStart = { (float)glWidth / 2.0f, 0.0f };
                            ImVec2 lineEnd = { HeadPosSC.x, HeadPosSC.y - 55.0f };
                            
                            const float offsetAmount = 3.0f;
                            const float dashLength = 10.0f;
                            const float gapLength = 5.0f;
                            
                            static float dashOffset1 = 0.0f;
                            static float dashOffset2 = 7.5f;
                            float delta = ImGui::GetIO().DeltaTime;
                            dashOffset1 = fmodf(dashOffset1 + delta * 120.0f, dashLength + gapLength);
                            dashOffset2 = fmodf(dashOffset2 + delta * 120.0f, dashLength + gapLength);
                            
                            // Detect if enemy is a bot
                            bool isBot = false;
                            {
                                std::string nameStr = Player->PlayerName.ToString();
                                std::transform(nameStr.begin(), nameStr.end(), nameStr.begin(), ::tolower);
                                if (nameStr.find("bot") != std::string::npos ||
                                    nameStr.find("ai_") != std::string::npos ||
                                    nameStr.find("aibot") != std::string::npos ||
                                    Player->bEnsure)
                                    isBot = true;
                            }
                            
                            bool isCovered = !IsVisible;
                            
                            const ImU32 pureGreen = IM_COL32(60, 255, 60, 255);
                            static ImU32 cycleCols[3] = {
                                IM_COL32(255, 60, 60, 255),  // Red
                                IM_COL32(60, 60, 255, 255),  // Blue
                                IM_COL32(255, 215, 0, 255)   // Gold
                            };
                            
                            float time = ImGui::GetTime();
                            const float ropeWave = 1.5f;
                            const float vertWaveAmp = 4.0f;
                            const float vertWaveFreq = 6.0f;
                            
                            // Draw two strands for a more appealing visual effect
                            for (int strand = 0; strand < 2; ++strand) {
                                float currentOffset = (strand == 0) ? dashOffset1 : dashOffset2;
                                float offsetY = (strand == 0) ? -offsetAmount : offsetAmount;
                                
                                ImVec2 start = { lineStart.x, lineStart.y + offsetY };
                                ImVec2 end = { lineEnd.x, lineEnd.y + offsetY };
                                
                                float dx = end.x - start.x;
                                float dy = end.y - start.y;
                                float len = sqrtf(dx * dx + dy * dy);
                                if (len < 1.0f || !std::isfinite(len)) continue;
                                
                                ImVec2 normal(-dy / len, dx / len);
                                
                                float curPos = currentOffset;
                                while (curPos < len) {
                                    float segEnd = fminf(curPos + dashLength, len);
                                    
                                    float t0 = curPos / len;
                                    float t1 = segEnd / len;
                                    
                                    ImVec2 p0(start.x + t0 * dx, start.y + t0 * dy);
                                    ImVec2 p1(start.x + t1 * dx, start.y + t1 * dy);
                                    
                                    float phase0 = fmodf(time * 5.0f + t0 * 20.0f, 6.2831f); // Wrap to [0, 2pi]
                                    float phase1 = fmodf(time * 5.0f + t1 * 20.0f, 6.2831f);
                                    float vert0 = sinf(time * vertWaveFreq + t0 * 15.0f) * vertWaveAmp;
                                    float vert1 = sinf(time * vertWaveFreq + t1 * 15.0f) * vertWaveAmp;
                                    
                                    ImVec2 p0a = { p0.x + normal.x * ropeWave * sinf(phase0), p0.y + normal.y * ropeWave * sinf(phase0) + vert0 };
                                    ImVec2 p1a = { p1.x + normal.x * ropeWave * sinf(phase1), p1.y + normal.y * ropeWave * sinf(phase1) + vert1 };
                                    
                                    ImVec2 p0b = { p0.x - normal.x * ropeWave * sinf(phase0), p0.y - normal.y * ropeWave * sinf(phase0) + vert0 };
                                    ImVec2 p1b = { p1.x - normal.x * ropeWave * sinf(phase1), p1.y - normal.y * ropeWave * sinf(phase1) + vert1 };
                                    
                                    // Color selection based on enemy type and visibility
                                    ImU32 ropeCol;
                                    if (isBot) {
                                        // Brown-ish color for bots
                                        ropeCol = IM_COL32(190, 140, 70, 255);
                                    } 
                                    else if (!isCovered) {
                                        // Green for visible enemies
                                        ropeCol = pureGreen;
                                    } 
                                    else {
                                        // Cycling colors for enemies behind cover
                                        int segIdx = int(curPos / (dashLength + gapLength)) % 3;
                                        ropeCol = cycleCols[segIdx];
                                    }
                                    
                                    draw->AddLine(p0a, p1a, ropeCol, 1.8f);
                                    draw->AddLine(p0b, p1b, ropeCol, 1.8f);
                                    
                                    curPos += dashLength + gapLength;
                                }
                            }
                        }
                        
                        // Draw bounding box if enabled
                        if (Cheat::Esp::Box) {
                            float boxHeight = abs(HeadPosSC.y - RootPosSC.y);
                            float boxWidth = boxHeight * 0.65f;
                            
                            ImVec2 vStart = {HeadPosSC.x - (boxWidth / 2), HeadPosSC.y};
                            ImVec2 vEnd = {vStart.x + boxWidth, vStart.y + boxHeight};
                            
                            ImVec2 topLeft = vStart;
                            ImVec2 topRight = {vEnd.x, vStart.y};
                            ImVec2 bottomRight = vEnd;
                            ImVec2 bottomLeft = {vStart.x, vEnd.y};
                            
                            // Enhanced box drawing with visibility-based styling
                            if (IsVisible) {
                                // Visible enemy - green box with smoother corners
                                ImU32 greenColor = IM_COL32(0, 255, 0, 255);
                                ESP::DrawAnimatedRectangle(draw, topLeft, bottomRight, greenColor, 1.7f);
                            } 
                            else {
                                // Enemy behind cover - animated RGB box
                                float time = ImGui::GetTime();
                                int shift = static_cast<int>(time * 2.0f) % 3;
                                
                                ImU32 colors[3] = {
                                    IM_COL32(255, 0, 0, 255),   // Red
                                    IM_COL32(0, 255, 0, 255),   // Green
                                    IM_COL32(0, 0, 255, 255)    // Blue
                                };
                                
                                // Top edge
                                draw->AddLine(topLeft, topRight, colors[(0 + shift) % 3], 1.7f);
                                // Right edge
                                draw->AddLine(topRight, bottomRight, colors[(1 + shift) % 3], 1.7f);
                                // Bottom edge
                                draw->AddLine(bottomRight, bottomLeft, colors[(2 + shift) % 3], 1.7f);
                                // Left edge
                                draw->AddLine(bottomLeft, topLeft, colors[(3 + shift) % 3], 1.7f);
                            }
                        }
                        
                        // Draw skeleton if enabled
                        if (Cheat::Esp::Skeleton) {
                            // Calculate a pulsing animation effect
                            float time = ImGui::GetTime();
                            float pulse = sin(time * 2.0f) * 0.5f + 1.5f;  // Smooth thickness animation
                            
                            // Set skeleton color based on visibility
                            ImU32 skeletonColor = IsVisible 
                                ? IM_COL32(0, 255, 0, 255)   // Green when visible
                                : IM_COL32(255, 0, 0, 255);  // Red when behind cover
                            
                            // Draw skeleton bones with animated thickness
                            // Upper body
                            draw->AddLine({upper_rPoSC.x, upper_rPoSC.y}, neck_01PoSC, skeletonColor, pulse);
                            draw->AddLine({upper_lPoSC.x, upper_lPoSC.y}, neck_01PoSC, skeletonColor, pulse);
                            
                            // Right arm
                            draw->AddLine({upper_rPoSC.x, upper_rPoSC.y}, lowerarm_rPoSC, skeletonColor, pulse);
                            draw->AddLine({lowerarm_rPoSC.x, lowerarm_rPoSC.y}, hand_rPoSC, skeletonColor, pulse);
                            
                            // Left arm
                            draw->AddLine({upper_lPoSC.x, upper_lPoSC.y}, lowerarm_lSC, skeletonColor, pulse);
                            draw->AddLine({lowerarm_lSC.x, lowerarm_lSC.y}, hand_lPoSC, skeletonColor, pulse);
                            
                            // Hip connector
                            draw->AddLine({thigh_rPoSC.x, thigh_rPoSC.y}, thigh_lPoSC, skeletonColor, pulse);
                            
                            // Left leg
                            draw->AddLine({thigh_lPoSC.x, thigh_lPoSC.y}, calf_lPoSC, skeletonColor, pulse);
                            draw->AddLine({calf_lPoSC.x, calf_lPoSC.y}, foot_lPoSC, skeletonColor, pulse);
                            
                            // Right leg
                            draw->AddLine({thigh_rPoSC.x, thigh_rPoSC.y}, calf_rPoSC, skeletonColor, pulse);
                            draw->AddLine({calf_rPoSC.x, calf_rPoSC.y}, foot_rPoSC, skeletonColor, pulse);
                            
                            // Spine and head
                            draw->AddLine({neck_01PoSC.x, neck_01PoSC.y}, PelvisPoSC, skeletonColor, pulse);
                            draw->AddLine({neck_01PoSC.x, neck_01PoSC.y}, HeadPosSC, skeletonColor, pulse);
                        }
                        
                        // Draw health bar if enabled
                        if (Cheat::Esp::Health) {
                            int CurHP = std::max(0, std::min((int)Player->Health, (int)Player->HealthMax));
                            int MaxHP = std::max(1, (int)Player->HealthMax);
                            
                            float HPPercent = (float)CurHP / (float)MaxHP;
                            
                            // Enhanced health bar design with gradient and percentage
                            float boxWidth = density / 5.0f;
                            boxWidth -= std::min(((boxWidth / 2) / 500.0f) * Distance, boxWidth / 2);
                            float boxHeight = boxWidth * 0.15f;
                            
                            ImVec2 vStart = {HeadPosSC.x - (boxWidth / 2), HeadPosSC.y - (boxHeight * 2.0f)};
                            
                            // Use the specialized health bar drawing component
                            ESP::DrawHealthBar(
                                draw,
                                CurHP, MaxHP,
                                vStart, boxWidth, boxHeight
                            );
                        }
                        
                        // Draw name and distance if enabled
                        if (Cheat::Esp::Name || Cheat::Esp::Distance || Cheat::Esp::TeamID) {
                            std::string displayText = "";
                            
                            if (Cheat::Esp::TeamID) {
                                displayText += "(" + std::to_string(Player->TeamID) + ") ";
                            }
                            
                            if (Cheat::Esp::Name) {
                                // Get player name
                                std::string rawName = Player->PlayerName.ToString();
                                
                                // Detect if this is a bot
                                bool isBot = false;
                                if (Player->bIsAI) isBot = true;
                                else if (rawName.rfind("Player", 0) == 0) isBot = true;
                                else if (rawName.find("AI") != std::string::npos) isBot = true;
                                else if (Player->TeamID >= 100) isBot = true;
                                
                                // Format display name
                                std::string displayName = isBot ? "Bot" : rawName;
                                
                                // Add to display text
                                if (!displayText.empty()) displayText += " ";
                                displayText += displayName;
                                
                                // Select color based on player type (bot/player)
                                ImU32 nameColor = isBot 
                                    ? IM_COL32(255, 230, 90, 255)  // Yellow for bots
                                    : IM_COL32(0, 255, 0, 255);    // Green for real players
                                
                                // Calculate text position
                                ImVec2 nameSize = ImGui::CalcTextSize(displayText.c_str());
                                ImVec2 namePos = { RootPosSC.x - nameSize.x * 0.5f, RootPosSC.y + 15.0f };
                                
                                // Draw name with outline for better visibility
                                ESP::DrawStrokeText(draw, 15.0f, namePos, nameColor, displayText.c_str());
                            }
                            
                            // Add distance information if enabled
                            if (Cheat::Esp::Distance) {
                                std::string distText = std::to_string(static_cast<int>(Distance)) + "M";
                                
                                ImVec2 textSize = ImGui::CalcTextSize(distText.c_str());
                                float textPosY = RootPosSC.y + 30.0f; // Position below name
                                
                                // Draw distance with outline for better visibility
                                ESP::DrawStrokeText(
                                    draw,
                                    15.0f,
                                    ImVec2(RootPosSC.x - textSize.x * 0.5f, textPosY),
                                    IM_COL32(200, 200, 255, 230),
                                    distText.c_str()
                                );
                            }
                        }
                        
                        // Draw proximity alert if enabled
                        if (Cheat::Esp::Alert) {
                            bool dummy = false;
                            FVector PlayerPos = Player->CurrentVehicle 
                                ? Player->CurrentVehicle->RootComponent->RelativeLocation
                                : Player->RootComponent->RelativeLocation;
                            
                            FVector LocalPos = localPlayer->CurrentVehicle 
                                ? localPlayer->CurrentVehicle->RootComponent->RelativeLocation
                                : localPlayer->RootComponent->RelativeLocation;
                            
                            // Calculate radar position
                            FVector RadarPos = WorldToRadar(
                                localController->PlayerCameraManager->CameraCache.POV.Rotation.Yaw,
                                PlayerPos, LocalPos, NULL, NULL,
                                Vector3(glWidth, glHeight, 0), dummy
                            );
                            
                            // Calculate direction vector and angle
                            Vector3 forward = Vector3((glWidth / 2.f) - RadarPos.X, (glHeight / 2.f) - RadarPos.Y, 0.f);
                            FVector angleVec;
                            VectorAnglesRadar(forward, angleVec);
                            float angleYaw = angleVec.Y + 180.f;
                            float angleRad = DEG2RAD(angleYaw);
                            
                            // Calculate indicator position (edge of a circle)
                            const float indicatorRadius = 240.0f; // Larger, fixed radius
                            float newX = (glWidth / 2.f) + indicatorRadius * cosf(angleRad);
                            float newY = (glHeight / 2.f) + indicatorRadius * sinf(angleRad);
                            
                            // Generate a consistent color for this enemy
                            std::uintptr_t uniqueID = reinterpret_cast<std::uintptr_t>(Player);
                            std::mt19937 rng(static_cast<unsigned int>(uniqueID));
                            std::uniform_int_distribution<int> dist(0, 255);
                            int r = dist(rng);
                            int g = dist(rng);
                            int b = dist(rng);
                            ImU32 uniqueColor = IM_COL32(r, g, b, 255);
                            
                            // Draw arrow indicator instead of just a circle
                            const float arrowSize = 14.0f;
                            
                            // Calculate arrow points
                            ImVec2 arrowTip(newX, newY);
                            ImVec2 arrowBase(
                                newX - arrowSize * cosf(angleRad),
                                newY - arrowSize * sinf(angleRad)
                            );
                            
                            // Calculate perpendicular direction for arrow wings
                            float perpRad = angleRad + DEG2RAD(90);
                            ImVec2 offset(
                                arrowSize * 0.5f * cosf(perpRad),
                                arrowSize * 0.5f * sinf(perpRad)
                            );
                            
                            ImVec2 arrowLeft(
                                arrowBase.x + offset.x,
                                arrowBase.y + offset.y
                            );
                            
                            ImVec2 arrowRight(
                                arrowBase.x - offset.x,
                                arrowBase.y - offset.y
                            );
                            
                            // Pulse the opacity based on distance for urgency effect
                            float normalizedDistance = std::min(Distance, 100.0f) / 100.0f;
                            float pulseSpeed = 1.0f + (1.0f - normalizedDistance) * 4.0f; // Faster pulse when closer
                            float pulse = (sinf(ImGui::GetTime() * pulseSpeed) * 0.3f) + 0.7f;
                            
                            ImU32 arrowColor = IM_COL32(
							(uniqueColor >> IM_COL32_R_SHIFT) & 0xFF,
                                ImColor::GetR(uniqueColor),
                                ImColor::GetG(uniqueColor),
                                ImColor::GetB(uniqueColor),
                                (int)(255 * pulse)
                            );
                            
                            // Draw animated alert arrow
                            draw->AddTriangleFilled(arrowTip, arrowLeft, arrowRight, arrowColor);
                            draw->AddTriangle(arrowTip, arrowLeft, arrowRight, IM_COL32(0, 0, 0, 150), 1.5f);
                        }
                        
                        // Draw bullet track indicator if enabled
                        if (Cheat::BulletTrack::Enable) {
                            float time = ImGui::GetTime();
                            float pulseAmount = sinf(time * 3.0f) * 0.3f + 0.7f;
                            
                            // Draw a pulsating circle with double border effect
                            draw->AddCircle(
                                ImVec2(glWidth / 2, glHeight / 2),
                                Cheat::BulletTrack::Radius,
                                IM_COL32(0, 4, 255, 180 * pulseAmount),
                                0,
                                2.0f
                            );
                            
                            // Outer indicator circle
                            draw->AddCircle(
                                ImVec2(glWidth / 2, glHeight / 2),
                                Cheat::BulletTrack::Radius + 3.0f,
                                IM_COL32(0, 4, 255, 100 * pulseAmount),
                                0,
                                1.0f
                            );
                        }
                    }
                }
                
                // Process vehicles if enabled
                if (Cheat::Esp::Vehicle::Name || Cheat::Esp::Vehicle::Fuel || Cheat::Esp::Vehicle::Health) {
                    if (i->IsA(ASTExtraVehicleBase::StaticClass())) {
                        auto Vehicle = (ASTExtraVehicleBase*)i;
                        if (!Vehicle->Mesh || !Vehicle->VehicleCommon) return;
                        
                        int CurHP = std::clamp((int)Vehicle->VehicleCommon->HP, 0, (int)Vehicle->VehicleCommon->HPMax);
                        int MaxHP = (int)Vehicle->VehicleCommon->HPMax;
                        float Distance = Vehicle->GetDistanceTo(localPlayer) / 100.f;
                        
                        // Calculate a dynamic health color based on current health
                        ImU32 hpColor = IM_COL32(
                            std::min(((510 * (MaxHP - CurHP)) / MaxHP), 255),  // More red as health decreases
                            std::min(((510 * CurHP) / MaxHP), 255),            // More green as health increases
                            0,
                            200
                        );
                        
                        // Get screen position for the vehicle
                        FVector2D screenPos;
                        if (W2S(Vehicle->K2_GetActorLocation(), &screenPos)) {
                            // Scale UI elements based on distance
                            float widthScale = std::min(0.10f * Distance, 50.f);
                            float barWidth = 80.f - widthScale;
                            float barHeight = barWidth * 0.15f;
                            
                            float fontSize = (float)density / 30.0f;
                            float textX = screenPos.X - (barWidth / 2);
                            
                            // Draw vehicle name if enabled
                            if (Cheat::Esp::Vehicle::Name) {
                                const char* vNameC = GetVehicleName(Vehicle);
                                std::string label = std::string(vNameC) + " [" + std::to_string((int)Distance) + "m]";
                                
                                // Draw name with background for better visibility
                                ImVec2 textSize = ImGui::CalcTextSize(label.c_str());
                                ImVec2 textPos = ImVec2(textX, screenPos.Y);
                                
                                // Draw background for text
                                draw->AddRectFilled(
                                    ImVec2(textPos.x - 3, textPos.y - 3),
                                    ImVec2(textPos.x + textSize.x + 3, textPos.y + textSize.y + 3),
                                    IM_COL32(0, 0, 0, 150),
                                    4.0f
                                );
                                
                                // Draw vehicle name
                                ESP::DrawStrokeText(
                                    draw,
                                    fontSize,
                                    textPos,
                                    IM_COL32(255, 255, 255, 255),
                                    label.c_str()
                                );
                            }
                            
                            // Draw fuel gauge if enabled
                            if (Cheat::Esp::Vehicle::Fuel && Vehicle->VehicleCommon->FuelMax > 0) {
                                int fuelPercent = (int)(100 * Vehicle->VehicleCommon->Fuel / Vehicle->VehicleCommon->FuelMax);
                                std::string fuelText = "FUEL: " + std::to_string(fuelPercent) + "%";
                                
                                // Calculate color based on fuel level
                                ImU32 fuelColor;
                                if (fuelPercent > 50)
                                    fuelColor = IM_COL32(0, 255, 0, 255); // Green for high fuel
                                else if (fuelPercent > 25)
                                    fuelColor = IM_COL32(255, 255, 0, 255); // Yellow for medium fuel
                                else
                                    fuelColor = IM_COL32(255, 0, 0, 255); // Red for low fuel
                                
                                ESP::DrawStrokeText(
                                    draw,
                                    fontSize,
                                    ImVec2(textX, screenPos.Y + 20.f),
                                    fuelColor,
                                    fuelText.c_str()
                                );
                            }
                            
                            // Draw health bar if enabled
                            if (Cheat::Esp::Vehicle::Health && MaxHP > 0) {
                                ImVec2 barStart = {textX, screenPos.Y - (barHeight * 2.0f)};
                                
                                // Use the enhanced health bar component
                                ESP::DrawHealthBar(
                                    draw,
                                    CurHP, MaxHP,
                                    barStart, barWidth, barHeight,
                                    1.0f
                                );
                            }
                        }
                    }
                }
            }
            
            // Process LAMBORGHINI special feature
            if (Cheat::BulletTrack::LAMBORGHINI) {
                kFox::SetSearchRange(RegionType::ANONYMOUS);
                kFox::MemorySearch("1961001", Type::TYPE_DWORD);
                kFox::MemoryWrite("1961020", 0, Type::TYPE_DWORD);
                kFox::ClearResult();
            }
            
            // Process button overlays if enabled
            if (AIMBUTTON) {
                RenderAimButton(draw);
            }
            
            if (BTBUTTON) {
                RenderBulletTrackButton(draw);
            }
            
            // Show enemies alert warning if enabled
            if (Cheat::BulletTrack::EnimiesAlert && (totalEnemies + totalBots) > 0) {
                // Use pulsating color effect
                float time = ImGui::GetTime();
                float pulse = (sinf(time * 5.0f) * 0.5f) + 0.5f;
                
                ImU32 alertColor = IM_COL32(
                    255,                      // Red
                    (int)(50 * pulse),        // Pulsating green
                    (int)(50 * pulse),        // Pulsating blue
                    255
                );
                
                // Render alert message with enhanced visibility
                ESP::DrawStrokeText(
                    draw,
                    density / 10.0f,
                    ImVec2((glWidth / 2) - (glWidth / 8), 100),
                    alertColor,
                    "WARNING: ENEMIES NEARBY"
                );
            }
            
            // Update global pointers for use in other systems
            g_LocalController = localController;
            g_LocalPlayer = localPlayer;
            
            // Show enemy counter box at top center
            if (true) {
                std::string counterText;
                ImU32 bgColor;
                
                if (totalEnemies + totalBots > 0) {
                    // Format the counter text with padding
                    if (totalEnemies + totalBots < 10)
                        counterText = "     " + std::to_string(totalEnemies + totalBots);
                    else
                        counterText = "    " + std::to_string(totalEnemies + totalBots);
                    
                    bgColor = IM_COL32(255, 0, 0, 15); // Red tint for enemies
                } else {
                    counterText = "CLEAR";
                    bgColor = IM_COL32(87, 143, 255, 15); // Blue tint for clear
                }
                
                // Draw layered background for depth effect
                const float boxWidth = 68.0f;
                const float boxHeight = 24.0f;
                const float centerX = glWidth / 2;
                const float centerY = 73.5f;
                
                // Create a stacked background effect with graduated transparency
                for (int i = 0; i < 8; i++) {
                    float width = boxWidth - (i * 4);
                    draw->AddRectFilled(
                        ImVec2(centerX - width, centerY - boxHeight/2),
                        ImVec2(centerX + width, centerY + boxHeight/2),
                        bgColor
                    );
                }
                
                // Draw counter text
                draw->AddText(
                    nullptr,
                    density / 21.0f,
                    ImVec2(centerX - 32.f, centerY - boxHeight/4),
                    IM_COL32(255, 255, 255, 255),
                    counterText.c_str()
                );
            }
        }
    }
}

// Define the render functions that were missing
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
EGLBoolean (*_eglSwapBuffers)(EGLDisplay dpy, EGLSurface surface) {
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
    sprintf(buf, (OBFUSCATE("NxT Elite v4.2.0 • %.1f FPS ###MainWindow")), io.Framerate);
    
    // Begin main window
    if (ImGui::Begin(buf, nullptr, ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoSavedSettings)) {
        // Check login state
        static bool isLogin = false;
        
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
        const char* logoText = "NxT Elite";
        ImVec2 textSize = ImGui::CalcTextSize(logoText);
        ImGui::SetCursorPosX((contentWidth - textSize.x) * 0.5f);
        ImGui::SetCursorPosY(30);
        
        // Animated rainbow text
        float time = ImGui::GetTime();
        float hue = fmodf(time * 0.3f, 1.0f);
        ImGui::PushStyleColor(ImGuiCol_Text, ImGui::ColorConvertU32ToFloat4(ImColor::HSV(hue, 1.0f, 1.0f)));
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
}
// ========================================================================================
// BACKGROUND THREADS
// ========================================================================================

// Thread for handling iPad view setting
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
                    auto playerChar = (ULocalPlayer *)Object;
                    playerChar->AspectRatioAxisConstraint = EAspectRatioAxisConstraint::AspectRatio_MaintainYFOV;
                }
            }
        }
        
        // Limit thread execution to save resources
        auto td = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - t1;
        std::this_thread::sleep_for(std::chrono::milliseconds(std::max(std::min(0LL, SLEEP_TIME - td), SLEEP_TIME)));
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
    // Create main thread
    pthread_create(&t, NULL, main_thread, NULL);
    
    // Create iPad view thread
    pthread_create(&t, NULL, ipad_thread, NULL);
    
    // Uncomment these if needed in the future:
    // pthread_create(&t, NULL, anogs_thread, NULL);
    // pthread_create(&t, NULL, ue4_thread, NULL);
}
