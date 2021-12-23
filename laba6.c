#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/ktime.h>
#include <linux/slab.h>

struct main_list {
 struct main_list *attached;
 ktime_t time;
 };

MODULE_AUTHOR("Ivan Kucherenko IV-91");
MODULE_DESCRIPTION("Laba6");
MODULE_LICENSE("Dual BSD/GPL");

static struct main_list *stellar;

static int amount = 1;
module_param(amount, uint, 0444);
MODULE_PARM_DESC(amount, "Amount of outputs");

static int __init helloinit(void){
 uint i;

 struct main_list *var_1, *var_2;

 stellar = kmalloc(sizeof(struct main_list *), GFP_KERNEL);

 var_1 = stellar;
 if (amount == 0) {
    pr_warn("Amount is identical to 0");
 } else if (amount >= 5 && amount <= 10) {
    pr_warn("Amount is in range in 5 to 10");
 }
 BUG_ON(amount > 10);

 for (i = 0; i < amount; i++) {
    var_1->attached = kmalloc(sizeof(struct main_list), GFP_KERNEL);
    if(i == 6) var_1 = NULL;
    var_1->time = ktime_get();
    pr_info("Hello World!");
    var_2 = var_1;
    var_1 = var_1->attached;
 }

 if (amount != 0) {
    kfree(var_2->attached);
    var_2->attached = NULL;
 }

 pr_info("Amount: %d\n", amount);

 return 0;
}

static void __exit helloexit(void){
 struct main_list *var;

 while (stellar != NULL && amount != 0) {
    var = stellar;
    pr_info("Time: %lld", var->time);
    stellar = var->attached;
    kfree(var);
 }
 pr_info("");
}

module_init(helloinit);
module_exit(helloexit);