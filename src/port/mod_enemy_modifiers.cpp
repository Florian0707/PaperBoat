// File: src/port/mod_enemy_modifiers.cpp
#include <libultraship/libultraship.h>

void DrawGlobalModifierMenu() {
    if (ImGui::CollapsingHeader("Hard Mode: Global Enemy Modifiers")) {
        
        // Master Toggle
        bool hardMode = CVarGetInteger("gHardModeEnabled", 0);
        if (ImGui::Checkbox("Enable Hard Mode", &hardMode)) {
            CVarSetInteger("gHardModeEnabled", hardMode);
        }

        if (hardMode) {
            ImGui::Indent();

            // HP Multiplier Slider
            float hpMult = CVarGetFloat("gEnemyHpMultiplier", 1.50f);
            if (ImGui::SliderFloat("Enemy HP Multiplier", &hpMult, 1.0f, 3.0f, "%.2fx")) {
                CVarSetFloat("gEnemyHpMultiplier", hpMult);
            }

            // ATK Multiplier Slider
            float atkMult = CVarGetFloat("gEnemyAtkMultiplier", 1.25f);
            if (ImGui::SliderFloat("Enemy Attack Multiplier", &atkMult, 1.0f, 2.5f, "%.2fx")) {
                CVarSetFloat("gEnemyAtkMultiplier", atkMult);
            }

            // Defense Flat Bonus
            int defBonus = CVarGetInteger("gEnemyDefenseBonus", 0);
            if (ImGui::SliderInt("Flat Defense Bonus", &defBonus, 0, 3)) {
                CVarSetInteger("gEnemyDefenseBonus", defBonus);
            }

            ImGui::Unindent();
        }
    }
}