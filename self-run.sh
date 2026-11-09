#!/bin/sh
set -e

MAIN_DIR="/etc/spyderfly"
SITES_DIR="/etc/spyderfly/enabled-sites"
CONF_DIR="/etc/spyderfly/config"
DIS_SITE="/etc/spyderfly/disabled-sites"
LOG_DIR="/var/log/spyderfly"
MAIN_CONF="/etc/spyderfly/spyderfly.conf"
SRVCE="/etc/systemd/system/spyderfly.service"

echo "Welcome to the Spyderfly beta auto compiler!"
echo "Any bugs with this are part of the process. I am not responsible for any OS breaking bugs caused to your system."
echo "-sizablesplash"

mkdir -p "$MAIN_DIR" "$SITES_DIR" "$CONF_DIR" "$DIS_SITE" "$LOG_DIR"

gcc src/core/*.c src/auto-config/*.c -o /usr/sbin/spyderfly -lssl -lcrypto

sudo spyderfly -s
