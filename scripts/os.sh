#!/bin/bash
set -e

PKG_TYPE="${1:-debian}"

echo "Building SpyderFly package for: $PKG_TYPE"

case "$PKG_TYPE" in
    debian)
        # Your existing stdeb / pybuild pipeline
        python3 setup.py --command-packages=stdeb.command bdist_deb
        echo "Debian package built in deb_dist/"
        ;;
    rpm)
        # Create tarball and build RPM
        mkdir -p ~/rpmbuild/{SOURCES,SPECS}
        tar -czf ~/rpmbuild/SOURCES/spyderfly-0.6.0.tar.gz --exclude=.git .
        cp pkg/rpm/spyderfly.spec ~/rpmbuild/SPECS/
        rpmbuild -ba ~/rpmbuild/SPECS/spyderfly.spec
        echo "RPM package built in ~/rpmbuild/RPMS/"
        ;;
    arch)
        # Build Arch package
        cd pkg/arch
        makepkg -si
        echo "Arch package built locally."
        ;;
    *)
        echo "Unknown package type: $PKG_TYPE (Choose: debian, rpm, arch)"
        exit 1
        ;;
esac
