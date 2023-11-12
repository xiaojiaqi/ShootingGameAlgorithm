// 敵の状ﾆﾔを表すゾ?：
// ?備（出現前），出現，?動，消失
typedef enum {
	READY, APPEAR, ACT, DISAPPEAR
} STATE_TYPE;

// 出現と消失にかかる?間，?動?間
#define TIME 30
#define ACT_TIME 180

// 空?に現れる敵の??
void EmergingEnemy(
	int num_enemy,           // 敵の?
	STATE_TYPE state[],      // 敵の状ﾆﾔ
	float ex[], float ey[],  // 敵の座標
	float alpha[],           // ･ﾂ?フﾆﾍ値
	int timer[]              // タイマー
) {
	// 全ての敵に関する?ープ
	for (int i=0; i<num_enemy; i++) {
		
		// 状ﾆﾔに?じて分岐
		switch (state[i]) {
			
			// ?備（出現前）：
			// ･ﾂ?フﾆﾍ値とタイマーを?期化して，
			// 出現状ﾆﾔに移行する。
			case READY:
				state[i]=APPEAR;
				alpha[i]=0;
				timer[i]=TIME;
				break;
			
			// 出現：
			// ･ﾂ?フﾆﾍ値をだんだん大ｪｽくする。
			// タイマーｸm0になったら?動状ﾆﾔに移行する。
			case APPEAR:
				alpha[i]=(float)(TIME-timer[i])/TIME;
				timer[i]--;
				if (timer[i]==0) {
					state[i]=ACT;
					timer[i]=ACT_TIME;
				}
				break;
			
			// ?動：
			// 移動や攻?を行ｴﾓ。
			// タイマーｸm0になったら消失状ﾆﾔに移行する。
			// 移動や攻?の具体的な??は，
			// MoveEnemy関?で行ｴﾓとする。
			case ACT:
				MoveEnemy(i);
				timer[i]--;
				if (timer[i]==0) {
					state[i]=DISAPPEAR;
					timer[i]=TIME;
				}
				break;
			
			// 消失：
			// ･ﾂ?フﾆﾍ値をだんだん小さくする。
			// タイマーｸm0になったら敵を消す。
			// 敵を消す具体的な??は，
			// DeleteEnemy関?で行ｴﾓとする。
			case DISAPPEAR:
				alpha[i]=(float)timer[i]/TIME;
				timer[i]--;
				if (timer[i]==0) {
					DeleteEnemy(i);
				}
				break;
		}
		
		// 敵の表示：
		// ･ﾂ?フﾆﾍ値に基づいて･ﾂ?フﾆﾍ?成表示を行ｴﾓ。
		DrawEnemy(ex[i], ey[i], alpha[i]);
	}
}
