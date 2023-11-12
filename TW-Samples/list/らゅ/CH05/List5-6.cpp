// 帺婡偺忬圃乮捠忢丆僶乕僒乕僋丆庛偄乯
typedef enum {
	NORMAL, BERSERK, WEAK
} STATE_TYPE;

// 僶乕僒乕僋忬圃偺??
void Berserk(
	int num_shot,   // 枴曽偺僔?僩偺?
	int num_enemy,  // 揋偺?
	int num_bullet  // 抏乮揋抏乯偺?
) {
	static STATE_TYPE state=NORMAL;  // 帺婡偺忬圃乮嵟?偼捠忢乯
	static int energy=0;             // 僄僱?僊乕
	static int berserk_energy=100;   // 僶乕僒乕僋忬圃偺敪摦偵
	                                 // 币梫側僄僱?僊乕
	static int time;                 // 岠壥偺巆傝?娫
	
	// 忬圃偵?偠偰暘婒偡傞
	switch (state) {
		
		// 捠忢忬圃
		case NORMAL:

			// 捠忢峌?丗
			// 嬶懱揑側??偼NormalAttack娭?偱峴从偲偡傞丅
			NormalAttack();

			// 揋傗抏偲偺?偨傝敾僝??丗
			// ?偨傞偲儈僗偵側傞丅
			// 敾僝傗?壥偺嬶懱揑側??偼HitEnemy丆
			// HitBullet丆Miss偺奺娭?偱峴从偲偡傞丅
			for (int i=0; i<num_enemy; i++)
				if (HitEnemy(i)) Miss();
			for (int i=0; i<num_bullet; i++)
				if (HitBullet(i)) Miss();

			// 枴曽偺僔?僩偲偺?偨傝敾僝??丗
			// 僄僱?僊乕傪棴傔傞丅
			// 敾僝傗?壥偺嬶懱揑側??偼HitShot丆
			// DeleteShot偺奺娭?偱峴从偲偡傞丅
			for (int i=0; i<num_shot; i++) {
				if (HitShot(i)) {
					energy++;
					DeleteShot(i);
				}
			}

			// 僄僱?僊乕検偺敾僝丗
			// 僄僱?僊乕竚硐暘偵棴傑偭偨傜
			// 僶乕僒乕僋忬圃偵堏峴偡傞丅
			// 僄僱?僊乕偼帺慠偵尭偭偰偄偔丅
			if (energy>=berserk_energy) {
				state=BERSERK;
				time=300;
			} else {
				energy--;
			}

			break;
		
		// 僶乕僒乕僋忬圃
		case BERSERK:

			// 摿庩峌?丗
			// 嬶懱揑側??偼SpecialAttack娭?偱峴从偲偡傞丅
			SpecialAttack();

			// 揋傗抏偲偺?偨傝敾僝??丗
			// 揋偵僟?乕僕傪梌稸丆抏偼徚偡丅
			// ?壥偺嬶懱揑側??偼DamageEnemy丆
			// DeleteBullet偺奺娭?偱峴从偲偡傞丅
			for (int i=0; i<num_enemy; i++)
				if (HitEnemy(i)) DamageEnemy(i);
			for (int i=0; i<num_bullet; i++)
				if (HitBullet(i)) DeleteBullet(i);
			
			// 巆傝?娫竚愗傟偨傜庛偄忬圃偵堏峴偡傞
			time--;
			if (time<=0) {
				state=WEAK;
				time=200;
			}
			
			break;
			
		// 庛偄忬圃
		case WEAK:
			
			// 揋傗抏偲偺?偨傝敾僝??丗
			// ?偨傞偲儈僗偵側傞丅
			for (int i=0; i<num_enemy; i++)
				if (HitEnemy(i)) Miss();
			for (int i=0; i<num_bullet; i++)
				if (HitBullet(i)) Miss();

			// 巆傝?娫竚愗傟偨傜捠忢忬圃偵堏峴偡傞
			time--;
			if (time<=0) {
				state=NORMAL;
				energy=0;
			}
			
			break;
	}
}
