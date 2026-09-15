#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>

static ngx_http_module_t ngx_http_autopkgtest_module_ctx = {
    NULL, /* preconfiguration */
    NULL, /* postconfiguration */

    NULL, /* create main configuration */
    NULL, /* initialize main configuration */

    NULL, /* create server configuration */
    NULL, /* merge server configuration */

    NULL, /* create location configuration */
    NULL  /* merge location configuration */
};

ngx_module_t ngx_http_autopkgtest_module = {
    NGX_MODULE_V1,
    &ngx_http_autopkgtest_module_ctx,
    NULL,
    NGX_HTTP_MODULE,

    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,

    NGX_MODULE_V1_PADDING
};
