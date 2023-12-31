// 敵の状ﾆﾔ：
// 通常，捕捉
typedef enum {
	NORMAL, CAPTURED
} CAPTOR_STATE;

// 自機をとらｷVる敵の動ｪｽ
void Captor(
	bool capture  // 今回，捕捉攻?をするかどｴﾓか
) {
	static int state=NORMAL;  // 敵の状ﾆﾔ
	
	// 状ﾆﾔによって分岐する
	switch (state) {
		
		// 通常状ﾆﾔ：
		// 通常攻?または捕捉攻?を行ｴﾓ。
		// 捕捉攻?ｸm成功したら捕捉状ﾆﾔに移る。
		// 攻?の具体的な??は，CaptureAttack，
		// NormalAttackの各関?で行ｴﾓとする。
		case NORMAL:
			if (capture) {
				if (CaptureAttack()) state=CAPTURED;
			} else {
				NormalAttack();
			}
			break;
		
		// 捕捉状ﾆﾔ：
		// 通常攻?を行ｴﾓ。
		// 破壊されたら自機を返した後に消滅する。
		// 判ゾなどの具体的な??は，Destroyed，
		// ReturnMyShip，Deleteの各関?で行ｴﾓとする。
		case CAPTURED:
			NormalAttack();
			if (Destroyed()) {
				ReturnMyShip();
				Delete();
			}
			break;
	}
}

