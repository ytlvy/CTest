#!/usr/sbin/dtrace -s

syscall::read:entry,
syscall::write:entry
/pid == 9627/
{

}