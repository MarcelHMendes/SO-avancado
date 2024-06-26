/*
 * test_ping.c - sends ping echo requests
 */

#include <stdio.h>

#include <base/log.h>
#include <net/ping.h>
#include <runtime/runtime.h>
#include <runtime/timer.h>
#include <net/icmp.h>

#define N_PINGS 32
#define DEST_IP_ADDR 168427777 // 10.10.1.1

static void main_handler(void *arg)
{
	int i, ret;

	ret = net_ping_init();
	if (ret) {
		log_err("failed to init ping");
		return;
	}

	for (i = 0; i < N_PINGS; i++) {
		net_send_ping(i, DEST_IP_ADDR);

		/* wait 1 second before sending next ping */
		timer_sleep(1000*1000);
		//leep(1);
	}
}

int main(int argc, char *argv[])
{
	int ret;

	if (argc < 2) {
		printf("arg must be config file\n");
		return -EINVAL;
	}

	ret = runtime_init(argv[1], main_handler, NULL);

	if (ret) {
		printf("failed to start runtime\n");
		return ret;
	}

	return 0;
}
