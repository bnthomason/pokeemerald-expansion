#ifndef GUARD_BATTLE_FACTORY_H
#define GUARD_BATTLE_FACTORY_H

//void CallBattleFactoryFunction(void);
//bool8 InBattleFactory(void);
void CreateIslandMon(const struct TrainerMon *fmon, u16 level, u8 fixedIV, u32 otID, u32 flags, struct Pokemon *dst);
void FillIslandBossParties(void);
//u8 GetNumPastRentalsRank(u8 battleMode, u8 lvlMode);
//u32 GetAiScriptsInBattleFactory(void);
//void SetMonMoveAvoidReturn(struct Pokemon *mon, u16 moveArg, u8 moveSlot);

#endif // GUARD_BATTLE_FACTORY_H
