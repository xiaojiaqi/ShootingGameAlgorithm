#include "Mover.h"
#include "Hit.h"
#include "..\LibGame\Input.h"
#include <assert.h>




//==============================================================
// 發射的子程序

// 一般的發射
void CMover::Shot() {

	// 變弱狀態
	if (Valid.Berserk && Berserk.State!=BS_NORMAL) return;
	
	// 切換顏色
	if (Valid.ChangeColor) {
		New(ChangeColor.Shot[Color-1]);
	}

	// 手臂
	if (Valid.Arm) {
		if (Arm.NumStock<=0) return;
		Arm.NumStock--;
		CMover* model=Weapon.Shot;
		CObject3D* obj3d=model->Obj3D;
		model->Obj3D=Arm.Stock[Arm.NumStock];
		New(model);
		model->Obj3D=obj3d;
	} else

	// 發射攻擊的強化
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

	// 自由移動的瞄準器
	if (Valid.MovableSightS && MovableSightS.SightMover) {
		CMover* sight=MovableSightS.SightMover;
		CMover model=*Weapon.Shot;
		model.Valid.Target=true;
		model.Target.Type=TG_MOVER;
		model.Target.Mover=sight;
		New(&model);
	} else

	// 合體
	if (Valid.Docking && Docking.Docked) {
		New(Docking.Shot);
	} else

	// 依物品的強化
	if (Valid.SAItem && SAItem.EffectMover) {
		New(SAItem.ShotModel);
	} else

	// 正常
	{
		New(Weapon.Shot);
		if (Valid.Captee && Captee.Doubled) {
			CMover* mover=New(Weapon.Shot);
			mover->X+=10;
		}
	}
}


// 集氣攻擊
void CMover::BigShot(int power) {
	New(Weapon.BigShot);
}


// 最大能量的集氣攻擊
void CMover::MaxShot() {
	New(Weapon.MaxShot);
}




//==============================================================
// 基本的射擊操作
void CMover::BasicShot(
	bool button,       // 本次的按鈕狀態
	bool& prev_button  // 上次按鈕狀態
) {
	// 發射子彈：
	// 上次未按下按鈕，只有此次被按押時，
	// 發射子彈。
	// 發射時的細部處理以shot函數來執行。
	if (!prev_button && button) Shot();
	
	// 儲存此次按鈕的狀態
	prev_button=button;
}


//==============================================================
// 連續射擊
void CMover::AutoShot(
	bool button  // 按鈕的狀態（按下時為true）
) {
	//發射子彈：
	//按下按鈕就發射子彈。
	//發射的詳細處理是以shot函數來執行
	if (button) Shot();
}


//==============================================================
// 集氣射擊
void CMover::PowerShot(
	bool button,    // 按鈕的狀態（被按押時為true）
	int min_power,  // 射出子彈所需的最低能量
	int max_power,  // 最高能量
	int& power      // 累積能量
) {
	//按鈕按押時：
	//增加累積能量。
	if (button && power<max_power) power++;
	
	//放開按鈕時：
	//能量蓄積>0時，就發射子彈，累積能量恢復為0。
	if (!button && power>0) {
		
		//最高能量時：
		//發射特殊的子彈。
		//具體的處理是以函數MaxShot來執行。
		if (power==max_power) MaxShot(); else
		
		//最低能量以上，未達到最高能量時：
		//發射與能量累積值所對應的強力子彈。
		//具體的處理是以BigShot函數來執行。
		if (min_power<=power) BigShot(power);
		
		//累積能量恢復為0
		power=0;
	}
}


//==============================================================
// 連續射擊與集氣射擊共存
void CMover::SemiAutoShot(
	bool button,    // 按鈕的狀態（被按押時為true）
	int min_power,  // 累積能量的最小值
	int max_power,  // 累積能量的最大值
	int max_gauge,  // 連續射擊計量表的最大值
	int& power,     // 累積能量
	int& gauge      // 連續射擊能量
) {
	// 按住按鈕時
	if (button) {
		
		//累積能量不足時：
		//發射普通子彈。
		if (power<min_power) Shot();
	
		//增加累積能量，使連續射擊計量表為最大
		if (power<max_power) power++;
		gauge=max_gauge;
	}
	
	//放開按鈕時：
	else {
		
		//累積能量足夠時：
		//發射集氣彈：
		//能量為最大時，發射特殊子彈。
		if (min_power<=power) {
			if (power==max_power) MaxShot(); 
				else BigShot(power);
			gauge=0;
		}
		
		//連續射擊計量表>0時：
		//發射普通子彈，使連續射擊計量表-1。 
		if (gauge>0) {
			Shot();
			gauge--;
		}

		//使累積能量為0
		power=0;
	}
}


