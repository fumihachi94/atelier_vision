let loadOpencv = document.getElementById('opencv');
let video      = document.getElementById('videoInput');

var keyName;
let keyEvent   = document.addEventListener('keydown', (event) => {
    keyName = event.key;
});

const FPS = 30;
let streaming = false;

let src, dst, cap ;


function onOpenCvReady() {
    console.log("status ready");
    document.getElementById('status').innerHTML = 'OpenCV.js is ready.';
}
  
function onVideoReady(){
    video.height = 480;
    video.width = 640;
    src = new cv.Mat(video.height, video.width, cv.CV_8UC4);
    dst = new cv.Mat(video.height, video.width, cv.CV_8UC1);
    cap = new cv.VideoCapture(video);

    navigator.mediaDevices.getUserMedia({ video: true, audio: false }).then(function(_stream) {
        streaming = video.srcObject = _stream;
        video.play();
        // schedule the first one.
        setTimeout(processVideo, 0);
        console.log("Streaming Start.");
    }).catch(function(_err) {
        console.log("An error occurred! " + _err);
    });
}

function processVideo() {
    try {
        if (!streaming) {
            // clean and stop.
            console.log("end");
            src.delete();
            dst.delete();
            return;
        }
        let begin = Date.now();
        // start processing.
        cap.read(src);
        cv.cvtColor(src, dst, cv.COLOR_RGBA2GRAY);
        console.log(dst.width);
        cv.imshow('canvasOutput', dst);
        if(keyName == "s"){
            // console.log("Key : " + keyName);
            saveCanvas('canvasOutput');
            keyName = NaN;
        }
        // schedule the next one.
        let delay = 1000/FPS - (Date.now() - begin);
        setTimeout(processVideo, delay);
    } catch (_err) {
        console.log("An error occurred! " + _err);
    }
};

function saveCanvas(canvas_id)
{
	var canvas = document.getElementById(canvas_id);
	//アンカータグを作成
	var a = document.createElement('a');
	//canvasをJPEG変換し、そのBase64文字列をhrefへセット
	a.href = canvas.toDataURL('image/jpeg', 0.85);
	//ダウンロード時のファイル名を指定
	a.download = 'download.jpg';
	//クリックイベントを発生させる
	a.click();
}


loadOpencv.onload = function(){
    onOpenCvReady();
    onVideoReady();
}