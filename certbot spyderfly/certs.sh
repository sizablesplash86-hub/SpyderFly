sudo apt remove python3-certbot-spyderfly -y
sudo apt install ./deb_dist/python3-certbot-spyderfly_0.1.0-1_all.deb

sudo rm -rf /etc/letsencrypt/archive/test.sizablesplash.com
sudo rm -rf /etc/letsencrypt/live/test.sizablesplash.com
sudo rm /etc/letsencrypt/renewal/test.sizablesplash.com.conf

sudo certbot --spyderfly -d test.sizablesplash.com
