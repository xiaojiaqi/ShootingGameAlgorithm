// ･ﾂー?の状ﾆﾔ：
// 待機，伸びている途?，伸びｪｽった，縮んでいる途?。
typedef enum {
	READY, EXTENDING, EXTENDED, SHRINKING
} STATE_TYPE;

// ･ﾂー?の動ｪｽ
void MoveArm(
	bool button  // ･ﾂー?を伸ばすボタ?の状ﾆﾔ
) {
	static STATE_TYPE state=READY;  // ･ﾂー?の状ﾆﾔ
	static int length;              // ･ﾂー?の長さ
	static int max_length=20;       // ･ﾂー?の最大長
	static int time;                // ?間待ち用
	
	// ･ﾂー?の状ﾆﾔによって??を変ｷVる
	switch (state) {
		
		// 待機：
		// ボタ?ｸm?されたら･ﾂー?を伸ばす。
		case READY:
			if (button) {
				state=EXTENDING;
				length=0;
			}
			break;
		
		// 伸びている途?：
		// ･ﾂー?を伸ばし，
		// 最大長に達したら伸びｪｽった状ﾆﾔに移る。
		case EXTENDING:
			if (length<max_length) {
				length++;
			} else {
				state=EXTENDED;
				time=10;
			}
			break;
		
		// 伸びｪｽった：
		// 一ゾ?間ｸm経過したら縮ませる。
		case EXTENDED:
			if (time>0) {
				time--;
			} else {
				state=SHRINKING;
			}
			break;
		
		// 縮んでいる途?：
		// 長さｸm0になったら待機状ﾆﾔに戻る。
		case SHRINKING:
			if (length>0) {
				length--;
			} else {
				state=READY;
			}
			break;
	}
}

