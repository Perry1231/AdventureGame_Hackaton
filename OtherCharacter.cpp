#include "Header.h"

OtherCharacter OtherCharacter::CreateQuestGiver()
{
    OtherCharacter oc;
    oc.ctype = QUESTGIVERS;
    return oc;
}

OtherCharacter OtherCharacter::CreateMerchant()
{
    OtherCharacter oc;
    oc.ctype = MERCHANS;
    return oc;
}

