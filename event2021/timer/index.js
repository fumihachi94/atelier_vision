

function timerStartStop(){
    var obj = document.getElementById("st_end");
    if(obj.value == "▶"){
        obj.value = "■";
        obj.style.font.color = rgba(255, 24, 43, 1.0);
    }else{
        obj.value = "▶";
        obj.style.color = rgba(255, 24, 43, 1.0);
    }
}


//------------------


function countdown(){
    var count = document.getElementById("input_value").value;

var countdownid = setInterval(function(){
            count --;
  remain.innerHTML=count;
    if(count==0){
       clearInterval(countdownid);
       }
} ,1000);
}


var timer1; //タイマーを格納する変数（タイマーID）の宣言


//カウントダウン関数を1000ミリ秒毎に呼び出す関数
function cntStart()
{
  document.timer.elements[2].disabled=true;
  timer1=setInterval("countDown()",1000);
}

//タイマー停止関数
function cntStop()
{
  document.timer.elements[2].disabled=false;
  clearInterval(timer1);
}

//カウントダウン関数
function countDown()
{
  var min=document.timer.elements[0].value;
  var sec=document.timer.elements[1].value;
  
  if( (min=="") && (sec=="") )
  {
    alert("時刻を設定してください！");
    reSet();
  }
  else
  {
    if (min=="") min=0;
    min=parseInt(min);
    
    if (sec=="") sec=0;
    sec=parseInt(sec);
    
    tmWrite(min*60+sec-1);
  }
}

//残り時間を書き出す関数
function tmWrite(int)
{
  int=parseInt(int);
  
  if (int<=0)
  {
    reSet();
    alert("時間です！");
  }
  else
  {
    //残り分数はintを60で割って切り捨てる
    document.timer.elements[0].value=Math.floor(int/60);
    //残り秒数はintを60で割った余り
    document.timer.elements[1].value=int % 60;
  }
}

//フォームを初期状態に戻す（リセット）関数
function reSet()
{
  document.timer.elements[0].value="0";
  document.timer.elements[1].value="0";
  document.timer.elements[2].disabled=false;
  clearInterval(timer1);
}  













//-------------------------------------------------------
const setSeitchTimeThr = 1000;
var v_set = 100;
var ig = 0;

(window.onload = function() {
    document.getElementById("meterDisp").src = "image/meter_igoff.jpg";
    document.getElementById("setVelocityBase").style.display = "none";
    document.getElementById("setVelocity").style.display = "none";
})();

// パワースイッチONでメータ表示
function ignitionON(){
    const elements = document.getElementsByName("ignition");
    ig = elements[0].checked;
    if(ig){
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


window.onload = function(){
    var $res = document.getElementById("res");
    $res.onmousedown = fonction($event) 
    {
        if($event.button == 0){
            console.log("test");
            v_set -= 1;
            document.getElementById("setVelocity").textContent = v_set;
        }
    }
}