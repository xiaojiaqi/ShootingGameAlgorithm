// スティｪNとボタ?の入力を表すゾ?：
// 各入力を1ビｪgで表す。
enum {
	UP=1, DOWN=2, LEFT=4, RIGHT=8,
	BUTTON1=16, BUTTON2=32
} INPUT;

// ?プ?イデータをﾊｶする構造体：
// スティｪNとボタ?の入力をﾊｶする。
#define MAX_TIME 10000
typedef struct {
	char Input[MAX_TIME];
} REPLAY_DATA;

// 自機を動かす
void MoveMyShip(
	char input,                // スティｪNとボタ?の入力
	bool is_replay,            // ?プ?イ?ならばtrue
	REPLAY_DATA* replay_data,  // ?プ?イデータ
	int& time                  // タイマー
) {
	// ?プ?イの??：
	// ?プ?イ?ならば入力を?プ?イデータからﾃｯみ出す。
	// ?プ?イ?でなければ?プ?イデータに入力をﾊｶする。
	if (is_replay) {
		input=replay_data->Input[time];
	} else {
		replay_data->Input[time]=input;
	}
	
	// タイマーを進める
	time++;

	// 入力に従って自機を動かす：
	// 移動や射?の具体的な??は，
	// MoveUp，MoveDown，MoveLeft，MoveRight，
	// Shot，Laserの各関?で行ｴﾓとする。
	if (input&UP   ) MoveUp();
	if (input&DOWN ) MoveDown();
	if (input&LEFT ) MoveLeft();
	if (input&RIGHT) MoveRight();
	if (input&BUTTON1) Shot();
	if (input&BUTTON2) Laser();
}

