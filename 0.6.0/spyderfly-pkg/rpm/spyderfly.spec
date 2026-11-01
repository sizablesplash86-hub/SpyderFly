# currently a placeholder for if I desire to someday add this


Name:           spyderfly
Version:        0.6.0
Release:        1%{?dist}
Summary:        A high-performance custom C web server and reverse proxy

License:        MIT
URL:            https://sizablesplash.com
Source0:        %{name}-%{version}.tar.gz

BuildRequires:  gcc make systemd-rpm-macros
Requires:       openssl

%description
SpyderFly is a custom C-based web server featuring a master-worker process 
architecture, reverse proxying, and native systemd/Certbot integration.

%prep
%autosetup

%build
%make_build

%install
# Install binary
install -D -m 0755 src/spyderfly %{buildroot}%{_bindir}/spyderfly

# Install systemd service
install -D -m 0644 spyderfly.service %{buildroot}%{_unitdir}/spyderfly.service

# Install default site directories
install -d -m 0755 %{buildroot}%{_sysconfdir}/spyderfly/sites-available

%post
%systemd_post spyderfly.service

%preun
%systemd_preun spyderfly.service

%postun
%systemd_postun_with_restart spyderfly.service

%files
%{_bindir}/spyderfly
%{_unitdir}/spyderfly.service
%dir %{_sysconfdir}/spyderfly
%dir %{_sysconfdir}/spyderfly/sites-available

%changelog
* Mon Oct 26 2026 Trevor Bergstrom <trevor@sizablesplash.com> - 0.6.0-1
- Initial RPM release of SpyderFly
