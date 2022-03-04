// ogre, goblin, skeleton, orc и troll.

enum MonsterType{

	MONSTER_OGRE,
	MONSTER_GOBLIN,
	MONSTER_SKELETON,
	MONSTER_ORC,
	MONSTER_TROLL,
};

MonsterType monster = MONSTER_OGRE;


int editDate();

typedef int status_t; //typedef позволяет создавать псевдонимы для типов данных.
status_t editDate();

using status_t = int; //позволяет создавать псевдонимы для типов данных.
