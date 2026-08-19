#include <stdio.h>
#include <dlfcn.h>

// 直接声明核心库函数（无需头文件）
extern void core_detect(void);
extern int core_add(int a, int b);

// 插件函数指针类型
typedef int (*plugin_init_fn)(void);
typedef void (*plugin_run_fn)(void);

int main(void) {
    // 1. 使用核心库功能（通过 soname 链接）
    printf("=== Core library ===\n");
    core_detect();
    printf("core_add(3,5) = %d\n", core_add(3, 5));

    // 2. 加载插件（通过 dlopen 动态加载）
    printf("\n=== Plugin ===\n");
    void *handle = dlopen("./plugin.so", RTLD_NOW);
    if (!handle) {
        fprintf(stderr, "Failed to load plugin: %s\n", dlerror());
        return 1;
    }

    // 获取插件函数
    plugin_init_fn init_fn = (plugin_init_fn)dlsym(handle, "plugin_init");
    plugin_run_fn run_fn = (plugin_run_fn)dlsym(handle, "plugin_run");
    if (!init_fn || !run_fn) {
        fprintf(stderr, "Failed to find plugin functions\n");
        dlclose(handle);
        return 1;
    }

    // 调用插件
    init_fn();
    run_fn();

    // 保持插件加载状态（可调用 dlclose(handle) 卸载）
    dlclose(handle);

    return 0;
}