#include "Mover.h"
#include "Hit.h"
#include "..\LibGame\Input.h"
#include <assert.h>




//==============================================================
// ショットのサブルーチン

// 通常のショット
void CMover::Shot() {

	// 弱い状態
	if (Valid.Berserk && Berserk.State!=BS_NORMAL) return;
	
	// 色の切り替え
	if (Valid.ChangeColor) {
		New(ChangeColor.Shot[Color-1]);
	}

	// アーム
	if (Valid.Arm) {
		if (Arm.NumStock<=0) return;
		Arm.NumStock--;
		CMover* model=Weapon.Shot;
		CObject3D* obj3d=model->Obj3D;
		model->Obj3D=Arm.Stock[Arm.NumStock];
		New(model);
		model->Obj3D=obj3d;
	} else

	// ショットの強化
	if (Valid.RFShot) {
		CMoverGroup* mg=GetGroup(MYSHIP_GROUP);
		CMover *mover;
		CHit hit=*RFShot.Hit;
		hit.SetPos(X, Y);
		if (mover=mg->FirstHit(&hit)) {
			do {
				if (mover!=this) {
					switch (RFShot.Mode) {
						case 0:
							New(RFShot.Shot);
							return;
						case 1:
							CMover model=*RFShot.Shot;
							model.Angle=
								atan2(X-mover->X, mover->Y-Y)/D3DX_PI/2+0.25f;
							New(&model);
							return;
					}
				}
			} while (mover=mg->NextHit(&hit));
			New(Weapon.Shot);
		}
	} else

	// 自由に動かせる照準
	if (Valid.MovableSightS && MovableSightS.SightMover) {
		CMover* sight=MovableSightS.SightMover;
		CMover model=*Weapon.Shot;
		model.Valid.Target=true;
		model.Target.Type=TG_MOVER;
		model.Target.Mover=sight;
		New(&model);
	} else

	// 合体
	if (Valid.Docking && Docking.Docked) {
		New(Docking.Shot);
	} else

	// アイテムによる強化
	if (Valid.SAItem && SAItem.EffectMover) {
		New(SAItem.ShotModel);
	} else

	// 通常
	{
		New(Weapon.Shot);
		if (Valid.Captee && Captee.Doubled) {
			CMover* mover=New(Weapon.Shot);
			mover->X+=10;
		}
	}
}


// 溜め撃ち
void CMover::BigShot(int power) {
	New(Weapon.BigShot);
}


// 最大パワーの溜め撃ち
void CMover::MaxShot() {
	New(Weapon.MaxShot);
}




//==============================================================
// 基本のショット操作
void CMover::BasicShot(
	bool button,       // 今回のボタンの状態
	bool& prev_button  // 前回のボタンの状態
) {
	// ショットの発射：
	// 前回ボタンが押されておらず，今回押されているときだけ，
	// ショットを発射する。
	// 発射の詳細な処理はShot関数で行うものとする。
	if (!prev_button && button) Shot();
	
	// 今回のボタンの状態を保存する
	prev_button=button;
}


//==============================================================
// 連射
void CMover::AutoShot(
	bool button  // ボタンの状態（押されたときtrue）
) {
	// ショットの発射：
	// ボタンが押されていたらショットを発射する。
	// 発射の詳細な処理はShot関数で行うものとする。
	if (button) Shot();
}


//==============================================================
// 溜め撃ち
void CMover::PowerShot(
	bool button,    // ボタンの状態（押されたときtrue）
	int min_power,  // 弾が出る最小のパワー
	int max_power,  // 最大のパワー
	int& power      // 溜めパワー
) {
	// ボタンを押している場合：
	// 溜めパワーを増やす。
	if (button && power<max_power) power++;
	
	// ボタンを離している場合：
	// 溜めパワー>0ならば弾を撃ち，溜めパワーを0に戻す。
	if (!button && power>0) {
		
		// 最大パワーのとき：
		// 特別な弾を撃つ。
		// 具体的な処理はMaxShot関数で行うとする。
		if (power==max_power) MaxShot(); else
		
		// 最小パワー以上，最大パワー未満のとき：
		// 溜めパワーに応じた強さの溜め撃ち弾を撃つ。
		// 具体的な処理はBigShot関数で行うとする。
		if (min_power<=power) BigShot(power);
		
		// 溜めパワーを0に戻す
		power=0;
	}
}


//==============================================================
// セミオート連射
void CMover::SemiAutoShot(
	bool button,    // ボタンの状態（押されたときtrue）
	int min_power,  // 溜めパワーの最小値
	int max_power,  // 溜めパワーの最大値
	int max_gauge,  // 連射ゲージの最大値
	int& power,     // 溜めパワー
	int& gauge      // 連射ゲージ
) {
	// ボタンを押している場合
	if (button) {
		
		// 溜めパワー不足の場合：
		// 通常の弾を撃つ。
		if (power<min_power) Shot();
	
		// 溜めパワーを増やし，連射ゲージを最大にする
		if (power<max_power) power++;
		gauge=max_gauge;
	}
	
	// ボタンを離している場合：
	else {
		
		// 溜めパワー十分の場合：
		// 溜め撃ち弾を撃つ：
		// 最大パワーのときは特別な弾を撃つ。
		if (min_power<=power) {
			if (power==max_power) MaxShot(); 
				else BigShot(power);
			gauge=0;
		}
		
		// 連射ゲージ>0の場合：
		// 通常の弾を撃ち，連射ゲージを-1する。
		if (gauge>0) {
			Shot();
			gauge--;
		}

		// 溜めパワーを0にする
		power=0;
	}
}


