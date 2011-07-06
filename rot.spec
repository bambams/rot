Name:           rot
Version:        1.0.0
Release:        1%{?dist}
Summary:        rot is a cipher utility for character rotation ciphers.

License:        GPLv2+
URL:            https://github.com/bamccaig/rot/
Source0:        https://www.castopulence.org/rot-1.0.0.tar.gz

#BuildRequires:  
#Requires:       

%description
Rot is a simple utility that does rotation based ciphers i.e., rot13,
rot47, and is flexible enough to handle arbitrary rules based on ranges of
characters (8-bit).

%prep
%setup -q


%build
premake4 gmake
make %{?_smp_mflags}


%install
rm -rf $RPM_BUILD_ROOT
#make install DESTDIR=$RPM_BUILD_ROOT
install -m 755 -d %{buildroot}/usr/bin
install -m 755 rot %{buildroot}%{_bindir}/


%files
%doc COPYING README
%{_bindir}/rot


%changelog
* Wed Jul 06 2011 Brandon McCaig <bamccaig@gmail.com> 1.0.0-1
- Initial spec.

