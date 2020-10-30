#ifndef CARD_LIBRARY_H
#define CARD_LIBRARY_H
#include "minion.h"
#include "spell.h"
#include "trigger.h"
#include "ritual.h"
#include "enchantment.h"
#include "ability.h"
#include <map>
#include <string>

extern std::map <std::string, Card*> allCards;
extern std::map <std::string, Minion> minionCards;

Trigger A = {"MLP", "Gain +1/+1 whenever a minion leaves play.", 1, 1};
Trigger B = {"MEP", "Whenever an opponent's minion enters play, deal 1 damage to it.", 0, 0, 1};
Trigger C = {"EOT", "At the end of your turn, all your minions gain +0/+1.", 0, 1};
Ability dmg = {1, "Deal 1 damage to target minion"};
Ability summon1 = {1, "Summon a 1/1 air elemental"};
Ability summon2 = {2, "Summon up to three 1/1 air elementals"};

Minion airElemental = {"Air Elemental", 0, 1, 1};
Minion earthElemental = {"Earth Elemental", 3, 4, 4};
Minion boneGolem = {"Bone Golem", 2, 1, 3, &A};
Minion fireElemental = {"Fire Elemental", 2, 2, 2, &B};
Minion potionSeller = {"Potion Seller", 2, 1, 3, &C};
Minion novicePyromancer = {"Novice Pyromancer", 1, 0, 1, nullptr, &dmg};
Minion apprenticeSummoner = {"Apprentice Summoner", 1, 1, 1, nullptr, &summon1};
Minion masterSummoner = {"Master Summoner", 3, 2, 3, nullptr, &summon2};


Spell banish = {"Banish", 2, "Destory target minion or ritual"};
Spell unsummon = {"Unsummon", 1, "Return target minion to its owner's hand"};
Spell recharge = {"Recharge", 1, "Your ritual gains 3 charges"};
Spell disenchant = {"Disenchant", 1, "Destory the top enchantment on target minion"};
Spell raiseDead = {"Raise Dead", 1, "Resurrect the top minion in your graveyard and set its defense to 1"};
Spell blizzard = {"Blizzard", 3, "Deal 2 damage to all minions"};

Trigger DR = {"SOT", "At the start of your turn, gain 1 magic"};
Trigger AOP = {"MEP", "Whenever a minion enters play under your control, it gains +1/+1", 1, 1};
Trigger SS = {"MEP", "Whenever a minio enters play, destory it"};
Ritual darkRitual = {"Dark Ritual", 0, DR, 1, 5};
Ritual auraOfPower = {"Aura of Power", 1, AOP, 1, 4};
Ritual standstill = {"Standstill", 3, SS, 2, 4};

Enchantment giantStrength = {"Giant Strength", 1, 2, 2};
Enchantment enrage = {"Enrage", 2, 2, 2, true};
Enchantment haste = {"Haste", 1, 0, 0};
Enchantment magicFatigue = {"Magic Fatigue", 0, 0, 0};
Enchantment silence = {"Silence", 1, 0, 0};

#endif
