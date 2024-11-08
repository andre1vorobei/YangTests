//compile
//new: gcc -L/home/andrei/libe/libyang/build/ -Wl,-rpath,/home/andrei/libe/libyang/build/ c.cpp -o c -lyang

#include <stdio.h>

#define PATH_TO_NEW "/home/andrei/libe/libyang/src/libyang.h"

#ifdef PATH_TO_NEW
// #include PATH_TO_NEW
#include "/home/andrei/libe/libyang/build/libyang/libyang.h"
#else
#include <libyang/libyang.h>
#endif

int main()
{
#ifdef PATH_TO_NEW
    ly_ctx *ctx;
    lys_module *mod;
    lyd_node *tree;
    lyd_node *diff;

    FILE *f = fopen("inputfile.xml", "r");

    ly_out *lo;
    ly_out_new_fd(1, &lo);
    
    ly_in *li;
    ly_in_new_file(f, &li);

    ly_ctx_new("yangs/", 0, &ctx);
    mod = ly_ctx_load_module(ctx, "example", 0, 0);
    ly_ctx_load_module(ctx, "zelax-keepalive", 0, 0);
    // lys_print_module(lo, mod, LYS_OUT_YANG, 0, 0);

    lyd_parse_data(ctx, 0, li, LYD_XML, LYD_PARSE_ONLY,0, &tree);
    lyd_print_tree(lo, tree, LYD_XML,0);
    printf("\n");
    lyd_new_path(tree, ctx, "/example:data/interface[name='eth3']", 0, LYD_NEW_PATH_UPDATE, 0);

    lyd_print_tree(lo, tree, LYD_XML,0);

    // printf("%d\n", lyd_validate_module(&tree, mod, 0, &diff));
    // lyd_print_tree(lo, diff, LYD_XML,0);

#else
    ly_ctx *ctx = ly_ctx_new("/usr/share/zelax-sdwan-controller/yang-modules/", 0);
#endif


}