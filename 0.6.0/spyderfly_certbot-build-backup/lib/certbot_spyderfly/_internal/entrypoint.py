import logging
import os
from typing import Any, Optional
from acme import challenges
from certbot import achallenges, errors
from certbot.display import util as display_util
from certbot.plugins import common

logger = logging.getLogger(__name__)

class SpyderFlyConfigurator(common.Configurator):
    """SpyderFly plugin for Certbot using direct file stream manipulation."""
    
    description = "SpyderFly Web Server plugin"
    SITES_DIR = "/etc/spyderfly/sites-available"

    def __init__(self, *args: Any, **kwargs: Any) -> None:
        super().__init__(*args, **kwargs)
        self.save_notes = ""

    @classmethod
    def add_parser_arguments(cls, add: Any) -> None:
        """Add plugin-specific arguments if needed."""
        pass

    def more_info(self) -> str:
        """Human-readable string to help understand the module."""
        return "Configures SpyderFly web server to install HTTPS."

    def prepare(self) -> None:
        """Prepare the configurator and verify site directories."""
        if not os.path.isdir(self.SITES_DIR):
            logger.info("Sites directory %s does not exist, creating it.", self.SITES_DIR)
            try:
                os.makedirs(self.SITES_DIR, exist_ok=True)
            except OSError as e:
                raise errors.PluginError(f"Failed to create sites directory: {e}")

    def get_all_names(self) -> set[str]:
        """Scan .site files for domain names defined in server blocks."""
        all_names = set()
        
        if not os.path.exists(self.SITES_DIR):
            return all_names

        for filename in os.listdir(self.SITES_DIR):
            if filename.endswith(".site"):
                fullpath = os.path.join(self.SITES_DIR, filename)
                try:
                    with open(fullpath, "r") as f:
                        for line in f:
                            line = line.strip()
                            if line.startswith("server_name"):
                                parts = line.split()
                                if len(parts) >= 2:
                                    domain = parts[1].rstrip(";")
                                    all_names.add(domain)
                except OSError:
                    continue
        return all_names

    def deploy_cert(self, domain: str, cert_path: str, key_path: str, chain_path: str,
                    fullchain_path: str) -> None:
        """Inject SSL directives into the matching .site file."""
        target_file = None

        if not os.path.exists(self.SITES_DIR):
            os.makedirs(self.SITES_DIR, exist_ok=True)

        for filename in os.listdir(self.SITES_DIR):
            if filename.endswith(".site"):
                fullpath = os.path.join(self.SITES_DIR, filename)
                try:
                    with open(fullpath, "r") as f:
                        if domain in f.read():
                            target_file = fullpath
                            break
                except OSError:
                    continue

        if not target_file:
            target_file = os.path.join(self.SITES_DIR, f"{domain}.site")
            with open(target_file, "w") as f:
                f.write(f"server {{\n    server_name {domain};\n    listen 443;\n}}\n")

        with open(target_file, "r") as f:
            config_data = f.read()

        ssl_block = (
            f"    ssl_certificate {fullchain_path};\n"
            f"    ssl_certificate_key {key_path};\n"
            f"    ssl_trusted_certificate {chain_path};"
        )

        last_brace = config_data.rfind("}")
        if last_brace != -1:
            config_data = config_data[:last_brace] + "\n" + ssl_block + "\n" + config_data[last_brace:]

        with open(target_file, "w") as f:
            f.write(config_data)

        self.save_notes += f"Injected SSL certificates for {domain} into {target_file}\n"
        display_util.notify(f"Successfully deployed certificate for {domain} via SpyderFly plugin.")

    def supported_enhancements(self) -> list[str]:
        return []

    def enhance(self, domain: str, enhancement: str, options: Any = None) -> None:
        pass

    def get_chall_pref(self, unused_identifier: str) -> list[type[challenges.Challenge]]:
        return [challenges.HTTP01]

    def perform(self, achalls: list[achallenges.AnnotatedChallenge]) -> list[challenges.ChallengeResponse]:
        return []

    def cleanup(self, achalls: list[achallenges.AnnotatedChallenge]) -> None:
        pass

    def restart(self) -> None:
        logger.info("SpyderFly certificate deployment completed.")

    def config_test(self) -> None:
        pass

    def save(self, title: Optional[str] = None, temporary: bool = False) -> None:
        pass

    def recovery_routine(self) -> None:
        pass

    def revert_challenge_config(self) -> None:
        pass

    def rollback_checkpoints(self, rollback: int = 1) -> None:
        pass
