# SpyderFly Web Server
SpyderFly is a custom web server I started developing after I wanted to try Pingora. I had a thought: "This is like developing my own web server"... Then I began working. The goal of SpyderFly is to create an easy to manage web server. Worry about creating your website, not managing the web server. It's inspired by NGINX and meant to work in a similar way. I started the SpyderFly project on September 12, 2026.

# Install
SpyderFly has a repository you can add. Currently no support for other Distros than Debian/Ubuntu systems. It is possible, I'm just used to Debian and that comes first. When released, SpyderFly for Debian will be the priority and will come first. RHEL & Arch will get support eventually. Other Distros like Slackware, OpenSUSE, Gentoo, etc. may happen some day. FreeBSD may happen some day. Unlikely Windows support will happen ever, but never say never. If I get bored enough, it'll happen.

```
curl -fsSL https://repo.sizablesplash.com/pubkey.gpg | sudo gpg --dearmor -o /etc/apt/trusted.gpg.d/sizablesplash.gpg
echo "deb [arch=amd64 signed-by=/etc/apt/trusted.gpg.d/sizablesplash.gpg] https://repo.sizablesplash.com/spyderfly stable main" | sudo tee /etc/apt/sources.list.d/spyderfly.list
sudo apt update
sudo apt install spyderfly
```

At any point in time, you are free to download SpyderFly's code and compile it yourself. Assuming you have build-essentials and libssl installed, open the root folder and run `sudo make` in your terminal. You'll see the binary output in objs. If you run `sudo make install` it'll create the folders and output the binary. Once you run `sudo spyderfky -s` it'll start right up. The script will not create a daemon system yet.


# Other Distros
As far as I'm aware, SpyderFly should work on other Distros, but I have not tested it. Untill I setup a packager for them, you can install it manually. The code should be portable.

# What SpyderFly Offers
Nginx is a very versatile web server. When it works, it's very stable. Except one time it randomly shut down and I still don't know why. My biggest issue is its all or nothing config. Yeah, you can disable the site, but I didn't know that. There's a lot of working cogs and if something goes wrong, everything goes wrong. If you have a broken configuration, your entire web server goes down. At the time of writing this, these features I'm about to list are not made yet. They Will most likely be released in version 1.0. 
Spyderfly has a built in auto config for sites. It allows you to create your site with ease. SpyderFly also has a certbot plugin as part of the install. If you desire to not install it, you can hit no at the prompt during the install. If you ever desire to do so later on, just run ```sudo spyderfly --certbot``` and it'll run you through the post install script. Or download the install file from https://repo.sizablesplash.com/spyderfly/ Once installed, run ```sudo certbot --spyderfly -d example.domain.com``` to deploy your certificate.

DaemonCraft is a branch of SpyderFly. A Minecraft server manager I made to branch off from SpyderFly. Its foundation is SpyderFly and working on DaemonCraft helped me fix issues I was having with SpyderFly.

project started: 9/12/26
project release: TBD
