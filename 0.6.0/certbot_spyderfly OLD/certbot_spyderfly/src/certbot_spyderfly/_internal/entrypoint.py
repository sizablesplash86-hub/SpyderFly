""" Entry point for SpyderFly Plugin """

from certbot.plugins import common
from certbot import interfaces
from zope.interface import implementer
import os
import logging

logger = logging.getLogger(__name__)

@implementer(interfaces.IConfigurator)
class Configurator(common.Plugin, interfaces.Configurator):
    description = "SpyderFly Web Server Certbot Plugin"

    def more_info(self):
        return "Automates obtaining and deploying SSL certificates for the SpyderFly web server."

    def prepare(self):
        if not os.path.exists("/etc/spyderfly"):
            logger.warning("SpyderFly config directory /etc/spyderfly not found.")

    def get_chall_pref(self, domain):
        return []

    def perform(self, achalls):
        responses = []
        for achall in achalls:
            response = achall.response(achall.account.key)
            responses.append(response)
        return responses

    def cleanup(self, achalls):
        pass

    def deploy_cert(self, domain, cert_path, key_path, chain_path, fullchain_path):
        target_dir = f"/etc/letsencrypt/live/{domain}"
        os.makedirs(target_dir, exist_ok=True)
        
        target_fullchain = os.path.join(target_dir, "fullchain.pem")
        target_privkey = os.path.join(target_dir, "privkey.pem")

        with open(fullchain_path, "r") as src, open(target_fullchain, "w") as dst:
            dst.write(src.read())

        with open(key_path, "r") as src, open(target_privkey, "w") as dst:
            dst.write(src.read())

        logger.info(f"Successfully deployed SSL certificates for {domain} to {target_dir}")

    def enhance(self, domain, enhancement, options=None):
        pass

    def supported_enhancements(self):
        return []

    def save(self, title=None, summarize=True):
        pass

    def rollback_checkpoints(self, flow=None):
        pass

    def recovery_routine(self, flow=None):
        pass

    def restart(self):
        pass

ENTRYPOINT = Configurator
