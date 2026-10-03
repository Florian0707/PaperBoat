// File: src/battle/hard_mode_modifiers.c
#include "common.h"
#include "battle/battle.h"

typedef struct {
    float hpMultiplier;      // e.g., 1.5f = +50% HP
    float atkMultiplier;     // e.g., 1.25f = +25% Attack
    s32 flatDefenseBonus;    // e.g., +1 Defense across the board
    float statusResistBonus; // Multiplier for status duration / chance
} GlobalEnemyModifiers;

// Fetch current values from PaperBoat CVar configuration
GlobalEnemyModifiers GetCurrentModifiers(void) {
    GlobalEnemyModifiers mods;
    
    // Fall back to default Hard Mode multipliers if specific CVars aren't set
    mods.hpMultiplier      = CVarGetFloat("gEnemyHpMultiplier", 1.50f);
    mods.atkMultiplier     = CVarGetFloat("gEnemyAtkMultiplier", 1.25f);
    mods.flatDefenseBonus  = CVarGetInteger("gEnemyDefenseBonus", 0);
    mods.statusResistBonus = CVarGetFloat("gEnemyStatusResistMultiplier", 1.50f);

    return mods;
}

// 1. Dynamic Attribute Hook (Triggered when an enemy spawns)
void ApplyGlobalEnemyModifiers(Actor* enemy) {
    if (!CVarGetInteger("gHardModeEnabled", 0)) {
        return;
    }

    // Never modify Mario or Partner actors
    if (enemy->flags & (ACTOR_FLAG_PLAYER | ACTOR_FLAG_PARTNER)) {
        return;
    }

    GlobalEnemyModifiers mods = GetCurrentModifiers();

    // Scale HP
    s32 scaledMaxHp = (s32)(enemy->maxHP * mods.hpMultiplier);
    if (scaledMaxHp < 1) scaledMaxHp = 1;
    
    enemy->maxHP = scaledMaxHp;
    enemy->curHP = scaledMaxHp;

    // Apply Flat Defense Bonus across element tables
    if (mods.flatDefenseBonus > 0 && enemy->defenseTable != NULL) {
        s32 i = 0;
        while (enemy->defenseTable[i].element != ELEMENT_END) {
            enemy->defenseTable[i].defense += mods.flatDefenseBonus;
            i++;
        }
    }
}

// 2. Incoming Damage Hook (Triggered when an enemy deals damage to player)
s32 CalculateModifiedEnemyAttack(Actor* attacker, s32 baseDamage) {
    if (!CVarGetInteger("gHardModeEnabled", 0)) {
        return baseDamage;
    }

    if (attacker->flags & (ACTOR_FLAG_PLAYER | ACTOR_FLAG_PARTNER)) {
        return baseDamage;
    }

    GlobalEnemyModifiers mods = GetCurrentModifiers();
    s32 finalDamage = (s32)(baseDamage * mods.atkMultiplier);

    // Guarantee at least 1 DMG if base damage was non-zero
    if (baseDamage > 0 && finalDamage < 1) {
        finalDamage = 1;
    }

    return finalDamage;
}