Generate SSL certs
==================

1. Run `make exec-apache`
2. Then run in the Docker shell  `certbot --apache -d projectstreet.dynu.com -m info@nordgedanken.de -n --agree-tos`