//==============================================================
// ボタンを離して溜める溜め撃ち
void CMover::PowerShotReleased(
	bool button,    // ボタンの状態（押されたときtrue）
	int min_power,  // 弾が出る最小のパワー
	int max_power,  // 最大のパワー
	int& power      // 溜めパワー
) {
	// ボタンを離している場合：
	// 溜めパワーを増やす。
	if (!button && power<max_power) power++;
	
	// ボタンを押している場合：
	// 溜めパワー>0ならば弾を撃ち，溜めパワーを0に戻す。
	if (button && power>0) {
		
		// 最大パワーのとき：
		// 特別な弾を撃つ。
		// 具体的な処理はMaxShot関数で行うとする。
		if (power==max_power) MaxShot(); else
		
		// 最小パワー以上，最大パワー未満のとき：
		// 溜めパワーに応じた強さの溜め撃ち弾を撃つ。
		// 具体的な処理はBigShot関数で行うとする。
		if (min_power<=power) BigShot(power);
		
		// 溜めパワーを0に戻す
		power=0;
	}
}


//==============================================================
// コマンドショット
void CMover::CommandShot(const CInputState* is) {
	int& index=Weapon.Cmd.HistIndex;
	int* hist=Weapon.Cmd.Hist;
	COMMAND_LIST* list=Weapon.Cmd.List;

	// 入力を履歴に記録する
	hist[index]=
		(is->Up?CMD_UP:0)|
		(is->Down?CMD_DOWN:0)|
		(is->Left?CMD_LEFT:0)|
		(is->Right?CMD_RIGHT:0)|
		(is->Button[0]?CMD_BUTTON0:0)|
		(is->Button[1]?CMD_BUTTON1:0)|
		(is->Button[2]?CMD_BUTTON2:0)|
		(is->Button[3]?CMD_BUTTON3:0);

	// 各コマンドが入力されたかどうかを判定する
	int c, j, i;
	for (c=0; c<list->NumCommand; c++) {
		COMMAND& cmd=list->Command[c];
		
		// コマンドの入力確認
		for (i=0, j=cmd.Length-1; j>=0; j--) {
			for (; i<cmd.Limit; i++) {
				if (hist[(index-i+NUM_CMD_HIST)%NUM_CMD_HIST]==
					cmd.Input[j]) break;
			}
			if (i==cmd.Limit) break;
		}
		
		// コマンドの入力が確認できた：
		// コマンドショットを撃ち，履歴をクリアする。
		if (j==-1) {
			CMover* mover=Group->GetManager()->GetGroup(WEAPON_GROUP)->New();
			if (mover) mover->Init(cmd.Model, this);
			for (i=0; i<NUM_CMD_HIST; i++) hist[i]=CMD_NONE;
		}
	}
	
	// 記録位置を更新する
	index=(index+1)%NUM_CMD_HIST;
}


//==============================================================
// 連射とレーザーの共存
void CMover::ShotAndLaser(
	bool button,    // ボタンの状態（押されたときtrue）
	int min_power,  // 溜めパワーの最小値
	int max_gauge,  // 連射ゲージの最大値
	int& power,     // 溜めパワー
	int& gauge      // 連射ゲージ
) {
	// ボタンを押している場合
	if (button) {
		
		// 溜めパワー不足の場合：
		// 溜めパワーを増やし，連射ゲージを最大にして，
		// 弾を撃つ。具体的な処理はShot関数で行うとする。
		if (power<min_power) {
			power++;
			gauge=max_gauge;
			Shot();
		}
	
		// 溜めパワー十分の場合：
		// 連射ゲージを0にして，レーザーを撃つ。
		else {
			gauge=0;
			CMover* mover=Group->GetManager()->GetGroup(WEAPON_GROUP)->New();
			if (mover) mover->Init(Weapon.Laser, this);
		}
	}
	
	// ボタンを離している場合：
	else {
		
		// 連射ゲージ>0の場合：
		// 普通の弾を撃ち，連射ゲージを-1する。
		if (gauge>0) {
			Shot();
			gauge--;
		}

		// 溜めパワーを0にする
		power=0;
	}
}


//==============================================================
// ロックショット
void CMover::LockShot(
	bool button,     // ボタンの状態（押されたときtrue）
	int min_power,   // 溜めパワーの最小値
	int max_gauge,   // 連射ゲージの最大値
	int& power,      // 溜めパワー
	int& gauge       // 連射ゲージ
) {
	// ボタンを押している場合
	if (button) {
		
		// 溜めパワー不足の場合：
		// 溜めパワーを増やし，連射ゲージを最大にして，
		// 弾を撃つ。具体的な処理はShot関数で行うとする。
		if (power<min_power) {
			power++;
			gauge=max_gauge;
			Shot();
		}
	
		// 溜めパワー十分の場合：
		// 連射ゲージを0にして，ロックショットを撃つ。
		else {
			gauge=0;
			
			// ロックショットを撃つ：
			// 敵を追尾しているときは敵を狙い撃ちする。
			// （「自機に向かって飛ぶ弾」と同様）
			// 敵を追尾していないときは自機の正面に弾を撃つ。
			// （「自由な方向に飛ぶ弾」と同様）
			CMover* mover=Group->GetManager()->GetGroup(WEAPON_GROUP)->New();
			mover->Init(Weapon.Laser, this);
		}
	}
	
	// ボタンを離している場合：
	else {
		
		// 連射ゲージ>0の場合：
		// 普通の弾を撃ち，連射ゲージを-1する。
		if (gauge>0) {
			Shot();
			gauge--;
		}

		// 溜めパワーを0にする
		power=0;

		// ロックを外す
		ClearLockedEnemy();
	}
}




