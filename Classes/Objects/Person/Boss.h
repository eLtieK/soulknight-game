#ifndef BOSS_H
#define BOSS_H

#include "Enemy.h"

class Boss : public Enemy {
public:
    Boss(const std::string& spritePath = "", int maxHits = 20); // Mặc định cần 25 hit để chết
    void onHit() { hitTaken++; }
    void initAnimations() override;
    bool isDefeated() const { return hitTaken >= maxHit; } // Kiểm tra nếu boss bị đánh bại

private:
    int hitTaken = 0;  // Số hit đã nhận
    int maxHit;        // Số hit tối đa để đánh bại boss
};

#endif // BOSS_H
