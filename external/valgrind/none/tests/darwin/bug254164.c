

#include <stdio.h>
#include <sys/resource.h>

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <mach/task.h>
#include <mach/mach_init.h>

void getres(task_t task, unsigned int *rss, unsigned int *vs)
{
    struct task_basic_info t_info;
    mach_msg_type_number_t t_info_count = TASK_BASIC_INFO_COUNT;
    
    task_info(task, TASK_BASIC_INFO, (task_info_t)&t_info, &t_info_count);
    *rss = t_info.resident_size;
    *vs = t_info.virtual_size;
}


int main(void)
{
    unsigned int rss, vs;
    task_t task = MACH_PORT_NULL;
    
    if (task_for_pid(current_task(), getpid(), &task) != KERN_SUCCESS)
        abort();
    
    getres(task, &rss, &vs);
    
    
    return 0;
}

