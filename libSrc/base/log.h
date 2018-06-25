#ifndef _PEACE_BASE_LOG_H_
#define _PEACE_BASE_LOG_H_

#include <stdio.h>

namespace peace {
namespace base {

#define LOGD(fmt,...) printf("file: "__FILE__", line: %05d: "fmt"\n", __LINE__, ##__VA_ARGS__)

/*int loglevel = 5;
#define udi_info_log(fmt,...) if(levelog >= 1) syslog(LOG_INFO, "time:%s, file: %s, line: %05d: "fmt"", get_cur_time_us(),__FILE__, __LINE__, ##__VA_ARGS__)
#define udi_erro_log(fmt,...) if(levelog >= 2) syslog(LOG_ERR, "time:%s, file: %s, line: %05d: "fmt"", get_cur_time_us(),__FILE__, __LINE__, ##__VA_ARGS__)
#define udi_warning_log(fmt,...) if(levelog >= 3) syslog(LOG_WARNING, "time:%s, file: %s, line: %05d: "fmt"", get_cur_time_us(),__FILE__, __LINE__, ##__VA_ARGS__)
#define udi_alert_log(fmt,...) if(levelog >= 4) syslog(LOG_ALERT, "time:%s, file: %s, line: %05d: "fmt"", get_cur_time_us(),__FILE__, __LINE__, ##__VA_ARGS__)
#define udi_crit_log(fmt,...) if(levelog == 5) syslog(LOG_CRIT, "time:%s, file: %s, line: %05d: "fmt"", get_cur_time_us(),__FILE__, __LINE__, ##__VA_ARGS__) 
*/

}
}

#endif

