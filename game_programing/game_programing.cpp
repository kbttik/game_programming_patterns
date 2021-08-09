// game_programing.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <stdio.h>
#include <iostream>

//モンスタークラスを作る（インスタンスの親クラス）.
class Monster {
public:
	Monster() {};
	virtual ~Monster() {};
};

//幽霊クラスを作る（インスタンスする本体）.
class Ghost :public Monster {
public:
	Ghost(int health, int speed)
		: health_(health),
		speed_(speed)
	{};
	void Monster() {};
	int get_health() { return health_; };
	int get_speed() { return speed_; };


private:
	int health_;
	int speed_;
};


//スポナー定義.

//※1の関数へのポインタ*Monsterがあり、さらにそれに対するポインタSpawnCallbackを生成.
// 戻り値がMonsterポインタの関数 SpawnCallbackの生成
//typedef int (*FUNC_POINTER)(double);
// 返り値 (* ポインタ変数名)(引数の型)
// FUNC_POINTER p; で関数ポインタ
// http://shiroibanana.blogspot.com/2012/09/callback.html
typedef Monster* (*SpawnCallback)();

//スポナーをなくし、代わりに独立した以下の関数をスポナー代わりに使う.
//これを呼び出せばゴーストクラスがインスタンスされる.
//Monster* spawnGhost(int hp, int sp)
//{
//	return new Ghost(hp, sp);//ゴーストのインスタンスを返す.
//};

Monster* spawnGhost()
//Ghost spawnGhost()
{
	return new Ghost(10, 11);//ゴーストのインスタンスを返す.
};


class Spawner {
public:
	Spawner(SpawnCallback spawn) //=Spawner(Monster spawn).
	: spawn_(spawn)
	{}

	//spawn_ = Spawner(Monster* spawn(int hp, int sp)) {};

	Monster* spawnMonster() { return spawn_(); }

private:
	SpawnCallback spawn_;
};


int main()
{
	// 基底クラス(Monster)しか扱えないが、どうやってGhostまで戻すのか。。。(Ghostのメンバ変数にどうアクセスするのか)
	Spawner* ghostSpawner = new Spawner(spawnGhost);
	// 参照戻しで、Monsterオブジェクトにアクセス
	Monster ghost = *ghostSpawner->spawnMonster();
	// Monsterポインタをghost2に入れる
	Monster* ghost2 = ghostSpawner->spawnMonster();

	//Spawner* ghostSpawner = new Spawner(spawnGhost(50, 60));
	printf("main = %p\n", main);
	printf("ゴーストをスポーン(値) health:%s\n", "1");
	printf("ゴーストをスポーン(ポインタ) %p\n", &ghost);

	return 0;
};
