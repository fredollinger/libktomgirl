#
# Regular cron jobs for the libktomgirl package
#
0 4	* * *	root	[ -x /usr/bin/libktomgirl_maintenance ] && /usr/bin/libktomgirl_maintenance
