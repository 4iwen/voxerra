//
// Created by 42077 on 10/4/2022.
//

#ifndef VOXERRA_ARMORCLASS_H
#define VOXERRA_ARMORCLASS_H


class ArmorClass {
private:
    int level;

    int armor;
    int additionalHealth;
    int additionalMana;
    int additionalStamina;
    int additionalHeaviness;
    int additionalSharpness;
    int additionalCritChance;
    int additionalCritDamage;
    int additionalAgility;
public:
    ArmorClass(int armor, int additionalHealth, int additionalMana, int additionalStamina, int additionalHeaviness,
               int additionalSharpness, int additionalCritChance, int additionalCritDamage, int additionalAgility);

    int GetArmor();
    int GetAdditionalHealth();
    int GetAdditionalMana();
    int GetAdditionalStamina();
    int GetAdditionalHeaviness();
    int GetAdditionalSharpness();
    int GetAdditionalCritChance();
    int GetAdditionalCritDamage();
    int GetAdditionalAgility();
};


#endif //VOXERRA_ARMORCLASS_H
