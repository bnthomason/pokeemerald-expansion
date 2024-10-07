#ifndef GUARD_BATTLE_STATBOOST_H
#define GUARD_BATTLE_STATBOOST_H

bool32 CanStatBoost(u32 battler);
bool32 IsStatBoosted(u32 battler);
void ApplyStatMultiplier(u32 battler, struct Pokemon* mon);
void ActivateStatBoost(u32 battler);
void UndoStatBoost(u32 battler);
bool32 IsMoveBlockedByMaxGuard(u32 move);
bool32 IsMoveBlockedByDynamax(u32 move);

u16 GetMaxMove(u32 battler, u32 baseMove);
u8 GetMaxMovePower(u32 move);
bool32 IsMaxMove(u32 move);
void ChooseDamageNonTypesString(u8 type);

void BS_UpdateStats(void);
void BS_JumpIfStatBoosted(void);

#endif //GUARD_BATTLE_STATBOOST_H