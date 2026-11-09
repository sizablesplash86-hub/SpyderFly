#!/bin/sh
set -e

LATE_VER="https://repo.sizablesplash.com/spyderfly/releases/latest/spyderfly_latest_amd64.deb"
TEMP_DEB="$(mktemp /tmp/spyderfly-XXXXXX.deb)"

echo "Downloading latest version..."

curl -sSL "$LATE_VER" -o "$TEMP_DEB"
sudo apt-get install -y "$TEMP_DEB"
sudo rm "$TEMP_DEB"
