float ratioToDb(float ratio){
	return 20*log10f(ratio);
}

float dbToRatio(float db){
	// Volume is coming in in dbfs
	// 0.0 dbfs = gain of 1
	// gain (db) = 20*log10(in/out)
	// Therefore, in/out = 10^(gain(db)/20)
	return 10^(db/20);
}