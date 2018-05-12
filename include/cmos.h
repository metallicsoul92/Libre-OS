#ifndef LIBRE_OS_CMOS_H_
#define LIBRE_OS_CMOS_H_


struct tm *getCurrentTime();

int get_update_in_progress_flag();
unsigned char get_RTC_register(int reg);
void read_rtc();

#endif
