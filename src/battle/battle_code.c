// File: src/battle/battle_code.c

void calc_enemy_damage_output(Evt* script, s32 initialDamage) {
    Actor* attacker = get_actor(script->ownerID);
    
    // Scale damage via global modifier calculation
    s32 scaledDamage = CalculateModifiedEnemyAttack(attacker, initialDamage);

    // Pass modified value into vanilla damage event pipeline
    evt_set_variable(script, LVar0, scaledDamage);
}