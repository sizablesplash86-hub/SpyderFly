from setuptools import setup, find_packages

setup(
    name='certbot-spyderfly',
    version='0.1.0',
    description='SpyderFly plugin for Certbot',
    long_description='SpyderFly Web Server plugin for Certbot to automate SSL/TLS certificates.',
    long_description_content_type='text/plain',
    packages=find_packages(where='src'),
    package_dir={'': 'src'},
    include_package_data=True,
    install_requires=[
        'certbot',
        'zope.interface',
    ],
    entry_points={
        'certbot.plugins': [
            'spyderfly = certbot_spyderfly._internal.entrypoint:SpyderFlyConfigurator',
        ],
    },
)