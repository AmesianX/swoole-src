/*
  +----------------------------------------------------------------------+
  | Swoole                                                               |
  +----------------------------------------------------------------------+
  | This source file is subject to version 2.0 of the Apache license,    |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.apache.org/licenses/LICENSE-2.0.html                      |
  | If you did not receive a copy of the Apache2.0 license and are unable|
  | to obtain it through the world-wide-web, please send a note to       |
  | license@swoole.com so we can mail you a copy immediately.            |
  +----------------------------------------------------------------------+
  | Author: Tianfeng Han  <mikan.tenny@gmail.com>                        |
  +----------------------------------------------------------------------+
*/

#pragma once

#define SW_SOCKS5_VERSION_CODE 0x05

enum swHttp_proxy_state {
    SW_HTTP_PROXY_STATE_WAIT = 0,
    SW_HTTP_PROXY_STATE_HANDSHAKE,
    SW_HTTP_PROXY_STATE_READY,
};

struct swHttp_proxy {
    uint8_t state;
    uint8_t dont_handshake;
    int proxy_port;
    const char *proxy_host;
    const char *user;
    const char *password;
    int l_user;
    int l_password;
    const char *target_host;
    int l_target_host;
    int target_port;
    char buf[512];
};

enum swSocks5_state {
    SW_SOCKS5_STATE_WAIT = 0,
    SW_SOCKS5_STATE_HANDSHAKE,
    SW_SOCKS5_STATE_AUTH,
    SW_SOCKS5_STATE_CONNECT,
    SW_SOCKS5_STATE_READY,
};

enum swSocks5_method {
    SW_SOCKS5_METHOD_AUTH = 0x02,
};

struct swSocks5_proxy {
    const char *host;
    int port;

    uint8_t state;
    uint8_t version;
    uint8_t method;
    uint8_t dns_tunnel;

    const char *username;
    const char *password;
    uint16_t l_username;
    uint16_t l_password;

    const char *target_host;
    int target_port;
    uint16_t l_target_host;

    char buf[600];
};

static sw_inline void swSocks5_pack(char *buf, int method) {
    buf[0] = SW_SOCKS5_VERSION_CODE;
    buf[1] = 0x01;
    buf[2] = method;
}

const char *swSocks5_strerror(int code);
int swSocks5_connect(swoole::network::Client *cli, char *recv_data, int length);
