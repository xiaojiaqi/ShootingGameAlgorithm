// 揋偺忬圃丗
// 捠忢丆曔懆
typedef enum {
	NORMAL, CAPTURED
} CAPTOR_STATE;

// 帺婡傪偲傜稸傞揋偺摦
void Captor(
	bool capture  // 崱夞丆曔懆峌?傪偡傞偐偳从偐
) {
	static int state=NORMAL;  // 揋偺忬圃
	
	// 忬圃偵傛偭偰暘婒偡傞
	switch (state) {
		
		// 捠忢忬圃丗
		// 捠忢峌?傑偨偼曔懆峌?傪峴从丅
		// 曔懆峌?竚惉岟偟偨傜曔懆忬圃偵堏傞丅
		// 峌?偺嬶懱揑側??偼丆CaptureAttack丆
		// NormalAttack偺奺娭?偱峴从偲偡傞丅
		case NORMAL:
			if (capture) {
				if (CaptureAttack()) state=CAPTURED;
			} else {
				NormalAttack();
			}
			break;
		
		// 曔懆忬圃丗
		// 捠忢峌?傪峴从丅
		// 攋夡偝傟偨傜帺婡傪曉偟偨屻偵徚柵偡傞丅
		// 敾僝側偳偺嬶懱揑側??偼丆Destroyed丆
		// ReturnMyShip丆Delete偺奺娭?偱峴从偲偡傞丅
		case CAPTURED:
			NormalAttack();
			if (Destroyed()) {
				ReturnMyShip();
				Delete();
			}
			break;
	}
}

