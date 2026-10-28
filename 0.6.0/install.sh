set -e

# this is to have the main install script

LAT_VER="https://repo.sizablesplash.com/spyderfly/releases/latest.deb"
CRTB_LAT="https://repo.sizablesplash.com/spyderfly/certbot/releases/latest.deb"
SPYDRFLY_TMP="/tmp/spyderfly.deb"


echo "[*] Installing latest SpyderFly version..."

if ! ls $MAIN_DIR &> /dev/null; then
while true; do
    read -p "Would you like to install Certbot SpyderFly? (y/n): " yn
    case $yn in
        [Yy]* ) 
            echo "Not setup yet"

            # # # # # # #

            # Add your positive action code here
            break
            ;;
        [Nn]* ) 
            echo "If you ever change your mind, run sudo spyderfly --certbot to do the install"
            # Add your negative action or exit code here
            break
            ;;
        * ) 
            echo "Please answer yes (y) or no (n)."
            ;;
    esac
done
fi

echo "Downloading package..."

curl -SSL "$LAT_VER" -o "$SPYDRFLY_TMP"

echo "Installing SpyderFly..."
sudo apt install "$SPYDRFLY_TMP" -y

sudo rm "$SPYDRFLY_TMP"

echo "SpyderFly installed! Thank you for choosing SpyderFly!"
