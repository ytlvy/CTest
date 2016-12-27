#!/usr/sbin/dtrace -s

objc$target::thread_start:entry
/ execname == "KWPlayer" /
{
    self->ts = timestamp;
}

objc$target::thread_start:return
/ execname == "KWPlayer" && self->ts != 0 /
{
    @totals[probefunc] = sum(timestamp - self->ts);
}

END
{
    printa(@totals);
}