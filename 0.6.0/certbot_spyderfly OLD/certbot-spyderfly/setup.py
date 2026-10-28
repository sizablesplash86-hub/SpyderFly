from setuptools import setup

version = '0.1.0'

install_requires = [
    f'certbot[spyderfly]>={version}',
]

setup(
    version=version,
    install_requires=install_requires,
)