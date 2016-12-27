/* run with
 * dtrace -s malloctime.d -c ./simple
 */

pid$target::malloc:entry
{
    entry_time = timestamp;
}

pid$target::malloc:return
{
    delta_time = timestamp - entry_time;
    printf ("the call to malloc took %d ns", delta_time);
}
