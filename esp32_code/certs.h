
#define CERTS_H

#include <pgmspace.h>

// ------------------ Thing & Wi-Fi ------------------

// AWS IoT Thing Name
#define THING_NAME "YOUR THINGS NAME"

// Wi-Fi Credentials
const char WIFI_SSID[] = "ur wifi name";
const char WIFI_PASSWORD[] = "password";

// AWS IoT Endpoint
const char AWS_IOT_ENDPOINT[] =
  "xxxats.iot.us-east-1.amazonaws.com";

// ------------------ Certificates ------------------

// Amazon Root CA 1
static const char AWS_ROOT_CA[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
...
-----END CERTIFICATE-----
)KEY";

// Device Certificate
static const char DEVICE_CERT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
...
-----END CERTIFICATE-----
)KEY";

// Device Private Key
static const char DEVICE_PRIVATE_KEY[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
...
-----END RSA PRIVATE KEY-----
)KEY";

