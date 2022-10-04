//
// Created by 42077 on 9/27/2022.
//

#include "WeaponClass.h"

float WeaponClass::GetDamage(float armor) {
    if(Random::Range(0,100) < critChance)
        return CalculateDamage(armor) * critDamage;
    else
        return CalculateDamage(armor);
}

float WeaponClass::GetAttackSpeed() {
    return attackSpeed;
}

float WeaponClass::CalculateDamage(float armor) {
    float base;

    switch (type)
    {
        case Sword:
            return damage+(sharpness + (pow(sharpness,1.5) / (pow(armor, 0.125))));
            break;
        case Spear:
            return damage+(sharpness + (pow(sharpness,1.5) / (pow(armor, 0.125))));
            break;
        case Dagger:
            return damage+(sharpness + (pow(sharpness,1.5) / (pow(armor, 0.125))));
            break;
        case Hammer:
            return damage+(heaviness + (pow(heaviness,1.2) * (pow(armor, 0.2))));
            break;
        case Fists:
            return damage+(heaviness + (pow(heaviness,1.2) * (pow(armor, 0.15))));
            break;
        case Staff:
            return damage+(heaviness + (pow(heaviness,1.2) * (pow(armor, 0.175))));
            break;
        default:
            return damage+((sharpness + (pow(sharpness,1.5) / (pow(armor, 0.125)))+(heaviness + (pow(heaviness,1.2) * (pow(armor, 0.15))))))/1.75;
            break;
    }
}

WeaponClass::WeaponClass(float damage, float heaviness, float sharpness, float critDamage, float critChance,
                         float attackSpeed, weaponType type,std::string name,std::string description) {
    this->damage = damage;
    this->heaviness = heaviness;
    this->sharpness = sharpness;
    this->critDamage = critDamage;
    this->critChance = critChance;
    this->attackSpeed = attackSpeed;
    this->type = type;
    this->name = name;
    this->description = description;
}
