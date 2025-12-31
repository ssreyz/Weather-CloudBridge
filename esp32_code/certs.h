#ifndef CERTS_H
#define CERTS_H

#include <pgmspace.h>

// ------------------ Thing & Wi-Fi ------------------

// AWS IoT Thing Name
#define THING_NAME "esp32_1"

// Wi-Fi Credentials
const char WIFI_SSID[] = "OPPO";
const char WIFI_PASSWORD[] = "panda123";

// AWS IoT Endpoint
const char AWS_IOT_ENDPOINT[] =
  "a3ef8g4t9p41mb-ats.iot.us-east-1.amazonaws.com";

// ------------------ Certificates ------------------

// Amazon Root CA 1
static const char AWS_ROOT_CA[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
...
-----END CERTIFICATE-----
)KEY";

// Device Certificate
static const char DEVICE_CERT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWTCCAkGgAwIBAgIUe5deddEKMPwuV4yJWAudIeZNOVYwDQYJKoZIhvcNAQEL
...
-----END CERTIFICATE-----
)KEY";

// Device Private Key
static const char DEVICE_PRIVATE_KEY[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEogIBAAKCAQEAnMGKRDgV1TeqkSDgTaVjop179sfR2eMZ18R/fnINYnd8rR8n
...
-----END RSA PRIVATE KEY-----
)KEY";

#endif
