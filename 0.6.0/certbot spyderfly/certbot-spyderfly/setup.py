from setuptools import setup, find_packages

setup(
    name="certbot-spyderfly",
    version="0.1.0",
    packages=find_packages(where="src"),
    package_dir={"": "src"},
    long_description="",  # Explicitly prevents the NoneType crash
    entry_points={
        "certbot.plugins": [
            "spyderfly = certbot_spyderfly._internal.entrypoint:SpyderFlyConfigurator",
        ],
    },
)
