#include "Fight.hpp"

Fight::Fight(Player &player) : m_player(player) {
}

void Fight::start(std::shared_ptr<EnemyCard> enemy) {
	m_player.setFighting(true);
	m_enemy = enemy;
}

std::string Fight::turn(std::shared_ptr<ObjectCard> weapon) {
	char message[80];
	int damagesDealtToEnemy = m_player.attack(m_enemy, weapon);
	if (!m_enemy->isDead()) {
		int damagesDealtToPlayer = m_enemy->attack(m_player);
		snprintf(
			message,
			80,
			"You hit %s (%d DP)\n%s hits you (%d DP)",
			m_enemy->getName(),
			damagesDealtToEnemy,
			m_enemy->getName(),
			damagesDealtToPlayer
		);
	}
	else {
		snprintf(
			message,
			80,
			"You defeated %s",
			m_enemy->getName()
		);
		m_enemy = nullptr;
		m_player.setFighting(false);
	}
	return message;
}

bool Fight::isFighting() const {
	return m_enemy != nullptr;
}
