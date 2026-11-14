CC = gcc
CFLAGS = -Wall -Wextra -g -O0 \
         -Isrc \
         -Isrc/core \
         -Isrc/lib \
         -Isrc/os \
         -Isrc/misc \
         -Isrc/misc/auto-config

# Explicitly list all source modules across your directory tree (fixed missing src/ prefix)
SRCS = src/core/main.c \
       src/core/load_sites.c \
       src/core/log.c \
       src/core/site_bind.c \
       src/core/site_config.c \
       src/core/site_upstream.c \
       src/core/start_spyderfly.c \
       src/misc/auto-config/auto-config.c \
       src/misc/auto-config/created.c \
       src/misc/auto-config/directory.c \
       src/misc/auto-config/http.c \
       src/misc/auto-config/https.c \
       src/misc/auto-config/lan_ip.c \
       src/misc/auto-config/manual.c \
       src/misc/auto-config/presets.c \
       src/misc/auto-config/proxy.c

# Map src/file.c to objs/src/file.o to preserve the src directory structure under objs/
OBJS = $(patsubst src/%.c, objs/src/%.o, $(SRCS))
TARGET = objs/spyderfly

# Installation paths
PREFIX ?= /usr
SBINDIR ?= $(PREFIX)/sbin
MAIN_DIR = /etc/spyderfly
SITES_DIR = $(MAIN_DIR)/enabled-sites
CONF_DIR = $(MAIN_DIR)/config
DIS_SITE = $(MAIN_DIR)/disabled-sites
LOG_DIR = /var/log/spyderfly

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) -lssl -lcrypto -lpthread

# Automatically create nested objs/src/... subdirectories before compiling each object file
objs/src/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

install: all
	@echo "Creating SpyderFly system directories..."
	install -d -m 755 $(MAIN_DIR)
	install -d -m 755 $(SITES_DIR)
	install -d -m 755 $(CONF_DIR)
	install -d -m 755 $(DIS_SITE)
	install -d -m 755 $(LOG_DIR)
	@echo "Installing binary to $(SBINDIR)/spyderfly..."
	install -m 755 $(TARGET) $(SBINDIR)/spyderfly
	@echo "SpyderFly installation completed successfully."

clean:
	rm -rf objs

.PHONY: all install clean
