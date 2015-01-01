
Copyright (c) 2013-2014 X11Coin Developers


X11Coin 0.3.0 BETA

Copyright (c) 2013-2014 X11Coin Developers
Copyright (c) 2013 NovaCoin Developers
Copyright (c) 2011-2012 Bitcoin Developers
Distributed under the MIT/X11 software license, see the accompanying
file license.txt or http://www.opensource.org/licenses/mit-license.php.
This product includes software developed by the OpenSSL Project for use in
the OpenSSL Toolkit (http://www.openssl.org/).  This product includes
cryptographic software written by Eric Young (eay@cryptsoft.com).


Intro
-----
X11Coin is a free open source project derived from NovaCoin, with
the goal of providing a long-term energy-efficient scrypt-based crypto-currency.
Built on the foundation of Bitcoin and NovaCoin, innovations such as proof-of-stake
help further advance the field of crypto-currency.

Setup
-----
After completing windows setup then run windows command line (cmd)
  cd daemon
  x11coind
You would need to create a configuration file x11coin.conf in the default
wallet directory. Grant access to x11coind.exe in anti-virus and firewall
applications if necessary.

The software automatically finds other nodes to connect to.  You can
enable Universal Plug and Play (UPnP) with your router/firewall
or forward port 

23489 (TCP) to your computer so you can receive
incoming connections.  X11Coin works without incoming connections,
but allowing incoming connections helps the X11Coin network.

Upgrade
-------
All you existing coins/transactions should be intact with the upgrade.
To upgrade first backup wallet
x11coind backupwallet <destination_backup_file>
Then shutdown x11coind by
x11coind stop
Start up the new x11coind.


See the documentation/wiki at the X11Coin site:
  http://x11coin.cc/
for help and more information.

