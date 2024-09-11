#ifndef GUARD_STARTER_CHOOSE_H
#define GUARD_STARTER_CHOOSE_H

extern const u16 gBirchBagGrass_Pal[];
extern const u32 gBirchBagTilemap[];
extern const u32 gBirchGrassTilemap[];
extern const u32 gBirchBagGrass_Gfx[];
extern const u32 gPokeballSelection_Gfx[];

u16 GetStarterPokemon(u16 chosenStarterId);
u16 GetStarterPokemon1(u16 chosenStarterId);
u16 GetStarterPokemon2(u16 chosenStarterId);
u16 GetStarterPokemon3(u16 chosenStarterId);
u16 GetStarterPokemon4(u16 chosenStarterId);
u16 GetStarterPokemon5(u16 chosenStarterId);
u16 GetStarterPokemon6(u16 chosenStarterId);
u16 GetStarterPokemon7(u16 chosenStarterId);
u16 GetStarterPokemon8(u16 chosenStarterId);
u16 GetStarterPokemon9(u16 chosenStarterId);
void CB2_ChooseStarter(void);

#endif // GUARD_STARTER_CHOOSE_H
