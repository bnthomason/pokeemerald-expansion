#ifndef GUARD_SURVIVAL_MASTER_H
#define GUARD_SURVIVAL_MASTER_H

#include "data.h"

struct RSSurvivalMasterRecord
{
    /*0x00*/ u8 lvlMode; // 0 = level 50, 1 = level 100
    /*0x01*/ u8 gamefacilityClass;
    /*0x02*/ u16 winStreak;
    /*0x04*/ u8 name[PLAYER_NAME_LENGTH + 1];
    /*0x0C*/ u8 trainerId[TRAINER_ID_LENGTH];
    /*0x10*/ u16 greeting[EASY_CHAT_BATTLE_WORDS_COUNT];
    /*0x1C*/ struct BattleTowerPokemon party[FRONTIER_PARTY_SIZE];
    /*0xA0*/ u32 checksum;
};

struct SurvivalIslandTrainer
{
    u8 gamefacilityClass;
    u8 filler1[3];
    u8 trainerName[PLAYER_NAME_LENGTH + 1];
    u16 speechBefore[EASY_CHAT_BATTLE_WORDS_COUNT];
    u16 speechWin[EASY_CHAT_BATTLE_WORDS_COUNT];
    u16 speechLose[EASY_CHAT_BATTLE_WORDS_COUNT];
    const u16 *monSet;
};

extern const u8 gMasterMaleGameFacilityClasses[30];
extern const u16 gMasterMaleTrainerGfxIds[30];
extern const u8 gMasterFemaleGameFacilityClasses[20];
extern const u16 gMasterFemaleTrainerGfxIds[20];
extern const struct TrainerMon gSurvivalIslandMons[];
extern const struct SurvivalIslandTrainer gSurvivalIslandTrainers[];
//extern const struct TrainerMon gSlateportBattleTentMons[];
//extern const struct SurvivalIslandTrainer gSlateportBattleTentTrainers[];

// Temporary storage for monIds of the opponent team
// during team generation in battle factory and similar facilities.
extern u16 gIslandTempParty[];

extern const struct SurvivalIslandTrainer *gGameFacilityTrainers;
extern const struct TrainerMon *gGameFacilityTrainerMons;

void CallSurvivalMasterFunc(void);
u16 GetRandomScaledIslandTrainerId(u8 challengeNum, u8 battleNum);
void SetBattleGameFacilityTrainerGfxId(u16 trainerId, u8 tempVarId);
//void SetEReaderTrainerGfxId(void);
u16 GetBattleGameFacilityTrainerGfxId(u16 trainerId);
void PutNewSurvivalMasterRecord(struct EmeraldBattleTowerRecord *newRecordEm);
u8 GetIslandTrainerFrontSpriteId(u16 trainerId);
u8 GetIslandOpponentClass(u16 trainerId);
void GetIslandTrainerName(u8 *dst, u16 trainerId);
void FillIslandTrainerParty(u8 monsCount);
void FillIslandTrainersParties(u8 monsCount);
u16 GetRandomIslandMonFromSet(u16 trainerId);
void IslandSpeechToString(const u16 *words);
void DoSpecialIslandTrainerBattle(void);
void CalcEmeraldSurivalMasterChecksum(struct EmeraldBattleTowerRecord *record);
void CalcRubySurvivalMasterChecksum(struct RSBattleTowerRecord *record);
u16 GetCurrentSurvivalIslandWinStreak(u8 lvlMode, u8 battleMode);
// u8 GetEreaderTrainerFrontSpriteId(void);
// u8 GetEreaderTrainerClassId(void);
// void GetEreaderTrainerName(u8 *dst);
// void ValidateEReaderTrainer(void);
// void ClearEReaderTrainer(struct BattleTowerEReaderTrainer *ereaderTrainer);
//void CopyEReaderTrainerGreeting(void);
void TryHideSurvivalMasterReporter(void);
bool32 RubySurivalMasterRecordToEmerald(struct RSBattleTowerRecord *src, struct EmeraldBattleTowerRecord *dst);
bool32 EmeraldSurvivalMAsterRecordToRuby(struct EmeraldBattleTowerRecord *src, struct RSBattleTowerRecord *dst);
//void CalcApprenticeChecksum(struct Apprentice *apprentice);
void GetSurvivalMasterTrainerLanguage(u8 *dst, u16 trainerId);
u8 SetGameFacilityPtrsGetLevel(void);
u8 GetIslandEnemyMonLevel(u8 lvlMode);
// s32 GetHighestLevelInPlayerParty(void);
u16 GameFacilityClassToGraphicsId(u8 facilityClass);
bool32 ValidateSurivalMasterRecord(u8 recordId); // unused
void TrySetLinkSurvivalMasterEnemyPartyLevel(void);
void CreateGameFacilityMon(const struct TrainerMon *fmon, u16 level, u8 fixedIV, u32 otID, u32 flags, struct Pokemon *dst);

#endif //GUARD_SURVIVAL_MASTER_H