//==============================================================
// 放開按鈕發射集氣彈
void CMover::PowerShotReleased(
	bool button,    // 按鈕的狀態（被按押時為true）
	int min_power,  // 發射子彈的最低能量
	int max_power,  // 最高能量
	int& power      // 累積能量
) {
	//放開按鈕時：
	//增加累積能量。
	if (!button && power<max_power) power++;
	
	//按下按鈕時：
	//累積能量>0時發射子彈，累積能量恢復為0。
	if (button && power>0) {
		
		//最大能量時：
		//發射特別子彈。
		//具體處理是以MaxShot函數來執行。
		if (power==max_power) MaxShot(); else
		
		//最低能量以上，但未滿最高能量時：
		//發射與累積能量值對應的強力子彈。
		//具體處理是以BigShot函數來執行。
		if (min_power<=power) BigShot(power);
		
		//累積能量恢復至0
		power=0;
	}
}


//==============================================================
// 指令射擊
void CMover::CommandShot(const CInputState* is) {
	int& index=Weapon.Cmd.HistIndex;
	int* hist=Weapon.Cmd.Hist;
	COMMAND_LIST* list=Weapon.Cmd.List;

	// 將輸入歷程記錄下來
	hist[index]=
		(is->Up?CMD_UP:0)|
		(is->Down?CMD_DOWN:0)|
		(is->Left?CMD_LEFT:0)|
		(is->Right?CMD_RIGHT:0)|
		(is->Button[0]?CMD_BUTTON0:0)|
		(is->Button[1]?CMD_BUTTON1:0)|
		(is->Button[2]?CMD_BUTTON2:0)|
		(is->Button[3]?CMD_BUTTON3:0);

	// 判定各指令是否輸入
	int c, j, i;
	for (c=0; c<list->NumCommand; c++) {
		COMMAND& cmd=list->Command[c];
		
		// 確認指令的輸入
		for (i=0, j=cmd.Length-1; j>=0; j--) {
			for (; i<cmd.Limit; i++) {
				if (hist[(index-i+NUM_CMD_HIST)%NUM_CMD_HIST]==
					cmd.Input[j]) break;
			}
			if (i==cmd.Limit) break;
		}
		
		// 完成確認指令的輸入：
		// 執行指令射擊，清除歷程。
		if (j==-1) {
			CMover* mover=Group->GetManager()->GetGroup(WEAPON_GROUP)->New();
			if (mover) mover->Init(cmd.Model, this);
			for (i=0; i<NUM_CMD_HIST; i++) hist[i]=CMD_NONE;
		}
	}
	
	// 更新記錄的位置
	index=(index+1)%NUM_CMD_HIST;
}


//==============================================================
// 連續射擊與雷射共存
void CMover::ShotAndLaser(
	bool button,    // 按鈕的狀態（按下時為true）
	int min_power,  // 累積能量的最小值
	int max_gauge,  // 連續射擊計量表的最大值
	int& power,     // 累積能量
	int& gauge      // 連續射擊能量
) {
	// 按下按鈕時
	if (button) {
		
		//累積能量不足時：
		//增加累積能量，使連續射擊計量表為最大，
		//發射子彈。具體處理是以Shot函數來執行。
		if (power<min_power) {
			power++;
			gauge=max_gauge;
			Shot();
		}
	
		//累積能量足夠時：
		//使連續射擊計量表為0，發射雷射。
		else {
			gauge=0;
			CMover* mover=Group->GetManager()->GetGroup(WEAPON_GROUP)->New();
			if (mover) mover->Init(Weapon.Laser, this);
		}
	}
	
	//放開按鈕時：
	else {
		
		//連續射擊計量表>0時： 
		//發射一般子彈，將連續射擊計量表-1。
		if (gauge>0) {
			Shot();
			gauge--;
		}

		//使累積能量為0。
		power=0;
	}
}


//==============================================================
// 鎖定射擊
void CMover::LockShot(
	bool button,     // 按鈕的狀態（按下時為true）
	int min_power,   // 累積能量的最小值
	int max_gauge,   // 連續射擊計量表的最大值
	int& power,      // 累積能量
	int& gauge       // 連續射擊能量
) {
	//按下按鈕時
	if (button) {
		
		//累積能量不足時：
		//增加累積能量、使連續射擊計量表為最大，
		//發射子彈。具體處理是以Shot函數來執行。
		if (power<min_power) {
			power++;
			gauge=max_gauge;
			Shot();
		}
	
		//累積能量充足時：
		//使連續射擊計量表為0，執行鎖定射擊。
		else {
			gauge=0;
			
			//鎖定射擊：
			//追蹤敵機時，瞄準敵人。
			//（與「朝著自機飛來的子彈」原理相同）
			//未追蹤敵機時，朝自機正面方向發射子彈。
			//（與「朝自由方向發射子彈」相同）
			CMover* mover=Group->GetManager()->GetGroup(WEAPON_GROUP)->New();
			mover->Init(Weapon.Laser, this);
		}
	}
	
	//放開按鈕時：
	else {
		
		//連續射擊計量表>0時：
		//發射一般子彈，連續射擊計量表-1。
		if (gauge>0) {
			Shot();
			gauge--;
		}

		//使累積能量為0 
		power=0;

		// 解除鎖定
		ClearLockedEnemy();
	}
}




