cordova.define('cordova/plugin_list', function(require, exports, module) {
module.exports = [
  {
    "id": "cz.blocshop.socketsforcordova.Socket",
    "file": "plugins/cz.blocshop.socketsforcordova/socket.js",
    "pluginId": "cz.blocshop.socketsforcordova",
    "clobbers": [
      "window.Socket"
    ]
  },
  {
    "id": "cordova-plugin-chrome-apps-common.events",
    "file": "plugins/cordova-plugin-chrome-apps-common/events.js",
    "pluginId": "cordova-plugin-chrome-apps-common",
    "clobbers": [
      "chrome.Event"
    ]
  },
  {
    "id": "cordova-plugin-chrome-apps-common.errors",
    "file": "plugins/cordova-plugin-chrome-apps-common/errors.js",
    "pluginId": "cordova-plugin-chrome-apps-common"
  },
  {
    "id": "cordova-plugin-chrome-apps-common.stubs",
    "file": "plugins/cordova-plugin-chrome-apps-common/stubs.js",
    "pluginId": "cordova-plugin-chrome-apps-common"
  },
  {
    "id": "cordova-plugin-chrome-apps-common.helpers",
    "file": "plugins/cordova-plugin-chrome-apps-common/helpers.js",
    "pluginId": "cordova-plugin-chrome-apps-common"
  },
  {
    "id": "cordova-plugin-chrome-apps-sockets-tcp.sockets.tcp",
    "file": "plugins/cordova-plugin-chrome-apps-sockets-tcp/sockets.tcp.js",
    "pluginId": "cordova-plugin-chrome-apps-sockets-tcp",
    "clobbers": [
      "chrome.sockets.tcp"
    ]
  },
  {
    "id": "cordova-plugin-network-information.network",
    "file": "plugins/cordova-plugin-network-information/www/network.js",
    "pluginId": "cordova-plugin-network-information",
    "clobbers": [
      "navigator.connection",
      "navigator.network.connection"
    ]
  },
  {
    "id": "cordova-plugin-network-information.Connection",
    "file": "plugins/cordova-plugin-network-information/www/Connection.js",
    "pluginId": "cordova-plugin-network-information",
    "clobbers": [
      "Connection"
    ]
  },
  {
    "id": "cordova-plugin-networkinterface.networkinterface",
    "file": "plugins/cordova-plugin-networkinterface/www/networkinterface.js",
    "pluginId": "cordova-plugin-networkinterface",
    "clobbers": [
      "window.networkinterface"
    ]
  },
  {
    "id": "cordova-plugin-chrome-apps-sockets-tcpserver.sockets.tcpServer",
    "file": "plugins/cordova-plugin-chrome-apps-sockets-tcpserver/sockets.tcpServer.js",
    "pluginId": "cordova-plugin-chrome-apps-sockets-tcpserver",
    "clobbers": [
      "chrome.sockets.tcpServer"
    ]
  },
  {
    "id": "cordova-plugin-chrome-apps-sockets-udp.sockets.udp",
    "file": "plugins/cordova-plugin-chrome-apps-sockets-udp/sockets.udp.js",
    "pluginId": "cordova-plugin-chrome-apps-sockets-udp",
    "clobbers": [
      "chrome.sockets.udp"
    ]
  }
];
module.exports.metadata = 
// TOP OF METADATA
{
  "cordova-plugin-whitelist": "1.3.3",
  "cz.blocshop.socketsforcordova": "1.1.0",
  "cordova-plugin-chrome-apps-common": "1.0.7",
  "cordova-plugin-chrome-apps-sockets-tcp": "1.3.8-dev",
  "cordova-plugin-network-information": "2.0.1",
  "cordova-plugin-networkinterface": "2.0.0",
  "cordova-plugin-chrome-apps-sockets-tcpserver": "1.2.4",
  "cordova-plugin-chrome-apps-sockets-udp": "1.3.0"
};
// BOTTOM OF METADATA
});