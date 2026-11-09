from certbot import interfaces
from certbot.plugins import common

class SpyderFlyConfigurator(common.Plugin, interfaces.IAuthenticator, interfaces.IInstaller):
    description = "SpyderFly Web Server plugin"

    @classmethod
    def add_parser_arguments(cls, add):
        add("conf-path", default="/home/daemoncraft/spyderfly.conf", help="Path to SpyderFly configuration file.")

    def prepare(self):
        pass

    def more_info(self):
        return "A Certbot plugin for the custom SpyderFly C web server."

    def get_chall_pref(self, domain):
        from certbot.plugins import challenges
        return [challenges.HTTP01]

    def perform(self, achallenges):
        responses = []
        for achall in achallenges:
            response = achall.gen_response(0)
            token_path = f"/home/daemoncraft/.well-known/acme-challenge/{achall.chall.encode('token')}"
            import os
            os.makedirs(os.path.dirname(token_path), exist_ok=True)
            with open(token_path, "w") as f:
                f.write(response.key_authorization)
            responses.append(response)
        return responses

    def cleanup(self, achallenges):
        import os
        for achall in achallenges:
            token_path = f"/home/daemoncraft/.well-known/acme-challenge/{achall.chall.encode('token')}"
            if os.path.exists(token_path):
                os.remove(token_path)

    def deploy_cert(self, domain, cert_path, key_path, chain_path, fullchain_path):
        pass

    def enhance(self, domain, enhancement, options=None):
        pass

    def supported_enhancements(self):
        return []

    def get_all_names(self):
        return []

    def save(self, title=None, message=None):
        pass

    def rollback(self, checkpoints):
        pass

    def restart(self):
        import subprocess
        subprocess.run(["pkill", "-HUP", "spyderfly"], check=False)