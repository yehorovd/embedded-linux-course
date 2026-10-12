#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/string.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Danylo");
MODULE_DESCRIPTION("Lab 02 hello module for Raspberry Pi 4B");
MODULE_VERSION("1.0");

static char *name = "Danylo";
module_param(name, charp, 0444);
MODULE_PARM_DESC(name, "Name printed when the module loads");

static unsigned int count = 1;
module_param(count, int, 0444);
MODULE_PARM_DESC(count, "Count of greatings");


static int __init hello_init(void)
{
    if (!name || name[0] == '\0')
        return -EINVAL;

    if (count < 1 || count > 10) {
        return -EINVAL;
    }

    for (unsigned int i = 0; i < count; i++) {
        pr_info("hello_module: Hello, %s, from kernel space on RPi! %i/%i\n", name, i+1, count);
    }
    return 0;
}

static void __exit hello_exit(void)
{
    pr_info("hello_module: Goodbye from kernel space on RPi!\n");
}

module_init(hello_init);
module_exit(hello_exit);
