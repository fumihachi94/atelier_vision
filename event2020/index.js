const setSeitchTimeThr = 1000;
var v_set = 100;


// パワースイッチONでメータ表示
function ignitionON(){
    const elements = document.getElementsByName("ignition");
    if(elements[0].checked){
        document.getElementById("meterDisp").src = "image/meter_base.jpg";
        document.getElementById("setVelocityBase").style.display = "block";
        document.getElementById("setVelocity").style.display = "block";
        document.getElementById("setVelocity").textContent = v_set;
    }else{
        document.getElementById("meterDisp").src = "image/meter_igoff.jpg";
        document.getElementById("setVelocityBase").style.display = "none";
        document.getElementById("setVelocity").style.display = "none";
    }
}

// +RESスイッチ押下
function pushRES(){
    v_set += 1;
    document.getElementById("setVelocity").textContent = v_set;
    
    // let count = 0;
    // let timer;

    // var pop = function(){
    //     v_set += 5;
    //     document.getElementById("setVelocity").textContent = v_set;
    // }

    // timer = setInterval(pop ,1000);

}

// +SETスイッチ押下
function pushSET(){
    v_set -= 1;
    document.getElementById("setVelocity").textContent = v_set;
}