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

    if(type == Sword || type == Spear || type == Dagger)
    {
        base = sharpness + pow(damage,armor*.125);
    }
    else if(type == Hammer || type == Fists || type == Staff)
    {
        base = damage + pow(heaviness,armor*.125);
    }
    else
    {
        base =  ((damage + pow(heaviness,armor*.125)) + (sharpness + pow(damage,armor*.125))/2);
    }

    return base;
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
