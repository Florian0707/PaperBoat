// File: src/battle/battle_actor.c

Actor* create_actor(ActorBlueprint* blueprint) {
    Actor* actor = heap_malloc(sizeof(*actor));
    // ... [Vanilla initialization code] ...

    // Apply global modifiers to enemy actors
    ApplyGlobalEnemyModifiers(actor);

    return actor;
}