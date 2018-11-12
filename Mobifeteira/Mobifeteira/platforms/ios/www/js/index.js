
var AppSocketId, AppSocketIdS;
var ip = "192.168.1.204";
var myip;

var app = {
    initialize: function() {
        /*if(document.codova)*/ document.addEventListener('deviceready', this.onDeviceReady.bind(this), false);
        /*else this.receivedEvent();*/
    },

    onDeviceReady: function() {
        this.receivedEvent('deviceready');
    },

    // Update DOM on a Received Event
    receivedEvent: function(id) {
        phonon.options({
            navigator: {
                defaultPage: 'mainpage',
                defaultTemplateExtension: 'html',
                animatePages: false,
                enableBrowserBackButton: true,
                templateRootDirectory: './'
            },
                i18n: {
                directory: 'res/lang/',
                localePreferred: 'pt'
            }
        });
        var ui = phonon.navigator();

        ui.start();

        document.getElementById("ipconfig").value = ip;
        createSocket(ip,  7777);
    }
};

function createSocket(ip, porta){
    chrome.sockets.tcpServer.onAccept.addListener(function (ev){
        alert("Conectaram no socket");
    });
    chrome.sockets.tcp.onReceive.addListener(function (ev){
        alert(JSON.stringify(ev));
        document.getElementById("resposta_r").value = JSON.stringify(ev);
    });
    
    networkinterface.getWiFiIPAddress(function( ipInformation ) {
        myip = ipInformation.ip;
        alert(myip);
        //server
        chrome.sockets.tcpServer.create(function(ev){
            AppSocketIdS = ev.socketId;
            alert("Server socket Open");
            chrome.sockets.tcpServer.listen(AppSocketIdS, myip, 7777, function (ev2){
                if (ev2 >= 0){
                    chrome.sockets.tcp.create(function(ev){
                        AppSocketId = ev.socketId;
                        alert("Send socket Open");
                        chrome.sockets.tcp.connect(AppSocketId, ip, porta, function(ev2){
                            chrome.sockets.tcp.setPaused(AppSocketId, false);
                            if (ev2 >= 0){
                                alert("Conectado");
                            } else {
                                return false;
                            }
                        });
                    });
                } else {
                    return false;
                }  
            });     
        });
    }, function onError( error ) {
        alert( error );
    });
}

//Guarda os setIntervals
var EnviaF, EnviaR, EnviaD, EnviaE;
var EnviaP, EnviaT;
var EnviaV, EnviaB, EnviaN, EnviaM;

/* ACELERA */
document.getElementById("SINAL_ACELERA").addEventListener("touchstart", function(ev){
    EnviaF = setInterval(function(){
        let data = getData({text: "F"});
        chrome.sockets.tcp.send(AppSocketId, data, function(result) {});
    }, 10);
});
document.getElementById("SINAL_ACELERA").addEventListener("touchend", function(ev){
    clearInterval(EnviaF);
});

/* RE */
document.getElementById("SINAL_RE").addEventListener("touchstart", function(ev){
    EnviaR = setInterval(function(){
        let data = getData({text: "R"});
        chrome.sockets.tcp.send(AppSocketId, data, function(result) {});
    }, 10);
});
document.getElementById("SINAL_RE").addEventListener("touchend", function(ev){
    clearInterval(EnviaR);
});

/* DIREITA */
document.getElementById("SINAL_DIREITA").addEventListener("touchstart", function(ev){
    EnviaD = setInterval(function(){
        let data = getData({text: "D"});
        chrome.sockets.tcp.send(AppSocketId, data, function(result) {});
    }, 10);
});
document.getElementById("SINAL_DIREITA").addEventListener("touchend", function(ev){
    clearInterval(EnviaD);
});

/* ESQUERDA */
document.getElementById("SINAL_ESQUERDA").addEventListener("touchstart", function(ev){
    EnviaE = setInterval(function(){
        let data = getData({text: "E"});
        chrome.sockets.tcp.send(AppSocketId, data, function(result) {});
    }, 10);
});
document.getElementById("SINAL_ESQUERDA").addEventListener("touchend", function(ev){
    clearInterval(EnviaE);
});

/* PARAR *//*
document.getElementById("SINAL_PARAR").addEventListener("touchstart", function(ev){
    EnviaP = setInterval(function(){
        let data = getData({text: "P"});
        chrome.sockets.tcp.send(AppSocketId, data, function(result) {});
    }, 10);
});
document.getElementById("SINAL_PARAR").addEventListener("touchend", function(ev){
    clearInterval(EnviaP);
});*/

/* TELEOP */
document.getElementById("SINAL_TELEOP").addEventListener("click", function(ev){
    let data = getData({text: "T"});
    chrome.sockets.tcp.send(AppSocketId, data, function(result) {});
    let s = document.getElementById("teleop_status");
    if (s.innerText == "Teleoperando")
        s.innerText = "Autônomo";
    else
        s.innerText = "Teleoperando";
});

/* AUMLIN */
document.getElementById("SINAL_AUMLIN").addEventListener("click", function(ev){
    let data = getData({text: "V"});
    chrome.sockets.tcp.send(AppSocketId, data, function(result) {});
});

/* DIMLIN */
document.getElementById("SINAL_DIMLIN").addEventListener("click", function(ev){
    let data = getData({text: "N"});
    chrome.sockets.tcp.send(AppSocketId, data, function(result) {});
});

/* AUMANG */
document.getElementById("SINAL_AUMANG").addEventListener("click", function(ev){
    let data = getData({text: "B"});
    chrome.sockets.tcp.send(AppSocketId, data, function(result) {});
});

/* DIMANG */
document.getElementById("SINAL_DIMANG").addEventListener("click", function(ev){
    let data = getData({text: "M"});
    chrome.sockets.tcp.send(AppSocketId, data, function(result) {});
});

/* ChangeIP */
document.getElementById("submitNewIP").addEventListener("click", function(ev){
    let data = document.getElementById("ipconfig").value;
    ip = data;

    chrome.sockets.tcpServer.disconnect(AppSocketIdS, function (ev){
        chrome.sockets.tcp.disconnect(AppSocketId, function (ev){
            alert("Server socket re-open");
            chrome.sockets.tcpServer.listen(AppSocketIdS, myip, 7778, function (ev2){
                if (ev2 >= 0){
                    alert("Send socket re-open ");
                    chrome.sockets.tcp.connect(AppSocketId, ip, 7777, function(ev2){
                        if (ev2 >= 0){
                            alert("Conectado");
                        } else {
                            
                            return false;
                        }
                    });
                } 
            });     
        });
    });
});

function getData(msg){
    let size = msg.text.length;

    let data = new Uint8Array(size);
    for (let x = 0; x < size; x++){
        data[x] = msg.text.charCodeAt(x);
    }
    
    return data.buffer;
}

app.initialize();