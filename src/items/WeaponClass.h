//
// Created by 42077 on 9/27/2022.
//

#ifndef VOXERRA_WEAPONCLASS_H
#define VOXERRA_WEAPONCLASS_H
#include "../Random.h"
#include "../enums.h"
#include <cmath>
#include <iostream>

class WeaponClass {
private:
    weaponType type;
    float damage;
    float heaviness;
    float sharpness;
    float critDamage;
    float critChance;
    float attackSpeed;
    std::string name;
    std::string description;
    float CalculateDamage(float armor);
public:
    WeaponClass(float damage,float heaviness, float sharpness, float critDamage,float critChance,
                float attackSpeed, weaponType type, std::string name, std::string description);
    std::string GetName();
    std::string GetDescription();
    float GetDamage(float armor);
    float GetAttackSpeed();
};


#endif //VOXERRA_WEAPONCLASS_H
