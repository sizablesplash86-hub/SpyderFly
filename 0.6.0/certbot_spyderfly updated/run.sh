sudo rm -rf build/ deb_dist/ src/*.egg-info dist/
python3 setup.py --command-packages=stdeb.command bdist_deb
