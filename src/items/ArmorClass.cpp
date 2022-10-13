//
// Created by 42077 on 10/4/2022.
//

#include "ArmorClass.h"

ArmorClass::ArmorClass(int armor, int additionalHealth, int additionalMana, int additionalStamina, int additionalHeaviness,
                       int additionalSharpness, int additionalCritChance, int additionalCritDamage, int additionalAgility) {
    this->armor = armor;
    this->additionalHealth = additionalHealth;
    this->additionalMana = additionalMana;
    this->additionalStamina = additionalStamina;
    this->additionalHeaviness = additionalHeaviness;
    this->additionalSharpness = additionalSharpness;
    this->additionalCritChance = additionalCritChance;
    this->additionalCritDamage = additionalCritDamage;
    this->additionalAgility = additionalAgility;
}


