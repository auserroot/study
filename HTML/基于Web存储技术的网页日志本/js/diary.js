var allrizi = document.getElementById("all");
getHistory();
var id = document.getElementById("id");
var date =document.getElementById("date");
var rizi = document.getElementById("rizi");

function getHistory(){	
	var txt = localStorage.length;
	var j=0;
	if (txt != 0){
		allrizi.innerHTML = "0";
		for(var i = 0;i < txt;i++ ){
		id = document.createElement("li");
		var key = date.toLocaleString();//获取本地格式时间
        id.innerHTML = localStorage.getItem(key);
		/*var name = localStorage.key(i);
		id.innerHTML = localStorage.getItem(name);*///获取Web存储数据
		allrizi.appendChild(xuhao);
		table.insertRow(j++);// 插入一行
        row.insertCell(2);//插入单元格
		}
	}

   

}
function saveDiary(){
	var now = new Date();//获取当前时间	
    var key = now.getTime();//将当前日期时间转换为时间戳
    localStorage.setItem(key,rizi);//将数据保存到Web存储
    
    getHistory();
}

function clearDiary(){
	
	localStorage.clear();//清空所有Web存储记录

}
