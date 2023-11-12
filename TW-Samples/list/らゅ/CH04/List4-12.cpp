void SightedBomb(
	float x, float y,        // 自機の座標
	float sx, float sy,      // 照?の座標
	float bvx, float bvy,    // ?弾の速ﾃg
	bool button              // ボタ?の状ﾆﾔ（?されたとｪｽtrue）
) {
	// ?弾の状ﾆﾔ
	static bool bombing=false;  // ???かどｴﾓか
	static float bx, by;        // ?弾の座標
	static float tx, ty;        // ?弾ｼｨの座標

	// ???ではないとｪｽ：
	// ボタ?ｸm?されたら??する。
	// ?弾の?期座標と?弾ｼｨの座標を設ゾする。
	if (!bombing) {
		if (button) {
			bombing=true;
			bx=x; by=y;
			tx=sx; ty=sy;
		}
	}
	
	// ???のとｪｽ：
	// ?弾を移動させる。
	// ?弾ｸm?弾ｼｨに?達したら?発させる。
	// ?発の具体的な??はExplode関?で行ｴﾓとする。
	else {
		bx+=bvx; by+=bvy;
		if (bx==tx && by==ty) {
			Explode();
			bombing=false;
		}
	}
	
	// 自機と照?を描く：
	// 具体的な??はDrawMyShip関?とDrawScope関?で行ｴﾓとする。
	// 照?と地上物との?たり判ゾ??を行ｷVば，
	// 照?の端をｼｨ滅させる蓼ともでｪｽる。
	DrawMyShip(x, y);
	DrawScope(sx, sy);

	// ???の場?には?弾ｼｨと?弾を描く：
	// 具体的な??はDrawTarget関?とDrawBomb関?で行ｴﾓとする。
	if (bombing) {
		DrawTarget(tx, ty);
		DrawBomb(bx, by);
	}
}

