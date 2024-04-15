#!/bin/bash

RED="\033[0;38;5;199m"
BLUE="\033[0;38;5;44m"
GREEN="\033[0;32m"
NC="\033[0m" # No Color
cd /home/${USER}/sgoinfre


if ! command -v brew &>/dev/null; then
    echo -e "${BLUE}Installing Homebrew...${NC}"
    git clone https://github.com/Homebrew/brew homebrew
    eval "$(homebrew/bin/brew shellenv)"
    brew update --force --quiet
    chmod -R go-w "$(brew --prefix)/share/zsh"
    echo -e "eval \"\$($(brew --prefix)/bin/brew shellenv)\"" >> ~/.zshrc
else
    echo -e "${GREEN}Homebrew is already installed.${NC}"
fi




if ! brew list mkcert &>/dev/null; then
    echo -e "${BLUE}Installing mkcert...${NC}"
    brew install mkcert
else
    echo -e "${GREEN}mkcert is already installed.${NC}"
fi


if ! brew list nss &>/dev/null; then
    echo -e "${BLUE}Installing nss...${NC}"
    brew install nss
else
    echo -e "${GREEN}nss is already installed.${NC}"
fi


CERT_DIR="${HOME}/certs"
rm -rf "${CERT_DIR}"
mkdir -p "${CERT_DIR}" 


CURRENT_IP=$(hostname -I | awk '{print $1}')
echo -e "${BLUE}Setting up SSL certificates...${NC}"
mkcert -key-file "${CERT_DIR}/nginx.key" -cert-file "${CERT_DIR}/nginx.crt" localhost "${CURRENT_IP}" "42pong.ddns.net" &>/dev/null

PROM_CERTS="${HOME}/certs/certs_prometheus"
rm -rf "${PROM_CERTS}"
mkdir -p "${PROM_CERTS}" 

echo -e "${BLUE}Setting up SSL certificates for prometheus...${NC}"
mkcert -key-file "${PROM_CERTS}/prometheus.key" -cert-file "${PROM_CERTS}/prometheus.crt" localhost "${CURRENT_IP}" prometheus &>/dev/null
chmod 777 ${PROM_CERTS}/prometheus.key
chmod 777 ${PROM_CERTS}/prometheus.crt

NODE_CERTS="${HOME}/certs/certs_node"
rm -rf "${NODE_CERTS}"
mkdir -p "${NODE_CERTS}"

echo -e "${BLUE}Setting up SSL certificates for node...${NC}"
mkcert -key-file "${NODE_CERTS}/node.key" -cert-file "${NODE_CERTS}/node.crt" localhost "${CURRENT_IP}" prometheus-node-exporter &>/dev/null
chmod 777 ${NODE_CERTS}/node.key
chmod 777 ${NODE_CERTS}/node.crt

ALERT_CERTS="${HOME}/certs/certs_alert"
rm -rf "${ALERT_CERTS}"
mkdir -p "${ALERT_CERTS}"

echo -e "${BLUE}Setting up SSL certificates for alert...${NC}"
mkcert -key-file "${ALERT_CERTS}/alert.key" -cert-file "${ALERT_CERTS}/alert.crt" localhost "${CURRENT_IP}" alertmanager &>/dev/null
chmod 777 ${ALERT_CERTS}/alert.key
chmod 777 ${ALERT_CERTS}/alert.crt


GRAFANA_CERTS="${HOME}/certs/certs_grafana"
rm -rf "${GRAFANA_CERTS}"
mkdir -p "${GRAFANA_CERTS}"

echo -e "${BLUE}Setting up SSL certificates for grafana...${NC}"
mkcert -key-file "${GRAFANA_CERTS}/grafana.key" -cert-file "${GRAFANA_CERTS}/grafana.crt" localhost "${CURRENT_IP}" grafana &>/dev/null
chmod 777 ${GRAFANA_CERTS}/grafana.key
chmod 777 ${GRAFANA_CERTS}/grafana.crt


echo -e "${GREEN}SSL certificates created!${NC}"
