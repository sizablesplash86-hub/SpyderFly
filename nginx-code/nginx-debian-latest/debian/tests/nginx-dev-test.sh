#!/bin/sh
set -eu

# nginx binnary in in the /usr/sbin
PATH="/usr/sbin:${PATH}"
export PATH

nginx_src=/usr/share/nginx/src
test_dir="$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)"
module_src="$test_dir/nginx-dev-test"
build_dir="$AUTOPKGTEST_TMP/build"
module="$build_dir/ngx_http_autopkgtest_module.so"

mkdir -p "$build_dir"

# conf_flags contains a Bash array, so use Bash for the build commands.
bash -eu -o pipefail -c '
    module_src=$1
    build_dir=$2
    nginx_src=$3

    # Match Debian::Debhelper::Buildsystem::nginx_mod: evaluate conf_flags
    # from the external module source directory.
    cd "$module_src"
    . "$nginx_src/conf_flags"

    cd "$nginx_src"
    ./configure \
        "${NGX_CONF_FLAGS[@]}" \
        --add-dynamic-module="$module_src" \
        --builddir="$build_dir"

    make -f "$build_dir/Makefile" modules
' sh "$module_src" "$build_dir" "$nginx_src"

test -s "$module"

# Verify that the resulting module is loadable by the matching nginx binary.
cat >"$AUTOPKGTEST_TMP/nginx.conf" <<EOF
load_module $module;
error_log stderr;
pid $AUTOPKGTEST_TMP/nginx.pid;

events {}

http {}
EOF

mkdir -p "$AUTOPKGTEST_TMP/prefix"

nginx -t -q \
    -p "$AUTOPKGTEST_TMP/prefix/" \
    -c "$AUTOPKGTEST_TMP/nginx.conf"
