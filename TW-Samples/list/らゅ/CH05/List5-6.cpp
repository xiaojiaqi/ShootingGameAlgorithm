// 自機の状ﾆﾔ（通常，バーサーク，弱い）
typedef enum {
	NORMAL, BERSERK, WEAK
} STATE_TYPE;

// バーサーク状ﾆﾔの??
void Berserk(
	int num_shot,   // 味方のシ?ｪ�トの?
	int num_enemy,  // 敵の?
	int num_bullet  // 弾（敵弾）の?
) {
	static STATE_TYPE state=NORMAL;  // 自機の状ﾆﾔ（最?は通常）
	static int energy=0;             // エネ?ギー
	static int berserk_energy=100;   // バーサーク状ﾆﾔの発動に
	                                 // ｱﾒ要なエネ?ギー
	static int time;                 // 効果の残り?間
	
	// 状ﾆﾔに?じて分岐する
	switch (state) {
		
		// 通常状ﾆﾔ
		case NORMAL:

			// 通常攻?：
			// 具体的な??はNormalAttack関?で行ｴﾓとする。
			NormalAttack();

			// 敵や弾との?たり判ゾ??：
			// ?たるとミスになる。
			// 判ゾや?果の具体的な??はHitEnemy，
			// HitBullet，Missの各関?で行ｴﾓとする。
			for (int i=0; i<num_enemy; i++)
				if (HitEnemy(i)) Miss();
			for (int i=0; i<num_bullet; i++)
				if (HitBullet(i)) Miss();

			// 味方のシ?ｪ�トとの?たり判ゾ??：
			// エネ?ギーを溜める。
			// 判ゾや?果の具体的な??はHitShot，
			// DeleteShotの各関?で行ｴﾓとする。
			for (int i=0; i<num_shot; i++) {
				if (HitShot(i)) {
					energy++;
					DeleteShot(i);
				}
			}

			// エネ?ギー量の判ゾ：
			// エネ?ギーｸm�ﾏ分に溜まったら
			// バーサーク状ﾆﾔに移行する。
			// エネ?ギーは自然に減っていく。
			if (energy>=berserk_energy) {
				state=BERSERK;
				time=300;
			} else {
				energy--;
			}

			break;
		
		// バーサーク状ﾆﾔ
		case BERSERK:

			// 特殊攻?：
			// 具体的な??はSpecialAttack関?で行ｴﾓとする。
			SpecialAttack();

			// 敵や弾との?たり判ゾ??：
			// 敵にダ?ージを与ｷV，弾は消す。
			// ?果の具体的な??はDamageEnemy，
			// DeleteBulletの各関?で行ｴﾓとする。
			for (int i=0; i<num_enemy; i++)
				if (HitEnemy(i)) DamageEnemy(i);
			for (int i=0; i<num_bullet; i++)
				if (HitBullet(i)) DeleteBullet(i);
			
			// 残り?間ｸm切れたら弱い状ﾆﾔに移行する
			time--;
			if (time<=0) {
				state=WEAK;
				time=200;
			}
			
			break;
			
		// 弱い状ﾆﾔ
		case WEAK:
			
			// 敵や弾との?たり判ゾ??：
			// ?たるとミスになる。
			for (int i=0; i<num_enemy; i++)
				if (HitEnemy(i)) Miss();
			for (int i=0; i<num_bullet; i++)
				if (HitBullet(i)) Miss();

			// 残り?間ｸm切れたら通常状ﾆﾔに移行する
			time--;
			if (time<=0) {
				state=NORMAL;
				energy=0;
			}
			
			break;
	}
}
