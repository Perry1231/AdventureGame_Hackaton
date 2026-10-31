#include "Header.h"
#include <iostream>
#include <cstdlib>
#include <string>

// Enemy class method implementations

void Enemy::SetAttitude(int attitude_g)
{
    attitude = attitude_g;
}

void Enemy::RandomizeStats()
{
    // Simple randomization based on difficulty
    health = 100 + (rand() % 50); // 100-150 health
    Shealth = health;
    strength = 10 + (rand() % 20); // 10-30 strength
    defense = 5 + (rand() % 15); // 5-20 defense
    gold = 20 + (rand() % 30); // 20-50 gold
}

int Enemy::GetTotalDefense() const
{
    return defense;
}

int Enemy::GetTotalAttack() const
{
    return strength;
}

void Enemy::ApplyPotionEffect(int effectType, int potency)
{
    switch (effectType) {
        case 0: // HEALTH
            health += potency;
            break;
        case 1: // DEFENSE
            defense += potency;
            break;
        case 2: // AGILITY
            // Enemy doesn't have agility in this implementation
            break;
        case 3: // INTELLIGENCE
            // Enemy doesn't have intelligence in this implementation
            break;
        case 4: // GOLD
            gold += potency;
            break;
        case 5: // STRENGTH
            strength += potency;
            break;
        default:
            break;
    }
}
