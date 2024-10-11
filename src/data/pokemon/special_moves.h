#include "constants/moves.h"

static const u16 sNoneSpecialMoveLearnset[] = {
    MOVE_UNAVAILABLE,
};

#if P_FAMILY_DRACOCEROS_HERO
static const u16 sDracocerosHolySpecialMoveLearnset[] = {
    MOVE_LEER,
    MOVE_HISS,
    MOVE_RECOVER,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_DRACOCEROS_HERO

#if P_FAMILY_FAERIAL_HERO
static const u16 sFaerialBeautySpecialMoveLearnset[] = {
    MOVE_CHARM,
    MOVE_TAIL_WHIP,
    MOVE_GROOM,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_FAERIAL_HERO

