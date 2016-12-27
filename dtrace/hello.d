#!/usr/sbin/dtrace -s


dtrace:::BEGIN
{
    trace("hello, world");
    exit(0);
}