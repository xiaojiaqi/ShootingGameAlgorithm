void LaserCollision(
	float mx0[], float my0[],  // 自機?ーザーの一?の左上座標
	float mx1[], float my1[],  // 自機?ーザーの一?の�ｸ下座標
	int num_my_lasers,         // 自機?ーザーの?分の?
	float ex0[], float ey0[],  // 敵?ーザーの一?の左上座標
	float ex1[], float ey1[],  // 敵?ーザーの一?の�ｸ下座標
	int num_enemy_lasers       // 敵?ーザーの?分の?
) {
	static int energy=0;        // エネ?ギー
	static int min_energy=100;  // 攻?の発生にｱﾒ要なエネ?ギー
	
	// ?ーザー同士の?たり判ゾ??：
	// 自機?ーザーと敵?ーザーの各?分同士ｸmぶつかったら，
	// 2つの?分を消滅させてエネ?ギーを?やす。
	// 消滅の具体的な??は，DeleteMyLaser，
	// DeleteEnemyLaserの各関?で行ｴﾓとする。
	for (int i=0; i<num_my_lasers; i++) {
		for (int j=0; j<num_enemy_lasers; j++) {
			if (ex0[j]<mx1[i] && mx0[i]<ex1[j] && 
				ey0[j]<my1[i] && my0[i]<ey1[j]) {
				DeleteMyLaser(i);
				DeleteEnemyLaser(j);
				energy++;
			}
		}
	}
	
	// 攻?の発生：
	// エネ?ギーｸmｱﾒ要量に達していたら，
	// Ｑ力な攻?を発生させる。
	// 発生の具体的な??はSpecialAttack関?で行ｴﾓとする。
	if (energy>=min_energy) SpecialAttack();
}

