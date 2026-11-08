sudo rm -r dist/ deb_dist/ certbot_spyderfly-0.1.0.tar.gz
cd 'certbot spyderfly'/certbot-spyderfly/
sudo rm -r dist/ deb_dist/ certbot_spyderfly-0.1.0.tar.gz

python3 setup.py --command-packages=stdeb.command bdist_deb
mv dist/ ../
mv deb_dist/ ../
mv certbot_spyderfly-0.1.0.tar.gz ../
cd ../../
