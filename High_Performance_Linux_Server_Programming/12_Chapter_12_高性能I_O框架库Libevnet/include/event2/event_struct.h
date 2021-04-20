
#ifndef EVENT_STRUCT
#define EVENT_STRUCT

struct evnet
{
	TAILQ_ENTRY(event) ev_active_next;
	TAILQ_ENTRY(event) ev_next;
	union
	{
		TAILQ_ENTRY(event) ev_next_with_common_timeout;
		int min_heap_idx;
	}ev_timeout_pos;

	evutil_socket_t ev_fd;
	
	struct event_base* ev_base;

	union
	{
		struct
		{
			TAILQ_ENTRY(event) ev_io_next;
			struct timeval ev_tieout;
		}ev_io;

		struct
		{
			TAILQ_ENTRY(event) ev_signal_next;
			short ev_ncalls;
			short *ev_pncalls;
		}ev_signal;
	}_ev;

	short ev_events;
	short ev_res;
	short rv_flags;
	ev_uint8_t ev_pri;
	ev_uint8_t ev_closure;
	struct timeval ev_timeout;

	void (*ev_callback) (evutil_socket_t,short,void *arg);
	void *ev_arg;

};

#define EVLIST_TIMEOUT 0x01
#define EVLIST_INSERTED 0x02
#define EVLIST_SIGNAL 0x04
#define EVLIST_ACTIVE 0x08
#define EVLIST_INTERNAL 0x10
#define EVLIST_INIT 0x80
#define EVLIST_ALL (0xf000 | 0x9f)

#endif
