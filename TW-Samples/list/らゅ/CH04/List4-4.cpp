void SemiAutoShot(
	bool button,    // 儃僞?偺忬圃乮?偝傟偨偲true乯
	int min_power,  // 棴傔僷?乕偺嵟彫抣
	int max_power,  // 棴傔僷?乕偺嵟戝抣
	int max_gauge   // 楢幩僎乕僕偺嵟戝抣
) {
	// 棴傔僷?乕丆楢幩僎乕僕
	static int power=0, gauge=0;

	// 儃僞?傪?偟偰偄傞応?
	if (button) {
		
		// 棴傔僷?乕晄懌偺応?丗
		// 捠忢偺抏傪?偮丅
		// 嬶懱揑側??偼Shot娭?偱峴从偲偡傞丅
		if (power<min_power) Shot();
	
		// 棴傔僷?乕硐暘偺応?丗
		// 棴傔忬圃偺昞帵傪偡傞丅
		// 嬶懱揑側??偼PowerEffect娭?偱峴从偲偡傞丅
		else PowerEffect();
	
		// 棴傔僷?乕傪?傗偟丆楢幩僎乕僕傪嵟戝偵偡傞
		if (power<max_power) power++;
		gauge=max_gauge;
	}
	
	// 儃僞?傪棧偟偰偄傞応?丗
	else {
		
		// 棴傔僷?乕硐暘偺応?丗
		// 棴傔?偪抏傪?偮丗
		// 嵟戝僷?乕偺偲偼摿暿側抏傪?偮丅
		// 嬶懱揑側??偼MaxShot娭?偲BigShot娭?偱峴从偲偡傞丅
		if (min_power<=power) {
			if (power==max_power) MaxShot(); 
				else BigShot(power);
			gauge=0;
		}
		
		// 楢幩僎乕僕>0偺応?丗
		// 捠忢偺抏傪?偪丆楢幩僎乕僕傪-1偡傞丅
		// 嬶懱揑側??偼Shot娭?偱峴从偲偡傞丅
		if (gauge>0) {
			Shot();
			gauge--;
		}

		// 棴傔僷?乕傪0偵偡傞
		power=0;
	}
}
