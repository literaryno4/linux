#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/tracepoint.h>
#include <trace/events/sched.h>

static void my_sched_switch_handler(void *ignore,
				    bool preempt,
				    struct task_struct *prev,
				    struct task_struct *next,
				    unsigned int state)
{
	printk(KERN_INFO "Sched switch: %s [%d] ==> %s [%d]\n",
	       prev->comm, prev->pid, next->comm, next->pid);
}

static int __init hello_init(void) {
	int ret;

        ret = register_trace_sched_switch(my_sched_switch_handler, NULL);
	if (ret) {
		printk(KERN_ERR "Failed to register sched switch tracepoint handler.\n");
	}

	printk(KERN_INFO "Loaded hello module.\n");
	return 0;
}

static void __exit hello_exit(void) {
	unregister_trace_sched_switch(my_sched_switch_handler, NULL);
	printk(KERN_INFO "exit\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
