ltsv
====
simple LTSV parser implemented by C

e.g.
----
	struct ltsv ltsv;
	
	ltsv_open(&ltsv, "sample.ltsv");
	
	while (ltsv_get(&ltsv) == 0) {
		printf("%d:%d	",
		    LTSV_LINE(&ltsv),
		    LTSV_COLUMN(&ltsv));
	
		printf("key=%s	value=%s\n",
		    LTSV_KEY(&ltsv),
		    LTSV_VALUE(&ltsv));
	}
	
	ltsv_close(&ltsv);

Reference
---------
* [LTSV] Labeled Tab-separated Values http://ltsv.org/  
* [What is ltsv?] http://d.hatena.ne.jp/naoya/20130209/1360381374 (in japanese)  
