

/*
 * Date:2021-12-06 21:06
 * filename:requestData.cpp
 *
 */

#include "requestData.h"
#include "util.h"
#include "epoll.h"
#include <sys/epoll.h>
#include <unistd.h>
#include <sys/time.h>
#include <unordered_map>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <queue>

#include <iostream>
using namespace std;

pthread_mutex_t qlock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t MimeType::lock = PTHREAD_MUTEX_INITIALIZER;
std::unordered_map<std::string, std::string> MimeType::mime;

std::string MimeType::getMime(const std::string& suffix) {
	if (mime.size() == 0) {
		pthread_mutex_lock(&lock);

		if (mime.size() == 0) {
			mime[".html"] = "text/html";
			mime[".avi"] = "video/x-msvideo";
			mime[".bmp"] = "image/bmp";
			mime[".c"] = "text/plain";
			mime[".doc"] = "application/msword";
			mime[".gif"] = "image/gif";
			mime[".gz"] = "application/x-gzip";
			mime[".htm"] = "text/html";
			mime[".ico"] = "application/x-ico";
			mime[".jpg"] = "image/jpeg";
			mime[".png"] = "image/png";
			mime[".txt"] = "text/plain";
			mime[".mp3"] = "audio/mp3";
			mime["default"] = "text/html";
		}
		pthread_mutex_unlock(&lock);
	}
	if (mime.find(suffix) == mime.end())
		return mime["defalut"];
	else
		return mime[suffix];
}

priority_queue<mytimer*, deque<mytimer*>, timerCmp> myTimerQueue;

requestData::requestData() : againTimes(0), now_read_pos(0), state(STATE_PARSE_URI), h_state(h_start),
	 keep_alive(false),timer(NULL) {
		cout << "requestData constructed" << endl;
}

requestData::requestData(int _epollfd, int _fd, std::string _path) : 
	againTimes(0), path(_path), fd(_fd), epollfd(_epollfd), now_read_pos(), state(STATE_PARSE_URI), h_state(h_start),
	keep_alive(false), timer(NULL) {
}



