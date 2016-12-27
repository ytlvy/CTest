#!/usr/sbin/dtrace -s

syscall::write:entry
{
    self->ts = timestamp;
}

syscall::write:return
/self->ts/
{
    @time[execname] = quantize(timestamp - self->ts);
    self->ts = 0;
}


//syscall::write:entry
//{
//    @fds[execname] = lquantize(arg0, 0, 100, 1);
//}