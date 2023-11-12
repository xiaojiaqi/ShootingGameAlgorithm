// ボスの状ﾆﾔ：
// 攻?0，攻?1，攻?2，待機
typedef enum {
	ATTACK0, ATTACK1, ATTACK2, WAIT
} BOSS_STATE;


// 各状ﾆﾔの制限?間
int Time[]={30, 40, 25, 20};

// ボスの行動
void MoveBoss(
	BOSS_STATE& state,  // 現在の状ﾆﾔ
	int& timer           // タイマー
) {
	// 攻?：
	// 状ﾆﾔに?じた攻?を行ｴﾓ。待機のとｪｽにはﾀeもしない。
	// 攻?の具体的な??は，
	// Attack0，Attack1，Attack2の各関?で行ｴﾓとする。
	switch (state) {
		case ATTACK0: Attack0(); break;
		case ATTACK1: Attack1(); break;
		case ATTACK2: Attack2(); break;
	}
	
	// 状ﾆﾔ遷移：
	// タイマーを加算し，
	// 各状ﾆﾔの制限?間を超ｷVたら?の状ﾆﾔに移行する。
	timer++;
	if (timer>Time[state]) {
		state=(BOSS_STATE)((state+1)%4);
		timer=0;
	}
}

