(function(){
	var element_file = document.getElementById("input");
	var element_result = document.getElementById("support");

	// ------------------------------------------------------------
	// サポート状況
	// ------------------------------------------------------------
	if(window.File){
		element_result.value = "File クラスに対応しています";
        console.log("vslu");
		return;
	}
	if(!window.FileReader){
		element_result.value = "FileReader クラスに対応していません。";
		return;
	}
})