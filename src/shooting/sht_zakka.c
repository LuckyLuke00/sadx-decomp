#include "decls.h"

// STUB: SADX 0x007f1570
void ZakkaDisp(struct task *tp)
{
}

// FUNCTION: SADX 0x007f1680
void sht_TV1(struct task *tp)
{
	tp->twp->wtimer = 0;
	tp->exec = ZakkaTask;
	ZakkaTask(tp);
}

// FUNCTION: SADX 0x007f16a0
void sht_ISU1(struct task *tp)
{
	tp->twp->wtimer = 1;
	tp->exec = ZakkaTask;
	ZakkaTask(tp);
}

// FUNCTION: SADX 0x007f16c0
void sht_ISU2(struct task *tp)
{
	tp->twp->wtimer = 2;
	tp->exec = ZakkaTask;
	ZakkaTask(tp);
}

// FUNCTION: SADX 0x007f16e0
void sht_TANSU(struct task *tp)
{
	tp->twp->wtimer = 3;
	tp->exec = ZakkaTask;
	ZakkaTask(tp);
}

// FUNCTION: SADX 0x007f1700
void sht_KABIN(struct task *tp)
{
	tp->twp->wtimer = 4;
	tp->exec = ZakkaTask;
	ZakkaTask(tp);
}

// FUNCTION: SADX 0x007f1720
void sht_KAIGA(struct task *tp)
{
	tp->twp->wtimer = 5;
	tp->exec = ZakkaTask;
	ZakkaTask(tp);
}

// FUNCTION: SADX 0x007f1740
void sht_TV2(struct task *tp)
{
	tp->twp->wtimer = 6;
	tp->exec = ZakkaTask;
	ZakkaTask(tp);
}

// FUNCTION: SADX 0x007f1760
void sht_REIZOU(struct task *tp)
{
	tp->twp->wtimer = 7;
	tp->exec = ZakkaTask;
	ZakkaTask(tp);
}

// FUNCTION: SADX 0x007f1780
void sht_SOFA(struct task *tp)
{
	tp->twp->wtimer = 8;
	tp->exec = ZakkaTask;
	ZakkaTask(tp);
}

// FUNCTION: SADX 0x007f17a0
void sht_TANA(struct task *tp)
{
	tp->twp->wtimer = 9;
	tp->exec = ZakkaTask;
	ZakkaTask(tp);
}

// FUNCTION: SADX 0x007f17c0
void sht_YAKAN(struct task *tp)
{
	tp->twp->wtimer = 10;
	tp->exec = ZakkaTask;
	ZakkaTask(tp);
}
