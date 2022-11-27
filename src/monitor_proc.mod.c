#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(.gnu.linkonce.this_module) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section(__versions) = {
	{ 0xdd8f8694, "module_layout" },
	{ 0x428db41d, "kmalloc_caches" },
	{ 0x1d8f45ba, "single_open" },
	{ 0x779a18af, "kstrtoll" },
	{ 0x37669270, "single_release" },
	{ 0x375cb97e, "seq_printf" },
	{ 0x9cfebac4, "remove_proc_entry" },
	{ 0x5e5292c, "filp_close" },
	{ 0x3c3ff9fd, "sprintf" },
	{ 0x40970142, "seq_read" },
	{ 0xc973ee21, "kernel_read" },
	{ 0xc5850110, "printk" },
	{ 0xa7eedcc4, "call_usermodehelper" },
	{ 0xdecd0b29, "__stack_chk_fail" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0xca7a3159, "kmem_cache_alloc_trace" },
	{ 0x1be63b22, "seq_lseek" },
	{ 0x37a0cba, "kfree" },
	{ 0x222e7ce2, "sysfs_streq" },
	{ 0x24ff48a4, "proc_create" },
	{ 0x362ef408, "_copy_from_user" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0xddd346a3, "filp_open" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "575D22D48C9D0C4C533D972");
