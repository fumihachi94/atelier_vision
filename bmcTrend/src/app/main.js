function editContent() {
    var topContent = document.getElementById('topContent');
    topContent.contentEditable = 'true';
}

function saveContent() {
    // <html> を clone
    var html = document.getElementsByTagName('html')[0].cloneNode(true);
    console.log(html);
    console.log("-----------------log---------------");

    // href や src に指定されたURLを絶対パスに変換
    var nodes = html.querySelectorAll('[href],[src]');
    for (var i = 0, n = nodes.length; i < n; i++) {
        if (nodes[i].href) { nodes[i].href = nodes[i].href; }
        if (nodes[i].src) { nodes[i].src = nodes[i].src; }
        //console.log('href: ' + nodes[i].href + ', src: ' + nodes[i].src);
    }

    // ソースコードをテキストで取得
    var src = html.innerHTML;
    //console.log(src.slice(0, 5000));

    // 上記の src には DOCTYPE が含まれていないので別途用意
    var name = document.doctype.name;
    var publicId = document.doctype.publicId;
    var systemID = document.doctype.systemId;
    var doctype = '<!DOCTYPE ' + name
        + (publicId ? ' PUBLIC "' + publicId + '"' : '')
        + (systemID ? ' "' + systemID + '"' : '')
        + '>';
    console.log(doctype);

    // <html> タグを再構成
    var htmlTag = '<html';
    var attrs = html.attributes;
    for (var i = 0, n = attrs.length; i < n; i++) {
        var attr = attrs[i];
        htmlTag += ' ' + attr.nodeName + (attr.nodeValue ? '="' + attr.nodeValue + '"' : '');
    }
    htmlTag += '>';
    console.log(htmlTag);

    // ソースコードを Blob オブジェクトに変換してURLを取得
    var blob = new Blob([doctype, '\n', htmlTag, '\n', src, '\n</html>']);
    var url = window.URL || window.webkitURL;
    var blobURL = url.createObjectURL(blob);
    console.log(blobURL);

    // <a> を新たに作成し、ダウンロード用の設定をいろいろ
    var a = document.createElement('a');
    // URI を元にダウンロード時のファイル名を決定
    const filePath = location.pathname;
    const arr = filePath.split("/");
    a.download = arr.slice(-1)[0];
    a.href = blobURL;

    a.click();
}

function adjust_frame_css(){
  if(document.getElementById('compare')) {
    var myF = document.getElementById('compare');
    myF.style.width = myF.contentWindow.document.body.scrollWidth + "px";
    myF.style.height = myF.contentWindow.document.body.scrollHeight + "px";
  }
}
